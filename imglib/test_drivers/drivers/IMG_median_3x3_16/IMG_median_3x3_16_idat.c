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
/* cols, in_size, out_size */
4, 12, 4,

/* Input data : 1 */
 38690, 43602, 53201, 15427,
 14640, 2339, 35822, 22613,
 29673, 63219, 38324, 19629,

/* Function parameters : 2 */
/* cols, in_size, out_size */
28, 84, 28,

/* Input data : 2 */
 948, 1513, 45653, 23288, 49372, 41405, 32875, 28875, 13651, 55435, 59256, 52047, 15904, 26389, 34589, 40421, 27225, 65524, 21298, 35111, 54398, 29563, 12505, 40422, 7090, 13442, 40427, 22115,
 1628, 8011, 665, 13950, 41325, 35190, 57351, 2406, 53953, 38197, 32507, 45233, 39660, 32571, 33502, 2297, 58131, 2764, 58785, 24979, 37955, 28559, 57425, 22262, 19795, 19720, 49326, 35272,
 41419, 36590, 34456, 39507, 5083, 38508, 54772, 7059, 25080, 59566, 29439, 10790, 809, 4116, 53903, 419, 63629, 51917, 48837, 64139, 44325, 8369, 55190, 16144, 30696, 18360, 62067, 48016,

/* Function parameters : 3 */
/* cols, in_size, out_size */
12, 36, 12,

/* Input data : 3 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 4 */
/* cols, in_size, out_size */
24, 72, 24,

/* Input data : 4 */
 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
};

int testcases = 4;
