
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
*       idct_8x8_12q4 -- IEEE-1180/1990 Compliant IDCT, Little Endian.      *
*                                                                           *
*   USAGE                                                                   *
*       This routine is C callable, and has the following C prototype:      *
*                                                                           *
*           void idct_8x8_12q4(short idct_data[], unsigned num_idcts)       *
*                                                                           *
*       The idct_8x8_12q4 routine accepts a list of 8x8 DCT coeffient blocks*
*       and performs IDCTs on each.  The array should be aligned to a       *
*       64-bit boundary, and be laid out equivalently to the C array        *
*       idct_data[num_idcts][8][8].  The input data should be in 12Q4       *
*       format.                                                             *
*                                                                           *
*       The routine operates entirely in-place, requiring no additional     *
*       storage for intermediate results.                                   *
*                                                                           *
*       This code requires '62 + 92 * num_idcts' cycles to process          *
*       'num_idcts' blocks, including 6 cycles of function call overhead.   *
*                                                                           *
*   DESCRIPTION                                                             *
*       The idct_8x8_12q4 algorithm performs an IEEE-1180 compliant IDCT,   *
*       complete with rounding and saturation to signed 9-bit quantities.   *
*       The input coefficients are assumed to be signed 16-bit DCT          *
*       coefficients in 12Q4 format.                                        *
*                                                                           *
*       void idct_8x8_12q4(short idct_data[], unsigned num_idcts)           *
*       {                                                                   *
*           /* -------------------------------------------------------- */  *
*           /*  Cosine Constants (Q16, scaled down by sqrt(2)).         */  *
*           /* -------------------------------------------------------- */  *
*           const unsigned short C0 = 0xB505;                               *
*           const unsigned short C1 = 0xB18B, C2 = 0xA73D;                  *
*           const unsigned short C3 = 0x9683, C5 = 0x6492;                  *
*           const unsigned short C6 = 0x4546, C7 = 0x2351;                  *
*                                                                           *
*           /* -------------------------------------------------------- */  *
*           /*  Intermediate values (used in both loops).               */  *
*           /* -------------------------------------------------------- */  *
*           short F0, F1, F2, F3, F4, F5, F6, F7;  /* stage 0           */  *
*           short P0, P1, R0, R1, Q0, Q1, S0, S1;  /* stage 1           */  *
*           short p0, p1, r0, r1, q0, q1, s0, s1;  /* stage 2           */  *
*           short g0, g1, g2, g3, h0, h1, h2, h3;  /* stage 3           */  *
*           short f0, f1, f2, f3, f4, f5, f6, f7;  /* stage 4           */  *
*           short f0r,f1r,f2r,f3r,f4r,f5r,f6r,f7r; /* rounded           */  *
*           int   f0s,f1s,f2s,f3s,f4s,f5s,f6s,f7s; /* saturated         */  *
*           int   f0t,f1t,f2t,f3t,f4t,f5t,f6t,f7t; /* truncated         */  *
*           int   i, j;                            /* loop counts       */  *
*           short (*idct)[8][8] = (short (*)[8][8])idct_data;               *
*                                                                           *
*           /* -------------------------------------------------------- */  *
*           /*  Vertical Pass                                           */  *
*           /*                                                          */  *
*           /*  This pass performs a single 8-pt IDCT per iteration.    */  *
*           /*  Inputs are in 12Q4 format, and results of this pass     */  *
*           /*  are in 11Q5 format. (Actually, the results are halfway  */  *
*           /*  between 11Q5 and 12Q4 due to the scaling by sqrt(2).)   */  *
*           /*                                                          */  *
*           /*  The outer loop steps between IDCT blocks, whereas the   */  *
*           /*  inner loop focuses on columns within each IDCT block.   */  *
*           /* -------------------------------------------------------- */  *
*           for (i = 0; i < num_idcts; i++)                                 *
*           {                                                               *
*               for (j = 0; j < 8; j++)                                     *
*               {                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 0:  Load in freq-domain coefficients.     */  *
*                   /* ------------------------------------------------ */  *
*                   F0 = idct[i][0][j];                                     *
*                   F1 = idct[i][1][j];                                     *
*                   F2 = idct[i][2][j];                                     *
*                   F3 = idct[i][3][j];                                     *
*                   F4 = idct[i][4][j];                                     *
*                   F5 = idct[i][5][j];                                     *
*                   F6 = idct[i][6][j];                                     *
*                   F7 = idct[i][7][j];                                     *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 1 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   P0 = F0;                P1 = F4;                        *
*                   R1 = F2;                R0 = F6;                        *
*                                                                           *
*                   Q1 = (F1*C7 - F7*C1 + 0x8000) >> 16;                    *
*                   Q0 = (F5*C3 - F3*C5 + 0x8000) >> 16;                    *
*                   S0 = (F5*C5 + F3*C3 + 0x8000) >> 16;                    *
*                   S1 = (F1*C1 + F7*C7 + 0x8000) >> 16;                    *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 2 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   p0 = ((int)P0 + (int)P1 + 1 ) >> 1;                     *
*                   p1 = ((int)P0 - (int)P1     ) >> 1;                     *
*                   r1 = (R1*C6 - R0*C2 + 0x8000) >> 16;                    *
*                   r0 = (R1*C2 + R0*C6 + 0x8000) >> 16;                    *
*                                                                           *
*                   s1 = (S1 + S0);         q1 = (Q1 + Q0);                 *
*                   s0 = (S1 - S0);         q0 = (Q1 - Q0);                 *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 3 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   g0 = (p0 + r0);         g1 = (p1 + r1);                 *
*                   h0 = (p0 - r0);         h1 = (p1 - r1);                 *
*                                                                           *
*                   h2 = s1;                g2 = q1;                        *
*                   g3 = (s0*C0 - q0*C0 + 0x8000) >> 16;                    *
*                   h3 = (s0*C0 + q0*C0 + 0x8000) >> 16;                    *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 4 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   f0 = (g0 + h2);         f7 = (g0 - h2);                 *
*                   f1 = (g1 + h3);         f6 = (g1 - h3);                 *
*                   f2 = (h1 + g3);         f5 = (h1 - g3);                 *
*                   f3 = (h0 + g2);         f4 = (h0 - g2);                 *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 5:  Write sample-domain results.          */  *
*                   /* ------------------------------------------------ */  *
*                   idct[i][0][j] = f0;                                     *
*                   idct[i][1][j] = f1;                                     *
*                   idct[i][2][j] = f2;                                     *
*                   idct[i][3][j] = f3;                                     *
*                   idct[i][4][j] = f4;                                     *
*                   idct[i][5][j] = f5;                                     *
*                   idct[i][6][j] = f6;                                     *
*                   idct[i][7][j] = f7;                                     *
*               }                                                           *
*           }                                                               *
*                                                                           *
*           /* -------------------------------------------------------- */  *
*           /*  Horizontal Pass                                         */  *
*           /*                                                          */  *
*           /*  This performs one IDCT per iteration on the 11Q5        */  *
*           /*  results from the previous pass.  Both horizontal and    */  *
*           /*  vertical passes are scaled down by sqrt(2) -- the net   */  *
*           /*  effect of which is that the IDCT results generated by   */  *
*           /*  this pass (prior to saturation) are also 11Q5 results,  */  *
*           /*  only with no sqrt(2) factors remaining.                 */  *
*           /*                                                          */  *
*           /*  The IDCT butterflies in this pass are identical to the  */  *
*           /*  ones in the vertical pass, except for an additional     */  *
*           /*  rounding value which is added into the DC term early    */  *
*           /*  in the flow graph.                                      */  *
*           /*                                                          */  *
*           /*  The 11Q5 sample-domain terms are saturated to 9Q7       */  *
*           /*  values, and then truncated to 9Q0 results before        */  *
*           /*  storing.                                                */  *
*           /*                                                          */  *
*           /*  The outer loop steps between IDCT blocks, whereas the   */  *
*           /*  inner loop focuses on rows within each IDCT block.      */  *
*           /* -------------------------------------------------------- */  *
*           for (i = num_idcts - 1; i >= 0; i--)                            *
*           {                                                               *
*               for (j = 0; j < 8; j++)                                     *
*               {                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 0:  Load in freq.-domain coefficients.    */  *
*                   /* ------------------------------------------------ */  *
*                   F0 = idct[i][j][0];                                     *
*                   F1 = idct[i][j][1];                                     *
*                   F2 = idct[i][j][2];                                     *
*                   F3 = idct[i][j][3];                                     *
*                   F4 = idct[i][j][4];                                     *
*                   F5 = idct[i][j][5];                                     *
*                   F6 = idct[i][j][6];                                     *
*                   F7 = idct[i][j][7];                                     *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 1 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   P0 = F0;                P1 = F4;                        *
*                   R1 = F2;                R0 = F6;                        *
*                                                                           *
*                   Q1 = (F1*C7 - F7*C1 + 0x8000) >> 16;                    *
*                   Q0 = (F5*C3 - F3*C5 + 0x8000) >> 16;                    *
*                   S0 = (F5*C5 + F3*C3 + 0x8000) >> 16;                    *
*                   S1 = (F1*C1 + F7*C7 + 0x8000) >> 16;                    *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 2 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   p0 = (((int)P0 + (int)P1 + 1) >> 1) + 15;               *
*                   p1 = (((int)P0 - (int)P1    ) >> 1) + 16;               *
*                   r1 = (R1*C6 - R0*C2 + 0x8000) >> 16;                    *
*                   r0 = (R1*C2 + R0*C6 + 0x8000) >> 16;                    *
*                                                                           *
*                   s1 = (S1 + S0);         q1 = (Q1 + Q0);                 *
*                   s0 = (S1 - S0);         q0 = (Q1 - Q0);                 *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 3 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   g0 = (p0 + r0);         g1 = (p1 + r1);                 *
*                   h0 = (p0 - r0);         h1 = (p1 - r1);                 *
*                                                                           *
*                   h2 = s1;                g2 = q1;                        *
*                   g3 = (s0*C0 - q0*C0 + 0x8000) >> 16;                    *
*                   h3 = (s0*C0 + q0*C0 + 0x8000) >> 16;                    *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 4 of signal flow graph.                   */  *
*                   /* ------------------------------------------------ */  *
*                   f0 = (g0 + h2);         f7 = (g0 - h2);                 *
*                   f1 = (g1 + h3);         f6 = (g1 - h3);                 *
*                   f2 = (h1 + g3);         f5 = (h1 - g3);                 *
*                   f3 = (h0 + g2);         f4 = (h0 - g2);                 *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 4.1:  Q-pt adjust: Bit 15 is don't-care.  */  *
*                   /* ------------------------------------------------ */  *
*                   f0r = f0 + f0;          f7r = f7 + f7;                  *
*                   f1r = f1 + f1;          f6r = f6 + f6;                  *
*                   f2r = f2 + f2;          f5r = f5 + f5;                  *
*                   f3r = f3 + f3;          f4r = f4 + f4;                  *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 4.2:  Saturate results to 9Q6.            */  *
*                   /* ------------------------------------------------ */  *
*                   f0s = f0r>0x3FFF?0x3FFF: f0r<-0x4000?-0x4000 : f0r;     *
*                   f1s = f1r>0x3FFF?0x3FFF: f1r<-0x4000?-0x4000 : f1r;     *
*                   f2s = f2r>0x3FFF?0x3FFF: f2r<-0x4000?-0x4000 : f2r;     *
*                   f3s = f3r>0x3FFF?0x3FFF: f3r<-0x4000?-0x4000 : f3r;     *
*                   f4s = f4r>0x3FFF?0x3FFF: f4r<-0x4000?-0x4000 : f4r;     *
*                   f5s = f5r>0x3FFF?0x3FFF: f5r<-0x4000?-0x4000 : f5r;     *
*                   f6s = f6r>0x3FFF?0x3FFF: f6r<-0x4000?-0x4000 : f6r;     *
*                   f7s = f7r>0x3FFF?0x3FFF: f7r<-0x4000?-0x4000 : f7r;     *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 4.3:  Truncate results to 9Q0.            */  *
*                   /* ------------------------------------------------ */  *
*                   f0t = f0s >> 6;         f7t = f7s >> 6;                 *
*                   f1t = f1s >> 6;         f6t = f6s >> 6;                 *
*                   f2t = f2s >> 6;         f5t = f5s >> 6;                 *
*                   f3t = f3s >> 6;         f4t = f4s >> 6;                 *
*                                                                           *
*                   /* ------------------------------------------------ */  *
*                   /*  Stage 5:  Store sample-domain results.          */  *
*                   /* ------------------------------------------------ */  *
*                   idct[i][j][0] = f0t;                                    *
*                   idct[i][j][1] = f1t;                                    *
*                   idct[i][j][2] = f2t;                                    *
*                   idct[i][j][3] = f3t;                                    *
*                   idct[i][j][4] = f4t;                                    *
*                   idct[i][j][5] = f5t;                                    *
*                   idct[i][j][6] = f6t;                                    *
*                   idct[i][j][7] = f7t;                                    *
*               }                                                           *
*           }                                                               *
*                                                                           *
*           return;                                                         *
*       }                                                                   *
*                                                                           *
*       Note:  This code guarantees correct operation, even in the case     *
*       that 'num_idcts == 0'.  In that case, the function runs for only    *
*       13 cycles (counting 6 cycles of function-call overhead), due to     *
*       early-exit code.  Also, the assembly code imposes additional data   *
*       alignment restrictions that are not present in the C code above.    *
*                                                                           *
*   TECHNIQUES                                                              *
*       All levels of looping are collapsed into single loops which are     *
*       pipelined.  The outer loop focuses on 8-pt IDCTs, whereas the       *
*       inner loop controls the column-pointer to handle jumps between      *
*       IDCT blocks.  (The column-pointer adjustment is handled by a        *
*       four-phase rotating "fixup" constant which takes the place of       *
*       the original inner-loop.)                                           *
*                                                                           *
*       For performance, portions of the outer-loop code have been          *
*       inter-scheduled with the prologs and epilogs of both loops.         *
*       Finally, cosine term registers are reused between the horizontal    *
*       and vertical loops to save the need for reinitialization.           *
*                                                                           *
*       To save codesize, prolog and epilog collapsing have been performed  *
*       to the extent that performance is not affected.  The remaining      *
*       prolog and epilog code has been interscheduled with code outside    *
*       the loops to improve performance.                                   *
*                                                                           *
*       Additional section-specific optimization notes are provided below.  *
*                                                                           *
*   ASSUMPTIONS                                                             *
*       This is a LITTLE ENDIAN implementation.                             *
*                                                                           *
*       The input array must be aligned on a double-word boundary.          *
*                                                                           *
*   MEMORY NOTE                                                             *
*       No bank conflicts occur.                                            *
*       The input array must be aligned on a double-word boundary.          *
*                                                                           *
*       Bank usage for N 32-bit banks:                                      *
*                                                                           *
*           Vert loop accesses:  2 of N banks for 54% of cycles             *
*                                1 of N banks for 36% of cycles             *
*                                0 of N banks for  9% of cycles             *
*                                                                           *
*           Horiz loop accesses: 4 of N banks for 16% of cycles             *
*                                2 of N banks for 33% of cycles             *
*                                0 of N banks for 50% of cycles             *
*                                                                           *
*       The code may perform speculative reads of up to 128 bytes           *
*       beyond the end or before the start of the IDCT array.  The          *
*       speculatively accessed data is ignored.                             *
*                                                                           *
*   NOTES                                                                   *
*       This is fully interruptable and fully reentrant.                    *
*                                                                           *
*       The cosine terms have all been scaled by sqrt(2), so that the       *
*       "c4" term is basically an even power of 2.                          *
*                                                                           *
*   CYCLES                                                                  *
*       cycles = 62 + 92 * num_idcts, for num_idcts > 0                     *
*       cycles = 13,                  for num_idcts == 0.                   *
*                                                                           *
*       For num_idcts =  6, cycles = 614.                                   *
*       For num_idcts = 24, cycles = 2270.                                  *
*                                                                           *
*   CODESIZE                                                                *
*       968 bytes                                                           *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *


            .sect ".text:hand"
            .if     __TI_EABI__
          		 .asg    IMG_idct_8x8_12q4,  _IMG_idct_8x8_12q4
            .endif
            .global _IMG_idct_8x8_12q4
