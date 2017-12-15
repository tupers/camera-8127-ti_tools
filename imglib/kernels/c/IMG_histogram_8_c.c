/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB-2  DSP Image/Video Processing Library                            */
/*                                                                          */
/*      Release:        Revision 2.0.1                                      */
/*      Snapshot date:  6-May-2008                                          */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      histogram                                                           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*       void IMG_histogram_8_cn(unsigned char * image, int  n, int         */
/*                              accumulate, unsigned short * t_hist,        */
/*                              unsigned short * hist)                      */
/*                                                                          */
/*           image      =  input image data                                 */
/*           n          =  number of points                                 */
/*           accumulate =  defines addition/subtract from existing          */
/*                         histogram: 1, -1                                 */
/*           t_hist     =  temporary histogram bins (1024)                  */
/*           hist       =  running histogram bins (256)                     */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This code takes a histogram of an array of n, 8 bit inputs. It      */
/*      returns the histogram of 256 bins at 16 bit precision.  It can      */
/*      either add or subtract to an existing histogram, using the          */
/*      'accumulate' control.  It requires some temporary storage for 4     */
/*      temporary histograms, which are later summed together.              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      It is assumed that the array of data, t_hist is initialized         */
/*      to zero.  The input array of image data must be aligned to an 8     */
/*      byte boundary and n must be a multiple of 8.  The maximum number    */
/*      of pixels that can be profiled in each bin is 65535 in the main     */
/*      histogram and the maximum n is 262143.                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_histogram_8_cn,   ".text:ansi");

void IMG_histogram_8_cn
(
    const unsigned char *restrict image,
    int   n, 
    short accumulate,
    short *restrict t_hist,
    short *restrict hist
)
#if 1
{
    /* -------------------------------------------------------------------- */
    /*  This is pretty much bit-exact with our optimized implementation.    */
    /* -------------------------------------------------------------------- */
    int p0, p1, p2, p3, i;

#ifndef NOASSUME
    _nassert((int)t_hist % 8 == 0);
    _nassert((int)hist   % 8 == 0);
    _nassert(n % 8 == 0);
    _nassert(n >= 8);    
    #pragma MUST_ITERATE(2,,2);
#endif

    /* -------------------------------------------------------------------- */
    /*  This loop is unrolled four times, producing four interleaved        */
    /*  histograms into a temporary buffer.                                 */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < n; i += 4)
    {
        p0 = image[i + 0] * 4 + 0;
        p1 = image[i + 1] * 4 + 1;
        p2 = image[i + 2] * 4 + 2;
        p3 = image[i + 3] * 4 + 3;

        t_hist[p0]++;
        t_hist[p1]++;
        t_hist[p2]++;
        t_hist[p3]++;
    }

    /* -------------------------------------------------------------------- */
    /*  Accumulate the interleaved histograms back into the final           */
    /*  histogram buffer.                                                   */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < 256; i++)
    {
        hist[i] += (t_hist[i*4 + 0] +
                    t_hist[i*4 + 1] +
                    t_hist[i*4 + 2] +
                    t_hist[i*4 + 3]) * accumulate;
    }
}
#else
{
    /* -------------------------------------------------------------------- */
    /*  This is the cannonical form for Histogram.  We cannot use this      */
    /*  here, as it does not use the temporary array "t_hist", and that's   */
    /*  an "output" of our code.                                            */
    /* -------------------------------------------------------------------- */
    int pixel, j; 
    for (j = 0; j < n; j++) 
    {
        pixel = (int) image[j];
        hist[pixel] += accumulate;
    }
}
#endif
/* ======================================================================== */
/*  End of file:  IMG_histogram_8_c.c                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
