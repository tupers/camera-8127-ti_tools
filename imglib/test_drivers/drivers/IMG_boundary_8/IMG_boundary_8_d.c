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
#include "IMG_boundary_8.h"
#include "IMG_boundary_8_c.h"

#define N 400
#define PAD 64
#define SIZE (N + 2*PAD)
unsigned char input_1[SIZE];
int coord[SIZE], ref_coord[SIZE];
int grey[SIZE], ref_grey[SIZE];

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern int out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */

main()
{
  clock_t t_start, t_stop, t_overhead, t1, t2, t_c, t_cn;
  int count;
  int in_size, out_size;
  int rows, cols;
  short align_in, align_out;
  unsigned char *src_ptr_1;
  int *coord_ptr, *ref_coord_ptr;
  int *grey_ptr, *ref_grey_ptr;

  int *inp = &in_data[0];
  int *outp = &out_data[0];

  /* Compute the overhead of calling clock twice to get timing info. */
  t_start    = clock();
  t_stop     = clock();
  t_overhead = t_stop - t_start;

  align_in  = *inp++;
  align_out = *inp++;

  src_ptr_1 =     (unsigned char*)( (unsigned int)&input_1[PAD]  + align_in );
  coord_ptr =     (int *)( (unsigned int)&coord[PAD] + align_out);
  ref_coord_ptr = (int *)( (unsigned int)&ref_coord[PAD] + align_out);
  grey_ptr  =     (int *)( (unsigned int)&grey[PAD] + align_out);
  ref_grey_ptr =  (int *)( (unsigned int)&ref_grey[PAD] + align_out);

  for(count = 0; count < testcases; count++)
  {
    /* Read test-case params. */
    rows = *inp++;
    cols = *inp++;
    in_size  = *inp++;
    out_size = *inp++;

    /* Checking sanity of generated driver. */
    if( N < in_size )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      return(0);
    }

    /* Prepare output arrays */
    memset(coord, 0, sizeof(coord[0]) * SIZE);
    memset(grey,  0, sizeof(grey[0])  * SIZE);
    memset(ref_coord, 0, sizeof(ref_coord[0]) * SIZE);
    memset(ref_grey,  0, sizeof(ref_grey[0]) * SIZE);

    /* Copy input and ref output to respective buffers */
    copy_int_to_uchar(src_ptr_1, inp, in_size);
    inp += in_size;
    copy_int_to_int(ref_coord_ptr, outp, out_size);
    outp += out_size;
    copy_int_to_int(ref_grey_ptr, outp, out_size);
    outp += out_size;

    /* run the testcase */
    memset(coord, 0, sizeof(short) * SIZE);
    memset(grey, 0, sizeof(short) * SIZE);

    t1 = clock();
    IMG_boundary_8 (src_ptr_1, rows, cols, coord_ptr, grey_ptr );
    t2 = clock();

    t_c = t2 - t1 - t_overhead;

    if( memcmp(coord, ref_coord, SIZE * sizeof(ref_coord[0])) )
    {
      printf("Result failure: coord - intrinsics: case # %d\n", count);
      return(0);
    }

    if( memcmp(grey, ref_grey, SIZE * sizeof(ref_grey[0])) )
    {
      printf("Result failure: grey - intrinsics: case # %d\n", count);
      return(0);
    }


    memset(coord, 0, sizeof(short) * SIZE);
    memset(grey, 0, sizeof(short) * SIZE);

    t1 = clock();
    IMG_boundary_8_cn(src_ptr_1, rows, cols, coord_ptr, grey_ptr );
    t2 = clock();

    t_cn = t2 - t1 - t_overhead;

    if( memcmp(coord, ref_coord, SIZE * sizeof(ref_coord[0])) )
    {
      printf("Result failure: coord - natural c: case # %d\n", count);
      return(0);
    }

    if( memcmp(grey, ref_grey, SIZE * sizeof(ref_grey[0])) )
    {
      printf("Result failure: grey - natural c: case # %d\n", count);
      return(0);
    }

    printf("%2d : C = %4d, natC = %4d\n", count, t_c, t_cn);

  } /* for */

  printf("Success. Test suite (%d cases) passed.\n", testcases);

}

