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
#include "IMG_corr_3x3_i16s_c16s.h"
#include "IMG_corr_3x3_i16s_c16s_c.h"

#define M_SIZE 3
#define O_N 34
#define N (M_SIZE * O_N)
#define C_N (M_SIZE * M_SIZE)
#define PAD 8
#define SIZE (N + 2*PAD)
#define C_SIZE (C_N + 2*PAD)
#define O_SIZE (O_N + 2*PAD)

typedef short I_type;
typedef short C_type;
typedef int   O_type;

I_type input_1[SIZE];
C_type mask[C_SIZE];
O_type output[O_SIZE], ref_output[O_SIZE];

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern O_type out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */

main()
{
  clock_t t_start, t_stop, t_overhead, t1, t2, t_c, t_cn;
  int count;
  int in_size, out_size, m_size;
  int width, pitch;
  int round, shift;
  short align_in, align_mask, align_out;
  I_type *src_ptr_1;
  C_type *mask_ptr;
  O_type *output_ptr, *ref_output_ptr;

  int *inp = &in_data[0];
  O_type *outp = &out_data[0];

  /* Compute the overhead of calling clock twice to get timing info. */
  t_start    = clock();
  t_stop     = clock();
  t_overhead = t_stop - t_start;

  /* Read test parameters. */
  m_size      = *inp++;
  align_in    = *inp++;
  align_mask  = *inp++;
  align_out   = *inp++;

  if(m_size != M_SIZE)
  {
    printf("Incorrect data file: for mask size %d\n", m_size);
    return(0);
  }

  src_ptr_1 =      (I_type *)( (unsigned int)&input_1[PAD]  + align_in );
  mask_ptr =       (C_type *)( (unsigned int)&mask[PAD]     + align_mask);
  output_ptr  =    (O_type *)( (unsigned int)&output[PAD]   + align_out);
  /* Spl case. Kernel writes output data corresponding to the centeral pixel of the mask. */
  ref_output_ptr = (O_type *)( (unsigned int)&ref_output[PAD] + align_out);

  for(count = 1; count <= testcases; count++)
  {
    /* Read test-case params. */
    width = *inp++;
    pitch = *inp++;
	shift = *inp++;
    round = *inp++;
    in_size  = *inp++;
    out_size = *inp++;

    /* Checking sanity of generated driver. */
    if( N < in_size )
    {
      printf("source array size (%d) is less than test-case (ID %d) size (%d)\n", N, count, in_size);
      return(0);
    }

    /* Prepare output arrays */
    memset(input_1, 0, sizeof(input_1));
    memset(output, 0, sizeof(output[0]) * O_SIZE);
    memset(ref_output, 0, sizeof(ref_output[0]) * O_SIZE);

    /* Copy input and ref output to respective buffers */
    copy_int_to_short(src_ptr_1, inp, in_size);   // copy input
    inp += in_size;
    copy_int_to_short(mask_ptr, inp, C_N);     // copy mask
    inp += C_N;
    memcpy(ref_output_ptr, outp, out_size * sizeof(outp[0]));
    outp += out_size;

    /* run the testcase */
    t1 = clock();
    IMG_corr_3x3_i16s_c16s (src_ptr_1, output_ptr, width, pitch, mask_ptr, shift, round);
    t2 = clock();

    t_c = t2 - t1 - t_overhead;

    if( memcmp(output, ref_output, O_SIZE * sizeof(ref_output[0])) )
    {
      printf("Result failure: output - intrinsics: case # %d\n", count);
      return(0);
    }


    memset(output, 0, sizeof(output[0]) * O_SIZE);

    t1 = clock();
    IMG_corr_3x3_i16s_c16s_cn (src_ptr_1, output_ptr, width, pitch, mask_ptr, shift, round);
    t2 = clock();

    t_cn = t2 - t1 - t_overhead;

    if( memcmp(output, ref_output, O_SIZE * sizeof(ref_output[0])) )
    {
      printf("Result failure: output - natural c: case # %d\n", count);
      return(0);
    }

    printf("%2d : C = %4d, natC = %4d\n", count, t_c, t_cn);

  } /* for */

  printf("Success. Test suite (%d cases) passed.\n", testcases);

  return(0);
}




