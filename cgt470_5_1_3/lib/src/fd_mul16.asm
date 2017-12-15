;******************************************************************************
;* FD_MUL16.ASM  - 16 BIT STATE -  v5.1.3                                     *
;*                                                                            *
;* Copyright (c) 1996-2013 Texas Instruments Incorporated                     *
;* http://www.ti.com/                                                         *
;*                                                                            *
;*  Redistribution and  use in source  and binary forms, with  or without     *
;*  modification,  are permitted provided  that the  following conditions     *
;*  are met:                                                                  *
;*                                                                            *
;*     Redistributions  of source  code must  retain the  above copyright     *
;*     notice, this list of conditions and the following disclaimer.          *
;*                                                                            *
;*     Redistributions in binary form  must reproduce the above copyright     *
;*     notice, this  list of conditions  and the following  disclaimer in     *
;*     the  documentation  and/or   other  materials  provided  with  the     *
;*     distribution.                                                          *
;*                                                                            *
;*     Neither the  name of Texas Instruments Incorporated  nor the names     *
;*     of its  contributors may  be used to  endorse or  promote products     *
;*     derived  from   this  software  without   specific  prior  written     *
;*     permission.                                                            *
;*                                                                            *
;*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS     *
;*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT     *
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR     *
;*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT     *
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
;*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT     *
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
;*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT     *
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
;*                                                                            *
;******************************************************************************

;****************************************************************************
;* FD$MUL - MULTIPLY TWO IEEE 754 FORMAT DOUBLE PRECISION FLOATING 
;*          POINT NUMBERS.
;****************************************************************************
;*
;*   o INPUT OP1 IS IN r0:r1
;*   o INPUT OP2 IS IN r2:r3
;*   o RESULT IS RETURNED IN r0:r1
;*   o INPUT OP2 IN r2:r3 IS NOT DESTROYED
;*
;*   o SIGNALLING NOT-A-NUMBER (SNaN) AND QUIET NOT-A-NUMBER (QNaN)
;*     ARE TREATED AS INFINITY
;*   o OVERFLOW RETURNS +/- INFINITY 
;*       (0x7ff00000:00000000) or (0xfff00000:00000000) 
;*   o UNDERFLOW RETURNS ZERO (0x00000000:00000000)
;*   o DENORMALIZED NUMBERS ARE TREATED AS UNDERFLOWS
;*   o ROUNDING MODE:  ROUND TO NEAREST
;*
;*   o IF THE OPERATION INVOLVES INFINITY AS AN INPUT, UNLESS THE OTHER INPUT
;*     IS ZERO, THE RESULT IS INFINITY WITH THE SIGN DETERMINED IN THE USUAL
;*     FASHION.
;*
;****************************************************************************
;*
;* +------------------------------------------------------------------+
;* | DOUBLE PRECISION FLOATING POINT FORMAT                           |
;* |   64-bit representation                                          |
;* |   31 30      20 19                  0                            |
;* |   +-+----------+---------------------+                           |
;* |   |S|     E    |        M1           |                           |
;* |   +-+----------+---------------------+                           |
;* |                                                                  |
;* |   31                                0                            |
;* |   +----------------------------------+                           |
;* |   |             M2                   |                           |
;* |   +----------------------------------+                           |
;* |                                                                  |
;* |   <S>  SIGN FIELD    :          0 - POSITIVE VALUE               |
;* |                                 1 - NEGATIVE VALUE               |
;* |                                                                  |
;* |   <E>  EXPONENT FIELD: 0000000000 - ZERO IFF M == 0              |
;* |            0000000001..1111111110 - EXPONENT VALUE(1023 BIAS)    |
;* |                        1111111111 - INFINITY                     |
;* |                                                                  |
;* |   <M1:M2>  MANTISSA FIELDS:  FRACTIONAL MAGNITUDE WITH IMPLIED 1 |
;* +------------------------------------------------------------------+
;*
;****************************************************************************

        .global __TI_umull

	.state16

        .if __TI_EABI_ASSEMBLER            ; ASSIGN EXTERNAL NAMES BASED ON
        .asg __aeabi_dmul, __TI_FD$MUL     ; RTS BEING BUILT
        .else
	.clink
        .asg FD$MUL, __TI_FD$MUL
        .endif

	.global	__TI_FD$MUL

	.if .TMS470_BIG_DOUBLE

rp1_hi	.set	r0	; High word of regpair 1
rp1_lo	.set	r1	; Low word of regpair 1
rp2_hi	.set	r2	; High word of regpair 2
rp2_lo	.set	r3	; Low word of regpair 2
res1	.set	r0	; OVERLOADED WITH INPUT #1
op1e	.set	r1	; OVERLOADED WITH INPUT #1
op1m1	.set	r2	; OVERLOADED WITH INPUT #2
op1m2	.set	r3	; OVERLOADED WITH INPUT #2

	.else

