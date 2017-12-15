
* ######################################################################## *
* #  TI Disclaimer: This kernel is obsolete. It is provided here for     # *
* #  backward compatibility.                                             # *
* ######################################################################## *

* ======================================================================== *
*  TEXAS INSTRUMENTS, INC.                                                 *
*                                                                          *
*  IMGLIB-2  DSP Image/Video Processing Library                            *
*                                                                          *
*      Release:        Revision 2.0.1                                      *
*      Snapshot date:  6-May-2008                                          *
*                                                                          *
*  This library contains proprietary intellectual property of Texas        *
*  Instruments, Inc.  The library and its source code are protected by     *
*  various copyrights, and portions may also be protected by patents or    *
*  other legal protections.                                                *
*                                                                          *
*  This software is licensed for use with Texas Instruments TMS320         *
*  family DSPs.  This license was provided to you prior to installing      *
*  the software.  You may review this license by consulting the file       *
*  TI_license.PDF which accompanies the files in this library.             *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2008 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== *
* ========================================================================= *
*                                                                           *
*   TEXAS INSTRUMENTS, INC.                                                 *
*                                                                           *
*   NAME                                                                    *
*       mad_8x8 : Minimum absolute Difference                               *
*                                                                           *
*   USAGE                                                                   *
*                                                                           *
*       This routine is C-callable and can be called as:                    *
*                                                                           *
*       void mad_8x8                                                        *
*       (                                                                   *
*           const unsigned char *ref_data,  /* Ref. image to search */      *
*           const unsigned char *src_data,  /* Source 8x8 block     */      *
*           int                 pitch,      /* Width of ref image   */      *
*           int sx, int sy,                 /* Search window size   */      *
*           unsigned int        *match      /* Result               */      *
*       );                                                                  *
*                                                                           *
*       The reference image is an image of width 'pitch'.  The mad_8x8      *
*       routine searches a (sx,sy) window within the image.                 *
*                                                                           *
*       The source image is an 8x8 block of pixels which contain the        *
*       image block that is being searched for.                             *
*                                                                           *
*       The match[] array is where the best match location and MAD value    *
*       for the best match are stored.  The best match position and its     *
*       absolute difference are returned in match, packed as follows:       *
*                                                                           *
*                      31             16 15             0                   *
*                      +----------------+----------------+                  *
*           match[0]:  |    X offset    |    Y offset    |                  *
*                      +----------------+----------------+                  *
*                                                                           *
*                      31                               0                   *
*                      +---------------------------------+                  *
*           match[1]:  |   Sum of absolute differences   |                  *
*                      +---------------------------------+                  *
*                                                                           *
*   DESCRIPTION                                                             *
*       This routine locates the position in a reference image which        *
*       most closely matches an 8x8 block from a source image, using        *
*       the Minimum Absolute Difference metric.  Searches over a range      *
*       that is 'sx' pixels wide and 'sy' pixels tall within a reference    *
*       image that is 'pitch' pixels wide.                                  *
*                                                                           *
*       The search is performed in top-to-bottom, left-to-right order,      *
*       with the earliest match taking precedence in the case of ties.      *
*                                                                           *
*       The match location as well as the Minimum Absolute Difference       *
*       metric for the match are returned in the 'match' array.             *
*       The first element contains the packed horizontal and vertical       *
*       coordinates of the match, with the X coordinate in the upper        *
*       halfword and the Y coordinate in the lower halfword.  The           *
*       second element contains the MAD value for this match location.      *
*                                                                           *
*   TECHNIQUES                                                              *
*       The inner loops that perform the 8x8 mads are completely            *
*       unrolled and the outer two loops are collpaesd together. In         *
*       addition all source image data is pre-loaded into registers.        *
*                                                                           *
*       The data required for any one row is brought in using               *
*       non-aligned loads. SUBABS4 and DOTPU4 are used together to do       *
*       the MAD computation.                                                *
*                                                                           *
*       To save instructions and fit within an 8 cycle loop, the            *
*       precise location of a given match is not stored.  Rather,           *
*       the loop iteration that it was encountered on is stored.            *
*       A short divide loop after the search loop converts this             *
*       value into X and Y coordinates for the location.                    *
*                                                                           *
*   ASSUMPTIONS                                                             *
*       The arrays for the source image data and the result must be         *
*       word aligned.                                                       *
*                                                                           *
*   MEMORY NOTE                                                             *
*       No bank conflicts occur for this kernel.                            *
*                                                                           *
*       No particular memory alignment is required for the reference        *
*       image, although the source image data and result                    *
*       must be word aligned.                                               *
*                                                                           *
*   NOTES                                                                   *
*       The search window spans from (0,0) to (sx-1,sy-1), inclusive.       *
*                                                                           *
*       The inner loop comprises 64 instructions that are executed in 8     *
*       cycles, with 64 absolute-differences accumulated in a single        *
*       iteration.  The source pixels are pre-read into registers and       *
*       the inner loop is unrolled completely.  This code thus executes     *
*       8 instructions per cycle, and computes 8 absolute differences       *
*       per cycle.                                                          *
*                                                                           *
*       This benchmark is Little Endian.                                    *
*                                                                           *
*       This code suppresses interrupts for the entire duration of the      *
*       code, hence it is interrupt tolerant but not interruptible.         *
*                                                                           *
*   C CODE                                                                  *
*       The following is the equivalent C code.  The assembly code          *
*       has restrictions as noted under "ASSUMPTIONS".                      *
*                                                                           *
*       void mad_8x8                                                        *
*       (                                                                   *
*           const unsigned char *restrict refImg,                           *
*           const unsigned char *restrict srcImg,                           *
*           int pitch, int sx, int sy,                                      *
*           unsigned int *restrict match                                    *
*       )                                                                   *
*       {                                                                   *
*           int i, j, x, y, matx, maty;                                     *
*           unsigned matpos, matval;                                        *
*                                                                           *
*           matval = ~0U;                                                   *
*           matx   = maty = 0;                                              *
*                                                                           *
*           for (x = 0; x < sx; x++)                                        *
*               for (y = 0; y < sy; y++)                                    *
*               {                                                           *
*                   unsigned acc = 0;                                       *
*                                                                           *
*                   for (i = 0; i < 8; i++)                                 *
*                       for (j = 0; j < 8; j++)                             *
*                           acc += abs(srcImg[i*8 + j] -                    *
*                                      refImg[(i+y)*pitch + x + j]);        *
*                                                                           *
*                   if (acc < matval)                                       *
*                   {                                                       *
*                       matval = acc;                                       *
*                       matx   = x;                                         *
*                       maty   = y;                                         *
*                   }                                                       *
*               }                                                           *
*                                                                           *
*           matpos    = (0xffff0000 & (matx << 16)) |                       *
*                       (0x0000ffff & maty);                                *
*           match[0] = matpos;                                              *
*           match[1] = matval;                                              *
*       }                                                                   *
*                                                                           *
*   CYCLES                                                                  *
*       sx = # of columns of the search space                               *
*       sy = # of rows of the search space                                  *
*       cycles = 8 * sx * sy + 66.                                          *
*                                                                           *
*       For sx=  4 and sy=  4, cycles = 194.                                *
*       For sx= 64 and sy= 32, cycles = 16450.                              *
*                                                                           *
*       Overall throughput is 7.97 pixels/cycle (0.126 cycles/pixel)        *
*       over the whole function for the case H=64 and V=32.                 *
*                                                                           *
*   CODESIZE                                                                *
*       788 bytes                                                           *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *

               .sect    ".text:hand"
               .if     __TI_EABI__
          		 .asg    IMG_mad_8x8,  _IMG_mad_8x8
                .endif
               .global _IMG_mad_8x8
               .global __divu

