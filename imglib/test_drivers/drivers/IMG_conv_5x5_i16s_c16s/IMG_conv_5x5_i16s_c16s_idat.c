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
/* Test data for kernel size : 5 x 5 
 * kernel size */
 5,
/* Alignment data.
 * 0 = dooble word, 4 = word, 2 = half word, 1 = byte alignment respectively.
 * src align, mask align, dst align */
2, 2, 4,

/* Function parameters : 1 */
/* width, pitch, shift, in_size, out_size*/
2, 6, 13, 30, 2,

/* Image data : 1 */
 8557, 107, -25709, 5429, 19279, -31959,
 -27685, 24583, -19117, 26798, 12465, -6379,
 8637, 22004, 21185, 26488, -21978, -197,
 2422, -3893, -7688, -261, -16864, -28652,
 5740, -30362, 22667, -3329, 6892, 1821,

/* mask : 1 */
 740, -2266, -387, 1354, -3804,
 3806, 2554, 382, 694, -2168,
 -1269, -1642, -3978, -3892, 1081,
 -3907, -3095, 478, 1611, -4013,
 211, -1185, -2352, 842, 2075,

/* Function parameters : 2 */
/* width, pitch, shift, in_size, out_size*/
30, 34, 13, 170, 30,

/* Image data : 2 */
 734, -5543, 19149, -7789, -3205, 22422, -12973, 7659, 15248, -14850, 18860, 10443, -9416, 32697, -22422, 15744, 17947, 332, 2506, 28382, -1045, 26365, 1377, -32690, -32103, 26243, 8305, 2343, 20234, -8398, -7418, 26998, -9676, 3086,
 21135, 25363, -11470, 31371, -4209, 7654, -2072, 16558, 24750, -30891, -17559, 16396, 11174, 23722, -15605, -17937, -19783, 13759, -25966, -11927, -2864, -29981, 2702, 30248, 4696, 7028, -9318, -15097, 14457, 13404, -24006, -14634, -29397, -31313,
 7653, 30861, 26017, 21630, -24399, -10506, -19326, 29299, 12378, -16394, -1578, -3306, -20779, -27988, 4031, 606, -28814, -22716, -6582, 25188, 29913, 10091, -4422, 22091, 12644, 29307, 15251, 21514, -23325, 30954, 28309, 7540, 4056, -17632,
 -30471, 32756, 16069, 5187, -20263, -16624, -13048, -10653, 22104, -20262, 28411, 6622, 8330, 23798, -9177, 28722, -30294, 21328, -442, -31803, 23111, -161, -2927, 26878, -27363, -361, 7638, 30501, 10696, 16085, 1399, -19146, 9928, 20945,
 -32349, -30004, 2343, 11557, 24657, -25678, -14408, 2504, -25514, -10032, 16487, 23731, 17514, 3418, 26048, -15273, 1634, -20978, -31029, -4824, -10289, -21548, 27898, 3449, -24432, 28251, -21532, 15209, 4956, 10676, -6900, -1424, 11694, 27292,

/* mask : 2 */
 740, -2266, -387, 1354, -3804,
 3806, 2554, 382, 694, -2168,
 -1269, -1642, -3978, -3892, 1081,
 -3907, -3095, 478, 1611, -4013,
 211, -1185, -2352, 842, 2075,

/* Function parameters : 3 */
/* width, pitch, shift, in_size, out_size*/
10, 14, 13, 70, 10,

/* Image data : 3 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* mask : 3 */
 740, -2266, -387, 1354, -3804,
 3806, 2554, 382, 694, -2168,
 -1269, -1642, -3978, -3892, 1081,
 -3907, -3095, 478, 1611, -4013,
 211, -1185, -2352, 842, 2075,

/* Function parameters : 4 */
/* width, pitch, shift, in_size, out_size*/
8, 12, 13, 60, 8,

/* Image data : 4 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,

/* mask : 4 */
 740, -2266, -387, 1354, -3804,
 3806, 2554, 382, 694, -2168,
 -1269, -1642, -3978, -3892, 1081,
 -3907, -3095, 478, 1611, -4013,
 211, -1185, -2352, 842, 2075,

/* Function parameters : 5 */
/* width, pitch, shift, in_size, out_size*/
40, 44, 16, 220, 40,

/* Image data : 5 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* mask : 5 */
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,

/* Function parameters : 6 */
/* width, pitch, shift, in_size, out_size*/
4, 8, 16, 40, 4,

/* Image data : 6 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* mask : 6 */
 2631, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,
 2621, 2621, 2621, 2621, 2621,

/* Function parameters : 7 */
/* width, pitch, shift, in_size, out_size*/
12, 16, 16, 80, 12,

/* Image data : 7 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* mask : 7 */
 32767, 32767, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,

/* Function parameters : 8 */
/* width, pitch, shift, in_size, out_size*/
14, 18, 16, 90, 14,

/* Image data : 8 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,

/* mask : 8 */
 -32768, -32768, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,

/* Function parameters : 9 */
/* width, pitch, shift, in_size, out_size*/
16, 20, 16, 100, 16,

/* Image data : 9 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* mask : 9 */
 -32768, -32768, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
};

int testcases = 9;
