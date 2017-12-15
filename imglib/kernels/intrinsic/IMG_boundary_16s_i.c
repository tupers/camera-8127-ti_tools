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
/*      IMG_boundary_16s -- Returns coordinates of boundary pixels(16 bit). */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and is called as follows:               */
/*                                                                          */
/*          void IMG_boundary_16s                                           */
/*          (                                                               */
/*              const  short *restrict  i_data,                             */
/*                       int              rows,                             */
/*                       int              cols,                             */
/*              unsigned int *restrict o_coord,                             */
/*                     short *restrict  o_grey                              */
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
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. Rows should minimum of 1 and maximum of 32767.                   */
/*      2. Cols should be a multiple of 4 ,minimum of 4 and max of 32764.   */
/*      3. Input and output arrays should not overlap.                      */
/*      4. Input must be double word aligned.                               */
/*      5. Output arrays should be word alligned.                           */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      Outer and inner loops are merged.                                   */
/*      "Inner loop" is unrolled to process four pixels per iteration.      */
/*      Packed coordinate value is updated directly, rather than            */
/*      by repacking x, y every time it's needed.                           */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible with both c64x+ and c64x  processors        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_boundary_16s, ".text:intrinsic");


void IMG_boundary_16s 
(
    const  short *restrict  i_data,
             int              rows,
             int              cols,
    unsigned int *restrict o_coord,
           short *restrict  o_grey
) 
{
    int     i,      x,         ph;
    int     pl;
    int     c0,     c1,        c2;
    int     c3,     r_step;

    short   p0,     p1,        p2;
    short   p3;

    long long     p;
    long long     * in_ptr = (long long *)i_data;

    _nassert(cols % 4 == 0);        /* cols must be a multiple of 4       */
    _nassert(cols >= 4);            /* cols must be atleast 4             */
    _nassert(cols <= 32764);        /* cols must not be more than 32764   */
    _nassert(rows <= 32767);        /* rows must not be more than 32764   */
    _nassert((int)i_data % 8 == 0); /* i_data must be double word aligned */
   

    /* ------------------------------------------------------------------ */ 
    /* r_step is the value to be added to incriment the row value         */
    /* (i.e higher 16bits of o_coord) after every "cols" number of        */
    /* pixels and make lower 16bits(cols) zero at start of every row      */ 
    /* ------------------------------------------------------------------ */
    r_step = 0x10000 - cols;


    #pragma MUST_ITERATE(1,,1);

    for (i = x = c0 = 0; i < rows * cols; i += 4, x += 4)
    {
        /* ------------------------------------------------------------- */
        /* Add r_step at start of new row to incriment "row" part        */
        /*(i.e higher 16 bit of o_coord) and make "cols" zero            */
        /* eg: after 1st row c0=cols, and c0+ = r_step --> 0x00010000    */
        /* ------------------------------------------------------------- */
        if (x == cols) { x = 0; c0 += r_step; }

        p  = _amem8_const(in_ptr++);

        ph = _hill(p);
        pl = _loll(p);
        p0 = (pl      ) ;
        p1 = (pl >> 16) ;
        p2 = (ph      ) ;
        p3 = (ph >> 16) ;
  
        c1 = c0 + 1;
        c2 = c0 + 2;
        c3 = c0 + 3;

        if (p0) 
        {
           *o_coord++ = c0;
           *o_grey++  = p0;
        }
        if (p1) 
        {  
           *o_coord++ = c1;
           *o_grey++  = p1;
        }
        if (p2) 
        { 
           *o_coord++ = c2;
           *o_grey++  = p2;
        }
        if (p3) 
        { 
           *o_coord++ = c3;
           *o_grey++  = p3;
        }

        c0 += 4;/* incriment the "cols" part by 4 */
    }
}

/* ======================================================================== */
/*  End of file:  IMG_boundary_16s_i.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