_IMG_mad_8x8:

* ===================== SYMBOLIC REGISTER ASSIGNMENTS ===================== *
        .asg            A0,         A_i  
        .asg            A1,         A_err1l
        .asg            A1,         A_err7l
        .asg            A1,         A_mad_3
        .asg            A1,         A_mad_4
        .asg            A1,         A_row_6
        .asg            A2,         A_f
        .asg            A2,         A_src
        .asg            A3,         A_h_fix
        .asg            A4,         A_ref_d
        .asg            A5,         A_src7l
        .asg            A6,         A_p1
        .asg            A7,         A_err3l
        .asg            A7,         A_mad_2
        .asg            A8,         A_v_dim
        .asg            A8,         A_k_one
        .asg            A9,         A_p7
        .asg            A9,         A_tmp
        .asg            A10,        A_err5l
        .asg            A10,        A_row_4
        .asg            A10,        A_row_5
        .asg            A10,        A_row_7
        .asg            A11,        A_err6l
        .asg            A11,        A_mad_5
        .asg            A11,        A_row_1
        .asg            A12,        A_mad_6
        .asg            A12,        A_ref1l
        .asg            A12,        A_ref3l
        .asg            A13,        A_err2l
        .asg            A13,        A_ref1h
        .asg            A13,        A_ref3h
        .asg            A13,        A_row_3
        .asg            A16,        A_p2
        .asg            A17,        A_p3
        .asg            A18,        A_p4
        .asg            A19,        A_p5
        .asg            A20,        A_p6
        .asg            A21,        A_src0l
        .asg            A22,        A_src1l
        .asg            A23,        A_src2l
        .asg            A24,        A_src3l
        .asg            A25,        A_src4l
        .asg            A26,        A_src5l
        .asg            A27,        A_src6l
        .asg            A28,        A_ref5l
        .asg            A28,        A_ref7l
        .asg            A28,        A_row_2
        .asg            A29,        A_ref5h
        .asg            A29,        A_ref7h
        .asg            A30,        A_row_0
        .asg            A31,        A_err0l
        .asg            A31,        A_err4l
        .asg            B0,         B_v1
        .asg            B1,         B_bst
        .asg            B1,         B_err0h
        .asg            B1,         B_err2h
        .asg            B1,         B_mad_0
        .asg            B1,         B_mad_4
        .asg            B1,         B_row_4
        .asg            B2,         B_k_one
        .asg            B3,         B_ret  
        .asg            B4,         B_src
        .asg            B4,         B_v_dim
        .asg            B5,         B_err1h
        .asg            B5,         B_err6h
        .asg            B5,         B_err7h
        .asg            B5,         B_row_1
        .asg            B5,         B_row_7
        .asg            B6,         B_bhvl
        .asg            B6,         B_h_dim
        .asg            B7,         B_no_gie
        .asg            B7,         B_err3h
        .asg            B7,         B_err4h
        .asg            B7,         B_err5h
        .asg            B7,         B_mad_5
        .asg            B7,         B_mad_6
        .asg            B8,         B_match
        .asg            B9,         B_mad_2
        .asg            B9,         B_row_3
        .asg            B16,        B_mad_1
        .asg            B17,        B_row_0
        .asg            B18,        B_best
        .asg            B19,        B_hvl
        .asg            B20,        B_mad
        .asg            B21,        B_src0h
        .asg            B22,        B_src1h
        .asg            B23,        B_src2h
        .asg            B24,        B_src3h
        .asg            B25,        B_src4h
        .asg            B26,        B_src5h
        .asg            B27,        B_src6h
        .asg            B28,        B_src7h
        .asg            B29,        B_csr
        .asg            B30,        B_mad_3
        .asg            B30,        B_ref0l
        .asg            B30,        B_ref2l
        .asg            B30,        B_ref4l
        .asg            B30,        B_ref6l
        .asg            B30,        B_row_5
        .asg            B31,        B_ref0h
        .asg            B31,        B_ref2h
        .asg            B31,        B_ref4h
        .asg            B31,        B_ref6h
        .asg            B31,        B_row_2
        .asg            B31,        B_row_6
