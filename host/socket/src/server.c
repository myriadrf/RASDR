#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for memset()
#include <stdint.h>
#include <limits.h>

#include "socket.h" // for socket_xxx()'s

extern char* stristr(const char* haystack, const char* needle, size_t len);

#ifdef _MSC_VER		// >=1600 (2010), >=1800 (2013)
#define strdup	_strdup
//#define strtok	_strtok
#endif

#define ALPHA		0.99
#define FACTOR		256
#define LOG2FACTOR	8

void usage(char *argv0)
{
	fprintf(stderr,"Usage:\n  %s url [bytes][opt]\n"
		"\n"
		"Where:\n"
		"  url:   'addr:port' for TCP/IP Socket\n"
		"  bytes: (optional) msg length to expect\n"
		"         if non-positive, use value from client.\n"
		"  opt:   (optional) comma-separated list of flags to modify IPC resource;\n"
		"         valid options are:\n"
		"         'ipv4' forces IPV4 addresses when using TCP/IP Sockets\n"
		"         'ipv6' forces IPV6 addresses when using TCP/IP Sockets\n"
		"         'persist[=N]' respawns the server after a client exits\n"
		"            optional 'N' limits number of respawns.\n"
		"\n"
		"Examples:\n"
		"  $ %s localhost:3500 0 ipv4\n"
		"\n"
		"  This will open a TCP/IP socket on the local machine at port 3500, dynamically\n"
		"accept the block size from the client, and force IPV4 operation.\n"
		"\n"
		"Notes:\n"
		"  1) Some OS default TCP/IP sockets to IPv4/IPv6 inconsistenly (UBUNTU 10.04).\n"
		"     workaround this by specifying the address family explicitly with [opt].\n"
		"\n",
		argv0, argv0 );
	exit(1);
}

int main(int argc, char**argv, char**envp)
{
	int s, svr;
	int flag;
	size_t received = 0;
	int l, len, sz;
	uint8_t *p, *buf = NULL;
	struct statistics {
		size_t recv;
		int min, max, avg;
		int a, b;
	} stats;
	char *r;
	const char *iptype = "ip\0\0";
	int persist = -1;
    char *address = NULL;
    short port = -1;

	// parse arguments
	if( argc<2 ) usage(argv[0]);	// require at least IPC resource name
    if( argc>1 ) {
	    char *svc;
        address = strdup(argv[1]);
	    svc = strtok(address,":");
	    if( svc ) svc = strtok(NULL,":");
        if( svc ) port = (short)atoi(svc);
        // address contains IP, port holds port number
    }
	sz = (argc>2)?atoi(argv[2]):0;	// length of I/O is arg2
	if( argc>3 && stristr(argv[3],"ipv4",4) ) iptype = "ipv4";
	if( argc>3 && stristr(argv[3],"ipv6",4) ) iptype = "ipv6";
	if( argc>3 && (r=strstr(argv[3],"persist")) ) {
		char *t, *u = strdup(r);

		t = strtok(u,"=");
		if( t ) t = strtok(NULL,"=");
		if( t ) persist = atoi(t);
		else    persist = 0;
		free(u);
	}

	// platform independence (see socket.h)
    socket_init();

    flag = SOCKET_VERBOSE;
    if( iptype[3]=='6') flag |= SOCKET_IPV6;
    if( argc>4 && stristr(argv[4],"bsd",3)) flag |= SOCKET_BSD;

    svr = socket_open_bind_and_listen(address,port,1,flag);
    if (svr>0) do {
        s = socket_accept(svr,flag);
        if (s>0) {
            // refresh expected block size
		    sz = (argc>2)?atoi(argv[2]):0;

            // read initial word to determine transfer unit
            l = socket_recv(s,&len,sizeof(len),flag);
            if (l==sizeof(len)) {

                if( sz>0 && (len!=sz) ) {
		            fprintf(stderr,"LEN mismatch - expected %d, received %d\n", sz, len);
		            break;
	            }
	            sz = len;

	            buf = (uint8_t *)malloc(sz);
	            if( !buf ) { perror("malloc"); break; }

	            memset(&stats, 0, sizeof(struct statistics));
	            stats.min = INT_MAX;
	            stats.max = INT_MIN;
	            stats.avg = sz;
	            stats.a   = (int)(ALPHA * FACTOR);
	            stats.b   = (int)(FACTOR - stats.a);

	            // consume buffers continuously
	            p = buf; len=0;
	            for(;;) {
                    l = socket_recv(s,p,sz-len,flag);
                    if( l<=0 ) break;

		            stats.recv++;
		            if(l < stats.min) stats.min=l;
		            if(l > stats.max) stats.max=l;
		            stats.avg = ((stats.a*stats.avg) + (stats.b*l))>>LOG2FACTOR;	// autoregressive

		            len += l; p+= l;
		            if( len == sz ) { p=buf; len=0; }
	            }
#if __STDC_VERSION__ >= 199901L
	            fprintf(stdout,"%zu record%s in; min=%d max=%d avg=%d\n",
			            stats.recv, (stats.recv==1?"":"s"), stats.min, stats.max, stats.avg);
#else
	            fprintf(stdout,"%lu record%s in; min=%d max=%d avg=%d\n",
			            (unsigned long)stats.recv, (stats.recv==1?"":"s"), stats.min, stats.max, stats.avg);
#endif
		        free(buf);
            }
            socket_close(s);
        }

	    // handle persistency request
	    if( !persist || (persist > 1) ) {
		    if( persist ) persist--;		// server restart lifetime counter
            continue;
		} else break;

	} while(1);

    socket_close(svr);

	// platform independence (see socket.h)
    socket_fini();

	exit(0);
}
