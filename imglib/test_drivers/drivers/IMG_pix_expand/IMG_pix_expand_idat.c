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

/* ========================================================================= *
 * Copyright 2007, Texas Instruments, Inc.  All rights reserved. 
 * ========================================================================= */

int in_data[] = {
/* Alignment data.
 * 0 = double word, 4 = word, 2 = half word, 1 = byte alignment respectively.
 * src align, dst align */
0, 0,

/* Function parameters : 1 */
/* dat_size (in, out) */
16,

/* Input data : 1 */
 0, 0, 0, 1, 1, 1, 1, 10, 10, 10, 255, 255, 255, 255, 255, 255,

/* Function parameters : 2 */
/* dat_size (in, out) */
48,

/* Input data : 2 */
 151, 57, 116, 170, 9, 247, 208, 140, 150, 60, 88, 77, 4, 6, 162, 6, 31, 143, 178, 3, 135, 91, 54, 154, 193, 161, 20, 162, 137, 150, 128, 224, 214, 113, 9, 28, 53, 211, 98, 217, 149, 233, 231, 127, 115, 203, 177, 42,
};

int testcases = 2;
