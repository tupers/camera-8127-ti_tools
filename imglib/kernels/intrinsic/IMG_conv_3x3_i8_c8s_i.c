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
/*   USAGE                                                                  */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*      void IMG_conv_3x3_i8_c8s(const unsigned char *restrict inptr,       */
/*                                 unsigned char *restrict outptr,          */
/*                                          int            x_dim,           */
/*                           const          char *restrict mask,            */
/*                                          int            shift)           */
/*                                                                          */
/*     The convolution routine accepts three rows of 'x_dim' input points   */
/*     and performs some operation on each.  A total of 'x_dim' outputs     */
/*     are written to the output array. The 'mask' array has the 3 by 3     */
/*     array of coefficients.                                               */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*     The convolution kernel accepts three rows of 'x_dim' input points    */
/*     and produces one output row of 'x_dim' points using the input mask   */
/*     of 3 by 3. The user defined shift value is used to shift the convo-  */
/*     lution value, down to the byte range. The convolution sum is also    */
/*     range limited to 0..255. The shift amount is non-zero for low pass   */
/*     filters, and zero for high pass and sharpening filters.              */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*   ASSUMPTIONS                                                            */
/*        x_dim must be a multiple of 8.                                    */
/*                                                                          */
/*                                                                          */
/*    TECHNIQUES                                                            */
/*     The inner loop that computes the convolution sum is completely       */
/*     unrolled and 8 output pixels are computed together. The mask         */
/*     values are loaded and packed as double words.                        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#pragma CODE_SECTION(IMG_conv_3x3_i8_c8s, ".text:intrinsic");

#include "IMG_conv_3x3_i8_c8s.h"
/* ======================================================================== */
/*  IMG_conv_3x3_i8_c8s  -- Optimized C with Intrinsics.                    */
/* ======================================================================== */

void IMG_conv_3x3_i8_c8s (const unsigned char *restrict inptr,
                                unsigned char *restrict outptr,
                                         int            x_dim,
                          const          char *restrict mask,
                                         int            shift)
{
    /*----------------------------------------------------------------------*/
    /* count is a variable for the number of output pixels. IN1, IN2 and    */
    /* IN3 are input pointers to three adjacent lines of image data. OUT    */
    /* is a pointer to output data.                                         */
    /*----------------------------------------------------------------------*/

    int                      j, count;
    const   unsigned char   *IN1,    *IN2,    *IN3;
    unsigned int            *OUT;

    /*----------------------------------------------------------------------*/
    /* maskA_B : A is row no., B is starting column no.                     */
    /*----------------------------------------------------------------------*/

    unsigned int  mask1_0, mask2_0, mask3_0;
    unsigned int  mask1_1, mask2_1, mask3_1;

    /*----------------------------------------------------------------------*/
    /* Other variables.                                                     */
    /*----------------------------------------------------------------------*/
    double r1_76543210, r2_76543210, r3_76543210;
    unsigned int r1_7654, r1_3210;
    unsigned int r2_7654, r2_3210;
    unsigned int r3_7654, r3_3210;
    unsigned int r1_5432, r2_5432, r3_5432;

    int           sum0, sum1, sum2, sum3;
    unsigned int  sum32, sum10, sum3210;

    /*----------------------------------------------------------------------*/
    /*  Read mask values and prepare registers for convolution              */
    /*----------------------------------------------------------------------*/
    mask1_0 = _extu( _mem4_const(&mask[0]), 8, 8);
    mask2_0 = _extu( _mem4_const(&mask[3]), 8, 8);
    mask3_0 = _extu( _mem4_const(&mask[6]), 8, 8);

    mask1_1 = mask1_0 << 8;
    mask2_1 = mask2_0 << 8;
    mask3_1 = mask3_0 << 8;

    /*-----------------------------------------------------------------------*/
    /* Set loop counter for output pixels and three input pointers x_dim     */
    /* apart from the user passed input pointer. Copy output pointer         */
    /*-----------------------------------------------------------------------*/

    count   =   x_dim >> 2 ;

    IN1     =   inptr;
    IN2     =   IN1+ x_dim;
    IN3     =   IN2+ x_dim;
    OUT     =   (unsigned int *)outptr;

    /*----------------------------------------------------------------------*/
    /* In order to minimize data loads, dat re-use is achieved by moves.    */
    /* The data to be used for pix10, pix11 are pre-loaded into pix12 and   */
    /* pix13 and moved within the loop. The process is repeated for rows 2  */
    /* and 3 for pix20, pix21 and pix30 and pix31 respectively.             */
    /*----------------------------------------------------------------------*/

    for( j = 0; j < count; j++)
    {

        r1_76543210 = _memd8_const(IN1);
        r2_76543210 = _memd8_const(IN2);
        r3_76543210 = _memd8_const(IN3);
        IN1 += 4;
        IN2 += 4;
        IN3 += 4;

        r1_3210 = _lo(r1_76543210);
        r2_3210 = _lo(r2_76543210);
        r3_3210 = _lo(r3_76543210);
        r1_7654 = _hi(r1_76543210);
        r2_7654 = _hi(r2_76543210);
        r3_7654 = _hi(r3_76543210);

        sum0 = (_dotpsu4(mask1_0, r1_3210) + _dotpsu4(mask2_0, r2_3210)
                + _dotpsu4(mask3_0, r3_3210) ) >> shift;


        sum1 = (_dotpsu4(mask1_1, r1_3210) + _dotpsu4(mask2_1, r2_3210)
                + _dotpsu4(mask3_1, r3_3210) ) >> shift;

        sum10 = _spack2(sum1, sum0);

        r1_5432 = _packlh2(r1_7654, r1_3210);
        r2_5432 = _packlh2(r2_7654, r2_3210);
        r3_5432 = _packlh2(r3_7654, r3_3210);

        sum2 = (_dotpsu4(mask1_0, r1_5432) + _dotpsu4(mask2_0, r2_5432)
                + _dotpsu4(mask3_0, r3_5432) ) >> shift;


        sum3 = (_dotpsu4(mask1_1, r1_5432) + _dotpsu4(mask2_1, r2_5432)
                + _dotpsu4(mask3_1, r3_5432) ) >> shift;

        sum32 = _spack2(sum3, sum2);

        sum3210 = _spacku4(sum32, sum10);

        _mem4(OUT) = sum3210;
        OUT++;
    }
}

/* ======================================================================== */
/*  End of file: IMG_conv_3x3_i8_c8s_i.c                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
