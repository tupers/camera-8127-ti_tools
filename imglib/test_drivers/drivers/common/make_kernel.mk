#* ======================================================================== *#
#*  TEXAS INSTRUMENTS, INC.                                                 *#
#*                                                                          *#
#*  IMGLIB-2  DSP Image/Video Processing Library                            *#
#*                                                                          *#
#*      Release:        Revision 2.0.1                                      *#
#*      Snapshot date:  6-May-2008                                          *#
#*                                                                          *#
#*  This library contains proprietary intellectual property of Texas        *#
#*  Instruments, Inc.  The library and its source code are protected by     *#
#*  various copyrights, and portions may also be protected by patents or    *#
#*  other legal protections.                                                *#
#*                                                                          *#
#*  This software is licensed for use with Texas Instruments TMS320         *#
#*  family DSPs.  This license was provided to you prior to installing      *#
#*  the software.  You may review this license by consulting the file       *#
#*  TI_license.PDF which accompanies the files in this library.             *#
#* ------------------------------------------------------------------------ *#
#*          Copyright (C) 2008 Texas Instruments, Incorporated.             *#
#*                          All Rights Reserved.                            *#
#* ======================================================================== *#
CC=cl6x
CPP=cl6x
LINK=lnk6x
ASM=asm6x

OBJDIR=debug
TARGET=${OBJDIR}/${K_NAME}.out
INP_DIR=../common/
K_DIR_I=../../../kernels/intrinsic/
K_DIR_C=../../../kernels/c/
K_DIR_SA=../../../kernels/serial_asm/
I_DIR=../../../include/

RTS_LIB=rts64plus.lib
LNK_CMD=${INP_DIR}/kernel_test.cmd

OPT_FLG=-o3
ifeq (${DBG}, YES)
	OPT_FLG=-g -d"INTERACTIVE_DEBUG" -d"COMM_FLOW"
endif

CFLAGS=-q -mv6400+ -k -ml3 -mwth -mi ${OPT_FLG}
DIR_FLAGS=-ft${OBJDIR} -fr${OBJDIR} -fs${OBJDIR} -i${INP_DIR} -i${I_DIR}

ASM_FLAGS=-q -v6400+

MAP_FILE=$(patsubst %.out,%.map,${TARGET})

SA=NO
ifeq (${SA}, YES)
	OBJS=$(OBJDIR)/${K_NAME}.obj
else
	OBJS=$(OBJDIR)/${K_NAME}_i.obj
endif

OPT_H=${I_DIR}/${K_NAME}.h

OBJS+=$(OBJDIR)/support.obj	  \
		${OBJDIR}/${K_NAME}_d.obj \
		${OBJDIR}/${K_NAME}_c.obj \
		${OBJDIR}/${K_NAME}_idat.obj \
		${OBJDIR}/${K_NAME}_odat.obj \
		$(OBJDIR)/mem_cpy.obj

.PHONY: all
all: ${TARGET}

${OBJDIR}:
	mkdir ${OBJDIR}

${TARGET}: ${OBJDIR} ${OBJS} ${LNK_CMD}
	${LINK} -heap 0x10000 -stack 0x2000 -c -x ${OBJS} ${LNK_CMD} -l${RTS_LIB} -m ${MAP_FILE} -o $@

.PHONY:clean
clean:
	rm -fr ${OBJDIR} *~

#rm -fr ${OBJDIR} ${OBJS} ${TARGET} ${MAP_FILE} *~

%.obj:
	${CC}  ${CFLAGS} ${DIR_FLAGS} $<

${OBJDIR}/${K_NAME}_d.obj: ${K_NAME}_d.c ${I_DIR}/${K_NAME}_c.h ${OPT_H}
${OBJDIR}/${K_NAME}_c.obj: ${K_DIR_C}/${K_NAME}_c.c ${I_DIR}/${K_NAME}_c.h
${OBJDIR}/${K_NAME}_i.obj: ${K_DIR_I}/${K_NAME}_i.c ${OPT_H}
${OBJDIR}/${K_NAME}_idat.obj: ${K_NAME}_idat.c
${OBJDIR}/${K_NAME}_odat.obj: ${K_NAME}_odat.c
${OBJDIR}/mem_cpy.obj    : ${INP_DIR}/mem_cpy.c ${INP_DIR}/mem_cpy.h
${OBJDIR}/support.obj    : ${INP_DIR}/support.c ${INP_DIR}/support.h

${OBJDIR}/${K_NAME}.obj: ${K_DIR_SA}/${K_NAME}.sa ${OPT_H}
	${CC}  ${CFLAGS} ${DIR_FLAGS} ${K_DIR_SA}/${K_NAME}.sa

