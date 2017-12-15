
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
*       fdct_8x8 -- 8x8 Block FDCT With Rounding, Little Endian             *
*                                                                           *
*   USAGE                                                                   *
*       This routine is C callable, and has the following C prototype:      *
*                                                                           *
*           void fdct_8x8(short fdct_data[], unsigned num_fdcts)            *
*                                                                           *
*       The fdct routine accepts a list of 8x8 pixel blocks and performs    *
*       FDCTs on each.  The array should be laid out identically to         *
*       "fdct_data[num_fdcts][8][8]".  All operations in this array are     *
*       performed entirely in-place.                                        *
*                                                                           *
*       Input values are stored in shorts, and may be in the range          *
*       [-512,511].  Larger input values may result in overflow.            *
*                                                                           *
*       This code requires '50 + 76 * num_fdcts' cycles to process          *
*       'num_fdcts' blocks, including function call overhead.  When         *
*       'num_fdcts' is zero, an early exit is taken and the function        *
*       runs for only 13 cycles (again, including call overhead).           *
*                                                                           *
*   DESCRIPTION                                                             *
*       The fdct_8x8 function implements a Chen FDCT.  Output values are    *
*       rounded, providing improved accuracy.  Input terms are expected     *
*       to be signed 11Q0 values, producing signed 15Q0 results.  (A        *
*       smaller dynamic range may be used on the input, producing a         *
*       correspondingly smaller output range.  Typical applications         *
*       include processing signed 9Q0 and unsigned 8Q0 pixel data,          *
*       producing signed 13Q0 or 12Q0 outputs, respectively.)  No           *
*       saturation is performed.                                            *
*                                                                           *
*       Note:  This code guarantees correct operation, even in the case     *
*       that 'num_fdcts == 0'.  In this case, the function runs for only    *
*       13 cycles (counting 6 cycles of function-call overhead), due to     *
*       early-exit code.  The early-exit case performs one access to the    *
*       fdct_data[] array and no access to the stack.                       *
*                                                                           *
*   C CODE                                                                  *
*                                                                           *
*       void fdct_8x8(short *dct_data, unsigned num_fdcts)                  *
*       {                                                                   *
*           /* ---------------------------------------------------- */      *
*           /*  Set up the cosine coefficients.                     */      *
*           /* ---------------------------------------------------- */      *
*           const unsigned short c1 = 0x1F62;   /* Q13   coeff      */      *
*           const unsigned short c3 = 0x1A9B;   /* Q13   coeff      */      *
*           const unsigned short c5 = 0x11C7;   /* Q13   coeff      */      *
*           const unsigned short c7 = 0x063E;   /* Q13   coeff      */      *
*           const unsigned short c2 = 0x29CF;   /* Q13.5 coeff      */      *
*           const unsigned short c6 = 0x1151;   /* Q13.5 coeff      */      *
*           const unsigned short C1 = 0xFB15;   /* Q16   coeff      */      *
*           const unsigned short C3 = 0xD4DB;   /* Q16   coeff      */      *
*           const unsigned short C5 = 0x8E3A;   /* Q16   coeff      */      *
*           const unsigned short C7 = 0x31F1;   /* Q16   coeff      */      *
*           const unsigned short C2 = 0xA73D;   /* Q15.5 coeff      */      *
*           const unsigned short C6 = 0x4546;   /* Q15.5 coeff      */      *
*           const unsigned short C4 = 0xB505;   /* Q16   coeff      */      *
*                                                                           *
*           /* ---------------------------------------------------- */      *
*           /*  Intermediate calculations.                          */      *
*           /* ---------------------------------------------------- */      *
*           short f0, f1, f2, f3;   /* Spatial domain samples.      */      *
*           short f4, f5, f6, f7;   /* Spatial domain samples.      */      *
*           short g0, g1, h0, h1;   /* Even-half intermediate.      */      *
*           short p0, p1;           /* Even-half intermediate.      */      *
*           short r0, r1, r0_,r1_;  /* Even-half intermediate.      */      *
*           short P0, P1, R0, R1;   /* Even-half intermediate.      */      *
*           short g2, g3, h2, h3;   /* Odd-half intermediate.       */      *
*           short q1a,s1a,q0, q1;   /* Odd-half intermediate.       */      *
*           short s0, s1;           /* Odd-half intermediate.       */      *
*           short Q0, Q1, S0, S1;   /* Odd-half intermediate.       */      *
*           short F0, F1, F2, F3;   /* Freq. domain results.        */      *
*           short F4, F5, F6, F7;   /* Freq. domain results.        */      *
*                                                                           *
*           /* ---------------------------------------------------- */      *
*           /*  Input and output pointers, loop control.            */      *
*           /* ---------------------------------------------------- */      *
*           unsigned i, j;                                                  *
*           short    *dct_io_ptr;                                           *
*                                                                           *
*           /* ---------------------------------------------------- */      *
*           /*  Outer vertical loop -- Process each 8x8 block.      */      *
*           /* ---------------------------------------------------- */      *
*           dct_io_ptr = dct_data;                                          *
*           for (i = 0; i < num_fdcts; i++)                                 *
*           {                                                               *
*               /* ------------------------------------------------ */      *
*               /*  Perform Vertical 1-D FDCT on columns within     */      *
*               /*  each block.  The inputs to this pass are in Q0  */      *
*               /*  and the outputs are in Q1.5.                    */      *
*               /* ------------------------------------------------ */      *
*               for (j = 0; j < 8; j++)                                     *
*               {                                                           *
*                   /* -------------------------------------------- */      *
*                   /*  Load the spatial-domain samples.            */      *
*                   /*  The incoming terms start at Q0 precision.   */      *
*                   /* -------------------------------------------- */      *
*                   f0 = dct_io_ptr[ 0];                                    *
*                   f1 = dct_io_ptr[ 8];                                    *
*                   f2 = dct_io_ptr[16];                                    *
*                   f3 = dct_io_ptr[24];                                    *
*                   f4 = dct_io_ptr[32];                                    *
*                   f5 = dct_io_ptr[40];                                    *
*                   f6 = dct_io_ptr[48];                                    *
*                   f7 = dct_io_ptr[56];                                    *
*                                                                           *
*                   /* -------------------------------------------- */      *
*                   /*  Stage 1:  Separate into even & odd halves.  */      *
*                   /*                                              */      *
*                   /*  The results of this stage are implicitly    */      *
*                   /*  in Q1, since we do not explicitly multiply  */      *
*                   /*  by 0.5.                                     */      *
*                   /* -------------------------------------------- */      *
*                   g0 = f0 + f7;               /*  Results in Q1   */      *
*                   g1 = f1 + f6;               /*  Results in Q1   */      *
*                   h1 = f2 + f5;               /*  Results in Q1   */      *
*                   h0 = f3 + f4;               /*  Results in Q1   */      *
*                   g2 = f3 - f4;               /*  Results in Q1   */      *
*                   g3 = f2 - f5;               /*  Results in Q1   */      *
*                   h3 = f1 - f6;               /*  Results in Q1   */      *
*                   h2 = f0 - f7;               /*  Results in Q1   */      *
*                                                                           *
*                   /* -------------------------------------------- */      *
*                   /*  Stage 2                                     */      *
*                   /*                                              */      *
*                   /*  Note, on the odd-half, the results are in   */      *
*                   /*  Q1.5 since those values are scaled upwards  */      *
*                   /*  by sqrt(2) at this point.                   */      *
*                   /* -------------------------------------------- */      *
*                   p0 = g0 + h0;               /*  Results in Q1   */      *
*                   p1 = g1 + h1;               /*  Results in Q1   */      *
*                   r0 = g0 - h0;               /*  Results in Q1   */      *
*                   r1 = g1 - h1;               /*  Results in Q1   */      *
*                                                                           *
*                   q1a = g2 + g2;              /*  q1a is now Q2   */      *
*                   s1a = h2 + h2;              /*  s1a is now Q2   */      *
*                   q1  = (q1a * C4 + 0x8000) >> 16; /*  .. in Q1.5 */      *
*                   s1  = (s1a * C4 + 0x8000) >> 16; /*  .. in Q1.5 */      *
*                                                                           *
*                   s0 = h3 + g3;               /*  Results in Q1.5 */      *
*                   q0 = h3 - g3;               /*  Results in Q1.5 */      *
*                                                                           *
*                   /* -------------------------------------------- */      *
*                   /*  Stage 3                                     */      *
*                   /*                                              */      *
*                   /*  Now, the even-half ends up in Q1.5.  On P0  */      *
*                   /*  and P1, this happens because the multiply-  */      *
*                   /*  by-C4 was canceled with an upward scaling   */      *
*                   /*  by sqrt(2).  On R0 and R1, this happens     */      *
*                   /*  because C2 and C6 are at Q15.5, and we      */      *
*                   /*  scale r0 and r1 to Q2 before we multiply.   */      *
*                   /* -------------------------------------------- */      *
*                   P0 = p0 + p1;               /*  Results in Q1.5 */      *
*                   P1 = p0 - p1;               /*  Results in Q1.5 */      *
*                                                                           *
*                   r0_= r0 + r0;               /*  r0_ is now Q2   */      *
*                   r1_= r1 + r1;               /*  r1_ is now Q2   */      *
*                   R1 = (C6 * r1_+ C2 * r0_+ 0x8000) >>16; /* Q1.5 */      *
*                   R0 = (C6 * r0_- C2 * r1_+ 0x8000) >>16; /* Q1.5 */      *
*                                                                           *
*                   Q1 = q1 + q0;               /*  Results in Q1.5 */      *
*                   S1 = s1 + s0;               /*  Results in Q1.5 */      *
*                   Q0 = q1 - q0;               /*  Results in Q1.5 */      *
*                   S0 = s1 - s0;               /*  Results in Q1.5 */      *
*                                                                           *
*                   /* -------------------------------------------- */      *
*                   /*  Stage 4                                     */      *
*                   /*  No further changes in Q-point happen here.  */      *
*                   /* -------------------------------------------- */      *
*                   F0 = P0;                    /*  Results in Q1.5 */      *
*                   F4 = P1;                    /*  Results in Q1.5 */      *
*                   F2 = R1;                    /*  Results in Q1.5 */      *
*                   F6 = R0;                    /*  Results in Q1.5 */      *
*                                                                           *
*                   F1 = (C7 * Q1 + C1 * S1 + 0x8000) >>16; /* Q1.5 */      *
*                   F7 = (C7 * S1 - C1 * Q1 + 0x8000) >>16; /* Q1.5 */      *
*                   F5 = (C3 * Q0 + C5 * S0 + 0x8000) >>16; /* Q1.5 */      *
*                   F3 = (C3 * S0 - C5 * Q0 + 0x8000) >>16; /* Q1.5 */      *
*                                                                           *
*                   /* -------------------------------------------- */      *
*                   /*  Store the frequency domain results.         */      *
*                   /*  These values are all at Q1.5 precision.     */      *
*                   /* -------------------------------------------- */      *
*                   dct_io_ptr[ 0] = F0;                                    *
*                   dct_io_ptr[ 8] = F1;                                    *
*                   dct_io_ptr[16] = F2;                                    *
*                   dct_io_ptr[24] = F3;                                    *
*                   dct_io_ptr[32] = F4;                                    *
*                   dct_io_ptr[40] = F5;                                    *
*                   dct_io_ptr[48] = F6;                                    *
*                   dct_io_ptr[56] = F7;                                    *
*                                                                           *
*                   dct_io_ptr++;                                           *
*               }                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Update pointer to next 8x8 FDCT block.          */      *
*               /* ------------------------------------------------ */      *
*               dct_io_ptr += 56;                                           *
*           }                                                               *
*                                                                           *
*           /* ---------------------------------------------------- */      *
*           /*  Perform Horizontal 1-D FDCT on each 8x8 block.      */      *
*           /* ---------------------------------------------------- */      *
*           dct_io_ptr = dct_data;                                          *
*           for (i = 0; i < 8 * num_fdcts; i++)                             *
*           {                                                               *
*               /* ------------------------------------------------ */      *
*               /*  Load the spatial-domain samples.                */      *
*               /*  The incoming terms are at Q1.5 precision from   */      *
*               /*  the first pass.                                 */      *
*               /* ------------------------------------------------ */      *
*               f0 = dct_io_ptr[0];                                         *
*               f1 = dct_io_ptr[1];                                         *
*               f2 = dct_io_ptr[2];                                         *
*               f3 = dct_io_ptr[3];                                         *
*               f4 = dct_io_ptr[4];                                         *
*               f5 = dct_io_ptr[5];                                         *
*               f6 = dct_io_ptr[6];                                         *
*               f7 = dct_io_ptr[7];                                         *
*                                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Stage 1:  Separate into even and odd halves.    */      *
*               /*                                                  */      *
*               /*  The results of this stage are implicitly in     */      *
*               /*  Q2.5, since we do not explicitly multiply by    */      *
*               /*  0.5.                                            */      *
*               /* ------------------------------------------------ */      *
*               g0 = f0 + f7;                   /*  Results in Q2.5 */      *
*               g1 = f1 + f6;                   /*  Results in Q2.5 */      *
*               h1 = f2 + f5;                   /*  Results in Q2.5 */      *
*               h0 = f3 + f4;                   /*  Results in Q2.5 */      *
*               g2 = f3 - f4;                   /*  Results in Q2.5 */      *
*               g3 = f2 - f5;                   /*  Results in Q2.5 */      *
*               h3 = f1 - f6;                   /*  Results in Q2.5 */      *
*               h2 = f0 - f7;                   /*  Results in Q2.5 */      *
*                                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Stage 2                                         */      *
*               /*                                                  */      *
*               /*  Note, on the odd-half, the results are in Q3    */      *
*               /*  since those values are scaled upwards by        */      *
*               /*  sqrt(2) at this point.  The order of operations */      *
*               /*  differs in this pass as compared to the first   */      *
*               /*  due to overflow concerns.                       */      *
*               /*                                                  */      *
*               /*  We also inject a rounding term into the DC      */      *
*               /*  term which will also round the Nyquist term,    */      *
*               /*  F4.  This trick works despite the fact that we  */      *
*               /*  are technically still at Q2.5 here, since       */      *
*               /*  the step from Q2.5 to Q3 later is done          */      *
*               /*  implicitly, rather than with a multiply. (This  */      *
*               /*  is due to the sqrt(2) terms cancelling on the   */      *
*               /*  P0/P1 butterfly.)                               */      *
*               /* ------------------------------------------------ */      *
*               p0 = g0 + h0 + 4;               /*  Results in Q2.5 */      *
*               p1 = g1 + h1;                   /*  Results in Q2.5 */      *
*               r0 = g0 - h0;                   /*  Results in Q2.5 */      *
*               r1 = g1 - h1;                   /*  Results in Q2.5 */      *
*                                                                           *
*               q1a= (g2 * C4 + 0x8000) >> 16;  /*  q1a now in Q2   */      *
*               s1a= (h2 * C4 + 0x8000) >> 16;  /*  s1a now in Q2   */      *
*               q1 = q1a + q1a;                 /*  Results in Q3   */      *
*               s1 = s1a + s1a;                 /*  Results in Q3   */      *
*                                                                           *
*               s0 = h3 + g3;                   /*  Results in Q3   */      *
*               q0 = h3 - g3;                   /*  Results in Q3   */      *
*                                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Stage 3                                         */      *
*               /*                                                  */      *
*               /*  Now, the even-half becomes Q0.  This happens    */      *
*               /*  on P0 and P1 because the multiply-by-c4 was     */      *
*               /*  canceled with an upward scaling by sqrt(2),     */      *
*               /*  yielding Q3 intermediate values.  The final     */      *
*               /*  >> 3 leaves these at Q0.  On R0 and R1, this    */      *
*               /*  happens because c2 and c6 are at Q13.5,         */      *
*               /*  yielding Q16 intermediate values.  The final    */      *
*               /*  >> 16 then leaves those values at Q0.           */      *
*               /* ------------------------------------------------ */      *
*               P0 = ((short)(p0 + p1)) >> 3;   /*  Results in Q0   */      *
*               P1 = ((short)(p0 - p1)) >> 3;   /*  Results in Q0   */      *
*               R1 = (c6 * r1 + c2 * r0 + 0x8000) >> 16; /* .. Q0   */      *
*               R0 = (c6 * r0 - c2 * r1 + 0x8000) >> 16; /* .. Q0   */      *
*                                                                           *
*               Q1 = q1 + q0;                   /*  Results in Q3   */      *
*               Q0 = q1 - q0;                   /*  Results in Q3   */      *
*               S1 = s1 + s0;                   /*  Results in Q3   */      *
*               S0 = s1 - s0;                   /*  Results in Q3   */      *
*                                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Stage 4                                         */      *
*               /*                                                  */      *
*               /*  Next, the odd-half ends up in Q0. This happens  */      *
*               /*  because our values are in Q3 and our cosine     */      *
*               /*  terms are in Q13, giving us Q16 intermediate    */      *
*               /*  values. The final >> 16 leaves us a Q0 result.  */      *
*               /* ------------------------------------------------ */      *
*               F0 = P0;                        /*  Results in Q0   */      *
*               F4 = P1;                        /*  Results in Q0   */      *
*               F2 = R1;                        /*  Results in Q0   */      *
*               F6 = R0;                        /*  Results in Q0   */      *
*                                                                           *
*               F1 = (c7 * Q1 + c1 * S1 + 0x8000) >> 16; /* .. Q0   */      *
*               F7 = (c7 * S1 - c1 * Q1 + 0x8000) >> 16; /* .. Q0   */      *
*               F5 = (c3 * Q0 + c5 * S0 + 0x8000) >> 16; /* .. Q0   */      *
*               F3 = (c3 * S0 - c5 * Q0 + 0x8000) >> 16; /* .. Q0   */      *
*                                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Store the results                               */      *
*               /* ------------------------------------------------ */      *
*               dct_io_ptr[0] = F0;                                         *
*               dct_io_ptr[1] = F1;                                         *
*               dct_io_ptr[2] = F2;                                         *
*               dct_io_ptr[3] = F3;                                         *
*               dct_io_ptr[4] = F4;                                         *
*               dct_io_ptr[5] = F5;                                         *
*               dct_io_ptr[6] = F6;                                         *
*               dct_io_ptr[7] = F7;                                         *
*                                                                           *
*               /* ------------------------------------------------ */      *
*               /*  Update pointer to next FDCT row.                */      *
*               /* ------------------------------------------------ */      *
*               dct_io_ptr += 8;                                            *
*           }                                                               *
*                                                                           *
*           return;                                                         *
*       }                                                                   *
*                                                                           *
*                                                                           *
*   TECHNIQUES                                                              *
*       The loop nest in the vertical pass has been collapsed into a        *
*       single-level loop.  Both vertical and horizontal loops have         *
*       been software pipelined.                                            *
*                                                                           *
*       For performance, portions of the code outside the loops have been   *
*       inter-scheduled with the prolog and epilog code of the loops.       *
*       Also, twin stack-pointers are used to accelerate stack accesses.    *
*       Finally, pointer values and cosine term registers are reused        *
*       between the horizontal and vertical loops to reduce the impact of   *
*       pointer and constant reinitialization.                              *
*                                                                           *
*       To save codesize, prolog and epilog collapsing have been performed  *
*       to the extent that it does not impact performance.                  *
*                                                                           *
*       To reduce register pressure and save some code, the horizontal      *
*       loop uses the same pair of pointer register for both reading and    *
*       writing.  The pointer increments are on the LDs to permit prolog    *
*       and epilog collapsing, since LDs can be speculated.                 *
*                                                                           *
*   ASSUMPTIONS                                                             *
*       Stack is aligned to a double-word boundary.                         *
*                                                                           *
*   MEMORY NOTE                                                             *
*       No bank conflicts occur.                                            *
*                                                                           *
*       The "fdct_data[]" array must be aligned on a double-word (8 byte)   *
*       boundary.                                                           *
*                                                                           *
*       The code requires 4 words of stack space to save Save-On-Entry      *
*       (SOE) registers.                                                    *
*                                                                           *
*       Nearly every cycle of this function performs at least one           *
*       memory access.                                                      *
*                                                                           *
*   NOTES                                                                   *
*       This code is fully interruptible.  Interrupts are blocked only      *
*       branch delay slots.                                                 *
*                                                                           *
*       The cosine terms have all been scaled by sqrt(2), so that the       *
*       "c4" term is basically an even power of 2.                          *
*                                                                           *
*       The code is LITTLE ENDIAN.                                          *
*                                                                           *
*   CYCLES                                                                  *
*       cycles = 50 + 76 * num_fdcts                                        *
*                                                                           *
*       For num_fdcts =  6, cycles = 506.                                   *
*       For num_fdcts = 24, cycles = 1848.                                  *
*                                                                           *
*   CODESIZE                                                                *
*       980 bytes.                                                          *
*                                                                           *
*   SOURCE                                                                  *
*       Chen FDCT.                                                          *
*                                                                           *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
                .sect ".text:hand"
                .if     __TI_EABI__
          		 .asg    IMG_fdct_8x8, _IMG_fdct_8x8
        	    .endif
                .global _IMG_fdct_8x8

