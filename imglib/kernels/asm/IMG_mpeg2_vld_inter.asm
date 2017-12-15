
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
*   TEXAS INSTRUMENTS, INC.                                                 *
*                                                                           *
*   NAME                                                                    *
*       mpeg2_vld_inter                                                     *
*                                                                           *
*   PLATFORM                                                                *
*       C6400                                                               *
*                                                                           *
*   DESCRIPTION                                                             * 
*       This routine takes a bitstream of an MPEG-2 non-intra coded         * 
*       macroblock and returns the decoded IDCT coefficients. The routine   * 
*       is implemented as specified in the MPEG-2 standard text (ISO/IEC    * 
*       13818-2). The routine checks the coded block pattern (cbp),         * 
*       performs coefficient decoding inlcuding, variable length decode,    * 
*       run-length expansion, inverse zigzag, dequantization, saturation    * 
*       and mismatch control.                                               * 
*                                                                           * 
*   USAGE                                                                   * 
*       This routine is C callable, and has the following C prototype:      * 
*                                                                           * 
*       void mpeg2_vld_inter                                                * 
*       (                                                                   * 
*           const short    *restrict Wptr,                                  * 
*           short          *restrict outi,                                  * 
*           IMG_mpeg2_vld  *restrict Mpeg2v,                                * 
*           int            mode_12Q4,                                       * 
*           int            num_blocks,                                      * 
*           int            bsbuf_words                                      * 
*       );                                                                  * 
*                                                                           * 
*         Wptr:   Pointer to array that contains quantization matrix. The   * 
*                 elements of the quantization matrix in *Wptr must be      * 
*                 ordered according to the scan pattern used (zigzag or     * 
*                 alternate scan). Video format 4:2:0 requires one          * 
*                 quantization matrix (64 array elements).  For formats     * 
*                 4:2:2 and 4:4:4 two quantization matrices (one for luma   * 
*                 and one for chroma) must specified in the array (128      * 
*                 array elements).                                          * 
*                                                                           * 
*         outi:   Pointer to the IDCT coefficients output array             * 
*                 (6*64 elements), elements must be set to zero prior to    * 
*                 function call.                                            * 
*                                                                           * 
*         Mpeg2v: Pointer to the context object containing the coding       * 
*                 parameters of the MB to be decoded and the current state  * 
*                 of the bitstream buffer. The structure is described       * 
*                 below.                                                    * 
*                                                                           * 
*      mode_12Q4: 0: Coefficients are returned in normal 16-bit integer     * 
*                 format.                                                   * 
*                 Otherwise: Coefficients are returned in 12Q4 format       * 
*                 (normal 16-bit integer format left shifted by 4). This    * 
*                 mode is useful for directly passing the coefficients      * 
*                 into the IMG_idct_8x8 routine.                            * 
*                                                                           * 
*     num_blocks: Number of blocks that the MB contains. Valid values are   * 
*                 6 for 4:2:0, 8 for 4:2:2 and 12 for 4:4:4 format.         * 
*                                                                           * 
*    bsbuf_words: Size of bitstream buffer in words. Must be a power of 2.  * 
*                 Bitstream buffer must be aligned at an address boundary   * 
*                 equal to its size in bytes (bitstream buffer is           * 
*                 addressed circularly by this routine.)                    * 
*                                                                           * 
*       The structure Mpeg2v is defined as follows:                         * 
*                                                                           * 
*C          #ifndef IMG_MPEG2_VLD_STRUCT_                                   * 
*C          #define IMG_MPEG2_VLD_STRUCT_ 1                                 * 
*C                                                                          * 
*C          typedef struct {                                                * 
*C            unsigned int  *bsbuf;      // pointer to bitstream buffer     * 
*C            unsigned int  next_wptr;   // next word to read from buffer   * 
*C            unsigned int  bptr;        // bit position within word        * 
*C            unsigned int  word1;       // word aligned buffer             * 
*C            unsigned int  word2;       // word aligned buffer             * 
*C            unsigned int  top0;        // top 32 bits of bitstream        * 
*C            unsigned int  top1;        // next 32 bits of bitstream       * 
*C            const unsigned char *scan; // inverse zigzag scan matrix      * 
*C            unsigned int  intravlc;    // intra_vlc_format                * 
*C            unsigned int  quant_scale; // quant_scale                     * 
*C            unsigned int  dc_prec;     // intra_dc_precision              * 
*C            unsigned int  cbp;         // coded_block_pattern             * 
*C            unsigned int  fault;       // fault condition (returned)      * 
*C            unsigned int  reserved;    // reserved                        * 
*C          } IMG_mpeg2_vld;                                                * 
*C                                                                          * 
*C          #endif                                                          * 
*                                                                           * 
*       The Mpeg2v variables should  have a fixed layout since they are     * 
*       accessed by this routine. If the layout is changed, the             * 
*       corresponding changes have to be made in the assembly code too.     * 
*                                                                           * 
*       The routine sets the fault flag Mpeg2v.fault to 1 if an invalid     * 
*       VLC code was encountered or the total run went beyond 63. In        * 
*       theses cases the decoder has to resynchronize.                      * 
*                                                                           * 
*       The required lookup tables for this routine are provided in         * 
*       IMGLIB and are linked in automatically when linking against         * 
*       IMGLIB.                                                             * 
*                                                                           * 
*       Before calling the routine the bitstream varaibles in Mpeg2v        * 
*       have to be initialized. If bsbuf is a circular buffer and bsptr     * 
*       contains the number of bits in the buffer that already have         * 
*       been consumed, then next_wptr, bptr, word1, word2, top0 and         * 
*       top1 are initialized as follows:                                    * 
*                                                                           * 
*       1. nextwptr: bsptr may not be a multiple of 32, therefore obtain    * 
*       the next lower multiple of 32.                                      * 
*                                                                           * 
*           next_wptr = (bsptr >> 5);                                       * 
*                                                                           * 
*       2. bptr: bptr is the bit pointer which points to the current        * 
*       bit WITHIN the word pointed to by next_wptr.                        * 
*                                                                           * 
*           bptr = bsptr & 31;                                              * 
*           bptr_cmpl = 32 - bptr;                                          * 
*                                                                           * 
*       3. word1 and word2: read next 3 words from the bitstream buffer     * 
*       (word0 is a temporary variable). bsbuf_words is the size of the     * 
*       bitstream buffer in words.                                          * 
*                                                                           * 
*           word0 = bsbuf[next_wptr];                                       * 
*           next_wptr = (next_wptr + 1) & (bsbuf_words-1);                  * 
*                                                                           * 
*           word1 = bsbuf[next_wptr];                                       * 
*           next_wptr = (next_wptr + 1) & (bsbuf_words-1);                  * 
*                                                                           * 
*           word2 = bsbuf[next_wptr];                                       * 
*           next_wptr = (next_wptr + 1) & (bsbuf_words-1);                  * 
*                                                                           * 
*       4. top0 and top1: Shift words word0, word1, word2 by bptr to the    * 
*       left so that the current bit becomes the MSB in word0. word0 can    * 
*       simply be shifted by bptr; the then empty LSBs of word0 have to be  * 
*       filled with the MSBs of word1. To do that the required MSBs are     * 
*       brought into the position of empty LSBs of word0 by shifting word1  * 
*       to the right by (32-bptr). The result is then copied into word0 by  * 
*       an addition. Rather than overwriting word0, top0 is used to hold    * 
*       the new bit aligned word. The same procedure is used to obtain      * 
*       top1. top0 and top1 contain the next 64 bits of the bitstream.      * 
*                                                                           * 
*           s1 = word0 << bptr;                                             * 
*           s2 = word1 >> bptr_cmpl;  /* unsigned right-shift */            * 
*           top0 = s1 + s2;                                                 * 
*                                                                           * 
*           s3 = word1 << bptr;                                             * 
*           s4 = word2 >> bptr_cmpl;  /* unsigned right-shift */            * 
*           top1 = s3 + s4;                                                 * 
*                                                                           * 
*       Note that the routine returns the updated state of the bitstream    * 
*       buffer variables, top0, top1, word1, word2, bptr and next_wptr. If  * 
*       all other functions which access the bitstream in a decoder system  * 
*       maintain the buffer variables in the same way, then the above       * 
*       initialization procedure has to be performed only once at the       * 
*       beginning.                                                          * 
*                                                                           * 
*                                                                           * 
*   TECHNIQUES                                                              * 
*       The instruction NORM is used to detect the number of leading zeros  * 
*       or ones in a code word. This value together with additional bits    * 
*       extracted from the codeword is then used as an index into look-up   * 
*       tables to determine the length, run, level and sign. Escape code    * 
*       sequences are directly extracted from the code word.                * 
*                                                                           * 
*   ASSUMPTIONS                                                             * 
*       The bitstream must be stored in memory in 32-bit words which are    * 
*       in little endian byte order.                                        * 
*                                                                           * 
*       Wptr is allowed to overrun once (to detect total run overrun), so   * 
*       maximum overrun that can occur is 66 (Error mark). Therefore,       * 
*       in memory 66+1 halfwords behind the weighting matrix should be      * 
*       valid (e.g. peripherals). No memory is overwritten,                 * 
*       only loads occurr.                                                  * 
*                                                                           * 
*       Note that the AMR register is set to zero on exit.                  * 
*                                                                           * 
*   NOTES                                                                   * 
*       This code is little ENDIAN.                                         * 
*       This code is interrupt-tolerant but not interruptible.              * 
*                                                                           * 
*   MEMORY NOTES                                                            * 
*       No bank conflicts                                                   * 
*                                                                           * 
*   CYCLES                                                                  * 
*       10 * (S - CB) + 37 * CB + 15 * NCB + 34                             * 
*       where S:   Number of symbols in MB, CB: Number of coded blocks,     * 
*             NCB: Number of not-coded blocks, and CB+NCB=6                 * 
*                                                                           * 
*   CODE SIZE                                                               * 
*       1248 bytes                                                          * 
*                                                                           * 
*   MEMORY REQUIREMENTS                                                     * 
*       1792 bytes for the lookup tables                                    * 
*       (can be shared with mpeg2_vld_intra)                                * 
*                                                                           * 
*                                                                           * 
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *

