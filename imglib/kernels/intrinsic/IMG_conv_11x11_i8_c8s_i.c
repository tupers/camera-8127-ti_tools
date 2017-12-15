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
/*      IMG_conv_11x11_i8_c8s -> Intrinsic C Implementation                 */
/*      11x11 convolution for 8-bit input, 8-bit masks and 8-bit output     */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_conv_11x11_i8_c8s                                      */
/*          (                                                               */
/*              const unsigned char  *restrict   imgin_ptr,                 */
/*                    unsigned char  *restrict  imgout_ptr,                 */
/*                             short                 width,                 */
/*                             short                 pitch,                 */
/*              const          char  *restrict    mask_ptr,                 */
/*                             short                 shift                  */
/*          )                                                               */
/*                                                                          */
/*      imgin_ptr :   pointer to an input  array of 8 bit pixels            */
/*      imgout_ptr:   pointer to an output array of 8 bit pixels            */
/*      width     :   number of output pixels                               */
/*      pitch     :   number of columns in the image                        */
/*      mask_ptr  :   pointer to 8 bit filter mask.                         */
/*      shift     :   user specified shift amount                           */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The convolution kernel accepts eleven rows of 'pitch' input pixels  */
/*      and produces one row of 'width' output pixels using the input       */
/*      mask of 11 by 11. This convolution performs a point by point mult-  */
/*      iplication of 11 by 11 mask with the input image. The result of 121 */
/*      multiplications are then summed together to produce a 32-bit conv-  */
/*      olution intermediate sum.The user defined shift value is used to    */
/*      shift this convolution sum down to the byte range and store in an   */
/*      output array. The result being stored is also range limited between */
/*      0 to 255 and will be saturated accordingly. The mask is moved one   */
/*      column at a time, advancing the mask over the entire image until    */
/*      the entire 'width' is covered.The input, output image pixels are    */
/*      provided as 8-bit unsigned while the masks are 8-bit signed.        */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. width:   'width' >=2 and a multiple of 2.                        */
/*      2. pitch:   'pitch' >= 'width'.                                     */
/*      3. Input and output arrays should not overlap                       */
/*      4. Output array should be word aligned                              */
/*      5. No restrictions on the alignment of mask and input arrays        */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      The code is compatible with both C64x+ and C64x                     */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_conv_11x11_i8_c8s, ".text:intrinsic");


void IMG_conv_11x11_i8_c8s
(
    const unsigned char    *restrict  imgin_ptr,
          unsigned char    *restrict imgout_ptr,
                   short                  width, 
                   short                  pitch, 
    const          char    *restrict   mask_ptr, 
                   short                  shift
)
{
   int              i,              k;  

   int              sum1,           sum2;    

   int              sum1_temp,      sum2_temp;
   int              mask11_8,       mask_temp;
   int              row11_8,        row_temp1,      row_temp2;
   int              mask_temp1,     mask_temp2,     mask_temp3;

   int              temp1,          temp2,          temp3;
   int              temp4,          temp5,          temp6;

   double           row7_0,         mask7_0;

   short            sum;


   const unsigned char  *in; 

   _nassert((int)imgout_ptr % 4 == 0);  /* Output word aligned              */
   _nassert((int)(width)    % 2 == 0);  /* output samples multiple of 2     */

   /* --------------------------------------------------------------------- */
   /*  Loop is manually unrolled by 2                                       */
   /* --------------------------------------------------------------------- */
    
   k = 0;

   #pragma MUST_ITERATE(1, ,1);
   for (i = 0; i < width ; i += 2)
   {

     /* ------------------------------------------------------------------- */
     /* Introduce a pointer to point to the ith input image pixel within    */
     /* the iteration. Also zero accumulator values for two output samples  */
     /* ------------------------------------------------------------------- */
     
     in             =   (&imgin_ptr[i]);
     sum1_temp      =   0;
     sum2_temp      =   0;

     /* ------------------------------------------------------------------- */
     /*  This loop calculates the convolution sum for a single row          */
     /* ------------------------------------------------------------------- */

     for(k = 0;k < 11; k++)      
        {

          /* -------------------------------------------------------------- */
          /* Load 12 pixels that can be used to calculate two output pixels */
          /* from the kth row                                               */
          /* -------------------------------------------------------------- */
          
          row7_0     =  _memd8_const( ( void * ) &in[k * pitch]);
          row11_8    =  _mem4_const( ( void * ) &in[k * pitch + 8]); 

          /* -------------------------------------------------------------- */
          /*  Load the 11 mask values to be used                            */
          /* -------------------------------------------------------------- */

          mask7_0    =   _memd8_const( ( void * ) &mask_ptr[k * 11]);
          mask11_8   =   _mem4_const( ( void * ) &mask_ptr[k * 11 + 8]);

          /* -------------------------------------------------------------- */
          /* Make 12th pixel zero for the first output sample and 1st pixel */
          /* zero for calculating the second output sample                  */
          /* -------------------------------------------------------------- */

          row_temp1  =   row11_8 & 0x00ffffff;
          row_temp2  =   _lo(row7_0)  & 0xffffff00;

          /* -------------------------------------------------------------- */
          /* Make 11th mask zero for the first output sample and calculate  */
          /* masks for computing second output samples                      */
          /* -------------------------------------------------------------- */

          mask_temp1 =   ( (unsigned) _lo( mask7_0) ) << 8;         
          mask_temp2 =   _shlmb(_lo( mask7_0),_hi(mask7_0));
          mask_temp3 =   _shlmb(_hi( mask7_0),mask11_8);
          mask_temp  =   mask11_8 & 0x00ffffff;
          
          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1      = _dotpsu4(_lo(mask7_0), _lo(row7_0));
          temp2      = _dotpsu4(_hi(mask7_0), _hi(row7_0));
          sum1_temp += temp1 + temp2;

          temp3      = _dotpsu4(mask_temp, row_temp1);
          temp4      = _dotpsu4(mask_temp1, row_temp2);

          sum1_temp += temp3;
          sum2_temp += temp4;
          
          temp5      = _dotpsu4(mask_temp2, _hi(row7_0));
          temp6      = _dotpsu4(mask_temp3, row11_8);
 
          sum2_temp += temp5 + temp6; 

        }

        /* ---------------------------------------------------------------- */
        /* shift the sum to fall in byte range with user defined value      */
        /* sum1 correponds to pixel1 and sum to corresponds to pixel2.      */
        /* ---------------------------------------------------------------- */

        sum1         =   (sum1_temp >> shift); 
        sum2         =   (sum2_temp >> shift); 

        /* ---------------------------------------------------------------- */
        /* check for saturation and pack the two bytes to store using _mem2 */
        /* ---------------------------------------------------------------- */
        
        sum          =   _spacku4(0, _spack2(sum2, sum1));

        _amem2(( void* ) &imgout_ptr[i]) = sum;
   }    
}

/* ======================================================================== */
/*  End of file:  IMG_conv_11x11_i8_c8s_i.c                                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