* ========================================================================= *

        STW     .D2T1   A10,        * B15--(16)
||      MV              B_src,      A_src

        LDW     .D2T2   *B_src[15], B_src7h
||      LDW     .D1T1   *A_src[14], A_src7l
||      SUB     .S1     A_v_dim,    1,          A_tmp

        LDW     .D2T2   *B_src[13], B_src6h
||      LDW     .D1T1   *A_src[12], A_src6l
||      MPY     .M1     A_tmp,      A_p1,       A_tmp

        LDW     .D2T2   *B_src[11], B_src5h
||      LDW     .D1T1   *A_src[10], A_src5l
||      MVKL    .S2     0x01010101, B_k_one

        LDW     .D2T2   *B_src[ 9], B_src4h
||      LDW     .D1T1   *A_src[ 8], A_src4l
||      SUB     .S1     1,          A_tmp,      A_h_fix

        LDW     .D2T2   *B_src[ 7], B_src3h
||      LDW     .D1T1   *A_src[ 6], A_src3l
||      MVKH    .S2     0x01010101, B_k_one

        LDW     .D2T2   *B_src[ 5], B_src2h
||      LDW     .D1T1   *A_src[ 4], A_src2l

        LDW     .D2T2   *B_src[ 3], B_src1h
||      LDW     .D1T1   *A_src[ 2], A_src1l

        LDW     .D2T2   *B_src[ 1], B_src0h
