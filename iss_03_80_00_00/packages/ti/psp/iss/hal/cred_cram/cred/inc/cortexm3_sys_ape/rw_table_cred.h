/** ==================================================================
 *  @file   rw_table_cred.h                                                  
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
 *  @Component:   RW_TABLE
 *
 *  @Filename:    rw_table_cred.h
 *
 *  @Description: Component description is not available
 *
 *  Generated by: Socrates CRED generator prototype
 *
    *//* ====================================================================== */

#ifndef __RW_TABLE_CRED_H
#define __RW_TABLE_CRED_H

#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * Instance RW_TABLE_CPU1 of component RW_TABLE mapped in MONICA at address 0xE00FE000
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
     *  List of Register arrays for component RW_TABLE
     *
     */

    /* 
     *  List of bundle arrays for component RW_TABLE
     *
     */

    /* 
     *  List of bundles for component RW_TABLE
     *
     */

    /* 
     * List of registers for component RW_TABLE
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DUCATI_RW_PID1
 *
 * @BRIEF        Register description is not available
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DUCATI_RW_PID1                           0x0ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DUCATI_RW_PID2
 *
 * @BRIEF        Register description is not available
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DUCATI_RW_PID2                           0x4ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DMLED_SW_CTRL_REG
 *
 * @BRIEF        Reserved for DMLED testing 
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DMLED_SW_CTRL_REG                        0x8ul

    /* 
     * List of register bitfields for component RW_TABLE
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DUCATI_RW_PID1__BASEADD1   
 *
 * @BRIEF        Bitfield description is not available - (RW)
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DUCATI_RW_PID1__BASEADD1            BITFIELD(31, 0)
#define RW_TABLE__DUCATI_RW_PID1__BASEADD1__POS       0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DUCATI_RW_PID2__BASEADD2   
 *
 * @BRIEF        Bitfield description is not available - (RW)
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DUCATI_RW_PID2__BASEADD2            BITFIELD(31, 0)
#define RW_TABLE__DUCATI_RW_PID2__BASEADD2__POS       0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DMLED_SW_CTRL_REG__SYNCBIT   
 *
 * @BRIEF        Reset depending upon PIN - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DMLED_SW_CTRL_REG__SYNCBIT          BITFIELD(2, 2)
#define RW_TABLE__DMLED_SW_CTRL_REG__SYNCBIT__POS     2

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DMLED_SW_CTRL_REG__EXECBIT   
 *
 * @BRIEF        Bitfield description is not available - (RW)
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DMLED_SW_CTRL_REG__EXECBIT          BITFIELD(1, 1)
#define RW_TABLE__DMLED_SW_CTRL_REG__EXECBIT__POS     1

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   RW_TABLE__DMLED_SW_CTRL_REG__STATUSBIT   
 *
 * @BRIEF        Bitfield description is not available - (RW)
 *
    *//*------------------------------------------------------------------------ */
#define RW_TABLE__DMLED_SW_CTRL_REG__STATUSBIT        BITFIELD(0, 0)
#define RW_TABLE__DMLED_SW_CTRL_REG__STATUSBIT__POS   0

    /* 
     * List of register bitfields values for component RW_TABLE
     *
     */

#ifdef __cplusplus
}
#endif
#endif                                                     /* __RW_TABLE_CRED_H 
                                                            */
