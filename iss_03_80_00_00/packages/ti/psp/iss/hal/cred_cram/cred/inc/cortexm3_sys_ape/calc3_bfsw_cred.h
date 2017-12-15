/** ==================================================================
 *  @file   calc3_bfsw_cred.h                                                  
 *                                                                    
 *  @path   /ti/psp/iss/hal/cred_cram/cred/inc/cortexm3_sys_ape/                                                  
 *                                                                    
 *  @desc   This  File contains.                                      
 * ===================================================================
 *  Copyright (c) Texas Instruments Inc 2011, 2012                    
 *                                                                    
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===================================================================*/

/* ============================================================================ 
 * TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION Property of Texas
 * Instruments For Unrestricted Internal Use Only Unauthorized reproduction
 * and/or distribution is strictly prohibited.  This product is protected
 * under copyright law and trade secret law as an unpublished work.  Created
 * 2008, (C) Copyright 2008 Texas Instruments.  All rights reserved. */

/**
 *  @Component:   CALC3_BFSW
 *
 *  @Filename:    calc3_bfsw_cred.h
 *
 *  @Description: Component description is not available
 *
 *  Generated by: Socrates CRED generator prototype
 *
    *//* ====================================================================== */

#ifndef __CALC3_BFSW_CRED_H
#define __CALC3_BFSW_CRED_H

#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * Instance CALC3_CFG__BFSW of component CALC3_BFSW mapped in MONICA at address 0x5A058200
     */

                                                                              /*-------------------------------------------------------------------------*//**
 * @DEFINITION   BITFIELD
 *
 * @BRIEF        The bitfield must be defined according to register width
 *               of the component - 64/32/16/8
 *
    *//*------------------------------------------------------------------------ */