_IMG_fdct_8x8:
* ================= SYMBOLIC REGISTER ASSIGNMENTS: ARGS. ================== *
        ;;                                      ; void fdct_8x8(
        .asg            A4,         A_dct_data  ;   short dct_data[],
        .asg            B4,         B_num_dcts  ;   unsigned num_dcts
        ;;                                      ; );
* ================= SYMBOLIC REGISTER ASSIGNMENTS: MISC. ================== *
        .asg            B15,        B_SP        ; Stack pointer, B datapath
        .asg            A2,         A_SP        ; Twin Stack ptr, A datapath
        .asg            B3,         B_ret       ; Return address 
        .asg            A11,        A_ret_sv    ; Return address copy
* ===================== SYMBOLIC CONSTANT ASSIGNMENTS ===================== *
        .asg            0xFB15,     cst_C1      ; Cosine term C1
        .asg            0xA73D,     cst_C2      ; Cosine term C2
        .asg            0xD4DB,     cst_C3      ; Cosine term C3
        .asg            0xB505,     cst_C4      ; Cosine term C4
        .asg            0x8E3A,     cst_C5      ; Cosine term C5
        .asg            0x4546,     cst_C6      ; Cosine term C6
        .asg            0x31F1,     cst_C7      ; Cosine term C7
