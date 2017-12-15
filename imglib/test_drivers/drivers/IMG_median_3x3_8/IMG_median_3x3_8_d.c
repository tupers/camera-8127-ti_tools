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
#include "IMG_median_3x3_8.h"
#include "IMG_median_3x3_8_c.h"

#define N 32
#define PAD 32
#define I_N (N*3)
#define I_SIZE (I_N + 2*PAD)
#define O_SIZE (N + 2*PAD)

typedef unsigned char I_type;
typedef unsigned char O_type;

I_type input[I_SIZE];
O_type output[O_SIZE], ref_output[O_SIZE];

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern O_type out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */

main()
{
  clock_t t_start, t_stop, t_overhead, t1, t2, t_c, t_cn;
  int count;
  int in_size, out_size;
  short align_in, align_out;
  I_type *src_ptr;
  O_type *output_ptr, *ref_output_ptr;

  int *inp = &in_data[0];
  O_type *outp = &out_data[0];

  /* Compute the overhead of calling clock twice to get timing info. */
  t_start    = clock();
  t_stop     = clock();
  t_overhead = t_stop - t_start;

  /* Read test parameters. */
  align_in    = *inp++;
  align_out   = *inp++;

  src_ptr =        (I_type *)( (unsigned int)&input[PAD]  + align_in );
  output_ptr  =    (O_type *)( (unsigned int)&output[PAD] + align_out);
  ref_output_ptr = (O_type *)( (unsigned int)&ref_output[PAD] + align_out);

  for(count = 1; count <= testcases; count++)
  {
    /* Read test-case params. */
		int n = *inp++;
    in_size  = *inp++;
    out_size = *inp++;  // input and output size is the same.

    /* Checking sanity of generated driver. */
    if( I_N < in_size )
    {
      printf("source or dst array size is less than test-case (ID %d) size (%d)\n", count, in_size);
      return(0);
    }

    /* Prepare output arrays */
    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));
    memset(ref_output, 0, sizeof(ref_output));

    /* Copy input and ref output to respective buffers */
    copy_int_to_uchar(src_ptr, inp, in_size);   // copy input
    inp += in_size;
    memcpy(ref_output_ptr, outp, out_size * sizeof(outp[0]));
    outp += out_size;

    /* run the testcase */
    t1 = clock();
    IMG_median_3x3_8 (src_ptr, n, output_ptr);
    t2 = clock();
    t_c = t2 - t1 - t_overhead;

    if( memcmp(output, ref_output, sizeof(ref_output)) )
    {
      printf("Result failure: output - intrinsics: case # %d\n", count);
      return(0);
    }


    memset(output, 0, sizeof(output));

    t1 = clock();
    IMG_median_3x3_8_cn (src_ptr, n, output_ptr);
    t2 = clock();
    t_cn = t2 - t1 - t_overhead;

    if( memcmp(output, ref_output, sizeof(ref_output)) )
    {
      printf("Result failure: output - natural c: case # %d\n", count);
      return(0);
    }

    printf("%2d : C = %4d, natC = %4d\n", count, t_c, t_cn);

  } /* for */

  printf("Success. Test suite (%d cases) passed.\n", testcases);

  return(0);
}

