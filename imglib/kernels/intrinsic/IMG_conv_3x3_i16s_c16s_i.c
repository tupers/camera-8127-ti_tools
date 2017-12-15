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
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_conv_3x3_i16s_c16s -> Natural C Implementation                  */
/*      3x3 convolution for 16-bit input, 16-bit masks and 16-bit output    */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_conv_3x3_i16s_c16s                                     */
/*          (                                                               */
/*              const short        *restrict   imgin_ptr,                   */
/*                    short        *restrict  imgout_ptr,                   */
/*                    short                        width,                   */
/*                    short                        pitch,                   */
/*              const short        *restrict    mask_ptr,                   */
/*                    short                        shift                    */
/*          )                                                               */
/*                                                                          */
/*      imgin_ptr :   pointer to an input  array of 16 bit pixels           */
/*      imgout_ptr:   pointer to an output array of 16 bit pixels           */
/*      width     :   number of output pixels                               */
/*      pitch     :   number of columns in the image                        */
/*      mask_ptr  :   pointer to 16 bit filter mask.                        */
/*      shift     :   user specified shift amount                           */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The convolution kernel accepts three rows of 'pitch' input pixels   */
/*      and produces one row of 'width' output pixels using the input       */
/*      mask of 3 by 3. This convolution performs a point by point mult-    */
/*      iplication of 3 by 3 mask with the input image. The result of 9     */
/*      multiplications are then summed together to produce a 32-bit conv-  */
/*      olution intermediate sum. Overflow while accumulation is not hand-  */
/*      led. However assumptions are made on filter gain to avoid overflow. */
/*      The user defined shift value is used to shift this convolution sum  */
/*      down to the short range and store in an output array. The result    */
/*      being stored is also range limited between -32768 to 32767 and will */
/*      be saturated accordingly. The mask is moved one column at a time,   */
/*      advancing the mask over the entire image until the entire 'width'   */
/*      is covered.The input, output image pixels and the masks are         */
/*      provided as 16-bit signed values.                                   */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. width:   'width' >=2 and a multiple of 2.                        */
/*      2. pitch:   'pitch' >= 'width'                                      */
/*      3. Input and output arrays should not overlap.                      */
/*      4. Output array should be word aligned.                             */
/*      5. Input array and mask should be half-word aligned.                */
/*      6. Internal accuracy of the computations is 32 bits. To ensure      */
/*         correctness on a 16 bit input data, the maximum permissible      */
/*         filter gain in terms of bits is 16-bits i.e. the cumulative sum  */
/*         of the absolute values of the filter coefficients should not     */
/*         exceed 2^16 - 1.                                                 */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible only with C64x+.                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


#pragma CODE_SECTION(IMG_conv_3x3_i16s_c16s, ".text:intrinsic");