rp1_hi	.set	r1	; High word of regpair 1
rp1_lo	.set	r0	; Low word of regpair 1
rp2_hi	.set	r3	; High word of regpair 2
rp2_lo	.set	r2	; Low word of regpair 2
res1	.set	r1	; OVERLOADED WITH INPUT #1
op1e	.set	r0	; OVERLOADED WITH INPUT #1
op1m1	.set	r3	; OVERLOADED WITH INPUT #2
op1m2	.set	r2	; OVERLOADED WITH INPUT #2

	.endif

tmp	.set	r4
op2m1	.set	r5
op2m2	.set	r6
op2e	.set	r7
res2	.set	r7	; OVERLOADED WITH op2e

	.if __TI_ARM9ABI_ASSEMBLER  | __TI_EABI_ASSEMBLER
	.thumbfunc __TI_FD$MUL
	.endif

        .if __TI_ARM_V6M0__
__TI_FD$MUL:    .asmfunc    stack_usage(40) ; V6M0 needs a little more stack
        .else                               ; space to work in thumb mode.
__TI_FD$MUL:    .asmfunc    stack_usage(32)
        .endif
        
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	PUSH	{r2-r7, lr}		;
	.else
	PUSH	{r2-r7}			;  PUSH THE LR SEPARATELY SO IT CAN BE
	PUSH	{lr}			;  POPPED FIRST.
	.endif

	MOV	tmp, rp1_hi		; SET THE SIGN OF THE RESULT
        EOR     tmp, rp2_hi             ;
	LSR	tmp, tmp, #31		;
	LSL	tmp, tmp, #31		;
	PUSH	{tmp}			;

	LSL	op2m1, rp2_hi, #11	; BUILD INPUT #2 MANTISSA
	LSR	tmp, rp2_lo, #21	;
	ORR	op2m1, tmp		;
	LSL	op2m2, rp2_lo, #11	;
	LSL	op2e, rp2_hi, #1	; BUILD INPUT #2 EXPONENT
	LSR	op2e, op2e, #21		;
	BEQ	unfl			;

	MOV	tmp, #0x1		;
	LSL	tmp, tmp, #31		; SET IMPLIED ONE IN MANTISSA
	ORR	op2m1, tmp	 	;

	MOV	tmp, #0x7		;
	LSL	tmp, tmp, #8		;
	ADD	tmp, #0xFF		;
	CMP	op2e, tmp		; IF op2e == 0x7FF, THEN OVERFLOW
	BEQ	ovfl			;

	LSL	op1m1, rp1_hi, #11	; BUILD INPUT #1 MANTISSA
	LSR	tmp, rp1_lo, #21	;
	ORR	op1m1, tmp		;
	LSL	op1m2, rp1_lo, #11	;
	LSL	op1e, rp1_hi, #1	; BUILD INPUT #1 EXPONENT
	LSR	op1e, op1e, #21		;
	BEQ	unfl			;

	MOV	tmp, #0x1		; SET IMPLIED ONE IN MANTISSA
	LSL	tmp, tmp, #31		;
	ORR	op1m1, tmp	 	;

	MOV	tmp, #0x7		;
	LSL	tmp, tmp, #8		;
	ADD	tmp, #0xFF		;
	CMP	op1e, tmp		; IF op1e == 0x7FF, THEN OVERFLOW
	BEQ	ovfl			;

        ADD     op1e, op1e, op2e        ; ADD EXPONENTS

        .if __TI_ARM_V6M0__
        
        PUSH    {op1e}          ; Store this off since we need the register
        
        MOV     r0, op1m1       ; Setup arguments for the first UMULL
        MOV     r1, op2m1
        BL      __TI_umull      ; r0:r1 = r0 * r1
        MOV     res2, r1        ; Move the results around
        PUSH    {r0}            ; Store this off since we need the register

        MOV     r0, op1m1       ; Again...
        MOV     r1, op2m2
        BL      __TI_umull
        MOV     op1m1, r0
        MOV     tmp, r1
        
        MOV     r0, op1m2       ; Again...
        MOV     r1, op2m2
        BL      __TI_umull
        MOV     op2m2, r0       ; We only need the high word
        
        MOV     r0, op1m2       ; Again...
        MOV     r1, op2m1
        BL      __TI_umull
        MOV     op2m1, r0
        ADD     op2m2, r1       ; The low word gets added into op2m2

        MOV     op1m2, #0
        
        POP     {res1, op1e}    ; Grab that stuff we stored off
        
        .else
	
        NOP				; 
	BX	pc			; CHANGE TO 32 BIT STATE FOR MULTIPLY
	NOP				;

	.state32

	; MULTIPLY THE MANTISAE: op1m * op2m => res1:res2
	UMULL	res2, res1, op1m1, op2m1; op1m1*op2m1 =>res1:res2: 0   : 0
	UMULL	tmp, op1m1, op2m2, op1m1; op1m1*op2m2 =>  0 :op1m1:tmp : 0
	UMULL	lr, op2m2, op1m2, op2m2 ; op1m2*op2m2 =>  0 :  0 :op2m2: lr
	UMULL	lr, op2m1, op1m2, op2m1 ; op1m2*op2m1 =>  0 :op2m1: lr : 0
	ADDS	op2m2, op2m2, lr	;                 0 :  0 :op2m2: 0

	MOV	op1m2, #0x0
	
        ADD	lr, pc, #0x1		; CHANGE BACK TO 16 BIT STATE
	BX	lr			;

	.state16
        
        .endif

	ADC	op2m1, op1m2		;                 0 :op2m1: 0  : 0
	ADC	res1, op1m2		;               res1:  0 : 0   : 0
	ADD	tmp, op2m2		;                 0 :  0 : tmp : 0
	ADC	op2m1, op1m2		;                 0 :op2m1: 0  : 0
	ADC	res1, op1m2	 	;               res1:  0 : 0   : 0

	MOV	tmp, #0x80		; SETUP 1/2 CONSTANT FOR ROUNDING
	LSL	tmp, tmp, #2    	;

	ADD	op1m1, op2m1		;                 0 :op1m1: 0  : 0
	ADC	res1, op1m2		;               res1:  0 : 0   : 0
	ADD	res2, op1m1		;                 0 :res2: 0   : 0
	ADC	res1, op1m2		;               res1:  0 : 0   : 0

	BPL	$1			; IF THE MANTISSA WILL NOT NEED
	LSL	tmp, tmp, #0x1		; ALIGNMENT, ADJUST 1/2 CONSTANT.

