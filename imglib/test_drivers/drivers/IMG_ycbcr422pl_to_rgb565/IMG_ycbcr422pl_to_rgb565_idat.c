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
 * y align, croma align, dst align, coeff align*/
0, 4, 0, 0,

/* Function parameters : 1 */
/* num_pix */
16,

/* Coefficients : 1 */
 8192, 11229, -2757, -5720, 14192,

/* Input data Y : 1 */
 151, 193, 170, 161, 208, 20, 60, 162, 16, 137, 16, 150, 178, 128, 91, 224,

/* Input data Cb: 1 */
 57, 16, 140, 88, 16, 31, 16, 54,

/* Input data Cr: 1 */
 116, 240, 150, 77, 162, 143, 135, 154,

/* Function parameters : 2 */
/* num_pix */
64,

/* Coefficients : 2 */
 8192, 11229, -2757, -5720, 14192,

/* Input data Y : 2 */
 214, 92, 28, 230, 98, 190, 233, 58, 115, 130, 42, 235, 16, 68, 16, 198, 211, 51, 16, 16, 235, 16, 203, 134, 191, 129, 235, 182, 173, 39, 33, 211, 216, 46, 63, 138, 120, 27, 72, 102, 235, 126, 188, 16, 214, 235, 16, 81, 89, 226, 122, 16, 169, 109, 154, 124, 172, 117, 196, 235, 19, 218, 40, 88,

/* Input data Cb: 2 */
 113, 53, 217, 231, 203, 62, 103, 135, 158, 106, 240, 83, 137, 212, 115, 49, 158, 28, 53, 158, 86, 225, 28, 64, 202, 239, 192, 221, 47, 240, 221, 67,

/* Input data Cr: 2 */
 16, 211, 149, 127, 177, 155, 127, 131, 16, 227, 16, 230, 98, 148, 112, 224, 87, 77, 77, 193, 138, 176, 70, 49, 59, 192, 115, 91, 161, 221, 141, 144,
};

int testcases = 2;