* ===================== SYMBOLIC REGISTER ASSIGNMENTS ====================== *
        .asg            A0,         A_neg
        .asg            A1,         A_bptr1
        .asg            A1,         A_qw
        .asg            A1,         A_test1
        .asg            A1,         A_test2
        .asg            A16,        A_len_c
        .asg            A17,        A_bptr
        .asg            A18,        A_len_tbl_adr
        .asg            A19,        A_const31
        .asg            A2,         A_top0l
        .asg            A20,        A_const32
        .asg            A22,        A_const36
        .asg            A23,        A_qscl
        .asg            A24,        A_level4
        .asg            A24,        A_t2
        .asg            A24,        A_top0_bk
        .asg            A25,        A_empty
        .asg            A25,        A_len
        .asg            A25,        A_level_f_
        .asg            A26,        A_nrm
        .asg            A26,        A_t1l
        .asg            A26,        A_t4l
        .asg            A27,        A_t1h
        .asg            A27,        A_t4h
        .asg            A3,         A_top0h
        .asg            A4,         A_ptop0l
        .asg            A5,         A_level_f
        .asg            A5,         A_level5
        .asg            A5,         A_ptop0h
        .asg            A6,         A_W
        .asg            A7,         A_top1
        .asg            A8,         A_word1
        .asg            A9,         A_t3
        .asg            A9,         A_t7
        .asg            A9,         A_t8
        .asg            B0,         B_eob
        .asg            B1,         B_run
        .asg            B1,         B_test3
        .asg            B1,         B_12Q4      ; 12Q4 MERGE
        .asg            B16,        B_level2
        .asg            B16,        B_rld_left
        .asg            B17,        B_bptr_cmpl
        .asg            B17,        B_t14
        .asg            B17,        B_t9
        .asg            B19,        B_word2
        .asg            B20,        B_Wptr_end
        .asg            B21,        B_Zptr
        .asg            B22,        B_outi
        .asg            B23,        B_sum
        .asg            B24,        B_top0_bk
        .asg            B26,        B_level3
        .asg            B3,         B_const63
        .asg            B4,         B_rld_table_adr
        .asg            B5,         B_const32
        .asg            B6,         B_rld_table_adr_1
        .asg            B7,         B_bsbuf_circ
        .asg            B8,         B_Wptr
        .asg            B9,         B_level
        .asg            B9,         B_t12
        .asg            B9,         B_t13
        .asg            B9,         B_t15
        .asg            B9,         B_t16
        .asg            A11,        A_outi      ; 12Q4   
        .asg            A12,        A_cnum      ; 12Q4
        .asg            A13,        A_const16   ; 12Q4
        .asg            B18,        B_constFFF0 ; 12Q4
  