* ================== SYMBOLIC REGISTER ASSIGNMENTS: V_LOOP ================ *
        ;; Cosine terms
        .asg            A21,        A_C1C7      ; Packed terms C1, C7
        .asg            B0,         B_C1C7      ; Packed terms C1, C7
        .asg            B2,         B_C2C6      ; Packed terms C2, C6
        .asg            A23,        A_C3C5      ; Packed terms C3, C5
        .asg            B4,         B_C3C5      ; Packed terms C3, C5
        .asg            A18,        A_C4__      ; Packed terms C4, zero
        .asg            A28,        A___C4      ; Packed terms zero, C4
        .asg            A24,        A_C5C3      ; Packed terms C5, C3
        .asg            A20,        A_C6C2      ; Packed terms C6, C2
        .asg            B10,        B_C7C1      ; Packed terms C7, C1

        ;; Input and output pointers
        .asg            A4,         A_i_ptr     ; Input pointer
        .asg            B26,        B_o_ptr     ; Output pointer
        .asg            B28,        B_fix       ; Pointer fixup constant
        .asg            B23,        B_fix_      ; Pointer fixup offset
        .asg            A29,        A_fix_      ; Pointer fixup offset

        ;; Incoming spatial-domain samples
        .asg            A9,         A_f0f0      ; Packed f0 terms, both cols
        .asg            B24,        B_f1f1      ; Packed f1 terms, both cols
        .asg            B25,        B_f2f2      ; Packed f2 terms, both cols
        .asg            A22,        A_f3f3      ; Packed f3 terms, both cols
        .asg            A26,        A_f4f4      ; Packed f4 terms, both cols
        .asg            B19,        B_f5f5      ; Packed f5 terms, both cols
        .asg            B9,         B_f6f6      ; Packed f6 terms, both cols
        .asg            A5,         A_f7f7      ; Packed f7 terms, both cols

        ;; Initial add/subtract butterflies
        .asg            A17,        A_g0g0      ; g0 = f7 + f0, both columns
        .asg            B29,        B_g1g1      ; g1 = f6 + f1, both columns
        .asg            B16,        B_h1h1      ; h1 = f5 + f2, both columns
        .asg            A1,         A_h0h0      ; h0 = f4 + f3, both columns
        .asg            A31,        A_g2g2      ; g2 = f3 - f4, both columns
        .asg            B9,         B_g3g3      ; g3 = f2 - f5, both columns
        .asg            B8,         B_h3h3      ; h3 = f1 - f6, both columns
        .asg            A31,        A_h2h2      ; h2 = f0 - f7, both columns
        .asg            B9,         B_s0s0      ; s0 = h3 + g3, both columns
        .asg            B8,         B_q0q0      ; q0 = h3 - g3, both columns
        .asg            A10,        A_p0p0      ; p0 = g0 + h0, both columns
        .asg            B16,        B_p1p1      ; p1 = g1 + h1, both columns
        .asg            B21,        B_r1r1      ; r1 = g1 - h1, both columns
        .asg            A7,         A_r0r0      ; r0 = g0 - h0, both columns
        .asg            B20,        B_r1r1_     ; r1, q-point adjusted
        .asg            A3,         A_r0r0_     ; r0, q-point adjusted
        .asg            A27,        A_r0r1_     ; r0, r1 packed, "A" column
        .asg            B29,        B_r1r0_     ; r1, r0 packed, "B" column
        .asg            B31,        B_r0r1_     ; r0, r1 packed, "B" column
        .asg            A9,         A_g2g2_     ; g2, q-point adjusted
        .asg            A3,         A_h2h2_     ; h2, q-point adjusted
        .asg            A30,        A_g2h2      ; g2, h2 packed, "A" column
        .asg            A8,         Axg2h2      ; g2, h2 packed, "B" column
        .asg            B7,         B_g2h2      ; g2, h2 packed, "B" column

        ;; Remaining FDCT butterflies.
        .asg            A5,         A_q1        ; q1 = C4 * g2
        .asg            A11,        A_s1        ; s1 = C4 * h2
        .asg            A5,         A_s1q1      ; s1, q1 packed
        .asg            B5,         Bxs0q0      ; s0, q0 packed
        .asg            A12,        A_S1Q1      ; S1 = s1 + s0, Q1 = q1 + q0
        .asg            A2,         A_S0Q0      ; S0 = s1 - s0, Q0 = q1 - q0

        .asg            B25,        B_q1        ; q1 = C4 * g2
        .asg            B7,         B_s1        ; s1 = C4 * h2
        .asg            B18,        B_s1q1      ; s1, q1 packed
        .asg            B8,         B_s0q0      ; s0, q0 packed
        .asg            B6,         B_S0Q0      ; S1 = s1 + s0, Q1 = q1 + q0
        .asg            B20,        B_S1Q1      ; S0 = s1 - s0, Q0 = q1 - q0

        ;; Final frequency-domain terms.
        .asg            A3,         A_F4F4_     ; F4 terms, both columns
        .asg            A2,         A_F1        ; Freq domain F1, "A" column
        .asg            A19,        A_F2        ; Freq domain F2, "A" column
        .asg            A7,         A_F3        ; Freq domain F3, "A" column
        .asg            A8,         A_F5        ; Freq domain F5, "A" column
        .asg            A31,        A_F6        ; Freq domain F6, "A" column
        .asg            A6,         A_F7        ; Freq domain F7, "A" column
        .asg            B30,        B_F1        ; Freq domain F1, "B" column
        .asg            B21,        B_F2        ; Freq domain F2, "B" column
        .asg            B6,         B_F3        ; Freq domain F3, "B" column
        .asg            B18,        B_F5        ; Freq domain F5, "B" column
        .asg            B17,        B_F6        ; Freq domain F6, "B" column
        .asg            B27,        B_F7        ; Freq domain F7, "B" column
        .asg            A16,        A_F0F0      ; Packed F0 terms, both cols
        .asg            B16,        B_F1F1      ; Packed F1 terms, both cols
        .asg            A19,        A_F2F2      ; Packed F2 terms, both cols
        .asg            B8,         B_F3F3      ; Packed F3 terms, both cols
        .asg            A25,        A_F4F4      ; Packed F4 terms, both cols
        .asg            B7,         B_F5F5      ; Packed F5 terms, both cols
        .asg            A31,        A_F6F6      ; Packed F6 terms, both cols
        .asg            B21,        B_F7F7      ; Packed F7 terms, both cols

        ;; Loop control
        .asg            A0,         Ap          ; Prolog collapse predicate
        .asg            B1,         B_i         ; Loop counter
        .asg            B22,        B_i_horiz   ; Loop ctr copy for h_loop
