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
1, 1, 4,

/* Function parameters : 1 */
/* width, pitch, shift, in_size, out_size*/
2, 12, 13, 132, 2,

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
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66,
 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,

/* Function parameters : 2 */
/* width, pitch, shift, in_size, out_size*/
30, 40, 13, 440, 30,

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
 65, 120, 34, 99, 25, 8, 5, 67, 65, 91, 20,
 106, 23, 69, 13, 51, 63, 3, 119, 41, 113, 2,
 55, 62, 58, 122, 109, 44, 115, 5, 84, 64, 22,
 67, 69, 55, 58, 118, 0, 123, 107, 116, 71, 1,
 73, 89, 11, 16, 115, 78, 121, 63, 119, 80, 46,
 94, 79, 22, 69, 35, 106, 124, 94, 104, 92, 18,
 85, 74, 48, 90, 124, 95, 85, 50, 17, 119, 67,
 51, 117, 35, 79, 27, 61, 45, 7, 72, 83, 87,
 70, 3, 30, 105, 117, 83, 14, 51, 18, 81, 52,
 109, 48, 126, 101, 3, 93, 18, 112, 7, 100, 126,
 18, 34, 127, 95, 98, 46, 97, 123, 125, 31, 100,

/* Function parameters : 3 */
/* width, pitch, shift, in_size, out_size*/
10, 20, 16, 220, 10,

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
 -108, 127, -128, 112, -128, -128, -49, 127, -128, -128, -128,
 -9, -128, -128, 31, -128, 127, 93, -128, 41, 127, -47,
 92, -95, -124, -128, -128, -128, -128, 125, -128, 127, -128,
 37, -128, -128, -128, -71, 127, -100, -128, 3, -128, -128,
 -14, -128, -128, -82, -20, 127, 127, 50, -128, -35, -128,
 -128, 50, -4, -128, -128, -128, -128, -128, -128, -128, -83,
 -69, -128, 51, -19, 127, -128, -128, -128, 56, 127, 0,
 127, -128, -18, -128, -128, -128, -128, -128, -128, -128, -128,
 114, 127, -18, -128, -82, -128, -128, -128, -128, -128, 44,
 -75, -128, -123, -128, 127, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, 104, 127, 5, -23, 127, -18,

/* Function parameters : 4 */
/* width, pitch, shift, in_size, out_size*/
8, 18, 16, 198, 8,

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
 -108, 127, -128, 112, -128, -128, -49, 127, -128, -128, -128,
 -9, -128, -128, 31, -128, 127, 93, -128, 41, 127, -47,
 92, -95, -124, -128, -128, -128, -128, 125, -128, 127, -128,
 37, -128, -128, -128, -71, 127, -100, -128, 3, -128, -128,
 -14, -128, -128, -82, -20, 127, 127, 50, -128, -35, -128,
 -128, 50, -4, -128, -128, -128, -128, -128, -128, -128, -83,
 -69, -128, 51, -19, 127, -128, -128, -128, 56, 127, 0,
 127, -128, -18, -128, -128, -128, -128, -128, -128, -128, -128,
 114, 127, -18, -128, -82, -128, -128, -128, -128, -128, 44,
 -75, -128, -123, -128, 127, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, 104, 127, 5, -23, 127, -18,

/* Function parameters : 5 */
/* width, pitch, shift, in_size, out_size*/
40, 50, 16, 550, 40,

/* Image data : 5 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 5 */
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,

/* Function parameters : 6 */
/* width, pitch, shift, in_size, out_size*/
4, 14, 16, 154, 4,

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
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,

/* Function parameters : 7 */
/* width, pitch, shift, in_size, out_size*/
12, 22, 11, 242, 12,

/* Image data : 7 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 7 */
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,

/* Function parameters : 8 */
/* width, pitch, shift, in_size, out_size*/
14, 24, 16, 264, 14,

/* Image data : 8 */
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

/* mask : 8 */
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
 -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
};

int testcases = 8;
