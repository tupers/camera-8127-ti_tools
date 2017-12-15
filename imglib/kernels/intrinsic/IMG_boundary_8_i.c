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
/*  NAME                                                                    */
/*      IMG_boundary_8 -- Returns coordinates of boundary pixels.           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and is called as follows:               */
/*                                                                          */
/*          void IMG_boundary_8                                             */
/*          (                                                               */
/*              const unsigned char *restrict i_data,                       */
/*              int rows, int cols,                                         */
/*              int *restrict o_coord,                                      */
/*              int *restrict o_grey                                        */
/*          );                                                              */
/*                                                                          */
/*      The arguments are defined as follows:                               */
/*                                                                          */
/*          i_data   Input images that is cols-by-rows in size.             */
/*          rows     Height of the input image                              */
/*          cols     Width of the input image                               */
/*          o_coord  Array to write output coordinates to                   */
/*          o_grey   Array to write output grey levels to                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine scans an image looking for non-zero pixels.            */
/*      The locations of those pixels are stored out to the o_coord         */
/*      as packed Y/X pairs, with Y in the upper half, and X in             */
/*      the lower half.  The grey levels encountered are stored             */
/*      in the o_grey array in parallel.                                    */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      At least one row is being processed.                                */
/*      Input is word aligned.                                              */
/*      Input is a multiple of 4 pixels wide.                               */
/*      Output buffers o_coord and o_grey start in different banks          */
/*      and are word-aligned.                                               */
/*      No more than 32764 rows or 32764 columns are being processed.       */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      Outer and inner loops are collapsed together.                       */
/*      Inner loop is unrolled to process four pixels per iteration.        */
/*      Packed coordinate value is updated directly, rather than            */
/*      by repacking x, y every time it's needed.                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



#pragma CODE_SECTION(IMG_boundary_8, ".text:intrinsic");

void IMG_boundary_8
(
    const unsigned char *restrict i_data, 
    int rows, int cols, 
    int *restrict o_coord, 
    int *restrict o_grey
) 
{
    int i, x, p, p0, p1, p2, p3;
    int c0, c1, c2, c3, r_step;

    _nassert(cols % 4 == 0);
    _nassert(cols >= 16);
    _nassert(cols <= 32764);
    _nassert(rows <= 32764);
    _nassert((int)i_data % 8 == 0);
    _nassert((int)o_coord % 8 != (int)o_grey % 8);

    r_step = 0x10000 - cols;
#   pragma MUST_ITERATE(1, 32764/4*32764, 1);
    for (i = x = c0 = 0; i < rows*cols; i += 4, x += 4)
    {
        if (x == cols) { x = 0; c0 += r_step; }

        p  = _amem4_const(&i_data[i]);

        p0 = (p      ) & 0xFF;
        p1 = (p >>  8) & 0xFF;
        p2 = (p >> 16) & 0xFF;
        p3 = (p >> 24) & 0xFF;
  
        c1 = c0 + 1;
        c2 = c0 + 2;
        c3 = c0 + 3;

        if (p0) { *o_coord++ = c0; *o_grey++ = p0; }
        if (p1) { *o_coord++ = c1; *o_grey++ = p1; }
        if (p2) { *o_coord++ = c2; *o_grey++ = p2; }
        if (p3) { *o_coord++ = c3; *o_grey++ = p3; }

        c0 += 4;
    }
}

/* ======================================================================== */
/*  End of file:  IMG_boundary_8_i.c                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
