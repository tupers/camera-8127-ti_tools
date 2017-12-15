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
/*      IMG_corr_11x11_i16s_c16s -> Natural C Implementation                */
/*      11x11 correlation for 16-bit input, 16-bit masks and 32-bit output  */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_corr_11x11_i16s_c16s                                   */
/*          (                                                               */
/*              const short      *restrict  imgin_ptr,                      */
/*                    int        *restrict imgout_ptr,                      */
/*                    short                     width,                      */
/*                    short                     pitch,                      */
/*              const short      *restrict   mask_ptr,                      */
/*                    short                     shift,                      */
/*                    int                       round                       */
/*          )                                                               */
/*                                                                          */
/*      imgin_ptr :  pointer to an input  array of 16 bit pixels            */
/*      imgout_ptr:  pointer to an output array of 32 bit pixels            */
/*      width     :  number of output pixels                                */
/*      pitch     :  number of columns in the input image                   */
/*      mask_ptr  :  pointer to 16 bit filter mask.                         */
/*      shift     :  user specified shift amount                            */
/*      round     :  user specified round value                             */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The correlation kernel accepts 11 rows of 'pitch' input pixels and  */
/*      produces one row of 'width' output pixels using the input mask of   */
/*      11x11. This correlation performs a point by point multiplication    */
/*      of 11x11 mask with the input image. The result of the 121 multipli- */
/*      cations are then summed together to produce a 40-bit sum. A         */
/*      rounding constant is added to the sum and then right-shifted to     */
/*      produce a 32-bit value. This is stored in the output array.         */
/*      Overflow and Saturation of the accumulated sum is not handled.      */
/*      However assumptions are made on filter gain to avoid them.          */
/*      The mask is moved one column at a time, advancing the mask over     */
/*      the entire image until the entire 'width' is covered. The masks     */
/*      are provided as 16-bit signed values and the input image pixels     */
/*      are provided as 16-bit  signed values and the output pixels will    */
/*      be 32-bit signed.The mask to be correlated is typically part of the */
/*      input image or another image.                                       */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and Intrinsic codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. width:   'width' >=2 and a multiple of 2.                        */
/*      2. pitch:   'pitch' >= 'width'                                      */
/*      3. Input and output arrays should not overlap                       */
/*      4. Output array should be double word aligned                       */
/*      5. Input and mask arrays should be half-word aligned                */
/*      6. Internal accuracy of the computations is 40 bits.                */
/*      7. Shift is appropriate to produce a 32-bit result. Overflows are   */
/*         not handled.                                                     */
/*      8. Range of filter co-efficients is -32767 to 32767.                */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible only with C64x+.                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_corr_11x11_i16s_c16s,   ".text:intrinsic");


void IMG_corr_11x11_i16s_c16s
(
    const  short    *restrict  imgin_ptr,
           int      *restrict imgout_ptr,
           short                   width, 
           short                   pitch, 
    const  short    *restrict   mask_ptr, 
           short                   shift,
           int                     round
)
{
    int            i,               k;  
    int            row1,            row2;
    int            mask01,          mask02,          mask03;
    int            mask04,          mask05,          mask06;  

    long           sum1,            sum2;    

    double         mask_row_00,     mask_row_01,     mask_row_02;

    long long      temp1,           temp2,           temp3;
    long long      temp4,           temp5;
    long long      row_00,          row_01,          row_02;
    long long      row_5432,        row_9876; 
   
    const short    *in; 
    const short    *maskptr;

    _nassert((int)imgout_ptr % 8 == 0);  /* Output Dword aligned            */
    _nassert((int)(width)    % 2 == 0);  /* output samples multiple of 2    */

    for (i = 0; i < width ; i += 2)
    {

        in        = &imgin_ptr[i];
        maskptr   = &mask_ptr[0];
        sum1      = round;
        sum2      = round;

        /* ---------------------------------------------------------------- */
        /*  This loop calculates the convolution sum for a single row       */
        /* ---------------------------------------------------------------- */

        for(k = 0;k < 11; k++)      
        {

            /* ------------------------------------------------------------ */
            /* Load 12 pixels that can be used to calculate 2 output pixels */
            /* ------------------------------------------------------------ */
 
            row_00   = _mem8_const( ( void * ) &in[k * pitch    ]) ;
            row_01   = _mem8_const( ( void * ) &in[k * pitch + 4]) ;
            row_02   = _mem8_const( ( void * ) &in[k * pitch + 8]) ;     
            row1     = _hill(row_02) & 0xffff    ;  
            row2     = (_hill(row_02 >> 16)) & 0xffff;
            row_5432 = _itoll( _loll(row_01), _hill(row_00)); 
            row_9876 = _itoll( _loll(row_02), _hill(row_01));

            /* ------------------------------------------------------------ */
            /*  Load the 11 mask values to be used in the current row       */
            /* ------------------------------------------------------------ */

            mask_row_00 = _memd8_const( ( void * ) &maskptr[k * 11    ]);
            mask_row_01 = _memd8_const( ( void * ) &maskptr[k * 11 + 4]);
            mask_row_02 = _memd8_const( ( void * ) &maskptr[k * 11 + 8]);

            /* ------------------------------------------------------------ */
            /* Extract 2 mask values to an int so it can be used in ddotpl2 */
            /* ------------------------------------------------------------ */

            mask01 = _lo(mask_row_00);
            mask02 = _hi(mask_row_00);
            mask03 = _lo(mask_row_01);
            mask04 = _hi(mask_row_01);
            mask05 = _lo(mask_row_02);
            mask06 = _hi(mask_row_02) & 0xffff;

            /* ------------------------------------------------------------ */
            /* Calculate the sum of products using ddotpl2.The lower half of*/
            /* thr output contains values for the first pixel and the upper */
            /* half for the 2nd pixel                                       */
            /* ------------------------------------------------------------ */

            temp1 = _ddotpl2(row_00, mask01);
            temp2 = _ddotpl2(row_5432, mask02);
            temp3 = _ddotpl2(row_01, mask03);
            temp4 = _ddotpl2(row_9876, mask04);
            temp5 = _ddotpl2(row_02, mask05);


            /* ------------------------------------------------------------ */
            /* Calculate sum1,sum2 which has convolution sums for 2 pixels  */
            /* ------------------------------------------------------------ */
 
            sum1 = _lsadd(_loll(temp1), sum1);
            sum1 = _lsadd(_loll(temp2), sum1);
            sum1 = _lsadd(_loll(temp3), sum1);
            sum1 = _lsadd(_loll(temp4), sum1);
            sum1 = _lsadd(_loll(temp5), sum1);
            sum1 = _lsadd(_dotp2(row1,mask06), sum1);
                        
            sum2 = _lsadd(_hill(temp1),sum2);
            sum2 = _lsadd(_hill(temp2),sum2);
            sum2 = _lsadd(_hill(temp3),sum2);
            sum2 = _lsadd(_hill(temp4),sum2);
            sum2 = _lsadd(_hill(temp5),sum2);
            sum2 = _lsadd(_dotp2(row2,mask06),sum2);  

        }

        /* ---------------------------------------------------------------- */
        /*  Shift the sum  by 7 bits to avoid overflow                      */
        /* ---------------------------------------------------------------- */

        sum1   = (sum1 >> shift); 
        sum2   = (sum2 >> shift); 

        _amemd8( ( void * )&imgout_ptr[i] ) = _itod((int)sum2, (int)sum1);



    }

}

/* ======================================================================== */
/*  End of file:  IMG_corr_11x11_i16s_c16s_i.c                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

