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
1, 1, 0,

/* Function parameters : 1 */
/* width, shift, round const, in_size, out_size*/
6, 7, 64, 18, 4,

/* Image data : 1 */
 151, 170, 208, 60, 4, 6,
 57, 9, 140, 88, 6, 31,
 116, 247, 150, 77, 162, 143,

/* mask : 1 */
 5, 6, 7,
 8, 9, 10,
 11, 12, 13,

/* Function parameters : 2 */
/* width, shift, round const, in_size, out_size*/
22, 5, 0, 66, 20,

/* Image data : 2 */
 40, 32, 28, 13, 54, 58, 51, 16, 26, 34, 39, 27, 64, 21, 34, 53, 29, 12, 39, 7, 13, 39,
 34, 56, 2, 53, 37, 32, 44, 39, 32, 33, 2, 57, 3, 57, 24, 37, 28, 56, 22, 19, 19, 48,
 38, 53, 7, 24, 58, 29, 11, 1, 4, 53, 0, 62, 51, 48, 63, 43, 8, 54, 16, 30, 18, 61,

/* mask : 2 */
 22, 0, 17,
 11, 7, 19,
 24, 20, 2,

/* Function parameters : 3 */
/* width, shift, round const, in_size, out_size*/
10, 5, 16, 30, 8,

/* Image data : 3 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 3 */
 0, 0, 32,
 74, 0, 255,
 255, 0, 84,

/* Function parameters : 4 */
/* width, shift, round const, in_size, out_size*/
14, 5, 0, 42, 12,

/* Image data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* mask : 4 */
 0, 0, 32,
 74, 0, 255,
 255, 0, 84,

/* Function parameters : 5 */
/* width, shift, round const, in_size, out_size*/
22, 5, 16, 66, 20,

/* Image data : 5 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 5 */
 255, 255, 255,
 255, 255, 255,
 255, 255, 255,

/* Function parameters : 6 */
/* width, shift, round const, in_size, out_size*/
6, 5, 0, 18, 4,

/* Image data : 6 */
 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255,

/* mask : 6 */
 255, 255, 255,
 255, 255, 255,
 255, 255, 255,

/* Function parameters : 7 */
/* width, shift, round const, in_size, out_size*/
18, 5, 16, 54, 16,

/* Image data : 7 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 7 */
 255, 255, 255,
 255, 255, 255,
 255, 255, 255,
};

int testcases = 7;
