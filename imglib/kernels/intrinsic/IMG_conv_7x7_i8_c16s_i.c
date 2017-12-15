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
/*      IMG_conv_7x7_i8_c16s -> Intrinsic C Implementation                  */
/*      7x7 convolution for 8-bit input, 16-bit masks and 8-bit output      */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_conv_7x7_i8_c16s                                       */
/*          (                                                               */
/*              const unsigned char  *restrict   imgin_ptr,                 */
/*                    unsigned char  *restrict  imgout_ptr,                 */
/*                             short                 width,                 */
/*                             short                 pitch,                 */
/*              const          short  *restrict    mask_ptr,                */
/*                             short                 shift                  */
/*          )                                                               */
/*                                                                          */
/*      imgin_ptr :   pointer to an input  array of 8 bit pixels            */
/*      imgout_ptr:   pointer to an output array of 8 bit pixels            */
/*      pitch     :   number of columns in the image                        */
/*      width     :   number of output pixels                               */
/*      mask_ptr  :   pointer to 16 bit filter mask.                        */
/*      shift     :   user specified shift amount                           */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The convolution kernel accepts seven rows of 'pitch' input pixels   */
/*      and produces one row of 'width' output pixels using the input       */
/*      mask of 7 by 7. This convolution performs a point by point mult-    */
/*      iplication of 7 by 7 mask with the input image. The result of 49    */
/*      multiplications are then summed together to produce a 32-bit conv-  */
/*      olution intermediate sum. The user defined shift value is used to   */
/*      shift this convolution sum, down to the byte range and stored in    */
/*      output array. The result being stored is also range limited between */
/*      0 to 255 and will be saturated accordingly. The mask is moved one   */
/*      column at a time, advancing the mask over the entire image until    */
/*      the entire 'width' is covered. The masks are provided as 16-bit     */
/*      signed values. The input image pixels are provided as 8-bit uns-    */
/*      igned pixels and the output pixels will be in 8-bit unsigned.       */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. width:          'width' >= 2 and multiple of 2.                  */
/*      2. pitch:          'pitch' >= 'width'                               */
/*      3. Input and Output arrays should not overlap.                      */
/*      4. Output array should be word-aligned.                             */
/*      5. Mask pointer should be half-word aligned.                        */
/*      6. No restrictions on the alignment of Input arrays.                */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible for c64x+                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_conv_7x7_i8_c16s,   ".text:intrinsic");


void IMG_conv_7x7_i8_c16s
(
    const unsigned char *restrict  imgin_ptr,
    unsigned char       *restrict imgout_ptr,
    short                              width,
    short                              pitch,
    const          short *restrict  mask_ptr,
    int                                shift 
)
{
   int                  i,          k;  
   int                  sum1,       sum2;
   int                  temp;
   long long            r1;
   long long            temp1,      temp2,      temp3;
   long long            row_3210,   row_7654;

   double               mask00,     mask01;
   double               temp4; 

   unsigned int         sum21;     

   const unsigned char  *in; 

  
    /* -------------------------------------------------------------------- */
    /*  Inform the compiler by _nasserts the following:                     */
    /*      a) The output array is dword aligned                            */
    /*      c) The width is greater than or equal to 2                      */
    /*      b) The width is a multiple of 2.                                */
    /* -------------------------------------------------------------------- */

    _nassert((int)imgout_ptr % 4 == 0);          
    _nassert(width           % 2 == 0);
    _nassert(width               >= 2);

    /* -------------------------------------------------------------------- */
    /*  Loop is manually unrolled by 2.                                     */
    /* -------------------------------------------------------------------- */

    #pragma MUST_ITERATE(1, ,1)
    for (i = 0; i < width ; i += 2)
    {

     /* ------------------------------------------------------------------- */
     /* Introduce a pointer to point to the ith input image pixel within    */
     /* the iteration. Also set accumulator to user defined value for two   */
     /* output samples                                                      */
     /* ------------------------------------------------------------------- */

     in        =    &imgin_ptr[i];
     sum1      =    0;
     sum2      =    0;

    /* -------------------------------------------------------------------- */
    /*  This loop calculates the convolution sum for a single row           */
    /* -------------------------------------------------------------------- */

     #pragma MUST_ITERATE(7,7,7);
     
     for(k = 0;k < 7; k++)      
        {

          /* -------------------------------------------------------------- */
          /* Load 8 pixels that can be used to calculate two output pixels  */
          /* from the kth row                                               */
          /* -------------------------------------------------------------- */
         
          r1    =   _mem8_const( ( void * ) &in[k * pitch ]);
         

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_3210      =   _itoll(_unpkhu4(_loll(r1)),_unpklu4(_loll(r1)) );
          row_7654      =   _itoll(_unpkhu4(_hill(r1)),_unpklu4(_hill(r1)) );

          /* -------------------------------------------------------------- */
          /*  Load the 7 mask values                                        */
          /* -------------------------------------------------------------- */

          mask00        =   _memd8( ( void * ) &mask_ptr[k * 7    ] );
          mask01        =   _memd8( ( void * ) &mask_ptr[k * 7 + 4] );

          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1         =   _ddotpl2(row_3210,_lo(mask00));

          temp2         =   _ddotpl2(_itoll(_loll(row_7654),
                            _hill(row_3210) ),_hi(mask00));

          temp3         =   _ddotpl2(row_7654,_lo(mask01));

          temp          =   _pack2(_hi(mask01),_hi(mask01));

          temp4         =   _mpy2(_hill(row_7654) , temp);

          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the sums for two output    */
          /* pixels                                                         */
          /* -------------------------------------------------------------- */

          sum1  += (_loll(temp1) + _loll(temp2) + _loll(temp3) + _lo(temp4));
          sum2  += (_hill(temp1) + _hill(temp2) + _hill(temp3) + _hi(temp4));  
          
      
        }
      
      /* ------------------------------------------------------------------ */
      /* shift the sum to fall in byte range with user defined value        */
      /* ------------------------------------------------------------------ */
      
      sum1      =   sum1 >> shift;
      sum2      =   sum2 >> shift; 
       
      /* ------------------------------------------------------------------ */
      /* check for saturation and pack the two bytes to store using amem2   */
      /* ------------------------------------------------------------------ */
      
      sum21     =   _spacku4(0, _spack2(sum2, sum1));  

      _amem2((void*)&imgout_ptr[i])     =   (short)sum21;

   }
 }

/* ======================================================================== */
/*  End of file:  IMG_conv_7x7_i8_c16s_i.c                                  */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


