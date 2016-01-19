// http://stackoverflow.com/questions/4515874/searching-for-a-fast-efficient-histogram-algorithm-with-pre-specified-bins

#include <stdlib.h>         // for calloc()
#include <math.h>           // for floor(), ceil()

typedef float elem_type;    // we need it to sort floats...

static inline int TRANSFER( const elem_type v, const elem_type min, const double factor, const int n )
{
    int index = (int)floor((v - min) * factor);
    if (index < 0)  return 0;
    if (index >= n) return n-1;
    return index;
}

elem_type histogram_select(elem_type arr[], int n)
{
    elem_type min = 370.0, max = -370.0;
    int bins;
    double range, factor;
    int *counts;
    int ii, cmax = 0, imax = 0;
    elem_type result;

    for(int i=0;i<n;i++) {
        if( arr[i] < min ) min = arr[i];
        if( arr[i] > max ) max = arr[i];
    }
    range  = max - min;
    bins   = (int)ceil(range * 10.0);
    factor = (range > 0.0) ? (double)bins / range : 0.0;

    if(bins <= 0) return min;
    counts = new int[bins];
    for(ii=0;ii<bins;ii++) counts[ii] = 0;
    for(ii=0;ii<n;ii++) counts[TRANSFER(arr[ii],min,factor,bins)]++;
    for(ii=0;ii<bins;ii++)
    {
        if( counts[ii] > cmax ) { cmax = counts[ii]; imax = ii; }
    }
    result = (((elem_type)imax / (elem_type)bins ) * ( max - min )) + min;
    delete counts;
    return result;
}

