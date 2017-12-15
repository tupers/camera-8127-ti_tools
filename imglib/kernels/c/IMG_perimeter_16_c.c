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
/*      IMG_perimeter_16                                                    */
/*                Natural C implementation for 16-bit                       */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function is C callable, and has the following prototype:       */
/*                                                                          */
/*          int IMG_perimeter_16                                            */
/*          (                                                               */
/*              const unsigned short *restrict in,  // Input image    //    */
/*              int cols,                           // Width of input //    */
/*              unsigned short       *restrict out  // Output image   //    */
/*          );                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function returns the boundary pixels of an image.              */
/*      Each call of perimeter() calculates one new line of output          */
/*      from a three line window of input.                                  */
/*                                                                          */
/*      The input pointer "in" points to the middle line of a three-line    */
/*      window of the image.  The perimeter function scans this window      */
/*      looking for pixels in the middle row which are on the perimeter     */
/*      of the image.  A pixel is on the perimeter of the image if          */
/*      the pixel itself is non-zero, but one of its neighbors is zero.     */
/*      The total count of perimeter pixels is returned.                    */
/*                                                                          */
/*      This particular implementation evaluates four neighbors for         */
/*      the perimeter test:  The neighbors to the left, right, top          */
/*      and bottom.                                                         */
/*                                                                          */
/*      Perimeter pixels retain their original grey level in the            */
/*      output.  Non-perimeter pixels are set to zero in the output.        */
/*      Pixels on the far left and right edges of a row are defined         */
/*      as *not* being on the perimeter, and are always forced to           */
/*      zero.                                                               */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. 'cols' should be a multiple of 8                                 */
/*      2. input and output arrays should not overlap.                      */
/*      3. input and output arrays should be double word aligned.           */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*     The code is compatible with both C64x and C64x+                      */
/*                                                                          */
/*  SOURCE                                                                  */
/*     The algorithm is obtained from IMG_perimeter in IMGLIB               */
/*                                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "host_build.h"

#pragma CODE_SECTION(IMG_perimeter_16_cn,   ".text:ansi");

int IMG_perimeter_16_cn
(
    const unsigned short *restrict  in, 
    int 						  cols, 
    unsigned short       *restrict out 
) 
{
 
    unsigned short      pix_lft,    pix_rgt,    pix_top; 
    unsigned short      pix_mid,    pix_bot;
    int                 i,          count;  

    count = 0;  
  
    for(i = 0; i < cols; i++)
    {
        pix_lft = in[i - 1];
        pix_mid = in[i];
        pix_rgt = in[i + 1];
                   
        pix_top = in[i - cols];
        pix_bot = in[i + cols];

        if (((pix_lft == 0) || (pix_rgt == 0) ||
             (pix_top == 0) || (pix_bot == 0)) && (pix_mid > 0))
        {
            out[i] = pix_mid;
            count++;
        } 
        else
        {
            out[i] = 0;
        }
    }
    if (out[cols - 1]) 
    count--;
    if (out[0])      
    count--;

    out[0]      = 0;
    out[cols - 1] = 0;

    return count;
}

/* ======================================================================== */
/*  End of file:  IMG_perimeter_16_c.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
