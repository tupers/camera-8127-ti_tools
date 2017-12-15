/* ======================================================================= *
 * Texas Instruments OMAP(TM) Platform Software * (c) Copyright 2008 Texas
 * Instruments Incorporated. All Rights Reserved. * * Use of this software is 
 * controlled by the terms and conditions found * in the license agreement
 * under which this software has been supplied. *
 * ======================================================================== */
/**
* @file csi2_reg.h
*
* This file contains Register level layout structure  for CSI2 module of Ducati subsystem  in OMAP4/Monica
*
* @path ISP/CSI2/
*
* @rev 1.0
*
* @developer: 
*/
/*========================================================================*/

#ifndef _CSLR_CSI2_REG_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define _CSLR_CSI2_REG_H_

#include "csi2_utils.h"

/*******************************************************************
* CSI2 CSL register layout datastructure.
*Field names are exactly matched to the register names
*
*******************************************************************/
typedef struct {

    volatile uint32 CSI2_REVISION;

    /* Extra padding added for continuity of register space */
    volatile uint32 Reserved_0[3];

    volatile uint32 CSI2_SYSCONFIG;
    volatile uint32 CSI2_SYSSTATUS;
    volatile uint32 CSI2_IRQSTATUS;
    volatile uint32 CSI2_IRQENABLE;

    /* Extra padding added for continuity of register space */
    volatile uint32 Reserved_1[8];

    volatile uint32 CSI2_CTRL;
    volatile uint32 CSI2_DBG_H;
    volatile uint32 CSI2_GNQ;
    volatile uint32 CSI2_COMPLEXIO_CFG2;
    volatile uint32 CSI2_COMPLEXIO_CFG1;
    volatile uint32 CSI2_COMPLEXIO1_IRQSTATUS;
    volatile uint32 CSI2_COMPLEXIO2_IRQSTATUS;
    volatile uint32 CSI2_SHORT_PACKET;
    volatile uint32 CSI2_COMPLEXIO1_IRQENABLE;
    volatile uint32 CSI2_COMPLEXIO2_IRQENABLE;
    volatile uint32 CSI2_DBG_P;
    volatile uint32 CSI2_TIMING;

    volatile uint32 CSI2_CTX_CTRL1_0;
    volatile uint32 CSI2_CTX_CTRL2_0;
    volatile uint32 CSI2_CTX_DAT_OFST_0;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_0;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_0;
    volatile uint32 CSI2_CTX_IRQENABLE_0;
    volatile uint32 CSI2_CTX_IRQSTATUS_0;
    volatile uint32 CSI2_CTX_CTRL3_0;

    volatile uint32 CSI2_CTX_CTRL1_1;
    volatile uint32 CSI2_CTX_CTRL2_1;
    volatile uint32 CSI2_CTX_DAT_OFST_1;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_1;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_1;
    volatile uint32 CSI2_CTX_IRQENABLE_1;
    volatile uint32 CSI2_CTX_IRQSTATUS_1;
    volatile uint32 CSI2_CTX_CTRL3_1;

    volatile uint32 CSI2_CTX_CTRL1_2;
    volatile uint32 CSI2_CTX_CTRL2_2;
    volatile uint32 CSI2_CTX_DAT_OFST_2;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_2;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_2;
    volatile uint32 CSI2_CTX_IRQENABLE_2;
    volatile uint32 CSI2_CTX_IRQSTATUS_2;
    volatile uint32 CSI2_CTX_CTRL3_2;

    volatile uint32 CSI2_CTX_CTRL1_3;
    volatile uint32 CSI2_CTX_CTRL2_3;
    volatile uint32 CSI2_CTX_DAT_OFST_3;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_3;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_3;
    volatile uint32 CSI2_CTX_IRQENABLE_3;
    volatile uint32 CSI2_CTX_IRQSTATUS_3;
    volatile uint32 CSI2_CTX_CTRL3_3;

    volatile uint32 CSI2_CTX_CTRL1_4;
    volatile uint32 CSI2_CTX_CTRL2_4;
    volatile uint32 CSI2_CTX_DAT_OFST_4;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_4;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_4;
    volatile uint32 CSI2_CTX_IRQENABLE_4;
    volatile uint32 CSI2_CTX_IRQSTATUS_4;
    volatile uint32 CSI2_CTX_CTRL3_4;

    volatile uint32 CSI2_CTX_CTRL1_5;
    volatile uint32 CSI2_CTX_CTRL2_5;
    volatile uint32 CSI2_CTX_DAT_OFST_5;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_5;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_5;
    volatile uint32 CSI2_CTX_IRQENABLE_5;
    volatile uint32 CSI2_CTX_IRQSTATUS_5;
    volatile uint32 CSI2_CTX_CTRL3_5;

    volatile uint32 CSI2_CTX_CTRL1_6;
    volatile uint32 CSI2_CTX_CTRL2_6;
    volatile uint32 CSI2_CTX_DAT_OFST_6;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_6;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_6;
    volatile uint32 CSI2_CTX_IRQENABLE_6;
    volatile uint32 CSI2_CTX_IRQSTATUS_6;
    volatile uint32 CSI2_CTX_CTRL3_6;

    volatile uint32 CSI2_CTX_CTRL1_7;
    volatile uint32 CSI2_CTX_CTRL2_7;
    volatile uint32 CSI2_CTX_DAT_OFST_7;
    volatile uint32 CSI2_CTX_DAT_PING_ADDR_7;
    volatile uint32 CSI2_CTX_DAT_PONG_ADDR_7;
    volatile uint32 CSI2_CTX_IRQENABLE_7;
    volatile uint32 CSI2_CTX_IRQSTATUS_7;
    volatile uint32 CSI2_CTX_CTRL3_7;

    volatile uint32 CSI2_PHY_CFG_00;
    volatile uint32 CSI2_PHY_CFG_01;
    volatile uint32 CSI2_PHY_CFG_02;
    volatile uint32 CSI2_PHY_CFG_03;
    volatile uint32 CSI2_PHY_CFG_04;
    volatile uint32 CSI2_PHY_CFG_05;
    volatile uint32 CSI2_PHY_CFG_06;
    volatile uint32 CSI2_PHY_CFG_07;
    volatile uint32 CSI2_PHY_CFG_08;
    volatile uint32 CSI2_PHY_CFG_09;
    volatile uint32 CSI2_PHY_CFG_10;
    volatile uint32 CSI2_PHY_CFG_11;
    volatile uint32 CSI2_PHY_CFG_12;
    volatile uint32 CSI2_PHY_CFG_13;
    volatile uint32 CSI2_PHY_CFG_14;
    volatile uint32 CSI2_PHY_CFG_15;

    /* Extra padding added for continuity of register space */
    volatile uint32 Reserved_2[4];

    volatile uint32 CSI2_CTX_TRANSCODEH_0;
    volatile uint32 CSI2_CTX_TRANSCODEV_0;
    volatile uint32 CSI2_CTX_TRANSCODEH_1;
    volatile uint32 CSI2_CTX_TRANSCODEV_1;
    volatile uint32 CSI2_CTX_TRANSCODEH_2;
    volatile uint32 CSI2_CTX_TRANSCODEV_2;
    volatile uint32 CSI2_CTX_TRANSCODEH_3;
    volatile uint32 CSI2_CTX_TRANSCODEV_3;
    volatile uint32 CSI2_CTX_TRANSCODEH_4;
    volatile uint32 CSI2_CTX_TRANSCODEV_4;
    volatile uint32 CSI2_CTX_TRANSCODEH_5;
    volatile uint32 CSI2_CTX_TRANSCODEV_5;
    volatile uint32 CSI2_CTX_TRANSCODEH_6;
    volatile uint32 CSI2_CTX_TRANSCODEV_6;
    volatile uint32 CSI2_CTX_TRANSCODEH_7;
    volatile uint32 CSI2_CTX_TRANSCODEV_7;
} CSL_CSI2Regs;

