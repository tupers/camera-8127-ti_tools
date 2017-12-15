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
2, 2,

/* Function parameters : 1 */
/* cols, rows, in_size, out_size*/
4, 3, 12, 2,

/* Image data : 1 */
 5922, 10834, 20433, -17341,
 -18128, -30429, 3054, -10155,
 -3095, 30451, 5556, -13139,

/* Function parameters : 2 */
/* cols, rows, in_size, out_size*/
24, 3, 72, 22,

/* Image data : 2 */
 -31820, -31255, 12885, -9480, 16604, 8637, 107, -3893, -19117, 22667, 26488, 19279, -16864, -6379, 1821, 7653, -5543, 32756, -11470, 2343, 21630, -3205, -20263, 7654,
 -31140, -24757, -32103, -18818, 8557, 2422, 24583, -30362, 21185, 5429, -261, 12465, 6892, -197, 734, -30471, 25363, -30004, 26017, -7789, 5187, -4209, 24657, -10506,
 8651, 3822, 1688, 6739, -27685, 5740, 22004, -25709, -7688, 26798, -3329, -21978, -31959, -28652, 21135, -32349, 30861, 19149, 16069, 31371, 11557, -24399, 22422, -16624,

/* Function parameters : 3 */
/* cols, rows, in_size, out_size*/
20, 3, 60, 18,

/* Image data : 3 */
 -3210, -2416, 957, -1332, 3094, -3189, -2049, 2358, 3551, 2050, 2966, -2597, 4087, 2975, -1951, 3256, 76, 2243, -3787, 1720,
 -1622, -1631, 2070, 313, 1547, -1856, -2533, -2195, 2061, -413, -1177, 1041, 2965, 427, 504, 1968, 3590, -2473, 204, -2840,
 -259, -1801, 3662, 1906, 2763, -3861, -1254, -197, 1305, 828, 1397, 2189, -3498, -2803, -1147, -2242, -1909, -3602, 42, 2666,

/* Function parameters : 4 */
/* cols, rows, in_size, out_size*/
8, 3, 24, 6,

/* Image data : 4 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* Function parameters : 5 */
/* cols, rows, in_size, out_size*/
28, 3, 84, 26,

/* Image data : 5 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
};

int testcases = 5;