_IMG_idct_8x8_12q4:
; ====================== SYMBOLIC CONSTANT ASSIGNMENTS =======================
        .asg            0xB505,     cst_c0  ; cos term c0 (scaled by sqrt(2))
        .asg            0xB18B,     cst_c1  ; cos term c1 (scaled by sqrt(2))
        .asg            0xA73D,     cst_c2  ; cos term c2 (scaled by sqrt(2))
        .asg            0x9683,     cst_c3  ; cos term c3 (scaled by sqrt(2))
        .asg            0x8000,     cst_c4  ; cos term c4 (scaled by sqrt(2))
        .asg            0x6492,     cst_c5  ; cos term c5 (scaled by sqrt(2))
        .asg            0x4546,     cst_c6  ; cos term c6 (scaled by sqrt(2))
        .asg            0x2351,     cst_c7  ; cos term c7 (scaled by sqrt(2))
        .asg            0x01011D01, cst_fix ; Pointer fixup constant (v_loop)
        .asg            0x000F0010, cst_rnd ; Rounding constant (h_loop)
; =================== SYMBOLIC REGISTER ASSIGNMENTS: MISC ====================
        .asg            B3,         B_ret   ; Return address from function
        .asg            A30,        A_cnt   ; Loop trip count
        .asg            A16,        A_C00   ; Cosine term c0 packed twice
        .asg            A17,        A_C17   ; Cosine terms c1, c7 (packed)
        .asg            A18,        A_C26   ; Cosine terms c2, c6 (packed)
        .asg            A19,        A_C35   ; Cosine terms c3, c5 (packed)
        .asg            B19,        B_C35   ; Cosine terms c3, c5 (packed)
        .asg            A20,        A_C53   ; Cosine terms c5, c3 (packed)
        .asg            A21,        A_C62   ; Cosine terms c6, c2 (packed)
        .asg            A22,        A_C71   ; Cosine terms c7, c1 (packed)