/**************************************************************************
******************* Register Fields: MASK and SHIFT Values*********************
*These values are used to manipulate a specific bit field of a register without changing other fields
***************************************************************************/

// CSI2_REVISION
#define CSI2_REVISION_REV_SHIFT (0x0000u)
#define CSI2_REVISION_REV_MASK (0x00FFu)

// CSI2_SYSCONFIG
#define CSI2_SYSCONFIG_MSTANDBY_MODE_SHIFT (0x000Cu)
#define CSI2_SYSCONFIG_MSTANDBY_MODE_MASK (0x3000u)

#define CSI2_SYSCONFIG_SOFT_RESET_SHIFT (0x0001u)
#define CSI2_SYSCONFIG_SOFT_RESET_MASK (0x0002u)

#define CSI2_SYSCONFIG_AUTO_IDLE_SHIFT (0x0000u)
#define CSI2_SYSCONFIG_AUTO_IDLE_MASK (0x0001u)

// CSI2_SYSSTATUS
#define CSI2_SYSSTATUS_RESET_DONE_SHIFT	(0x0000u)
#define CSI2_SYSSTATUS_RESET_DONE_MASK	(0x0001u)

// CSI2_IRQSTATUS

#define CSI2_IRQSTATUS_OCP_ERR_IRQ_SHIFT (0x000Eu)
#define CSI2_IRQSTATUS_OCP_ERR_IRQ_MASK  (0x4000u)

