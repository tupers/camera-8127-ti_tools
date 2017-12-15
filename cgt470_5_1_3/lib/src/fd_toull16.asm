;******************************************************************************
;* FD_TOULL16.ASM  - 16 BIT STATE -  v5.1.3                                   *
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
;* FD$TOULL - CONVERT AN IEEE 754 FORMAT DOUBLE PRECISION FLOATING 
;*            INTO AN UNSIGNED 64 BIT INTEGER 
;****************************************************************************
;*
;*   o INPUT OP IS IN r0:r1
;*   o RESULT IS RETURNED IN r0:r1 (r1:r0 IF LITTLE ENDIAN)
;*
;*   o SIGNALLING NOT-A-NUMBER (SNaN) AND QUIET NOT-A-NUMBER (QNaN)
;*     ARE TREATED AS INFINITY
;*   o OVERFLOW RETURNS 0xFFFFFFFF:FFFFFFFF
;*   o UNDERFLOW RETURNS ZERO (0x00000000:00000000)
;*   o NEGATIVE VALUE RETURNS ZERO
;*   o ROUNDING MODE:  ROUND TO ZERO
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

	.state16

        .if __TI_EABI_ASSEMBLER            ; ASSIGN EXTERNAL NAMES BASED ON
        .asg __aeabi_d2ulz, __TI_FD$TOULL  ; RTS BEING BUILT
        .else
	.clink
        .asg FD$TOULL, __TI_FD$TOULL
        .endif

	.global	__TI_FD$TOULL

	.if .TMS470_BIG_DOUBLE
rp1_hi	.set	r0	; High word of regpair 1
rp1_lo	.set	r1	; Low word of regpair 1
	.else
rp1_hi	.set	r1	; High word of regpair 1
rp1_lo	.set	r0	; Low word of regpair 1
	.endif

	.if .TMS470_LITTLE
res_hi	.set	r1	; High word of result   
res_lo	.set	r0	; Low word of result   
	.else
res_hi	.set	r0	; High word of result   
res_lo	.set	r1	; Low word of result   
	.endif

ope	.set	r2
tmp	.set	r3
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
tmp2	.set	lr
	.else
tmp2	.set	r4
	.endif	 

	.if __TI_ARM9ABI_ASSEMBLER  | __TI_EABI_ASSEMBLER
	.thumbfunc __TI_FD$TOULL
	.endif

__TI_FD$TOULL: .asmfunc stack_usage(12)
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
        PUSH	{r2-r3, lr}		; SAVE CONTEXT
	.else
	PUSH	{r2-r4}
	.endif

	CMP	rp1_hi, #0		; CHECK FOR A NEGATIVE VALUE
	BMI	unfl			;

	LSL	ope, rp1_hi, #1		; PUT EXPONENT IN ope
	LSR	ope, ope, #21		;

	MOV	tmp, #0x3		;
	LSL	tmp, tmp, #8		;
	ADD	tmp, #0xFF		;
	SUB	ope, ope, tmp		; ADJUST FOR EXPONENT BIAS AND
	BCC	unfl			; CHECK FOR UNDERFLOW

	MOV	tmp, #0x3F		;
	SUB	ope, tmp, ope		; CHECK FOR OVERFLOW
	BCC	ovfl			; IF OVERFLOW, RETURN 0xFFFFFFFF

	LSL	rp1_hi, rp1_hi, #11	; PUT MANTISSA IN rp1_hi:rp1_lo
        LSR     tmp, rp1_lo, #21        ;
        ORR     rp1_hi, tmp             ;
        LSL     rp1_lo, rp1_lo, #11     ;
	MOV	tmp, #0x1		;
	LSL	tmp, tmp, #31		;
	ORR	rp1_hi, tmp		; SET IMPLIED ONE IN HI MANTISSA

        ; COMPUTE THE INTEGER VALUE
        MOV     tmp, ope                ;
        SUB     tmp, #32                ; IF ope >= 32 
        BCC     $1                      ;
        MOV     rp1_lo, rp1_hi          ;    rp1_hi:rp1_lo = 0:rp1_hi >> (ope - 32)
        MOV     rp1_hi, #0              ;
	LSR	rp1_lo, tmp		;
	B       return                  ;
$1:
        LSR     rp1_lo, ope             ; IF ope < 32
        NEG     tmp, tmp                ;    
        MOV     tmp2, rp1_hi            ;    rp1_hi:rp1_lo = rp1_hi:rp1_lo >> ope
        LSL     rp1_hi, tmp             ;
        ORR     rp1_lo, rp1_hi          ;
        MOV     rp1_hi, tmp2            ;
        LSR     rp1_hi, ope             ;

	; IF THE ENDIANNESS OF THE DOUBLE IS DIFFERENT FROM THE TARGET
	; ENDIAN (MIXED ENDIAN) SWAP THE REGISTER VALUES BEFORE RETURNING.
return:
	.if .TMS470_LITTLE != .TMS470_LITTLE_DOUBLE
	MOV	tmp2, res_hi		;
	MOV	res_hi, res_lo		;
	MOV	res_lo, tmp2		;
	.endif

	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	POP	{r2-r3, pc}		;
	.else
	POP	{r2-r4}
	BX	lr
	.endif

unfl:   MOV     r0, #0                  ; UNDERFLOW
        MOV     r1, #0                  ;
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	POP	{r2-r3, pc}		;
	.else
	POP	{r2-r4}
	BX	lr
	.endif
 
ovfl:	MOV	r0, #0x0		; IF OVERFLOW, 
	SUB	r0, r0, #0x1		; RETURN 0xFFFFFFFF:FFFFFFFF
        MOV     r1, r0                  ;
	.if __TI_ARM7ABI_ASSEMBLER | __TI_ARM9ABI_ASSEMBLER | !__TI_TMS470_V4__
	POP	{r2-r3, pc}		;
	.else
	POP	{r2-r4}
	BX	lr
	.endif
	
	.endasmfunc

	.end
