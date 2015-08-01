#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for memset()
#include <stdint.h>
#include <errno.h>
#include <limits.h>

#include "socket.h" // for socket_xxx()'s

extern char *stristr(const char *haystack, const char *needle, size_t len);

#ifdef _MSC_VER		// >=1600 (2010), >=1800 (2013)
#define strdup	_strdup
//#define strtok	_strtok
#endif

#define ALPHA		0.99
#define FACTOR		256
#define LOG2FACTOR	8

void usage(char *argv0)
{
	fprintf(stderr,"Usage:\n  %s url bytes [num][opt][csv]\n"
		"\n"
		"Where:\n"
		"  url:   'addr:port' for TCP/IP Socket\n"
		"  bytes: msg length\n"
		"  num:   (optional) number of messages to send in test (continuous otherwise)\n"
		"  opt:   (optional) comma-separated list of flags to modify IPC resource;\n"
		"         valid options are:\n"
		"         'ipv4' forces IPV4 addresses when using TCP/IP Sockets\n"
		"         'ipv6' forces IPV6 addresses when using TCP/IP Sockets\n"
		"         'bsd' uses an alternate connect()-fail retry method (MacOS X)\n"
		"\n"
		"  Client-side test program to send messages via various IPC mechanisms;\n"
		"The program uses TCP/IP sockets and is specifically tolerant of the IPC\n"
        "resource/server not initialized yet in order to simulate what might happen\n"
        "during a large application init and sync.\n"
		"\n"
		"Examples:\n"
		"  $ %s localhost:3500 16384 400000 ipv4,bsd\n"
		"\n"
		"  This will open an (IPV4) TCP/IP socket on the local machine at port 3500,\n"
		"use a 16K block and transfer a total of 6.6GB.  BSD-retry method if no server started.\n"
		"\n"
		"Notes:\n"
		"  1) Some OS default TCP/IP sockets to IPv4/IPv6 inconsistenly (UBUNTU 10.04).\n"
		"     workaround this by specifying the address family explicitly with [opt].\n"
		"  2) Some OS require an alternate connect()-fail retry method (MacOS X).\n"
		"     workaround this by specifying the 'bsd' option with [opt].\n"
        "  3) name lookup is not implemented, please use numeric IP addresses.\n"
		"\n",
		argv0, argv0 );
	exit(1);
}

int main(int argc, char**argv, char**envp)
{
	int s;
	int flag;
	int l, len, sz, nm;
	uint8_t *p, *buf = NULL;
	int ec = 0;
	struct statistics {
		size_t sent;
		size_t intr;
		size_t again;
		int min, max, avg;
		int a, b;
	} stats;
	const char *iptype = "ip\0\0";
    char *address = NULL;
    short port = -1;

	if( argc<3 ) usage(argv[0]);
    if( argc>1 ) {
	    char *svc;
        address = strdup(argv[1]);
	    svc = strtok(address,":");
	    if( svc ) svc = strtok(NULL,":");
        if( svc ) port = (short)atoi(svc);
        // address contains IP, port holds port number
    }
	sz = (argc>2)?atoi(argv[2]):4;	// length of I/O is arg2 (default=4)
	if( (sz<4) || (sz%4) ) { errno = EINVAL; perror("bytes"); exit(1); }
	nm = (argc>3)?atoi(argv[3]):-1;	// num messages is arg3 (default=-1)
	if( argc>4 && stristr(argv[4],"ipv4",4) ) iptype = "ipv4";
	if( argc>4 && stristr(argv[4],"ipv6",4) ) iptype = "ipv6";

	// platform independence (see socket.h)
    socket_init();

	// buffers and statistics
	buf = (uint8_t *)malloc(sz);
	if( !buf) { perror("malloc"); exit(1); }

	memset(&stats, 0, sizeof(struct statistics));
	stats.min = INT_MAX;
	stats.max = INT_MIN;
    stats.avg = 0;
	stats.a   = (int)(ALPHA * FACTOR);
	stats.b   = (int)(FACTOR - stats.a);

    flag = SOCKET_VERBOSE;
    if( iptype[3]=='6') flag |= SOCKET_IPV6;
    if( argc>4 && stristr(argv[4],"bsd",3)) flag |= SOCKET_BSD;

    // platform-independent socket (see socket.h)
    s = socket_open_and_connect(address, port, flag);
    if (s>0) {

	    fprintf(stderr,"%s: connected to %s,%hu ...\n", argv[0], address, port);
	    fprintf(stderr,"%s: using %d block size\n", argv[0], sz);

        l=socket_send(s,&sz,sizeof(sz),0);
        if( l==sizeof(sz) ) {
	        stats.avg = sz;

	        // transmit buffers continuously
	        p = buf; len=0;
	        do {
                l=socket_send(s,p,sz-len,0);
                if( l<=0 ) { ec = 1; break; }

			    stats.sent++;
		        if(l < stats.min) stats.min=l;
		        if(l > stats.max) stats.max=l;
		        stats.avg = ((stats.a*stats.avg) + (stats.b*l))>>LOG2FACTOR;	// autoregressive

		        len += l; p += l;
		        if( len == sz ) {
			        p=buf;
			        len=0;
	            }
	        } while( (nm==-1) || ((int)stats.sent < nm) );
        }
        socket_close(s);
    } else ec = 1;

	if( buf ) free(buf);

	if( stats.intr+stats.again+stats.sent ) {
#if __STDC_VERSION__ >= 199901L
		fprintf(stdout,"%zu+%zu+%zu record%s out",
			stats.sent, stats.intr, stats.again, (stats.sent==1?"":"s"));
#else
		fprintf(stdout,"%lu+%lu+%lu record%s out",
			(unsigned long)stats.sent,
            (unsigned long)stats.intr,
            (unsigned long)stats.again, (stats.sent==1?"":"s"));
#endif
		if( (stats.min!=stats.avg) || (stats.max!=stats.avg) || (stats.min!=stats.max) ) {
			fprintf(stdout,"; min=%d max=%d avg=%d\n", stats.min, stats.max, stats.avg);
		} else {
			fprintf(stdout,"; bs=%d\n", sz);
		}
	} else fprintf(stdout,"0+0+0 records out\n");

	// platform independence (see socket.h)
    socket_fini();

	exit(ec);
}