* ========================================================================= *
        .sect ".text:hand"
        .if     __TI_EABI__
          	   .asg    IMG_mpeg2_vld_inter,  _IMG_mpeg2_vld_inter
                   .asg    IMG_len_tbl0,  _IMG_len_tbl0
		   .asg    IMG_rld_table0,  _IMG_rld_table0
         .endif
        .global _IMG_mpeg2_vld_inter

        .global _IMG_len_tbl0 
        .global _IMG_rld_table0

; Mpeg2v structure:
BSBUF_M2OFF      .set   0x0
NEXTWPTR_M2OFF   .set   0x1
BPTR_M2OFF       .set   0x2
WORD1_M2OFF      .set   0x3
WORD2_M2OFF      .set   0x4
TOP0_M2OFF       .set   0x5
TOP1_M2OFF       .set   0x6
ZPTR_M2OFF       .set   0x7
QSCL_M2OFF       .set   0x9
CBP_M2OFF        .set   0xB
FAULT_M2OFF      .set   0xC

_IMG_mpeg2_vld_inter:
; parameters: B_Wptr, B_outi, A_Mpeg2v, B_12Q4, A_num_blocks, B_bsbuf_words
;             A4,     B4,     A6,       B6,     A8,           B8

* ========================================================================= *
*  Setup
* ========================================================================= *
        .asg            B15,        B_SP        ; Stack pointer, B datapath
        .asg            A16,        A_SP        ; Stack pointer, A datapath
        .asg            B0,         B_csr       ; CSR's value
        .asg            B1,         B_no_gie    ; CSR w/ GIE bit cleared
        .asg            B3,         B_ret       ; Return address
        .asg            A29,        A_Mpeg2v
        .asg            B18,        B_Mpeg2v
        .asg            B2,         B_cnt
        .asg            A10,        A_amr_arg            ; AMR arg
        .asg            B9,         B_amr_arg            ; AMR arg

        STW     .D2T1   A10,        *B_SP--[10]           ; RWD, MERGE, 2 W-mat
||      MVC     .S2     CSR,        B_csr                ; Get CSR's state
||      MV      .L2     B4,         B_outi  
||      MV      .L1     A6,         A_Mpeg2v
||      MV      .S1X    B8,         A_amr_arg            ; AMR arg

        STW     .D2T2   B_csr,      *+B_SP[1]            ; Save CSR
||      AND     .L2     B_csr,      -2,         B_no_gie ; Clear GIE
||      MV      .S2X    A4,         B_Wptr  
||      MV      .D1X    B_SP,       A_SP                 ; 12Q4 MERGE
||      LMBD    .L1     1,          A_amr_arg,  A_amr_arg; AMR arg
||      MVK     .S1     32,         A_const32            ; AMR arg

        STW     .D2T2   B_ret,      *+B_SP[2]            ; Save return addr.
||      STW     .D1T1   A14,        *+A_SP[6]            ; MERGE
||      MV      .L2X    A6,         B_Mpeg2v
||      MVC     .S2     B_no_gie,   CSR                  ; Disable ints.
||      SUB     .L1     A_const32,  A_amr_arg,  A_amr_arg; AMR arg
; ===== Interrupts masked here =====  

* ========================================================================= *
*  Get bitstream info
*  Setup circuar bitstream buffer
*  Load table addresses and constants
*  Block loop setup
* ========================================================================= *
        .asg     B31,    B_bsbuf
        .asg     B29,    B_next_wptr 
        .asg     B27,    B_cbp
        .asg     B0,     B0_amr_config
        .asg     A21,    A_const1
        .asg     A9,     A_tbs1
        .asg     A4,     A_tbs2
        .asg     B17,    B_tbs3
        .asg     B3,     B_const126
        .asg     B3,     B_const128
        .asg     A14,    A_constSHR                             ; 12Q4 MERGE

        LDW     .D2T2    *+B_Mpeg2v[BSBUF_M2OFF],      B_bsbuf
||      LDW     .D1T1    *+A_Mpeg2v[TOP0_M2OFF],       A_top0_bk 
||      MVK     .S2      128,          B_const128           
||      MV      .L2      B6,           B_12Q4                   ; 12Q4 MERGE

        LDW     .D2T2    *+B_Mpeg2v[NEXTWPTR_M2OFF],   B_next_wptr