* ========================================================================= *

* ========================================================================= *
*  V_LOOP:  VERTICAL PASS LOOP                                              *
* ========================================================================= *

* ==================== SETUP CODE AND PIPE LOOP PROLOG ==================== *
        LDW     .D1T1   *+A_i_ptr  [16],        A_f4f4          ;[ 1,1] 
||      ADDK    .S1     32,         A_i_ptr                     ; offset i_ptr
||      SHL     .S2     B_num_dcts, 2,          B_i             ; i = 4*num

  [ B_i]LDW     .D1T1   *+A_i_ptr  [ 4],        A_f3f3          ;[ 2,1] 
||[ B_i]ZERO    .L1     A_C4__                                  ; set up cst 0
||[!B_i]RET     .S2     B_ret                                   ; early abort

  [ B_i]LDW     .D1T1   *-A_i_ptr  [ 8],        A_f0f0          ;[ 3,1] 
||[ B_i]MVKLH   .S1     cst_C4,     A_C4__                      ; const C4
||[ B_i]MV      .L2X    A_i_ptr,    B_o_ptr

  [ B_i]LDW     .D1T1   *+A_i_ptr  [20],        A_f7f7          ;[ 4,1] 
||[ B_i]MVKL    .S1     cst_C5,     A_C3C5                      ; const C5
||[ B_i]MV      .L1X    B_SP,       A_SP

  [ B_i]LDW     .D1T2   *-A_i_ptr  [ 4],        B_f1f1          ;[ 5,1] 
||[ B_i]MVKL    .S1     cst_C2,     A_C6C2                      ; const C2
||[ B_i]MVK     .L1     1,          A_fix_                      ; init fixup

  [ B_i]LDW     .D1T2   *+A_i_ptr  [12],        B_f5f5          ;[ 6,1] 
||[ B_i]MVKLH   .S1     cst_C6,     A_C6C2                      ; const C6
||[ B_i]MVKL    .S2     cst_C7,     B_C1C7                      ; const C7
||[ B_i]SWAP2   .L1     A_C4__,     A___C4                      ; swapped pair
||[ B_i]ADDAW   .D2     B_o_ptr,    20,         B_o_ptr         ; offset o_ptr

  [ B_i]LDW     .D1T2   *+A_i_ptr  [16],        B_f6f6          ;[ 7,1] 
