
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
*   NAME                                                                    *
*       sad_8x8 -- Sum of Absolute Differences on single 16x16 block        *
*                                                                           *
*   USAGE                                                                   *
*       unsigned sad_8x8                                                    *
*       (                                                                   *
*           const unsigned char *restrict srcImg,  /* 8x8 source block   */ *
*           const unsigned char *restrict refImg,  /* Reference image    */ *
*           int pitch                              /* Width of ref image */ *
*       );                                                                  *
*                                                                           *
*       The code accepts a pointer to the 8x8 source block (srcImg),        *
*       and a pointer to the upper-left corner of a target position in      *
*       a reference image (refImg).  The width of the reference image       *
*       is given by the pitch argument.                                     *
*                                                                           *
*       The function returns the sum of the absolute differences            *
*       between the source block and the 8x8 region pointed to in the       *
*       reference image.                                                    *
*                                                                           *
*   DESCRIPTION                                                             *
*       The algorithm takes the difference between the pixel values in      *
*       the source image block and the corresponding pixels in the          *
*       reference image.  It then takes the absolute values of these        *
*       differences, and accumulates them over the entire 8x8 region.       *
*       It returns the final accumulation.                                  *
*                                                                           *
*   C CODE                                                                  *
*       The following is a C code description of the algorithm that lacks   *
*       restrictions.  The assembly code may have additional restrictions   *
*       as noted below.                                                     *
*                                                                           *
*           unsigned sad_8x8                                                *
*           (                                                               *
*               const unsigned char *restrict srcImg,                       *
*               const unsigned char *restrict refImg,                       *
*               int pitch                                                   *
*           )                                                               *
*           {                                                               *
*               int i, j;                                                   *
*               unsigned sad = 0;                                           *
*                                                                           *
*               for (i = 0; i < 8; i++)                                     *
*                   for (j = 0; j < 8; j++)                                 *
*                       sad += abs(srcImg[j+i*8] - refImg[j+i*pitch]);      *
*                                                                           *
*               return sad;                                                 *
*           }                                                               *
*                                                                           *
*   ASSUMPTIONS                                                             *
*       Some versions of this kernel may assume that srcImg is double-      *
*       word aligned.                                                       *
*                                                                           *
*   MEMORY NOTE                                                             *
*       No bank conflicts occur.                                            *
*       Endian Neutral.                                                     *
*                                                                           *
*   NOTES                                                                   *
*       This kernel blocks interrupts for 25 cycles.                        *
*                                                                           *
*   CYCLES                                                                  *
*       31 cycles                                                           *
*                                                                           *
*   CODESIZE                                                                *
*       164 bytes                                                           *
*                                                                           *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
        .if     __TI_EABI__
          		 .asg    IMG_sad_8x8,  _IMG_sad_8x8
        .endif
        .global _IMG_sad_8x8  
        .sect ".text:hand"

_IMG_sad_8x8:  
* ===================== SYMBOLIC REGISTER ASSIGNMENTS ===================== *
        .asg            A0,         A_p
        .asg            A1,         A_i
        .asg            A2,         A_s0
        .asg            A3,         A_k1
        .asg            A4,         A_srcImg
        .asg            A4,         A_retval
        .asg            A5,         A_sad
        .asg            A6,         A_pitch
        .asg            A6,         A_s3210
        .asg            A7,         A_d7654
        .asg            A7,         A_s7654
        .asg            A8,         A_r3210
        .asg            A8,         A_s1
        .asg            A9,         A_d3210
        .asg            A9,         A_r7654
        .asg            B3,         B_retaddr
        .asg            B4,         B_refImg
        .asg            B5,         B_pitch
        .asg            B6,         B_r3210
        .asg            B7,         B_d7654
        .asg            B7,         B_r7654
        .asg            B8,         B_d3210
        .asg            B8,         B_s3210
        .asg            B9,         B_s7654
        .asg            B16,        B_sad
        .asg            B17,        B_srcImg
        .asg            B18,        B_s2
        .asg            B19,        B_s3
