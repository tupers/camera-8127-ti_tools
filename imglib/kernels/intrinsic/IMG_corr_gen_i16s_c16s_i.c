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
/*========================================================================= */
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*           IMG_corr_gen_i16s_c16s                                         */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_corr_gen_i16s_c16s                                         */
/*      (                                                                   */
/*          short   *x,                                                     */
/*          short   *h,                                                     */
/*          short   *y,                                                     */
/*          int     m,                                                      */
/*          int     x_dim                                                   */
/*      );                                                                  */
/*                                                                          */
/*      x[]   : Input pixel array.                                          */
/*      h[M]  : Input 1xM mask array                                        */
/*      y[]   : Output array of correlation sum                             */
/*      M     : Length of filter.                                           */
/*      x_dim : Width of input image                                        */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The routine performs a generalized correlation with a 1 by M tap    */
/*      filter. It can be called repetitively to form an arbitrary MxN 2D   */
/*      generalized correlation kernel. The correlation sum is stored as    */
/*      half words. The input pixel, and mask data is assumed to come in    */
/*      as shorts.  No restrictions apply to x_dim and M.                   */
/*                                                                          */
/*      If the width of the input image is x_dim and the mask is M then     */
/*      the output array must have at-least a dimension of (x_dim - m + 8). */
/*                                                                          */
/*  C CODE                                                                  */
/*      void IMG_corr_gen_i16s_c16s(short *x, short *h, short *y, int M,    */
/*                                  int x_dim)                              */
/*      {                                                                   */
/*          iters = x_dim - M;                                              */
/*          for (j = 0; j < iters; j++)                                     */
/*          {                                                               */
/*              sum =  y[j];                                                */
/*              for (i = 0; i < M; i++)                                     */
/*              {                                                           */
/*                  sum += xptr[i + j] * hptr[i];                           */
/*              }                                                           */
/*              y[j] = sum;                                                 */
/*          }                                                               */
/*      }                                                                   */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      - Array x[] must be word aligned, array y[ ] must be double-word    */
/*        aligned, and array h[ ] must be half-word aligned.                */
/*      - Internal accuracy is 16 bits. The convloution sum should not      */
/*        exceed 16 bit's (signed).                                         */
/*      - Output array size must be at-least (x_dim - m + 8)                */
/*      - x_dim > m                                                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_corr_gen_i16s_c16s,   ".text:intrinsic");

void IMG_corr_gen_i16s_c16s(short *restrict x, short *restrict h,
														short *restrict y, int  m, int  x_dim)
{
     int             i,  j, iters,k;
     short          *hptr;
     short          h0, h1;
     int            *xptr;

     double          *yptr,   *zptr;
     double          yval0,   yval1;
     double          zval0,   zval1;

     unsigned int    h1h0,   x1x0,   x3x2, x5x4, x7x6;
     unsigned int    x2x1,   x4x3,   x6x5, x8x7, x9x8;
     unsigned int    sum0,   sum1,   sum2, sum3, sum4;
     unsigned int    sum5,   sum6,   sum7;
     unsigned int    sum10,  sum32, sum54, sum76;
     unsigned int    yword0, yword1, yword2, yword3;
     unsigned int    zword0, zword1, zword2, zword3;

     int             odd, iters_j;
     int             *xiptr, *yiptr, *ziptr;
     int             xword0, xword1, h0x0, h0x1, h0x2, h0x3;
     int             sum0word, sum1word, prev0,prev1,pres0,pres1;

     hptr  = h;

     iters = (x_dim - m) - ((x_dim - m) &1);
     k = 0;
     odd    = m&1;


     for (i = 0; i < m - odd; i += 2)
     {

         h0 = *hptr++;
         h1 = *hptr++;

         h1h0 = _pack2(h1,h0);

         xptr   = (int*) (x + k);
         x1x0   = *xptr++;
         k += 2;

         iters_j = (iters + 8) >> 3;
         yptr    = (double *) (y);
         zptr    = (double *) (y);


         for (j = 0; j < iters_j; j++)
         {
            x3x2     =    *xptr++;
            x5x4     =    *xptr++;
            x7x6     =    *xptr++;
            x9x8     =    *xptr++;

            sum0     =   _dotp2(h1h0,x1x0);  /* h0x0 + h1x1 */
            sum2     =   _dotp2(h1h0,x3x2);  /* h0x2 + h1x3 */
            sum4     =   _dotp2(h1h0,x5x4);  /* h0x4 + h1x5 */
            sum6     =   _dotp2(h1h0,x7x6);  /* h0x6 + h1x7 */

            x2x1     =  _packlh2(x3x2,x1x0);
            x4x3     =  _packlh2(x5x4,x3x2);
            x6x5     =  _packlh2(x7x6,x5x4);
            x8x7     =  _packlh2(x9x8,x7x6);

            sum1     =  _dotp2(h1h0, x2x1);  /* h0x1 + h1x2 */
            sum3     =  _dotp2(h1h0, x4x3);  /* h0x3 + h1x4 */
            sum5     =  _dotp2(h1h0, x6x5);  /* h0x5 + h1x6 */
            sum7     =  _dotp2(h1h0, x8x7);  /* h0x7 + h1x8 */

            sum10    =  _pack2(sum1, sum0);
            sum32    =  _pack2(sum3, sum2);
            sum54    =  _pack2(sum5, sum4);
            sum76    =  _pack2(sum7, sum6);

            yval0    =  *yptr++;
            yval1    =  *yptr++;

            yword0   = _lo(yval0);
            yword1   = _hi(yval0);
            yword2   = _lo(yval1);
            yword3   = _hi(yval1);

            zword0   = _add2(yword0, sum10);
            zword1   = _add2(yword1, sum32);
            zword2   = _add2(yword2, sum54);
            zword3   = _add2(yword3, sum76);

            zval0    = _itod(zword1,zword0);
            zval1    = _itod(zword3,zword2);

            *zptr++  = zval0;
            *zptr++  = zval1;

             x1x0   = x9x8;
         }
     }

     if (!odd)
     {
        y[x_dim - m] = 0;
        y[x_dim - m + 1] = 0;
        y[x_dim - m + 2] = 0;
        y[x_dim - m + 3] = 0;
        y[x_dim - m + 4] = 0;
        y[x_dim - m + 5] = 0;
        y[x_dim - m + 6] = 0;
        y[x_dim - m + 7] = 0;
        return;
     }


     hptr  = h + (m - 1);
     xiptr = (int *) ( x + m - 1);
     yiptr = (int *) (y);
     ziptr = (int *) (y);
     iters_j = (iters + 4) >> 2;

     h0 = *hptr;



     for ( j = 0; j < iters_j;  j++)
     {
          xword0 = *xiptr++;
          xword1 = *xiptr++;

          h0x0   = _mpy(h0,xword0);
          h0x1   = _mpylh(h0, xword0);
          h0x2   = _mpy(h0, xword1);
          h0x3   = _mpylh(h0,xword1);

          sum0word = (h0x1 << 16) + (h0x0 & 0x0000FFFF);
          sum1word = (h0x3 << 16) + (h0x2 & 0x0000FFFF);

          prev0    = *yiptr++;
          prev1    = *yiptr++;

          pres0    = _add2( prev0, sum0word);
          pres1    = _add2( prev1, sum1word);

          *ziptr++  = pres0;
          *ziptr++  = pres1;
     }

      y[x_dim - m] = 0;
      y[x_dim - m + 1] = 0;
      y[x_dim - m + 2] = 0;
      y[x_dim - m + 3] = 0;
      y[x_dim - m + 4] = 0;
      y[x_dim - m + 5] = 0;
      y[x_dim - m + 6] = 0;
      y[x_dim - m + 7] = 0;

      return;
}
/*============================================================================*/
/*      Copyright (C) 1997-1999 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/
