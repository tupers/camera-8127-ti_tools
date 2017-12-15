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
/* cols, rows, in_size, out_size*/
4, 3, 12, 2,

/* Image data : 1 */
 38690, 43602, 53201, 15427,
 14640, 2339, 35822, 22613,
 29673, 63219, 38324, 19629,

/* Function parameters : 2 */
/* cols, rows, in_size, out_size*/
24, 3, 72, 22,

/* Image data : 2 */
 948, 1513, 45653, 23288, 49372, 41405, 32875, 28875, 13651, 55435, 59256, 52047, 15904, 26389, 34589, 40421, 27225, 65524, 21298, 35111, 54398, 29563, 12505, 40422,
 1628, 8011, 665, 13950, 41325, 35190, 57351, 2406, 53953, 38197, 32507, 45233, 39660, 32571, 33502, 2297, 58131, 2764, 58785, 24979, 37955, 28559, 57425, 22262,
 41419, 36590, 34456, 39507, 5083, 38508, 54772, 7059, 25080, 59566, 29439, 10790, 809, 4116, 53903, 419, 63629, 51917, 48837, 64139, 44325, 8369, 55190, 16144,

/* Function parameters : 3 */
/* cols, rows, in_size, out_size*/
20, 3, 60, 18,

/* Image data : 3 */
 1773, 3361, 10107, 5529, 14379, 1813, 4094, 12907, 15295, 12291, 14125, 2997, 16366, 14141, 4291, 14704, 8344, 12679, 619, 11632,
 4949, 4930, 12332, 8818, 11286, 4479, 3127, 3802, 12314, 7365, 5838, 10275, 14122, 9047, 9200, 12128, 15372, 3246, 8600, 2513,
 7674, 4590, 15517, 12004, 13718, 469, 5684, 7798, 10803, 9848, 10986, 12570, 1195, 2586, 5898, 3708, 4374, 989, 8275, 13524,

/* Function parameters : 4 */
/* cols, rows, in_size, out_size*/
8, 3, 24, 6,

/* Image data : 4 */
 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,

/* Function parameters : 5 */
/* cols, rows, in_size, out_size*/
28, 3, 84, 26,

/* Image data : 5 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int testcases = 5;
