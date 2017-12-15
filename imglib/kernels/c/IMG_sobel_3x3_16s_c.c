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
/*      IMG_sobel_3x3_16s - sobel 3x3 for 16bit signed input.               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_sobel_3x3_16s                                              */
/*      (                                                                   */
/*          const short *restrict  in,  // Input image data  //             */
/*                short *restrict  out, // Output image data //             */
/*                short           cols, // Image columns     //             */
/*                short           rows  // Image rows        //             */
/*      )                                                                   */
/*                                                                          */
/*      The sobel filter is applied to the input image.  The input image    */
/*      dimensions are given by the arguments 'cols' and 'rows'.  The       */
/*      output image is 'cols' pixels wide and 'rows - 2' pixels tall.      */
/*                                                                          */
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
/*      Also the first pixel in the first processed line and the            */
/*      last pixel in the last processed line will not be computed.         */
/*      It is not necessary, since the results would be bogus.              */
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
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. cols :     'cols' >  3 and multiple of 2.                        */
/*      2. rows :     'rows' >= 3 .                                         */
/*      3. Input and outpur arrays do not overlap.                          */
/*      4. Input and output arrays have no alignment requirements.          */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible with C64x+ processors only.                 */
/*                                                                          */
/*  SOURCE                                                                  */
/*      The algorithm is taken from sobel in IMGLIB                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_sobel_3x3_16s_cn,   ".text:ansi");


void IMG_sobel_3x3_16s_cn
(
    const short *restrict   in,  /* Input image data   */
          short *restrict  out,  /* Output image data  */
          short           cols,  /* image columns      */
          short           rows   /* Image rows         */
)
{    
    int    H,       O,       V;
    int    i;
    int    i00,     i01,     i02;
    int    i10,     i12;
    int    i20,     i21,     i22;

   

    /* -------------------------------------------------------------------- */
    /*  Iterate over entire image as a single, continuous raster line.      */
    /* -------------------------------------------------------------------- */
    
    for (i = 0; i < (cols * (rows - 2) - 2); i++)
    {
        /* ---------------------------------------------------------------- */
        /*  Read in the required 3x3 region from the input.                 */
        /* ---------------------------------------------------------------- */

        i00 =   in[i               ]; 
        i01 =   in[i            + 1]; 
        i02 =   in[i            + 2];
        i10 =   in[i +     cols    ];                  
        i12 =   in[i +     cols + 2];
        i20 =   in[i + 2 * cols    ]; 
        i21 =   in[i + 2 * cols + 1]; 
        i22 =   in[i + 2 * cols + 2];

        /* ---------------------------------------------------------------- */
        /*  Apply horizontal and vertical filter masks.  The final filter   */
        /*  output is the sum of the absolute values of these filters.      */
        /* ---------------------------------------------------------------- */

        H   =   - i00 - 2 * i01 -  i02
                + i20 + 2 * i21 +  i22;

        V   =   - i00      +     i02 
                - 2 * i10  + 2 * i12 
                - i20      +     i22;    

        O   =   abs(H) + abs(V);

        /* ---------------------------------------------------------------- */
        /*  Clamp to 16-bit range.  The output is always positive due to    */
        /*  the absolute value, so we only need to check for overflow.      */
        /* ---------------------------------------------------------------- */

        O   =   (O > 32767) ? 32767 : O;

        /* ---------------------------------------------------------------- */
        /*  Store it.                                                       */
        /* ---------------------------------------------------------------- */

        out[i + 1] = O;
    }
}

/* ======================================================================== */
/*  End of file:  IMG_sobel_3x3_16s_c.c                                     */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