||      LDW     .D1T1    *+A_Mpeg2v[TOP1_M2OFF],       A_top1 
||      ADD     .L2      B_Wptr,       B_const128,     B_Wptr_end
||[!B_12Q4]MVK  .S1      20,           A_constSHR             ; non-12Q4 MERGE
||      SHL     .S2X     A_amr_arg,    16,             B_amr_arg; AMR arg
    
        LDW     .D1T1    *+A_Mpeg2v[BPTR_M2OFF],       A_bptr
||      STW     .D2T2    B_Wptr,         *+B_SP[7]              ; 2 W-mat
||      MV      .L2X     A8,             B_cnt                  ; 2 W-mat
||      SET     .S2      B_amr_arg, 14, 14,     B_amr_arg          ; AMR arg
    
        LDW     .D1T1    *+A_Mpeg2v[WORD1_M2OFF],      A_word1
||      LDW     .D2T2    *+B_Mpeg2v[WORD2_M2OFF],      B_word2
||      MVC     .S2      B_amr_arg,            AMR                 ; AMR arg
||      MVK     .S1      31,            A_const31
    
        LDW     .D1T1    *+A_Mpeg2v[QSCL_M2OFF],       A_qscl
||      LDW     .D2T2    *+B_Mpeg2v[CBP_M2OFF],        B_cbp
||[B_12Q4]MVK   .S1      16,           A_constSHR               ; 12Q4 MERGE
; B_constFFF0 and B_Mpeg2v share the same register

* ========================================================================= *
*  Setup bitstream pointers: top0h:top0l, top1 contain top bitstream
* ========================================================================= *
        .asg    B25,    B_word2_bk               
        .asg    A28,    A_word1_bk              
        .asg    A10,    A_word1_rw      ; RWD
        .asg    A21,    A_word1_rw_bk   ; RWD
        .asg    A31,    A_top0h_bk               
        .asg    A30,    A_top0l_bk               
        .asg    B28,    B_bptr_bk              
        .asg    B30,    B_bsbuf_circ_bk

        SHL     .S1      A_top0_bk,     8,          A_tbs1
||      STW     .D2T1    A11,           *+B_SP[3]                   
||[B_12Q4]MVKL  .S2      0xFFF0,        B_constFFF0            ; 12Q4 MERGE
   
        SHRU    .S1      A_top1,        24,         A_tbs2
||      STW     .D2T1    A12,           *+B_SP[4]                    
||[!B_12Q4]MVKL .S2      0xFFFF,        B_constFFF0           ; non-12Q4 MERGE
        
        ADD     .L1      A_tbs1,        A_tbs2,     A_top0l_bk
||      ADD     .S1      A_bptr,        8,          A_bptr1
||      STW     .D2T1    A13,           *+B_SP[5]                     
        
        CMPGT   .L1      A_bptr1,       A_const31,  A_test2
||      AND     .S1      A_bptr1,       A_const31,  A_bptr
||      MVK     .S2      32,            B_const32
||      ADDAW   .D2      B_bsbuf,       B_next_wptr,B_bsbuf_circ  
            
  [A_test2]MV   .S1      A_word1,                   A_word1_rw  ; RWD
||[A_test2]MV   .L1X     B_word2,                   A_word1
||[A_test2]LDW  .D2T2    *B_bsbuf_circ++,           B_word2
||      SUB     .S2      B_const32,     A_bptr,     B_bptr_cmpl

        MVKL    .S1      _IMG_len_tbl0,     A_len_tbl_adr 
||      MVKL    .S2      _IMG_rld_table0,   B_rld_table_adr
||      MV      .L2X     A_bptr,        B_bptr_bk
||      STW     .D2T2    B_cnt,         *+B_SP[8]               ; 2 W-mat

        MVKH    .S1      _IMG_len_tbl0,     A_len_tbl_adr
||      MVKH    .S2      _IMG_rld_table0,   B_rld_table_adr
        
 [B_12Q4]MVK   .S1      16,            A_const16               ; 12Q4

 [!B_12Q4]MVK   .S1      1,             A_const16              ; non-12Q4
||      SHRU    .S2      B_word2,       B_bptr_cmpl,B_tbs3     ; xp-stall removed
        
        SHL     .S1      A_word1,       A_bptr,     A_tbs1    
            
        ADD     .L1X     A_tbs1,        B_tbs3,     A_top1       
||      SHRU    .S1      A_top0_bk,     24,         A_top0h_bk
||      MV      .D1      A_word1,       A_word1_bk
||      MV      .D2      B_word2,       B_word2_bk
||      MV      .L2      B_bsbuf_circ,  B_bsbuf_circ_bk


block_loop:
* ------------------------------------------------------------------------- *
*  check cbp, etc.
* ------------------------------------------------------------------------- *
        .asg     B17,     B_cbp_mask
        .asg     B0,      B_coded  
        .asg     A5,      A_last_coeff
        .asg     A2,      A2_odd   
        .asg    B31,      B_run_bk
        .asg    B26,      B_num_blocks                        ; 2 W-mat

; if error occurred, before branching to exit the next 2 cycles are still executed 
            SUB   .S2     B_cnt,        1,        B_cnt       ; cbp, cnt--
||          ZERO  .L2     B_sum
;||         ZERO  .D2     B_run_bk                            ; not coded; bug fix 6/21/05: was zeroing bsbuf 
||          ZERO  .L1     A2_odd                              ; not coded
||          MVK   .S1     1,            A_const1              ; cbp

            SHL   .S2X    A_const1,     B_cnt,    B_cbp_mask  ; cbp
||          MV    .L2     B_Wptr_end,   B_Wptr                ; not coded
||          MVK   .S1     0,            A_last_coeff          ; not coded

            AND   .D2     B_cbp_mask,   B_cbp,    B_coded     ; cbp
||          MVK   .S2     126,          B_const126            ; const
||          ZERO  .L2     B_run_bk                            ; not coded; bug fix 6/21/05

  [!B_coded]B     .S1     mismatch                            ; not coded
