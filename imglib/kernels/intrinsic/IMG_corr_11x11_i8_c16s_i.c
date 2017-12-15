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
/*      IMG_corr_11x11_i8_c8s -> Natural C Implementation                   */
/*      11x11 correlation for 8-bit input, 16-bit masks and 32-bit output   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void IMG_corr_11x11_i8_c16s                                     */
/*          (                                                               */
/*              const unsigned char    *restrict  imgin_ptr,                */
/*                    int              *restrict imgout_ptr,                */
/*                    short                           width,                */
/*                    short                           pitch,                */
/*              const short            *restrict   mask_ptr,                */
/*          )                                                               */
/*                                                                          */
/*      imgin_ptr :  pointer to an input  array of 8 bit pixels             */
/*      imgout_ptr:  pointer to an output array of 32 bit pixels            */
/*      width     :  number of output pixels                                */
/*      pitch     :  number of columns in the image                         */
/*      mask_ptr  :  pointer to 16 bit filter mask.                         */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The correlation kernel accepts 11 rows of 'pitch' input pixels and  */
/*      produces one row of 'width' output pixels using the input mask of   */
/*      11x11. This correlation performs a point by point multiplication    */
/*      of 11x11 mask with the input image. The result of the 121 multipl-  */
/*      ications are then summed together to produce a 32-bit sum which is  */
/*      then stored in an output array. Overflow will not occur.            */
/*      The mask is moved one column at a time, advancing the mask over     */
/*      the entire image until the entire 'width' is covered. The masks     */
/*      are provided as 16-bit signed values and the input image pixels     */
/*      are provided as 8-bit unsigned values and the output pixels         */
/*      will be 32-bit signed. The image mask to be correlated is typically */
/*      part of the input image or another image.                           */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. width:   'width' >=2 and a multiple of 2.                        */
/*      2. pitch:   'pitch' >= 'width'                                      */
/*      3. Input and Output arrays should not overlap                       */
/*      4. Output array should be double word aligned.                      */
/*      5. No restrictions on the alignment of Input array                  */
/*      6. Mask array should be half-word aligned.                          */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible only with C64x+.                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_corr_11x11_i8_c16s,   ".text:intrinsic");
 


void IMG_corr_11x11_i8_c16s
(
    const unsigned char    *restrict  imgin_ptr,
                   int     *restrict imgout_ptr,
                   short                  width, 
                   short                  pitch, 
    const          short   *restrict   mask_ptr
)
{
    int         i,              k;  
    int         sum1,           sum2;    
    int         row1,           row2;
    int         mask01,         mask02,         mask03;
    int         mask04,         mask05,         mask06;    
    int         r2;

    double      r1;
    double      mask_row_00,    mask_row_01,   mask_row_02;

    long long   temp1,          temp2,          temp3;
    long long   temp4,          temp5; 
    long long   row_00,         row_01,         row_02;
    long long   row_5432,       row_9876;
    
    const unsigned char   *in; 

    _nassert((int)imgout_ptr % 8 == 0);  /* Output Dword aligned            */
    _nassert((int)(width)    % 2 == 0);  /* output samples multiple of 2    */
       
    /* -------------------------------------------------------------------- */
    /*  Loop is manually unrolled by 2 .                                    */
    /* -------------------------------------------------------------------- */

    #pragma MUST_ITERATE(1,,1);
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
    /*  This loop calculates the correlation sum for a single row           */
    /* -------------------------------------------------------------------- */

     for(k = 0; k < 11; k++)      
        {


          /* -------------------------------------------------------------- */
          /* Load 12 pixels that can be used to calculate two output pixels */
          /* from the kth row                                               */
          /* -------------------------------------------------------------- */
         
          r1    =   _memd8_const( ( void * ) &in[k * pitch ]);
          r2    =   _mem4_const ( ( void * ) &in[k * pitch + 8]); 

          /* -------------------------------------------------------------- */
          /* Convert the 8 bit pixels to 16 bit values so that ddotpl2      */
          /* can be used                                                    */
          /* -------------------------------------------------------------- */

          row_00      =     _itoll(_unpkhu4(_lo(r1)), _unpklu4(_lo(r1)) );
          row_01      =     _itoll(_unpkhu4(_hi(r1)), _unpklu4(_hi(r1)) );
          row_02      =     _itoll(_unpkhu4(r2), _unpklu4(r2) );

          row1        =     _hill(row_02) & 0xffff    ;  
          row2        =     (_hill(row_02 >> 16)) & 0xffff;

          row_5432    =     _itoll( _loll(row_01),_hill(row_00)); 
          row_9876    =     _itoll( _loll(row_02),_hill(row_01));

          /* -------------------------------------------------------------- */
          /*  Load the 11 mask values                                       */
          /* -------------------------------------------------------------- */

          mask_row_00   =   _memd8_const( ( void * ) &mask_ptr[k * 11]);
          mask_row_01   =   _memd8_const( ( void * ) &mask_ptr[k * 11 + 4]);
          mask_row_02   =   _memd8_const( ( void * ) &mask_ptr[k * 11 + 8]);

          mask01        =   _lo(mask_row_00);
          mask02        =   _hi(mask_row_00);
          mask03        =   _lo(mask_row_01);
          mask04        =   _hi(mask_row_01);
          mask05        =   _lo(mask_row_02);
          mask06        =   _hi(mask_row_02) & 0xffff;

          
          temp1         =   _ddotpl2(row_00, mask01);
          temp2         =   _ddotpl2(row_5432, mask02);
          temp3         =   _ddotpl2(row_01, mask03);
          temp4         =   _ddotpl2(row_9876, mask04);
          temp5         =   _ddotpl2(row_02, mask05);
 
          /* -------------------------------------------------------------- */
          /* Calculate sum1 and sum2 which holds the convolution sums for   */
          /* two pixels                                                     */
          /* -------------------------------------------------------------- */

          sum1 += _loll(temp1) +_loll(temp2) + _loll(temp3) +_loll(temp4) + 
                  _loll(temp5) +_dotp2(row1,mask06);
                        
          sum2 += _hill(temp1) +_hill(temp2) + _hill(temp3) +_hill(temp4) +
                  _hill(temp5) +_dotp2(row2,mask06);  
        }

        _amemd8((void*)&imgout_ptr[i]) = _itod(sum2,sum1);

   }


 }
/* ======================================================================== */
/*  End of file:  IMG_corr_11x11_i8_c16s_i.c                                */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

