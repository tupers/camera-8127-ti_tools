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
/* dat_size (in, out) */
32,

/* Input data : 1 */
 5922, -18128, -3095, 10834, -30429, 30451, 20433, 3054, 5556, -17341, -10155, -13139, -31820, -31140, 8651, -31255, -24757, 3822, 12885, -32103, 1688, -9480, -18818, 6739, 16604, 8557, -27685, 8637, 2422, 5740, 107, 24583,

/* Function parameters : 2 */
/* dat_size (in, out) */
64,

/* Input data : 2 */
 -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 255, 255, 255, 255, 255, 255, 255, 255, 256, 256, 256, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,

/* Function parameters : 3 */
/* dat_size (in, out) */
64,

/* Input data : 3 */
 344, -61, -474, -402, -299, 331, -120, 354, 85, 419, 414, -4, -52, 301, 195, -343, -264, 108, -499, -100, -3, -448, 28, 11, 330, 120, -476, -505, -87, 396, 482, 512, -469, 299, -179, 407, 251, 37, -122, 490, 338, 81, 181, -50, -66, -381, -317, 385, 350, 120, -164, -260, -401, -203, -32, -302, -204, -225, 120, 259, 458, -166, 39, 238,
};

int testcases = 3;
