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
/* NAME                                                                     */
/*     IMG_median_3x3_16s                                                   */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_median_3x3_16s                                         */
/*          (                                                               */
/*             const short *restrict i_data,                                */
/*             int                        n,                                */
/*             short       *restrict o_data                                 */
/*          )                                                               */
/*                                                                          */
/*      i_data  == Input image containing 3 rows (i.e., size of 3 x n).     */
/*      n       == Width of input image.                                    */
/*      o_data  == Output image containing 1 row (i.e., size of 1 x n).     */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This kernel performs a 3x3 median filter operation on 16-bit        */
/*      signed image pixels. The grey level at each pixel is replaced by    */
/*      the median of nine adjacent values. The median of a set of nine     */
/*      numbers is the middle element so that half of the elements in the   */
/*      list are larger and half are smaller. The input image contains 3    */
/*      adjacent rows from an actual image. The output array will be of     */
/*      size 1 row containing the median values of the middle row of the    */
/*      input. For the first two output's, the two columns outside the      */
/*      image are assumed to be all zeros.                                  */
/*                                                                          */
/*      The first 2 values in the output array will not be containing       */
/*      any meaningful data. The 3rd value in the output array will be      */
/*      the median of 2nd value in the middle row of input array and so on. */
/*      The nth value in the output array will be the median of the (n-1)th */
/*      value in the mid row of input array. Hence the output array will    */
/*      not contain the median values of first and last elements in the     */
/*      middle row of input image. Instead it will contain 2 meaningless    */
/*      values at the beginning of the array.                               */
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
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. The input array and output array should not overlap.             */
/*      2. Both input and output arrays must be double-word aligned.        */
/*      3. The minimum value for width of input image 'n' is 4.             */
/*      4. The width of input image 'n' must be a multiple of 4.            */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible for both C64x and C64x+ processors.         */
/*                                                                          */
/*  SOURCE                                                                  */
/*      median_3x3 in IMGLIB obtained from Texas Instruments.               */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_median_3x3_16s,   ".text:intrinsic");


void IMG_median_3x3_16s
(
    const short *restrict i_data,
    int                        n,
    short       *restrict o_data
)
{
    const    int     *line0,       *line1,       *line2;
    int              *line_y;
    int              i;
    unsigned int     R00,          R10,          R20;
    unsigned int     R01,          R11,          R21;
    unsigned int     x0_01,        x1_01,        x2_01;
    unsigned int     R_max1,       R_min1,       R_min2;
    unsigned int     row0_pk,      row1_pk,      row2_pk;
    unsigned int     min_max,      med_med,      max_min;
    unsigned int     med_max1,     med_min1,     med_min2;
    unsigned int     median2;

    line0  = (int *) i_data;
    line1  = (int *) (i_data + n);
    line2  = (int *) (i_data + n * 2);
    line_y = (int *) o_data; 

    /*======================================================================*/
    /* Initialise with the middle value in the range of 16 bit signed short */
    /*======================================================================*/
    R00    = 0x00000000;
    R10    = 0x00000000;
    R20    = 0x00000000;

    /*======================================================================*/
    /* Inform the compiler about assumptions that can be made.              */
    /* 1. Minimum value for width of input image 'n' is 4.                  */
    /* 2. Width of input image 'n' is a multiple of 4.                      */
    /* 3. All the 3 adjacent rows in input array are double-word aligned.   */
    /* 4. Output image array is double-word aligned.                        */
    /*======================================================================*/

    _nassert(          n       >= 4);
    _nassert(          n  % 4  == 0);
    _nassert((int) line0  % 8  == 0);
    _nassert((int) line1  % 8  == 0);
    _nassert((int) line2  % 8  == 0);
    _nassert((int) line_y % 8  == 0);

    #pragma MUST_ITERATE(2,,2)
    #pragma UNROLL(2)
    for (i = 0 ; i < n; i += 2)
    {
       
        /*==================================================================*/
        /* Get the input into x0_01,x1_01,x2_01 each containing 2 elements  */
        /* Get 2 columns of 3 rows of elements sorted columnwise in         */      
        /* descending order                                                 */      
        /*==================================================================*/

     
        x0_01    = *line0++;
        x1_01    = *line1++;
        x2_01    = *line2++;


        R_max1   = _max2(x0_01,x1_01);   
        R_min1   = _min2(x0_01,x1_01);
        R_min2   = _min2(R_max1,x2_01);

     
        /*==================================================================*/
        /* Sorted columns                                                   */   
        /*==================================================================*/
        R01      = _max2(R_max1,x2_01);
        R11      = _max2(R_min1,R_min2);
        R21      = _min2(R_min1,R_min2);

        row0_pk  = _packlh2(R01,R00);
        row1_pk  = _packlh2(R11,R10);
        row2_pk  = _packlh2(R21,R20);
     

        /*==================================================================*/
        /* Find the min value among R00, R01,row0_pk to get min of max      */
        /*==================================================================*/

        min_max  = _min2(R00,R01);
        min_max  = _min2(min_max,row0_pk);
    

        /*==================================================================*/
        /* Find the med value among R10,R11,row1_pk to get med of med       */
        /*==================================================================*/

        med_max1 = _max2(R10,R11);
        med_min1 = _min2(R10,R11);
        med_min2 = _min2(med_max1,row1_pk);
        med_med  = _max2(med_min1,med_min2);


        /*==================================================================*/
        /* Find the max value among R20,R21,row2_pk to get max of min       */
        /*==================================================================*/

        max_min  = _max2(R20,R21);
        max_min  = _max2(max_min,row2_pk);


        /*==================================================================*/
        /* Find the med value among min_max,med_med and max_min             */
        /*==================================================================*/
     
        med_max1 = _max2(min_max,med_med);
        med_min1 = _min2(min_max,med_med);
        med_min2 = _min2(med_max1,max_min);
        median2  = _max2(med_min1,med_min2);

        *line_y++ = median2;     

        /*==================================================================*/
        /* Store the already sorted columns into R00, R10 and R20           */
        /*==================================================================*/

        R00 = R01;
        R10 = R11;
        R20 = R21;
     
    }
}
/* =========================================================================*/
/*  End of file:  IMG_median_3x3_16s_i.c                                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* =========================================================================*/
