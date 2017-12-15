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
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_pix_sat -- 16 to 8 bit conversion                               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_pix_sat                                                    */
/*      (                                                                   */
/*          int Size,                         // Number of pixels //        */
/*          const short   *restrict in_data,  // Incoming data    //        */
/*          unsigned char *restrict out_data  // Outgoing data    //        */
/*      )                                                                   */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*      The function IMG_pix_sat() takes signed 16-bit input pixels and     */
/*      saturates them to unsigned 8-bit results.  Pixel values above       */
/*      255 are clamped to 255, and values below 0 are clamped to 0.        */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#pragma CODE_SECTION(IMG_pix_sat_cn, ".text:ansi");

#include "host_build.h"
#include "IMG_pix_sat_c.h"

void IMG_pix_sat_cn
(
    int                     n,
    const short   *restrict in_data,
    unsigned char *restrict out_data
)
{
    int i, pixel;

#ifndef NOASSUME
    _nassert((int) in_data % 8 == 0);
    _nassert((int)out_data % 8 == 0);
    #pragma MUST_ITERATE(0,,32);
#endif

    for (i = 0; i < n; i++)
    {
        pixel = in_data[i];
        if (pixel > 0xFF) 
        {
            out_data[i] = 0xFF;
        } else if (pixel < 0x00)
        {
            out_data[i] = 0x00;
        } else
        {
            out_data[i] = pixel;
        }
    }
}

/* ======================================================================== */
/*  End of file: IMG_pix_sat_c.c                                            */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
