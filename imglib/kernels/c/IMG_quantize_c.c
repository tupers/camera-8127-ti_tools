
/* ######################################################################## */
/* #  TI Disclaimer: This kernel is obsolete. It is provided here for     # */
/* #  backward compatibility.                                             # */
/* ######################################################################## */

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
/*      IMG_quantize -- Matrix Quantization w/ Rounding, Little Endian      */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and has the following C prototype:      */
/*                                                                          */
/*      void IMG_quantize                                                   */
/*      (                                                                   */
/*          short           *data,      (* Data to be quantized.        *)  */
/*          unsigned short  num_blks,   (* Number of 64-element blocks. *)  */
/*          unsigned short  blk_sz,     (* Block size (multiple of 16). *)  */
/*          const short     *recip_tbl, (* Quant. values (reciprocals). *)  */
/*          int             q_pt        (* Q-point of Quant values.     *)  */
/*      )                                                                   */
/*                                                                          */
/*      The number of blocks, num_blks, must be at least 1.  The block      */
/*      size (number of elements in each block) must be at least 1.         */
/*      The Q-point, q_pt, controls rounding and final truncation; it       */
/*      must be in the range from 0 <= q_pt <= 31.                          */
/*                                                                          */
/*      The data[] array must be 'num_blks * blk_sz' elements, and the      */
/*      recip_tbl[] array must be 'blk_sz' elements.                        */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The function IMG_quantize() quantizes matrices by multiplying their */
/*      contents with a second matrix that contains reciprocals of the      */
/*      quantization terms.  This step corresponds to the quantization      */
/*      that is performed in 2-D DCT-based compression techniques,          */
/*      although IMG_quantize() may be used on any signed 16-bit data using */
/*      signed 16-bit quantization terms.                                   */
/*                                                                          */
/*      IMG_quantize() merely multiplies the contents of the quantization   */
/*      matrix with the data being quantized.  Therefore, it may be used    */
/*      for inverse quantization as well, by setting the Q-point            */
/*      appropriately.                                                      */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The inner loop steps through individual blocks, while the           */
/*      outer loop steps through reciprocals for quantization.  This        */
/*      eliminates redundant loads for the quantization terms.              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The number of blocks, num_blks, may be zero.                        */
/*      The Q-point, q_pt, must be in the range 0 <= q_pt <= 31.            */
/*                                                                          */
/*  NOTES                                                                   */
/*      No checking is performed on the input arguments for correctness.    */
/*                                                                          */
/*  SOURCE                                                                  */
/*      n/a                                                                 */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"
#include "IMG_quantize_c.h"

void IMG_quantize_cn
(
    short           *restrict data,      /* Data to be quantized.         */
    unsigned short  num_blks,            /* Number of 64-element blocks.  */
    unsigned short  blk_size,            /* Block size (multiple of 16).  */
    const short     *restrict recip_tbl, /* Quant. values (reciprocals).  */
    int             q_pt                 /* Q-point of Quant values.      */
)
{
    short recip;                /* Reciprocal term.                 */
    int   quot;                 /* Quotient (data * reciprocal)     */
    int   round;                /* Rounding value.                  */
    int   i, j, k;              /* Loop counters.                   */

    round = 1 << (q_pt - 1);

    if (!num_blks) return;

#ifndef NOASSUME
    _nassert((int) recip_tbl % 8 == 0);
    _nassert((int) data      % 8 == 0);
    #pragma MUST_ITERATE(32,,16);
#endif

    /* -------------------------------------------------------------------- */
    /*  Outer loop:  Step between quantization matrix elements.             */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < blk_size; i++)
    {
        /* ---------------------------------------------------------------- */
        /*  Load a reciprocal and point to appropriate element of block.    */
        /* ---------------------------------------------------------------- */
        recip   = recip_tbl[i];
        k       = i;

        /* ---------------------------------------------------------------- */
        /*  Inner loop:  Step between blocks of elements, quantizing.       */
        /* ---------------------------------------------------------------- */
#ifndef NOASSUME
        #pragma MUST_ITERATE(1,,1);
#endif
        for (j = 0; j < num_blks; j++)
        {
            quot    = data[k] * recip + round;
            data[k] = quot >> q_pt;
            k      += blk_size;
        }
    }
}

/* ======================================================================== */
/*  End of file:  IMG_quantize_c.c                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