||      LDW     .D1T1   *A_src[ 0], A_src0l
||      MVC     .S2     CSR,        B_csr
* =========================== PIPE LOOP PROLOG ============================ *
        MPYUS   .M1     A_p1,       7,          A_p7
||      STW     .D2T1   A11,        *+B15(4)
||      AND     .L2     B_csr,      -2,         B_no_gie

        MPYUS   .M1     A_p1,       6,          A_p6
||      MV      .L2X    A_v_dim,    B_v_dim
||      STDW    .D2T1   A13:A12,    *+B15(8)
||      MVC     .S2     B_no_gie,   CSR

        LDNDW   .D      *A_ref_d(A_p7),         A_ref7h:A_ref7l ;[ 1,1] 
||      MV      .S1     A_p1,       A_f                         ;[ 1,1] 
||      MPYUS   .M1     A_p1,       3,          A_p3

        LDNDW   .D      *A_ref_d(A_p6),         B_ref6h:B_ref6l ;[ 2,1] 
||      MPYUS   .M1     A_p1,       5,          A_p5

        LDNDW   .D      *A_ref_d(A_p3),         A_ref3h:A_ref3l ;[ 3,1] 
||      SUB     .D2     B_v_dim,    1,          B_v1            ;[ 3,1] 
||      MPYUS   .M1     A_p1,       4,          A_p4

        LDNDW   .D      *A_ref_d(A_p5),         A_ref5h:A_ref5l ;[ 4,1] 
||[!B_v1]MV     .S1     A_h_fix,    A_f                         ;[ 4,1] 
||      MPYUS   .M1     A_p1,       2,          A_p2

        LDNDW   .D      *A_ref_d(A_p4),         B_ref4h:B_ref4l ;[ 5,1] 
||      MPY     .M1X    B_h_dim,    A_v_dim,    A_i  
||      ZERO    .L2     B_hvl
||      ZERO    .D2     B_bhvl
||      MVK     .S2     0x7FFF,     B_best

        LDNDW   .D      *A_ref_d(A_p2),         B_ref2h:B_ref2l ;[ 6,1] 
||      SUBABS4 .L2X    B_src7h,    A_ref7h,    B_err7h         ;[ 6,1] 
||[!B_v1]MV     .S2     B_v_dim,    B_v1                        ;[ 6,1] 
||      MV      .S1X    B_k_one,    A_k_one

        LDNDW   .D      *A_ref_d(A_p1),         A_ref1h:A_ref1l ;[ 7,1] 
