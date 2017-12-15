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

#include "host_build.h"


uint32 _lnorm(int40 a)
{
  uint32 y32u;
  union reg40 a40,b40,m40;

  a40.x1 = a;

  y32u = 0;
  m40.x2u.hi = (uint8)MIN_INT40_HI >> 1;
  m40.x2u.lo = (uint32)MIN_INT40_LO >> 1;

  if(a40.x2.hi < 0)
    {
      b40.x2u.hi = ~a40.x2.hi;
      b40.x2u.lo = ~a40.x2.lo;
    }
  else
    {
      b40.x2u.hi = a40.x2.hi;
      b40.x2u.lo = a40.x2.lo;
    }

  if((b40.x2u.hi == 0) && (b40.x2u.lo == 0))
    return(39);

  while((b40.x2u.hi & m40.x2u.hi) != m40.x2u.hi)
    {
      b40.x2u.hi = (b40.x2u.hi << 1) | (b40.x2u.lo >> 31);
      b40.x2u.lo <<= 1;
      y32u++;
    }
  
  return(y32u);
} /* end of _lnorm() function */