#define CSI2_IRQSTATUS_SHORT_PACKET_IRQ_SHIFT (0x000Du)
#define CSI2_IRQSTATUS_SHORT_PACKET_IRQ_MASK  (0x2000u)

#define CSI2_IRQSTATUS_ECC_CORRECTION_IRQ_SHIFT (0x000Cu)
#define CSI2_IRQSTATUS_ECC_CORRECTION_IRQ_MASK (0x1000u)

#define CSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ_SHIFT (0x000Bu)
#define CSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ_MASK (0x0800u)

#define CSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ_SHIFT (0x000Au)
#define CSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ_MASK (0x0400u)

#define CSI2_IRQSTATUS_COMPLEXIO1_ERR_IRQ_SHIFT (0x0009u)
#define CSI2_IRQSTATUS_COMPLEXIO1_ERR_IRQ_MASK (0x0200u)

#define CSI2_IRQSTATUS_FIFO_OVF_IRQ_SHIFT (0x0008u)
#define CSI2_IRQSTATUS_FIFO_OVF_IRQ_MASK (0x0100u)

#define CSI2_IRQSTATUS_CONTEXT7_SHIFT (0x0007u)
#define CSI2_IRQSTATUS_CONTEXT7_MASK (0x0080u)

#define CSI2_IRQSTATUS_CONTEXT6_SHIFT (0x0006u)
#define CSI2_IRQSTATUS_CONTEXT6_MASK (0x0040u)

#define CSI2_IRQSTATUS_CONTEXT5_SHIFT (0x0005u)
#define CSI2_IRQSTATUS_CONTEXT5_MASK (0x0020u)

#define CSI2_IRQSTATUS_CONTEXT4_SHIFT (0x0004u)
#define CSI2_IRQSTATUS_CONTEXT4_MASK (0x0010u)

#define CSI2_IRQSTATUS_CONTEXT3_SHIFT (0x0003u)
#define CSI2_IRQSTATUS_CONTEXT3_MASK (0x0008u)

#define CSI2_IRQSTATUS_CONTEXT2_SHIFT (0x0002u)
#define CSI2_IRQSTATUS_CONTEXT2_MASK (0x0004u)

#define CSI2_IRQSTATUS_CONTEXT1_SHIFT (0x0001u)
#define CSI2_IRQSTATUS_CONTEXT1_MASK (0x0002u)

#define CSI2_IRQSTATUS_CONTEXT0_SHIFT (0x0000u)
#define CSI2_IRQSTATUS_CONTEXT0_MASK (0x0001u)

// CSI2_IRQENABLE

#define CSI2_IRQENABLE_OCP_ERR_IRQ_SHIFT (0x000Eu)
#define CSI2_IRQENABLE_OCP_ERR_IRQ_MASK  (0x4000u)

#define CSI2_IRQENABLE_SHORT_PACKET_IRQ_SHIFT (0x000Du)
#define CSI2_IRQENABLE_SHORT_PACKET_IRQ_MASK  (0x2000u)

#define CSI2_IRQENABLE_ECC_CORRECTION_IRQ_SHIFT (0x000Cu)
#define CSI2_IRQENABLE_ECC_CORRECTION_IRQ_MASK (0x1000u)

#define CSI2_IRQENABLE_ECC_NO_CORRECTION_IRQ_SHIFT (0x000Bu)
#define CSI2_IRQENABLE_ECC_NO_CORRECTION_IRQ_MASK (0x0800u)

#define CSI2_IRQENABLE_COMPLEXIO2_ERR_IRQ_SHIFT (0x000Au)
#define CSI2_IRQENABLE_COMPLEXIO2_ERR_IRQ_MASK (0x0400u)

#define CSI2_IRQENABLE_COMPLEXIO1_ERR_IRQ_SHIFT (0x0009u)
#define CSI2_IRQENABLE_COMPLEXIO1_ERR_IRQ_MASK (0x0200u)

#define CSI2_IRQENABLE_FIFO_OVF_IRQ_SHIFT (0x0008u)
#define CSI2_IRQENABLE_FIFO_OVF_IRQ_MASK (0x0100u)

#define CSI2_IRQENABLE_CONTEXT7_SHIFT (0x0007u)
#define CSI2_IRQENABLE_CONTEXT7_MASK (0x0080u)

#define CSI2_IRQENABLE_CONTEXT6_SHIFT (0x0006u)
#define CSI2_IRQENABLE_CONTEXT6_MASK (0x0040u)

