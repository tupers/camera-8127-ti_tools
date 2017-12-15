/** ==================================================================
 *  @file   lse_cred.h                                                  
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
 *  @Component:   LSE
 *
 *  @Filename:    lse_cred.h
 *
 *  @Description: Component description is not available
 *
 *  Generated by: Socrates CRED generator prototype
 *
    *//* ====================================================================== */

#ifndef __LSE_CRED_H
#define __LSE_CRED_H

#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * Instance CALC3_CFG__LSE of component LSE mapped in MONICA at address 0x5A058300
     * Instance IPE3_CFG__LSE of component LSE mapped in MONICA at address 0x5A058B00
     * Instance MC3_CFG__LSE of component LSE mapped in MONICA at address 0x5A059300
     * Instance ECD3_CFG__LSE of component LSE mapped in MONICA at address 0x5A059B00
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
     *  List of Register arrays for component LSE
     *
     */

    /* 
     *  List of bundle arrays for component LSE
     *
     */

    /* 
     *  List of bundles for component LSE
     *
     */

    /* 
     * List of registers for component LSE
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL
 *
 * @BRIEF        Controller 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL                                      0x0ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_PARAM
 *
 * @BRIEF        Parameter address for SB Bypas mode 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_PARAM                                     0x4ul

    /* 
     * List of register bitfields for component LSE
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__INT_EOS_THRU   
 *
 * @BRIEF        int_eos through bit 
 *               0 : LSE does the process for slice boundary after receiving 
 *               int_eos. 
 *               1 : int_eos is passed through to SyncBox without the process 
 *               for slice boundary. 
 *               Refer to 4.2.3. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__INT_EOS_THRU                   BITFIELD(12, 12)
#define LSE__LSE_CTRL__INT_EOS_THRU__POS              12

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__OCP_ERR   
 *
 * @BRIEF        OCP error status bit  
 *               [11]: OCP DMA IP_CORE side  
 *               [10]: OCP DMA SL2 side  
 *               [9] : OCP CFG  IP_CORE side  
 *               0: When Sresp is not ERR 
 *               1: When Sresp is ERR. 
 *                Writing 0 is ignored 
 *                These bits will remain ?1? until RESET or until Host sets 
 *               to ?1?. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__OCP_ERR                        BITFIELD(11, 9)
#define LSE__LSE_CTRL__OCP_ERR__POS                   9

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__ADPTV_VALUE   
 *
 * @BRIEF        Status Adaptv_add() value 
 *               This signal is cleared, if Token_clr=1. - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__ADPTV_VALUE                    BITFIELD(8, 8)
#define LSE__LSE_CTRL__ADPTV_VALUE__POS               8

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__TOKEN_CLR   
 *
 * @BRIEF        LSE internal signals will be initialized to understand 
 *               prologue(1st MB) as below:  . 
 *                -token status signal  
 *                -token  start/end signal 
 *                -DMA pointer 
 *               Writing 0 is ignored. 
 *               Writing 1 will clear some internal signal. 
 *               This is a ?self clearing? bit. The host will always read 
 *               ?0?. 
 *               If this is not used for initialization at prologue, some 
 *               internal signal is kept. And also, synchronization does not 
 *               function well - (WO) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__TOKEN_CLR                      BITFIELD(7, 7)
#define LSE__LSE_CTRL__TOKEN_CLR__POS                 7

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__SSM   
 *
 * @BRIEF        Single Step Mode 
 *               1 : Enable Single Step Mdde 
 *               0 : Normal Mode - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__SSM                            BITFIELD(6, 6)
#define LSE__LSE_CTRL__SSM__POS                       6

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__BFSW_CHG_DIS   
 *
 * @BRIEF        Disabled internal BFSW change 
 *               0 : Enable internal bfsw change (default) Then, LSE controls 
 *               BFSW after LD task finshed. 
 *               1 : Disable BFSW change (If Host want to control BFSW with 
 *               each task step by step with LD_GO, Comp_GO and ST_GO.) - 
 *               (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__BFSW_CHG_DIS                   BITFIELD(5, 5)
#define LSE__LSE_CTRL__BFSW_CHG_DIS__POS              5

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__CSB   
 *
 * @BRIEF        Command Status Bit 
 *               0 : LSE command is defined 
 *               1 : LSE command is undefined 
 *               Writing 0 is ignored 
 *               These bits will remain ?1? until RESET or Token_clr or until 
 *               Host sets to ?1?. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__CSB                            BITFIELD(4, 4)
#define LSE__LSE_CTRL__CSB__POS                       4

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__LD_GO   
 *
 * @BRIEF        Execute LOAD task on Byps mode 
 *                Target ParamAddr_ld_byps need to set before this bit is 
 *               set.? 
 *               1:  Execute ?LD task?.  
 *                   LSE access to ParamAddr_ld_byps and execute the command 
 *               for LOAD task.  
 *               0 : Idle 
 *                 
 *               Writing 0 is ignored  
 *               This bit is cleared after LD Task finished. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__LD_GO                          BITFIELD(3, 3)
#define LSE__LSE_CTRL__LD_GO__POS                     3

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__COMP_GO   
 *
 * @BRIEF        Execute Comp task on Byps mode 
 *               1:  Execute ?Comp task?.  
 *                   In the single step mode, LSE access to ParamAddr_ld_byps 
 *               and execute the command for Comp task. In the normal mode, 
 *               LSE executes COMP commands followed by LD commands. 
 *               0 : Idle 
 *               Writing 0 is ignored 
 *               This bit is cleared after Comp Task finished. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__COMP_GO                        BITFIELD(2, 2)
#define LSE__LSE_CTRL__COMP_GO__POS                   2

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__ST_GO   
 *
 * @BRIEF        Execute Store task on Byps mode 
 *               Target ParamAddr_st_byps need to set before this bit is 
 *               set.? 
 *               1:  Execute ?Store task?.  
 *                   LSE access to ParamAddr_st_byps and execute the command 
 *               for Store task.  
 *               0 : Idle 
 *               Writing 0 is ignored 
 *               This bit is cleared after ST Task finished. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__ST_GO                          BITFIELD(1, 1)
#define LSE__LSE_CTRL__ST_GO__POS                     1

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_CTRL__SB_BYPS   
 *
 * @BRIEF        Sync-Box Byps mode: 
 *               1 : LSE functions SyncBox bypass mode and executes the task 
 *               of go_bit. 
 *               0 : LSE function normal SyncBox mode and waits 
 *               NewTaskSignal.  
 *               This value should not change during execution. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_CTRL__SB_BYPS                        BITFIELD(0, 0)
#define LSE__LSE_CTRL__SB_BYPS__POS                   0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_PARAM__PARAMADDR_LD_BYPS   
 *
 * @BRIEF        Only used in the bypass mode. 
 *               Address of the first command of LD and COMP sequence 
 *               [128-bit word unit]. This is 128-bit word address, not byte 
 *               address. The conversion from byte address to 128-bit word 
 *               address should be done by CPU. 
 *               If LSE_CTRL SB_BYPS is 1, this value is used. In the bypass 
 *               mode, this address is given via this field, instead via 
 *               SyncBox  
 *               And also, this field will be used on the Single Step Mode. - 
 *               (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_PARAM__PARAMADDR_LD_BYPS             BITFIELD(31, 16)
#define LSE__LSE_PARAM__PARAMADDR_LD_BYPS__POS        16

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   LSE__LSE_PARAM__PARAMADDR_ST_BYPS   
 *
 * @BRIEF        Only used in the bypass mode. 
 *               Address of the first command of ST sequence [128-bit word 
 *               unit]. This is 128-bit word address, not byte address. The 
 *               conversion from byte address to 128-bit word address should 
 *               be done by CPU. 
 *               If LSE_CTRL SB_BYPS is 1, this value is used. In the bypass 
 *               mode, this address is given via this field, instead via 
 *               SyncBox  
 *               And also, this field will be used on the Single Step Mode. - 
 *               (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define LSE__LSE_PARAM__PARAMADDR_ST_BYPS             BITFIELD(15, 0)
#define LSE__LSE_PARAM__PARAMADDR_ST_BYPS__POS        0

    /* 
     * List of register bitfields values for component LSE
     *
     */

#ifdef __cplusplus
}
#endif
#endif                                                     /* __LSE_CRED_H */
