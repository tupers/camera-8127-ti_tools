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
/* num_luma, in_size, y_size, cb_cr_size */
16, 32, 16, 8,

/* Input data : 1 */
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,

/* Function parameters : 2 */
/* num_luma, in_size, y_size, cb_cr_size */
64, 128, 64, 32,

/* Input data : 2 */

  /* r 1, c 1:100 */  19345, 7320, 14836, 21801, 1170, 31610, 26600, 17911, 19162, 7714, 11307, 9815, 474, 814, 20709, 757, 4006, 18295, 22827, 332, 17228, 11644, 6975, 19754, 24686, 20663, 2542, 20703, 17595, 19254, 16437, 28675, 27386, 14437, 1203, 3529, 6825, 26976, 12540, 27718, 19099, 29783, 29628, 16253, 14720, 26024, 22616, 5395, 7952, 19830, 404, 13194, 16286, 2058, 17295, 16751, 26951, 20210, 1148, 209, 13612, 29066, 31815, 32762, 1382, 25958, 10649, 29393, 24419, 17556, 12490, 32070, 27199, 18977, 22163, 14781, 14280, 4184, 6252, 28712, 27595, 20211, 11131, 8072, 3545, 9897, 15348, 6721, 9860, 9180, 20214, 24663, 31033, 11058, 17636, 24008, 28759, 22573, 27436, 3627,
  /* r 1, c 101:128 */  8959, 938, 8187, 6253, 11368, 25814, 7605, 15595, 30590, 24627, 21606, 24582, 14731, 19695, 28249, 11676, 21971, 5994, 20549, 25141, 32733, 28245, 2390, 28283, 18093, 5173, 8582, 18400,

};

int testcases = 2;
