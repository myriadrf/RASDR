// raw2iq.c - A tool for converting RASDRstreamer .raw files to interleaved I,Q
//
// Acknowledgements:

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // for tolower()
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
} g = { NULL, "wb", NULL, NULL, NULL };

void usage( const char *argv0 )
{
    printf("Convert RASDRstreamer raw stream into a I/Q output"
    "\n"
	"\nUsage:"
	"\n%s [OPTIONS]"
	"\nWhere:"
	"\n  -i, --input-file FILE   Full path to file to be read or - for stdin"
	"\n  -o, --output-file FILE  Full path to file to be written or - for stdout"
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

        if (strncmp(key, "-h", 2) == 0 || strncmp(key, "--help", 6) == 0) {
            usage(argv[0]);
        }
        if (strncmp(key, "-i", 2) == 0 || strncmp(key, "--input-file", 12) == 0) {
            if ((i + 1) >= argc)
                break;
            g.infile = argv[++i];
        }
        if (strncmp(key, "-o", 2) == 0 || strncmp(key, "--output-file", 13) == 0) {
            if ((i + 1) >= argc)
                break;
            g.outfile = argv[++i];
        }
    }
    if (g.infile == NULL || strcmp(g.infile,"-") == 0) {
        g.infd = stdin;
        g.infile = "stdin";
    } else {
        g.infd = fopen(g.infile, "r");
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
#define LOG(fmt, ...) \
            do { fprintf(stderr, fmt, __VA_ARGS__); } while (0)

int main(int argc, char *argv[], char *envp[])
{
    argparse(argc,argv,envp);

    LOG("input=%s\n",g.infile);
    LOG("output=%s, fmt=%s\n",g.outfile,g.ofmt);
    LOG("CPU Threads=%d\n", g.threads);

    if( g.infd )  fclose(g.infd);
    if( g.outfd ) fclose(g.outfd);
    return 0;
}
