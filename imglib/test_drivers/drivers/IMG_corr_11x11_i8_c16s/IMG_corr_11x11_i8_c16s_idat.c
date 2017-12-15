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
/* Test data for kernel size : 11 x 11 
 * kernel size */
 11,
/* Alignment data.
 * 0 = double word, 4 = word, 2 = half word, 1 = byte alignment respectively.
 * src align, mask align, dst align */
1, 2, 0,

/* Function parameters : 1 */
/* width, pitch, in_size, out_size*/
2, 12, 132, 2,

/* Image data : 1 */
 151, 77, 54, 113, 115, 131, 83, 33, 77, 28, 169, 221,
 57, 4, 154, 9, 203, 211, 230, 49, 72, 70, 192, 19,
 116, 6, 193, 28, 177, 158, 191, 224, 158, 7, 115, 221,
 170, 162, 161, 53, 42, 9, 137, 216, 193, 64, 154, 141,
 9, 6, 20, 211, 62, 2, 98, 158, 242, 49, 221, 40,
 247, 31, 162, 98, 155, 106, 251, 87, 86, 89, 91, 67,
 208, 143, 137, 217, 3, 227, 212, 63, 138, 202, 172, 144,
 140, 178, 150, 149, 103, 249, 148, 28, 188, 59, 47, 92,
 150, 3, 128, 233, 127, 255, 173, 77, 225, 122, 161, 230,
 60, 135, 224, 231, 16, 11, 115, 120, 176, 239, 196, 190,
 88, 91, 214, 127, 135, 203, 112, 53, 214, 192, 255, 58,

/* mask : 1 */
 -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40,
 -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29,
 -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18,
 -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7,
 -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4,
 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,

/* Function parameters : 2 */
/* width, pitch, in_size, out_size*/
30, 40, 440, 30,

/* Image data : 2 */
 98, 193, 164, 250, 229, 115, 66, 162, 10, 166, 218, 226, 127, 119, 80, 15, 229, 128, 239, 107, 139, 182, 184, 78, 15, 56, 121, 238, 13, 229, 58, 39, 100, 20, 69, 129, 116, 161, 88, 182,
 91, 87, 192, 55, 190, 110, 70, 11, 87, 109, 66, 180, 70, 130, 127, 125, 144, 203, 157, 180, 72, 240, 80, 42, 252, 106, 57, 145, 63, 33, 89, 112, 83, 53, 232, 102, 122, 146, 85, 247,
 151, 29, 187, 151, 62, 216, 135, 157, 139, 19, 122, 187, 8, 16, 159, 11, 44, 1, 123, 198, 202, 89, 83, 78, 105, 188, 193, 40, 242, 114, 185, 59, 241, 6, 247, 89, 110, 117, 234, 146,
 152, 5, 73, 57, 200, 27, 44, 165, 174, 127, 101, 195, 195, 143, 50, 176, 229, 116, 12, 168, 10, 59, 209, 217, 215, 157, 177, 245, 206, 23, 96, 163, 166, 96, 74, 152, 34, 19, 22, 88,
 44, 206, 148, 98, 236, 240, 255, 88, 63, 251, 52, 218, 57, 128, 54, 239, 139, 238, 206, 81, 197, 191, 156, 187, 130, 48, 158, 98, 148, 49, 215, 205, 144, 117, 107, 55, 83, 86, 98, 106,
 76, 112, 247, 127, 239, 23, 237, 89, 211, 254, 83, 130, 38, 232, 121, 194, 241, 72, 53, 11, 62, 157, 68, 189, 236, 232, 155, 150, 169, 154, 206, 170, 164, 9, 14, 190, 162, 239, 165, 121,
 75, 39, 87, 19, 61, 29, 147, 63, 182, 160, 99, 195, 141, 9, 167, 252, 88, 217, 71, 51, 110, 130, 167, 194, 82, 113, 76, 217, 189, 159, 79, 37, 134, 19, 161, 82, 32, 120, 200, 108,
 192, 49, 146, 163, 68, 204, 20, 103, 86, 22, 191, 52, 39, 230, 193, 183, 20, 230, 202, 33, 229, 173, 255, 238, 244, 65, 232, 95, 172, 54, 10, 182, 236, 23, 51, 124, 71, 90, 40, 184,
 110, 29, 100, 25, 20, 77, 211, 227, 25, 234, 245, 146, 67, 242, 65, 164, 227, 45, 238, 241, 132, 16, 113, 202, 96, 107, 20, 23, 215, 178, 127, 157, 107, 85, 189, 26, 91, 204, 175, 72,
 116, 205, 96, 90, 63, 143, 226, 91, 115, 154, 223, 11, 76, 27, 227, 89, 1, 79, 103, 205, 64, 138, 96, 22, 73, 223, 162, 141, 242, 85, 72, 156, 190, 92, 155, 35, 200, 55, 54, 123,
 75, 231, 252, 19, 253, 229, 73, 83, 40, 67, 241, 173, 3, 131, 251, 12, 179, 250, 244, 236, 35, 213, 151, 66, 37, 137, 195, 189, 157, 69, 187, 101, 64, 249, 227, 182, 162, 126, 96, 248,