; ================== SYMBOLIC REGISTER ASSIGNMENTS: V_LOOP ===================
        ; Constants held in registers
        .asg            A27,        A_k_neg ; Negation cst: 0x0000FFFF
        .asg            B21,        B_k_fix ; Pointer fixup cst: 0x01011D01
        .asg            A6,         A_fx2   ; Pointer fixup, output pointer
        .asg            B16,        B_fx1   ; Pointer fixup, input pointer

        ; Pointers and loop control
        .asg            B23,        B_i_ptr ; Input pointer
        .asg            A4,         A_o_ptr ; Output pointer
        .asg            B4,         B_i     ; Loop counter
        .asg            B0,         B_c     ; Prolog collapse predicate

        ; Inputs (common to both IDCTs)
        .asg            B29,        B_F00   ; Freq domain term F0 (two cols)
        .asg            B9,         B_F11   ; Freq domain term F1 (two cols)
        .asg            B2,         B_F22   ; Freq domain term F2 (two cols)
        .asg            B31,        B_F33   ; Freq domain term F3 (two cols)
        .asg            B22,        B_F44   ; Freq domain term F4 (two cols)
        .asg            B18,        B_F55   ; Freq domain term F5 (two cols)
        .asg            B8,         B_F66   ; Freq domain term F6 (two cols)
        .asg            B17,        B_F77   ; Freq domain term F7 (two cols)

        ; Symbolic names for IDCTs in even-numbered columns.
        .asg            B19,        B_F04   ; Freq terms F0, F4 (packed)
        .asg            B9,         B_F17   ; Freq terms F1, F7 (packed)
        .asg            B9,         B_F26   ; Freq terms F2, F6 (packed)
        .asg            B19,        B_F40   ; Freq terms F4, F0 (packed)
        .asg            B18,        B_F53   ; Freq terms F5, F3 (packed)
        .asg            B6,         B_F0n4  ; F04, with term F4 'negated'
        .asg            B6,         B_p0p1  ; Nodes p0, p1 (packed)
        .asg            B26,        B_r0    ; Node r0 in signal flow graph
        .asg            B27,        B_r1    ; Node r1 in signal flow graph
        .asg            B16,        B_r0r1  ; Nodes r0, r1 (packed)
        .asg            B30,        B_g0g1  ; Nodes g0, g1 (packed)
        .asg            B5,         B_h0h1  ; Nodes h0, h1 (packed)
        .asg            B8,         B_Q1    ; Node Q1 in signal flow graph
        .asg            B28,        B_Q0    ; Node Q0 in signal flow graph
        .asg            B25,        B_S0    ; Node S0 in signal flow graph
        .asg            B7,         B_S1    ; Node S1 in signal flow graph
        .asg            B25,        B_S0Q0  ; Nodes S0, Q0 (packed)
        .asg            B7,         B_S1Q1  ; Nodes S1, Q1 (packed)
        .asg            B28,        B_s0q0  ; Nodes s0, q0 (packed)
        .asg            B20,        B_h2g2  ; Nodes h2, g2 (packed)
        .asg            B19,        B_g3    ; Node g3 in signal flow graph
        .asg            B24,        B_h3    ; Node h3 in signal flow graph
        .asg            B24,        B_h2h3  ; Nodes h2, h3 (packed)
        .asg            B20,        B_g2g3  ; Nodes g2, g3 (packed)
        .asg            B26,        B_f01   ; Sample domain f0, f1 (packed)
        .asg            B17,        B_f32   ; Sample domain f3, f2 (packed)
        .asg            B1,         B_f45   ; Sample domain f4, f5 (packed)
        .asg            B27,        B_f76   ; Sample domain f7, f6 (packed)

        ; Symbolic names for IDCTs in odd-numbered columns.
        .asg            B29,        B_F04x  ; Freq terms F0, F4 (packed)
        .asg            B31,        B_F17x  ; Freq terms F1, F7 (packed)
        .asg            B6,         B_F26x  ; Freq terms F2, F6 (packed)
        .asg            B1,         B_F53x  ; Freq terms F5, F3 (packed)
        .asg            A24,        A_F17   ; Freq terms F1, F7 (packed)
        .asg            A1,         A_F26   ; Freq terms F2, F6 (packed)
        .asg            A8,         A_F40   ; Freq terms F4, F0 (packed)
        .asg            A9,         A_F53   ; Freq terms F5, F3 (packed)
        .asg            A31,        A_F0n4  ; F04, with term F4 'negated'
        .asg            A0,         A_p0p1  ; Nodes p0, p1 (packed)
        .asg            A3,         A_r0    ; Node r0 in signal flow graph
        .asg            A28,        A_r1    ; Node r1 in signal flow graph
        .asg            A7,         A_r0r1  ; Nodes r0, r1 (packed)
        .asg            A0,         A_g0g1  ; Nodes g0, g1 (packed)
        .asg            A5,         A_h0h1  ; Nodes h0, h1 (packed)
        .asg            A7,         A_Q1    ; Node Q1 in signal flow graph
        .asg            A23,        A_Q0    ; Node Q0 in signal flow graph
        .asg            A31,        A_S0    ; Node S0 in signal flow graph
        .asg            A28,        A_S1    ; Node S1 in signal flow graph
        .asg            A23,        A_S0Q0  ; Nodes S0, Q1 (packed)
        .asg            A6,         A_S1Q1  ; Nodes S0, Q1 (packed)
        .asg            A7,         A_s0q0  ; Nodes s0, q1 (packed)
        .asg            A6,         A_h2g2  ; Nodes h0, g1 (packed)
        .asg            A8,         A_g3    ; Node g3 in signal flow graph
        .asg            A3,         A_h3    ; Node h3 in signal flow graph
        .asg            A6,         A_h2h3  ; Nodes h2, h3 (packed)
        .asg            A9,         A_g2g3  ; Nodes g2, g3 (packed)
        .asg            A8,         A_f01   ; Sample domain f0, f1 (packed)
        .asg            A29,        A_f32   ; Sample domain f3, f2 (packed)
        .asg            A26,        A_f45   ; Sample domain f4, f5 (packed)
        .asg            A5,         A_f76   ; Sample domain f7, f6 (packed)

        ; Final output/recombination step
        .asg            A25,        A_f00   ; Sample domain term f0 (two cols)
        .asg            A9,         A_f11   ; Sample domain term f1 (two cols)
        .asg            A9,         A_f22   ; Sample domain term f2 (two cols)
        .asg            A29,        A_f33   ; Sample domain term f3 (two cols)
        .asg            A7,         A_f44   ; Sample domain term f4 (two cols)
        .asg            A24,        A_f55   ; Sample domain term f5 (two cols)
        .asg            A23,        A_f66   ; Sample domain term f6 (two cols)
        .asg            A5,         A_f77   ; Sample domain term f7 (two cols)
