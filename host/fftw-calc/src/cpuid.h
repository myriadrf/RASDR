/* cpuid.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 01/19/2012
 * Last Modified    : 01/19/2014
 *   Bogdan Vacaliuc - introduce cpuid_info_t, cpuid_get_info(), refactor
 * 
 * 
 * And of course... The typical copyright stuff...
 * 
 *      Redistribution of this program in both source or binary, regardless of
 *  form, with or without modification is permitted as long as the following
 *  conditions are met:
 *          1.  This copyright notice is maintained either inline in the source
 *              or distributed with the binary.
 *          2.  A list of all contributing authors along with their contributions
 *              is included either inline in the source or distributed with the
 *              binary.
 *          3.  The following disclaimer is maintained either inline in the
 *              source or distributed with the binary.
 * 
 *  Disclaimer:
 *  This software is provided "as is", without any guarantee made to its
 *  suitability or fitness for any particular use. It may contain bugs so use
 *  of this program is at your own risk. I take no responsibility for any
 *  damage that may unintentionally be caused through its use.
 */

#ifndef _cpuid_h
#define _cpuid_h
#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && !defined(__cplusplus)
    // TODO: perhaps test version number when M$ updates the compiler
    #pragma once
    #define bool int
    #define true  (1==1)
    #define false (1==0)
#else
    // C99+
    #include <stdbool.h>
#endif
#if defined(_MSC_VER)
#include <intrin.h>
#define cpuid __cpuid
#else
void cpuid(int *info,int x);
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    int info[4];    // buffer from CPUID instruction
    union {
        int  buf[13];
        char str[13*sizeof(int)];
    } name;
    int threads;    // concurrency metric
    struct {
        bool x64;
        bool MMX;
        bool SSE;
        bool SSE2;
        bool SSE3;
        bool SSSE3;
        bool SSE41;
        bool SSE42;
        bool SSE4a;
        bool AVX;
        bool XOP;
        bool FMA3;
        bool FMA4;
    } exts;
} cpuid_info_t;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void cpuid_get_info( cpuid_info_t *s );
void cpuid_print_name();
void cpuid_print_exts();
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