#define CSI2_IRQENABLE_CONTEXT5_SHIFT (0x0005u)
#define CSI2_IRQENABLE_CONTEXT5_MASK (0x0020u)

#define CSI2_IRQENABLE_CONTEXT4_SHIFT (0x0004u)
#define CSI2_IRQENABLE_CONTEXT4_MASK (0x0010u)

#define CSI2_IRQENABLE_CONTEXT3_SHIFT (0x0003u)
#define CSI2_IRQENABLE_CONTEXT3_MASK (0x0008u)

#define CSI2_IRQENABLE_CONTEXT2_SHIFT (0x0002u)
#define CSI2_IRQENABLE_CONTEXT2_MASK (0x0004u)

#define CSI2_IRQENABLE_CONTEXT1_SHIFT (0x0001u)
#define CSI2_IRQENABLE_CONTEXT1_MASK (0x0002u)

#define CSI2_IRQENABLE_CONTEXT0_SHIFT (0x0000u)
#define CSI2_IRQENABLE_CONTEXT0_MASK (0x0001u)

// CSI2_CTRL

#define CSI2_CTRL_MFLAG_LEVH_SHIFT (0x0014u)
#define CSI2_CTRL_MFLAG_LEVH_MASK  (0x00700000u)

#define CSI2_CTRL_MFLAG_LEVL_SHIFT (0x0011u)
#define CSI2_CTRL_MFLAG_LEVL_MASK (0x000E0000u)

#define CSI2_CTRL_BURST_SIZE_EXPAND_SHIFT (0x0010u)
#define CSI2_CTRL_BURST_SIZE_EXPAND_MASK (0x00010000u)

#define CSI2_CTRL_VP_CLK_EN_SHIFT (0x000Fu)
#define CSI2_CTRL_VP_CLK_EN_MASK (0x00008000u)

#define CSI2_CTRL_STREAMING_SHIFT (0x000Eu)
#define CSI2_CTRL_STREAMING_MASK (0x00004000u)

#define CSI2_CTRL_NON_POSTED_WRITE_SHIFT (0x000Du)
#define CSI2_CTRL_NON_POSTED_WRITE_MASK (0x00002000u)

#define CSI2_CTRL_VP_ONLY_EN_SHIFT (0x000Bu)
#define CSI2_CTRL_VP_ONLY_EN_MASK (0x00000800u)

#define CSI2_CTRL_STREAMING_32_BIT_SHIFT (0x000Au)
#define CSI2_CTRL_STREAMING_32_BIT_MASK (0x00000400u)

#define CSI2_CTRL_VP_OUT_CTRL_SHIFT (0x0008u)
#define CSI2_CTRL_VP_OUT_CTRL_MASK (0x00000300u)

#define CSI2_CTRL_DBG_EN_SHIFT (0x0007u)
#define CSI2_CTRL_DBG_EN_MASK (0x00000080u)

#define CSI2_CTRL_BURST_SIZE_SHIFT (0x0005u)
#define CSI2_CTRL_BURST_SIZE_MASK (0x00000060u)

#define CSI2_CTRL_ENDIANNESS_SHIFT (0x0004u)
#define CSI2_CTRL_ENDIANNESS_MASK (0x00000010u)

#define CSI2_CTRL_FRAME_SHIFT (0x0003u)
#define CSI2_CTRL_FRAME_MASK (0x00000008u)

#define CSI2_CTRL_ECC_EN_SHIFT (0x0002u)
#define CSI2_CTRL_ECC_EN_MASK (0x00000004u)

#define CSI2_CTRL_SECURE_SHIFT (0x0001u)
#define CSI2_CTRL_SECURE_MASK (0x00000002u)

#define CSI2_CTRL_IF_EN_SHIFT (0x0000u)
#define CSI2_CTRL_IF_EN_MASK (0x00000001u)

// CSI2_DBG_H
#define CSI2_DBG_H_DBG_SHIFT (0x0000u)
#define CSI2_DBG_H_DBG_MASK (0xFFFFFFFFu)

// CSI2_DBG_P
#define CSI2_DBG_P_DBG_SHIFT (0x0000u)
#define CSI2_DBG_P_DBG_MASK (0xFFFFFFFFu)

// CSI2_GNQ
#define CSI2_GNQ_FIFODEPTH_SHIFT (0x0002u)
#define CSI2_GNQ_FIFODEPTH_MASK (0x003Cu)

#define CSI2_GNQ_NBCONTEXTS_SHIFT (0x0000u)
#define CSI2_GNQ_NBCONTEXTS_MASK (0x0003u)

// CSI2_COMPLEXIO_CFG