; ============================================================================

* ========================================================================= *
*  Vertical loop setup                                                      *
*                                                                           *
*  Here, the first stage of the prolog is interscheduled with the setup     *
*  code which sets up the cosine terms for the function.  Additionally, we  *
*  perform the "abort" test here, since it doesn't cost us anything,        *
*  except possibly codesize.                                                *
*                                                                           *
*  To save some superfluous MVs, A_o_ptr and B_i have been allocated to     *
*  A4 and B4 respectively.  Also, since A_o_ptr and B_i_ptr start out       *
*  pointing to the same location, the LDWs in the prolog have been          *
*  rewritten to use A_o_ptr, so that we can start loading DCT inputs        *
*  right in the first cycle of the function.                                *
*                                                                           *
*  In the vertical loop, the input and output pointers need to alternate    *
*  through four separate column positions, and then jump between DCT        *
*  blocks.  This is achieved by adding a repeating sequence of pointer      *
*  fixup values to the pointers.  The sequence rotates through the values   *
*  1, 1, 1 and 29, thus providing the following pointer motion:             *
*  cols 0/1 -> 2/3, cols 2/3 -> 4/5, cols 4/5 -> 6/7, and then              *
*  cols 6/7 -> 0/1 (next block).  Since each fixup value is small enough    *
*  to fit in a byte, the four fixup values are stored in a 32-bit constant  *
*  which is rotated 8 bits each iteration.  The upper 8 bits are extracted  *
*  to provide the fixup value.                                              *
*                                                                           *
*  Finally, the starting pointer value and loop trip count calculated       *
*  here are saved in registers for the horizontal loop that follows this.   *
* ========================================================================= *

; ============================ PIPE LOOP PROLOG ==============================
; PROLOG:
;-
        LDW     .D1T2   *+A_o_ptr[12],          B_F33        ;[ 1,1] read F3
||      MVKL    .S1     cst_c0,     A_C00                    ; Constant c0 (lo)
||      MVKL    .S2     cst_c5,     B_C35                    ; Constant c5 (lo)
||      MV      .L2     B_i,        B_c                      ; Early abort flag

  [ B_c]LDW     .D1T2   *+A_o_ptr[20],          B_F55        ;[ 2,1] read F5
||[ B_c]MVKL    .S1     cst_c1,     A_C71                    ; Constant c1 (lo)
||[!B_c]RET     .S2     B_ret       ; abort if num_idcts == 0
;-
  [ B_c]LDW     .D1T2   *+A_o_ptr[28],          B_F77        ;[ 3,1] read F7
||[ B_c]SHL     .S2     B_i,        2,          B_i          ; 4*num_idct iters
||[ B_c]MVKL    .S1     cst_c2,     A_C62                    ; Constant c2 (lo)
||[ B_c]MVK     .D2     1,          B_fx1                    ; Init ptr fixup

  [ B_c]LDW     .D1T2   *+A_o_ptr[4],           B_F11        ;[ 4,1] read F1
||[ B_c]MVKLH   .S2     cst_c3,     B_C35                    ; Constant c3 (hi)
||[ B_c]MVKLH   .S1     cst_c6,     A_C62                    ; Constant c6 (hi)
||[ B_c]PACK2   .L1     A_C00,      A_C00,      A_C00        ; Constant c0 (hi)
;-
  [ B_c]LDW     .D1T2   *+A_o_ptr[8],           B_F22        ;[ 5,1] read F2
||[ B_c]XPND2   .M1     A_C62,      A_k_neg                  ; Constant 0xFFFF

  [ B_c]LDW     .D1T2   *+A_o_ptr[16],          B_F44        ;[ 6,1] read F4
||[ B_c]MVKLH   .S1     cst_c7,     A_C71                    ; Constant c7 (hi)
||[ B_c]MVKL    .S2     cst_fix,    B_k_fix                  ; Ptr fixup const
||[ B_c]ROTL    .M1     A_C62,      16,         A_C26        ; Swap c6, c2
||[ B_c]MV      .D2X    A_o_ptr,    B_i_ptr                  ; Init B_i_ptr
||[ B_c]MV      .L1X    B_C35,      A_C35                    ; Partitioning MV.
;-
  [ B_c]LDW     .D1T2   *+A_o_ptr[24],          B_F66        ;[ 7,1] read F6
||[ B_c]PACKH2  .L2     B_F55,      B_F33,      B_F53x       ;[ 7,1] 
||[ B_c]PACKLH2 .L1     A_C71,      A_C71,      A_C17        ; Swap c1, c7
||[ B_c]MV      .S1X    B_i,        A_cnt                    ; h_loop counter
||[ B_c]MPY     .M2     B_fx1,      3,          B_c          ; Prolog collapse
||[ B_c]ROTL    .M1     A_C35,      16,         A_C53        ; Swap c6, c2
||[ B_c]MVKH    .S2     cst_fix,    B_k_fix                  ; Ptr fixup (hi)
;-
; Collapsed 3 stages of prolog
; ============================ PIPE LOOP KERNEL ==============================
v_loop:
        ADD2    .D1     A_h0h1,     A_g2g3,     A_f32        ;[30,2] 
||      PACKHL2 .L1     A_h2g2,     A_h3,       A_h2h3       ;[30,2] 
||      ADD2    .L2     B_g0g1,     B_h2h3,     B_f01        ;[30,2] 
||      ROTL    .M1X    B_F04x,     16,         A_F40        ;[19,3] 
||      XOR     .S1X    B_F04x,     A_k_neg,    A_F0n4       ;[19,3] negate F4
||      PACK2   .S2     B_r0,       B_r1,       B_r0r1       ;[19,3] 
||      DOTPNRSU2.M2X   B_s0q0,     A_C00,      B_g3         ;[19,3] 
||      LDW     .D2T2   *B_i_ptr++[B_fx1],      B_F00        ;[ 8,4] read F0
;-
        SUB2    .D1     A_g0g1,     A_h2h3,     A_f76        ;[31,2] 
