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
/*      IMG_conv_5x5_i8_c16s -> Natural C Implementation                    */
/*      5x5 convolution for 8-bit input, 16-bit masks and 8-bit output      */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_conv_5x5_i8_c16s                                       */
/*          (                                                               */
/*              const unsigned char  *restrict   imgin_ptr,                 */
/*                    unsigned char  *restrict  imgout_ptr,                 */
/*                             short                 width,                 */
/*                             short                 pitch,                 */
/*              const          short  *restrict    mask_ptr,                */
/*                             short                 shift                  */
/*          )                                                               */
/*                                                                          */
/*      imgin_ptr :   pointer to an input  array of 8 bit pixels            */
/*      imgout_ptr:   pointer to an output array of 8 bit pixels            */
/*      pitch     :   number of columns in the image                        */
/*      width     :   number of output pixels                               */
/*      mask_ptr  :   pointer to 16 bit filter mask.                        */
/*      shift     :   user specified shift amount                           */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The convolution kernel accepts five rows of 'pitch' input pixels    */
/*      and produces one row of 'width' output pixels using the input       */
/*      mask of 5 by 5. This convolution performs a point by point mult-    */
/*      iplication of 5 by 5 mask with the input image. The result of 25    */
/*      multiplications are then summed together to produce a 32-bit conv-  */
/*      olution intermediate sum. The user defined shift value is used to   */
/*      shift this convolution sum, down to the byte range and store in an  */
/*      output array. The result being stored is also range limited between */
/*      0 to 255 and will be saturated accordingly. The mask is moved one   */
/*      column at a time, advancing the mask over the entire image until    */
/*      the entire 'width' is covered. The masks are provided as 16-bit     */
/*      signed values. The input image pixels are provided as 8-bit uns-    */
/*      igned pixels and the output pixels will be in 8-bit unsigned.       */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. width:       'width' >= 2 and multiples of 2.                    */
/*      2. pitch:       'pitch' >= 'width'                                  */
/*      3. Filter Coefficient array should be half-word aligned             */
/*      4. Output array should be word-aligned.                             */
/*      5. No restrictions on the alignment of Input arrays                 */
/*      6. Input and Output arrays should not overlap.                      */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible for c64x+                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_conv_5x5_i8_c16s_cn,   ".text:ansi");


void IMG_conv_5x5_i8_c16s_cn
(
    const unsigned char *restrict  imgin_ptr,
          unsigned char *restrict imgout_ptr,
    short                              width,
    short                              pitch,
    const          short *restrict  mask_ptr,
    short                              shift
)
{
    int     i,      j,      k;
    int     sum;

    /*--------------------------------------------------------------------- */
    /* outer loop to calculate "width" pixel outputs                        */
    /*--------------------------------------------------------------------- */

    for (i = 0; i < width; i++)
    {

        sum = 0;

        /* ---------------------------------------------------------------- */
        /*  This loop computes the convolution corresponding to one output  */
        /* ---------------------------------------------------------------- */

        for (j = 0; j < 5; j++)
            for (k = 0; k < 5; k++)
                sum += imgin_ptr[j * pitch + i + k] * mask_ptr[j * 5 + k];

        sum >>= shift;
        sum   = (sum > 255) ? 255 :((sum < 0) ? 0 : sum);
          
        imgout_ptr[i] = (sum);
    }
}

/* ======================================================================== */
/*  End of file:  IMG_conv_5x5_i8_c16s_c.c                                  */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