#define CSI2_COMPLEXIO_CFG_RESET_CTRL_SHIFT (0x001Eu)
#define CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK (0x40000000u)

#define CSI2_COMPLEXIO_CFG_RESET_DONE_SHIFT (0x001Du)
#define CSI2_COMPLEXIO_CFG_RESET_DONE_MASK (0x20000000u)

#define CSI2_COMPLEXIO_CFG_PWR_CMD_SHIFT (0x001Bu)
#define CSI2_COMPLEXIO_CFG_PWR_CMD_MASK (0x18000000u)

#define CSI2_COMPLEXIO_CFG_PWR_STATUS_SHIFT (0x0019u)
#define CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK (0x06000000u)

#define CSI2_COMPLEXIO_CFG_PWR_AUTO_SHIFT (0x0018u)
#define CSI2_COMPLEXIO_CFG_PWR_AUTO_MASK (0x01000000u)

#define CSI2_COMPLEXIO_CFG_DATA4_POL_SHIFT (0x0013u)
#define CSI2_COMPLEXIO_CFG_DATA4_POL_MASK (0x00080000u)

#define CSI2_COMPLEXIO_CFG_DATA4_POSITION_SHIFT (0x0010u)
#define CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK (0x00070000u)

#define CSI2_COMPLEXIO_CFG_DATA3_POL_SHIFT (0x000Fu)
#define CSI2_COMPLEXIO_CFG_DATA3_POL_MASK (0x00008000u)

#define CSI2_COMPLEXIO_CFG_DATA3_POSITION_SHIFT (0x000Cu)
#define CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK (0x00007000u)

#define CSI2_COMPLEXIO_CFG_DATA2_POL_SHIFT (0x000Bu)
#define CSI2_COMPLEXIO_CFG_DATA2_POL_MASK (0x00000800u)

#define CSI2_COMPLEXIO_CFG_DATA2_POSITION_SHIFT (0x0008u)
#define CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK (0x00000700u)

#define CSI2_COMPLEXIO_CFG_DATA1_POL_SHIFT (0x0007u)
#define CSI2_COMPLEXIO_CFG_DATA1_POL_MASK (0x00000080u)

#define CSI2_COMPLEXIO_CFG_DATA1_POSITION_SHIFT (0x0004u)
#define CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK (0x00000070u)

#define CSI2_COMPLEXIO_CFG_CLOCK_POL_SHIFT (0x0003u)
#define CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK (0x00000008u)

#define CSI2_COMPLEXIO_CFG_CLOCK_POSITION_SHIFT (0x0000u)
#define CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK (0x00000007u)

// CSI2_COMPLEXIO_IRQSTATUS

#define CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMEXIT_SHIFT (0x001Au)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMEXIT_MASK (0x04000000u)

#define CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMENTER_SHIFT (0x0019u)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMENTER_MASK (0x02000000u)

#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM5_SHIFT (0x0018u)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM5_MASK (0x01000000u)

#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM4_SHIFT (0x0017u)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM4_MASK (0x00800000u)

#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM3_SHIFT (0x0016u)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM3_MASK (0x00400000u)

#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM2_SHIFT (0x0015u)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM2_MASK (0x00200000u)

#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM1_SHIFT (0x0014u)
#define CSI2_COMPLEXIO_IRQSTATUS_STATEULPM1_MASK (0x00100000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL5_SHIFT (0x0013u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL5_MASK (0x00080000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL4_SHIFT (0x0012u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL4_MASK (0x00040000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL3_SHIFT (0x0011u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL3_MASK (0x00020000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL2_SHIFT (0x0010u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL2_MASK (0x00010000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL1_SHIFT (0x000Fu)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL1_MASK (0x00008000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC5_SHIFT (0x000Eu)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC5_MASK (0x00004000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC4_SHIFT (0x000Du)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC4_MASK (0x00002000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC3_SHIFT (0x000Cu)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC3_MASK (0x00001000u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC2_SHIFT (0x000Bu)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC2_MASK (0x00000800u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC1_SHIFT (0x000Au)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRESC1_MASK (0x00000400u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS5_SHIFT (0x0009u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS5_MASK (0x00000200u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS4_SHIFT (0x0008u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS4_MASK (0x00000100u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS3_SHIFT (0x0007u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS3_MASK (0x00000080u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS2_SHIFT (0x0006u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS2_MASK (0x00000040u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS1_SHIFT (0x0005u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS1_MASK (0x00000020u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS5_SHIFT (0x0004u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS5_MASK (0x00000010u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS4_SHIFT (0x0003u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS4_MASK (0x00000008u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS3_SHIFT (0x0002u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS3_MASK (0x00000004u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS2_SHIFT (0x0001u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS2_MASK (0x00000002u)

