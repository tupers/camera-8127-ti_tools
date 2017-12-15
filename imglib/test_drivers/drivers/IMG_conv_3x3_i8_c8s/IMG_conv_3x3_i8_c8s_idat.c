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
/* Test data for kernel size : 3 x 3 
 * kernel size */
 3,
/* Alignment data.
 * 0 = double word, 4 = word, 2 = half word, 1 = byte alignment respectively.
 * src align, mask align, dst align */
1, 1, 4,

/* Function parameters : 1 */
/* width, shift, in_size, out_size*/
8, 4, 26, 8,

/* Image data : 1 */
 151, 170, 208, 60, 4, 6, 178, 91,
 57, 9, 140, 88, 6, 31, 3, 54,
 116, 247, 150, 77, 162, 143, 135, 154,
 151, 170,

/* mask : 1 */
 -3, -2, -1,
 0, 1, 2,
 3, 4, 5,

/* Function parameters : 2 */
/* width, shift, in_size, out_size*/
16, 12, 50, 16,

/* Image data : 2 */
 113, 53, 217, 231, 203, 62, 103, 135, 158, 106, 255, 83, 137, 212, 115, 49,
 9, 211, 149, 127, 177, 155, 127, 131, 9, 227, 11, 230, 98, 148, 112, 224,
 28, 98, 233, 115, 42, 3, 16, 211, 2, 249, 203, 191, 251, 173, 33, 216,
 113, 53,

/* mask : 2 */
 96, 81, 10,
 81, 69, 75,
 64, 112, 107,

/* Function parameters : 3 */
/* width, shift, in_size, out_size*/
24, 16, 74, 24,

/* Image data : 3 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255,

/* mask : 3 */
 127, -128, -128,
 -128, -128, -62,
 -128, 127, -128,

/* Function parameters : 4 */
/* width, shift, in_size, out_size*/
8, 16, 26, 8,

/* Image data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0,

/* mask : 4 */
 127, -128, -128,
 -128, -128, -62,
 -128, 127, -128,

/* Function parameters : 5 */
/* width, shift, in_size, out_size*/
16, 16, 50, 16,

/* Image data : 5 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255,

/* mask : 5 */
 127, 127, 127,
 127, 127, 127,
 127, 127, 127,

/* Function parameters : 6 */
/* width, shift, in_size, out_size*/
16, 16, 50, 16,

/* Image data : 6 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255,

/* mask : 6 */
 127, 127, 127,
 127, 127, 127,
 127, 127, 127,

/* Function parameters : 7 */
/* width, shift, in_size, out_size*/
24, 11, 74, 24,

/* Image data : 7 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255,

/* mask : 7 */
 127, 127, 127,
 127, 127, 127,
 127, 127, 127,

/* Function parameters : 8 */
/* width, shift, in_size, out_size*/
16, 16, 50, 16,

/* Image data : 8 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255,

/* mask : 8 */
 -128, -128, -128,
 -128, -128, -128,
 -128, -128, -128,
};

int testcases = 8;
