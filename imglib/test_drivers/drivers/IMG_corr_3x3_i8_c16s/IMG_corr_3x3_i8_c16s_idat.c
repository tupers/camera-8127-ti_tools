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
1, 2, 0,

/* Function parameters : 1 */
/* width, pitch, in_size, out_size*/
2, 4, 12, 2,

/* Image data : 1 */
 151, 170, 208, 60,
 57, 9, 140, 88,
 116, 247, 150, 77,

/* mask : 1 */
 -50, -49, -48,
 -47, -46, -45,
 -44, -43, -42,

/* Function parameters : 2 */
/* width, pitch, in_size, out_size*/
30, 32, 96, 30,

/* Image data : 2 */
 91, 193, 162, 128, 113, 53, 217, 231, 203, 62, 103, 135, 158, 106, 255, 83, 137, 212, 115, 49, 158, 28, 53, 158, 86, 225, 28, 64, 202, 239, 192, 221,
 54, 161, 137, 224, 9, 211, 149, 127, 177, 155, 127, 131, 9, 227, 11, 230, 98, 148, 112, 224, 87, 77, 77, 193, 138, 176, 70, 49, 59, 192, 115, 91,
 154, 20, 150, 214, 28, 98, 233, 115, 42, 3, 16, 211, 2, 249, 203, 191, 251, 173, 33, 216, 63, 120, 72, 242, 188, 214, 7, 89, 122, 169, 154, 172,

/* mask : 2 */
 -31820, -31140, 8651,
 -31255, -24757, 3822,
 12885, -32103, 1688,

/* Function parameters : 3 */
/* width, pitch, in_size, out_size*/
10, 12, 36, 10,

/* Image data : 3 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 3 */
 -20779, 8330, 17514,
 32697, 23722, -27988,
 23798, 3418, -22422,

/* Function parameters : 4 */
/* width, pitch, in_size, out_size*/
8, 10, 30, 8,

/* Image data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* mask : 4 */
 -20779, 8330, 17514,
 32697, 23722, -27988,
 23798, 3418, -22422,

/* Function parameters : 5 */
/* width, pitch, in_size, out_size*/
30, 32, 96, 30,

/* Image data : 5 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 5 */
 32767, 32767, 32767,
 32767, 32767, 32767,
 32767, 32767, 32767,

/* Function parameters : 6 */
/* width, pitch, in_size, out_size*/
4, 6, 18, 4,

/* Image data : 6 */
 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255,

/* mask : 6 */
 -32768, -32768, -32768,
 -32768, -32768, -32768,
 -32768, -32768, -32768,
};

int testcases = 6;