||[!B_coded]ADD   .L2     B_outi,       B_const126, B_outi    ; not coded
||[B_coded]LDW  .D2T2   *+B_SP[8],      B_num_blocks          ; 2 W-mat
 
* =========================== PIPE LOOP PROLOG ============================ *
        .asg     A0,      A_tm
        .asg     B0,      B_tm_neg

; the added lines below calculate cc which is required for weighting
; matrix selection in 4:2:2 and 4:4:4 mode
; the following additional registers are required: B_block, B_flag, B_cc
        .asg    B31,      B_block 
        .asg    B1,       B_cc    
        .asg    B0,       B_flag  

        NORM    .L1     A_top0h_bk:A_top0l_bk,  A_nrm           ;[ 1,1] 
||      SHRU    .S1     A_top0h_bk,     7,      A_tm            ;table mod

        MPY     .M1     A_nrm,      -16,        A_t2            ;[ 2,1] 
||      SHL     .S1     A_top0h_bk:A_top0l_bk,  A_nrm, A_t1h:A_t1l;[ 2,1] 

        MVK     .S1     36,             A_const36               ;const

        SHRU    .S1     A_t1h:A_t1l,    A_const36,  A_t4h:A_t4l ;[ 4,1]
||      SUB     .L1     A_len_tbl_adr,  A_t2,       A_t3        ;[ 4,1] 
||[B_coded]LDW  .D2T2   *+B_SP[7],      B_Wptr             ;get W-mat base adr

  [!A_tm]LDBU   .D1T1   *A_t3[A_t4l],   A_len                   ;[ 5,1]
||[B_coded] SUB .L2     B_num_blocks,   1,          B_num_blocks;2 W-mat
; branch occurs if not coded MB

        SUB     .S2     B_num_blocks,   B_cnt,      B_block    ;cc for 2 W-mat
||      CMPGT   .L2     B_num_blocks,   6,          B_flag     
;prevent 2 W-mat if 4:2:0

        SHRU    .S1     A_top0h_bk:A_top0l_bk, 8, A_empty:A_top0_bk;[ 8,1] 
||[B_flag]CMPGT .L2     B_block,        3,          B_flag     ;cc for 2 W-mat
||      ZERO    .S2     B_cc                                   ;cc for 2 W-mat 

  [A_tm]MVK     .L1     2,          A_len                      ;table mod
||[B_flag] AND  .D2     B_block,        1,          B_cc       ;cc for 2 W-mat  

        MV      .L1X    B_bptr_bk,  A_bptr                     ;restore
||      MVK     .S2     128,         B_const128                ;const
||[B_flag] ADD  .D2     B_cc,           1,          B_cc       ;cc for 2 W-mat    

        SUB     .S2X    A_len,      5,          B_rld_left      ;[10,1] 
||      CMPLT   .L2X    A_len,      5,          B_test3         ;[10,1] 
||      ADD     .L1     A_bptr,     A_len,      A_bptr1         ;[10,1] 
||      SHL     .S1     A_top0h_bk:A_top0l_bk,  A_len, A_ptop0h:A_ptop0l;[10,1] 
||[!A_tm]SUB    .D1     A_const32,  A_len,      A_len_c         ;[10,1] 
||[B_cc]ADD     .D2     B_Wptr,     B_const128, B_Wptr          
;if cc!=0 select 2nd W-mat

  [B_test3]MPY  .M2     B_rld_left, 0,          B_rld_left      ;[11,1] 
||      MV      .L2X    A_top0_bk,  B_top0_bk                   ;[11,1] 
||      AND     .S1     A_const31,  A_bptr1,    A_bptr          ;[11,1] 
||      MV      .D1     A_ptop0h,   A_top0h                     ;[11,1] 
||      NORM    .L1     A_ptop0h:A_ptop0l,      A_nrm           ;[ 1,2] 

        CMPGT   .L1     A_bptr1,    A_const31,  A_test2         ;[12,1] 
||      MPY     .M1     A_nrm,      -16,        A_t2            ;[ 2,2] 
||      SHL     .S1     A_ptop0h:A_ptop0l, A_nrm, A_t1h:A_t1l   ;[ 2,2] 
||      ADD     .L2     B_Wptr,      B_const128, B_Wptr_end     ;reset

        SHL     .S2     B_top0_bk,  B_rld_left, B_t13           ;[13,1]
||      MPY     .M2X    B_const32,  A_len,      B_t12           ;[13,1] 
||[A_tm]MVK     .S1     30,                     A_len_c         ;table mod
||      MV      .L1     A_word1_bk,  A_word1                    ;restore
||      MV      .L2     B_word2_bk,  B_word2                    ;restore
||      MV      .D2     B_bsbuf_circ_bk, B_bsbuf_circ           ;restore

        SHRU    .S2     B_t13,      27,         B_t14           ;[14,1]  
||[ A_test2]LDW .D2T2   *B_bsbuf_circ++,        B_word2         ;[14,1] 
||      SHRU    .S1     A_t1h:A_t1l,            A_const36,  A_t4h:A_t4l ;[ 4,2]
||      SUB     .L1     A_len_tbl_adr,          A_t2,       A_t3;[ 4,2] 

        ADD     .L2     B_t14,      B_t12,      B_t15           ;[15,1] 
||      SUB     .S2X    B_const32,  A_bptr,     B_bptr_cmpl     ;[15,1] 
||[ A_test2]MV  .L1X    B_word2,    A_word1                     ;[15,1] 
|| [A_test2]MV  .S1     A_word1,    A_word1_rw                  ; RWD
||      LDBU    .D1T1   *A_t3[A_t4l],           A_len           ;[ 5,2]
||      ZERO    .D2     B_tm_neg                                ;table mod

        ADD     .L2     B_t15,      B_t15,      B_t16           ;[16,1] 
