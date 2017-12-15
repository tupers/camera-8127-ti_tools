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
/* cols, rows, threshold, dat_size (in, out) */
16, 1, 200, 16,

/* Input data : 1 */
 151, 57, 116, 170, 9, 247, 208, 140, 150, 60, 88, 77, 4, 6, 162, 6,

/* Function parameters : 2 */
/* cols, rows, threshold, dat_size (in, out) */
32, 2, 205, 64,

/* Input data : 2 */
 31, 143, 178, 3, 135, 91, 54, 154, 193, 161, 20, 162, 137, 150, 128, 224, 214, 113, 9, 28, 53, 211, 98, 217, 149, 233, 231, 127, 115, 203, 177, 42, 62, 155, 3, 103, 127, 16, 135, 131, 211, 158, 9, 2, 106, 227, 249, 255, 11, 203, 83, 230, 191, 137, 98, 251, 212, 148, 173, 115, 112, 33, 49, 224,

/* Function parameters : 3 */
/* cols, rows, threshold, dat_size (in, out) */
8, 6, 0, 48,

/* Input data : 3 */
 216, 158, 87, 63, 28, 77, 120, 53, 77, 72, 158, 193, 242, 86, 138, 188, 225, 176, 214, 28, 70, 7, 64, 49, 89, 202, 59, 122, 239, 192, 169, 192, 115, 154, 221, 91, 172, 47, 161, 196, 255, 221, 19, 221, 141, 40, 67, 144,

/* Function parameters : 4 */
/* cols, rows, threshold, dat_size (in, out) */
4, 16, 1, 64,

/* Input data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 5 */
/* cols, rows, threshold, dat_size (in, out) */
8, 6, 10, 48,

/* Input data : 5 */
 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,

/* Function parameters : 6 */
/* cols, rows, threshold, dat_size (in, out) */
8, 8, 23, 64,

/* Input data : 6 */
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
};

int testcases = 6;