||      SUB2    .S1     A_h0h1,     A_g2g3,     A_f45        ;[31,2] 
||      SUB2    .D2     B_g0g1,     B_h2h3,     B_f76        ;[31,2] 
||      DOTPRSU2.M1     A_F26,      A_C26,      A_r0         ;[20,3] 
||      DOTPRSU2.M2X    B_s0q0,     A_C00,      B_h3         ;[20,3] 
||      MV      .L1X    B_F53x,     A_F53                    ;[ 9,4] part. MV
||      PACK2   .L2     B_F55,      B_F33,      B_F53        ;[ 9,4] 
||      PACKH2  .S2     B_F11,      B_F77,      B_F17x       ;[ 9,4] 
;-
  [!B_c]STW     .D1T1   A_f55,      *+A_o_ptr[20]            ;[43,1] write f0
||      SHR     .S1X    B_k_fix,    24,         A_fx2        ;[43,1] ptr fixup
||      ADD2    .L1     A_g0g1,     A_h2h3,     A_f01        ;[32,2] 
||      SUB2    .S2     B_h0h1,     B_g2g3,     B_f45        ;[32,2] 
||      AVG2    .M1     A_F40,      A_F0n4,     A_p0p1       ;[21,3] 
||      ADD2    .D2     B_p0p1,     B_r0r1,     B_g0g1       ;[21,3] 
||      PACK2   .L2     B_F11,      B_F77,      B_F17        ;[10,4] 
||      DOTPNRSU2.M2X   B_F53,      A_C35,      B_Q0         ;[10,4] 
;-
  [!B_c]STW     .D1T1   A_f00,      *A_o_ptr++[A_fx2]        ;[44,1] write f0
||      ADD2    .S2     B_h0h1,     B_g2g3,     B_f32        ;[33,2] 
||      PACK2   .S1     A_S1,       A_Q1,       A_S1Q1       ;[22,3] 
||      DOTPNRSU2.M1    A_F26,      A_C62,      A_r1         ;[22,3] 
||      ADD2    .L2     B_S1Q1,     B_S0Q0,     B_h2g2       ;[22,3] 
||      SUB2    .D2     B_p0p1,     B_r0r1,     B_h0h1       ;[22,3] 
||      MV      .L1X    B_F17x,     A_F17                    ;[11,4] part. MV
||      DOTPRSU2.M2X    B_F53,      A_C53,      B_S0         ;[11,4] 
;-
  [ B_c]SUB     .S2     B_c,        1,          B_c          ; prolog collapse
||      PACK2   .L1X    A_f76,      B_f76,      A_f66        ;[34,2] 
||      SUB2    .D1     A_S1Q1,     A_S0Q0,     A_s0q0       ;[23,3] 
||      ADD2    .S1     A_S1Q1,     A_S0Q0,     A_h2g2       ;[23,3] 
||      DOTPRSU2.M1     A_F53,      A_C53,      A_S0         ;[12,4] 
||      PACKH2  .L2     B_F22,      B_F66,      B_F26x       ;[12,4] 
||      DOTPRSU2.M2X    B_F17,      A_C17,      B_S1         ;[12,4] 
||      LDW     .D2T2   *+B_i_ptr[12],          B_F33        ;[ 1,5] read F3
;-
        BDEC    .S2     v_loop,     B_i                      ;[47,1] iterate
||[!B_c]STW     .D1T1   A_f66,      *+A_o_ptr[24]            ;[35,2] write f6
||      PACKH2  .S1X    A_f32,      B_f32,      A_f33        ;[35,2] 
||      PACK2   .L1X    A_f32,      B_f32,      A_f22        ;[35,2] 
||      DOTPNRSU2.M1    A_F53,      A_C35,      A_Q0         ;[13,4] 
||      PACK2   .L2     B_F22,      B_F66,      B_F26        ;[13,4] 
||      DOTPNRSU2.M2X   B_F17,      A_C71,      B_Q1         ;[13,4] 
||      LDW     .D2T2   *+B_i_ptr[20],          B_F55        ;[ 2,5] read F5
;-
  [!B_c]STW     .D1T1   A_f22,      *+A_o_ptr[8]             ;[36,2] write f2
||      PACKH2  .L1X    A_f01,      B_f01,      A_f00        ;[36,2] 
||      PACK2   .S1X    A_f01,      B_f01,      A_f11        ;[36,2] 
||      PACKHL2 .L2     B_h2g2,     B_h3,       B_h2h3       ;[25,3] 
||      DOTPNRSU2.M1    A_s0q0,     A_C00,      A_g3         ;[25,3] 
||      DOTPRSU2.M2X    B_F26,      A_C26,      B_r0         ;[14,4] 
||      SHR     .S2     B_k_fix,    24,         B_fx1        ;[ 3,5] ptr fixup
||      LDW     .D2T2   *+B_i_ptr[28],          B_F77        ;[ 3,5] 
;-
  [!B_c]STW     .D1T1   A_f11,      *+A_o_ptr[4]             ;[37,2] write f1
||      PACKH2  .S1X    A_f76,      B_f76,      A_f77        ;[37,2] 
||      PACK2   .L1     A_r0,       A_r1,       A_r0r1       ;[26,3] 
||      DOTPRSU2.M1     A_s0q0,     A_C00,      A_h3         ;[26,3] 
||      PACK2   .L2     B_h2g2,     B_g3,       B_g2g3       ;[26,3] 
||      DOTPNRSU2.M2X   B_F26,      A_C62,      B_r1         ;[15,4] 
||      PACK2   .S2     B_F00,      B_F44,      B_F04        ;[15,4] 
||      LDW     .D2T2   *+B_i_ptr[4],           B_F11        ;[ 4,5] read F1
;-
  [!B_c]STW     .D1T1   A_f77,      *+A_o_ptr[28]            ;[38,2] write f7
||      ADD2    .S1     A_p0p1,     A_r0r1,     A_g0g1       ;[27,3] 
||      SUB2    .L1     A_p0p1,     A_r0r1,     A_h0h1       ;[27,3] 
||      ROTL    .M1X    B_F26x,     0,          A_F26        ;[16,4] 
||      XOR     .S2X    B_F04,      A_k_neg,    B_F0n4       ;[16,4] negate F4
||      PACK2   .L2     B_S0,       B_Q0,       B_S0Q0       ;[16,4] 
||      ROTL    .M2     B_F04,      16,         B_F40        ;[16,4] 
||      LDW     .D2T2   *+B_i_ptr[8],           B_F22        ;[ 5,5] read F2
;-
  [!B_c]STW     .D1T1   A_f33,      *+A_o_ptr[12]            ;[39,2] write f3
||      PACKH2  .S1X    A_f45,      B_f45,      A_f44        ;[39,2] 
||      PACKH2  .L2     B_F00,      B_F44,      B_F04x       ;[17,4] 
||      PACK2   .L1     A_S0,       A_Q0,       A_S0Q0       ;[17,4] 
||      DOTPRSU2.M1     A_F17,      A_C17,      A_S1         ;[17,4] 
||      PACK2   .S2     B_S1,       B_Q1,       B_S1Q1       ;[17,4] 
||      LDW     .D2T2   *+B_i_ptr[16],          B_F44        ;[ 6,5] read F4
||      ROTL    .M2     B_k_fix,    8,          B_k_fix      ;[ 6,5] ptr fixup
;-
  [!B_c]STW     .D1T1   A_f44,      *+A_o_ptr[16]            ;[40,2] write f4