||[!A_tm]SUB    .D1     A_len,      24,         A_test1         ;[16,1]
||[A_tm]ZERO    .L1     A_test1                                 ;table mod
||      SHRU    .S1     A_top1,     A_len_c,    A_t7            ;[16,1] 
||[A_tm]EXTU    .S2     B_top0_bk,  1, 31,      B_tm_neg        ;table mod

  [ A_test1]LDB .D2T2   *B_rld_table_adr[B_t16],B_level         ;[17,1] 
||      ADD     .D1     A_ptop0l,   A_t7,       A_top0l         ;[17,1] 
||      ADD     .L2     B_rld_table_adr,     1, B_rld_table_adr_1;const
||[A_tm]MVK     .S2     1,          B_level                     ;table mod

  [ A_test1]LDB .D2T2   *B_rld_table_adr_1[B_t16], B_run        ;[18,1]
||[!A_tm]EXT    .S2     B_top0_bk,  12, 20,    B_level          ;[18,1] 
||      SHRU    .S1     A_top0h:A_top0l, 8,    A_empty:A_top0_bk;[ 8,2] 
||[B_tm_neg]NEG .L2     B_level,    B_level                     ;table mod

        SHRU    .S2     B_word2,    B_bptr_cmpl,B_t9            ;[19,1] 
||      SHL     .S1     A_word1,    A_bptr,     A_t8            ;[19,1] 

        SUB     .S2X    A_len,      5,          B_rld_left      ;[10,2] 
||      CMPLT   .L2X    A_len,      5,          B_test3         ;[10,2] 
||      ADD     .L1     A_bptr,     A_len,      A_bptr1         ;[10,2] 
||      SHL     .S1     A_top0h:A_top0l, A_len, A_ptop0h:A_ptop0l;[10,2] 
||      SUB     .D1     A_const32,  A_len,      A_len_c         ;[10,2] 

  [!A_tm]EXTU   .S2     B_top0_bk,  6,  26,     B_run           ;[21,1] 
||[A_tm] ZERO   .D2     B_run                                   ;table mod
||[B_test3]MPY  .M2     B_rld_left, 0,          B_rld_left      ;[11,2] 
||      MV      .L2X    A_top0_bk,  B_top0_bk                   ;[11,2] 
||      AND     .S1     A_const31,  A_bptr1,    A_bptr          ;[11,2] 
||      MV      .D1     A_ptop0h,   A_top0h                     ;[11,2] 
||      NORM    .L1     A_ptop0h:A_ptop0l,      A_nrm           ;[ 1,3]

        MPY     .M2     B_level,    2,          B_level2        ;[22,1] 
||      CMPGT   .L1     A_bptr1,    A_const31,  A_test2         ;[12,2] 
||      MPY     .M1     A_nrm,      -16,        A_t2            ;[ 2,3] 
||      SHL     .S1     A_ptop0h:A_ptop0l, A_nrm, A_t1h:A_t1l   ;[ 2,3] 
||      LDW     .D1T2   *+A_Mpeg2v[ZPTR_M2OFF], B_Zptr          ;reset
||      MVK     .S2     63,         B_const63                   ;const

        LDH     .D2T1   *++B_Wptr[B_run],       A_W             ;[23,1] 
||      CMPLT   .L1X    B_level,    0,          A_neg           ;[23,1] 
||      SHL     .S2     B_top0_bk,  B_rld_left, B_t13           ;[13,2]
||      MPY     .M2X    B_const32,  A_len,      B_t12           ;[13,2] 

        ADD     .L2     B_Wptr,     2,          B_Wptr          ;[24,1] 
||      ADD     .D1X    A_t8,       B_t9,       A_top1          ;[24,1] 
||      SHRU    .S2     B_t13,      27,         B_t14           ;[14,2] 
||[ A_test2]LDW .D2T2   *B_bsbuf_circ++,        B_word2         ;[14,2] 
||      SHRU    .S1     A_t1h:A_t1l,            A_const36,  A_t4h:A_t4l;[ 4,3] 
||      SUB     .L1     A_len_tbl_adr,          A_t2,       A_t3;[ 4,3] 

  [ A_neg]SUB   .D2     B_level2,   1,          B_level3        ;[25,1] 
||      ADD     .L2     B_t14,      B_t12,      B_t15           ;[15,2] 
||      SUB     .S2X    B_const32,  A_bptr,     B_bptr_cmpl     ;[15,2] 
||[ A_test2]MV  .L1X    B_word2,    A_word1                     ;[15,2] 
|| [A_test2]MV  .S1     A_word1,    A_word1_rw                  ; RWD
||      LDBU    .D1T1   *A_t3[A_t4l],           A_len           ;[ 5,3]

  [!A_neg]ADD   .L2     B_level2,   1,          B_level3        ;[26,1] 
||      ADD     .S2     B_t15,      B_t15,      B_t16           ;[16,2]
||      SUB     .D1     A_len,      24,         A_test1         ;[16,2]
||      SHRU    .S1     A_top1,     A_len_c,    A_t7            ;[16,2] 

        CMPGT   .L2     B_run,      B_const63,  B_eob           ;[27,1] 
||[ A_test1]LDB .D2T2   *B_rld_table_adr[B_t16],B_level         ;[17,2] 
||      ADD     .D1     A_ptop0l,   A_t7,       A_top0l         ;[17,2] 
||      MV      .L1X    B_outi,     A_outi                      ; 12Q4

* =========================== PIPE LOOP KERNEL ============================ *
        .asg    A2,     A2_top0l 

loop:
        MPY     .M1     A_qscl,     A_W,        A_qw            ;[28,1] 
