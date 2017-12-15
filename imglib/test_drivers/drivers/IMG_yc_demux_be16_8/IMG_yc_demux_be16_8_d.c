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
#include "IMG_yc_demux_be16_8.h"
#include "IMG_yc_demux_be16_8_c.h"

#define N 128
#define N_Y (N >> 1)
#define N_C (N >> 2)
#define PAD 64
#define SIZE (N + 2*PAD)
#define SIZE_Y (N_Y + 2*PAD)
#define SIZE_C (N_C + 2*PAD)

typedef unsigned char I_type;
typedef short O_type;

I_type input[SIZE];
O_type y_out[SIZE_Y], cr_out[SIZE_C], cb_out[SIZE_C];
O_type y_out_ref[SIZE_Y], cr_out_ref[SIZE_C], cb_out_ref[SIZE_C];

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern O_type out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */

main()
{
  clock_t t_start, t_stop, t_overhead, t1, t2, t_c, t_cn;
  int count;
  int in_size, out_size_y, out_size_c;
  int num_luma;
  short align_in, align_out;
  I_type *src_ptr;
  O_type *y_out_ptr, *y_out_ptr_ref;
  O_type *cb_out_ptr, *cb_out_ptr_ref;
  O_type *cr_out_ptr, *cr_out_ptr_ref;

  int *inp = &in_data[0];
  O_type *outp = &out_data[0];

  /* Compute the overhead of calling clock twice to get timing info. */
  t_start    = clock();
  t_stop     = clock();
  t_overhead = t_stop - t_start;

  /* Read test parameters. */
  align_in    = *inp++;
  align_out   = *inp++;

  src_ptr    		= (I_type *)( (unsigned int)&input[PAD]  + align_in );
  y_out_ptr  		= (O_type *)( (unsigned int)&y_out[PAD] + align_out);
  y_out_ptr_ref = (O_type *)( (unsigned int)&y_out_ref[PAD] + align_out);

  cr_out_ptr  =    (O_type *)( (unsigned int)&cr_out[PAD] + align_out);
  cr_out_ptr_ref = (O_type *)( (unsigned int)&cr_out_ref[PAD] + align_out);

  cb_out_ptr  =    (O_type *)( (unsigned int)&cb_out[PAD] + align_out);
  cb_out_ptr_ref = (O_type *)( (unsigned int)&cb_out_ref[PAD] + align_out);

  for(count = 1; count <= testcases; count++)
  {
    /* Read test-case params. */
    num_luma = *inp++;
    in_size  = *inp++;
    out_size_y = *inp++;
    out_size_c = *inp++;

    /* Checking sanity of generated driver. */
    if( N < in_size )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      return(0);
    }

    /* Prepare output arrays */
    memset(input, 0, sizeof(input));
    memset(y_out, 0, sizeof(y_out));
    memset(y_out_ref,  0, sizeof(y_out_ref));
    memset(cr_out,     0, sizeof(cr_out));
    memset(cr_out_ref, 0, sizeof(cr_out_ref));
    memset(cb_out,     0, sizeof(cb_out));
    memset(cb_out_ref, 0, sizeof(cb_out_ref));

    /* Copy input and ref output to respective buffers */
    copy_int_to_uchar(src_ptr, inp, in_size);   // copy input
    inp += in_size;

    memcpy(y_out_ptr_ref, outp, out_size_y * sizeof(outp[0]));
    outp += out_size_y;
    memcpy(cr_out_ptr_ref, outp, out_size_c * sizeof(outp[0]));
    outp += out_size_c;
    memcpy(cb_out_ptr_ref, outp, out_size_c * sizeof(outp[0]));
    outp += out_size_c;

    /* run the testcase */
    t1 = clock();
    IMG_yc_demux_be16_8 (num_luma, src_ptr, y_out_ptr, cr_out_ptr, cb_out_ptr);
    t2 = clock();
    t_c = t2 - t1 - t_overhead;

    if( memcmp(y_out, y_out_ref, sizeof(y_out_ref) ))
    {
      printf("Result failure: y_out - intrinsics: case # %d\n", count);
      return(0);
    }
		if( memcmp(cr_out, cr_out_ref, sizeof(cr_out_ref) ))
    {
      printf("Result failure: cr_out - intrinsics: case # %d\n", count);
      return(0);
    }
    if( memcmp(cb_out, cb_out_ref, sizeof(cb_out_ref) ))
    {
      printf("Result failure: cb_out - intrinsics: case # %d\n", count);
      return(0);
    }

		/* Test for natural C */
    memset(y_out,  0, sizeof(y_out));
    memset(cr_out, 0, sizeof(cr_out));
    memset(cb_out, 0, sizeof(cb_out));

    t1 = clock();
    IMG_yc_demux_be16_8_cn (num_luma, src_ptr, y_out_ptr, cr_out_ptr, cb_out_ptr);
    t2 = clock();
    t_cn = t2 - t1 - t_overhead;

    if( memcmp(y_out, y_out_ref, sizeof(y_out_ref) ))
    {
      printf("Result failure: y_out - nat c: case # %d\n", count);
      return(0);
    }
		if( memcmp(cr_out, cr_out_ref, sizeof(cr_out_ref) ))
    {
      printf("Result failure: cr_out - nat c: case # %d\n", count);
      return(0);
    }
    if( memcmp(cb_out, cb_out_ref, sizeof(cb_out_ref) ))
    {
      printf("Result failure: cb_out - nat c: case # %d\n", count);
      return(0);
    }

    printf("%2d : C = %4d, natC = %4d\n", count, t_c, t_cn);

  } /* for */

  printf("Success. Test suite (%d cases) passed.\n", testcases);

  return(0);
}

