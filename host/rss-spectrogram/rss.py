import binascii,datetime,socket,sys
from struct import unpack_from
from time import gmtime, strftime

#globals
channels = 0
bytes = 0
parameters = {}  #headers/metadata read in from first bytes
remainder = 0    #starting point for any left over data
data = []        #current raw data
channels_read = 0

"""
Connects to and reads an rss formatted stream from rasdrproc.
Normal usage from another module is:

  from rss import rss
  r = rss()
  rtl_power_lines = r.read_data()   #rtl_power_lines can be ignored, but are lines of rtl_power like output

  do something with r.data, r.remainder is an index to unprocessed raw bytes
"""

class rss:
    def __init__(self):
        self.channels = 0
        self.bytes = 0
        self.parameters = {}  #headers/metadata read in from first bytes
        self.remainder = []   #starting point for any left over data
        self.data = []        #current data
        self.channels_read = 0
        self.setup()
        #remainder.index,self.data,self.rasdrsocket = self.setup()
        
    def stringify_csv_list(self,list):
        '''
        Simple function to concatenate a list of numbers with commas.
        '''
        s = [str(element) for element in list]
        return ','.join(s)

    def make_timestamp(self):
        '''
        make an rtl_power timestamp from current time
        '''
        now = datetime.datetime.now()
        hr = str(now.hour)
        minute = str(now.minute)
        second = str(now.second)

        year = str(now.year)
        month = str(now.month)
        day = str(now.day)
        
        datestr = '-'.join([year,month,day]) + ' , '  #E.g. '2016-7-24 , ' 
        timestr = ':'.join([hr,minute,second])
        timestamp = datestr + timestr
        return timestamp

    def process_header(self):
        '''
        Given a first chunk of bytes from the rasdproc stream,
        identify the metadata such channels
        return to an index to the rest of the bytes
        that are actual data.
        '''
        d =str(self.data[0:100],'ascii', 'ignore') #guess that metadata is in first 100 bytes
        i = d.find('|')
        center_frequency = float(d[1:i])
    
        self.parameters['center_frequency'] = center_frequency
        begin = i+2
        i = d.find('|',begin)
        bandwidth_hertz = float(d[begin:i])
        self.parameters['bandwidth_hertz'] = bandwidth_hertz
        begin = i+2
        i = d.find('|',begin)
        offset_hertz = float(d[begin:i])
        self.parameters['offset_hertz'] = offset_hertz
        begin = i+2
        i = d.find('|',begin)
        self.channels = int(d[begin:i])
        self.parameters['channels'] = self.channels
        i = i + 3     #skip \n\r
        #print center_frequency,bandwidth_hertz,offset_hertz,self.channels
        self.bytes = self.channels * 2 #short (signed int)
        return i  #return index to rest of data

    def process(self,start,timestamp):
        '''
        Process scans.  data constitutes 2 bytes of unsigned bytes ending with a -258.
        returns an index to starting point of any unused data and an array of lines in the rtl_power format.
        '''
        lines = []
        size = len(self.data)
        unpack_spec = str(self.channels+2) +'h'  #unsigned shorts
        endmarker = size -1
        cf = self.parameters['center_frequency']
        bw = self.parameters['bandwidth_hertz']
        half_bw = bw/2.0
        lo = cf - half_bw
        hi = cf + half_bw
        step = bw/self.channels
        scan_size = (self.channels*2)+4
        #print 'unpack_spec',unpack_spec,' start ',start,' size',size
        while (start+scan_size <= size and size >= scan_size):
            dbm = list(unpack_from(unpack_spec,self.data[start:]))
            end_index = len(dbm)
            skip = 2
            #print 'start ' + str(start) + ' end_index ' + str(end_index) + ' length dbm ' + str(len(dbm))
            for i in range(0,end_index):
                if dbm[i] == -258: #look for terminator
                    #print "** ",dbm[i-1],dbm[i],dbm[i+1],i,size
                    break
            if (i < end_index):
                dbm_new = dbm[0:i-1] #exclude terminator
                dbm = dbm_new + dbm[i+1:]
            #print len(dbm),size
            dbm.reverse() #now frequencies lowest to highest
            #create a line mimicing rtl_power output 
            line = ','.join([timestamp,str(int(lo)),str(int(hi)),str(int(step)),str(10000000),self.stringify_csv_list(dbm)])
            lines.append(line)
            start = start + (self.channels * 2) + 2 #skip last value (two bytes per value)
            #print "** ",start
        return start,lines

    def get_more_data(self,size):
        return self.rasdrsocket.recv(size)

    def read_data(self):
        '''
        create a timestamp from current time
        process bytes for a scan
        process bytes for more scans until incomplete scan is reached
        make another timestamp
        read more bytes (up to 10 scans worth)
        process bytes for more scans until incomplete scan is reached
        return lines of rtl_power formatted strings, an index to the rest of the unprocessed data, and all the raw data itself.
        '''
        results = []
        timestamp = self.make_timestamp()
        self.remainder,lines = self.process(self.remainder,timestamp)
        #print "read_data", len(lines), self.remainder,len(self.data)
        #print results
        results.extend(lines)
        #print "process results " + str(len(results))
        scan_size = (self.channels*2) + 4
        while (self.remainder <= len(self.data) - scan_size and len(self.data) >= scan_size): 
            self.remainder,lines = self.process(self.remainder,timestamp)
            results.extend(lines)
            #print '*** ',self.remainder,len(self.data),len(lines),len(results)
        timestamp = self.make_timestamp()
        data2  = self.rasdrsocket.recv((self.channels*2*10))  #receive up to 10 scans worth of bytes
        #print "data2 bytes "+ str(len(data2))
        self.data = self.data[self.remainder:] + data2
        self.remainder = 0
        #print "self.data ",len(self.data)
        self.remainder,lines = self.process(self.remainder,timestamp)
        results.extend(lines)
        return results
        
    def loop(self):
        while (True):
            self.read_data()

    def setup(self):
        '''
        set up socket and read some data
        returns unused data index(remainder), all the data, and a connected socket instance.
        '''
        self.setupsocket()

    def setupsocket(self):
        '''
        create and connect to socket.
        read 2048 bytes
        process header
        return unprocessed bytes which may be 1..n scans
        '''
        self.rasdrsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        z = None
        self.remainder = 0
        try:
            self.rasdrsocket.connect(('127.0.0.1',8888))
        except Exception as e:
            z = e
            print( "Connection failure:  check that rasdrproc is running and RSS output is enabled.")
            print( "If true, then check Windows Firewall settings and/or any security software to ensure that port 8888 is accessible from localhost/127.0.0.1")
            print("  " + str(z))
            exit(-1)
        print("connected to rasdrproc")
        self.data = self.rasdrsocket.recv(2048)
        #print 'received ',len(self.data)
        self.remainder = self.process_header()
        #,data,rasdrsocket
        