/* mask : 2 */
 606, 28722, -15273, 17947, -19783, -28814, -30294, 1634, 332, 13759, -22716,
 21328, -20978, 2506, -25966, -6582, -442, -31029, 28382, -11927, 25188, -31803,
 -4824, -1045, -2864, 29913, 23111, -10289, 26365, -29981, 10091, -161, -21548,
 1377, 2702, -4422, -2927, 27898, -32690, 30248, 22091, 26878, 3449, -32103,
 4696, 12644, -27363, -24432, 26243, 7028, 29307, -361, 28251, 8305, -9318,
 15251, 7638, -21532, 2343, -15097, 21514, 30501, 15209, 20234, 14457, -23325,
 10696, 4956, -8398, 13404, 30954, 16085, 10676, -7418, -24006, 28309, 1399,
 -6900, 26998, -14634, 7540, -19146, -1424, -9676, -29397, 4056, 9928, 11694,
 3086, -31313, -17632, 20945, 27292, 9977, -25787, -6700, -23637, 8707, -6148,
 22892, -8276, 31730, 18816, -31100, 14933, -23656, 24626, -29131, 18188, 31544,
 -23607, -15545, 32143, 16039, 17254, -9030, 16695, 30339, 31256, -16844, 18619,

/* Function parameters : 3 */
/* width, pitch, in_size, out_size*/
10, 20, 220, 10,

/* Image data : 3 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 3 */
 28040, -406, -10831, 29786, -19903, -8285, 24124, -24503, -1255, 15715, 10778,
 4378, -11774, -29436, 2379, 7428, 334, -15109, 10375, -13480, 7810, 2311,
 -14610, 4727, 23134, -16562, -20085, -129, -3843, 25975, 29623, -6365, -20092,
 16696, -20429, -10193, -7404, 12933, -9934, 22856, -23214, -23210, -22767, 26909,
 -2095, -12864, -5532, 25389, 7389, -5754, 15941, 17563, 13647, -7110, -25447,
 -6628, 6335, -21618, -1009, 17294, 5660, -30270, 6481, 10949, -3640, 28460,
 -22890, -18690, -6918, -18225, 3091, -12920, -22685, 18696, -18777, 29727, -29159,
 -3313, 20286, 28943, -32189, -3620, -30610, -10706, 27871, -25351, -22309, -11390,
 3478, 569, -8298, -2373, 20907, -14562, -25860, 4688, 13103, 23146, -1553,
 -20599, 26049, 17789, 2355, -9695, -25056, 24718, 2960, 14285, -31779, 13974,
 -18952, -23308, -25978, -7783, 8511, -14551, 27735, -12764, -27228, 18876, -2642,

/* Function parameters : 4 */
/* width, pitch, in_size, out_size*/
8, 18, 198, 8,

/* Image data : 4 */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/* mask : 4 */
 28040, -406, -10831, 29786, -19903, -8285, 24124, -24503, -1255, 15715, 10778,
 4378, -11774, -29436, 2379, 7428, 334, -15109, 10375, -13480, 7810, 2311,
 -14610, 4727, 23134, -16562, -20085, -129, -3843, 25975, 29623, -6365, -20092,
 16696, -20429, -10193, -7404, 12933, -9934, 22856, -23214, -23210, -22767, 26909,
 -2095, -12864, -5532, 25389, 7389, -5754, 15941, 17563, 13647, -7110, -25447,
 -6628, 6335, -21618, -1009, 17294, 5660, -30270, 6481, 10949, -3640, 28460,
 -22890, -18690, -6918, -18225, 3091, -12920, -22685, 18696, -18777, 29727, -29159,
 -3313, 20286, 28943, -32189, -3620, -30610, -10706, 27871, -25351, -22309, -11390,
 3478, 569, -8298, -2373, 20907, -14562, -25860, 4688, 13103, 23146, -1553,
 -20599, 26049, 17789, 2355, -9695, -25056, 24718, 2960, 14285, -31779, 13974,
 -18952, -23308, -25978, -7783, 8511, -14551, 27735, -12764, -27228, 18876, -2642,

/* Function parameters : 5 */
/* width, pitch, in_size, out_size*/
30, 40, 440, 30,

/* Image data : 5 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 5 */
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* Function parameters : 6 */
/* width, pitch, in_size, out_size*/
4, 14, 154, 4,

/* Image data : 6 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 6 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
};

int testcases = 6;