||      SUBABS4 .L2     B_src6h,    B_ref6h,    B_err6h         ;[ 7,1] 
||      DOTPU4  .M2     B_err7h,    B_k_one,    B_row_7         ;[ 7,1] 
||      SUBABS4 .L1     A_src7l,    A_ref7l,    A_err7l         ;[ 7,1] 
||      SUB     .S1     A_i,        1,          A_i   

        LDNDW   .D      *A_ref_d++(A_f),        B_ref0h:B_ref0l ;[ 8,1] 
||      SUBABS4 .L2X    B_src3h,    A_ref3h,    B_err3h         ;[ 8,1] 
||      DOTPU4  .M2     B_err6h,    B_k_one,    B_row_6         ;[ 8,1] 
||      SUBABS4 .L1X    A_src6l,    B_ref6l,    A_err6l         ;[ 8,1] 
||      DOTPU4  .M1     A_err7l,    A_k_one,    A_row_7         ;[ 8,1] 

        DOTPU4  .M2     B_err3h,    B_k_one,    B_row_3         ;[ 9,1] 
||      SUBABS4 .L1     A_src5l,    A_ref5l,    A_err5l         ;[ 9,1] 
||      SUBABS4 .L2X    B_src5h,    A_ref5h,    B_err5h         ;[ 9,1] 
||      LDNDW   .D      *A_ref_d(A_p7),         A_ref7h:A_ref7l ;[ 1,2] 

        SUBABS4 .L1X    A_src4l,    B_ref4l,    A_err4l         ;[10,1] 
||      SUBABS4 .L2     B_src4h,    B_ref4h,    B_err4h         ;[10,1] 
||      DOTPU4  .M2     B_err5h,    B_k_one,    B_row_5         ;[10,1] 
||      DOTPU4  .M1     A_err6l,    A_k_one,    A_row_6         ;[10,1] 
||      LDNDW   .D      *A_ref_d(A_p6),         B_ref6h:B_ref6l ;[ 2,2] 

        SUBABS4 .L2     B_src2h,    B_ref2h,    B_err2h         ;[11,1] 
||      SUBABS4 .L1     A_src3l,    A_ref3l,    A_err3l         ;[11,1] 
||      DOTPU4  .M2     B_err4h,    B_k_one,    B_row_4         ;[11,1] 
||      DOTPU4  .M1     A_err5l,    A_k_one,    A_row_5         ;[11,1] 
||      LDNDW   .D      *A_ref_d(A_p3),         A_ref3h:A_ref3l ;[ 3,2] 
||      SUB     .D2     B_v1,       1,          B_v1            ;[ 3,2] 

        SUBABS4 .L2X    B_src1h,    A_ref1h,    B_err1h         ;[12,1] 
||      DOTPU4  .M2     B_err2h,    B_k_one,    B_row_2         ;[12,1] 
||      SUBABS4 .L1X    A_src2l,    B_ref2l,    A_err2l         ;[12,1] 
||      DOTPU4  .M1     A_err4l,    A_k_one,    A_row_4         ;[12,1] 
||      ADD     .D2     B_row_6,    B_row_7,    B_mad_6         ;[12,1] 
||      LDNDW   .D      *A_ref_d(A_p5),         A_ref5h:A_ref5l ;[ 4,2] 
||[!B_v1]MV     .S1     A_h_fix,    A_f                         ;[ 4,2] 

        SUBABS4 .L1X    A_src0l,    B_ref0l,    A_err0l         ;[13,1] 
||      SUBABS4 .L2     B_src0h,    B_ref0h,    B_err0h         ;[13,1] 
||      DOTPU4  .M2     B_err1h,    B_k_one,    B_row_1         ;[13,1] 
||      DOTPU4  .M1     A_err3l,    A_k_one,    A_row_3         ;[13,1] 
||      LDNDW   .D      *A_ref_d(A_p4),         B_ref4h:B_ref4l ;[ 5,2] 

        DOTPU4  .M2     B_err0h,    B_k_one,    B_row_0         ;[14,1] 
