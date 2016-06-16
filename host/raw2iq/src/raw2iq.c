// raw2iq.c - A tool for converting RASDRstreamer .raw files to interleaved I,Q
//
// Acknowledgements:

// http://stackoverflow.com/questions/14386/fopen-deprecated-warning
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // for tolower()
#include <limits.h>
#include <stdint.h>   // for uint16_t, etc.
//#include <errno.h>
//#include <time.h>   // for clock()
#include <string.h>
#ifdef _OPENMP
    #include <omp.h>
#endif

// http://stackoverflow.com/questions/1546789/clean-code-to-printf-size-t-in-c-or-nearest-equivalent-of-c99s-z-in-c
#if defined(_MSC_VER) || defined(__MINGW32__) //__MINGW32__ should go before __GNUC__
#define __SIZE_T_SPECIFIER    "%Iu"
#define __SSIZE_T_SPECIFIER   "%Id"
#define __PTRDIFF_T_SPECIFIER "%Id"
#else //elif defined(__GNUC__)
#define __SIZE_T_SPECIFIER    "%zu"
#define __SSIZE_T_SPECIFIER   "%zd"
#define __PTRDIFF_T_SPECIFIER "%zd"
#endif

#if defined(_MSC_VER)
#define strcasecmp      _stricmp
#define snprintf        _snprintf
static FILE *_fopen(const char *f, const char *m) { FILE *fp = NULL; int e = fopen_s(&fp, f, m); return fp; }
#define fopen(F,M)      _fopen(F,M)
#else
#include <strings.h>    // POSIX
#endif

struct _global {
    const char *infile;
    const char *outfile;
    const char *ofmt;
    FILE *infd;
    FILE *outfd;
    int threads;
    int verbose;
    uint16_t otm_polarity;
    uint16_t flag_mask;
    uint16_t flag_value;
    uint16_t iq_polarity;
} g = { NULL, NULL, "wb", NULL, NULL, 0, 0, 1, 3, 3, 0 };

typedef union _sample {
    struct _b {
         int16_t sample : 12;
        uint16_t iqsel : 1;
        uint16_t flag : 2;
        uint16_t pps : 1;
    } s;
    uint16_t ui;
    int16_t i;
} sample_t;

void usage( const char *argv0 )
{
    printf("Convert RASDRstreamer raw stream into a I/Q output"
    "\n"
	"\nUsage:"
	"\n%s [OPTIONS]"
	"\nWhere:"
	"\n  -i, --input-file FILE   Full path to file to be read or - for stdin"
	"\n  -o, --output-file FILE  Full path to file to be written or - for stdout"
    "\n  --iq-polarity N         Define starting I/Q polarity level"
    "\n                            (0=I sample first, 1=Q sample first, default=0)"
    "\n  --pps-polarity N        Define OTM/PPS polarity level"
    "\n                            (0=active low, 1=active high, default=0)"
    "\n  --flag-value HEX        Define FLAGs code for valid data"
    "\n                            (two bits, default=3)"
    "\n  --flag-mask HEX         Define FLAGs mask (two bits, default=3)"
    "\n  -v                      Increment verbosity level"
    "\n  --verbose N             Define verbosity level (0=quiet, 1=info, 2=trace)"
    "\n  -h, --help              Print this help"
    "\n\nExamples:"
	"\n\n%s < RASDRviewer.raw > test.dat"
	"\nConverts the .raw file to a binary interleaved 16-bit signed I/Q format file."
	"\n\n%s < RASDRviewer.raw -o test.csv"
	"\nConverts the .raw file to an ASCII 16-bit signed I/Q comma separated file."
	"\n\n", argv0, argv0, argv0);
	exit(1);
}

// http://stackoverflow.com/questions/5309471/getting-file-extension-in-c
const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

const char *get_filename_format(const char *ext) {
    if(!ext) return "wb";
    else if(strcasecmp(ext,"csv")==0) return "w";
    else if(strcasecmp(ext,"txt")==0) return "w";
    return "wb";
}

