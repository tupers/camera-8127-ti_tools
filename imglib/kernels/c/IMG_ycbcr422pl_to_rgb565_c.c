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
/*      IMG_ycbcr422pl_to_rgb565 -- Planarized YCbCr 4:2:2/4:2:0 to 16-bit  */
/*                              RGB 5:6:5 color space conversion.           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function is C callable, and is called according to this        */
/*      C prototype:                                                        */
/*                                                                          */
/*      void IMG_ycbcr422pl_to_rgb565                                       */
/*      (                                                                   */
/*        const short         coeff[5],  // Matrix coefficients.        //  */
/*        const unsigned char *y_data,   // Luminence data  (Y')        //  */
/*        const unsigned char *cb_data,  // Blue color-diff (B'-Y')     //  */
/*        const unsigned char *cr_data,  // Red color-diff  (R'-Y')     //  */
/*        unsigned short                                                    */
/*                   *restrict rgb_data, // RGB 5:6:5 packed pixel out. //  */
/*        unsigned            num_pixels // # of luma pixels to process //  */
/*      );                                                                  */
/*                                                                          */
/*      The 'coeff[]' array contains the color-space-conversion matrix      */
/*      coefficients.  The 'y_data', 'cb_data' and 'cr_data' pointers       */
/*      point to the separate input image planes.  The 'rgb_data' pointer   */
/*      points to the output image buffer.                                  */
/*                                                                          */
/*      The kernel is designed to process arbitrary amounts of 4:2:2        */
/*      image data, although 4:2:0 image data may be processed as well.     */
/*      For 4:2:2 input data, the 'y_data', 'cb_data' and 'cr_data'         */
/*      arrays may hold an arbitrary amount of image data, including        */
/*      multiple scan lines of image data.                                  */
/*                                                                          */
/*      For 4:2:0 input data, only a single scan-line (or portion           */
/*      thereof) may be processed at a time.  This is achieved by           */
/*      calling the function twice using the same row data for              */
/*      'cr_data' and 'cb_data', and providing new row data for             */
/*      'y_data'.  This is numerically equivalent to replicating the Cr     */
/*      and Cb pixels vertically.                                           */
/*                                                                          */
/*      The coefficients in the coeff array must be in signed Q13 form.     */
/*      These coefficients correspond to the following matrix equation:     */
/*                                                                          */
/*          [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']         */
/*          [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']         */
/*          [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']         */
/*                                                                          */
/*      The output from this kernel is 16-bit RGB in 5:6:5 format.          */
/*      The RGB components are packed into halfwords as shown below.        */
/*                                                                          */
/*                     15      11 10       5 4        0                     */
/*                    +----------+----------+----------+                    */
/*                    |   Red    |  Green   |   Blue   |                    */
/*                    +----------+----------+----------+                    */
/*                                                                          */
/*      This kernel can also return the red, green, and blue values in      */
/*      the opposite order if a particular application requires it.         */
/*      This is achieved by exchanging the 'cb_data' and 'cr_data'          */
/*      arguments when calling the function, and by reversing the order     */
/*      of coefficients in coeff[1] through coeff[4].  This essentially     */
/*      implements the following matrix multiply:                           */
/*                                                                          */
/*          [ coeff[0] 0.0000   coeff[4] ]   [ Y' -  16 ]     [ B']         */
/*          [ coeff[0] coeff[3] coeff[2] ] * [ Cr - 128 ]  =  [ G']         */
/*          [ coeff[0] coeff[1] 0.0000   ]   [ Cb - 128 ]     [ R']         */
/*                                                                          */
/*      The reversed RGB ordering output by this mode is as follows:        */
/*                                                                          */
/*                     15      11 10       5 4        0                     */
/*                    +----------+----------+----------+                    */
/*                    |   Blue   |  Green   |   Red    |                    */
/*                    +----------+----------+----------+                    */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This kernel performs Y'CbCr to RGB conversion.  From the Color      */
/*      FAQ, http://home.inforamp.net/~poynton/ColorFAQ.html :              */
/*                                                                          */
/*          Various scale factors are applied to (B'-Y') and (R'-Y')        */
/*          for different applications.  The Y'PbPr scale factors are       */
/*          optimized for component analog video.  The Y'CbCr scaling       */
/*          is appropriate for component digital video, JPEG and MPEG.      */
/*          Kodak's PhotoYCC(tm) uses scale factors optimized for the       */
/*          gamut of film colors.  Y'UV scaling is appropriate as an        */
/*          intermediate step in the formation of composite NTSC or PAL     */
/*          video signals, but is not appropriate when the components       */
/*          are keps separate.  Y'UV nomenclature is now used rather        */
/*          loosely, and it sometimes denotes any scaling of (B'-Y')        */
/*          and (R'-Y').  Y'IQ coding is obsolete.                          */
/*                                                                          */
/*      This code can perform various flavors of Y'CbCr to RGB              */
/*      conversion as long as the offsets on Y, Cb, and Cr are -16,         */
/*      -128, and -128, respectively, and the coefficients match the        */
/*      pattern shown.                                                      */
/*                                                                          */
/*      The kernel implements the following matrix form, which involves 5   */
/*      unique coefficients:                                                */
/*                                                                          */
/*          [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']         */
/*          [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']         */
/*          [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']         */
/*                                                                          */
/*                                                                          */
/*      Below are some common coefficient sets, along with the matrix       */
/*      equation that they correspond to.   Coefficients are in signed      */
/*      Q13 notation, which gives a suitable balance between precision      */
/*      and range.                                                          */
/*                                                                          */
/*      1.  Y'CbCr -> RGB conversion with RGB levels that correspond to     */
/*          the 219-level range of Y'.  Expected ranges are [16..235] for   */
/*          Y' and [16..240] for Cb and Cr.                                 */
/*                                                                          */
/*          coeff[] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };         */
/*                                                                          */
/*          [ 1.0000    0.0000    1.3707 ]   [ Y' -  16 ]     [ R']         */
/*          [ 1.0000   -0.3365   -0.6982 ] * [ Cb - 128 ]  =  [ G']         */
/*          [ 1.0000    1.7324    0.0000 ]   [ Cr - 128 ]     [ B']         */
/*                                                                          */
/*      2.  Y'CbCr -> RGB conversion with the 219-level range of Y'         */
/*          expanded to fill the full RGB dynamic range.  (The matrix       */
/*          has been scaled by 255/219.)  Expected ranges are [16..235]     */
/*          for Y' and [16..240] for Cb and Cr.                             */
/*                                                                          */
/*          coeff[] = { 0x2543, 0x3313, -0x0C8A, -0x1A04, 0x408D };         */
/*                                                                          */
/*          [ 1.1644    0.0000    1.5960 ]   [ Y' -  16 ]     [ R']         */
/*          [ 1.1644   -0.3918   -0.8130 ] * [ Cb - 128 ]  =  [ G']         */
/*          [ 1.1644    2.0172    0.0000 ]   [ Cr - 128 ]     [ B']         */
/*                                                                          */
/*      3.  Y'CbCr -> BGR conversion with RGB levels that correspond to     */
/*          the 219-level range of Y'.  This is equivalent to #1 above,     */
/*          except that the R, G, and B output order in the packed          */
/*          pixels is reversed.  Note:  The 'cr_data' and 'cb_data'         */
/*          input arguments must be exchanged for this example as           */
/*          indicated under USAGE above.                                    */
/*                                                                          */
/*          coeff[] = { 0x2000, 0x3770, -0x1658, -0x0AC5, 0x2BDD };         */
/*                                                                          */
/*          [ 1.0000    0.0000    1.7324 ]   [ Y' -  16 ]     [ B']         */
/*          [ 1.0000   -0.6982   -0.3365 ] * [ Cr - 128 ]  =  [ G']         */
/*          [ 1.0000    1.3707    0.0000 ]   [ Cb - 128 ]     [ R']         */
/*                                                                          */
/*      4.  Y'CbCr -> BGR conversion with the 219-level range of Y'         */
/*          expanded to fill the full RGB dynamic range.  This is           */
/*          equivalent to #2 above, except that the R, G, and B output      */
/*          order in the packed pixels is reversed.  Note:  The             */
/*          'cr_data' and 'cb_data' input arguments must be exchanged       */
/*          for this example as indicated under USAGE above.                */
/*                                                                          */
/*          coeff[] = { 0x2000, 0x408D, -0x1A04, -0x0C8A, 0x3313 };         */
/*                                                                          */
/*          [ 1.0000    0.0000    2.0172 ]   [ Y' -  16 ]     [ B']         */
/*          [ 1.0000   -0.8130   -0.3918 ] * [ Cr - 128 ]  =  [ G']         */
/*          [ 1.0000    1.5960    0.0000 ]   [ Cb - 128 ]     [ R']         */
/*                                                                          */
/*      Other scalings of the color differences (B'-Y') and (R'-Y')         */
/*      (sometimes incorrectly referred to as U and V) are supported, as    */
/*      long as the color differences are unsigned values centered around   */
/*      128 rather than signed values centered around 0, as noted above.    */
/*                                                                          */
/*      In addition to performing plain color-space conversion, color       */
/*      saturation can be adjusted by scaling coeff[1] through coeff[4].    */
/*      Similarly, brightness can be adjusted by scaling coeff[0].          */
/*      General hue adjustment can not be performed, however, due to the    */
/*      two zeros hard-coded in the matrix.                                 */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      Pixel replication is performed implicitly on chroma data to         */
/*      reduce the total number of multiplies required.  The chroma         */
/*      portion of the matrix is calculated once for each Cb, Cr pair,      */
/*      and the result is added to both Y' samples.                         */
/*                                                                          */
/*  SOURCE                                                                  */
/*      Poynton, Charles et al.  "The Color FAQ,"  1999.                    */
/*          http://home.inforamp.net/~poynton/ColorFAQ.html                 */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#pragma CODE_SECTION(IMG_ycbcr422pl_to_rgb565_cn, ".text:ansi");