||[!B_eob]CMPGT .L2     B_Wptr,     B_Wptr_end, B_eob           ;[28,1] 
||[A_test1]LDB  .D2T2   *B_rld_table_adr_1[B_t16],      B_run   ;[18,2] 
||      EXT     .S2     B_top0_bk,  12, 20,    B_level          ;[18,2] 
||      SHRU    .S1     A_top0h:A_top0l, 8,    A_empty:A_top0_bk;[ 8,3] 
||[B_eob]MPY    .M2     0,          B_Wptr,     B_Wptr          ;err det

        LDB     .D2T1   *++B_Zptr[B_run],       A_cnum          ;[29,1]     
||      SHRU    .S2     B_word2,    B_bptr_cmpl,B_t9            ;[19,2] 
||      SHL     .S1     A_word1,    A_bptr,     A_t8            ;[19,2] 
||[!B_eob]MV    .L1     A_top0h:A_top0l, A_top0h_bk:A_top0l_bk  ;preserve
||[B_eob]ADD    .L2     B_outi,     B_const63,  B_outi          ;mismatch
||[!B_eob]MPY   .M2X    1,          A_bptr,     B_bptr_bk       ;preserve

        ADD     .D2     B_Zptr,     1,          B_Zptr          ;[30,1] 
||      MPY     .M1X    A_qw,       B_level3,   A_level4        ;[30,1] 
||      SUB     .S2X    A_len,      5,          B_rld_left      ;[10,3] 
||      CMPLT   .L2X    A_len,      5,          B_test3         ;[10,3]
||      ADD     .L1     A_bptr,     A_len,      A_bptr1         ;[10,3] 
||      SHL     .S1     A_top0h:A_top0l, A_len, A_ptop0h:A_ptop0l;[10,3] 
||      SUB     .D1     A_const32,  A_len,      A_len_c         ;[10,3] 
||[B_eob]MPY    .M2     1,          B_run,      B_run_bk        ;preserve

        EXTU    .S2     B_top0_bk,  6,  26,     B_run           ;[21,2] 
||[B_test3]MPY  .M2     B_rld_left, 0,          B_rld_left      ;[11,3] 
||      MV      .L2X    A_top0_bk,  B_top0_bk                   ;[11,3] 
||      AND     .S1     A_const31,  A_bptr1,    A_bptr          ;[11,3] 
||      MV      .D1     A_ptop0h,   A_top0h                     ;[11,3] 
||      NORM    .L1     A_ptop0h:A_ptop0l,      A_nrm           ;[ 1,4] 
||[B_eob]ADD    .D2     B_outi,     B_const63,  B_outi          ;mismatch

  [!B_eob]B     .S2     loop                                    ;[32,1] 
||[ A_neg]ADD   .D1     A_level4,   A_const31,  A_level4        ;[32,1] 
||      MPY     .M2     B_level,    2,          B_level2        ;[22,2] 
||      CMPGT   .L1     A_bptr1,    A_const31,  A_test2         ;[12,3] 
||      MPY     .M1     A_nrm,      -16,        A_t2            ;[ 2,4] 
||      SHL     .S1     A_ptop0h:A_ptop0l, A_nrm, A_t1h:A_t1l   ;[ 2,4] 
||[!B_eob]MV    .L2     B_bsbuf_circ,      B_bsbuf_circ_bk      ;preserve
||[B_eob]LDH    .D2T1   *B_outi,    A_last_coeff                ;mismatch

        SSHL    .S1     A_level4,   15,         A_level5        ;[33,1] 
||[!B_eob]LDH   .D2T1   *++B_Wptr[B_run],       A_W             ;[23,2] 
||      CMPLT   .L1X    B_level,    0,          A_neg           ;[23,2] 
||      SHL     .S2     B_top0_bk,  B_rld_left, B_t13           ;[13,3] 
||      MPY     .M2X    B_const32,  A_len,      B_t12           ;[13,3] 
||[!B_eob]MV    .L2     B_word2,    B_word2_bk                  ;preserve
||[!B_eob]MV    .D1     A_word1,    A_word1_bk                  ;preserve
||[!B_eob]MVD   .M1     A_word1_rw, A_word1_rw_bk               ;preserve

  [!B_eob]ADD   .L2     B_Wptr,     2,          B_Wptr          ;[24,2] 
||[!B_eob]ADD   .D1X    A_t8,       B_t9,       A_top1          ;[24,2] 
||      SHRU    .S2     B_t13,      27,         B_t14           ;[14,3] 
||[ A_test2]LDW .D2T2   *B_bsbuf_circ++,        B_word2         ;[14,3] 
||      SHRU    .S1     A_t1h:A_t1l, A_const36, A_t4h:A_t4l     ;[ 4,4]
||      SUB     .L1     A_len_tbl_adr,          A_t2,       A_t3;[ 4,4] 

        SHR     .S1     A_level5,   A_constSHR, A_level_f       ;[35,1] 12Q4
||[ A_neg]SUB   .D2     B_level2,   1,          B_level3        ;[25,2] 
||      ADD     .L2     B_t14,      B_t12,      B_t15           ;[15,3]
||      SUB     .S2X    B_const32,  A_bptr,     B_bptr_cmpl     ;[15,3] 
||[ A_test2]MV  .L1X    B_word2,    A_word1                     ;[15,3] 
|| [A_test2]MVD .M1     A_word1,    A_word1_rw                  ; RWD
||      LDBU    .D1T1   *A_t3[A_t4l],           A_len           ;[ 5,4]

  [!A_neg]ADD   .L2     B_level2,   1,          B_level3        ;[26,2] 
||      ADD     .S2     B_t15,      B_t15,      B_t16           ;[16,3]
||      SUB     .D1     A_len,      24,         A_test1         ;[16,3] 
||      SHRU    .S1     A_top1,     A_len_c,    A_t7            ;[16,3] 
||[!B_eob]AND   .L1X    B_constFFF0,A_level_f,  A_level_f_      ; 12Q4, fix XP

  [!B_eob]STH   .D1T1   A_level_f_, *+A_outi[A_cnum]            ;[36,1] BC, fix XP
