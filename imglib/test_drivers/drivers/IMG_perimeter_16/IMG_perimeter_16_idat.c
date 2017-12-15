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
/* cols, in_size, out_size, count */
8, 24, 8, 1,

/* Input data : 1 */
 38690, 43602, 53201, 0, 0, 0, 45653, 0,
 0, 0, 35822, 0, 0, 0, 0, 0,
 0, 63219, 38324, 0, 41419, 36590, 34456, 39507,

/* Function parameters : 2 */
/* cols, in_size, out_size, count */
80, 240, 80, 19,

/* Input data : 2 */
 0, 0, 0, 0, 0, 55435, 59256, 0, 0, 0, 0, 0, 0, 65524, 0, 0, 54398, 0, 0, 0, 0, 0, 0, 0, 57518, 0, 0, 0, 61179, 0, 56499, 0, 65465, 56566, 0, 58816, 0, 0, 0, 0, 0, 0, 61150, 0, 0, 0, 0, 0, 0, 63016, 0, 0, 59011, 0, 0, 0, 54282, 53002, 0, 0, 0, 61077, 59766, 0, 0, 0, 0, 0, 0, 55660, 0, 0, 0, 0, 0, 63107, 0, 0, 0, 0,
 0, 0, 57351, 0, 53953, 0, 0, 0, 0, 0, 0, 0, 58131, 0, 58785, 0, 0, 0, 57425, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56490, 0, 0, 0, 61490, 0, 0, 0, 0, 0, 0, 0, 62681, 59133, 0, 0, 60666, 54859, 0, 0, 0, 61019, 0, 0, 63269, 0, 0, 63722, 0, 0, 0, 0, 0, 0, 53713, 0, 0, 0, 0, 57394, 64312, 64911, 0, 64024, 0, 0, 0, 0,
 0, 0, 54772, 0, 0, 59566, 0, 0, 0, 0, 53903, 0, 63629, 0, 0, 64139, 0, 0, 55190, 0, 0, 0, 62067, 0, 54872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54096, 0, 0, 57956, 0, 55879, 0, 0, 0, 0, 59646, 0, 0, 62075, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60060, 0, 0, 64498, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 3 */
/* cols, in_size, out_size, count */
40, 120, 40, 0,

/* Input data : 3 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* Function parameters : 4 */
/* cols, in_size, out_size, count */
48, 144, 48, 0,

/* Input data : 4 */
 49449, 1403, 9971, 52516, 49115, 37800, 37295, 64545, 38596, 32384, 6357, 58645, 51280, 15501, 16143, 28110, 61454, 52342, 58651, 34662, 60594, 53966, 41466, 42262, 16024, 23230, 22193, 16193, 21919, 10277, 4810, 65059, 59990, 55699, 25838, 25454, 57027, 46132, 55848, 13268, 44294, 2011, 9809, 17240, 30409, 36679, 2183, 6822,
 22219, 52623, 12595, 59218, 47803, 63315, 25476, 63946, 14604, 4908, 22963, 48696, 60315, 17489, 64890, 55301, 5896, 19608, 16928, 11296, 37683, 57785, 2915, 22571, 26433, 21177, 35654, 54086, 6404, 42532, 32606, 40854, 39540, 16898, 13236, 48808, 61710, 47918, 33331, 37426, 32498, 49834, 36182, 19516, 33258, 32699, 58868, 33613,
 7479, 28707, 7349, 42026, 18762, 22392, 24499, 14052, 25114, 41630, 4745, 15803, 61181, 5136, 29434, 6909, 7537, 36692, 17845, 65430, 4994, 18766, 40092, 22757, 58031, 2629, 44500, 46641, 29413, 27880, 64319, 5513, 17258, 31247, 21229, 62712, 57966, 49938, 49924, 2795, 17863, 14717, 9952, 875, 4213, 59469, 61852, 20481,
};

int testcases = 4;
