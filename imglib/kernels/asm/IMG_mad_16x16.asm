
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
*       mad_16x16                                                           *
*                                                                           *
*   USAGE                                                                   *
*       This routine is C-callable and can be called as:                    *
*                                                                           *
*       void mad_16x16                                                      *
*       (                                                                   *
*           const unsigned char *restrict refImg,                           *
*           const unsigned char *restrict srcImg,                           *
*           int pitch,                                                      *
*           int                 h,                                          *
*           int                 v,                                          *
*           unsigned            *restrict match                             *
*       )                                                                   *
*                                                                           *
*       refImg          Reference image.                                    *
*       srcImg[256]     16x16 block image to look for.                      *
*       pitch           Width of reference image.                           *
*       h               Horiz. size of search area.                         *
*       v               Vert.  size of search area. Must be multiple of 2.  *
*       match[2]        Result:                                             *
*                           match[0] is packed x, y.                        *
*                           match[1] is MAD value.                          *
*                                                                           *
*   DESCRIPTION                                                             *
*       This routine returns the location of the minimum absolute           *
*       difference between a 16x16 search block and some block in a         *
*       (h + 16) x (v + 16) search area. h and v are the sizes of the       *
*       search space for the top left coordinate of the search block.       *
*       refImg points to the top left pixel of the search area.             *
*                                                                           *
*            (0,0)          (h,0)      (h+16,0)                             *
*              ;--------------+--------;                                    *
*              ;    search    |        ;                                    *
*              ;    space     |        ;                                    *
*              ;              |        ;        search area                 *
*              ;--------------+        ;        within reference image      *
*            (0,v)          (h,v)      ;                                    *
*              ;                       ;                                    *
*              ;-----------------------;                                    *
*            (0, v+16)                 (v+16,h+16)                          *
*                                                                           *
*       The location is returned relative to the above coordinate system    *
*       as x and y packed in two 16-bit quantities in a 32-bit word:        *
*                                                                           *
*                   31             16 15             0                      *
*                   +----------------+----------------+                     *
*        match[0]:  |       x        |       y        |                     *
*                   +----------------+----------------+                     *
*                                                                           *
*                   31                               0                      *
*                   +---------------------------------+                     *
*        match[1]:  |   SAD value at location x, y    |                     *
*                   +---------------------------------+                     *
*                                                                           *
*   ASSUMPTIONS                                                             *
*       srcImg and refImg do not alias in memory.                           *
*       The routine is written for Little Endian configuration.             *
*       Two MADS are performed together and hence it is assumed that v      *
*       the vertical dimension is a multiple of 2.                          *
*                                                                           *
*   MEMORY NOTE                                                             *
*       No special requirements on alignment of arrays is required.         *
*                                                                           *
*   TECHNIQUES                                                              *
*       The two outer loops are merged, the two inner loops are merged.     *
*       The inner loop process 2 lines of 2 search locations in parallel.   *
*       The search is performed in top-to-bottom, left-to-right order,      *
*       with the earliest match taking precedence in the case of ties.      *
*       Further use is made of C64x specific instructions such as SUBABS4   *
*       and DOTPU4. The SUBABS4 takes the absolute difference on four 8     *
*       bit quantities packed into a 32 bit word. The DOTPU4 performs four  *
*       8 bit wide multiplies and adds the results together.                *
*                                                                           *
*   C CODE                                                                  *
*                                                                           *
*       void mad_16x16                                                      *
*       (                                                                   *
*           const unsigned char *restrict refImg,                           *
*           const unsigned char *restrict srcImg,                           *
*           int pitch, int h, int v,                                        *
*           unsigned int *restrict match                                    *
*       )                                                                   *
*       {                                                                   *
*           int i, j, x, y, matx, maty;                                     *
*           unsigned matpos, matval;                                        *
*                                                                           *
*           matval = ~0U;                                                   *
*           matx   = maty = 0;                                              *
*                                                                           *
*           for (x = 0; x < x; x++)                                         *
*               for (y = 0; y < v; y++)                                     *
*               {                                                           *
*                   unsigned acc = 0;                                       *
*                                                                           *
*                   for (i = 0; i < 16; i++)                                *
*                       for (j = 0; j < 16; j++)                            *
*                           acc += abs(srcImg[i*16 + j] -                   *
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
*       38 * h * v + 20                                                     *
*                                                                           *
*       e.g. h=v= 4:   628 cycles                                           *
*            h=v=32: 38932 cycles                                           *
*                                                                           *
*   CODESIZE                                                                *
*       776 bytes.                                                          *
*                                                                           *
* ------------------------------------------------------------------------- *
*              Copyright (c) 2008 Texas Instruments, Incorporated.          *
*                             All Rights Reserved.                          *
* ========================================================================= *
	    .if     __TI_EABI__
          		 .asg    IMG_mad_16x16,  _IMG_mad_16x16
            .endif
            .global _IMG_mad_16x16

; ================= SYMBOLIC REGISTER ASSIGNMENTS: SETUP ================== ;
        .asg            B15,        B_SP        ; Stack pointer, B datapath
        .asg            B2,         B_csr       ; CSR's value
        .asg            B1,         B_no_gie    ; CSR w/ GIE bit cleared
        .asg            A30,        A_csr       ; Copy of CSR's value
        .asg            B3,         B_ret       ; Return address
; ========================================================================= ;
; ====================== SYMBOLIC REGISTER ASSIGNMENTS =======================
        .asg            A0,         A_best
        .asg            A0,         A_i
        .asg            A0,         A_sub
        .asg            A0,         A_w
        .asg            A1,         A_vl
        .asg            A16,        A_matpos
        .asg            A17,        A_matval
        .asg            A14,        A_ptch
        .asg            A10,        A_ref_ri0d
        .asg            A11,        A_ref_ri0c
        .asg            A18,        A_2diffi_1c
        .asg            A18,        A_2sumi1d
        .asg            A18,        A_diffi_1d
        .asg            A19,        A_2sumi1c
        .asg            A19,        A_sumi1c
        .asg            A2,         A_vl1
        .asg            A20,        A_2diffi_1d
        .asg            A20,        A_2sumi0d
        .asg            A20,        A_diffi_0d
        .asg            A20,        A_diffi_1c
        .asg            A21,        A_matchi1
        .asg            A22,        A_k_ones
        .asg            A23,        A_pitch_8
        .asg            A24,        A_2sumi0c
        .asg            A24,        A_2sumi0cd
        .asg            A24,        A_srchid
        .asg            A25,        A_2sumi1cd
        .asg            A25,        A_diffi_0c
        .asg            A25,        A_srchic
        .asg            A26,        A_2srchid
        .asg            A26,        A_sumi1
        .asg            A26,        A_sumi1cd
        .asg            A27,        A_2diffi_0c
        .asg            A27,        A_2srchic
        .asg            A27,        A_sumi0cd
        .asg            A27,        A_sumi1d
        .asg            A28,        A_2diffi_0d
        .asg            A28,        A_ref_ri2d
        .asg            A28,        A_sumi0c
        .asg            A29,        A_ref_ri2c
        .asg            A29,        A_sumi0d
        .asg            A3,         A_vptch
        .asg            A30,        A_ref_ri1d
        .asg            A31,        A_2sumi1
        .asg            A31,        A_ref_ri1c
        .asg            A4,         A_ref_img
;       .asg            A5,         A_c40
        .asg            A6,         A_hl
        .asg            A6,         A_pitch
        .asg            A7,         A_ffff
        .asg            B6,         B_h
        .asg            A9,         A_bptch
        .asg            B0,         B_best
        .asg            B1,         B_ml
        .asg            B5,         B_matval
        .asg            B16,        B_ref_ri0b
        .asg            B17,        B_ref_ri0a
        .asg            B18,        B_2sumi0ab
        .asg            B18,        B_2sumi0b
        .asg            B18,        B_sumi0a
        .asg            B19,        B_diffi_0b
        .asg            B19,        B_sumi0b
        .asg            B19,        B_sumi1b
        .asg            B20,        B_src_imgcp
        .asg            B21,        B_2diffi_0b
        .asg            B21,        B_2sumi0a
        .asg            B22,        B_matchi0
        .asg            B23,        B_k_ones
        .asg            B24,        B_2sumi1a
        .asg            B24,        B_srchib
        .asg            B25,        B_2diffi_0a
        .asg            B25,        B_diffi_0a
        .asg            B25,        B_srchia
        .asg            B26,        B_2srchib
        .asg            B26,        B_sumi1ab
        .asg            B27,        B_2srchia
        .asg            B27,        B_2sumi1ab
        .asg            B27,        B_diffi_1b
        .asg            B28,        B_2diffi_1b
        .asg            B28,        B_ref_ri2b
        .asg            B29,        B_ref_ri2a
        .asg            B29,        B_sumi1a
        .asg            B30,        B_ref_ri1b
        .asg            B31,        B_2sumi1b
        .asg            B31,        B_ref_ri1a
        .asg            B4,         B_src_img
        .asg            B8,         B_match
        .asg            A8,         A_v
        .asg            B9,         B_2diffi_1a
        .asg            B9,         B_2sumi0
        .asg            B9,         B_diffi_1a
        .asg            B9,         B_sumi0
        .asg            B9,         B_sumi0ab
; ============================================================================

_IMG_mad_16x16:
; parameters: A_refImg, B_srcImg, A_pitch, B_h, A_v, B_match
;             A4,       B4,       A6,      B6,  A8,  B8
 
        STW     .D2T1   A14,        *B_SP--[3]               ; Save A14
||      MVC     .S2     CSR,        B_csr                    ; Remember CSR

        AND             B_csr,      -2,         B_no_gie     ; Clear GIE
||      STW     .D2T1   A11,        *+B_SP[2]                ; Save A11
||      ADD     .D1     A_v,        17,         A_w          ; pitch
||      MPY     .M1     -16,        A_pitch,    A_bptch      ; hpatch
 
        STW     .D2T1   A10,        *+B_SP[1]                ; Save A10
||      MVC     .S2     B_no_gie,   CSR                      ; Disable ints
||      MPY     .M1     A_w,        A_pitch,    A_vptch      ; vptch
||      SUB     .L1     A_pitch,    8,          A_pitch_8    ; pitch - 8
||      MVKL    .S1     0000FFFFh,  A_ffff                   ; save -1
; ===== Interrupts masked here =====                  

        MVKL    .S1     01010101h,  A_k_ones                 ; constant
||      MV      .L1     A_v,        A_vl                     ; vert. v...1
||      LDNDW   .D      *A_ref_img++(8),        B_ref_ri0a:B_ref_ri0b  ; Load ref

        MVKH    .S1     01010101h,  A_k_ones                 ; constant
||      ADD     .L1     -1,         A_vptch,    A_vptch      ; vptch--
||      MPY     .M2X    A_v,        B_h,        B_ml         ; ml = h*v
||      LDNDW   .D      *A_ref_img++(A_pitch_8),A_ref_ri0c:A_ref_ri0d   ; Load
||      MV      .D2     B_src_img,  B_src_imgcp              ; srcimg

        MVKL    .S2     01010101h,  B_k_ones                 ; constant
||      MV      .L1     A_v,        A_vl1                    ; v
||      MVKH    .S1     0000FFFFh,  A_ffff                   ; -1
||      LDNDW   .D2T2   *B_src_imgcp++,         B_srchia:B_srchib      ; Load src
||      SUB     .D1     A_pitch,    A_bptch,    A_bptch      ; 

        MVKH    .S2     01010101h,  B_k_ones                 ; constant
||      OR      .L2     -1,         B_matval,   B_matval     ; matval
||      MV      .S1     A_bptch,    A_ptch                   ; ptch
||      ZERO    .L1     A_hl                                 ; hl 
||      LDNDW   .D      *A_ref_img++(8),        B_ref_ri1a:B_ref_ri1b ; Load ref 

; ============================ PIPE LOOP PROLOG ==============================

        LDNDW   .D2T1   *B_src_imgcp++,         A_srchic:A_srchid     ; Load 
||      ZERO    .S1     A_matpos                             ; matpos

        LDNDW   .D      *A_ref_img++(A_pitch_8),A_ref_ri1c:A_ref_ri1d ;[ 4,1] 

        LDNDW   .D      *A_ref_img++(8),        B_ref_ri2a:B_ref_ri2b ;[ 5,1] 

        LDNDW   .D      *A_ref_img++(A_pitch_8),A_ref_ri2c:A_ref_ri2d ;[ 6,1] 

        SUBABS4 .L2     B_ref_ri1b, B_srchib,   B_diffi_1b   ;[ 7,1]
||      LDNDW   .D2T2   *B_src_imgcp++,  B_2srchia:B_2srchib ;[ 7,1]
||      B       .S2     L_5 + 12                             ;       

        LDNDW   .D2T1   *B_src_imgcp++,  A_2srchic:A_2srchid ;[ 8,1]
||      B       .S2     L_6 + 4                              ;       

M_LOOP:
        ADD     .D1     -2,         A_vl,       A_vl         ; vl-= 2
||      MPY     .M1     0, A_matchi1, A_matchi1              ; matchi1
||[!A_vl1 ]MV   .S1     A_v,        A_vl1                    ;[16,0] 
||      SUBABS4 .L2     B_ref_ri1a, B_srchia,   B_diffi_1a   ;[ 9,1] 
||      SUBABS4 .L1     A_ref_ri1d, A_srchid,   A_diffi_1d   ;[ 9,1] 
||      LDNDW   .D2T2   *B_src_imgcp++,  B_srchia:B_srchib   ;[ 1,2] 
||      B       .S2     L_7 + 8                              ;      

        MVK     .S1     7,          A_i                      ; i = 7
||      MV      .D2     B_ref_ri2b, B_ref_ri0b               ;[10,1]
||      SUBABS4 .L2     B_ref_ri0b, B_srchib,   B_diffi_0b   ;[10,1]
||      DOTPU4  .M2     B_diffi_1a, B_k_ones,   B_sumi1a     ;[10,1] 
||      SUBABS4 .L1     A_ref_ri1c, A_srchic,   A_diffi_1c   ;[10,1] 
||      LDNDW   .D      *A_ref_img++(8), B_ref_ri1a:B_ref_ri1b;[ 2,2]
||      B       .S2     L_8 + 8                              ;[ 2,2] 

        MV      .S2     B_ref_ri2a, B_ref_ri0a               ;[11,1]
||      DOTPU4  .M2     B_diffi_1b, B_k_ones,   B_sumi1b     ;[11,1]
||      SUBABS4 .L2     B_ref_ri0a, B_srchia,   B_diffi_0a   ;[11,1]
||      SUBABS4 .L1     A_ref_ri0d, A_srchid,   A_diffi_0d   ;[11,1]
||      DOTPU4  .M1     A_diffi_1c, A_k_ones,   A_sumi1c     ;[11,1]
||      LDNDW   .D2T1   *B_src_imgcp++,  A_srchic:A_srchid   ;[ 3,2]
||      B       .S1     LOOP_X                               ;
||[!A_vl]MV     .D1     A_vptch,    A_ptch                   ; ptch   

        SUBABS4 .L1     A_ref_ri0c, A_srchic,   A_diffi_0c   ;[12,1]
||      DOTPU4  .M2     B_diffi_0a, B_k_ones,   B_sumi0a     ;[12,1]
||      SUBABS4 .L2     B_ref_ri1a, B_2srchia,  B_2diffi_0a  ;[12,1]
||      DOTPU4  .M1     A_diffi_0d, A_k_ones,   A_sumi0d     ;[12,1]
||      LDNDW   .D      *A_ref_img++(A_pitch_8),A_ref_ri1c:A_ref_ri1d ;[ 4,2]
||[!A_vl]MV     .S1     A_v,         A_vl                    ; vl = v 
||      ZERO    .S2     B_matchi0                            ; matchi0 

; ============================ PIPE LOOP KERNEL ==============================
LOOP_X:

  [ A_i]ADD     .S1     A_i,        -1,         A_i           ;[17,1]
||      ADD     .S2     B_sumi1a,   B_sumi1b,   B_sumi1ab     ;[17,1]
||      DOTPU4  .M2     B_2diffi_1b,B_k_ones,   B_2sumi1b     ;[17,1]
||      DOTPU4  .M1     A_2diffi_0d,A_k_ones,   A_2sumi0d     ;[17,1]
||      ADD     .D1     A_sumi1c,   A_sumi1d,   A_sumi1cd     ;[17,1]
||      SUBABS4 .L2     B_ref_ri1a, B_srchia,   B_diffi_1a    ;[ 9,2]
||      SUBABS4 .L1     A_ref_ri1d, A_srchid,   A_diffi_1d    ;[ 9,2]
||      LDNDW   .D2T2   *B_src_imgcp++,  B_srchia:B_srchib    ;[ 1,3]

        ADD     .S2     B_sumi0a,   B_sumi0b,   B_sumi0ab     ;[18,1]
||      DOTPU4  .M1     A_2diffi_1d,A_k_ones,   A_2sumi1d     ;[18,1]
||      ADD     .S1     A_sumi0c,   A_sumi0d,   A_sumi0cd     ;[18,1]
||      ADD     .D2     B_ref_ri2b, 0,          B_ref_ri0b    ;[10,2]
||      SUBABS4 .L2     B_ref_ri0b, B_srchib,   B_diffi_0b    ;[10,2]
||      DOTPU4  .M2     B_diffi_1a, B_k_ones,   B_sumi1a      ;[10,2]
||      SUBABS4 .L1     A_ref_ri1c, A_srchic,   A_diffi_1c    ;[10,2]
||      LDNDW   .D      *A_ref_img++(8), B_ref_ri1a:B_ref_ri1b;[ 2,3]

  [ A_i]B       .S1     LOOP_X                                ;[19,1]
||      ADD     .D1X    A_sumi1cd,  B_sumi1ab,  A_sumi1       ;[19,1]
||      ADD     .S2     B_ref_ri2a, 0,          B_ref_ri0a    ;[11,2]
||      DOTPU4  .M2     B_diffi_1b, B_k_ones,   B_sumi1b      ;[11,2]
||      SUBABS4 .L2     B_ref_ri0a, B_srchia,   B_diffi_0a    ;[11,2]
||      SUBABS4 .L1     A_ref_ri0d, A_srchid,   A_diffi_0d    ;[11,2]
||      DOTPU4  .M1     A_diffi_1c, A_k_ones,   A_sumi1c      ;[11,2]
||      LDNDW   .D2T1   *B_src_imgcp++,  A_srchic:A_srchid    ;[ 3,3]

        ADD     .S2X    B_sumi0ab,  A_sumi0cd,  B_sumi0       ;[20,1]
||      ADD     .S1     A_matchi1,  A_sumi1,    A_matchi1     ;[20,1]
||      SUBABS4 .L1     A_ref_ri0c, A_srchic,   A_diffi_0c    ;[12,2]
||      DOTPU4  .M2     B_diffi_0a, B_k_ones,   B_sumi0a      ;[12,2]
||      SUBABS4 .L2     B_ref_ri1a, B_2srchia,  B_2diffi_0a   ;[12,2]
||      DOTPU4  .M1     A_diffi_0d, A_k_ones,   A_sumi0d      ;[12,2]
||      LDNDW   .D      *A_ref_img++(A_pitch_8),A_ref_ri1c:A_ref_ri1d   ;[ 4,3]

L_5:    ADD     .D2     B_matchi0,  B_sumi0,    B_matchi0     ;[21,1]
||      ADD     .S2     B_2sumi1a,  B_2sumi1b,  B_2sumi1ab    ;[21,1]
||      ADD     .S1     A_2sumi0c,  A_2sumi0d,  A_2sumi0cd    ;[21,1]
||      SUBABS4 .L2     B_ref_ri2a, B_2srchia,  B_2diffi_1a   ;[13,2]
||      DOTPU4  .M1     A_diffi_1d, A_k_ones,   A_sumi1d      ;[13,2]
||      SUBABS4 .L1     A_ref_ri2d, A_2srchid,  A_2diffi_1d   ;[13,2]
||      DOTPU4  .M2     B_2diffi_0a,B_k_ones,   B_2sumi0a     ;[13,2]
||      LDNDW   .D      *A_ref_img++(8), B_ref_ri2a:B_ref_ri2b;[ 5,3]

L_6:    ADD     .D2     B_2sumi0a,  B_2sumi0b,  B_2sumi0ab    ;[22,1]
||      ADD     .S1     A_2sumi1c,  A_2sumi1d,  A_2sumi1cd    ;[22,1]
||      DOTPU4  .M1     A_diffi_0c, A_k_ones,   A_sumi0c      ;[14,2]
||      SUBABS4 .L1     A_ref_ri2c, A_2srchic,  A_2diffi_1c   ;[14,2]
||      DOTPU4  .M2     B_diffi_0b, B_k_ones,   B_sumi0b      ;[14,2]
||      SUBABS4 .L2     B_ref_ri1b, B_2srchib,  B_2diffi_0b   ;[14,2]
||      LDNDW   .D      *A_ref_img++(A_pitch_8), A_ref_ri2c:A_ref_ri2d  ;[ 6,3]

L_7:    ADD     .S1X    A_2sumi1cd, B_2sumi1ab, A_2sumi1     ;[23,1]
||      ADD     .S2X    B_2sumi0ab, A_2sumi0cd, B_2sumi0     ;[23,1]
||      ADD     .D1     A_ref_ri2c, 0,          A_ref_ri0c   ;[15,2]
||      DOTPU4  .M1     A_2diffi_1c,A_k_ones,   A_2sumi1c    ;[15,2]
||      SUBABS4 .L1     A_ref_ri1c, A_2srchic,  A_2diffi_0c  ;[15,2]
||      DOTPU4  .M2     B_2diffi_1a,B_k_ones,   B_2sumi1a    ;[15,2]
||      SUBABS4 .L2     B_ref_ri1b, B_srchib,   B_diffi_1b   ;[ 7,3]
||      LDNDW   .D2T2   *B_src_imgcp++,  B_2srchia:B_2srchib ;[ 7,3]


L_8:    ADD     .S2     B_matchi0,  B_2sumi0,   B_matchi0    ;[24,1]
||      ADD     .S1     A_matchi1,  A_2sumi1,   A_matchi1    ;[24,1]
||      ADD     .D1     A_ref_ri2d, 0,          A_ref_ri0d   ;[16,2]
||      DOTPU4  .M2     B_2diffi_0b,B_k_ones,   B_2sumi0b    ;[16,2]
||      SUBABS4 .L2     B_ref_ri2b, B_2srchib,  B_2diffi_1b  ;[16,2]
||      SUBABS4 .L1     A_ref_ri1d, A_2srchid,  A_2diffi_0d  ;[16,2]
||      DOTPU4  .M1     A_2diffi_0c,A_k_ones,   A_2sumi0c    ;[16,2]
||      LDNDW   .D2T1   *B_src_imgcp++,  A_2srchic:A_2srchid ;[ 8,3]

; ============================ PIPE LOOP EPILOG ==============================
; EPILOG:

        ADD     .S2     B_sumi1a,   B_sumi1b,   B_sumi1ab    ;[17,3]
||      DOTPU4  .M2     B_2diffi_1b,B_k_ones,   B_2sumi1b    ;[17,3]
||      DOTPU4  .M1     A_2diffi_0d,A_k_ones,   A_2sumi0d    ;[17,3]
||      ADD     .D1     A_sumi1c,   A_sumi1d,   A_sumi1cd    ;[17,3]
||      SUB     .S1     A_ref_img,  A_ptch,     A_ref_img    ; 

        ADD     .S2     B_sumi0a,   B_sumi0b,   B_sumi0ab    ;[18,3]
||      DOTPU4  .M1     A_2diffi_1d,A_k_ones,   A_2sumi1d    ;[18,3]
||      ADD     .S1     A_sumi0c,   A_sumi0d,   A_sumi0cd    ;[18,3]
||      MV      .L2     B_src_img,  B_src_imgcp              ;

        ADD     .S1X    A_sumi1cd,  B_sumi1ab,  A_sumi1      ;[19,3]
||      LDNDW   .D      *A_ref_img++(8), B_ref_ri0a:B_ref_ri0b;

        ADD     .S2X    B_sumi0ab,  A_sumi0cd,  B_sumi0      ;[20,3]
||      ADD     .S1     A_matchi1,  A_sumi1,    A_matchi1    ;[20,3]
||      LDNDW   .D      *A_ref_img++(A_pitch_8), A_ref_ri0c:A_ref_ri0d;

        ADD     .L2     B_matchi0,  B_sumi0,    B_matchi0    ;[21,3]
||      ADD     .S2     B_2sumi1a,  B_2sumi1b,  B_2sumi1ab   ;[21,3]
||      ADD     .S1     A_2sumi0c,  A_2sumi0d,  A_2sumi0cd   ;[21,3]
||      LDNDW   .D2T2   *B_src_imgcp++,  B_srchia:B_srchib   ;

        ADD     .S2     B_2sumi0a,  B_2sumi0b,  B_2sumi0ab   ;[22,3]
||      ADD     .S1     A_2sumi1c,  A_2sumi1d,  A_2sumi1cd   ;[22,3]
|| [B_ml]ADD    .L2     B_ml,       -2,         B_ml         ;
||      LDNDW   .D      *A_ref_img++(8),        B_ref_ri1a:B_ref_ri1b; Load ref 

        ADD     .S1X    A_2sumi1cd, B_2sumi1ab, A_2sumi1     ;[23,3]
||      ADD     .L2X    B_2sumi0ab, A_2sumi0cd, B_2sumi0     ;[23,3]
||[ B_ml]B      .S2     M_LOOP                               ;
||      LDNDW   .D2T1   *B_src_imgcp++,         A_srchic:A_srchid ; Load 

        ADD     .L2     B_matchi0,  B_2sumi0,   B_matchi0    ;[24,3]
||      ADD     .S1     A_matchi1,  A_2sumi1,   A_matchi1    ;[24,3]
||      LDNDW   .D      *A_ref_img++(A_pitch_8),  A_ref_ri1c:A_ref_ri1d ;[ 4,1] 
||      MV      .L1X    B_matval,   A_matval

; ============================================================================
; END:

        CMPLTU  .L2     B_matchi0,  B_matval,   B_best       ;
||      ADD     .L1     -1,         A_vl1,      A_vl1        ;
||      MV      .S1     A_bptch,    A_ptch                   ;
||      LDNDW   .D      *A_ref_img++(8),        B_ref_ri2a:B_ref_ri2b ;[ 5,1] 

  [ B_best] MV    .L2   B_matchi0,  B_matval                 ;
||[ B_best] MV    .L1X  B_matchi0,  A_matval                 ;
||[ B_best] PACK2 .S1   A_hl,       A_vl1,      A_matpos     ;
||          LDNDW .D    *A_ref_img++(A_pitch_8),A_ref_ri2c:A_ref_ri2d ;[ 6,1]

        ADD     .S1     -1,         A_vl1,      A_vl1        ;
||      CMPLTU  .L1     A_matchi1,  A_matval,   A_best       ; XP stall
||      SUBABS4 .L2     B_ref_ri1b, B_srchib,   B_diffi_1b   ;[ 7,1] 
||      LDNDW   .D2T2   *B_src_imgcp++,  B_2srchia:B_2srchib ;[ 7,1] 
||[ B_ml]B      .S2     L_5 + 12                             ;       

  [ A_best] PACK2 .L1   A_hl,       A_vl1,      A_matpos     ;
||[!A_vl1 ] ADD   .D1   A_hl,       1,          A_hl         ;
||[ A_best] MV    .S2X  A_matchi1,  B_matval                 ;
||          LDNDW .D2T1 *B_src_imgcp++,  A_2srchic:A_2srchid ;[ 8,1] 
||[ B_ml]   B     .S1   L_6 + 4                              ;     

        ;==== Branch occurs                                  

; ========================================================================= ;
        LDW     .D2T1   *+B_SP[1],  A10

        RET     .S2     B_ret                                ; Return to caller
||      LDW     .D2T1   *+B_SP[2],  A11

        MV      .S1     A_v,        A_sub                    ;
||      AND     .L1     A_matpos,   A_ffff,     A_vl         ;
||      LDW     .D2T1   *++B_SP[3],  A14

        SUB     .L1     A_sub,      1,          A_sub        ;
||      SHL     .S1     A_ffff,     16,         A_ffff       ;

        SUB     .S1     A_sub,      A_vl,       A_vl         ;
||      AND     .L1     A_matpos,   A_ffff,     A_matpos     ;

        ADD     .S1     A_matpos,   A_vl,       A_matpos     ;
||      MV      .L1X    B_matval,   A_matval                 ;
        
        STNDW   .D2T1   A_matval:A_matpos,      *B_match     ;
||      MVC     .S2     B_csr,            CSR         ; Restore CSR
; ===== Interruptibility state restored here =====
; ===== Branch Occurs =====

* ========================================================================= *
*   End of file:  mad_16x16_h.asm                                           *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