||[!B_eob]XOR   .S2X    B_sum,      A_level_f,  B_sum           ;[37,1] fix XP 
||        CMPGT .L2     B_run,      B_const63,  B_eob           ;[27,2] 
||[ A_test1]LDB .D2T2   *B_rld_table_adr[B_t16],B_level         ;[17,3] 
||[!B_eob]ADD   .L1     A_ptop0l,   A_t7,       A2_top0l        ;[17,3]    
||[B_eob] XOR   .S1     A_const16,  A_last_coeff, A_last_coeff  ;mismatch 12Q4
||[B_eob] MVD   .M1     A_word1_rw_bk,          A_word1_rw      ; RWD

* =========================== PIPE LOOP EPILOG ============================ *
* ========================================================================= *
; live-out: top0h:top0k, top1, word1, word2, bsbuf_circ, run, Wptr, Wptr_end, 
;           sum, bptr

    .asg    B0,     B_err       ; same reg as B_eob
    .asg    A29,    A_Mpeg2v
    .asg    B31,    B_bsbuf
    .asg    B3,     B_ret       ; Return address
    .asg    B15,    B_SP        ; Stack pointer, B datapath
    .asg    B1,     B_const65

mismatch: 
 [B_cnt] B       .S1     block_loop                             ; -- BRANCH --
||       MVK     .S2     65,           B_const65                ; invalid VLC
||       CMPGTU  .L2     B_Wptr,       B_Wptr_end, B_err        ; overrun
||       AND     .L1X    A_const16,    B_sum,      A2_odd       ; mismatch 12Q4

 [!B_err]CMPGT   .L2     B_run_bk,     B_const65,  B_err        ; invalid VLC
||       ADD     .S2     B_outi,       2,          B_outi
||       LDW     .D1T2   *+A_Mpeg2v[BSBUF_M2OFF],  B_bsbuf      ; exit
||[!A2_odd]STH   .D2T1   A_last_coeff, *B_outi                  ; mismatch     

  [B_err]B       .S2     exit                                   ; -- BRANCH --
||       LDW     .D2T2   *+B_SP[2],    B_ret                    ; exit
||       MV      .L2     B_bsbuf_circ_bk, B_bsbuf_circ          ; AMR arg

         NOP             3                                      ; MERGE
; branch occurs to block_loop
; branch occurs to exit occurs after 2 cycles in block_loop 
; (preserve B0_err for exit)
         
; this will execute only if B_cnt was 0
        NOP              2                                      ; MERGE

* =================================== EXIT =============================== *
        .asg            B26,        B_csr        ; CSR value to restore
        .asg            B22,        B_byte_diff
        .asg            B29,        B_next_wptr
        .asg            B1,         B_lz
        .asg            B27,        B_amr_config
        .asg            B4,         B_constBUFMASK                

exit:
        SUB     .L2      B_bsbuf_circ,  B_bsbuf, B_byte_diff
||      SHRU    .S1      A_top1,        8,         A_t2
||      SUB     .S2      B_bptr_bk,     8,         B_bptr_bk   
||      LDW     .D2T1    *+B_SP[6],     A14                     ; MERGE
        
        SHR     .S2      B_byte_diff,   2,         B_next_wptr
||      SHL     .S1      A_top0l_bk,    24,        A_t3
||      CMPLT   .L2      B_bptr_bk,     0,         B_lz
||      LDW     .D2T1    *+B_SP[3],     A11                       

        ADD     .L1      A_t2,          A_t3,      A_top1
||      SHRU    .S1      A_top0h_bk:A_top0l_bk, 8, A_empty:A_top0_bk
||      STW     .D1T2    B_err,      *+A_Mpeg2v[FAULT_M2OFF]
||[B_lz]MVD     .M1      A_word1_rw,               A_word1_bk   ; RWD
||[B_lz]MV      .L2X     A_word1_bk,               B_word2_bk
||      LDW     .D2T1    *+B_SP[4],     A12                       
 
        LDW     .D2T2    *+B_SP[1],     B_csr       ; Get CSR's value
||      STW     .D1T1    A_top1,        *+A_Mpeg2v[TOP1_M2OFF]      
||[B_lz]ADD     .L2      B_bptr_bk,     A_const32, B_bptr_bk

        STW     .D1T2    B_bptr_bk,     *+A_Mpeg2v[BPTR_M2OFF]      
||      LDW     .D2T1    *+B_SP[5],     A13                        

        RET     .S2      B_ret                      ; Return to caller
||      STW     .D1T1    A_top0_bk,     *+A_Mpeg2v[TOP0_M2OFF]
||[B_lz]SUBAW   .D2      B_bsbuf_circ,  1, B_bsbuf_circ       ; AMR arg

        STW     .D1T2    B_next_wptr,   *+A_Mpeg2v[NEXTWPTR_M2OFF]
||      ZERO    .L2      B_amr_config
||      LDW     .D2T1    *++B_SP[10],    A10                   ; MERGE, 2 W-mat
||[B_lz]SUB     .S2      B_bsbuf_circ,  B_bsbuf, B_byte_diff  ; AMR arg
        
        STW     .D1T1    A_word1_bk,    *+A_Mpeg2v[WORD1_M2OFF]
||[B_lz]SHR     .S2      B_byte_diff,   2,         B_next_wptr ; AMR arg
        
        STW     .D1T2    B_word2_bk,    *+A_Mpeg2v[WORD2_M2OFF]
;  ===== Interruptibility state restored here =====

        STW     .D1T2    B_next_wptr,   *+A_Mpeg2v[NEXTWPTR_M2OFF]
||      MVC     .S2      B_amr_config,  AMR

        MVC     .S2      B_csr,         CSR           ; Restore CSR
; Branch occurs

* ========================================================================= *
*   End of file:   mpeg2_vld_inter_h.asm                                    *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2008 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