void argparse( int argc, char *argv[], char *envp[] )
{
    int i;

    // dependency-free simple argument parsing
    for (i = 1; i < argc; i++) {
        const char *key = argv[i];

        if (strcmp(key,"--") == 0) break;   // stop parsing arguments
        else if (strncmp(key, "-h", 2) == 0 || strncmp(key, "--help", 6) == 0) {
            usage(argv[0]);
        }
        else if (strcmp(key, "-i") == 0 || strncmp(key, "--input-file", 12) == 0) {
            if ((i + 1) >= argc) break;
            g.infile = argv[++i];
        }
        else if (strncmp(key, "-o", 2) == 0 || strncmp(key, "--output-file", 13) == 0) {
            if ((i + 1) >= argc) break;
            g.outfile = argv[++i];
        }
        else if (strncmp(key, "--pps-polarity", 14) == 0) {
            if ((i + 1) >= argc) break;
            g.otm_polarity = atoi(argv[++i])? 1 : 0;
        }
        else if (strncmp(key, "--iq-polarity", 13) == 0) {
            if ((i + 1) >= argc) break;
            g.iq_polarity = atoi(argv[++i])? 1 : 0;
        }
        else if (strncmp(key, "--flag-mask", 11) == 0) {
            if ((i + 1) >= argc) break;
            g.flag_mask = atoi(argv[++i]);
        }
        else if (strncmp(key, "--flag-value", 12) == 0) {
            if ((i + 1) >= argc) break;
            g.flag_value = atoi(argv[++i]);
        }
        else if (strncmp(key, "-v", 2) == 0) g.verbose++;
        else if (strncmp(key, "--verbose", 9) == 0) {
            if ((i + 1) >= argc) break;
            g.verbose = atoi(argv[++i]);
        }
    }
    if (g.infile == NULL || strcmp(g.infile,"-") == 0) {
        g.infd = stdin;
        g.infile = "stdin";
    } else {
        g.infd = fopen(g.infile, "rb"); // NB: input stream must be labeled binary
        if (g.infd == NULL) {
            perror("cannot open input file");
            exit(1);
        }
    }
    if (g.outfile == NULL || strcmp(g.outfile,"-") == 0) {
        g.outfd = stdout;
        g.outfile = "stdout";
    } else {
        g.ofmt = get_filename_format(get_filename_ext(g.outfile));
        g.outfd = fopen(g.outfile, g.ofmt);
        if (g.outfd == NULL) {
            perror("cannot open output file");
            exit(1);
        }

    }
#ifdef _OPENMP
    g.threads = omp_get_max_threads();
#else
    g.threads = 1;
#endif
}

// http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing
// http://stackoverflow.com/questions/7788850/macro-definition
// http://blog.mellenthin.de/archives/2010/10/26/portable-__va_args__-macros-for-linux-hp-ux-solaris-and-aix/comment-page-1/
#define LOG(fmt, ...) \
            do { fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)
