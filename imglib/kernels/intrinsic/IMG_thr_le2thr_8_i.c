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
/*      IMG_thr_le2thr_8                                                    */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*      void IMG_thr_le2thr_8                                               */
/*      (                                                                   */
/*          const unsigned char *in_data,     //  Input image data  //      */
/*          unsigned char *restrict out_data, //  Output image data //      */
/*          short cols, short rows,           //  Image dimensions  //      */
/*          unsigned char       threshold     //  Threshold value   //      */
/*      )                                                                   */
/*                                                                          */
/*      This routine performs a thresholding operation on an input          */
/*      image in in_data[] whose dimensions are given in the arguments      */
/*      'cols' and 'rows'.  The thresholded pixels are written to the       */
/*      output image pointed to by out_data[].  The input and output        */
/*      are exactly the same dimensions.                                    */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Pixels that are equal or above the threshold value are written to   */
/*      the output unmodified.  Pixels that are lesser than the threshold   */
/*      are set to the threshold value in the output image.                 */
/*                                                                          */
/*      The exact thresholding function performed is described by           */
/*      the following transfer function diagram:                            */
/*                                                                          */
/*                                                                          */
/*                 255_|                                                    */
/*                     |                  /                                 */
/*                     |                /                                   */
/*            O        |              /                                     */
/*            U        |            /                                       */
/*            T    th _|_________ /                                         */
/*            P        |         .                                          */
/*            U        |         .                                          */
/*            T        |         .                                          */
/*                     |         .                                          */
/*                   0_|_________.__________                                */
/*                     |         |        |                                 */
/*                     0        th       255                                */
/*                                                                          */
/*                             INPUT                                        */
/*                                                                          */
/*      Please see the IMGLIB functions IMG_thr_gt2thr, IMG_thr_le2min      */
/*      and IMG_thr_gt2max for other thresholding functions.                */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The input and output buffers do not alias.                          */
/*                                                                          */
/*      The input and output buffers must be double-word aligned.           */
/*                                                                          */
/*      The total number of pixels rows*cols must be at least               */
/*      16 and a multiple of 16.                                            */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The loop is manually unrolled 4x.  We ask the compiler to unroll    */
/*      the loop an additional factor of 4x, yielding a total unroll        */
/*      factor of 16x.  Packed-data processing techniques allow us to       */
/*      process all 4 pixels in parallel.                                   */
/*                                                                          */
/*      A single _amem4_const() intrinsic brings in four pixels,            */
/*      designated p0 thru p3.  These pixels are packed into the unsigned   */
/*      integer variable p3p2p1p0 as follows:                               */
/*                                                                          */
/*                            31  24   16    8    0                         */
/*                             +----+----+----+----+                        */
/*                    p3p2p1p0 | p3 | p2 | p1 | p0 |                        */
/*                             +----+----+----+----+                        */
/*                                                                          */
/*      (Note that this diagram assumes a little endian memory              */
/*      configuration, although this kernel works equally well in           */
/*      either endian mode.)                                                */
/*      We compare this packed word against a packed copy of the threshold  */
/*      value.  The packed threshold contains four copies of the threshold  */
/*      value, one in each byte, like so:                                   */
/*                                                                          */
/*                             31  24   16    8    0                        */
/*                              +----+----+----+----+                       */
/*                     thththth | th | th | th | th |                       */
/*                              +----+----+----+----+                       */
/*      We compare using _maxu4().  This instruction with select the larger */
/*      value between our input pixels and the threshold value.  The        */
/*      result is that input values below the threshold are clamped to the  */
/*      threshold value.                                                    */
/*                                                                          */
/*      The four pixels are then written with a single _amem4().            */
/*                                                                          */
/*      In this version of the code, we rely on the compiler to unroll      */
/*      the loop 4x (as noted above), and convert the _amem4_const() and    */
/*      _amem4() calls into _amemd8_const()/_amemd8() as part of its        */
/*      automatic optimizations.                                            */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      This code is ENDIAN NEUTRAL.                                        */
/*                                                                          */
/*      The input and output arrays must be double-word aligned.            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_thr_le2thr_8,   ".text:intrinsic");

void IMG_thr_le2thr_8
(
    const unsigned char *in_data,                /*  Input image data    */
    unsigned char       *restrict out_data,      /*  Output image data   */
    short cols, short rows,                      /*  Image dimensions    */
    unsigned char       threshold                /*  Threshold value     */
)
{
    int i, pixels = rows * cols;
    unsigned thththth;

    _nassert((int)in_data % 8 == 0);
    _nassert((int)out_data % 8 == 0);
    _nassert(pixels % 16 == 0);
    _nassert(pixels      >= 16);


    thththth = _pack2(threshold, threshold);
    thththth = _packl4(thththth, thththth);

    /* -------------------------------------------------------------------- */
    /*  Step through input image copying pixels to the output.  If the      */
    /*  pixels are below our threshold, set them to our threshold value.    */
    /* -------------------------------------------------------------------- */
    #pragma MUST_ITERATE(4,,4);
    #pragma UNROLL(4);
    for (i = 0; i < pixels; i += 4)
        _amem4(&out_data[i]) = _maxu4(_amem4_const(&in_data[i]), thththth);
}

/* ======================================================================== */
/*  End of file:  IMG_thr_le2thr_8_i.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