||      SUBABS4 .L1     A_src1l,    A_ref1l,    A_err1l         ;[14,1] 
||      DOTPU4  .M1     A_err2l,    A_k_one,    A_row_2         ;[14,1] 
||      ADD     .D2     B_row_5,    B_mad_6,    B_mad_5         ;[14,1] 
||      ADD     .S1     A_row_6,    A_row_7,    A_mad_6         ;[14,1] 
||      LDNDW   .D      *A_ref_d(A_p2),         B_ref2h:B_ref2l ;[ 6,2] 
||      SUBABS4 .L2X    B_src7h,    A_ref7h,    B_err7h         ;[ 6,2] 
||[!B_v1]MV     .S2     B_v_dim,    B_v1                        ;[ 6,2] 

        DOTPU4  .M1     A_err1l,    A_k_one,    A_row_1         ;[15,1] 
||      ADD     .D2     B_row_4,    B_mad_5,    B_mad_4         ;[15,1] 
||      ADD     .S1     A_row_5,    A_mad_6,    A_mad_5         ;[15,1] 
||      LDNDW   .D1T1   *A_ref_d(A_p1),         A_ref1h:A_ref1l ;[ 7,2] 
||      SUBABS4 .L2     B_src6h,    B_ref6h,    B_err6h         ;[ 7,2] 
||      DOTPU4  .M2     B_err7h,    B_k_one,    B_row_7         ;[ 7,2] 
||      SUBABS4 .L1     A_src7l,    A_ref7l,    A_err7l         ;[ 7,2] 
||      B       .S2     loop_4 + 8                              ; pro. coll.  

        ADD     .D2     B_row_3,    B_mad_4,    B_mad_3         ;[16,1] 
||      ADD     .S1     A_row_4,    A_mad_5,    A_mad_4         ;[16,1] 
||      LDNDW   .D      *A_ref_d++(A_p1),       B_ref0h:B_ref0l ;[ 8,2] 
||      SUBABS4 .L2X    B_src3h,    A_ref3h,    B_err3h         ;[ 8,2] 
||      DOTPU4  .M2     B_err6h,    B_k_one,    B_row_6         ;[ 8,2] 
||      SUBABS4 .L1X    A_src6l,    B_ref6l,    A_err6l         ;[ 8,2] 
||      DOTPU4  .M1     A_err7l,    A_k_one,    A_row_7         ;[ 8,2] 

; Collapsed 1 Prolog Stage
* =========================== PIPE LOOP KERNEL ============================ *
mad8x8_loop:
        ADD     .D2     B_hvl,      1,          B_hvl           ;[25,1] 
||      DOTPU4  .M1     A_err0l,    A_k_one,    A_row_0         ;[17,2] 
||      ADD     .S2     B_row_2,    B_mad_3,    B_mad_2         ;[17,2] 
||      DOTPU4  .M2     B_err3h,    B_k_one,    B_row_3         ;[ 9,3] 
||      SUBABS4 .L1     A_src5l,    A_ref5l,    A_err5l         ;[ 9,3] 
||      SUBABS4 .L2X    B_src5h,    A_ref5h,    B_err5h         ;[ 9,3] 
||      LDNDW   .D      *A_ref_d(A_p7),         A_ref7h:A_ref7l ;[ 1,4] 
||      MV      .S1     A_p1,       A_f                         ;[ 1,4] 
loop_1:
        ADD     .D2X    A_row_0,    B_mad_0,    B_mad_0         ;[26,1] 