#undef BITFIELD
#define BITFIELD BITFIELD_32

    /* 
     *  List of Register arrays for component CALC3_BFSW
     *
     */

    /* 
     *  List of bundle arrays for component CALC3_BFSW
     *
     */

    /* 
     *  List of bundles for component CALC3_BFSW
     *
     */

    /* 
     * List of registers for component CALC3_BFSW
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__VIEWMODE
 *
 * @BRIEF        View Mode Register. 
 *               It selects full-view mode or ping-pong view mode. 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__VIEWMODE                               0x0ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID1
 *
 * @BRIEF        Master ID 1 Register 
 *               Select master between HWA and DMA bus. 
 *               This register is used in both full view and ping-pong view 
 *               mode. 
 *               This register is for buffers which has two physical 
 *               memories. 
 *               This register is affected by direct_switch_pi input port. 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID1                                 0x4ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID2
 *
 * @BRIEF        Master ID 1 Register 
 *               Select master between HWA and DMA bus. 
 *               This register is for buffers which has only one physical 
 *               memory. 
 *               This register is NOT affected by direct_switch_pi input 
 *               port. 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID2                                 0x8ul

    /* 
     * List of register bitfields for component CALC3_BFSW
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__VIEWMODE__RSRV   
 *
 * @BRIEF        Reserved. 
 *               '0' will be returned at Read, and Write will be ignored. - 
 *               (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__VIEWMODE__RSRV                    BITFIELD(31, 2)
#define CALC3_BFSW__VIEWMODE__RSRV__POS               2

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__VIEWMODE__VIEW_CALCROBUF   
 *
 * @BRIEF        View mode selection for calcrobuf. 
 *               When '0', full view mode is selected. 
 *               When '1', ping-pong view mode is selected. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__VIEWMODE__VIEW_CALCROBUF          BITFIELD(1, 1)
#define CALC3_BFSW__VIEWMODE__VIEW_CALCROBUF__POS     1

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__VIEWMODE__VIEW_CALCRPBUF   
 *
 * @BRIEF        View mode selection for calcrpbuf. 
 *               When '0', full view mode is selected. 
 *               When '1', ping-pong view mode is selected. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__VIEWMODE__VIEW_CALCRPBUF          BITFIELD(0, 0)
#define CALC3_BFSW__VIEWMODE__VIEW_CALCRPBUF__POS     0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID1__RSRV   
 *
 * @BRIEF        Reserved. 
 *               '0' will be returned at Read, and Write will be ignored. - 
 *               (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID1__RSRV                      BITFIELD(31, 4)
#define CALC3_BFSW__MSTID1__RSRV__POS                 4

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID1__MST_CALCROBUF_B   
 *
 * @BRIEF        Master selection for calcrobuf B. 
 *               This bit is used in only ping-pong view mode. 
 *               when '0', buffer B is assigned to DMA 
 *               when '1', buffer B is assigned to HWA. 
 *               This bit has no effect in full view mode. 
 *               If direct_switch_pi is high, the value of this bit is 
 *               inverted. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID1__MST_CALCROBUF_B           BITFIELD(3, 3)
#define CALC3_BFSW__MSTID1__MST_CALCROBUF_B__POS      3

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID1__MST_CALCROBUF_A   
 *
 * @BRIEF        Master selection for calcrobuf A. 
 *               This bit is used in both full view and ping-pong view mode. 
 *               In full viw mode, 
 *               when '0', both buffer A and B are assigned to DMA 
 *               when '1', both buffer A and B are assigned to HWA. 
 *               In ping-pong view mode, 
 *               when '0', buffer A is assigned to DMA 
 *               when '1', buffer A is assigned to HWA. 
 *               (Buffer B is not affected in ping-pong view mode.) 
 *               If direct_switch_pi is high, the value of this bit is 
 *               inverted. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID1__MST_CALCROBUF_A           BITFIELD(2, 2)
#define CALC3_BFSW__MSTID1__MST_CALCROBUF_A__POS      2

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID1__MST_CALCRPBUF_B   
 *
 * @BRIEF        Master selection for calcrpbuf B. 
 *               This bit is used in only ping-pong view mode. 
 *               when '0', buffer B is assigned to DMA 
 *               when '1', buffer B is assigned to HWA. 
 *               This bit has no effect in full view mode. 
 *               If direct_switch_pi is high, the value of this bit is 
 *               inverted. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID1__MST_CALCRPBUF_B           BITFIELD(1, 1)
#define CALC3_BFSW__MSTID1__MST_CALCRPBUF_B__POS      1

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID1__MST_CALCRPBUF_A   
 *
 * @BRIEF        Master selection for calcrpbuf A. 
 *               This bit is used in both full view and ping-pong view mode. 
 *               In full viw mode, 
 *               when '0', both buffer A and B are assigned to DMA 
 *               when '1', both buffer A and B are assigned to HWA. 
 *               In ping-pong view mode, 
 *               when '0', buffer A is assigned to DMA 
 *               when '1', buffer A is assigned to HWA. 
 *               (Buffer B is not affected in ping-pong view mode.) 
 *               If direct_switch_pi is high, the value of this bit is 
 *               inverted. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID1__MST_CALCRPBUF_A           BITFIELD(0, 0)
#define CALC3_BFSW__MSTID1__MST_CALCRPBUF_A__POS      0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID2__RSRV   
 *
 * @BRIEF        Reserved. 
 *               '0' will be returned at Read, and Write will be ignored. - 
 *               (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID2__RSRV                      BITFIELD(31, 2)
#define CALC3_BFSW__MSTID2__RSRV__POS                 2

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID2__MST_CALCWBUF   
 *
 * @BRIEF        Master selection for calcwbuf. 
 *               when '0', the buffer is assigned to DMA 
 *               when '1', the buffer is assigned to HWA. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID2__MST_CALCWBUF              BITFIELD(1, 1)
#define CALC3_BFSW__MSTID2__MST_CALCWBUF__POS         1

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   CALC3_BFSW__MSTID2__MST_CALCQBUF   
 *
 * @BRIEF        Master selection for calcqbuf. 
 *               when '0', the buffer is assigned to DMA 
 *               when '1', the buffer is assigned to HWA. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define CALC3_BFSW__MSTID2__MST_CALCQBUF              BITFIELD(0, 0)
#define CALC3_BFSW__MSTID2__MST_CALCQBUF__POS         0

    /* 
     * List of register bitfields values for component CALC3_BFSW
     *
     */

#ifdef __cplusplus
}
#endif
#endif                                                     /* __CALC3_BFSW_CRED_H 
                                                            */
