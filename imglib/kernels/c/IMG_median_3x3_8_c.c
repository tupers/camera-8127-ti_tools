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
/*      IMG_median_3x3_8                                                    */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_median_3x3_8                                           */
/*         (                                                                */
/*             const unsigned char *restrict i_data, // Input image     //  */
/*             int n,                                // Length of input //  */
/*             unsigned char       *restrict o_data  // Output image    //  */
/*          )                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*      This kernel performs a 3x3 median filter operation on 8-bit         */
/*      unsigned values.  The median filter comes under the class           */
/*      of non-linear signal processing algorithms.                         */
/*                                                                          */
/*      Rather than replace the grey level at a pixel by a weighted         */
/*      average of the nine pixels including and surrounding it, the        */
/*      grey level at each pixel is replaced by the median of the nine      */
/*      values.  The median of a set of nine numbers is the middle          */
/*      element so that half of the elements in the list are larger and     */
/*      half are smaller.  Median filters remove the effects of extreme     */
/*      values from data, such as salt and pepper noise, although using     */
/*      a wide may result in unacceptable blurring of sharp edges in        */
/*      the original image.                                                 */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      This implementation uses an incremental sorting technique to        */
/*      greatly reduce the number of compares and exchanges necessary       */
/*      to sort the image pixels.                                           */
/*                                                                          */
/*      The main loop reads three new pixels from the input image each      */
/*      iteration.  These three pixels form the right edge of the filter    */
/*      mask.  The filter data from the previous iteration is "slid         */
/*      over" by one pixel to form the complete 3x3 mask.                   */
/*                                                                          */
/*      As 3-pixel is read in from the image, the pixels are sorted,        */
/*      resulting in a "lo", "medium" and "hi" pixel value for that         */
/*      column.  The result is that the filter mask is sorted into          */
/*      three rows -- a row of "minimums", a row of "middle values",        */
/*      and a row of "maximums".                                            */
/*                                                                          */
/*      The median filter operates from this partially ordered mask.        */
/*      It finds the smallest element in the row of "maximums",             */
/*      the middle element in the row of "middle values", and               */
/*      the largest element in the row of "minimums".  The median           */
/*      value of these three values is the median for the entire 3x3        */
/*      mask.                                                               */
/*                                                                          */
/*      This process minimizes compares, as the whole mask does not         */
/*      need to be sorted between iterations.  Rather, the partial          */
/*      ordering for two of the three columns from one iteration is         */
/*      used directly for the next iteration.                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  BIBLIOGRAPHY                                                            */
/*      Knuth, Donald E.  The_Art_of_Computer_Programming, Vol 3,           */
/*          Pg. 180:  "Minimum Comparison Sorting."                         */
/*                                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_median_3x3_8_cn,   ".text:ansi");

void IMG_median_3x3_8_cn
(
    const unsigned char *restrict i_data,
    int n,
    unsigned char       *restrict o_data
)
{
    unsigned char c0h, c1h, c2h, h_min;  /* "hi",  columns 0..2, and "min" */
    unsigned char c0m, c1m, c2m, m_mid;  /* "mid", columns 0..2, and "mid" */
    unsigned char c0l, c1l, c2l, l_max;  /* "lo",  columns 0..2, and "max" */
    unsigned char m_h, m_l, tmp, out;

    int i;

    /* -------------------------------------------------------------------- */
    /*  Start off with a well-defined initial state.                        */
    /* -------------------------------------------------------------------- */
    c1h = c2h = c1m = c2m = c1l = c2l = 127;

    /* -------------------------------------------------------------------- */
    /*  Iterate over the input row.                                         */
    /* -------------------------------------------------------------------- */
#ifndef NOASSUME
    _nassert((int) i_data % 4 == 0);
    _nassert((int) o_data % 4 == 0);
#   pragma MUST_ITERATE(4,,4);
#endif
    for (i = 0; i < n; i++)
    {
        /* ---------------------------------------------------------------- */
        /*  Slide our two previous columns of sorted pixels over by 1.      */
        /* ---------------------------------------------------------------- */
        c0h = c1h;    c1h = c2h;
        c0m = c1m;    c1m = c2m;
        c0l = c1l;    c1l = c2l;

        /* ---------------------------------------------------------------- */
        /*  Load in a new column of pixels, and sort into lo, med, high.    */
        /* ---------------------------------------------------------------- */
        c2h = i_data[i      ];
        c2m = i_data[i +   n];
        c2l = i_data[i + 2*n];

        if (c2l > c2h) { tmp = c2l; c2l = c2h; c2h = tmp; }
        if (c2l > c2m) { tmp = c2l; c2l = c2m; c2m = tmp; }
        if (c2m > c2h) { tmp = c2m; c2m = c2h; c2h = tmp; }

        /* ---------------------------------------------------------------- */
        /*  Find the minimum value of the "hi" terms.                       */
        /* ---------------------------------------------------------------- */
        h_min = c2h;
        if (c1h < h_min) { h_min = c1h; }
        if (c0h < h_min) { h_min = c0h; }

        /* ---------------------------------------------------------------- */
        /*  Find the middle value of the "mid" terms.                       */
        /* ---------------------------------------------------------------- */
        m_l   = c0m;
        m_mid = c1m;
        m_h   = c2m;

        if (m_l   > m_h  ) { tmp = m_l; m_l = m_h; m_h = tmp; }
        if (m_l   > m_mid) { m_mid = m_l; }
        if (m_mid > m_h  ) { m_mid = m_h; }

        /* ---------------------------------------------------------------- */
        /*  Find the maximum value of the "lo" terms.                       */
        /* ---------------------------------------------------------------- */
        l_max = c2l;
        if (c1l > l_max) { l_max = c1l; }
        if (c0l > l_max) { l_max = c0l; }

        /* ---------------------------------------------------------------- */
        /*  Find the middle value of "h_min", "m_mid", "l_max" into "out".  */
        /* ---------------------------------------------------------------- */
        out = m_mid;

        if (h_min > l_max) { tmp   = h_min; h_min = l_max; l_max = tmp; }
        if (h_min > out  ) { out   = h_min; }
        if (out   > l_max) { out   = l_max; }

        /* ---------------------------------------------------------------- */
        /*  Store the resulting pixel.                                      */
        /* ---------------------------------------------------------------- */
        o_data[i] = out;
    }
}

/* ======================================================================== */
/*  End of file:  IMG_median_3x3_8_c.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