||[ B_i]MVK     .L1     2,          Ap                          ; pro. collapse
||[ B_i]MVKLH   .S2     cst_C1,     B_C1C7                      ; const C1
||[ B_i]MVKLH   .S1     cst_C3,     A_C3C5                      ; const C3
||[ B_i]SUBU    .L2X    B_i,        A_fix_,     B_fix_:B_i_horiz; 2nd loop copy

        SUB2    .L1     A_f3f3,     A_f4f4,     A_g2g2          ;[ 8,1] 
||      ADD2    .S1     A_f3f3,     A_f4f4,     A_h0h0          ;[ 8,1] 
||      MVKL    .S2     0x0101011D, B_fix                       ; ptr fix cst.
||      ROTL    .M2X    A_C6C2,     16,         B_C2C6          ; swapped pair
||      ROTL    .M1     A_C3C5,     16,         A_C5C3          ; swapped pair
||      STW     .D1T1   A12,        *-A_SP[3]                   ; Save A12
||      STW     .D2T2   B10,        * B_SP--[4]                 ; Save B10

        ADD2    .L1     A_g2g2,     A_g2g2,     A_g2g2_         ;[ 9,1] 
||      SUB2    .S1     A_f0f0,     A_f7f7,     A_h2h2          ;[ 9,1] 
||      ADD2    .D1     A_f0f0,     A_f7f7,     A_g0g0          ;[ 9,1] 
||      MVKH    .S2     0x0101011D, B_fix                       ; ptr fix cst.
||      SWAP2   .L2     B_C1C7,     B_C7C1                      ; swapped pair
||      ROTL    .M2X    A_C3C5,     0,          B_C3C5          ; swapped pair
||      ROTL    .M1X    B_C1C7,     0,          A_C1C7          ; swapped pair
||      STDW    .D2T1   A11:A10,    *+B_SP[1]                   ; Save A11, A10

; Collapsed 2 prolog stages.
; ============================ PIPE LOOP KERNEL =========================== *
v_loop:
  [!Ap] STW     .D2T1   A_F0F0,     *-B_o_ptr  [28]             ;[30,1] 
||      PACK2   .S2X    B_F5,       A_F5,       B_F5F5          ;[30,1] 
||      DOTPNRSU2.M1    A_r0r1_,    A_C6C2,     A_F6            ;[30,1] 
||      PACK2   .L2     B_s1,       B_q1,       B_s1q1          ;[20,2] 
||      ROTL    .M2     B_r1r0_,    16,         B_r0r1_         ;[20,2] 
||      PACKH2  .S1X    A_r0r0_,    B_r1r1_,    A_r0r1_         ;[20,2] 
||      ADD2    .L1     A_h2h2,     A_h2h2,     A_h2h2_         ;[10,3] 
||[B_i] LDW     .D1T2   * A_i_ptr++[A_fix_],    B_f2f2          ;[10,3] 

        PACK2   .S2X    B_F3,       A_F3,       B_F3F3          ;[31,1] 
||      DOTPNRSU2.M1X   A_S1Q1,     B_C7C1,     A_F7            ;[31,1] 
||      SUB2    .D2     B_s1q1,     B_s0q0,     B_S0Q0          ;[21,2] 
||      ADD2    .L2     B_s1q1,     B_s0q0,     B_S1Q1          ;[21,2] 
||      PACK2   .L1     A_g2g2_,    A_h2h2_,    Axg2h2          ;[11,3] 
||      PACKH2  .S1     A_g2g2_,    A_h2h2_,    A_g2h2          ;[11,3] 
||[B_i] LDW     .D1T1   *+A_i_ptr  [ 8],        A_f4f4          ;[ 1,4] 
||      ROTL    .M2     B_fix,      8,          B_fix           ;[ 1,4]

  [!Ap] STW     .D2T2   B_F3F3,     *-B_o_ptr  [16]             ;[32,1] 
||      SUB2    .L1X    A_p0p0,     B_p1p1,     A_F4F4          ;[22,2] 
||      DOTPRSU2.M2X    B_S0Q0,     A_C5C3,     B_F5            ;[22,2] 
||      ROTL    .M1     A_F4F4,     0,          A_F4F4_         ;[22,2] 
||      SUB2    .S1     A_g0g0,     A_h0h0,     A_r0r0          ;[12,3] 
||      SUB2    .S2     B_f1f1,     B_f6f6,     B_h3h3          ;[12,3] 
||      ADD2    .L2     B_f1f1,     B_f6f6,     B_g1g1          ;[12,3] 
||[B_i] LDW     .D1T1   *+A_i_ptr  [ 4],        A_f3f3          ;[ 2,4] 

  [!Ap] STW     .D2T2   B_F5F5,     *-B_o_ptr  [ 8]             ;[33,1] 
||      PACK2   .L2X    B_F1,       A_F1,       B_F1F1          ;[33,1] 
||      ADD2    .S1X    A_p0p0,     B_p1p1,     A_F0F0          ;[23,2] 
||      DOTPNRSU2.M2    B_S0Q0,     B_C3C5,     B_F3            ;[23,2] 
||      PACK2   .L1     A_s1,       A_q1,       A_s1q1          ;[23,2] 
||      DOTPRSU2.M1     A_g2h2,     A___C4,     A_s1            ;[13,3] 
||[B_i] LDW     .D1T1   *-A_i_ptr  [ 8],        A_f0f0          ;[ 3,4] 
||[!Ap] EXT     .S2     B_fix,      8,  24,     B_fix_          ;[ 3,4]

  [B_i] BDEC    .S2     v_loop,     B_i                         ;[34,1] 
||[!Ap] STW     .D2T2   B_F1F1,     *-B_o_ptr  [24]             ;[34,1] 
||      DOTPRSU2.M2     B_S1Q1,     B_C1C7,     B_F1            ;[24,2] 
||      SUB2    .L1X    A_s1q1,     Bxs0q0,     A_S0Q0          ;[24,2] 
||      ADD2    .S1X    A_s1q1,     Bxs0q0,     A_S1Q1          ;[24,2] 
||      MV      .L2X    Axg2h2,     B_g2h2                      ;[14,3] 
||[B_i] LDW     .D1T1   *+A_i_ptr  [20],        A_f7f7          ;[ 4,4] 

        PACK2   .L1X    A_F6,       B_F6,       A_F6F6          ;[35,1] 
||[!Ap] STW     .D2T1   A_F4F4_,    *-B_o_ptr  [12]             ;[35,1] 
||      DOTPRSU2.M1     A_S0Q0,     A_C5C3,     A_F5            ;[25,2] 
||      DOTPRSU2.M2X    B_g2h2,     A_C4__,     B_q1            ;[15,3] 
||      ADD2    .S1     A_r0r0,     A_r0r0,     A_r0r0_         ;[15,3] 
||      SUB2    .S2     B_f2f2,     B_f5f5,     B_g3g3          ;[15,3] 
||      ADD2    .L2     B_f2f2,     B_f5f5,     B_h1h1          ;[15,3] 
||[B_i] LDW     .D1T2   *-A_i_ptr  [ 4],        B_f1f1          ;[ 5,4] 

        PACK2   .L1X    A_F2,       B_F2,       A_F2F2          ;[36,1] 
||      DOTPNRSU2.M1    A_S0Q0,     A_C3C5,     A_F3            ;[26,2] 
||      DOTPRSU2.M2X    B_g2h2,     A___C4,     B_s1            ;[16,3] 
||      SUB2    .S2     B_g1g1,     B_h1h1,     B_r1r1          ;[16,3] 
||      SUB2    .L2     B_h3h3,     B_g3g3,     B_q0q0          ;[16,3] 
||      ADD2    .D2     B_h3h3,     B_g3g3,     B_s0s0          ;[16,3] 
||[B_i] LDW     .D1T2   *+A_i_ptr  [12],        B_f5f5          ;[ 6,4] 

  [!Ap] STW     .D2T1   A_F2F2,     *-B_o_ptr  [20]             ;[37,1] 
