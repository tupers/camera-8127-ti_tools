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
/*      IMG_conv_5x5_i8_c16s -> Intrinsic C Implementation                  */
/*      5x5 convolution for 8-bit input, 16-bit masks and 8-bit output      */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_conv_5x5_i8_c16s                                       */
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
/*      The convolution kernel accepts five rows of 'pitch' input pixels    */
/*      and produces one row of 'width' output pixels using the input       */
/*      mask of 5 by 5. This convolution performs a point by point mult-    */
/*      iplication of 5 by 5 mask with the input image. The result of 25    */
/*      multiplications are then summed together to produce a 32-bit conv-  */
/*      olution intermediate sum. The user defined shift value is used to   */
/*      shift this convolution sum, down to the byte range and store in an  */
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
/*      1. width:       'width' >= 2 and multiples of 2.                    */
/*      2. pitch:       'pitch' >= 'width'                                  */
/*      3. Filter Coefficient array should be half-word aligned             */
/*      4. Output array should be word-aligned.                             */
/*      5. No restrictions on the alignment of Input arrays                 */
/*      6. Input and Output arrays should not overlap.                      */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible for c64x+                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_conv_5x5_i8_c16s,   ".text:intrinsic");

union db_ll
{
    long long ll;
    double    db;
};  

void IMG_conv_5x5_i8_c16s
(
    const unsigned char *restrict  imgin_ptr,
    unsigned char       *restrict imgout_ptr,
    short                              width,
    short                              pitch,
    const          short *restrict  mask_ptr,
    short                              shift
)
{
   int                  i;  
   int                  sum1 ,      sum2,       sum21;
   int                  row_54,     row_10;
   int                  mask44,     mask55,     mask24;
   int                  mask15_15,  mask24_24,  mask14_14;

   double               temp3; 
   double               mask3_0,    mask7_4,    mask11_8;
   double               mask15_12,  mask19_16,  mask23_20;
      
   long long            r1;
   long long            temp1,      temp2;

   union db_ll          row_3210,   row_5432;

   const unsigned char  *in,        *in1,       *in2;
   const unsigned char  *in3,       *in4; 

  
    /* -------------------------------------------------------------------- */
    /*  Inform the compiler by _nasserts the following:                     */
    /*      a) The output array is word aligned                             */
    /*      b) Filter Mask array is double word aligned                     */
    /*      c) The width is greater than or equal to 2                      */
    /*      d) The width is a multiple of 2.                                */
    /* -------------------------------------------------------------------- */

    _nassert((int)imgout_ptr % 4 == 0);    
    _nassert(width               >= 2);
    _nassert(width           % 2 == 0);    

    
    /* -------------------------------------------------------------------- */
    /*       initialise pointers to the starting of each of the 5 rows      */
    /* -------------------------------------------------------------------- */
    in          =   imgin_ptr;
    in1         =   in  + pitch;
    in2         =   in1 + pitch;
    in3         =   in2 + pitch;
    in4         =   in3 + pitch;
   
    /* -------------------------------------------------------------------- */
    /*  Load the 5 mask values                                              */
    /* -------------------------------------------------------------------- */

    mask3_0     =   _memd8((void * )mask_ptr);
    mask7_4     =   _memd8((void * )&mask_ptr[4]);
    mask11_8    =   _memd8((void * )&mask_ptr[8]);
    mask15_12   =   _memd8((void * )&mask_ptr[12]);
    mask19_16   =   _memd8((void * )&mask_ptr[16]);
    mask23_20   =   _memd8((void * )&mask_ptr[20]);

    mask24      =   mask_ptr[24];


    mask44      =   _pack2(_lo(mask7_4),_lo(mask7_4) );
    mask55      =   _packh2(_lo(mask7_4),_lo(mask7_4));
    mask14_14   =   _pack2(_hi(mask15_12),_hi(mask15_12));
    mask15_15   =   _packh2(_hi(mask15_12),_hi(mask15_12));
    mask24_24   =   _pack2(mask24,mask24);
    
   
    /* -------------------------------------------------------------------- */
    /*  Loop is manually unrolled by 2.                                     */
    /* -------------------------------------------------------------------- */
    sum1    =   0;
    sum2    =   0;

    #pragma MUST_ITERATE(1, ,1);
    for (i = 0; i < width ; i += 2)
    {

          /* -------------------------------------------------------------- */
          /* Load 8 pixels that can be used to calculate two output pixels  */
          /* from the kth row                                               */
          /* -------------------------------------------------------------- */
         
          r1    =   _mem8_const((void * ) &in[i]);

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_3210.db   =   _mpyu4(_loll(r1),0x01010101);
          row_54        =   _unpklu4(_hill(r1));

          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1 =  _ddotpl2(row_3210.ll,_lo(mask3_0));
          temp2 =  _ddotpl2(_itoll(row_54,_hill(row_3210.ll)),_hi(mask3_0));
          temp3 =  _mpy2(row_54 , mask44);
 
          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the sums for two output    */
          /* pixels                                                         */
          /* -------------------------------------------------------------- */

          sum1  +=  (_loll(temp1) +  _loll(temp2) +  _lo(temp3));                             
          sum2  +=  (_hill(temp1) +  _hill(temp2) +  _hi(temp3));  

          /* -------------------------------------------------------------- */
          /* Load 8 pixels that can be used to calculate two output pixels  */
          /* from the kth row                                               */
          /* -------------------------------------------------------------- */
         
          r1    =   _mem8_const((void * ) &in1[i ]);

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_5432.ll = _itoll(_unpklu4(_hill(r1)),_unpkhu4(_loll(r1)) );
          
          row_10      = _unpklu4(_loll(r1));

          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1  =  _ddotph2(_itoll(_loll(row_5432.ll),row_10),_hi(mask7_4));
          temp2  =  _ddotph2(row_5432.ll,_lo(mask11_8));
          temp3  =  _mpy2(row_10 , mask55);
 
          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the sums for two output    */
          /* pixels                                                         */
          /* -------------------------------------------------------------- */

          sum1 +=  (_loll(temp1) + _loll(temp2) +_lo(temp3));                             
          sum2 +=  (_hill(temp1) + _hill(temp2) +_hi(temp3)); 
          r1    =  _mem8_const((void * ) &in2[i]);

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_3210.db =  _mpyu4(_loll(r1), 0x01010101);
          row_54      =  _unpklu4(_hill(r1));

          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1 =  _ddotpl2(row_3210.ll,_hi(mask11_8));
          temp2 =  _ddotpl2(_itoll(row_54,_hill(row_3210.ll)),_lo(mask15_12));
          temp3 =  _mpy2(row_54 , mask14_14);
 
          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the sums for two output    */
          /* pixels                                                         */
          /* -------------------------------------------------------------- */

          sum1 +=  (_loll(temp1) + _loll(temp2) + _lo(temp3));
          sum2 +=  (_hill(temp1) + _hill(temp2) + _hi(temp3));
          r1    =  _mem8_const((void * ) &in3[i]);

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_5432.ll =  _itoll(_unpklu4(_hill(r1)),_unpkhu4(_loll(r1)) );
          row_10      =  _unpklu4(_loll(r1));

          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1 =  _ddotph2(_itoll(_loll(row_5432.ll),row_10),_lo(mask19_16));
          temp2 =  _ddotph2(row_5432.ll,_hi(mask19_16));
          temp3 =  _mpy2(row_10 , mask15_15);
 
          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the sums for two output    */
          /* pixels                                                         */
          /* -------------------------------------------------------------- */

          sum1 +=  (_loll(temp1) + _loll(temp2) +_lo(temp3));
          sum2 +=  (_hill(temp1) + _hill(temp2) +_hi(temp3));
          r1    =  _mem8_const((void * ) &in4[i]);

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_3210.db =  _mpyu4(_loll(r1),0x01010101);
          row_54      =  _unpklu4(_hill(r1));

          /* -------------------------------------------------------------- */
          /* Perform the partial multiplications of input pixel with corre- */
          /* ponding mask for the first and second sample outputs           */
          /* -------------------------------------------------------------- */

          temp1 =  _ddotpl2(row_3210.ll,_lo(mask23_20));
          temp2 =  _ddotpl2(_itoll(row_54,_hill(row_3210.ll)),_hi(mask23_20));
          temp3 =  _mpy2(row_54 , mask24_24);
 
          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the sums for two output    */
          /* pixels                                                         */
          /* -------------------------------------------------------------- */

          sum1 +=  (_loll(temp1) + _loll(temp2) + _lo(temp3));
          sum2 +=  (_hill(temp1) + _hill(temp2) + _hi(temp3));
       
          /* -------------------------------------------------------------- */
          /* shift the sum to fall in byte range with user defined value    */
          /* -------------------------------------------------------------- */

          sum1 = (sum1 >> shift); 
          sum2 = (sum2 >> shift); 
          
          /* -------------------------------------------------------------- */
          /* check for saturation and pack two bytes to store using amem2   */
          /* -------------------------------------------------------------- */

          sum21  =  _spacku4(0, _spack2(sum2, sum1)); 
           
          _amem2((void*)&imgout_ptr[i]) = sum21;
   }
 }

/* ======================================================================== */
/*  End of file:  IMG_conv_5x5_i8_c16s_i.c                                  */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