||      ADD     .S2     B_row_1,    B_mad_2,    B_mad_1         ;[18,2] 
||      ADD     .S1     A_row_3,    A_mad_4,    A_mad_3         ;[18,2] 
||      SUBABS4 .L1X    A_src4l,    B_ref4l,    A_err4l         ;[10,3] 
||      SUBABS4 .L2     B_src4h,    B_ref4h,    B_err4h         ;[10,3] 
||      DOTPU4  .M2     B_err5h,    B_k_one,    B_row_5         ;[10,3] 
||      DOTPU4  .M1     A_err6l,    A_k_one,    A_row_6         ;[10,3] 
||      LDNDW   .D      *A_ref_d(A_p6),         B_ref6h:B_ref6l ;[ 2,4] 
loop_2:
  [A_i] BDEC    .S1     mad8x8_loop,            A_i             ;[27,1] 
||      ADD     .S2X    B_mad_0,    A_mad_2,    B_mad           ;[27,1] 
||      SUBABS4 .L2     B_src2h,    B_ref2h,    B_err2h         ;[11,3] 
||      SUBABS4 .L1     A_src3l,    A_ref3l,    A_err3l         ;[11,3] 
||      DOTPU4  .M2     B_err4h,    B_k_one,    B_row_4         ;[11,3] 
||      DOTPU4  .M1     A_err5l,    A_k_one,    A_row_5         ;[11,3] 
||      LDNDW   .D      *A_ref_d(A_p3),         A_ref3h:A_ref3l ;[ 3,4] 
||      SUB     .D2     B_v1,       1,          B_v1            ;[ 3,4] 
loop_3:
        CMPGT2  .S2     B_best,     B_mad,      B_bst           ;[28,1] 
||      SUBABS4 .L2X    B_src1h,    A_ref1h,    B_err1h         ;[12,3] 
||      DOTPU4  .M2     B_err2h,    B_k_one,    B_row_2         ;[12,3] 
||      SUBABS4 .L1X    A_src2l,    B_ref2l,    A_err2l         ;[12,3] 
||      DOTPU4  .M1     A_err4l,    A_k_one,    A_row_4         ;[12,3] 
||      ADD     .D2     B_row_6,    B_row_7,    B_mad_6         ;[12,3] 
||      LDNDW   .D      *A_ref_d(A_p5),         A_ref5h:A_ref5l ;[ 4,4] 
||[!B_v1]MV     .S1     A_h_fix,    A_f                         ;[ 4,4] 
loop_4:
  [ B_bst]SUB   .D2     B_hvl,      1,          B_bhvl          ;[29,1] 
||[ B_bst]MV    .S2     B_mad,      B_best                      ;[29,1] 
||      ADD     .S1     A_row_2,    A_mad_3,    A_mad_2         ;[21,2] 
||      SUBABS4 .L1X    A_src0l,    B_ref0l,    A_err0l         ;[13,3] 
||      SUBABS4 .L2     B_src0h,    B_ref0h,    B_err0h         ;[13,3] 
||      DOTPU4  .M2     B_err1h,    B_k_one,    B_row_1         ;[13,3] 
||      DOTPU4  .M1     A_err3l,    A_k_one,    A_row_3         ;[13,3] 
|| [A_i]LDNDW   .D      *A_ref_d(A_p4),         B_ref4h:B_ref4l ;[ 5,4] 

        DOTPU4  .M2     B_err0h,    B_k_one,    B_row_0         ;[14,3] 
||      SUBABS4 .L1     A_src1l,    A_ref1l,    A_err1l         ;[14,3] 
||      DOTPU4  .M1     A_err2l,    A_k_one,    A_row_2         ;[14,3] 
||      ADD     .D2     B_row_5,    B_mad_6,    B_mad_5         ;[14,3] 
||      ADD     .S1     A_row_6,    A_row_7,    A_mad_6         ;[14,3] 
|| [A_i]LDNDW   .D      *A_ref_d(A_p2),         B_ref2h:B_ref2l ;[ 6,4] 
|| [A_i]SUBABS4 .L2X    B_src7h,    A_ref7h,    B_err7h         ;[ 6,4] 
||[!B_v1]MV     .S2     B_v_dim,    B_v1                        ;[ 6,4] 

        ADD     .D2X    A_row_1,    B_mad_1,    B_mad_1         ;[23,2] 
