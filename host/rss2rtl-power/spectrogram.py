import os, sys, gzip, math, argparse, colorsys, datetime
from collections import defaultdict
from itertools import *

from matplotlib import cm
import numpy
from numpy import linspace
from numpy import zeros
from numpy import array

import pygame   #1.9.2

from LogMixIn import LogMixIn
'''
Spectrogram rendering using Extended RSS format.
This class is designed to be instantiated by rss-power and used by rss2rtlpower when a new scan arrives.

3 temporal streams from left to right:
  a) realtime, where a row is a received scan
  b) 10x, where a row represents the average of 10 scans
  c) 100x, where a row represents the average of 100 scans

If the streams generator is producing 64 frames a second, then 600 lines in the 100x stream represents about 15 1/2 minutes
and the 10x stream about 94 seconds.

Perceptually uniform color maps (files) obtained from two sources below.
Matplotlib has a set of colormaps from which to choose, see assign_matplotlib_colormap().

http://peterkovesi.com/projects/colourmaps/
isoluminant_cgo_70_c39_n256

http://www.kennethmoreland.com/color-advice/
extended-blackbody
'''
class Spectrogram(LogMixIn):
    #constants and defaults
    MAX_BINS = 100
    BLACK = (0, 0, 0)
    GREEN = (0, 255, 0)
    RIGHT = 3
    linear_map = None
    upper_y = 15
    min_z = 99999
    max_z = -99999
    colormap = []  # linear spaced created colormap
    opts = None
    db_min = -30
    db_max = 30

    #connection metadata
    channels = 0
    center_freq_mhz = 0
    bandwidth_hz = 0
    bandwidth_mhz = 0
    base_freq_mhz = 0
    offset_hz = 0
    channel_resolution_khz = 0

    #bookeeping, dimensions, ...
    scans = 0
    compression_y = 0
    color_key_width = 0
    horiz_spacer = 0
    horizontal_compression = 0
    color_key_label_horiz_space = 0
    streams = 0
    stream_db = None
    stream_samples = None  #3d array
    stream_index  = 0

    screen = None
    compression_count = 0
    compression_count_100 = 0
    compression_power = []
    compression_power_100 = []
    compression_target = 0
    surf = None
    surf_integrated_power = None
    surf_integrated_power_100 = None
    x_integrated = 0   #FIX ME:  rename to x_integrated_10 to indicate integration/average of 10 scans
    x_integrated_100 = 0  #100 scans
    height = 0
    previous_mouse = (0, 0)
    remainder = 0
    data = None
    raw_data = None

    first_scan = False
    amplitudes = None  #init as np.array([3,self.channels,self.height]) when first scan comes in

    def __init__(self,options):
        self.opts = options
        self.total_received = 0
        self.db_max = options.db_max
        self.db_min = options.db_min
        pygame.init()

    def draw_color_key(self, colormap, x, anchor_y, min_db, max_db):
        key_surf = pygame.Surface((10, len(self.colormap)))
        y = 0
        for color in colormap[::-1]:
            pygame.draw.line(key_surf, color, [0, y], [10, y])
            y = y + 1
        font = pygame.font.SysFont("consolas", 16, True)
        # m = font.size(str(max_db))
        s = font.render("+" + str(self.db_max), True, (255, 255, 255))
        s2 = font.render(str(self.db_min), True, (255, 255, 255))
        self.screen.blit(s, (x + 12, anchor_y))
        self.screen.blit(s2, (x + 12, anchor_y + y - 10))  # magic number blech
        self.screen.blit(key_surf, (x, anchor_y))

    def render_amplitude(self,x,db,freq,snr):
        surf = pygame.Surface((120,90))
        surf.fill(pygame.Color("black"))
        self.screen.blit(surf, (x, len(self.colormap) + 10 + self.upper_y))
        font = pygame.font.SysFont("consolas", 16, True)
        s = font.render("{:.4f}".format(freq) + ' MHz', True, (255, 255, 255))
        self.screen.blit(s, (x, len(self.colormap) + 10 + self.upper_y))
        sign = "+"
        dbstr = None
        if (db < 0 and db > -900):
            sign = ''
        if (db < -900):
            dbstr = 'PSD     dB'
        else:
            dbstr = 'PSD ' + sign + "{:.1f}".format(db)+ " dB"
        s = font.render(dbstr, True, (255, 255, 255))
        self.screen.blit(s, (x, len(self.colormap)+10+self.upper_y+20))
        snrstr = None
        if (db < -900):
            snrstr = 'SNR     dB'
        elif (snr < 0):
            snrstr = 'SNR ' + "{:.1f}".format(snr) + " dB"
        else:
            snrstr = 'SNR +' + "{:.1f}".format(snr) + " dB"
        s = font.render(snrstr, True, (255, 255, 255))
        self.screen.blit(s, (x, len(self.colormap) + 10 + self.upper_y + 40))
        #print(snr," snr")


    def set_surface(self,surf,rows, corner_x, y, max,stream_index,db_vals):
        '''
        Set each pixel color on the surface (stream).  Scroll as necessary.
        Scroll/rotate db values accordingly to enable mouse look up for db value.
        :param surf:
        :param rows:
        :param corner_x:
        :param y:
        :param max:
        :param db_stream: two dimensional array of db values for a stream
        :return:
        '''
        x_compress = 0
        for pixels in rows:
            x = 0
            x_compress = x
            for color in pixels:
                surf.set_at((x, y), color)
                x_compress = x_compress + 1
                if (x_compress == self.horizontal_compression):
                    x = x + 1
                    x_compress = 0
            self.amplitudes[stream_index, y] = db_vals
            y = y + 1
            if y == max: #scroll surface?
                y = y - 1
                self.scroll(surf)
                self.rotate_array(stream_index) #"scroll" the db values themselves
            self.screen.blit(surf, (corner_x, self.upper_y))
            # print 'blit ',corner_x
            # print "display.flip()"
            pygame.display.flip()
        return y

    def scroll(self,surf):
        '''
        simple vertical scroll for a surface using pygame method.
        Pixels in row 0 will be replaced by row 1, pixels in row 1 will be replaced by row 2, ...
        The bottom / max row may then be used for a new row/scan.
        :param surf:  surface to vertically scroll upwards
        :return:
        '''
        surf.scroll(0, -1)

    def rotate_array(self,stream_index):
        '''
        rotate/scroll elements in 2d array as identified by stream_index.
        :param stream_index:
        :return:
        '''
        self.amplitudes[stream_index] = numpy.roll(self.amplitudes[stream_index],-1,axis=0)

    def init(self,psd):
        self.upper_y = 15  # distance from top of frame
        self.scans = 600  # fix me: magic number 1 y pixel / one line = a scan
        self.compression_y = 0
        self.compression_y_100 = 0
        self.compression_count = 0
        self.compression_target = 10
        self.compression_count_100 = 0
        self.color_key_width = 20  # color key strip on right of spectrogram
        self.horiz_spacer = 10     # horiz space between temporal streams
        self.horizontal_compression = 1
        self.color_key_label_horiz_space = 90
        self.streams = 3  # temporal streams

        stream_index = zeros((self.streams))     # where in the circular data structure did we just write a scan
        self.screen_size = self.width, self.height = int((self.channels * 3 / self.horizontal_compression) + (
            self.horiz_spacer * 3) + self.color_key_width + self.color_key_label_horiz_space), int(self.scans)
        self.stream_width = (self.channels / self.horizontal_compression) + self.horiz_spacer
        #print("stream_width", stream_width)
        self.amplitudes = numpy.full((self.streams,self.height, self.channels),-999,numpy.float)
        self.x_integrated = (self.channels / self.horizontal_compression) + self.horiz_spacer
        self.x_integrated_100 = ((self.channels * 2) / self.horizontal_compression) + (self.horiz_spacer * 2)
        self.spectrogram_size = self.channels / self.horizontal_compression, 600
        self.screen = pygame.display.set_mode(self.screen_size)
        # screen2 = pygame.display.set_mode(size)
        self.screen.fill(self.BLACK)
        self.draw_color_key(self.colormap, (self.channels * 3 / self.horizontal_compression) + (self.horiz_spacer * 3), self.upper_y, -30, 30)
        pygame.display.set_caption("RASDR Spectrogram " + str(self.center_freq_mhz) + "/" + str(
            self.bandwidth_hz) + "/" + str(self.channels))
        # pixels = numpy.zeros((width,height), dtype='O')
        self.surf = pygame.Surface(self.spectrogram_size)
        self.surf_integrated_power = pygame.Surface(self.spectrogram_size)
        self.surf_integrated_power_100 = pygame.Surface(self.spectrogram_size)
        self.y = 0
        self.y_integrated = 0
        self.y_integrated_100 = 0
        self.pix_height = 1

    def map_db_to_color(self, psd):
        '''
        Map db values to colors.
        return current, 10x integration, and 100x integration color values for each channel.
        :param psd: db float values for each channel
        :return:  3 lists of color values.
        '''

        width = self.channels
        # rgb = rgb_fn(args.palette(), args.db_limit[0], args.db_limit[1])
        #max_z = 5  #FIX ME 30 #args.db_limit[1]
        #min_z = -5 #FIX ME -30 #args.db_limit[0]
        rgb = self.colormap #do_colormap(min_z, max_z, MAX_BINS)
        # colormap(-30,20,MAX_BINS) #args.db_limit[0], args.db_limit[1],MAX_BINS)
        max = abs(self.db_max - self.db_min)
        step = self.MAX_BINS / max
        pixel_rows = []
        integrated_power_rows = []
        integrated_power_rows_100 = []
        a = []  # numpy.zeros((len(zs)),dtype='int32')
        i = 0
        pixel_rows.append(a)
        self.compression_count = self.compression_count + 1
        self.compression_count_100 = self.compression_count_100 + 1
        final_integration = False
        integrated_power = None
        integrated_power_100 = None
        final_integration_100 = False
        db_realtime = [0] * self.channels
        db_10 = None   #if 10x integrated, preserve db values
        db_100 = None  #if 100x integrated, preserve db values

        min_db = 9999
        max_db = -9999

        min_db_10 = 9999
        max_db_10 = -9999

        min_db_100 = 9999
        max_db_100 = -9999

        if self.compression_count == 10:
            final_integration = True
            self.compression_count = 0
            integrated_power = [0] * self.channels #prepare a data structure to return
            integrated_power_rows.append(integrated_power)
            db_10 = [0] * self.channels
        if self.compression_count_100 == 100:
            final_integration_100 = True
            self.compression_count_100 = 0
            integrated_power_100 = [0] * self.channels
            integrated_power_rows_100.append(integrated_power_100)
            db_100 = [0] * self.channels
        for x in range(len(psd)):
            dbm = psd[x]
            db_realtime[i] = dbm
            index = round(abs(self.db_min - dbm))
            # print 'index ',index,min_z,dbm," ",zs[x],abs(-30-zs[x])
            index = int(round(index * step))
            # print 'index ',index,dbm
            # print 'dbm,index ',dbm,index
            if (index < 0 or index >= len(rgb)):
                index = len(rgb) - 1
                # print 'dbm,index ',dbm,index
            color = rgb[index]  # zs[x]]
                # pix[x,y+tape_height] = color
            #   print(color)
            a.append(color)
            self.compression_power[i] = self.compression_power[i] + dbm
            self.compression_power_100[i] = self.compression_power_100[i] + dbm

            if dbm < min_db:
                min_db = dbm
                min_db_x = x

            if final_integration:
                dbm = self.compression_power[i] / 10
                db_10[i] = dbm
                self.compression_power[i] = 0
                index = abs(self.db_min - dbm)
                index = int(round(index * step))
                if (index < 0 or index >= len(rgb)):
                    index = len(rgb) - 1
                    # print 'integrated dbm,index ',dbm,index
                color = rgb[index]
                integrated_power[i] = color
            if final_integration_100:
                dbm = self.compression_power_100[i] / 100
                db_100[i] = dbm
                self.compression_power_100[i] = 0
                index = abs(self.db_min - dbm)
                index = int(round(index * step))
                if (index < 0 or index >= len(rgb)):
                    index = len(rgb) - 1
                color = rgb[index]
                integrated_power_100[i] = color
            i = i + 1
        return pixel_rows, integrated_power_rows, integrated_power_rows_100, db_realtime, db_10, db_100

    def set_connection_metadata(self,configuration):
        '''
        :param configuration:  dictionary
        :return:
        '''
        #supplied values from Extended RSS metadata
        self.channels        = int(configuration['NumberOfChannels'])
        self.center_freq_mhz = float(configuration['CenterFrequencyHertz'])/1e6
        self.bandwidth_hz    = float(configuration['BandwidthHertz'])
        self.offset_hz       = float(configuration['OffsetHertz'])
        #derived values
        self.bandwidth_mhz = self.bandwidth_hz / 1e6
        self.base_freq_mhz = self.center_freq_mhz - (.5 * self.bandwidth_mhz)
        self.compression_power = [0] * self.channels
        self.compression_power_100 = [0] * self.channels
        self.channel_resolution_khz = self.bandwidth_hz / self.channels * 1e3
        print(self.channels,self.center_freq_mhz,self.bandwidth_hz,self.base_freq_mhz,self.offset_hz)

    def lookup_amplitude(self,mouse_pos):
        '''
        1. determine in which temporal band the coordinates lie
        2. determine which time(not done yet) and channel and db value within that band given the stream,x,y position
        3. compute snr by:
            averaging the two smallest dB values from the 3 channels to the left and 3 channels to the right of the signal
            using this average as a noise value and subtracting from the signal dB
        return -999 if outside one of the three streams.
        return the dB frequency and snr
        '''
        #step 1
        stream = int(mouse_pos[0] / self.stream_width)
        #step 2
        channel = int(mouse_pos[0] - ((stream) * (self.stream_width)))
        if (stream > 2 or channel >= self.channels):
            return -999,0,0
        y_index = mouse_pos[1] - self.upper_y  # 0 starts at upper.y
        #a stream may not have arrived at the mouse y yet
        if (stream==0):
            if (y_index > self.y):
                return -999,0,0
        elif stream==1:
            if (y_index > self.y_integrated):
                return -999,0,0
        elif (y_index > self.y_integrated_100):
                return -999,0,0
        db = self.amplitudes[stream,y_index,channel]
        noise = []
        freq = self.base_freq_mhz
        fraction = channel/self.channels
        freq = freq + (fraction * self.bandwidth_mhz)
        #print(mouse_pos, 'is in stream ', stream, self.stream_width, " channel ", channel, " db ", db, " freq ",freq)
        i = 0
        delta = self.channels - channel -1
        if (delta < 6):
            i = self.channels - 7
        else:
            i = channel - 3
        while (len(noise) < 6):
            if (i >= 0 and i != channel):
                noise.append(self.amplitudes[stream,y_index,i])
            i = i + 1
        noise.sort()
        #print(noise)
        noise_est = (noise[0] + noise[1]) / 2
        snr = db - noise_est
        return db,freq,snr

    def add_scan(self,dt,scan):
        '''
        When the RSS streaming receiver receives a scan, it may call this method to update the spectrograms
        :param dt:    date time stamp of scan
        :param scan:  list of db values for each channel
        :return:
        '''
        #print(dt,len(scan),scan[0],scan[1])
        #print(dt,scan)
        if self.total_received == 0:
            self.init(scan)
        self.total_received = self.total_received + 1
        pixel_rows, integrated_power_rows, integrated_power_rows_100, db_realtime,db_10, db_100 = self.map_db_to_color(scan)
        new_y = self.set_surface(self.surf, pixel_rows, 0, self.y, self.height,0,db_realtime)
        self.y = new_y
        #enough updates to paint a new row for the 10x stream?
        if (len(integrated_power_rows) > 0):
            self.y_integrated = self.set_surface(self.surf_integrated_power,integrated_power_rows, self.x_integrated, self.y_integrated, self.height, 1,db_10)
        #enough updates to paint a new row for the 100x stream?
        if (len(integrated_power_rows_100) > 0):
            self.y_integrated_100 = self.set_surface(self.surf_integrated_power_100,integrated_power_rows_100, self.x_integrated_100,
                                           self.y_integrated_100, self.height,2,db_100)
        #now check for mouse position within a stream to determine db and freq of interest to display
        mouse_pos = pygame.mouse.get_pos()
        if (mouse_pos[0] < (self.channels * 3 / self.horizontal_compression) + (self.horiz_spacer * 2) and mouse_pos[1] >= self.upper_y):
            db, freq,snr = self.lookup_amplitude(mouse_pos)
            self.render_amplitude((self.channels * 3 / self.horizontal_compression) + (self.horiz_spacer * 3),db,freq,snr)
        event = pygame.event.poll()
        if event.type == pygame.QUIT:
            sys.exit(0)
        elif event.type == pygame.MOUSEBUTTONDOWN and event.button == self.RIGHT:
            print('right mouse click')
        '''
        for event in pygame.event.get():  # User did something
            pygame.MOUSEBUTTONDOWN.
            if event.type == pygame.QUIT:  # If user clicked close
                done = True  # Flag that we are done so we exit this loop
        '''

    def open_colormap(self, cmap, cmap_file):
        #read a couple different kind of colormap file formats
        #a non-default / non-null cmap_file will override cmap
        if (len(cmap) > 0 and (cmap_file is None or cmap_file.find('default') > -1) or len(cmap_file) < 1):
            return self.assign_matplotlib_colormap(cmap)
        for line in open(cmap_file, 'r'):
            t = line.strip().split(',')
            if t[0].find('scalar') > -1:
                continue
            if len(t) == 4:
                color = (int(t[1]), int(t[2]), int(t[3]))
            if len(t) == 3:
                color = (int(t[0]), int(t[1]), int(t[2]))
            self.colormap.append(color)
            #print(color)

    def assign_matplotlib_colormap(self,name):
        #perceptually uniform:  'plasma_r', 'inferno_r', 'inferno', 'magma_r', 'magma', 'viridis', 'viridis_r', 'plasma'
        #all ['Accent', 'Accent_r', 'Blues', 'Blues_r', 'BrBG', 'BrBG_r', 'BuGn', 'BuGn_r', 'BuPu', 'BuPu_r', 'CMRmap', 'CMRmap_r', 'Dark2', 'Dark2_r', 'GnBu', 'GnBu_r', 'Greens', 'Greens_r', 'Greys', 'Greys_r', 'LUTSIZE', 'OrRd', 'OrRd_r', 'Oranges', 'Oranges_r', 'PRGn', 'PRGn_r', 'Paired', 'Paired_r', 'Pastel1', 'Pastel1_r', 'Pastel2', 'Pastel2_r', 'PiYG', 'PiYG_r', 'PuBu', 'PuBuGn', 'PuBuGn_r', 'PuBu_r', 'PuOr', 'PuOr_r', 'PuRd', 'PuRd_r', 'Purples', 'Purples_r', 'RdBu', 'RdBu_r', 'RdGy', 'RdGy_r', 'RdPu', 'RdPu_r', 'RdYlBu', 'RdYlBu_r', 'RdYlGn', 'RdYlGn_r', 'Reds', 'Reds_r', 'ScalarMappable', 'Set1', 'Set1_r', 'Set2', 'Set2_r', 'Set3', 'Set3_r', 'Spectral', 'Spectral_r', 'Wistia', 'Wistia_r', 'YlGn', 'YlGnBu', 'YlGnBu_r', 'YlGn_r', 'YlOrBr', 'YlOrBr_r', 'YlOrRd', 'YlOrRd_r', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', '_generate_cmap', '_reverse_cmap_spec', '_reverser', 'absolute_import', 'afmhot', 'afmhot_r', 'autumn', 'autumn_r', 'binary', 'binary_r', 'bone', 'bone_r', 'brg', 'brg_r', 'bwr', 'bwr_r', 'cbook', 'cmap_d', 'cmapname', 'cmaps_listed', 'colors', 'cool', 'cool_r', 'coolwarm', 'coolwarm_r', 'copper', 'copper_r', 'cubehelix', 'cubehelix_r', 'datad', 'division', 'flag', 'flag_r', 'get_cmap', 'gist_earth', 'gist_earth_r', 'gist_gray', 'gist_gray_r', 'gist_heat', 'gist_heat_r', 'gist_ncar', 'gist_ncar_r', 'gist_rainbow', 'gist_rainbow_r', 'gist_stern', 'gist_stern_r', 'gist_yarg', 'gist_yarg_r', 'gnuplot', 'gnuplot2', 'gnuplot2_r', 'gnuplot_r', 'gray', 'gray_r', 'hot', 'hot_r', 'hsv', 'hsv_r', 'inferno', 'inferno_r', 'jet', 'jet_r', 'ma', 'magma', 'magma_r', 'mpl', 'nipy_spectral', 'nipy_spectral_r', 'np', 'ocean', 'ocean_r', 'os', 'pink', 'pink_r', 'plasma', 'plasma_r', 'print_function', 'prism', 'prism_r', 'rainbow', 'rainbow_r', 'register_cmap', 'revcmap', 'seismic', 'seismic_r', 'six', 'spec', 'spec_reversed', 'spectral', 'spectral_r', 'spring', 'spring_r', 'summer', 'summer_r', 'terrain', 'terrain_r', 'unicode_literals', 'viridis', 'viridis_r', 'winter', 'winter_r']
        if (hasattr(cm,name)):
            m_colormap = getattr(cm,name)
            print(name,' selected from matplotlib colormaps')
        else:
            print('colormap',name,' not held by matplotlib.cm')
            m_colormap = getattr(cm,'magma')
        linear_map = linspace(0, 1, 100)  # to deal with rounding error
        # plasma
        m = [m_colormap(val) for val in linear_map]
        self.colormap = []
        # transform floating point 0-1 to 0-255
        for color in m:
            c = (int(round(color[0] * 255)), int(round(color[1] * 255)), int(round(color[2] * 255)))
            self.colormap.append(c)

#s.assign_matplotlib_colormap('magma')
#print (s.colormap)
#s.open_colormap(sys.argv[1])