||      DOTPNRSU2.M2X   B_r0r1_,    A_C6C2,     B_F6            ;[27,2] 
||      DOTPRSU2.M1     A_S1Q1,     A_C1C7,     A_F1            ;[27,2] 
||      PACK2   .S2     B_s0s0,     B_q0q0,     B_s0q0          ;[17,3] 
||      PACKH2  .L2     B_s0s0,     B_q0q0,     Bxs0q0          ;[17,3] 
||      ADD2    .L1     A_g0g0,     A_h0h0,     A_p0p0          ;[17,3] 
||[B_i] LDW     .D1T2   *+A_i_ptr  [16],        B_f6f6          ;[ 7,4] 
||      SHR     .S1X    B_fix,      24,         A_fix_          ;[ 7,4]

  [!Ap] STW     .D2T1   A_F6F6,     *-B_o_ptr  [ 4]             ;[38,1] 
||      PACK2   .L2X    B_F7,       A_F7,       B_F7F7          ;[38,1] 
||      DOTPNRSU2.M2    B_S1Q1,     B_C7C1,     B_F7            ;[28,2] 
||      DOTPRSU2.M1X    A_r0r1_,    B_C2C6,     A_F2            ;[28,2] 
||      ADD2    .S2     B_r1r1,     B_r1r1,     B_r1r1_         ;[18,3] 
||      SUB2    .L1     A_f3f3,     A_f4f4,     A_g2g2          ;[ 8,4] 
||      ADD2    .D1     A_f3f3,     A_f4f4,     A_h0h0          ;[ 8,4] 
||[ Ap] SUB     .S1     Ap,         1,          Ap

  [!Ap] STW     .D2T2   B_F7F7,     * B_o_ptr++[B_fix_]         ;[39,1] 
||      DOTPRSU2.M2     B_r0r1_,    B_C2C6,     B_F2            ;[29,2] 
||      DOTPRSU2.M1     A_g2h2,     A_C4__,     A_q1            ;[19,3] 
||      PACK2   .S2X    B_r1r1_,    A_r0r0_,    B_r1r0_         ;[19,3] 
||      ADD2    .L2     B_g1g1,     B_h1h1,     B_p1p1          ;[19,3] 
||      ADD2    .L1     A_g2g2,     A_g2g2,     A_g2g2_         ;[ 9,4] 
||      SUB2    .S1     A_f0f0,     A_f7f7,     A_h2h2          ;[ 9,4] 
||      ADD2    .D1     A_f0f0,     A_f7f7,     A_g0g0          ;[ 9,4] 
* ========================================================================= *


* ================== SYMBOLIC REGISTER ASSIGNMENTS: H_LOOP ================ *
        ;; Cosine terms and rounding constant
        .asg            A21,        A_c1c7      ; Packed c1, c7
        .asg            A3,         A_c2c6      ; Packed c2, c6
        .asg            A23,        A_c3c5      ; Packed c3, c5
        .asg            A18,        A_C4__      ; Packed c4, zero
        .asg            B28,        B_C4__      ; Packed c4, zero 
        .asg            A24,        A_c5c3      ; Packed c5, c3
        .asg            A20,        A_c6c2      ; Packed c6, c2
        .asg            A22,        A_c7c1      ; Packed c7, c1
        .asg            A25,        A_dc_rnd    ; Packed DC rounding terms

        ;; Input and output pointers
        .asg            A4,         A_io_ptr    ; Twin Input/Output pointer
        .asg            B26,        B_io_ptr    ; Twin Input/Output pointer

        ;; Incoming spatial-domain samples
        .asg            A17,        A_f7f6      ; Packed f7, f6, "A" row
        .asg            A16,        A_f5f4      ; Packed f5, f4, "A" row
        .asg            A1,         A_f4f5      ; Packed f4, f5, "A" row
        .asg            A29,        A_f3f2      ; Packed f3, f2, "A" row
        .asg            A28,        A_f1f0      ; Packed f1, f0, "A" row
        .asg            A6,         A_f0f1      ; Packed f0, f1, "A" row

        .asg            A2,         Axf7f6      ; Packed f7, f6, "B" row
        .asg            B5,         B_f7f6      ; Packed f7, f6, "B" row
        .asg            B25,        B_f6f7      ; Packed f6, f7, "B" row
        .asg            B24,        B_f4f5      ; Packed f4, f5, "B" row
        .asg            B6,         B_f3f2      ; Packed f3, f2, "B" row
        .asg            B1,         B_f2f3      ; Packed f2, f3, "B" row
        .asg            B0,         B_f0f1      ; Packed f0, f1, "B" row

        ;; Initial add/subtract butterflies
                                                ; "A" row:
        .asg            A7,         A_g0g1      ; g0 = f0 + f7, g1 = f1 + f6
        .asg            A19,        A_h2h3      ; h2 = f0 - f7, h3 = f1 - f6
        .asg            A1,         A_h0h1      ; h0 = f3 + f4, h1 = f2 + f5
        .asg            A5,         A_g2g3      ; g2 = f3 - f4, g3 = f2 - f5
        .asg            A9,         A_p0p1      ; p0 = g0 + h0, p1 = g1 + h1
        .asg            A0,         A_r0r1      ; r0 = g0 - h0, r1 = g1 - h1

                                                ; "B" row:
        .asg            B5,         B_g0g1      ; g0 = f0 + f7, g1 = f1 + f6
        .asg            B24,        B_h2h3      ; h2 = f0 - f7, h3 = f1 - f6
        .asg            B7,         B_h0h1      ; h0 = f3 + f4, h1 = f2 + f5
        .asg            B6,         B_g2g3      ; g2 = f3 - f4, g3 = f2 - f5
        .asg            B9,         B_p0p1      ; p0 = g0 + h0, p1 = g1 + h1
        .asg            B29,        B_r0r1      ; r0 = g0 - h0, r1 = g1 - h1

        ;; DC and Nyquist term butterflies, which straddle both datapaths
        .asg            A7,         A_p0p0_     ; Packed p0's, pre-round.
        .asg            A30,        A_p0p0      ; Packed p0's, rounded.
        .asg            A9,         A_p1p1      ; Packed p1's.

        .asg            A9,         A_F0F0_     ; Packed F0's, Q3
        .asg            A16,        A_F4F4_     ; Packed F4's, Q3
        .asg            B19,        B_F0F0      ; Packed F0's, Q0 (final)
        .asg            B8,         B_F4F4      ; Packed F0's, Q0 (final)

        ;; Remaining FDCT butterflies
                                                ; "A" row:
        .asg            A27,        A_q1_       ; q1_= C4 * g2 
        .asg            A26,        A_s1_       ; s1_= C4 * h2
        .asg            A1,         A_s1q1_     ; Packed s1_, q1_
        .asg            A30,        A_s1q1      ; s1 = s1_ << 1, q1 = q1_ << 1 
        .asg            A5,         A_q0        ; q0 = h3 + g3
        .asg            A6,         A_s0        ; s0 = h3 - g3
        .asg            A5,         A_s0q0      ; Packed s0, q0
        .asg            A12,        A_S1Q1      ; S1 = s1 + s0, Q1 = q1 + q0
        .asg            A30,        A_S0Q0      ; S0 = s1 - s0, Q0 = q1 - q0

                                                ; "B" row:
        .asg            B4,         B_q1_       ; q1_= C4 * g2 
        .asg            B3,         B_s1_       ; s1_= C4 * h2
        .asg            B3,         B_s1q1_     ; Packed s1_, q1_
        .asg            B3,         B_s1q1      ; s1 = s1_ << 1, q1 = q1_ << 1 
        .asg            B6,         B_q0        ; q0 = h3 + g3
        .asg            B0,         B_s0        ; s0 = h3 - g3
        .asg            B10,        B_s0q0      ; Packed s0, q0
        .asg            B20,        B_S1Q1      ; S1 = s1 + s0, Q1 = q1 + q0
        .asg            B1,         B_S0Q0      ; S0 = s1 - s0, Q0 = q1 - q0

        ;; Final frequency-domain results.
                                                ; "A" row:
        .asg            A2,         A_F1        ; Freq. domain F1 term.
        .asg            A19,        A_F2        ; Freq. domain F2 term.
        .asg            A7,         A_F3        ; Freq. domain F3 term.
        .asg            A8,         A_F5        ; Freq. domain F5 term.
        .asg            A31,        A_F6        ; Freq. domain F6 term.
        .asg            A6,         A_F7        ; Freq. domain F7 term.

        .asg            A27,        A_F7F6      ; Packed F7, F6
        .asg            A26,        A_F5F4      ; Packed F5, F4
        .asg            A29,        A_F3F2      ; Packed F3, F2
        .asg            A28,        A_F1F0      ; Packed F1, F0

                                                ; "B" row:
        .asg            B30,        B_F1        ; Freq. domain F1 term.
        .asg            B21,        B_F2        ; Freq. domain F2 term.
        .asg            B6,         B_F3        ; Freq. domain F3 term.
        .asg            B18,        B_F5        ; Freq. domain F5 term.
        .asg            B17,        B_F6        ; Freq. domain F6 term.
        .asg            B27,        B_F7        ; Freq. domain F7 term.

        .asg            B17,        B_F7F6      ; Packed F7, F6
        .asg            B16,        B_F5F4      ; Packed F5, F4
        .asg            B31,        B_F3F2      ; Packed F3, F2
        .asg            B30,        B_F1F0      ; Packed F1, F0

        ;; Loop control
        .asg            B2,         Bp          ; Prolog collapse counter.
        .asg            B22,        B_i         ; Loop trip counter.
