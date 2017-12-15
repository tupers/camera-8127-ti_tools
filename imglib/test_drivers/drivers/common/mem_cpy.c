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

/* ======================================================================= */

#include <stdio.h>
#include "mem_cpy.h"

void copy_int_to_char(char *restrict dst, int *restrict src, int elements)
{
  int i;

  for(i = 0; i < elements; i++)
    dst[i] = src[i] & 0xFF;

}


void copy_int_to_short(short *restrict dst, int *restrict src, int elements)
{
  int i;
  int dat_out;
  char *char_dst = (char *)dst; // For non-aligned memory.

  for(i = 0; i < elements; i++)
  {
    dat_out = src[i];
    *char_dst++ = dat_out & 0xFF;
    *char_dst++ = dat_out >> 8;
  }
}


void copy_int_to_int(int *restrict dst, int *restrict src, int elements)
{
  memcpy(dst, src, elements * sizeof(int));
}


void copy_int_to_uchar(unsigned char *restrict dst, int *restrict src, int elements)
{
  copy_int_to_char( (char *)dst, src, elements);
}


void copy_int_to_ushort(unsigned short *restrict dst, int *restrict src, int elements)
{
  copy_int_to_short( (short *)dst, src, elements);
}


void copy_int_to_uint(unsigned int *restrict dst, int *restrict src, int elements)
{
  copy_int_to_int( (int *)dst, src, elements);
}





/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


