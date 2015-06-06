/* cpuid.c
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

#ifndef _cpuid_c
#define _cpuid_c
#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#endif
#include "cpuid.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#else
void cpuid(int *info,int x){
    int ax,bx,cx,dx;

    __asm__ __volatile__ ("cpuid": "=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (x));

    info[0] = ax;
    info[1] = bx;
    info[2] = cx;
    info[3] = dx;
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void cpuid_get_info( cpuid_info_t *p ){
    if( !p ) return;

    cpuid(p->name.buf + 0,0x80000002);
    cpuid(p->name.buf + 4,0x80000003);
    cpuid(p->name.buf + 8,0x80000004);
    p->name.buf[12] = '\0';
#ifdef _OPENMP
    p->threads = omp_get_max_threads();
#else
    p->threads = -1;
#endif

    //  Detect Instruction Set
    cpuid(p->info,0);
    if (p->info[0] >= 1){
        cpuid(p->info,0x00000001);
        p->exts.MMX   = (p->info[3] & ((int)1 << 23)) != 0;
        p->exts.SSE   = (p->info[3] & ((int)1 << 25)) != 0;
        p->exts.SSE2  = (p->info[3] & ((int)1 << 26)) != 0;
        p->exts.SSE3  = (p->info[2] & ((int)1 <<  0)) != 0;

        p->exts.SSSE3 = (p->info[2] & ((int)1 <<  9)) != 0;
        p->exts.SSE41 = (p->info[2] & ((int)1 << 19)) != 0;
        p->exts.SSE42 = (p->info[2] & ((int)1 << 20)) != 0;

        p->exts.AVX   = (p->info[2] & ((int)1 << 28)) != 0;
        p->exts.FMA3  = (p->info[2] & ((int)1 << 12)) != 0;
    }
    cpuid(p->info, 0x80000000);
    if (p->info[0] >= 0x80000001){
        cpuid(p->info,0x80000001);
        p->exts.x64   = (p->info[3] & ((int)1 << 29)) != 0;
        p->exts.SSE4a = (p->info[2] & ((int)1 <<  6)) != 0;
        p->exts.FMA4  = (p->info[2] & ((int)1 << 16)) != 0;
        p->exts.XOP   = (p->info[2] & ((int)1 << 11)) != 0;
    }
}
void cpuid_print_name(){
    int name[13];
    cpuid(name + 0,0x80000002);
    cpuid(name + 4,0x80000003);
    cpuid(name + 8,0x80000004);
    name[12] = '\0';

    printf("CPU Name = %s\n",(char*)name);
#ifdef _OPENMP
    printf("Threads  = %d\n",omp_get_max_threads());
#else
    printf("Threads  = -1/Unknown (not compiled for OpenMP)\n");
#endif
    printf("\n");
}
void cpuid_print_exts(){
    cpuid_info_t s;
    cpuid_get_info(&s);

    printf("Hardware Features:\n");
    printf("x64   = %d\n",s.exts.x64?1:0);
    printf("MMX   = %d\n",s.exts.MMX?1:0);
    printf("SSE   = %d\n",s.exts.SSE?1:0);
    printf("SSE2  = %d\n",s.exts.SSE2?1:0);
    printf("SSE3  = %d\n",s.exts.SSE3?1:0);
    printf("SSSE3 = %d\n",s.exts.SSSE3?1:0);
    printf("SSE4a = %d\n",s.exts.SSE4a?1:0);
    printf("SSE41 = %d\n",s.exts.SSE41?1:0);
    printf("SSE42 = %d\n",s.exts.SSE42?1:0);
    printf("AVX   = %d\n",s.exts.AVX?1:0);
    printf("FMA3  = %d\n",s.exts.FMA3?1:0);
    printf("FMA4  = %d\n",s.exts.FMA4?1:0);
    printf("XOP   = %d\n",s.exts.XOP?1:0);
    printf("\n");
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