* ========================================================================= *

* ========================================================================= *
*  H_LOOP: HORIZONTAL PASS LOOP                                             *
*                                                                           *
*  Note:  2 cycles of this code have been "relocated" to the end so that    *
*  the h_loop branch target does not span two fetch packets.  The net       *
*  result is that this function has NO execute packet padding.              *
* ========================================================================= *

* ====================== PIPE LOOP EPILOG AND PROLOG ====================== *
; Collapsed 2 epilog stages.
        LDNDW   .D2T2   *--B_io_ptr(12),        B_f2f3:B_f0f1   ;[ 2,1] 
||      PACK2   .S2X    B_F5,       A_F5,       B_F5F5          ;[30,4] 
||      DOTPNRSU2.M1X   A_S1Q1,     B_C7C1,     A_F7            ;[31,4] 
||      B               reloc

        LDW     .D1T2   *-A_io_ptr  [10],       B_f4f5          ;
||      DOTPNRSU2.M1    A_r0r1_,    A_C6C2,     A_F6            ;[30,4] 
||      STW     .D2T1   A_F0F0,     *-B_io_ptr [25]             ;[30,4] 
||      ADDK    .S2     -20,        B_io_ptr

        SHRU2   .S1     A_C6C2,     2,          A_c6c2
||      PACK2   .L2X    B_F3,       A_F3,       B_F3F3          ;[31,4] 
||      STW     .D2T2   B_F5F5,     *B_io_ptr--[ 8]             ;[33,4] 
||      B               h_loop

        SHRU2   .S1     A_C5C3,     3,          A_c5c3
||      STW     .D2T2   B_F3F3,     *B_io_ptr--[ 8]             ;[32,4] 
||      PACK2   .L2X    B_F1,       A_F1,       B_F1F1          ;[33,4] 
||      MV      .L1X    B_ret,      A_ret_sv

        SHRU2   .S1     A_C3C5,     3,          A_c3c5
||      MVK     .L2     3,          Bp
||      STW     .D2T2   B_F1F1,     *B_io_ptr++[12]             ;[34,4] 
||      PACK2   .L1X    A_F7,       B_F7,       Axf7f6          ;

        SWAP2   .L2     B_f2f3,     B_f3f2                      ;[ 7,1] 
||      MV      .S2X    A_C4__,     B_C4__
||      SHRU2   .S1     A_C1C7,     3,          A_c1c7
||      PACK2   .L1X    A_F2,       B_F2,       A_F2F2          ;[36,4] 
||      STW     .D2T1   A_F4F4,     *B_io_ptr--[ 8]             ;[35,4] 
||      MVK     .D1     4,          A_dc_rnd
* ========================== RELOC. BRANCH OCCURS ========================= *

; Collapsed 2 prolog stages.
* ============================ PIPE LOOP KERNEL ============================ *
h_loop:
        DOTPNRSU2.M1    A_S1Q1,     A_c7c1,     A_F7            ;[28,1] 
||      ADD2    .S2     B_s1q1,     B_s0q0,     B_S1Q1          ;[19,2] 
||      PACK2   .L1     A_s0,       A_q0,       A_s0q0          ;[19,2] 
||      ADD2    .S1     A_g0g1,     A_h0h1,     A_p0p1          ;[19,2] 
||      SUB     .L2     B_h2h3,     B_g2g3,     B_q0            ;[10,3] 
||      DOTPRSU2.M2     B_h2h3,     B_C4__,     B_s1_           ;[10,3] 
||      LDDW    .D1T1   * A_io_ptr--[4],        A_f3f2:A_f1f0   ;[10,3] 
||      LDDW    .D2T2   *+B_io_ptr  [1],        B_f6f7:B_f4f5   ;[ 1,4] 

        DOTPRSU2.M1     A_S1Q1,     A_c1c7,     A_F1            ;[29,1] 
||      PACK2   .L1X    A_p0p1,     B_p0p1,     A_p1p1          ;[20,2] 
||      PACKH2  .S1X    A_p0p1,     B_p0p1,     A_p0p0_         ;[20,2] 
||      DOTPNRSU2.M2X   B_S0Q0,     A_c3c5,     B_F3            ;[20,2] 
||      SUB2    .D1     A_g0g1,     A_h0h1,     A_r0r1          ;[20,2] 
||      PACK2   .L2     B_s0,       B_q0,       B_s0q0          ;[11,3] 
||      ADD2    .S2     B_g0g1,     B_h0h1,     B_p0p1          ;[11,3] 
||      LDDW    .D2T2   * B_io_ptr--[4],        B_f2f3:B_f0f1   ;[ 2,4] 

        PACK2   .S2     B_F1,       B_F0F0,     B_F1F0          ;[30,1] 
||      PACK2   .L2     B_F7,       B_F6,       B_F7F6          ;[30,1] 
||      PACKLH2 .L1X    A_F5,       B_F4F4,     A_F5F4          ;[30,1] 
||      DOTPNRSU2.M1    A_S0Q0,     A_c3c5,     A_F3            ;[30,1] 
||      ADD2    .D1     A_p0p0_,    A_dc_rnd,   A_p0p0          ;[21,2] 
||      DOTPNRSU2.M2X   B_S1Q1,     A_c7c1,     B_F7            ;[21,2] 
||      PACK2   .S1     A_s1_,      A_q1_,      A_s1q1_         ;[21,2] 
||[ Bp] SUB     .D2     Bp,         1,          Bp              ;pro. collapse

        BDEC    .S2     h_loop,     B_i                         ;[31,1]
||[!Bp] STDW    .D2T2   B_F3F2:B_F1F0,          *+B_io_ptr[16]  ;[31,1] 
||      SUB2    .D1     A_p0p0,     A_p1p1,     A_F4F4_         ;[22,2] 
||      ADD2    .S1     A_p0p0,     A_p1p1,     A_F0F0_         ;[22,2] 
||      DOTPRSU2.M2X    B_S1Q1,     A_c1c7,     B_F1            ;[22,2] 
||      ADD2    .L1     A_s1q1_,    A_s1q1_,    A_s1q1          ;[22,2] 
||      ROTL    .M1     A_f5f4,     16,         A_f4f5          ;[13,3] 

  [!Bp] STDW    .D2T2   B_F7F6:B_F5F4,          *+B_io_ptr[17]  ;[32,1] 