#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS1_SHIFT (0x0000u)
#define CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS1_MASK (0x00000001u)

// CSI2_SHORT_PACKET
#define CSI2_SHORT_PACKET_SHORT_PACKET_SHIFT (0x0000u)
#define CSI2_SHORT_PACKET_SHORT_PACKET_MASK (0x00FFFFFFu)

// CSI2_COMPLEXIO_IRQENABLE

#define CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMEXIT_SHIFT (0x001Au)
#define CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMEXIT_MASK (0x04000000u)

#define CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMENTER_SHIFT (0x0019u)
#define CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMENTER_MASK (0x02000000u)

#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM5_SHIFT (0x0018u)
#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM5_MASK (0x01000000u)

#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM4_SHIFT (0x0017u)
#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM4_MASK (0x00800000u)

#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM3_SHIFT (0x0016u)
#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM3_MASK (0x00400000u)

#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM2_SHIFT (0x0015u)
#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM2_MASK (0x00200000u)

#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM1_SHIFT (0x0014u)
#define CSI2_COMPLEXIO_IRQENABLE_STATEULPM1_MASK (0x00100000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL5_SHIFT (0x0013u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL5_MASK (0x00080000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL4_SHIFT (0x0012u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL4_MASK (0x00040000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL3_SHIFT (0x0011u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL3_MASK (0x00020000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL2_SHIFT (0x0010u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL2_MASK (0x00010000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL1_SHIFT (0x000Fu)
#define CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL1_MASK (0x00008000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRESC5_SHIFT (0x000Eu)
#define CSI2_COMPLEXIO_IRQENABLE_ERRESC5_MASK (0x00004000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRESC4_SHIFT (0x000Du)
#define CSI2_COMPLEXIO_IRQENABLE_ERRESC4_MASK (0x00002000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRESC3_SHIFT (0x000Cu)
#define CSI2_COMPLEXIO_IRQENABLE_ERRESC3_MASK (0x00001000u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRESC2_SHIFT (0x000Bu)
#define CSI2_COMPLEXIO_IRQENABLE_ERRESC2_MASK (0x00000800u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRESC1_SHIFT (0x000Au)
#define CSI2_COMPLEXIO_IRQENABLE_ERRESC1_MASK (0x00000400u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS5_SHIFT (0x0009u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS5_MASK (0x00000200u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS4_SHIFT (0x0008u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS4_MASK (0x00000100u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS3_SHIFT (0x0007u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS3_MASK (0x00000080u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS2_SHIFT (0x0006u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS2_MASK (0x00000040u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS1_SHIFT (0x0005u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS1_MASK (0x00000020u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS5_SHIFT (0x0004u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS5_MASK (0x00000010u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS4_SHIFT (0x0003u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS4_MASK (0x00000008u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS3_SHIFT (0x0002u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS3_MASK (0x00000004u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS2_SHIFT (0x0001u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS2_MASK (0x00000002u)

#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS1_SHIFT (0x0000u)
#define CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS1_MASK (0x00000001u)

// CSI2_TIMING

#define CSI2_TIMING_FORCE_RX_MODE_IO2_SHIFT (0x001Fu)
#define CSI2_TIMING_FORCE_RX_MODE_IO2_MASK (0x80000000u)

#define CSI2_TIMING_STOP_STATE_X16_IO2_SHIFT (0x001Eu)
#define CSI2_TIMING_STOP_STATE_X16_IO2_MASK (0x40000000u)

#define CSI2_TIMING_STOP_STATE_X4_IO2_SHIFT (0x001Du)
#define CSI2_TIMING_STOP_STATE_X4_IO2_MASK (0x20000000u)

#define CSI2_TIMING_STOP_STATE_COUNTER_IO2_SHIFT (0x0010u)
#define CSI2_TIMING_STOP_STATE_COUNTER_IO2_MASK (0x1FFF0000u)

#define CSI2_TIMING_FORCE_RX_MODE_IO1_SHIFT (0x000Fu)
#define CSI2_TIMING_FORCE_RX_MODE_IO1_MASK (0x00008000u)

#define CSI2_TIMING_STOP_STATE_X16_IO1_SHIFT (0x000Eu)
#define CSI2_TIMING_STOP_STATE_X16_IO1_MASK (0x00004000u)

#define CSI2_TIMING_STOP_STATE_X4_IO1_SHIFT (0x000Du)
#define CSI2_TIMING_STOP_STATE_X4_IO1_MASK (0x00002000u)

#define CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT (0x0000u)
#define CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK (0x00001FFFu)

// CSI2_CTX_CTRL1 