$1:	ADD	res2, res2, tmp		; ADD 1/2 FOR ROUNDING
	ADC	res1, op1m2		;

	BMI	$2			; ALIGN THE RESULT
	LSL	res2, res2, #1		;
	ADC	res1, res1		;
	B	$3			;

$2:	ADD	op1e, op1e, #0x1	; 

$3:	MOV	tmp, #0x3		;
	LSL	tmp, tmp, #8		;
	ADD	tmp, #0xFF		;
	SUB     op1e, op1e, tmp         ; ADJUST FOR BIAS
	BLE	unfl			; AND CHECK FOR UNDERFLOW

	ADD	tmp, tmp, tmp		;
        CMP     op1e, tmp	        ; AND CHECK FOR EXPONENT OVERFLOW 
	BHI	ovfl			;

	LSL	op1m1, op1e, #20	; ALIGN EXPONENT INTO op1m1
	LSR	rp1_lo, res2, #11	; REPACK LOW PART OF RESULT
	LSL	tmp, res1, #21		;
	ORR	rp1_lo, tmp		;
	LSL	rp1_hi, res1, #1	; REPACK HIGH PART OF RESULT
	LSR	rp1_hi, rp1_hi, #12	;
        ORR     rp1_hi, op1m1           ; REPACK THE EXPONENT INTO rp1_hi
	POP	{tmp}			;
        ORR     rp1_hi, tmp             ; REPACK THE SIGN INTO rp1_hi
 
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	POP	{r2-r7, pc}	        ;
	.else
	POP	{r2}
	MOV	lr, r2
	POP	{r2-r7}
	BX	lr
	.endif

ovfl:   MOV     rp1_lo, #0              ; IF OVERFLOW, RETURN +/- INFINITY
	MOV	rp1_hi, #0xFF
	LSL	rp1_hi, rp1_hi, #3
	ADD	rp1_hi, rp1_hi, #7
	LSL	rp1_hi, rp1_hi, #20
	POP	{tmp}			;
        ORR     rp1_hi, tmp             ;
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	POP	{r2-r7, pc}	        ;
	.else
	POP	{r2}
	MOV	lr, r2
	POP	{r2-r7}
	BX	lr
	.endif

unfl:   MOV     rp1_hi, #0              ; UNDERFLOW, SO RETURN ZERO
	MOV	rp1_lo, #0		;
	ADD	sp, #4			;
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	POP	{r2-r7, pc}	        ;
	.else
	POP	{r2}
	MOV	lr, r2
	POP	{r2-r7}
	BX	lr
	.endif
 
	.endasmfunc

	.end

