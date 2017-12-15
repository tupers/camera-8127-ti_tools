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
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_histogram_16                                                    */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*       void IMG_histogram_16                                              */
/*       (                                                                  */
/*          unsigned short *restrict       in,                              */
/*                     int                  n,                              */
/*                     int         accumulate,                              */
/*          unsigned short *restrict   t_hist,                              */
/*          unsigned short *restrict     hist,                              */
/*                     int           img_bits                               */
/*       )                                                                  */
/*                                                                          */
/*           image      =  input image data                                 */
/*           n          =  number of points                                 */
/*           accumulate =  defines addition/subtract from existing          */
/*                         histogram: 1, -1                                 */
/*           t_hist     =  temporary histogram bins( (2^img_bits) * 4)      */
/*           hist       =  running histogram bins (2^img_bits)              */
/*           img_bits   =  number of valid data bits in a pixel.            */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This code takes a histogram of an array (of type short) with n      */
/*      number of pixels, with "img_bits" being the number of               */
/*      valid data bits in a pixel. It returns the histogram of             */
/*      corresponding number of bins at "img_bits" bits precision. It can   */
/*      either add or subtract to an existing histogram, using the          */
/*      'accumulate' control.  It requires some temporary storage for 4     */
/*      temporary histograms, which are later summed together.The length    */
/*      of the hist and the t_hist arrays depends on the value of           */
/*      "img_bits" . Actual length of hist is (2 ^IMG_BITS) and that of     */
/*      t_hist is (4 * (2 ^ IMG_BITS)) as there are no pixel values greater */
/*      than or equal to  (2 ^ IMG_BITS) in the given image.                */
/*                                                                          */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes have restrictions as noted in the ASSUMPTIONS   */
/*      bellow.                                                             */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. 'n' must be a multiple of 8 and greater than or equal to 8.      */
/*      2. The arrays t_hist is initialized to zero.                        */
/*      3. all arrays must be double word aligned.                          */
/*      5. Input and output arrays do not overlap.                          */
/*      6. img_bits must be atleast 1 and at most 16                        */
/*      7. Max number of pixels that can be profiled in each bin is 32767   */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      This code operates on four interleaved histogram bins.  The loop    */
/*      is divided into two halves:  The "even" half operates on the        */
/*      even-numbered double-words from the input image, and the "odd"      */
/*      half operates on odd double-words.  Each half processes four        */
/*      pixels at a time, and both halves operate on the same four sets     */
/*      of histogram bins. This introduces a memory dependency on the       */
/*      histogram bins which ordinarily would degrade performance. To       */
/*      break the memory depenencies, the two halves forward their results  */
/*      to each other via the register file, bypassing memory.              */
/*                                                                          */
/*      Exact memory access ordering obviates the need to predicate         */
/*      stores within the loop.                                             */
/*                                                                          */
/*      The algorithm is ordered as follows:                                */
/*                                                                          */
/*        1. Load from histogram for even half                              */
/*        2. Store odd_bin to histogram for odd half (previous itn.)        */
/*        3. if data_even == previous data_odd increment even_bin by 2      */
/*           else increment even_bin by 1, forward to odd                   */
/*        4. Load from histogram for odd half (current itn.)                */
/*        5. Store even_bin to histogram for even half                      */
/*        6. if data_odd == previous data_even increment odd_bin by 2       */
/*           else increment odd_bin by 1, forward to even                   */
/*        7. goto 1.                                                        */
/*                                                                          */
/*      With this particular ordering, forwarding is necessary between      */
/*      even/odd halves when pixels in adjacent halves need to be           */
/*      placed in the same bin.                                             */
/*      The store is never predicated and occurs speculatively              */
/*      as it will be overwritten by the next value containing the          */
/*      extra forwarded value.                                              */
/*                                                                          */
/*      The four histograms are interleaved with each bin spaced four       */
/*      half-words apart and each histogram starting in a different         */
/*      memory bank. This allows the four histogram accesses to             */
/*      proceed in any order without worrying about bank conflicts.         */
/*      The diagram below illustrates this:  (addresses are halfword        */
/*      offsets)                                                            */
/*                                                                          */
/*           0       1       2       3       4       5       6   ...        */
/*       | hst 0 | hst 1 | hst 2 | hst 3 | hst 0 | hst 1 | ...   ...        */
/*       | bin 0 | bin 0 | bin 0 | bin 0 | bin 1 | bin 1 | ...   ...        */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible with both c64x+ and c64x  processors        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_histogram_16_cn,   ".text:ansi");



void IMG_histogram_16_cn
(
     unsigned short *restrict       in,  /* input image data                */
                int                  n,  /* number of input image pixels    */
                int         accumulate,  /* define add/sum for histogtram   */
              short *restrict   t_hist,  /* temporary histogram bins        */
              short *restrict     hist,  /* running histogram bins          */
                int           img_bits   /* number of data bits in a pixel  */
)
#if 1
{
    
    int    p0,     p1,   p2;
    int    p3,     i,    length;

    
    /* -------------------------------------------------------------------- */
    /*  This loop is unrolled four times, producing four interleaved        */
    /*  histograms into a temporary buffer.                                 */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < n; i += 4)
    {
        p0 = in[i    ] * 4 ;
        p1 = in[i + 1] * 4 + 1;
        p2 = in[i + 2] * 4 + 2;
        p3 = in[i + 3] * 4 + 3;

        t_hist[p0]++;
        t_hist[p1]++;
        t_hist[p2]++;
        t_hist[p3]++;
    }
    
    /* -------------------------------------------------------------------- */
    /*         calculate the length of the histogram array                  */
    /* -------------------------------------------------------------------- */
    length = 1 << img_bits;  
    
    
    /* -------------------------------------------------------------------- */
    /*  Accumulate the interleaved histograms back into the final           */
    /*  histogram buffer. loop iterates only "length" number of times as    */
    /*  there are no pixel values greater than or equal to "length"         */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < length; i++)
    {
        hist[i] += (t_hist[i * 4    ] +
                    t_hist[i * 4 + 1] +
                    t_hist[i * 4 + 2] +
                    t_hist[i * 4 + 3] ) * accumulate;
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
        pixel = (int) in[j];
        hist[pixel] += accumulate;
    }
}
#endif
/* ======================================================================== */
/*  End of file:  IMG_histogram_16_c.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