||      PACK2   .S1X    A_f45,      B_f45,      A_f55        ;[40,2] 
||      PACK2   .L1     A_h2g2,     A_g3,       A_g2g3       ;[29,3] 
||      DOTPNRSU2.M1    A_F17,      A_C71,      A_Q1         ;[18,4] 
||      SUB2    .S2     B_S1Q1,     B_S0Q0,     B_s0q0       ;[18,4] 
||      AVG2    .M2     B_F40,      B_F0n4,     B_p0p1       ;[18,4] 
||      PACKH2  .L2     B_F55,      B_F33,      B_F53x       ;[ 7,5] 
||      LDW     .D2T2   *+B_i_ptr[24],          B_F66        ;[ 7,5] read F6
;-
; ============================ PIPE LOOP EPILOG ==============================
; EPILOG:
; Collapsed 3 stages of epilog

; ================== SYMBOLIC REGISTER ASSIGNMENTS: H_LOOP ===================
        ; Constants held in registers
        .asg            B24,        B_k_neg ; Negation cst: 0x0000FFFF
        .asg            B25,        B_rnd   ; Rounding cst: 0x000F0010

        ; Pointers and loop control
        .asg            B23,        B_i_ptr ; Input (and output) pointer
        .asg            A2,         A_i_ptr ; Input (and output) pointer
        .asg            B22,        B_i     ; Loop counter
        .asg            A0,         A_c     ; Prolog collapse predicate

        ; Symbolic names for IDCTs in even-numbered rows
        .asg            B29,        B_F76   ; Freq domain terms F7, F6 (packed)
        .asg            B28,        B_F54   ; Freq domain terms F5, F4 (packed)
        .asg            B27,        B_F32   ; Freq domain terms F3, F2 (packed)
        .asg            B26,        B_F10   ; Freq domain terms F1, F0 (packed)
        .asg            B8,         B_F17   ; Freq domain terms F1, F7 (packed)
        .asg            B7,         B_F53   ; Freq domain terms F5, F3 (packed)
        .asg            B20,        B_F26   ; Freq domain terms F2, F6 (packed)
        .asg            B21,        B_F40   ; Freq domain terms F4, F0 (packed)
        .asg            B8,         B_F04   ; Freq domain terms F0, F4 (packed)
        .asg            B20,        B_F0n4  ; F04, with F4 'negated'
        .asg            B17,        B_p0p1_t; Nodes p0, p1, temp. (packed)
        .asg            B17,        B_p0p1  ; Nodes p0, p1
        .asg            B4,         B_r0    ; Node r0 in signal flow graph
        .asg            B6,         B_r1    ; Node r1 in signal flow graph
        .asg            B16,        B_r0r1  ; Nodes r0, r1 (packed)
        .asg            B6,         B_g0g1  ; Nodes g0, g1 (packed)
        .asg            B16,        B_h0h1  ; Nodes h0, h1 (packed)
        .asg            B18,        B_Q1    ; Node Q1 in signal flow graph
        .asg            B17,        B_Q0    ; Node Q0 in signal flow graph
        .asg            B7,         B_S0    ; Node S0 in signal flow graph
        .asg            B0,         B_S1    ; Node S1 in signal flow graph
        .asg            B9,         B_S0Q0  ; Nodes S0, Q0 (packed)
        .asg            B18,        B_S1Q1  ; Nodes S1, Q1 (packed)
        .asg            B6,         B_s0q0  ; Nodes s0, q0 (packed)
        .asg            B19,        B_h2g2  ; Nodes h2, g2 (packed)
        .asg            B4,         B_g3    ; Node g3 in signal flow graph
        .asg            B5,         B_h3    ; Node h3 in signal flow graph
        .asg            B5,         B_h2h3  ; Nodes h2, h3 (packed)
        .asg            B9,         B_g2g3  ; Nodes g2, g3 (packed)
        .asg            B19,        B_f01   ; Sample domain f0, f1 (packed)
        .asg            B8,         B_f32   ; Sample domain f3, f2 (packed)
        .asg            B20,        B_f45   ; Sample domain f4, f5 (packed)
        .asg            B5,         B_f76   ; Sample domain f7, f6 (packed)
        .asg            B16,        B_f10r  ; f1, f0 rounded
        .asg            B17,        B_f32r  ; f3, f2 rounded 
        .asg            B7,         B_f54r  ; f5, f4 rounded 
        .asg            B5,         B_f76r  ; f7, f6 rounded 
        .asg            B4,         B_f10s  ; f1, f0 saturated
        .asg            B31,        B_f32s  ; f3, f2 saturated
        .asg            B8,         B_f54s  ; f3, f2 saturated
        .asg            B9,         B_f76s  ; f3, f2 saturated
        .asg            B30,        B_f10t  ; f1, f0 truncated
        .asg            B31,        B_f32t  ; f3, f2 truncated
        .asg            B30,        B_f54t  ; f5, f4 truncated
        .asg            B31,        B_f76t  ; f7, f6 truncated

        ; Symbolic names for IDCTs in odd-numbered rows
        .asg            A27,        A_F76   ; Freq domain terms F7, F6 (packed)
        .asg            A26,        A_F54   ; Freq domain terms F5, F4 (packed)
        .asg            A29,        A_F32   ; Freq domain terms F3, F2 (packed)
        .asg            A28,        A_F10   ; Freq domain terms F1, F0 (packed)
        .asg            A8,         A_F17   ; Freq domain terms F1, F7 (packed)
        .asg            A3,         A_F53   ; Freq domain terms F5, F3 (packed)
        .asg            A8,         A_F26   ; Freq domain terms F2, F6 (packed)
        .asg            A24,        A_F40   ; Freq domain terms F4, F0 (packed)
        .asg            A9,         A_F04   ; Freq domain terms F0, F4 (packed)
        .asg            A6,         A_F0n4  ; F04, with F4 'negated'
        .asg            A6,         A_p0p1_t; Nodes p0, p1, temp. (packed)
        .asg            A6,         A_p0p1  ; Nodes p0, p1 (packed)
        .asg            A30,        A_r0    ; Node r0 in signal flow graph
        .asg            A7,         A_r1    ; Node r1 in signal flow graph
        .asg            A30,        A_r0r1  ; Nodes r0, r1 (packed)
        .asg            A9,         A_g0g1  ; Nodes g0, g1 (packed)
        .asg            A7,         A_h0h1  ; Nodes h0, h1 (packed)
        .asg            A6,         A_Q1    ; Node Q1 in signal flow graph
        .asg            A25,        A_Q0    ; Node Q0 in signal flow graph
        .asg            A23,        A_S0    ; Node S0 in signal flow graph
        .asg            A4,         A_S1    ; Node S1 in signal flow graph
        .asg            A3,         A_S0Q0  ; Nodes S0, Q0 (packed)
        .asg            A4,         A_S1Q1  ; Nodes S1, Q1 (packed)
        .asg            A1,         A_s0q0  ; Nodes s0, q0 (packed)
        .asg            A5,         A_h2g2  ; Nodes h2, g2 (packed)
        .asg            A23,        A_g3    ; Node g3 in signal flow graph
        .asg            A1,         A_h3    ; Node h3 in signal flow graph
        .asg            A7,         A_h2h3  ; Nodes h2, h3 (packed)
        .asg            A30,        A_g2g3  ; Nodes g2, g3 (packed)
        .asg            A8,         A_f01   ; Sample domain f0, f1 (packed)
        .asg            A7,         A_f32   ; Sample domain f3, f2 (packed)
        .asg            A3,         A_f45   ; Sample domain f4, f5 (packed)
        .asg            A9,         A_f76   ; Sample domain f7, f6 (packed)
        .asg            A8,         A_f10r  ; f1, f0 rounded
        .asg            A5,         A_f32r  ; f3, f2 rounded
        .asg            A5,         A_f54r  ; f5, f4 rounded
        .asg            A5,         A_f76r  ; f7, f6 rounded
        .asg            A9,         A_f10s  ; f1, f0 saturated
        .asg            A5,         A_f32s  ; f3, f2 saturated
        .asg            A4,         A_f54s  ; f5, f4 saturated
        .asg            A6,         A_f76s  ; f7, f6 saturated
        .asg            A30,        A_f10t  ; f1, f0 truncated
        .asg            A31,        A_f32t  ; f3, f2 truncated
        .asg            A24,        A_f54t  ; f5, f4 truncated
        .asg            A25,        A_f76t  ; f7, f6 truncated
