// http://stackoverflow.com/questions/27303062/strstr-function-like-that-ignores-upper-or-lower-case

#include <stdlib.h> // for size_t
#include <ctype.h>  // for tolower()

char* stristr(const char* haystack, const char* needle, size_t len)
{
    do {
        const char* h = haystack;
        const char* n = needle;
        while (tolower((unsigned char) *h) == tolower((unsigned char ) *n) && *n) {
            h++;
            n++;
        }
        if (*n == 0) {
            return (char *) haystack;
        }
    } while (*haystack++ && len--);
    return 0;
}
