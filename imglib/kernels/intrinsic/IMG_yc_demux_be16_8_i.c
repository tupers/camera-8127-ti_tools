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
/*      IMG_yc_demux_be16_8 -- De-interleave a 4:2:2 BIG ENDIAN video       */
/*                 stream into three separate LITTLE ENDIAN 16-bit planes   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function is C callable, and is called as follows:              */
/*                                                                          */
/*      void IMG_yc_demux_be16_8                                            */
/*      (                                                                   */
/*          int n,                       // Number of luma pixels    //     */
/*          const unsigned char * yc,    // Interleaved luma/chroma  //     */
/*          short *restrict y,           // Luma plane (16-bit)      //     */
/*          short *restrict cr,          // Cr chroma plane (16-bit) //     */
/*          short *restrict cb           // Cb chroma plane (16-bit) //     */
/*      );                                                                  */
/*                                                                          */
/*      The input array 'yc' is expected to be an interleaved 4:2:2         */
/*      video stream.  The input is expected in BIG ENDIAN byte order       */
/*      within each 4-byte word.  This is consistent with reading the       */
/*      video stream from a word-oriented BIG ENDIAN device while the       */
/*      C6000 device is in a LITTLE ENDIAN configuration.                   */
/*                                                                          */
/*      In other words, the expected pixel order is:                        */
/*                                                                          */
/*                  Word 0           Word 1          Word 2                 */
/*             +---------------+---------------+---------------+--          */
/*       Byte# | 0   1   2   3 | 4   5   6   7 | 8   9  10  11 |...         */
/*             |cb0 y1  cr0 y0 |cb2 y3  cr2 y2 |cb4 y5  cr4 y4 |...         */
/*             +---------------+---------------+---------------+--          */
/*                                                                          */
/*      The output arrays 'y', 'cr', and 'cb' are expected to not           */
/*      overlap.  The de-interleaved pixels are written as half-words       */
/*      in LITTLE ENDIAN order.                                             */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function reads the byte-oriented pixel data, zero-extends      */
/*      it, and then writes it to the appropriate result array.  Both       */
/*      the luma and chroma values are expected to be unsigned.             */
/*                                                                          */
/*      The data is expected to be in an order consistent with reading      */
/*      byte oriented data from a word-oriented peripheral that is          */
/*      operating in BIG ENDIAN mode, while the CPU is in LITTLE ENDIAN     */
/*      mode.  This results in a pixel ordering which is not                */
/*      immediately obvious.  This function correctly reorders the          */
/*      pixel values so that further processing may proceed in LITTLE       */
/*      ENDIAN mode.                                                        */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      Input and output arrays are double-word aligned.                    */
/*      The input must be a multiple of 16 luma pixels long.                */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The loop has been unrolled a total of 16 times to allow for         */
/*      processing 8 pixels in each datapath.                               */
/*                                                                          */
/*      Double-word loads and stores maximize memory bandwidth              */
/*      utilization.                                                        */
/*                                                                          */
/*      This code uses _gmpy4() to ease the L/S/D unit bottleneck on        */
/*      ANDs.  The _gmpy4(value, 0x00010001) is equivalent to               */
/*      value & 0x00FF00FF, as long as the size field of GFPGFR is          */
/*      equal to 7.  (The polynomial does not matter.)                      */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_yc_demux_be16_8,   ".text:intrinsic");
#include "IMG_yc_demux_be16_8.h"
#include <c6x.h>

void IMG_yc_demux_be16_8
(
    int n,                               /* Number of luma pixels    */
    const unsigned char *restrict yc,    /* Interbeaved luma/chroma  */
    short         *restrict y,           /* Luma plane (8-bit)       */
    short         *restrict cr,          /* Cr chroma plane (8-bit)  */
    short         *restrict cb           /* Cb chroma plane (8-bit)  */
)
{                                          
    int i;                      
    unsigned gfpgfr;

    gfpgfr = GFPGFR;
    GFPGFR = 0x07000000;

    _nassert((int)yc % 8 == 0);
    _nassert((int)y  % 8 == 0);
    _nassert((int)cr % 8 == 0);
    _nassert((int)cb % 8 == 0);
#   pragma MUST_ITERATE(4,,2);
#   pragma UNROLL(2);
    for (i = 0; i < (n >> 3); i++)
    {                         
        /*  3   2   1   0  */
        /* y0  cr0 y1  cb0 */

        unsigned y6r6y7b6    = _amem4_const(&yc[16*i + 12]);
        unsigned y4r4y5b4    = _amem4_const(&yc[16*i +  8]);
        unsigned y2r2y3b2    = _amem4_const(&yc[16*i +  4]);
        unsigned y0r0y1b0    = _amem4_const(&yc[16*i +  0]);
                            
        unsigned r6b6        =        y6r6y7b6 & 0x00FF00FF;
        unsigned r4b4        =        y4r4y5b4 & 0x00FF00FF;
        unsigned r2b2        =        y2r2y3b2 & 0x00FF00FF;
        unsigned r0b0        = _gmpy4(y0r0y1b0,  0x00010001);
                            
        unsigned b6b4        = _pack2 (r6b6,r4b4);
        unsigned b2b0        = _pack2 (r2b2,r0b0);
        unsigned r6r4        = _packh2(r6b6,r4b4);
        unsigned r2r0        = _packh2(r2b2,r0b0);
                            
        unsigned y7y6        = _rotl(y6r6y7b6 & ~0x00FF00FF, 8);
        unsigned y5y4        = _rotl(y4r4y5b4 & ~0x00FF00FF, 8);
        unsigned y3y2        = _rotl(y2r2y3b2 & ~0x00FF00FF, 8);
        unsigned y1y0        = _rotl(y0r0y1b0 & ~0x00FF00FF, 8);

        _amemd8(&y[i*8 + 4]) = _itod(y7y6, y5y4);
        _amemd8(&y[i*8 + 0]) = _itod(y3y2, y1y0);

        _amemd8(&cb[i*4])    = _itod(b6b4, b2b0);
        _amemd8(&cr[i*4])    = _itod(r6r4, r2r0);
    }

    GFPGFR = gfpgfr;
}

/* ======================================================================== */
/*  End of file:  IMG_yc_demux_be16_8_i.c                                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
