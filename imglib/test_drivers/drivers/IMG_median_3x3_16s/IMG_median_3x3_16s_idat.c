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
/* cols, in_size, out_size */
4, 12, 4,

/* Input data : 1 */
 5922, 10834, 20433, -17341,
 -18128, -30429, 3054, -10155,
 -3095, 30451, 5556, -13139,

/* Function parameters : 2 */
/* cols, in_size, out_size */
28, 84, 28,

/* Input data : 2 */
 -31820, -31255, 12885, -9480, 16604, 8637, 107, -3893, -19117, 22667, 26488, 19279, -16864, -6379, 1821, 7653, -5543, 32756, -11470, 2343, 21630, -3205, -20263, 7654, -25678, -19326, 7659, -10653,
 -31140, -24757, -32103, -18818, 8557, 2422, 24583, -30362, 21185, 5429, -261, 12465, 6892, -197, 734, -30471, 25363, -30004, 26017, -7789, 5187, -4209, 24657, -10506, -12973, -13048, 16558, 2504,
 8651, 3822, 1688, 6739, -27685, 5740, 22004, -25709, -7688, 26798, -3329, -21978, -31959, -28652, 21135, -32349, 30861, 19149, 16069, 31371, 11557, -24399, 22422, -16624, -2072, -14408, 29299, 15248,

/* Function parameters : 3 */
/* cols, in_size, out_size */
12, 36, 12,

/* Input data : 3 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,

/* Function parameters : 4 */
/* cols, in_size, out_size */
24, 72, 24,

/* Input data : 4 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
};

int testcases = 4;