#define CSI2_CTX_CTRL1_BYTESWAP_SHIFT (0x001Fu)
#define CSI2_CTX_CTRL1_BYTESWAP_MASK (0x80000000u)

#define CSI2_CTX_CTRL1_GENERIC_SHIFT (0x001Eu)
#define CSI2_CTX_CTRL1_GENERIC_MASK (0x40000000u)

#define CSI2_CTX_CTRL1_TRANSCODE_SHIFT (0x0018u)
#define CSI2_CTX_CTRL1_TRANSCODE_MASK (0x0F000000u)

#define CSI2_CTX_CTRL1_FEC_NUMBER_SHIFT (0x0010u)
#define CSI2_CTX_CTRL1_FEC_NUMBER_MASK (0x00FF0000u)

#define CSI2_CTX_CTRL1_COUNT_SHIFT (0x0008u)
#define CSI2_CTX_CTRL1_COUNT_MASK (0x0000FF00u)

#define CSI2_CTX_CTRL1_EOF_EN_SHIFT (0x0007u)
#define CSI2_CTX_CTRL1_EOF_EN_MASK (0x00000080u)

#define CSI2_CTX_CTRL1_EOL_EN_SHIFT (0x0006u)
#define CSI2_CTX_CTRL1_EOL_EN_MASK (0x00000040u)

#define CSI2_CTX_CTRL1_CS_EN_SHIFT (0x0005u)
#define CSI2_CTX_CTRL1_CS_EN_MASK (0x00000020u)

#define CSI2_CTX_CTRL1_COUNT_UNLOCK_SHIFT (0x0004u)
#define CSI2_CTX_CTRL1_COUNT_UNLOCK_MASK (0x00000010u)

#define CSI2_CTX_CTRL1_PING_PONG_SHIFT (0x0003u)
#define CSI2_CTX_CTRL1_PING_PONG_MASK (0x00000008u)

#define CSI2_CTX_CTRL1_VP_FORCE_SHIFT (0x0002u)
#define CSI2_CTX_CTRL1_VP_FORCE_MASK (0x00000004u)

#define CSI2_CTX_CTRL1_LINE_MODULO_SHIFT (0x0001u)
#define CSI2_CTX_CTRL1_LINE_MODULO_MASK (0x00000002u)

#define CSI2_CTX_CTRL1_CTX_EN_SHIFT (0x0000u)
#define CSI2_CTX_CTRL1_CTX_EN_MASK (0x00000001u)

// CSI2_CTX_CTRL2
#define CSI2_CTX_CTRL2_FRAME_SHIFT (0x0010u)
#define CSI2_CTX_CTRL2_FRAME_MASK (0xFFFF0000u)

#define CSI2_CTX_CTRL2_USER_DEF_MAPPING_SHIFT (0x000Du)
#define CSI2_CTX_CTRL2_USER_DEF_MAPPING_MASK (0x00006000u)

#define CSI2_CTX_CTRL2_VIRTUAL_ID_SHIFT (0x000Bu)
#define CSI2_CTX_CTRL2_VIRTUAL_ID_MASK (0x00001800u)

#define CSI2_CTX_CTRL2_DPCM_PRED_SHIFT (0x000Au)
#define CSI2_CTX_CTRL2_DPCM_PRED_MASK (0x00000400u)

#define CSI2_CTX_CTRL2_FORMAT_SHIFT (0x0000u)
#define CSI2_CTX_CTRL2_FORMAT_MASK (0x000003FFu)

// CSI2_CTX_CTRL3
#define CSI2_CTX_CTRL3_ALPHA_SHIFT (0x0010u)
#define CSI2_CTX_CTRL3_ALPHA_MASK (0x3FFF0000u)

#define CSI2_CTX_CTRL3_LINE_NUMBER_SHIFT (0x0000u)
#define CSI2_CTX_CTRL3_LINE_NUMBER_MASK (0x0000FFFFu)

// CSI2_CTX_DAT_OFST
#define CSI2_CTX_DAT_OFST_OFST_SHIFT (0x0000u)
#define CSI2_CTX_DAT_OFST_OFST_MASK (0xFFFFFFFFu)

// CSI2_CTX_DAT_PING_ADDR
#define CSI2_CTX_DAT_PING_ADDR_SHIFT (0x0000u)
#define CSI2_CTX_DAT_PING_ADDR_MASK (0xFFFFFFFFu)

// CSI2_CTX_DAT_PONG_ADDR
#define CSI2_CTX_DAT_PONG_ADDR_SHIFT (0x0000u)
#define CSI2_CTX_DAT_PONG_ADDR_MASK (0xFFFFFFFFu)

