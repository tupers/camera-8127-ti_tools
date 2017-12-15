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
/*==========================================================================*/
/*                                                                          */
/*    TEXAS INSTRUMENTS, INC.                                               */
/*                                                                          */
/*    NAME                                                                  */
/*          median3x3                                                       */
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
/*  ASSUMPTIONS                                                             */
/*      The length 'n' must be a multiple of four.                          */
/*      The length of the input array must by 3*n                           */
/*      The input pointers must be word aligned.                            */
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
#pragma CODE_SECTION(IMG_median_3x3_8,   ".text:intrinsic");

/*============================================================================*/
void IMG_median_3x3_8(const unsigned char *restrict ptr_in, int n,
        unsigned char *restrict ptr_out)
{
    const int   *line0, *line1, *line2;
    int    *line_y;
    int    i;
    int    x0_3210, x1_3210, x2_3210;
    int    x1_3210_a, x2_3210_a;
    int    x0_3210_b, x1_3210_b;
    int    x1_3210_c, x2_3210_c;
    int    x01x00, x11x10, x21x20;
    int    max0_3210, max1_3210;
    int    minmax_3210;
    int    min0_3210, min1_3210, min2_3210;
    int    maxmin_3210;
    int    med0_3210, med1_3210;
    int    maxmed_3210_0;
    int    minmed_3210_0, minmed_3210_1;
    int    medmed_3210;
    int    maxa_3210;
    int    mina_3210, minb_3210;
    int    med_3210, med_3210a, med_3210b;
    int    d1_3210_a, m1_3210_a, x1_3210_a0, x1_3210_a1;
    int    d_med_3210, m_med_3210;
/*============================================================================*/
    line0 = (int *) ptr_in;
    line1 = line0 + (n>>2);
    line2 = line1 + (n>>2);
    line_y = (int *) ptr_out;

    x01x00 = 0x7f7f7f7f;
    x11x10 = 0x7f7f7f7f;
    x21x20 = 0x7f7f7f7f;
/*============================================================================*/
    for (i = 0 ; i < n; i += 4)
    {
         x0_3210 = *line0++;
         x1_3210 = *line1++;
         x2_3210 = *line2++;

         /*-------------sort 3 elements----------------*/
         /*  x0_3210_b x1_3210_c x2_3210_c             */

         d1_3210_a = _cmpgtu4(x2_3210, x1_3210);
         m1_3210_a = _xpnd4(d1_3210_a);
         x1_3210_a0 = x2_3210 & m1_3210_a;
         x1_3210_a1 = x1_3210 & ~m1_3210_a;
         x1_3210_a = x1_3210_a0 | x1_3210_a1;

         x2_3210_a = _minu4(x2_3210, x1_3210);

         x0_3210_b = _maxu4(x0_3210, x1_3210_a);
         x1_3210_b = _minu4(x0_3210, x1_3210_a);

         x1_3210_c = _maxu4(x2_3210_a, x1_3210_b);
         x2_3210_c = _minu4(x2_3210_a, x1_3210_b);
         /*-------------------------------------------*/

         /* form 4 sets of transposed maximums for each output */
         max0_3210 = _packlh2(x0_3210_b, x01x00);
         max1_3210 = _shlmb(x01x00, x0_3210_b);

         /* get 4 min of maxes  */
         minmax_3210 = _minu4(max0_3210, max1_3210);
         minmax_3210 = _minu4(minmax_3210, x0_3210_b);

         min0_3210 = _packlh2(x2_3210_c, x21x20);
         min1_3210 = _shlmb(x21x20, x2_3210_c);
         min2_3210 = x2_3210_c;

         /* 4 max of mins */
         maxmin_3210 = _maxu4(min0_3210,   min1_3210);
         maxmin_3210 = _maxu4(maxmin_3210, min2_3210);

         med0_3210 = _packlh2(x1_3210_c, x11x10);
         med1_3210 = _shlmb(x11x10, x1_3210_c);

         /* 4 med of meds */
         maxmed_3210_0 = _maxu4(med1_3210, x1_3210_c);
         minmed_3210_0 = _minu4(med1_3210, x1_3210_c);
         minmed_3210_1 = _minu4(med0_3210, maxmed_3210_0);
         medmed_3210 = _maxu4(minmed_3210_1, minmed_3210_0);

         /* final med of medmed minmax and maxmin */
         maxa_3210 = _maxu4(maxmin_3210, medmed_3210);
         mina_3210 = _minu4(maxmin_3210, medmed_3210);
         minb_3210 = _minu4(minmax_3210, maxa_3210);
         d_med_3210 = _cmpgtu4(minb_3210, mina_3210);
         m_med_3210 = _xpnd4(d_med_3210);

         med_3210a = minb_3210 & m_med_3210;
         med_3210b = mina_3210 & ~m_med_3210;
         med_3210 = med_3210a | med_3210b;

         x01x00 = _mvd(x0_3210_b);
         x11x10 = _mvd(x1_3210_c);
         x21x20 = _mvd(x2_3210_c);

         *line_y++ = med_3210;
    }
}
/* ======================================================================== */
/*  End of file:  IMG_median_3x3_8_i.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
