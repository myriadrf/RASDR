// socket.h - simple platform independent TCP/IP sockets
//
// A wrapper around socket calls that suppresses the variances between winsock
// and Berkeley socket interfaces.  Effectively, it hides the ifdef's that inevitably
// surround these implementations.  You can get similar effects by using the
// various libraries that exist.  However, if you want to limit dependencies,
// this might be useful.

/*
 * Copyright (c) 2015 Bogdan Vacaliuc <bvacaliuc@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>  // for (f,sn)printf()
#include <string.h>	// for memset()

static const char rcsid[] = "$Id: socket.h,v 1.0.0.0 2015/08/01 00:00:00 bogdan Exp $";

#if defined(__WIN32__) || defined(WIN32)
    // https://msdn.microsoft.com/en-us/library/bw1hbe6y.aspx
    // http://stackoverflow.com/questions/4243027/winsock-compiling-error-it-cant-find-the-addrinfo-structures-and-some-relating
    #define _WIN32_WINNT 0x501
    #include <winsock2.h>
    // http://stackoverflow.com/questions/3443836/sockaddr-in6-not-declared
    #include <ws2tcpip.h>
    // http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html

#ifdef _MSC_VER		// >=1600 (2010), >=1800 (2013)
#define snprintf	_snprintf_s
#endif

    static void ErrorString(DWORD err, char *s, DWORD len)
    {
	    if( FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
			    NULL, err, 0, (LPTSTR)s, len, NULL) == 0)
	    {
            snprintf(s,len,"Unknown error code %08x (%d)", err, LOWORD(err));
        }
	    return;
    }
    extern "C" char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

    static int _net_perror(const char *tag)
    {
        char _err[256];
        int ec = WSAGetLastError();
        ErrorString(ec,_err,sizeof(_err));
		fprintf(stderr,"%s: %d %s\n",tag,ec,_err);
        return ec;
    }
#else
    #define INLINE inline
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/stat.h>
    #include <sys/un.h>	// macos-specific?
    #include <netdb.h>	// macos-specific?
    #include <unistd.h> // for sleep()
    #include <errno.h>

    static int _net_perror(const char *tag)
    {
        int ec = errno;
        perror(tag);
        return ec;
    }
#endif

// get sockaddr, IPv4 or IPv6:
static void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// for flags parameter..
#define SOCKET_VERBOSE  0x0001      // write to stderr
#define SOCKET_IPV6     0x0002      // select IPV6 socket operations
#define SOCKET_BSD      0x0004      // select BSD retry semantics

static void socket_init(void)
{
#if defined(__WIN32__) || defined(WIN32)
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}
#endif
}

static int socket_open_and_connect(const char *address, short port, int flag)
{
    struct sockaddr_in ai;
    int s, res;
    int repeat = 0;

    memset(&ai,0,sizeof(ai));
	ai.sin_addr.S_un.S_addr=inet_addr(address);
	ai.sin_family=(flag & SOCKET_IPV6)?AF_INET6:AF_INET;
	ai.sin_port=htons(port);

    s = socket(ai.sin_family,SOCK_STREAM,IPPROTO_TCP);                // svr == INVALID_SOCKET for winsock2.h
	if (s<0) {
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("socket");
        return s;
    }

	do {
		res = connect(s, (struct sockaddr *)&ai, sizeof(ai));
#if defined(__WIN32__) || defined(WIN32)
        if( res == SOCKET_ERROR ) switch(WSAGetLastError()) {
        case WSAEHOSTDOWN:
        case WSAECONNREFUSED:
            if(flag & SOCKET_VERBOSE && !repeat++) {
                (void)_net_perror("connect");
				fprintf(stderr,"waiting for %s to open port %hu\n",
				    address, ntohs(ai.sin_port));
            }
			Sleep(1000);
#else
		if (res<0) switch(errno) {
		case ENOENT:
		case ECONNREFUSED:
			if(!repeat++ && (flag & SOCKET_VERBOSE) ) {
				fprintf(stderr,"waiting for %s to open port %hu (%s)\n",
				    address, ntohs(ai.sin_port), strerror(errno));
            }
			sleep(1);
#endif
			if( flag & SOCKET_BSD ) {
				// need to treat BSD systems differently
				// see: http://stackoverflow.com/questions/4029291
#if defined(__WIN32__) || defined(WIN32)
				closesocket(s);
#else
				close(s);
#endif
                s = socket(ai.sin_family,SOCK_STREAM,IPPROTO_TCP);                // svr == INVALID_SOCKET for winsock2.h
	            if (s<0) {
                    if( flag & SOCKET_VERBOSE ) (void)_net_perror("socket");
                    return s;
                }
			}
			continue;
        default:
			(void)_net_perror("connect");
#if defined(__WIN32__) || defined(WIN32)
		    closesocket(s);
            return INVALID_SOCKET;
#else
		    close(s);
            return -1;
#endif
        }
	} while(res<0);

    if( flag & SOCKET_VERBOSE && (repeat>1) ) {
	    fprintf(stderr,"last message repeated %d times\n", repeat);
    }
    return s;
}

static int socket_send(int s, void *buf, size_t len, int _flag_unused)
{
    int l;
    char *p = (char *)buf;
    size_t remain = len;

	do {
        l=send(s,p,remain,0);
#if defined(__WIN32__) || defined(WIN32)
        if( l == SOCKET_ERROR ) switch(WSAGetLastError()) {
#else
	    if(l<0) switch(errno) {
		case EAGAIN:
			sleep(1);
		case EINTR:
			continue;
#endif
		default:
            (void)_net_perror("send");
		    return len - remain;    // how much was transferred so far
	    }
        // client disconnction
        else if(l==0) break;
        // otherwise progress was made
        p      += l;
        remain -= l;
    } while( remain > 0 );

    return len - remain;
}

static int socket_open_bind_and_listen(const char *address, short port, int backlog, int flag)
{
    struct sockaddr_in ai;
    int s, res;
	int yes = 1;

    memset(&ai,0,sizeof(ai));
	ai.sin_addr.S_un.S_addr=inet_addr(address);
	ai.sin_family=(flag & SOCKET_IPV6)?AF_INET6:AF_INET;
	ai.sin_port=htons(port);

    s = socket(ai.sin_family,SOCK_STREAM,IPPROTO_TCP);                  // s == INVALID_SOCKET for winsock2.h
	if (s<0) {
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("socket");
        return s;
    }

	res = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(int));   // res == SOCKET_ERROR for winsock2.h
    if (res<0) {
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("setsockopt");
#if defined(__WIN32__) || defined(WIN32)
	    closesocket(s); s = INVALID_SOCKET;
#else
        close(s); s = -1;
#endif
        return s;
    }

    res = bind(s, (SOCKADDR *)&ai, sizeof(struct sockaddr_in));         // res == SOCKET_ERROR for winsock2.h
    if (res<0) {
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("bind");
#if defined(__WIN32__) || defined(WIN32)
	    closesocket(s); s = INVALID_SOCKET;
#else
        close(s); s = -1;
#endif
        return s;
    }

    if( flag & SOCKET_VERBOSE ) {
        //extern "C" char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
	    char addr[INET6_ADDRSTRLEN];
        inet_ntop( ai.sin_family, get_in_addr((struct sockaddr *)&ai), addr, sizeof(addr) );

	    fprintf(stderr,"listening on %s,%hu %s...\n",
            addr, ntohs(ai.sin_port),
            (ai.sin_family==AF_INET)?"ipv4":((ai.sin_family==AF_INET6)?"ipv6":""));
    }

	// accept connections one at a time
	res = listen(s,backlog);        // res == SOCKET_ERROR for winsock2.h
    if (res<0) {
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("listen");
#if defined(__WIN32__) || defined(WIN32)
	    closesocket(s); s = INVALID_SOCKET;
#else
        close(s); s = -1;
#endif
        return s;
    }

    return s;
}

static int socket_accept(int svr, int flag)
{
    int s;

	s = accept(svr,NULL,NULL);  // s == INVALID_SOCKET for winsock2.h
	if (s<0) {
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("accept");
        return s;
    }

 	if( flag & SOCKET_VERBOSE ) {
		struct sockaddr_in *name, peer;
	    socklen_t slen = sizeof(struct sockaddr_in);
		char addr[INET6_ADDRSTRLEN];
        int res;

		res = getpeername(s,(struct sockaddr *)&peer,&slen);    // res == SOCKET_ERROR for windsock2.h
        if (res<0) {
            (void)_net_perror("getpeername");
        } else {
            //extern "C" char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
		    name = &peer;
		    inet_ntop( ((struct sockaddr *)name)->sa_family, get_in_addr((struct sockaddr *)name),
				addr, sizeof(addr));
		    fprintf(stderr,"connect from %s,%hu ...\n", addr, ntohs(name->sin_port));
	    }
    }

    return s;
}

static int socket_recv(int s, void *b, size_t len, int flag)
{
    int l;

#if defined(__WIN32__) || defined(WIN32)
    const char *tag = "recv";
    l=recv(s,(char *)b,len,0);
    if( l == SOCKET_ERROR ) switch(WSAGetLastError()) {
    case WSAETIMEDOUT:
        // socket must be closed; see 'SO_RCVTIMEO and SO_SNDTIMEO' in:
        // https://msdn.microsoft.com/en-us/library/windows/desktop/ms740476%28v=vs.85%29.aspx
        if( flag & SOCKET_VERBOSE ) (void)_net_perror("recv");
        return -1;
#else
    const char *tag = "read";
	l=read(s,b,len);
 	if(l<0) switch(errno) {
	case ENOTCONN:  // FIXME: really?  not connected gets returned by recv() and you keep going?
		sleep(1);
	case EINTR:
	case EAGAIN:
		continue;
#endif
	default:
		if( flag & SOCKET_VERBOSE ) (void)_net_perror(tag);
	}
    return l;
}

static void socket_close(int s)
{
#if defined(__WIN32__) || defined(WIN32)
    if( s != INVALID_SOCKET) closesocket(s);
#else
    if( s>0 ) close(s);
#endif
}

static void socket_fini(void)
{
#if defined(__WIN32__) || defined(WIN32)
    WSACleanup();
#endif
}
