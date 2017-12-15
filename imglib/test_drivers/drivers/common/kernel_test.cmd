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
/*  TEXAS INSTRUMENTS, INC.                                                */
/* ----------------------------------------------------------------------- */
/*  Da-vinci command file                                                  */
/* ======================================================================= */

-stack 0x2000
-heap 0x10000

MEMORY
{
    L1DRAM      o = 0x11F04000 l = 0xc000
    DDR         o = 0x80000000 l = 0x1000000
}

SECTIONS
{
   .csl_vect > DDR

   .sysmem > DDR
   .text   > DDR
   .bss    > DDR
   .switch > DDR
   .cinit  > DDR
   .data   > DDR
   .const  > DDR
   .far    > DDR
   .stack  > DDR
   .cio    > DDR
   .reset  > DDR
   .fardata > DDR
    
    GROUP (NEAR_DP_RELATIVE)
    {
       .neardata
       .rodata
       .bss
      } > DDR
}

/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
