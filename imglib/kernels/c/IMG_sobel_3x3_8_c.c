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
/*      sobel_3x3_8                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void sobel_3x3_8                                                    */
/*      (                                                                   */
/*          const unsigned char *in_data,      // Input image data  //      */
/*          unsigned char       *out_data,     // Output image data //      */ 
/*          short cols, short rows             // Image dimensions  //      */ 
/*      )                                                                   */
/*                                                                          */
/*      The sobel filter is applied to the input image.  The input image    */ 
/*      dimensions are given by the arguments 'cols' and 'rows'.  The       */
/*      output image is 'cols' pixels wide and 'rows - 2' pixels tall.      */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*      To see how the implementation is going to work on the input         */
/*      buffer, lets imagine we have the following input buffer:            */  
/*      lets imagine we have the following input buffer:                    */
/*                                                                          */
/*              yyyyyyyyyyyyyyyy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yyyyyyyyyyyyyyyy                                            */
/*                                                                          */
/*      The output buffer would be:                                         */
/*                                                                          */
/*              tXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXt                                            */  
/*                                                                          */
/*      Where:                                                              */
/*                                                                          */
/*          X = sobel(x)    The algorithm is applied to that pixel.         */
/*                          The correct output is obtained, the data        */ 
/*                          around the pixels we work on is used            */
/*                                                                          */
/*          t               Whatever was in the output buffer in that       */
/*                          position is kept there.                         */
/*                                                                          */
/*          z = sobel(y)    The algorithm is applied to that pixel.         */
/*                          The output is not meaningful, because the       */
/*                          necessary data to process the pixel is not      */
/*                          available.  This is because for each output     */
/*                          pixel we need input pixels from the right and   */
/*                          from the left of the output pixel.  But this    */ 
/*                          data doesn't exist.                             */
/*                                                                          */
/*      This means that we will only process (rows-2) lines.  Then, we      */
/*      will process all the pixels inside each line. Even though the       */
/*      results for the first and last pixels in each line will not         */
/*      be relevant, it makes the control much simpler and ends up          */
/*      saving cycles.                                                      */
/*                                                                          */ 
/*      Also the fist pixel in the first processed line and the             */ 
/*      last pixel in the last processed line will not be computed.         */ 
/*      It is not necessary, since the results would be bogus, and          */ 
/*      not computing them saves some time.                                 */ 
/*                                                                          */
/*      The following horizontal and vertical masks that are                */
/*      applied to the input buffer to obtain one output pixel.             */
/*                                                                          */
/*          Horizontal:                                                     */
/*              -1 -2 -1                                                    */
/*               0  0  0                                                    */
/*               1  2  1                                                    */
/*                                                                          */
/*          Vertical:                                                       */
/*              -1  0  1                                                    */
/*              -2  0  2                                                    */
/*              -1  0  1                                                    */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      n/a                                                                 */
/*                                                                          */
/*  NOTES                                                                   */
/*      The values of the left-most and right-most pixels on each line      */
/*      of the output are not well-defined.                                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_sobel_3x3_8_cn,   ".text:ansi");

void IMG_sobel_3x3_8_cn
(
    const unsigned char *restrict in,   /* Input image data   */
    unsigned char       *restrict out,  /* Output image data  */
    short cols, short rows              /* Image dimensions   */
)
{    
    int H, O, V, i;
    int i00, i01, i02;
    int i10,      i12;
    int i20, i21, i22;
    int w = cols;

#ifndef NOASSUME
    _nassert(cols > 3);
    _nassert(cols % 2 == 0);
    _nassert(rows > 3);
    _nassert(cols * (rows - 2) - 2 >= 8);
#endif

    /* -------------------------------------------------------------------- */
    /*  Iterate over entire image as a single, continuous raster line.      */
    /* -------------------------------------------------------------------- */
#ifndef NOASSUME
    #pragma MUST_ITERATE(8,,2);
#endif
    for (i = 0; i < cols*(rows-2) - 2; i++)
    {
        /* ---------------------------------------------------------------- */
        /*  Read in the required 3x3 region from the input.                 */
        /* ---------------------------------------------------------------- */
        i00=in[i    ]; i01=in[i    +1]; i02=in[i    +2];
        i10=in[i+  w];                  i12=in[i+  w+2];
        i20=in[i+2*w]; i21=in[i+2*w+1]; i22=in[i+2*w+2];

        /* ---------------------------------------------------------------- */
        /*  Apply horizontal and vertical filter masks.  The final filter   */
        /*  output is the sum of the absolute values of these filters.      */
        /* ---------------------------------------------------------------- */

        H = -   i00 - 2*i01 -   i02 +
            +   i20 + 2*i21 +   i22;

        V = -   i00         +   i02 
            - 2*i10         + 2*i12 
            -   i20         +   i22;    

        O = abs(H) + abs(V);

        /* ---------------------------------------------------------------- */
        /*  Clamp to 8-bit range.  The output is always positive due to     */
        /*  the absolute value, so we only need to check for overflow.      */
        /* ---------------------------------------------------------------- */
        if (O > 255) O = 255;

        /* ---------------------------------------------------------------- */
        /*  Store it.                                                       */
        /* ---------------------------------------------------------------- */
        out[i + 1] = O;
    }
}

/* ======================================================================== */
/*  End of file:  IMG_sobel_3x3_8_c.c                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