void IMG_conv_3x3_i16s_c16s
(
    const short   *restrict    imgin_ptr,
          short   *restrict   imgout_ptr,
          short                    width,
          short                    pitch,
    const short   *restrict     mask_ptr,
          short                    shift
)
{
    int          sum01_0,       sum01_1;
    int          sum0,          sum1;
    int          mask88,        mask52,     mask4_3 ;  
    int          mask8; 

    double       mask7_4,       mask3_0;
    double       sum2_0;

    long long    sum0_10,       sum1_10,    sum2_10 ;
    long long    pix0_3210,     pix1_3210,  pix2_3210;
    long long    pix03_13_02_12;

    unsigned int i;

 
    /* -------------------------------------------------------------------- */
    /* The 1st two mask values of each row are loaded into one int          */
    /* -------------------------------------------------------------------- */
    
    mask3_0 =  _memd8_const( ( void * ) &mask_ptr[0] );
    mask7_4 =  _memd8_const( ( void * ) &mask_ptr[4] );

    /* -------------------------------------------------------------------- */
    /* The last mask values of each row are loaded into an int              */
    /* -------------------------------------------------------------------- */
    mask8   =  mask_ptr[8];
    mask4_3 =  _packlh2(_lo(mask7_4) , _hi(mask3_0));

    /* -------------------------------------------------------------------- */
    /* mask2_22 contains the last mask of row 3 in its half words           */
    /* -------------------------------------------------------------------- */
    mask88  =  _pack2(mask8 , mask8);
   
    /* -------------------------------------------------------------------- */
    /* Pack the last mask of row 1 & 2 into a single int variable           */
    /* -------------------------------------------------------------------- */

    mask52  =  _packhl2( _lo(mask7_4), _hi(mask3_0));

    _nassert((int)imgout_ptr % 4 == 0);  /* Output is word aligned          */
    _nassert((int)(width)    % 2 == 0);  /* output samples multiple of 2    */
    _nassert((int)imgin_ptr % 2 != 0);
   
      
    for(i = 0; i < width ; i += 2 )
    {
        /* ---------------------------------------------------------------- */
        /*  Load 4 pixels at a time from each of the 3 rows using double    */
        /*  word memory accesses.                                           */
        /* ---------------------------------------------------------------- */

        pix0_3210   =  _mem8_const( ( void * ) &imgin_ptr[i]);
        pix1_3210   =  _mem8_const( ( void * ) &imgin_ptr[i + pitch]);
        pix2_3210   =  _mem8_const( ( void * ) &imgin_ptr[i + 2 * pitch]);

        /* ---------------------------------------------------------------- */
        /* Packs the pixels from 1st and 2nd rows which are at same column  */
        /*  postions (cols 2&3) into the same words, respectively. Here,    */
        /*_hill(pix03_13_02_12)= pix03_13 & _loll(pix03_13_02_12) = pix02_12*/
        /*  where pix03_13 contains pixels at 3rd cols of 0th and 1st rows  */
        /* ---------------------------------------------------------------- */
        
        pix03_13_02_12 =  _dpack2(_hill(pix1_3210), _hill(pix0_3210));

        /* ---------------------------------------------------------------- */
        /* Performs double dot-product for rows 0 & 1. The dot-product      */
        /*  obtained at the lower word corresponds to output pixel0, and    */
        /*  the one at the upper word corresponds to output pixel1.         */
        /* ---------------------------------------------------------------- */

        sum0_10 =  _ddotpl2(pix0_3210, _lo(mask3_0)); 
        sum1_10 =  _ddotpl2(pix1_3210, mask4_3);

        sum0    =  _loll(sum0_10) + _loll(sum1_10); 
        sum1    =  _hill(sum0_10) + _hill(sum1_10);

        sum01_0 =  _dotp2(_loll(pix03_13_02_12), mask52);
        sum01_1 =  _dotp2(_hill(pix03_13_02_12), mask52);
 
        sum0   +=  sum01_0;
        sum1   +=  sum01_1;

        sum2_10 =  _ddotpl2(pix2_3210, _hi(mask7_4)); 
        sum2_0  =  _mpy2(_hill(pix2_3210), mask88);

        sum0   +=  _loll(sum2_10) + _lo(sum2_0);
        sum1   +=  _hill(sum2_10) + _hi(sum2_0);

        /* ---------------------------------------------------------------- */
        /*  Performs right shift by the user-specified amount.              */
        /*  sum0 is the output pixel0 and sum1 is the output pixel1 with    */
        /*  ref to the current postion of input pointer given by offset i.  */
        /* ---------------------------------------------------------------- */
        
        sum0  >>=  shift;
        sum1  >>=  shift;

        /* ---------------------------------------------------------------- */
        /* The sum values obtained in 32-bits are saturated into 2 16-bits  */
        /* ---------------------------------------------------------------- */
        
        _amem4( ( void * )&imgout_ptr[i] ) = _spack2(sum1, sum0);
    }
}

/* ======================================================================== */
/*   End of file:  IMG_conv_3x3_i16s_c16s_i.c                               */
/* ------------------------------------------------------------------------ */
/*             Copyright (c) 2008 Texas Instruments, Incorporated.          */
/*                            All Rights Reserved.                          */
/* ======================================================================== */