; ============================================================================

* ========================================================================= *
*  Horizontal loop setup                                                    *
*                                                                           *
*  The horizontal loop needs very little setup in order to get rolling,     *
*  since it shares most of its incoming registers with the vertical loop.   *
*  For instance, all of the cosine terms are allocated to the same regs     *
*  in both loops.                                                           *
*                                                                           *
*  The horizontal loop processes DCT blocks in reverse order, starting      *
*  at the end of the list of DCTs, working towards the beginning.  As a     *
*  result, the input pointers for the horizontal loop are initialized from  *
*  the vertical pointer values left over from the vertical loop by adding   *
*  a fixed offset to each of the pointers.  This works regardless of the    *
*  number of DCT blocks.  This also allows us to perform the next small     *
*  optimization safely.                                                     *
*                                                                           *
*  For speed, the remaining two STWs from the vertical loop fill in the     *
*  delay after the initial LDDWs for the horizonal loop.  Also, some        *
*  rescheduling of the prolog has been performed to further speed things    *
*  up.                                                                      *
*                                                                           *
*  To save registers, the same pointer register is used for loading and     *
*  storing in each datapath.  This is possible since the LDDWs and STDWs    *
*  are close enough in the pipeline, and all pointers are traversing        *
*  linearly through memory.                                                 *
* ========================================================================= *

; ============================ PIPE LOOP PROLOG ==============================
; PROLOG:
        LDDW    .D2T1   *-B_i_ptr  [4],         A_F76:A_F54  ;[ 2,1] get F7..F4
||      ADDAW   .D1     A_o_ptr,    21,         A_i_ptr      ; point @ row 6

        LDDW    .D2T2   *-B_i_ptr  [2],         B_F76:B_F54  ;[ 3,1] get F7..F4
||      LDDW    .D1T1   * A_i_ptr--[4],         A_F32:A_F10  ;[ 3,1] get F3..F0

        MVKL    .S2     cst_rnd,    B_rnd                    ; rounding const.
||      LDDW    .D2T2   *-B_i_ptr  [3],         B_F32:B_F10  ;[ 4,1] get F3..F0

        MVKH    .S2     cst_rnd,    B_rnd                    ; round cst (hi)
||      XPND2   .M2X    A_C62,      B_k_neg                  ;[ 5,1]
;-
        STW     .D1T1   A_f55,      *+A_o_ptr[20]            ;v_loop: write f5
||      SUBAW   .D2     B_i_ptr,    14,         B_i_ptr      ; point @ row 7

        STW     .D1T1   A_f00,      * A_o_ptr                ;v_loop: write f0

        PACKH2  .L1     A_F54,      A_F32,      A_F53        ;[ 8,1] 
||      PACKH2  .S1     A_F10,      A_F76,      A_F17        ;[ 8,1] 

        PACKH2  .S2     B_F10,      B_F76,      B_F17        ;[ 9,1] 
||      DOTPRSU2.M1     A_F17,      A_C17,      A_S1         ;[ 9,1] 
||      SUB     .L2X    A_cnt,      1,          B_i          ; init loop cnt
;-
        DOTPNRSU2.M2X   B_F17,      A_C71,      B_Q1         ;[10,1] 
||      DOTPNRSU2.M1    A_F17,      A_C71,      A_Q1         ;[10,1] 
||      PACK2   .L2     B_F32,      B_F76,      B_F26        ;[10,1] 
||      PACK2   .L1     A_F32,      A_F76,      A_F26        ;[10,1] 
||      PACK2   .S1     A_F54,      A_F10,      A_F40        ;[10,1] 
||      MVK     .D1     2,          A_c                      ; prolog collapse
;-
; Collapsed 2 stages of prolog
; ============================ PIPE LOOP KERNEL ==============================
h_loop:
        SADD2   .S2     B_f54r,     B_f54r,     B_f54s       ;[36,1] sat f5, f4
||[!A_c]STDW    .D1T1   A_f32t:A_f10t,          *+A_i_ptr[12];[36,1] put f3..f0
||      ADD2    .D2     B_p0p1_t,   B_rnd,      B_p0p1       ;[24,2] round DC
||      PACK2   .S1     A_h2g2,     A_g3,       A_g2g3       ;[24,2] 
||      PACK2   .L2     B_F54,      B_F10,      B_F40        ;[12,3] 
||      DOTPRSU2.M2X    B_F17,      A_C17,      B_S1         ;[12,3] 
||      DOTPNRSU2.M1    A_F53,      A_C35,      A_Q0         ;[12,3] 
;-
        SHR2    .S2     B_f10s,     7,          B_f10t       ;[37,1] trnc f1,f0
||      DOTPNRSU2.M2X   B_s0q0,     A_C00,      B_g3         ;[25,2] 
||      ADD2    .L1     A_h0h1,     A_g2g3,     A_f32        ;[25,2] 
||      SUB2    .S1     A_h0h1,     A_g2g3,     A_f45        ;[25,2] 
||      PACKH2  .L2     B_F54,      B_F32,      B_F53        ;[13,3] 
||      DOTPRSU2.M1     A_F53,      A_C53,      A_S0         ;[13,3] 
||      LDDW    .D1T1   *+A_i_ptr  [1],         A_F76:A_F54  ;[ 1,4] get F7..F4
||      LDDW    .D2T2   * B_i_ptr--[4],         B_F32:B_F10  ;[ 1,4] get F3..F0
;-
        SADD2   .S2     B_f76r,     B_f76r,     B_f76s       ;[38,1] sat f7, f6
||      ADD2    .L2     B_p0p1,     B_r0r1,     B_g0g1       ;[26,2] 
||      DOTPRSU2.M2X    B_s0q0,     A_C00,      B_h3         ;[26,2] 
||      ADD     .S1     A_f32,      A_f32,      A_f32r       ;[26,2] qpt f3..f2
||      PACKHL2 .L1     A_h2g2,     A_h3,       A_h2h3       ;[26,2] 
||      DOTPRSU2.M1     A_F26,      A_C26,      A_r0         ;[14,3] 
||      LDDW    .D2T2   *+B_i_ptr  [5],         B_F76:B_F54  ;[ 2,4] get F7..F4
||      LDDW    .D1T1   * A_i_ptr--[4],         A_F32:A_F10  ;[ 2,4] get F3..F0
;-
        SHR2    .S2     B_f32s,     7,          B_f32t       ;[39,1] trnc f3,f2
||      SUB2    .L2     B_p0p1,     B_r0r1,     B_h0h1       ;[27,2] 
||      SUB2    .L1     A_g0g1,     A_h2h3,     A_f76        ;[27,2] 
||      ADD2    .D1     A_g0g1,     A_h2h3,     A_f01        ;[27,2] 
||      SADD2   .S1     A_f32r,     A_f32r,     A_f32s       ;[27,2] sat  f3,f2
||      DOTPNRSU2.M1    A_F26,      A_C62,      A_r1         ;[15,3] 
||      DOTPNRSU2.M2X   B_F53,      A_C35,      B_Q0         ;[15,3] 
;-
        SHR2    .S2     B_f54s,     7,          B_f54t       ;[40,1] trnc f5,f4