||      DOTPU4  .M1     A_err1l,    A_k_one,    A_row_1         ;[15,3] 
||      ADD     .S2     B_row_4,    B_mad_5,    B_mad_4         ;[15,3] 
||      ADD     .S1     A_row_5,    A_mad_6,    A_mad_5         ;[15,3] 
|| [A_i]LDNDW   .D      *A_ref_d(A_p1),         A_ref1h:A_ref1l ;[ 7,4] 
|| [A_i]SUBABS4 .L2     B_src6h,    B_ref6h,    B_err6h         ;[ 7,4] 
|| [A_i]DOTPU4  .M2     B_err7h,    B_k_one,    B_row_7         ;[ 7,4] 
|| [A_i]SUBABS4 .L1     A_src7l,    A_ref7l,    A_err7l         ;[ 7,4] 

        ADD     .S2     B_row_0,    B_mad_1,    B_mad_0         ;[24,2] 
||      ADD     .D2     B_row_3,    B_mad_4,    B_mad_3         ;[16,3] 
||      ADD     .S1     A_row_4,    A_mad_5,    A_mad_4         ;[16,3] 
|| [A_i]LDNDW   .D      *A_ref_d++(A_f),        B_ref0h:B_ref0l ;[ 8,4] 
|| [A_i]SUBABS4 .L2X    B_src3h,    A_ref3h,    B_err3h         ;[ 8,4] 
|| [A_i]DOTPU4  .M2     B_err6h,    B_k_one,    B_row_6         ;[ 8,4] 
|| [A_i]SUBABS4 .L1X    A_src6l,    B_ref6l,    A_err6l         ;[ 8,4] 
|| [A_i]DOTPU4  .M1     A_err7l,    A_k_one,    A_row_7         ;[ 8,4] 

* =========================== PIPE LOOP EPILOG ============================ *
; Collapsed 2 Epilog Stages
        .asg            A13,        A_v_dim
        .asg            A12,        A_ret
        .asg            A11,        A_bhvl   
        .asg            A10,        A_match 
        .asg            A4,         A_num
        .asg            B4,         B_den       ; Note: B_v_dim already in B4
        .asg            A4,         A_best_x
        .asg            A3,         A_best_y
        .asg            A4,         A_best_xy

        ADD     .L2X    A_row_0,    B_mad_0,    B_mad_0         ;[26,4] 
||      CALL    .S2     __divu
||      MV      .S1X    B_v_dim,    A_v_dim

        ADD     .S2X    B_mad_0,    A_mad_2,    B_mad           ;[27,4] 
||      MV      .S1X    B_ret,      A_ret

        CMPGT2  .S2     B_best,     B_mad,      B_bst           ;[28,4] 
||      SUB     .L1X    B_bhvl,     1,          A_num           ;[29,4] 

  [ B_bst]SUB   .D1X    B_hvl,      1,          A_num           ;[29,4] 
||[ B_bst]MV    .S2     B_mad,      B_best                      ;[29,4] 

        STW     .D2T2   B_best,     *B_match[1]
||      MV      .S1X    B_match,    A_match
||      MV      .L1     A_num,      A_bhvl

        ADDKPC  .S2     RL0,        B_ret,      0
; ===== Call Occurs.
RL0:
* ========================================================================= *
        LDDW    .D2T1   *B15(8),    A13:A12

        RET     .S2X    A_ret
||      LDW             *B15(4),    A11
||      MPYU    .M1     A_best_x,   A_v_dim,    A_tmp

        LDW     .D2T1   *++B15(16), A10

        SUB     .L1     A_bhvl,     A_tmp,      A_best_y

        PACK2   .L1     A_best_x,   A_best_y,   A_best_xy

        STW     .D1T1   A_best_xy,  *A_match[0]

        MVC     .S2     B_csr,      CSR
; ===== Branch Occurs.

* ========================================================================= *
*   End of file:  mad_8x8_h.asm                                             *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