* ========================================================================= *
* =========================== PIPE LOOP PROLOG ============================ *
        LDNDW   .D2T2   *B_refImg,              B_r7654:B_r3210 ;[ 1,1] 
||      B       .S2     loop
||      MVK     .S1     0x0101,     A_k1
||      ADD     .L2X    A_srcImg,   8,          B_srcImg

        LDDW    .D2T1   *B_srcImg++(16),        A_s7654:A_s3210 ;[ 2,1] 
||      LDDW    .D1T2   *A_srcImg++(16),        B_s7654:B_s3210 ;[ 2,1] 
||      MV      .L2X    A_pitch,    B_pitch
||      PACK2   .L1     A_k1,       A_k1,       A_k1

        LDNDW   .D2T1   *++B_refImg(B_pitch),   A_r7654:A_r3210 ;[ 3,1] 
||      ZERO    .L2     B_sad
||      ZERO    .L1     A_sad
||      MVK     .S1     3,          A_i

* =========================== PIPE LOOP KERNEL ============================ *
loop:
  [!A_i]ADD     .L1     A_sad,      A_s1,       A_sad           ;[13,1] 
||[!A_i]ADD     .S2     B_sad,      B_s3,       B_sad           ;[13,1] 
||[ A_i]B       .S1     loop                                    ;[10,2] 
||      DOTPU4  .M1     A_d3210,    A_k1,       A_s0            ;[10,2] 
||      SUBABS4 .L2     B_s7654,    B_r7654,    B_d7654         ;[ 7,3] 
||      LDNDW   .D2T2   *++B_refImg(B_pitch),   B_r7654:B_r3210 ;[ 1,5] 

  [!A_i]ADD     .S2     B_sad,      B_s2,       B_sad           ;[14,1] 
||      DOTPU4  .M2X    B_d7654,    A_k1,       B_s3            ;[ 8,3] 
||      SUBABS4 .L1     A_s7654,    A_r7654,    A_d7654         ;[ 8,3] 
||      SUBABS4 .L2     B_s3210,    B_r3210,    B_d3210         ;[ 8,3] 
||      LDDW    .D2T1   *B_srcImg++(16),        A_s7654:A_s3210 ;[ 2,5] 
||      LDDW    .D1T2   *A_srcImg++(16),        B_s7654:B_s3210 ;[ 2,5] 

  [ A_i]SUB     .D1     A_i,        1,          A_i             ;[15,1] 
||[!A_i]ADD     .S1     A_sad,      A_s0,       A_sad           ;[15,1] 
||      DOTPU4  .M1     A_d7654,    A_k1,       A_s1            ;[ 9,3] 
||      DOTPU4  .M2X    B_d3210,    A_k1,       B_s2            ;[ 9,3] 
||      SUBABS4 .L1     A_s3210,    A_r3210,    A_d3210         ;[ 9,3] 
||      LDNDW   .D2T1   *++B_refImg(B_pitch),   A_r7654:A_r3210 ;[ 3,5] 

* =========================== PIPE LOOP EPILOG ============================ *
        ADD     .L1     A_sad,      A_s1,       A_sad           ;[13,4] 
||      ADD     .S2     B_sad,      B_s3,       B_sad           ;[13,4] 
||      DOTPU4  .M1     A_d3210,    A_k1,       A_s0            ;[10,5] 

        ADD     .L2     B_sad,      B_s2,       B_sad           ;[14,4] 
||      RET     .S2     B_retaddr

        ADD     .S1     A_sad,      A_s0,       A_sad           ;[15,4] 

        ADD     .L1     A_sad,      A_s1,       A_sad           ;[13,5] 
||      ADD     .S2     B_sad,      B_s3,       B_sad           ;[13,5] 

        ADD     .S2     B_sad,      B_s2,       B_sad           ;[14,5] 

        ADD     .S1     A_sad,      A_s0,       A_sad           ;[15,5] 

        ADD     .S1X    A_sad,      B_sad,      A_retval
* ========================================================================= *
* ========================================================================= *
*   End of file: sad_8x8_h.asm                                              *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