||[!A_c]STDW    .D2T2   B_f32t:B_f10t,          *+B_i_ptr[16];[40,1] put f3..f0
||      SHR2    .S1     A_f32s,     7,          A_f32t       ;[28,2] trnc f3,f2
||      ADD     .D1     A_f76,      A_f76,      A_f76r       ;[28,2] qpt f7..f6
||      PACK2   .L2     B_S1,       B_Q1,       B_S1Q1       ;[16,3] 
||      DOTPRSU2.M2X    B_F53,      A_C53,      B_S0         ;[16,3] 
||      ROTL    .M1     A_F40,      16,         A_F04        ;[16,3] 
||      PACK2   .L1     A_S1,       A_Q1,       A_S1Q1       ;[16,3] 
;-
        SHR2    .S2     B_f76s,     7,          B_f76t       ;[41,1] trnc f7,f6
||      PACK2   .L2     B_h2g2,     B_g3,       B_g2g3       ;[29,2] 
||      SADD2   .S1     A_f76r,     A_f76r,     A_f76s       ;[29,2] sat  f7,f6
||      ROTL    .M1     A_f45,      17,         A_f54r       ;[29,2] q-pt f5,f4
||      PACK2   .L1     A_S0,       A_Q0,       A_S0Q0       ;[17,3] 
||      ROTL    .M2     B_F40,      16,         B_F04        ;[17,3] 
;-
        BDEC    .S2     h_loop,     B_i                      ;[42,1] 
||[!A_c]STDW    .D2T2   B_f76t:B_f54t,          *+B_i_ptr[17];[42,1] put f7..f4
||      PACKHL2 .L2     B_h2g2,     B_h3,       B_h2h3       ;[30,2] 
||      SHR2    .S1     A_f76s,     7,          A_f76t       ;[30,2] trnc f7,f6
||      ROTL    .M1     A_f01,      17,         A_f10r       ;[30,2] q-pt f1,f0
||      SUB2    .L1     A_S1Q1,     A_S0Q0,     A_s0q0       ;[18,3] 
||      XOR     .D1X    A_F04,      B_k_neg,    A_F0n4       ;[18,3] negate F4
||      DOTPRSU2.M2X    B_F26,      A_C26,      B_r0         ;[18,3] 
;-
        ADD2    .S2     B_g0g1,     B_h2h3,     B_f01        ;[31,2] 
||      SUB2    .D2     B_h0h1,     B_g2g3,     B_f45        ;[31,2] 
||      SUB2    .L2     B_g0g1,     B_h2h3,     B_f76        ;[31,2] 
||      SADD2   .S1     A_f54r,     A_f54r,     A_f54s       ;[31,2] sat  f5,f4
||      DOTPNRSU2.M2X   B_F26,      A_C62,      B_r1         ;[19,3] 
||      ADD2    .D1     A_S1Q1,     A_S0Q0,     A_h2g2       ;[19,3] 
||      AVG2    .M1     A_F40,      A_F0n4,     A_p0p1_t     ;[19,3] 
||      PACKH2  .L1     A_F54,      A_F32,      A_F53        ;[ 7,4] 
;-
        ADD2    .D2     B_h0h1,     B_g2g3,     B_f32        ;[32,2] 
||      ROTL    .M2     B_f45,      17,         B_f54r       ;[32,2] q-pt f5,f4
||[ A_c]SUB     .D1     A_c,        1,          A_c          ;[32,2] 
||      SADD2   .S1     A_f10r,     A_f10r,     A_f10s       ;[32,2] sat  f1,f0
||      XOR     .S2     B_F04,      B_k_neg,    B_F0n4       ;[20,3] negate F4
||      PACK2   .L2     B_S0,       B_Q0,       B_S0Q0       ;[20,3] 
||      DOTPNRSU2.M1    A_s0q0,     A_C00,      A_g3         ;[20,3] 
||      PACKH2  .L1     A_F10,      A_F76,      A_F17        ;[ 8,4] 
;-
        ROTL    .M2     B_f01,      17,         B_f10r       ;[33,2] q-pt f1,f0
||      ADD     .D2     B_f32,      B_f32,      B_f32r       ;[33,2] 
||      ADD     .L2     B_f76,      B_f76,      B_f76r       ;[33,2] 
||      SHR2    .S1     A_f54s,     7,          A_f54t       ;[33,2] trnc f5,f4
||      PACK2   .L1     A_r0,       A_r1,       A_r0r1       ;[21,3] 
||      ADD2    .D1X    A_p0p1_t,   B_rnd,      A_p0p1       ;[21,3] round DC
||      PACKH2  .S2     B_F10,      B_F76,      B_F17        ;[ 9,4] 
||      DOTPRSU2.M1     A_F17,      A_C17,      A_S1         ;[ 9,4] 
;-
        SADD2   .S2     B_f32r,     B_f32r,     B_f32s       ;[34,2] sat  f3,f2
||[!A_c]STDW    .D1T1   A_f76t:A_f54t,          *+A_i_ptr[13];[34,2] put f7..f4
||      ADD2    .D2     B_S1Q1,     B_S0Q0,     B_h2g2       ;[22,3] 
||      AVG2    .M2     B_F40,      B_F0n4,     B_p0p1_t     ;[22,3] 
||      DOTPRSU2.M1     A_s0q0,     A_C00,      A_h3         ;[22,3] 
||      SUB2    .L1     A_p0p1,     A_r0r1,     A_h0h1       ;[22,3] 
||      PACK2   .L2     B_F32,      B_F76,      B_F26        ;[10,4] 
||      PACK2   .S1     A_F54,      A_F10,      A_F40        ;[10,4] 
;-
        SADD2   .S2     B_f10r,     B_f10r,     B_f10s       ;[35,2] sat  f1,f0
||      SHR2    .S1     A_f10s,     7,          A_f10t       ;[35,2] trnc f1,f0
||      SUB2    .D2     B_S1Q1,     B_S0Q0,     B_s0q0       ;[23,3] 
||      PACK2   .L2     B_r0,       B_r1,       B_r0r1       ;[23,3] 
||      ADD2    .D1     A_p0p1,     A_r0r1,     A_g0g1       ;[23,3] 
||      DOTPNRSU2.M2X   B_F17,      A_C71,      B_Q1         ;[11,4] 
||      PACK2   .L1     A_F32,      A_F76,      A_F26        ;[11,4] 
||      DOTPNRSU2.M1    A_F17,      A_C71,      A_Q1         ;[11,4] 
;-
; ============================ PIPE LOOP EPILOG ==============================
; EPILOG:
; Collapsed 2 stages of epilog

* ========================================================================= *
*  Exit code                                                                *
*                                                                           *
*  Some slight rescheduling and rewriting squeezed a cycle out of this so   *
*  that I can issue my return branch immediately upon exiting the software  *
*  pipeline above.  The only way to return faster would be to return from   *
*  the loop kernel itself, which would sacrifice interruptibility, due to   *
*  having multiple branches in flight.                                      *
* ========================================================================= *

        STDW    .D1T1   A_f32t:A_f10t,          *+A_i_ptr[12];[36,4] put f3..f0
||      RET     .S2     B_ret                                ;[36,4] return.

        SHR2    .S1X    B_f10s,     7,          A_f10t       ;[37,4] trnc f1,f0
||      SADD2   .S2     B_f54r,     B_f54r,     B_f54s       ;[37,4] sat f5,f4

        SADD2   .S2     B_f76r,     B_f76r,     B_f76s       ;[38,4] sat f7,f6
||      SHR2    .S1X    B_f32s,     7,          A_f32t       ;[39,4] trnc f3,f2

        SHR2    .S2     B_f54s,     7,          B_f54t       ;[39,4] trnc f5,f4
||      STDW    .D2T1   A_f32t:A_f10t,          *+B_i_ptr[12];[40,4] put f3..f0
;-
        SHR2    .S2     B_f76s,     7,          B_f76t       ;[40,4] trnc f7,f6

        STDW    .D2T2   B_f76t:B_f54t,          *+B_i_ptr[13];[41,4] put f7..f4
;-
; ===== Branch Occurs =====
* ========================================================================= *
*   End of file:  idct_8x8_12q4_h.asm                                       *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