#define INFO(fmt, ...) \
            if (g.verbose>0) { fprintf(stderr, fmt, ##__VA_ARGS__); }
#define TRACE(fmt, ...) \
            if (g.verbose>1) { fprintf(stderr, fmt, ##__VA_ARGS__); }

#define PAGE    4096

int main(int argc, char *argv[], char *envp[])
{
    argparse(argc,argv,envp);

    INFO("input=%s\n",g.infile);
    INFO("output=%s, fmt=%s\n", g.outfile, g.ofmt);
    INFO("CPU Threads=%d\n", g.threads);
    TRACE("sizeof(sample_t)="__SIZE_T_SPECIFIER"\n", sizeof(sample_t));
    TRACE("polarity otm,iq=%hu,%hu\n", g.otm_polarity, g.iq_polarity);
    TRACE("flag_mask,value=%hu,%hu\n", g.flag_mask, g.flag_value);

    //exit(1);

    {
        uint8_t *b = (uint8_t *)malloc(g.threads*PAGE); // Binary output buffer
        char    *a = (char *)malloc(g.threads*PAGE*8);  // ASCII output buffer
        char    *t = (char *)malloc(g.threads*PAGE);    // On-Time-Marker (OTM) indicator
        char    *x = (char *)malloc(g.threads*PAGE);    // Invalid Sample indicator

        // shared scalars for diagnostics/reductions
        size_t t_count = 0, x_count = 0;
        size_t n_count = 0, r_count = 0;

        // private loop counters
        int i, j;

        //#pragma omp parallel
        //{
            // apply first-touch principle to initialize memory
            #pragma omp parallel for private(i)
            for (i=0; i < g.threads; i++)
            {
               memset(&b[i*PAGE], 0, PAGE);
               memset(&a[i*PAGE*8], 0, PAGE*8);
               memset(&t[i*PAGE], 0, PAGE);
               memset(&x[i*PAGE], 0, PAGE);
            }

            // read input stream in strict sequence ordering
            while ( !feof(g.infd) )
            {
                size_t n, r;

                //#pragma omp master
                n = fread(b, PAGE, g.threads, g.infd);
                //#pragma omp barrier

                //TRACE("n="__SIZE_T_SPECIFIER", err=%d%s\n", n, ferror(g.infd), feof(g.infd)?" EOF":"");

                if (ferror(g.infd)) { perror(g.infile); }
                if ( n < 1 ) TRACE("did not read enough bytes to process a full PAGE\n");
                if ( n < 1 ) break;

                // TODO: inspect first sample of each block to determine I/Q mismatch,
                //       if so, convert the last sample of each block and place in a
                //       hold buffer to be used by the next block.  This will properly
                //       re-align I/Q mismatches once they occur.

                // remove control bits and handle I,Q exceptions
                #pragma omp parallel for private(i,j)
                for (i=0; i < g.threads; i++)
                {
                    sample_t *in = (sample_t *)&b[i*PAGE];
                    int16_t *out = (int16_t *)in;
                    char    *otm = (char *)&t[i*PAGE];
                    char    *xcc = (char *)&x[i*PAGE];

                    //http://stackoverflow.com/questions/7661114/the-openmp-master-pragma-must-not-be-enclosed-by-the-parallel-for-pragma
                    //#pragma omp master it is error
                    //#pragma omp critical it is right
#ifdef _OPENMP
                    if (g.verbose > 2 && omp_get_thread_num() == 0)
#else
                    if (g.verbose > 2)
#endif
                    {
                        sample_t *_iq = in;
                        char _tag[6];
                        int _s;

                        TRACE("--- Coded input block ---\n");
                        for (_s = 0; _s<32; _s++, _iq++)  // N=number of samples to dump
                        {
                            snprintf(_tag, sizeof(_tag), "%c%04d", _s % 2 ? 'q' : 'i', _s / 2); _tag[5] = '\0';
                            TRACE("%s=0x%04x, sample=%+5d, iqsel=%u, flag=%#x, pps=%u\n",
                                _tag, _iq->ui, _iq->s.sample, _iq->s.iqsel, _iq->s.flag, _iq->s.pps);
                        }
                    }

                    memset(otm, 0, PAGE);                   // OTM is cleared in each block
                    memset(xcc, 0, PAGE);                   // invalid is cleared in each block
                    if ( (unsigned)i >= n ) continue;       // this thread did get a block read - does no work
                    for (j=0; j < PAGE/2; j+=2, in+=2)      // PAGE/sizeof(sample_t)
                    {
                        sample_t *_i, *_q;

                        if ( g.iq_polarity ) { _q = &in[0]; _i = &in[1]; }
                        else                 { _i = &in[0]; _q = &in[1]; }

                        if ( _i->s.iqsel || (_i->s.flag & g.flag_mask) != g.flag_value ) { xcc[j] = 1; }
                        if ( _i->s.pps == g.otm_polarity ) { otm[j] = 1; }
                        *out++ = _i->s.sample;
                        if ( !_q->s.iqsel || (_q->s.flag & g.flag_mask) != g.flag_value ) { xcc[j + 1] = 1; }
                        if ( _q->s.pps == g.otm_polarity) { otm[j + 1] = 1; }
                        *out++ = _q->s.sample;
                        
                        // DEBUG
#ifdef _OPENMP
                        if ( g.verbose > 1 && (otm[j] || xcc[j]) && omp_get_thread_num() == 0 )
#else
                        if ( g.verbose > 1 && (otm[j] || xcc[j]) )
#endif
                        {
                            char _tag[6];
                            static int _max = 10;
                            if (_max > 0)
                            {
                            snprintf(_tag, sizeof(_tag), "%c%04d", j % 2 ? 'q' : 'i', j / 2); _tag[5] = '\0';
                            TRACE("block="__SIZE_T_SPECIFIER",%s=0x%04x%s%s\n",
                                n_count, _tag, _i->ui, xcc[j]?",INVALID":"", otm[j]?",OTM":"");
                            _max--;
                            if (_max==0) TRACE("*** MAX I sample diagnostic output\n");
                            }
                        }
#ifdef _OPENMP
                        if ( g.verbose > 1 && (otm[j+1] || xcc[j+1]) && omp_get_thread_num() == 0 )
#else
                        if ( g.verbose > 1 && (otm[j+1] || xcc[j+1]) )
#endif
                        {
                            char _tag[6];
                            static int _max = 10;
                            if (_max > 0)
                            {
                            snprintf(_tag, sizeof(_tag), "%c%04d", (j+1) % 2 ? 'q' : 'i', (j+1) / 2); _tag[5] = '\0';
                            TRACE("block="__SIZE_T_SPECIFIER",%s=0x%04x%s%s\n",
                                n_count, _tag, _q->ui, xcc[j+1]?",INVALID":"", otm[j+1]?",OTM":"");
                            _max--;
                            if (_max==0) TRACE("*** MAX Q sample diagnostic output\n");
                            }
                        }
                    }

                    //http://stackoverflow.com/questions/7661114/the-openmp-master-pragma-must-not-be-enclosed-by-the-parallel-for-pragma
                    //#pragma omp master it is error
                    //#pragma omp critical it is right
#ifdef _OPENMP
                    if (g.verbose > 3 && omp_get_thread_num() == 0)
#else
                    if (g.verbose > 3)
#endif
                    {
                        int16_t *_iq = (int16_t *)&b[i*PAGE];
                        char _tag[6];
                        int _s;

                        TRACE("--- Decoded input block ---\n");
                        for (_s = 0; _s<32; _s++, _iq++)  // N=number of samples to dump
                        {
                            snprintf(_tag, sizeof(_tag), "%c%04d", _s % 2 ? 'q' : 'i', _s / 2); _tag[5] = '\0';
                            TRACE("%s, sample=%+5d, otm=%d, xcc=%d\n",
                                _tag, *_iq, otm[_s], xcc[_s]);
                        }
                    }
                }

                // render ASCII output
                if( g.ofmt[1] == '\0' )
                {
                    // TODO: figure out why we get a blob of NUL characters every 1024 samples

                    #pragma omp parallel for private(i,j)
                    for (i=0; i < g.threads; i++)
                    {
                        int16_t *in = (int16_t *)&b[i*PAGE];
                        char   *out = (char *)&a[i*PAGE*8];
                        char   *otm = (char *)&t[i*PAGE];
                        char   *xcc = (char *)&x[i*PAGE];

                        if ( (unsigned)i >= n ) continue;   // this thread did get a block read - does no work
                        for (j=0; j < PAGE/2; j+=2)         // PAGE/sizeof(sample_t)
                        {
                            const char f1 = (xcc[j] || xcc[j + 1]) ? 'X' : ' ';
                            const char f2 = (otm[j] || otm[j + 1]) ? 'T' : ' ';
                            //#pragma warning(disable:4996)
                            snprintf(&out[j * 8], 16, "%+5d,%+5d,%c%c\r\n",*in++, *in++, f1, f2);
                        }
                    }

#ifdef _OPENMP
                    if (g.verbose > 3 && omp_get_thread_num() == 0)
#else
                    if (g.verbose > 3)
#endif
                    {
                        char _s[(32*16)+1];
                        memcpy(_s,a,32*16); _s[sizeof(_s)-1] = '\0';
                        TRACE("--- ASCII output block ---\n");
                        TRACE("%s\n",_s);
                    }

                    // TODO: refine the timestamp for the first sample of the output block
                    //       and figure out a way to express it in the ASCII output stream

                    //#pragma omp master
                    r = fwrite(a,PAGE*8,n,g.outfd); // NB: output is *exactly* 8 times larger than the input buffer
                    //#pragma omp barrier
                }
                // render BINARY output
                else if( g.ofmt[1] == 'b' )
                {
                    // TODO: refine the timestamp for the first sample of the output block
                    // TODO: produce the ASCII index file correlating sample with timestamp

#ifdef _OPENMP
                    if (g.verbose > 3 && omp_get_thread_num() == 0)
#else
                    if (g.verbose > 3)
#endif
                    {
                        uint16_t *_hex = (uint16_t *)b;
                        int16_t *_iq = (int16_t *)b;
                        char _tag[6];
                        int _s;

                        TRACE("--- Binary output block ---\n");
                        for (_s = 0; _s<32; _s++, _hex++, _iq++)  // N=number of samples to dump
                        {
                            snprintf(_tag, sizeof(_tag), "%c%04d", _s % 2 ? 'q' : 'i', _s / 2); _tag[5] = '\0';
                            TRACE("%s=0x%04x, sample=%+5d\n",
                                _tag, *_hex, *_iq);
                        }
                    }

                    //#pragma omp master
                    r = fwrite(b,PAGE,n,g.outfd);
                    //#pragma omp barrier
                }
                // render NO output
                else
                {
#ifdef _OPENMP
                    if (g.verbose > 3 && omp_get_thread_num() == 0)
#else
                    if (g.verbose > 3)
#endif
                    { TRACE("--- Render No Output ---\n"); }

                    //#pragma omp master
                    r = n;
                    //#pragma omp barrier
                }

                //TRACE("r="__SIZE_T_SPECIFIER"\n", r);

                //#pragma omp master
                n_count = n_count + n;
                r_count = r_count + r;
                //#pragma omp barrier

                // Diagnostics
                #pragma omp parallel for private(i,j) reduction(+:t_count,x_count)
                for (i=0; i < g.threads; i++)
                {
                    char *otm = (char *)&t[i*PAGE];
                    char *xcc = (char *)&x[i*PAGE];

                    if ( (unsigned)i >= n ) continue;
                    for (j=0; j < PAGE; j++)
                    {
                         t_count = t_count + otm[j];
                         x_count = x_count + xcc[j];
                    }
                }

                //TRACE("t_count="__SIZE_T_SPECIFIER"\n", t_count);
                //TRACE("x_count="__SIZE_T_SPECIFIER"\n", x_count);

            } // while(!feof)
        //}   // parallel

        LOG(__SIZE_T_SPECIFIER" records in\n",n_count);
        LOG(__SIZE_T_SPECIFIER" records out\n",r_count);
        if (t_count > 0) INFO(__SIZE_T_SPECIFIER" On-Time-Markers\n", t_count);
        if (x_count > 0) INFO(__SIZE_T_SPECIFIER" Invalid Samples\n", x_count);
        if (n_count > 0) INFO(__SIZE_T_SPECIFIER" Total Samples\n", n_count * (PAGE/2));
    }

    if( g.infd )  fclose(g.infd);
    if( g.outfd ) fclose(g.outfd);
    return 0;
}
