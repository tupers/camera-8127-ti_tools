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
 * src align, mask align, dst align */
0, 0, 0,

/* Function parameters : 1 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
4, 2, 2, 10, 1, 11,

/* Image data : 1 */
 -6191, 21669, -60857, 60902,

/* mask : 1 */
 5922, -18128,

/* Function parameters : 2 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
10, 8, 2, 20, 15, 10,

/* Image data : 2 */
 283467726, -1024150215, -811224397, 125242828, 422227733, -1051953208, 55307299, -310653262, -616620174, 220824408,

/* mask : 2 */
 20433, 3054, 5556, -17341, -10155, -13139, -31820, -31140,

/* Function parameters : 3 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
20, 6, 14, 31, 0, 10,

/* Image data : 3 */
 6995607, 1611049912, 1442032802, -255153635, -1989784034, -1684891548, -1252861088, 1388353274, -503848991, 1485512032, 355824995, 1756217718, 1735925252, -17134585, -218161397, 1263469698, 816895943, -1440324918, -1105211036, 451681305,

/* mask : 3 */
 16604, 8557, -27685, 8637, 2422, 5740,

/* Function parameters : 4 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
30, 10, 20, 32, 3, 32,

/* Image data : 4 */
 -22173, 101452, 123445, 131026, -120017, 76596, -45881, 104069, 64277, 9372, -31156, 125486, 86520, 20747, 46230, -12822, -16835, -97597, -81053, 98627, 89686, 30615, -42023, -66497, -102711, -51893, -8287, -77303, -52192, -57630,

/* mask : 4 */
 -31959, -6379, -197, -28652, 1821, 734, 21135, 7653, -30471, -32349,

/* Function parameters : 5 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
40, 4, 36, 1, 16, 15,

/* Image data : 5 */
 10017, 60991, 98999, 49511, 88415, -102057, -59402, -123566, -65576, -81046, -40127, 75440, -70235, -6310, 113646, 65948, 41774, 65586, -13225, 26490, 94923, -37665, 44697, -83116, 33320, 70055, 130789, 94887, -111952, 95191, 13674, -89688, -62419, 16125, -36710, 104194, 62978, -71747, 2424, 114886,

/* mask : 5 */
 7659, 16558, 29299, -10653,

/* Function parameters : 6 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
32, 2, 30, 0, 0, 0,

/* Image data : 6 */
 -39566, -57628, -60588, 3268, 665, 27519, -45432, 42656, -41956, 5011, -51932, -13164, -885, -62058, 56765, -23853, 50376, -63606, -9647, -2090, -5728, 59826, 46221, -20578, 52731, -59963, 20183, -322, -43095, 2753, 5404, -8844,

/* mask : 6 */
 -15273, 17947,

/* Function parameters : 7 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
26, 12, 14, 2, 2, 0,

/* Image data : 7 */
 209943, 56227, 234459, -2888, 226009, 66440, -74548, 122006, 61100, -172256, 18741, -120775, 172115, 244012, 121669, 161876, 115659, -186601, 85569, 39644, -67187, 107231, 247631, 128683, 85407, -59344,

/* mask : 7 */
 -2927, 27898, -32690, 30248, 22091, 26878, 3449, -32103, 4696, 12644, -27363, -24432,

/* Function parameters : 8 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
32, 16, 16, 15, 10, 5,

/* Image data : 8 */
 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647,

/* mask : 8 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* Function parameters : 9 */
/* width, k_size, out_size, x_qp, h_qp, y_qp */
30, 14, 16, 15, 10, 6,

/* Image data : 9 */
 -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648,

/* mask : 9 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
};

int testcases = 9;
