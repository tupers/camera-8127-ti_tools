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

/* Copyright 2008, Texas Instruments, Inc.  All rights reserved. */

#include <stdio.h>
#include <time.h>
#include "mem_cpy.h"
#include "support.h"
#include "IMG_ycbcr422pl_to_rgb565.h"
#include "IMG_ycbcr422pl_to_rgb565_c.h"

#define N 64
#define PAD 32
#define SIZE (N + 2*PAD)
#define NUM_COEFF 5

typedef unsigned char I_type;
typedef unsigned short O_type;

I_type y_in[SIZE], cr_in[SIZE], cb_in[SIZE];
O_type rgb[SIZE], rgb_ref[SIZE];
short coeff[NUM_COEFF + 2*PAD];

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern O_type out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */

main()
{
  clock_t t_start, t_stop, t_overhead, t1, t2, t_c, t_cn;
  int count;
  int num, c_num;
  short align_y, align_c, align_out, align_coeff;
  I_type *y_in_ptr, *cb_in_ptr, *cr_in_ptr;
  O_type *rgb_ptr, *rgb_ref_ptr;
  short *coeff_ptr;

  int *inp = &in_data[0];
  O_type *outp = &out_data[0];

  /* Compute the overhead of calling clock twice to get timing info. */
  t_start    = clock();
  t_stop     = clock();
  t_overhead = t_stop - t_start;

  /* Read test parameters. */
  align_y    = *inp++;
  align_c    = *inp++;
  align_out  = *inp++;
  align_coeff= *inp++;

  y_in_ptr   = (I_type *)( (unsigned int)&y_in[PAD]  + align_y);
  cr_in_ptr  = (I_type *)( (unsigned int)&cr_in[PAD] + align_c);
  cb_in_ptr  = (I_type *)( (unsigned int)&cb_in[PAD] + align_c);
  rgb_ptr    = (O_type *)( (unsigned int)&rgb[PAD] + align_out);
  rgb_ref_ptr= (O_type *)( (unsigned int)&rgb_ref[PAD] + align_out);
  coeff_ptr  = (short *) ( (unsigned int)&coeff[PAD] + align_coeff);

  for(count = 1; count <= testcases; count++)
  {
    /* Read test-case params. */
    num = *inp++;
    c_num = num >> 1;

    /* Checking sanity of generated driver. */
    if( N < num )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      return(0);
    }

    /* Prepare i/o arrays */
    memset(y_in,  0, sizeof(y_in));
    memset(cr_in, 0, sizeof(cr_in));
    memset(cb_in, 0, sizeof(cb_in));
    memset(rgb,   0, sizeof(rgb));
    memset(rgb_ref, 0, sizeof(rgb_ref));

    /* Copy input and ref output to respective buffers */
    copy_int_to_short(coeff_ptr, inp, NUM_COEFF);
    inp += NUM_COEFF;
    copy_int_to_uchar(y_in_ptr, inp, num);   // copy input
    inp += num;
    copy_int_to_uchar(cb_in_ptr, inp, c_num);   // copy input
    inp += c_num;
    copy_int_to_uchar(cr_in_ptr, inp, c_num);   // copy input
    inp += c_num;

    memcpy(rgb_ref_ptr, outp, num * sizeof(outp[0]));
    outp += num;

    /* run the testcase */
    t1 = clock();
    IMG_ycbcr422pl_to_rgb565 (coeff_ptr, y_in_ptr, cb_in_ptr, cr_in_ptr, rgb_ptr, num);
    t2 = clock();
    t_c = t2 - t1 - t_overhead;

    if( memcmp(rgb, rgb_ref, sizeof(rgb_ref) ))
    {
      printf("Result failure: intrinsics: case # %d\n", count);
      return(-1);
    }

    /* Test for natural C */
    memset(rgb,  0, sizeof(rgb));

    t1 = clock();
    IMG_ycbcr422pl_to_rgb565_cn (coeff_ptr, y_in_ptr, cb_in_ptr, cr_in_ptr, rgb_ptr, num);
    t2 = clock();
    t_cn = t2 - t1 - t_overhead;

    if( memcmp(rgb, rgb_ref, sizeof(rgb_ref) ))
    {
      printf("Result failure: nat c: case # %d\n", count);
      return(-1);
    }

    printf("%2d : C = %4d, natC = %4d\n", count, t_c, t_cn);

  } /* for */

  printf("Success. Test suite (%d cases) passed.\n", testcases);

  return(0);
}

