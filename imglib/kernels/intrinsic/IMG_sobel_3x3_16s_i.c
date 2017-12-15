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
/*      IMG_sobel_3x3_16s - sobel 3x3 for 16bit signed input.               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_sobel_3x3_16s                                              */
/*      (                                                                   */
/*          const short *restrict  in,  // Input image data  //             */
/*                short *restrict  out, // Output image data //             */
/*                short           cols, // Image columns     //             */
/*                short           rows  // Image rows        //             */
/*      )                                                                   */
/*                                                                          */
/*      The sobel filter is applied to the input image.  The input image    */
/*      dimensions are given by the arguments 'cols' and 'rows'.  The       */
/*      output image is 'cols' pixels wide and 'rows - 2' pixels tall.      */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*      To see how the implementation is going to work on the input         */
/*      buffer, lets imagine we have the following input buffer:            */
/*      lets imagine we have the following input buffer:                    */
/*                                                                          */
/*              yyyyyyyyyyyyyyyy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yyyyyyyyyyyyyyyy                                            */
/*                                                                          */
/*      The output buffer would be:                                         */
/*                                                                          */
/*              tXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXt                                            */
/*                                                                          */
/*      Where:                                                              */
/*                                                                          */
/*          X = sobel(x)    The algorithm is applied to that pixel.         */
/*                          The correct output is obtained, the data        */
/*                          around the pixels we work on is used            */
/*                                                                          */
/*          t               Whatever was in the output buffer in that       */
/*                          position is kept there.                         */
/*                                                                          */
/*          z = sobel(y)    The algorithm is applied to that pixel.         */
/*                          The output is not meaningful, because the       */
/*                          necessary data to process the pixel is not      */
/*                          available.  This is because for each output     */
/*                          pixel we need input pixels from the right and   */
/*                          from the left of the output pixel.  But this    */
/*                          data doesn't exist.                             */
/*                                                                          */
/*      This means that we will only process (rows-2) lines.  Then, we      */
/*      will process all the pixels inside each line. Even though the       */
/*      results for the first and last pixels in each line will not         */
/*      be relevant, it makes the control much simpler and ends up          */
/*      saving cycles.                                                      */
/*                                                                          */
/*      Also the first pixel in the first processed line and the            */
/*      last pixel in the last processed line will not be computed.         */
/*      It is not necessary, since the results would be bogus.              */
/*                                                                          */
/*      The following horizontal and vertical masks that are                */
/*      applied to the input buffer to obtain one output pixel.             */
/*                                                                          */
/*          Horizontal:                                                     */
/*              -1 -2 -1                                                    */
/*               0  0  0                                                    */
/*               1  2  1                                                    */
/*                                                                          */
/*          Vertical:                                                       */
/*              -1  0  1                                                    */
/*              -2  0  2                                                    */
/*              -1  0  1                                                    */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. cols :     'cols' >  3 and multiple of 2.                        */
/*      2. rows :     'rows' >= 3 .                                         */
/*      3. Input and outpur arrays do not overlap.                          */
/*      4. Input and Output arrays have no alignment requirements.          */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible with C64x+ processors only.                 */
/*                                                                          */
/*  SOURCE                                                                  */
/*      The algorithm is taken from sobel in IMGLIB                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_sobel_3x3_16s,   ".text:intrinsic");


void IMG_sobel_3x3_16s
(
    const short *restrict   in,  /* Input image data   */
          short *restrict  out,  /* Output image data  */
          short           cols,  /* image columns      */
          short           rows   /* Image rows         */
)
{
    int    i,         end;
    int    mult1,     mult2; 


    _nassert(cols                  >  3);  /* cols must be greater than 3  */
    _nassert(rows                  >= 3);  /* rows must be atleast 3       */ 
    _nassert(cols              % 2 == 0);  /* cols must be a multiple of 2 */
    _nassert(cols * (rows - 2) - 2 >= 2);  /* "end" is atleast 2           */ 

    /* -------------------------------------------------------------------- */
    /*                   Initialise multiplier elements.                    */
    /* -------------------------------------------------------------------- */
    mult1 = 0x00020002; /*    2  2    */
    
    mult2 = 0x010101ff; /* 1  1 -1 -1 */

    /* -------------------------------------------------------------------- */
    /*  Iterate over entire image as a single, continuous raster line.      */
    /* -------------------------------------------------------------------- */
    end        = (cols * (rows - 2) - 2);

    /* -------------------------------------------------------------------- */
    /* A manual unroll by 4 would need an "if" condition to be included in  */
    /* the body of the loop as "end" is not a multiple of 4.I would rather  */
    /* unroll manually by 2 and leave further unroll of 2 to the compiler   */
    /* -------------------------------------------------------------------- */

    #pragma UNROLL(2)
    for (i = 0; i < end; i += 2)
    {
        double       in1_d,     in2_d,     in3_d;

        int          t1;
        int          O1,        O2;
        int          H1,        H2;
        int          V1,        V2;
        double       db1,       db2;
        long long    dt1,       dt2,       dt3;
        long long    dt4,       dpk1,      dpk2;

        /* ---------------------------------------------------------------- */
        /*  Read in the required 3x3 region from the input.                 */
        /* ---------------------------------------------------------------- */

        in1_d  =  _memd8_const((void*)&in[i           ]);

        in2_d  =  _memd8_const((void*)&in[i +     cols]);

        in3_d  =  _memd8_const((void*)&in[i + 2 * cols]);

        /* ---------------------------------------------------------------- */
        /*   Pack the 1st and the 3rd row pixels of the same column  in an  */
        /*   integer using dpack2. dpack2 uses S-unit                       */
        /* ---------------------------------------------------------------- */

        dpk1   =  _dpack2(_lo(in1_d) , _lo(in3_d));/* col 1&2 for row 1&3 */
        dpk2   =  _dpack2(_hi(in1_d) , _hi(in3_d));/* col 3&4 for row 1&3 */

        db1    =  _mpy2(_lo(in2_d) , mult1);  /* multiply row-2 with 2    */
        db2    =  _mpy2(_hi(in2_d) , mult1);

        /* ---------------------------------------------------------------- */
        /* calculate dot product using ddotp4, lower 16bit consists of      */
        /* horizontal  and higher constitute vertical mask elements         */
        /* ---------------------------------------------------------------- */

        dt1    =  _ddotp4(_loll(dpk1) , mult2);
        dt2    =  _ddotp4(_hill(dpk1) , mult2);
        dt3    =  _ddotp4(_loll(dpk2) , mult2);
        dt4    =  _ddotp4(_hill(dpk2) , mult2);

        /* ---------------------------------------------------------------- */
        /*  Apply horizontal and vertical filter masks.  The final filter   */
        /*  output is the sum of the absolute values of these filters.      */
        /* ---------------------------------------------------------------- */

        H1     =  (_loll(dt1) + (_loll(dt2) << 1) + _loll(dt3));
        H2     =  (_loll(dt2) + (_loll(dt3) << 1) + _loll(dt4));

        V1     =  (_hill(dt3) - _lo(db1) + _lo(db2) - _hill(dt1));
        V2     =  (_hill(dt4) - _hi(db1) + _hi(db2) - _hill(dt2));

        /* ---------------------------------------------------------------- */
        /*               calculate the absolute values                      */
        /* ---------------------------------------------------------------- */
        H1     =  _abs(H1);
        H2     =  _abs(H2);

        V1     =  _abs(V1);
        V2     =  _abs(V2);

        /* ---------------------------------------------------------------- */
        /*       add horizontal and vertical coefficients                   */
        /* ---------------------------------------------------------------- */

        O1     =  (V1 + H1);
        O2     =  (V2 + H2);

        /* ---------------------------------------------------------------- */
        /*            perform saturation and store result                   */
        /* ---------------------------------------------------------------- */

        t1  =   _spack2(O2 , O1);

        _mem4((void * )&out[i + 1])  =   t1;

    }

}

/* ======================================================================== */
/*  End of file:  IMG_sobel_3x3_16s_i.c                                     */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
