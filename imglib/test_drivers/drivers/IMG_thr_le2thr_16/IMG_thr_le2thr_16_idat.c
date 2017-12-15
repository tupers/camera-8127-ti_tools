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
/* cols, rows, threshold, dat_size (in, out) */
16, 1, 49151, 16,

/* Input data : 1 */
 38690, 14640, 29673, 43602, 2339, 63219, 53201, 35822, 38324, 15427, 22613, 19629, 948, 1628, 41419, 1513,

/* Function parameters : 2 */
/* cols, rows, threshold, dat_size (in, out) */
32, 2, 45875, 64,

/* Input data : 2 */
 8011, 36590, 45653, 665, 34456, 23288, 13950, 39507, 49372, 41325, 5083, 41405, 35190, 38508, 32875, 57351, 54772, 28875, 2406, 7059, 13651, 53953, 25080, 55435, 38197, 59566, 59256, 32507, 29439, 52047, 45233, 10790, 15904, 39660, 809, 26389, 32571, 4116, 34589, 33502, 53903, 40421, 2297, 419, 27225, 58131, 63629, 65524, 2764, 51917, 21298, 58785, 48837, 35111, 24979, 64139, 54398, 37955, 44325, 29563, 28559, 8369, 12505, 57425,

/* Function parameters : 3 */
/* cols, rows, threshold, dat_size (in, out) */
8, 6, 0, 48,

/* Input data : 3 */
 55190, 40422, 22262, 16144, 7090, 19795, 30696, 13442, 19720, 18360, 40427, 49326, 62067, 22115, 35272, 48016, 57518, 45146, 54872, 7254, 17918, 1877, 16374, 12506, 22736, 51628, 15209, 31190, 61179, 49255, 43211, 49164, 29462, 39390, 56499, 23352, 43942, 11989, 41098, 50282, 65465, 56490, 4780, 56566, 36186, 10346, 17163, 36799,

/* Function parameters : 4 */
/* cols, rows, threshold, dat_size (in, out) */
4, 16, 1, 64,

/* Input data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 5 */
/* cols, rows, threshold, dat_size (in, out) */
8, 6, 10, 48,

/* Input data : 5 */
 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,

/* Function parameters : 6 */
/* cols, rows, threshold, dat_size (in, out) */
8, 8, 23, 64,

/* Input data : 6 */
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
};

int testcases = 6;