||      PACK2   .L1     A_F7,       A_F6,       A_F7F6          ;[32,1] 
||      DOTPNRSU2.M2X   B_r0r1,     A_c6c2,     B_F6            ;[23,2] 
||      SUB2    .S1     A_s1q1,     A_s0q0,     A_S0Q0          ;[23,2] 
||      ADD2    .D1     A_s1q1,     A_s0q0,     A_S1Q1          ;[23,2] 
||      DOTPNRSU2.M1    A_r0r1,     A_c6c2,     A_F6            ;[23,2] 
||      PACK2   .L2     B_s1_,      B_q1_,      B_s1q1_         ;[14,3] 
||      SUB2    .S2     B_g0g1,     B_h0h1,     B_r0r1          ;[14,3] 

        PACK2   .L2     B_F3,       B_F2,       B_F3F2          ;[24,2] 
||      SHR2    .S2X    A_F4F4_,    3,          B_F4F4          ;[24,2] 
||      DOTPRSU2.M1     A_S0Q0,     A_c5c3,     A_F5            ;[24,2] 
||      ADD2    .D2     B_s1q1_,    B_s1q1_,    B_s1q1          ;[15,3] 
||      SUB2    .D1     A_f3f2,     A_f4f5,     A_g2g3          ;[15,3] 
||      ADD2    .S1     A_f3f2,     A_f4f5,     A_h0h1          ;[15,3] 
||      SWAP2   .L1     A_f1f0,     A_f0f1                      ;[15,3] 
||      ROTL    .M2     B_f6f7,     16,         B_f7f6          ;[ 6,4] 

  [!Bp] STDW    .D1T1   A_F7F6:A_F5F4,          *+A_io_ptr[13]  ;[34,1] 
||      PACK2   .S1     A_F3,       A_F2,       A_F3F2          ;[34,1] 
||      PACK2   .S2     B_F5,       B_F4F4,     B_F5F4          ;[25,2] 
||      SUB2    .D2     B_s1q1,     B_s0q0,     B_S0Q0          ;[16,3] 
||      DOTPRSU2.M2X    B_r0r1,     A_c2c6,     B_F2            ;[16,3] 
||      DOTPRSU2.M1     A_g2g3,     A_C4__,     A_q1_           ;[16,3] 
||      SUB2    .L1     A_f0f1,     A_f7f6,     A_h2h3          ;[16,3] 
||      SWAP2   .L2     B_f2f3,     B_f3f2                      ;[ 7,4] 

        PACKLH2 .S1X    A_F1,       B_F0F0,     A_F1F0          ;[35,1] 
||      DOTPRSU2.M2X    B_S0Q0,     A_c5c3,     B_F5            ;[17,3] 
||      DOTPRSU2.M1     A_h2h3,     A_C4__,     A_s1_           ;[17,3] 
||      ADD2    .L1     A_f0f1,     A_f7f6,     A_g0g1          ;[17,3] 
||      SUB2    .D2     B_f3f2,     B_f4f5,     B_g2g3          ;[ 8,4] 
||      ADD2    .L2     B_f3f2,     B_f4f5,     B_h0h1          ;[ 8,4] 
||      SUB2    .S2     B_f0f1,     B_f7f6,     B_h2h3          ;[ 8,4] 
||      LDDW    .D1T1   *+A_io_ptr  [1],        A_f7f6:A_f5f4   ;[ 8,4] 

  [!Bp] STDW    .D1T1   A_F3F2:A_F1F0,          *+A_io_ptr[12]  ;[36,1] 
||      SHR2    .S2X    A_F0F0_,    3,          B_F0F0          ;[27,2] 
||      DOTPRSU2.M1     A_r0r1,     A_c2c6,     A_F2            ;[27,2] 
||      SUB     .S1     A_h2h3,     A_g2g3,     A_q0            ;[18,3] 
||      ADD     .L1     A_h2h3,     A_g2g3,     A_s0            ;[18,3] 
||      ADD     .D2     B_h2h3,     B_g2g3,     B_s0            ;[ 9,4] 
||      DOTPRSU2.M2     B_g2g3,     B_C4__,     B_q1_           ;[ 9,4] 
||      ADD2    .L2     B_f0f1,     B_f7f6,     B_g0g1          ;[ 9,4] 

* ============================ PIPE LOOP EPILOG ============================ *
; Collapsed 2 epilog stages.
        DOTPNRSU2.M1    A_S1Q1,     A_c7c1,     A_F7            ;[28,4] 
||      PACK2   .L2     B_F7,       B_F6,       B_F7F6          ;[30,4] 
||      PACK2   .S2     B_F1,       B_F0F0,     B_F1F0          ;[30,4] 

        DOTPRSU2.M1     A_S1Q1,     A_c1c7,     A_F1            ;[29,4] 
||      LDW     .D2T1   *+B_SP[1],  A12                         ; get A12

        PACKLH2 .L1X    A_F5,       B_F4F4,     A_F5F4          ;[30,4] 
||      DOTPNRSU2.M1    A_S0Q0,     A_c3c5,     A_F3            ;[30,4] 
||      RET     .S2X    A_ret_sv
||      LDDW    .D2T1   *+B_SP[1],  A11:A10                     ; get A11,A10

        LDW     .D2T2   *++B_SP[4], B10                         ; get B10

        PACK2   .L1     A_F7,       A_F6,       A_F7F6          ;[32,4] 

        PACKLH2 .S1X    A_F1,       B_F0F0,     A_F1F0          ;[35,4] 

        PACK2   .L1     A_F3,       A_F2,       A_F3F2          ;[34,4] 
||      STDW    .D1T1   A_F7F6:A_F5F4,          *+A_io_ptr[ 9]  ;[34,4] 
||      STDW    .D2T2   B_F3F2:B_F1F0,          *+B_io_ptr[12]  ;[31,4] 

        STDW    .D1T1   A_F3F2:A_F1F0,          *+A_io_ptr[ 8]  ;[36,4] 
||      STDW    .D2T2   B_F7F6:B_F5F4,          *+B_io_ptr[13]  ;[32,4] 
* ========================== RETURN BRANCH OCCURS ========================= *

* ================ RELOCATED CODE (BRANCH TARGET ALIGNMENT) =============== *
reloc:
        SUB2    .D2     B_f3f2,     B_f4f5,     B_g2g3          ;[ 8,1] 
||      ADD2    .L2     B_f3f2,     B_f4f5,     B_h0h1          ;[ 8,1] 
||      SUB2    .S2X    B_f0f1,     Axf7f6,     B_h2h3          ;[ 8,1] 
||      LDW     .D1T1   *--A_io_ptr[14],        A_f5f4          ;
||      ROTL    .M1     A_c1c7,     16,         A_c7c1
||      PACK2   .S1     A_dc_rnd,   A_dc_rnd,   A_dc_rnd        ; 0x00040004

        ADD     .S2     B_h2h3,     B_g2g3,     B_s0            ;[ 9,1] 
||      DOTPRSU2.M2     B_g2g3,     B_C4__,     B_q1_           ;[ 9,1] 
||      ADD2    .L2X    B_f0f1,     Axf7f6,     B_g0g1          ;[ 9,1] 
||      ROTL    .M1     A_c6c2,     16,         A_c2c6
||      PACK2   .L1X    A_F6,       B_F6,       A_f7f6          ;[35,4] 
||      STW     .D2T1   A_F2F2,     *B_io_ptr++[ 9]             ;[37,4] 
||      ADDK    .S1     -8,         A_io_ptr
* ========================== H_LOOP BRANCH OCCURS ========================= *


* ========================================================================= *
*   End of file:  fdct_8x8_h.asm                                            *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
