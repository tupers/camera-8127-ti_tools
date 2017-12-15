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
 * 0 = dooble word, 4 = word, 2 = half word, 1 = byte alignment respectively.
 * src align, dst align */
0, 4,

/* Function parameters : 1 */
/* rows, cols, in_size, out_size*/
1, 4, 4, 4,

/* Input data.*/
 5922, -18128, -3095, 10834,

/* Function parameters : 2 */
/* rows, cols, in_size, out_size*/
2, 4, 8, 0,

/* Input data.*/
 0, 0, 0, 0,
 0, 0, 0, 0,

/* Function parameters : 3 */
/* rows, cols, in_size, out_size*/
4, 8, 32, 13,

/* Input data.*/
 0, -15273, 28382, 0, 7482, 0, -9416, 0,
 0, 0, -13856, -4431, 0, 0, -6582, 0,
 16487, 0, 0, 0, -19783, 0, 0, -12034,
 -11927, 0, -30294, 10443, 0, 0, 0, 0,

/* Function parameters : 4 */
/* rows, cols, in_size, out_size*/
20, 20, 400, 14,

/* Input data.*/
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -22797, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, -4562, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, -14006, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, -18164, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25877, 0, 0, 16681, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -13584, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -31365, 0,
 0, 0, 0, 0, 6164, 0, 0, 0, 0, 0, 0, 0, 5908, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, -13639, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, -25289, 0, 0, 0, 0, 0, 0, 0, 0, -10549, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 16347, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 5 */
/* rows, cols, in_size, out_size*/
7, 4, 28, 12,

/* Input data.*/
 0, 0, -21421, 0,
 0, 0, 16575, 0,
 -14266, 29084, -27750, 24593,
 25238, -45853, 12981, 0,
 0, 0, 28438, 0,
 10386, 0, 28144, 0,
 0, 0, 0, 0,

/* Function parameters : 6 */
/* rows, cols, in_size, out_size*/
4, 12, 48, 1,

/* Input data.*/
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 15621, 0, 0, 0, 0, 0, 0, 0,
};

int testcases = 6;
