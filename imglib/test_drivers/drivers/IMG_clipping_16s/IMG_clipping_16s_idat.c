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
/* cols, rows, threshold_max, threshold_min, dat_size (in, out) */
4, 2, 24575, -8192, 8,

/* Input data : 1 */
 5922, -18128, -3095, 10834, -30429, 30451, 20433, 3054,

/* Function parameters : 2 */
/* cols, rows, threshold_max, threshold_min, dat_size (in, out) */
12, 2, 22937, -13107, 24,

/* Input data : 2 */
 5556, -17341, -10155, -13139, -31820, -31140, 8651, -31255, -24757, 3822, 12885, -32103, 1688, -9480, -18818, 6739, 16604, 8557, -27685, 8637, 2422, 5740, 107, 24583,

/* Function parameters : 3 */
/* cols, rows, threshold_max, threshold_min, dat_size (in, out) */
8, 7, 100, 100, 56,

/* Input data : 3 */
 22004, -3893, -30362, -25709, -19117, 21185, -7688, 22667, 5429, 26798, 26488, -261, -3329, 19279, 12465, -21978, -16864, 6892, -31959, -6379, -197, -28652, 1821, 734, 21135, 7653, -30471, -32349, -5543, 25363, 30861, 32756, -30004, 19149, -11470, 26017, 16069, 2343, -7789, 31371, 21630, 5187, 11557, -3205, -4209, -24399, -20263, 24657, 22422, 7654, -10506, -16624, -25678, -12973, -2072, -19326,

/* Function parameters : 4 */
/* cols, rows, threshold_max, threshold_min, dat_size (in, out) */
4, 12, 1, 1, 48,

/* Input data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 5 */
/* cols, rows, threshold_max, threshold_min, dat_size (in, out) */
4, 10, 14, 9, 40,

/* Input data : 5 */
 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,

/* Function parameters : 6 */
/* cols, rows, threshold_max, threshold_min, dat_size (in, out) */
8, 6, 23, 13, 48,

/* Input data : 6 */
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
};

int testcases = 6;