// CSI2_CTX_IRQENABLE
#define CSI2_CTX_IRQENABLE_ECC_CORRECTION_IRQ_SHIFT (0x0008u)
#define CSI2_CTX_IRQENABLE_ECC_CORRECTION_IRQ_MASK (0x00000100u)

#define CSI2_CTX_IRQENABLE_LINE_NUMBER_IRQ_SHIFT (0x0007u)
#define CSI2_CTX_IRQENABLE_LINE_NUMBER_IRQ_MASK (0x00000080u)

#define CSI2_CTX_IRQENABLE_FRAME_NUMBER_IRQ_SHIFT (0x0006u)
#define CSI2_CTX_IRQENABLE_FRAME_NUMBER_IRQ_MASK (0x00000040u)

#define CSI2_CTX_IRQENABLE_CS_IRQ_SHIFT (0x0005u)
#define CSI2_CTX_IRQENABLE_CS_IRQ_MASK (0x00000020u)

#define CSI2_CTX_IRQENABLE_LE_IRQ_SHIFT (0x0003u)
#define CSI2_CTX_IRQENABLE_LE_IRQ_MASK (0x00000008u)

#define CSI2_CTX_IRQENABLE_LS_IRQ_SHIFT (0x0002u)
#define CSI2_CTX_IRQENABLE_LS_IRQ_MASK (0x00000004u)

#define CSI2_CTX_IRQENABLE_FE_IRQ_SHIFT (0x0001u)
#define CSI2_CTX_IRQENABLE_FE_IRQ_MASK (0x00000002u)

#define CSI2_CTX_IRQENABLE_FS_IRQ_SHIFT (0x0000u)
#define CSI2_CTX_IRQENABLE_FS_IRQ_MASK (0x00000001u)

// CSI2_CTX_IRQSTATUS
#define CSI2_CTX_IRQSTATUS_ECC_CORRECTION_IRQ_SHIFT (0x0008u)
#define CSI2_CTX_IRQSTATUS_ECC_CORRECTION_IRQ_MASK (0x00000100u)

#define CSI2_CTX_IRQSTATUS_LINE_NUMBER_IRQ_SHIFT (0x0007u)
#define CSI2_CTX_IRQSTATUS_LINE_NUMBER_IRQ_MASK (0x00000080u)

#define CSI2_CTX_IRQSTATUS_FRAME_NUMBER_IRQ_SHIFT (0x0006u)
#define CSI2_CTX_IRQSTATUS_FRAME_NUMBER_IRQ_MASK (0x00000040u)

#define CSI2_CTX_IRQSTATUS_CS_IRQ_SHIFT (0x0005u)
#define CSI2_CTX_IRQSTATUS_CS_IRQ_MASK (0x00000020u)

#define CSI2_CTX_IRQSTATUS_LE_IRQ_SHIFT (0x0003u)
#define CSI2_CTX_IRQSTATUS_LE_IRQ_MASK (0x00000008u)

#define CSI2_CTX_IRQSTATUS_LS_IRQ_SHIFT (0x0002u)
#define CSI2_CTX_IRQSTATUS_LS_IRQ_MASK (0x00000004u)

#define CSI2_CTX_IRQSTATUS_FE_IRQ_SHIFT (0x0001u)
#define CSI2_CTX_IRQSTATUS_FE_IRQ_MASK (0x00000002u)

#define CSI2_CTX_IRQSTATUS_FS_IRQ_SHIFT (0x0000u)
#define CSI2_CTX_IRQSTATUS_FS_IRQ_MASK (0x00000001u)

// CSI2_PHY_CFG
#define CSI2_PHY_CFG_SHIFT (0x0000u)
#define CSI2_PHY_CFG_MASK (0xFFFFFFFFu)

// CSI2_CTX_TRANSCODEH
#define CSI2_CTX_TRANSCODEH_HCOUNT_SHIFT (0x0010u)
#define CSI2_CTX_TRANSCODEH_HCOUNT_MASK (0x1FFF0000u)

#define CSI2_CTX_TRANSCODEH_HSKIP_SHIFT (0x0000u)
#define CSI2_CTX_TRANSCODEH_HSKIP_MASK (0x00001FFFu)

// CSI2_CTX_TRANSCODEV
#define CSI2_CTX_TRANSCODEV_VCOUNT_SHIFT (0x0010u)
#define CSI2_CTX_TRANSCODEV_VCOUNT_MASK (0x1FFF0000u)

#define CSI2_CTX_TRANSCODEV_VSKIP_SHIFT (0x0000u)
#define CSI2_CTX_TRANSCODEV_VSKIP_MASK (0x00001FFFu)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif