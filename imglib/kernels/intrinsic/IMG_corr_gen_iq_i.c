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
/*      IMG_corr_gen_iq, general correlation with I/O in IQ-format          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_corr_gen_iq                                                */
/*      (                                                                   */
/*          const int   *restrict x,                                        */
/*          const short *restrict h,                                        */
/*          int         *restrict y,                                        */
/*          int                   m,                                        */
/*          int               x_dim,                                        */
/*          int               x_qpt,                                        */
/*          int               h_qpt,                                        */
/*          int               y_qpt                                         */
/*      );                                                                  */
/*                                                                          */
/*      x[]   : Input image array (one row, of width 'x_dim').              */
/*      h[m]  : Input 1xM mask array.                                       */
/*      y[]   : Correlation output array of length (x_dim - m).             */
/*      m     : Length of filter.                                           */
/*      x_dim : Width of input image.                                       */
/*      x_qpt : Q-format used for input image array.                        */
/*      h_qpt : Q-format used for mask array.                               */
/*      y_qpt : Q-format to be used for output.                             */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The routine performs a generalized correlation with a 1 by m tap    */
/*      filter. It can be called n times repetitively to form arbitrary mxn */
/*      2D generalized correlation kernel. Input image data, mask data and  */
/*      output data are in Q-formats. The data type of input image array    */
/*      and output is int where as it is short for mask array. The inter-   */
/*      mediate correlation sum is accumulated to a 64-bit value in an      */
/*      intermediate Q-format. This sum is shifted by a suitable value      */
/*      to get the final output in the specified output Q-format.           */
/*      If the width of the input image is x_dim and the mask is m then     */
/*      the output array must have at-least a dimension of (x_dim - m).     */
/*                                                                          */
/*      Overflow may occur while accumulating the intermediate sum in 64-   */
/*      bits or while converting the intermediate sum to the final sum in   */
/*      32-bits. In either of the cases, no saturation will be performed by */
/*      this routine.                                                       */
/*                                                                          */
/*      The natural C implementation has no restrictions. The Optimized     */
/*      and IntrinsiC codes has restrictions as noted in the ASSUMPTIONS    */
/*      below.                                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      1. The output array should not overlap with any of the input arrays.*/
/*      2. Input image, filter and output arrays should be double-word      */
/*         aligned.                                                         */
/*      3. The input and output Q-formats should follow the relation        */
/*           x_qpt + h_qpt >= y_qpt                                         */
/*      4. Length of filter(m) should be a multiple of 2.                   */
/*      5. Width of input image (x_dim) should be a multiple of 2.          */
/*      6. Minimum value of 'm' is 2.                                       */
/*      7. Minimum value of 'x_dim' is 'm' + 2.                             */
/*      8. Internal accuracy of the computations is 64 bits. To ensure      */
/*         correctness on a 32 bit input data, the maximum permissible      */
/*         filter gain in terms of bits is 32-bits i.e. the Cumulative      */
/*         sum of the absolute values of the filter coefficients should     */
/*         not exceed 2^32 - 1.                                             */
/*                                                                          */
/*  COMPATIBILITY                                                           */
/*      This code is compatible for both c64x and C64x+ processors          */
/*                                                                          */
/*  SOURCE                                                                  */
/*      The algorithm was taken from corr_gen in IMGLIB                     */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_corr_gen_iq,   ".text:intrinsic");


union lldb 
{
    long long     ll;
    double        db;
};


void IMG_corr_gen_iq
(
    const int   *restrict x, 
    const short *restrict h, 
    int         *restrict y, 
    int                   m, 
    int               x_dim, 
    int               x_qpt,
    int               h_qpt,
    int               y_qpt 
) 
{
    int            i,            j;
    int            q_pt;
    int            h10;
    long long      temp_y0,      temp_y1;
    union lldb     temp_y01,     temp_y02;
    union lldb     temp_y11,     temp_y12;
    double         xx0,          xx1;
    int            res1,         res2;

    /* -------------------------------------------------------------------- */
    /*  Calculate the amount of shift to be done to the accumulated value   */
    /*  to get the final output in the output Q-format.                     */
    /* -------------------------------------------------------------------- */

    q_pt  = x_qpt + h_qpt - y_qpt;        

    /* -------------------------------------------------------------------- */
    /* Inform the compiler that                                             */
    /* 1. Input matrices x, h and output matrix y are double-word aligned.  */
    /* 2. Length of filter(m) is a multiple of 2.                           */
    /* 3. Width of input image (x_dim) is a multiple of 2.                  */
    /* 4. Minimum value for 'm' is 2.                                       */
    /* 5. Minimum value for 'x_dim' is 'm' + 2.                             */
    /* -------------------------------------------------------------------- */
    _nassert((int)x % 8  == 0);
    _nassert((int)h % 8  == 0);
    _nassert((int)y % 8  == 0);
    _nassert(     m % 2  == 0);
    _nassert( x_dim % 2  == 0);
    _nassert(     m      >= 2);
    _nassert((x_dim - m) >= 2);

    #pragma MUST_ITERATE(1,,1)
    for (j = 0; j < (x_dim - m); j += 2)
    {
        temp_y0 = 0;
        temp_y1 = 0; 

        for (i = 0; i < m; i += 2)        
        {
            
            /* ------------------------------------------------------------ */
            /* The input array is multiplied with the coefficients. The     */
            /* output of the multiplication is 48-bit which is stored in a  */
            /* double. The multiplied values are accumulated to get the     */   
            /* intermediate result in 64-bit.                               */
            /* ------------------------------------------------------------ */
 
            xx0             =   _amemd8_const(&x[i + j]);
            xx1             =   _amemd8_const(&x[i + j + 2]);
            h10             =   _amem4_const((void *)&h[i]);

            temp_y01.db     =   _mpyli(h10, _lo(xx0));
            temp_y11.db     =   _mpyli(h10, _hi(xx0));

            temp_y0        +=   temp_y01.ll;
            temp_y1        +=   temp_y11.ll;

            temp_y02.db     =   _mpyhi(h10, _hi(xx0));
            temp_y12.db     =   _mpyhi(h10, _lo(xx1));

            temp_y0        +=   temp_y02.ll;
            temp_y1        +=   temp_y12.ll;

        }

        /* ---------------------------------------------------------------- */
        /* The accumulated 64-bit value is shifted by q_pt by separately    */
        /* shifting the higher and lower 32-bit values appropriately. After */
        /* shifting, only the lower 32-bits need to be taken. This is       */
        /* actually taken care while shifting itself.                       */
        /* ---------------------------------------------------------------- */

        res1 = (q_pt < 32) ? 
               (_hill(temp_y0) << (_abs(q_pt - 32)) | 
               _loll(temp_y0) >> q_pt) :
               (signed)_hill(temp_y0) >> (_abs(q_pt - 32));

        res2 = (q_pt < 32) ? 
               (_hill(temp_y1) << (_abs(q_pt - 32)) | 
               _loll(temp_y1) >> q_pt) :
               (signed)_hill(temp_y1) >> (_abs(q_pt - 32));

 
        _amemd8(&y[j])  =   _itod(res2, res1);
    }
     
}
/* ======================================================================== */
/*  End of file:  IMG_corr_gen_iq_i.c                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