#include "host_build.h"

void IMG_ycbcr422pl_to_rgb565_cn
(
    const short             coeff[5],   /* Matrix coefficients.             */
    const unsigned char     *y_data,    /* Luminence data        (Y')       */
    const unsigned char     *cb_data,   /* Blue color-difference (B'-Y')    */
    const unsigned char     *cr_data,   /* Red color-difference  (R'-Y')    */
    unsigned short *restrict rgb_data,  /* RGB 5:6:5 packed pixel output.   */
    unsigned                num_pixels  /* # of luma pixels to process.     */
)
{
    int     i;                      /* Loop counter                     */
    int     y0, y1;                 /* Individual Y components          */
    int     cb, cr;                 /* Color difference components      */
    int     y0t,y1t;                /* Temporary Y values               */
    int     rt, gt, bt;             /* Temporary RGB values             */
    int     r0, g0, b0;             /* Individual RGB components        */
    int     r1, g1, b1;             /* Individual RGB components        */
    int     r0t,g0t,b0t;            /* Truncated RGB components         */
    int     r1t,g1t,b1t;            /* Truncated RGB components         */
    int     r0s,g0s,b0s;            /* Saturated RGB components         */
    int     r1s,g1s,b1s;            /* Saturated RGB components         */

    short   luma = coeff[0];        /* Luma scaling coefficient.        */
    short   r_cr = coeff[1];        /* Cr's contribution to Red.        */
    short   g_cb = coeff[2];        /* Cb's contribution to Green.      */
    short   g_cr = coeff[3];        /* Cr's contribution to Green.      */
    short   b_cb = coeff[4];        /* Cb's contribution to Blue.       */

    unsigned short  rgb0, rgb1;     /* Packed RGB pixel data            */

    /* -------------------------------------------------------------------- */
    /*  Iterate for num_pixels/2 iters, since we process pixels in pairs.   */
    /* -------------------------------------------------------------------- */
    i = num_pixels >> 1; 

    while (i-->0)
    {
        /* ---------------------------------------------------------------- */
        /*  Read in YCbCr data from the separate data planes.               */
        /*                                                                  */
        /*  The Cb and Cr channels come in biased upwards by 128, so        */
        /*  subtract the bias here before performing the multiplies for     */
        /*  the color space conversion itself.  Also handle Y's upward      */
        /*  bias of 16 here.                                                */
        /* ---------------------------------------------------------------- */

        y0 = *y_data++  - 16;
        y1 = *y_data++  - 16;
        cb = *cb_data++ - 128;
        cr = *cr_data++ - 128;

        /* ================================================================ */
        /*  Convert YCrCb data to RGB format using the following matrix:    */
        /*                                                                  */
        /*      [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']     */
        /*      [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']     */
        /*      [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']     */
        /*                                                                  */
        /*  We use signed Q13 coefficients for the coefficients to make     */
        /*  good use of our 16-bit multiplier.  Although a larger Q-point   */
        /*  may be used with unsigned coefficients, signed coefficients     */
        /*  add a bit of flexibility to the kernel without significant      */
        /*  loss of precision.                                              */
        /* ================================================================ */

        /* ---------------------------------------------------------------- */
        /*  Calculate chroma channel's contribution to RGB.                 */
        /* ---------------------------------------------------------------- */
        rt  = r_cr * (short)cr;
        gt  = g_cb * (short)cb + g_cr * (short)cr;
        bt  = b_cb * (short)cb;

        /* ---------------------------------------------------------------- */
        /*  Calculate intermediate luma values.  Include bias of 16 here.   */
        /* ---------------------------------------------------------------- */
        y0t = luma * (short)y0;
        y1t = luma * (short)y1;
        
        /* ---------------------------------------------------------------- */
        /*  Mix luma, chroma channels.                                      */
        /* ---------------------------------------------------------------- */
        r0  = y0t + rt; r1 = y1t + rt;
        g0  = y0t + gt; g1 = y1t + gt;
        b0  = y0t + bt; b1 = y1t + bt;

        /* ================================================================ */
        /*  At this point in the calculation, the RGB components are        */
        /*  nominally in the format below.  If the color is outside the     */
        /*  our RGB gamut, some of the sign bits may be non-zero,           */
        /*  triggering saturation.                                          */
        /*                                                                  */
        /*                  3     2 2        1 1                            */
        /*                  1     1 0        3 2         0                  */
        /*                 [ SIGN  | COLOR    | FRACTION ]                  */
        /*                                                                  */
        /*  This gives us an 8-bit range for each of the R, G, and B        */
        /*  components.  (The transform matrix is designed to transform     */
        /*  8-bit Y/C values into 8-bit R,G,B values.)  To get our final    */
        /*  5:6:5 result, we "divide" our R, G and B components by 4, 8,    */
        /*  and 4, respectively, by reinterpreting the numbers in the       */
        /*  format below:                                                   */
        /*                                                                  */
        /*          Red,    3     2 2     1 1                               */
        /*          Blue    1     1 0     6 5            0                  */
        /*                 [ SIGN  | COLOR | FRACTION    ]                  */
        /*                                                                  */
        /*                  3     2 2      1 1                              */
        /*          Green   1     1 0      5 4           0                  */
        /*                 [ SIGN  | COLOR  | FRACTION   ]                  */
        /*                                                                  */
        /*  "Divide" is in quotation marks because this step requires no    */
        /*  actual work.  The code merely treats the numbers as having a    */
        /*  different Q-point.                                              */
        /* ================================================================ */

        /* ---------------------------------------------------------------- */
        /*  Shift away the fractional portion, and then saturate to the     */
        /*  RGB 5:6:5 gamut.                                                */
        /* ---------------------------------------------------------------- */
        r0t = r0 >> 16;
        g0t = g0 >> 15;
        b0t = b0 >> 16;
        r1t = r1 >> 16;
        g1t = g1 >> 15;
        b1t = b1 >> 16;

        r0s = r0t < 0 ? 0 : r0t > 31 ? 31 : r0t;
        g0s = g0t < 0 ? 0 : g0t > 63 ? 63 : g0t;
        b0s = b0t < 0 ? 0 : b0t > 31 ? 31 : b0t;
        r1s = r1t < 0 ? 0 : r1t > 31 ? 31 : r1t;
        g1s = g1t < 0 ? 0 : g1t > 63 ? 63 : g1t;
        b1s = b1t < 0 ? 0 : b1t > 31 ? 31 : b1t;

        /* ---------------------------------------------------------------- */
        /*  Merge values into output pixels.                                */
        /* ---------------------------------------------------------------- */
        rgb0 = (r0s << 11) + (g0s <<  5) + (b0s <<  0);
        rgb1 = (r1s << 11) + (g1s <<  5) + (b1s <<  0);

        /* ---------------------------------------------------------------- */
        /*  Store resulting pixels to memory.                               */
        /* ---------------------------------------------------------------- */
        *rgb_data++ = rgb0;
        *rgb_data++ = rgb1;
    } 

    return;
}

/* ======================================================================== */
/*  End of file:  IMG_ycbcr422pl_to_rgb565_c.c                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
