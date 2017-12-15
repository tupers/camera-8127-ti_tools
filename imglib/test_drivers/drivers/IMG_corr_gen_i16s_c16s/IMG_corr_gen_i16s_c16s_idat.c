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
4, 2, 0,

/* Function parameters : 1 */
/* width, k_size, out_size*/
2, 1, 1,

/* Image data : 1 */
 5922, -18128,

/* mask : 1 */
 1,

/* Function parameters : 2 */
/* width, k_size, out_size*/
3, 1, 2,

/* Image data : 2 */
 -3095, 10834, -30429,

/* mask : 2 */
 1,

/* Function parameters : 3 */
/* width, k_size, out_size*/
13, 5, 8,

/* Image data : 3 */
 -40, -51, -124, -122, 34, -122, -97, 15, 50, -125, 7, -37, -74,

/* mask : 3 */
 119, 80, 12, 22, -68,

/* Function parameters : 4 */
/* width, k_size, out_size*/
15, 6, 9,

/* Image data : 4 */
 22, 0, 96, 86, -15, -119, -100, -75, 83, -30, 89, 21, 105, 103, -1,

/* mask : 4 */
 26, 65, 33, -108, 34, 9,

/* Function parameters : 5 */
/* width, k_size, out_size*/
21, 10, 11,

/* Image data : 5 */
 14, 6, 165, 60, -238, -253, -43, 198, 241, 256, -234, 150, -90, 203, 126, 18, -61, 245, 169, 41, 90,

/* mask : 5 */
 -7, 38, 24, -43, -33, 13, -62, -12, 0, -56,

/* Function parameters : 6 */
/* width, k_size, out_size*/
11, 10, 1,

/* Image data : 6 */
 -25, -4, -38, -25, -28, 15, 32, 57, -21, 5, 30,

/* mask : 6 */
 -25, -33, -191, -158, 193, 175, 60, -82, -130, -201,

/* Function parameters : 7 */
/* width, k_size, out_size*/
10, 9, 1,

/* Image data : 7 */
 37, -34, -3, 55, 32, 20, 32, -6, 13, 46,

/* mask : 7 */
 193, 97, 173, -199, -116, -241, -128, -158, -78,

/* Function parameters : 8 */
/* width, k_size, out_size*/
21, 9, 12,

/* Image data : 8 */
 7, -44, -30, 8, -18, 51, 31, -35, 1, 56, -30, 35, -39, -56, -59, 3, 1, 27, -44, 42, -41,

/* mask : 8 */
 -74, 87, -162, 65, 137, 255, 185, -219, 186,

/* Function parameters : 9 */
/* width, k_size, out_size*/
22, 5, 17,

/* Image data : 9 */
 111, -47, 98, -124, -19, -4, -11, 117, 90, -40, 103, -117, 39, -1, -84, 5, 11, -17, -11, 109, -128, 118,

/* mask : 9 */
 10, -101, -26, -2, -121,

/* Function parameters : 10 */
/* width, k_size, out_size*/
24, 4, 20,

/* Image data : 10 */
 18, 49, -107, -95, 103, 27, 114, -1, 110, 32, -36, 60, 30, -84, 9, -59, 84, 119, 59, 79, 56, -91, 42, 19,

/* mask : 10 */
 86, 105, 13, -125,

/* Function parameters : 11 */
/* width, k_size, out_size*/
18, 9, 9,

/* Image data : 11 */
 -54, 211, -114, 59, -150, -11, -76, -230, 32, 78, 91, 24, -245, -138, 164, 213, 78, -201,

/* mask : 11 */
 -16, 26, 60, 31, 21, -14, -47, 55, 3,

/* Function parameters : 12 */
/* width, k_size, out_size*/
28, 22, 6,

/* Image data : 12 */
 237, 244, -132, 145, -61, -73, 46, 48, -168, -103, -106, 127, -36, -24, -107, 130, -82, -198, -245, 155, -32, -178, -158, -199, 154, 207, 72, 128,

/* mask : 12 */
 -7, -23, 9, -6, 22, -8, 31, 18, -30, 15, -23, 24, -28, 18, 31, -23, -15, 31, 16, 17, -9, 16,
};

int testcases = 12;
