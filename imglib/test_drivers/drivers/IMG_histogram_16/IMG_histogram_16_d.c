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

/* File generated using matlab script "histogram_gen.m" */
/* Copyright 2008, Texas Instruments, Inc.  All rights reserved. */

#include <stdio.h>
#include <time.h>
#include "mem_cpy.h"
#include "support.h"
#include "IMG_histogram_16.h"
#include "IMG_histogram_16_c.h"

#define N 40000
#define PAD 64
#define SIZE (N + 2*PAD)
#define OUT_SIZE (65536 + 2*PAD)
#define TEMP_SIZE (4 * 65536 + 2*PAD)
unsigned short input_1[SIZE], input_2[SIZE];
short output_c[OUT_SIZE], output_i[OUT_SIZE], ref_out[OUT_SIZE];
unsigned short temp_buf[TEMP_SIZE];

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern short out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */

main()
{
  clock_t t_start, t_stop, t_overhead, t1, t2, t_c, t_cn;
  int count;
  int acc, num_bits, in_size, out_size;
  short align_in, align_out;
  unsigned short *src_ptr_1;
  short *dst_ptr_c, *dst_ptr_i, *ref_out_ptr;
  short *temp_ptr;

  int *inp = &in_data[0];
  short *outp = &out_data[0];

  /* Compute the overhead of calling clock twice to get timing info. */
  t_start    = clock();
  t_stop     = clock();
  t_overhead = t_stop - t_start;

  align_in  = *inp++;
  align_out = *inp++;

  src_ptr_1 = (unsigned short *)( (unsigned int)&input_1[PAD]  + align_in );
  dst_ptr_c = (short *)( (unsigned int)&output_c[PAD] + align_out);
  dst_ptr_i = (short *)( (unsigned int)&output_i[PAD] + align_out);
  temp_ptr  = (short *)( (unsigned int)&temp_buf[PAD]);
  ref_out_ptr = (short *)( (unsigned int)&ref_out[PAD] + align_out);

  for(count = 0; count < testcases; count++)
  {
    acc = *inp++;
    num_bits = *inp++;
    in_size = *inp++;
    out_size = *inp++;

    /* Checking sanity of generated driver. */
    if( (N < in_size) || (OUT_SIZE < out_size) )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      return(0);
    }

    /* Prepare output arrays */
    memset(output_c, 0, sizeof(ref_out[0]) * SIZE);
    memset(output_i, 0, sizeof(ref_out[0]) * SIZE);
    memset(ref_out , 0, sizeof(ref_out[0]) * SIZE);

    /* Copy input and ref output to respective buffers */
    copy_int_to_ushort(src_ptr_1, inp, in_size);
    inp += in_size;
    memcpy(ref_out_ptr, outp, out_size * sizeof(ref_out[0]));
    outp += out_size;

    /* run the testcase */
    memset(temp_buf, 0, sizeof(short) * TEMP_SIZE);
    t1 = clock();
    IMG_histogram_16_c (src_ptr_1, in_size, acc, temp_ptr, dst_ptr_i, num_bits );
    t2 = clock();

    t_c = t2 - t1 -t_overhead;

    memset(temp_buf, 0, sizeof(short) * TEMP_SIZE);
    t1 = clock();
    IMG_histogram_16_cn(src_ptr_1, in_size, acc, temp_ptr, dst_ptr_c, num_bits );
    t2 = clock();

    t_cn = t2 - t1 -t_overhead;

    if( memcmp(output_c, ref_out, SIZE * sizeof(ref_out[0])) )
    {
      printf("Result failure - natural c: case # %d\n", count);
      return(0);
    }

    if( memcmp(output_i, ref_out, SIZE * sizeof(ref_out[0])) )
    {
      printf("Result failure - intrinsics: case # %d\n", count);
      return(0);
    }

    printf("%2d : C = %4d, natC = %4d\n", count, t_c, t_cn);

  } /* for */

  printf("Success. Test suite (%d cases) passed.\n", testcases);

}
