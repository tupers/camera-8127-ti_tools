/*
********************************************************************************
* HDVICP2.0 Based MPEG4 ASP Decoder
*
* "HDVICP2.0 Based MPEG4 ASP Decoder" is software module developed on TI's
*  HDVICP2 based SOCs. This module is capable of decode a 4:2:0 Raw
*  video stream of Advanced/Simple profile and also H.263 bit-stream.
*  Based on  ISO/IEC 14496-2:2003."
* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/

/**
*****************************************************************************
* @file   <TestApp_rmanConfig.h>
*
* @brief  A header file describing IRES Implementation
*
* @author:  Ashish Singh
*
* @version 0.0 (July 2009)  : Initial version
*
* @version 0.1 (Apr 2010) : Code commenting and cleanup
*                           [Ananya]
* @version 0.2 (Oct 2010) : Cleared doxygen warning
*
* @version 0.3 (August 2011) : Updated with latest test app parameters
*
****************************************************************************
*/
#ifndef _TESTAPP_RMANCONFIG_H_
#define _TESTAPP_RMANCONFIG_H_

/******************************************************************************
*  INCLUDE FILES
******************************************************************************/

#define NUM_IVAHD_RESOURCES   2
#define MBOX_INTR_REG        0xE000E100

#if defined(USE_HOST_FILE_IO) && !defined(NETRA)
  #define IVAHD0_HOST_L2_BASE      0xBA000000
  #define IVAHD0_HOST_SL2          0xBB000000
  #define IVA0_RESET_CONTROLLER    0xAA306F10
  #define IVA0_MBX_INTR_EN_MASK    0x00400000
  #define IVA0_MBX_INTR_VEC_IDX    38
  #define SOC_TOTAL_IVAHDS         0x1
#else
#if defined(HOST_ARM9)
  #define IVAHD0_HOST_L2_BASE      0x50080000
  #define IVAHD0_HOST_SL2          0x90000000
  #define IVA0_RESET_CONTROLLER    0x30082000
  #define IVA0_MBX_INTR_EN_MASK    0x00400000
  #define IVA0_MBX_INTR_VEC_IDX    38
  #define SOC_TOTAL_IVAHDS         0x1
#elif defined(HOST_M3)
#ifdef NETRA
  #define IVAHD0_HOST_L2_BASE      0x58000000
  #define IVAHD0_HOST_SL2          0x59000000
  #define IVA0_RESET_CONTROLLER    0x48180C10
  #define IVA0_MBX_INTR_EN_MASK    0x00400000
  #define IVA0_MBX_INTR_VEC_IDX    38

  #define IVAHD1_HOST_L2_BASE      0x5A000000
  #define IVAHD1_HOST_SL2          0x5B000000
  #define IVA1_RESET_CONTROLLER    0x48180D10
  #define IVA1_MBX_INTR_EN_MASK    0x00080000
  #define IVA1_MBX_INTR_VEC_IDX    35

  #define IVAHD2_HOST_L2_BASE      0x53000000
  #define IVAHD2_HOST_SL2          0x54000000
  #define IVA2_RESET_CONTROLLER    0x48180E10
  #define IVA2_MBX_INTR_EN_MASK    0x00010000
  #define IVA2_MBX_INTR_VEC_IDX    32

  #define SOC_TOTAL_IVAHDS         0x3
#else
  #define IVAHD0_HOST_L2_BASE      0x5A000000
  #define IVAHD0_HOST_SL2          0x5B000000
  #define IVA0_RESET_CONTROLLER    0x4A306F10
  #define IVA0_MBX_INTR_EN_MASK    0x00400000
  #define IVA0_MBX_INTR_VEC_IDX    38
  #define SOC_TOTAL_IVAHDS         0x1
#endif
#else
  #define IVAHD0_HOST_L2_BASE      0x50080000
  #define IVAHD0_HOST_SL2          0x00800000
  #define IVA0_RESET_CONTROLLER    0x00000000
  #define IVA0_MBX_INTR_EN_MASK    0x00400000
  #define IVA0_MBX_INTR_VEC_IDX    38
  #define SOC_TOTAL_IVAHDS         0x1
#endif

#endif
/**
 *  Macro defining ICONT1 DTCM offset from the base address
*/
#define ICONT1_DTCM_OFFSET 0x00000000
/**
 *  Macro defining ICONT2 DTCM offset from the base address
*/
#define ICONT2_DTCM_OFFSET 0x00010000
/**
 *  Macro defining ICONT1 ITCM offset from the base address
*/
#define ICONT1_ITCM_OFFSET 0x00008000
/**
 *  Macro defining ICONT2 ITCM offset from the base address
*/
#define ICONT2_ITCM_OFFSET 0x00018000

/**
 *  Macro defining the Register base address to Clock management
*/
#define IVAHD_CLKREG_BASE ((IVA0_RESET_CONTROLLER & 0xFF000000) + 0x8F00)
/**
 *  Macro defining clock status register offset from the base
*/
#define IVAHD_CLKSTCTRL_OFFSET (0x00000000)
/**
 *  Macro defining clock control register offset from the base
*/
#define IVAHD_CLKCTRL_OFFSET (0x00000020)
/**
 *  Macro defining SL2 clock control register offset from the base
*/
#define SL2_CLKCTRL_OFFSET (0x00000028)


XDAS_Int8 RMAN_AssignResources(IALG_Handle handle);

#ifdef NETRA
static const XDAS_UInt32 regBaseAdderss[SOC_TOTAL_IVAHDS] =
                                                      {IVAHD0_HOST_L2_BASE,
                                                       IVAHD1_HOST_L2_BASE,
                                                       IVAHD2_HOST_L2_BASE
                                                      };

static const XDAS_UInt32 memBaseAddress[SOC_TOTAL_IVAHDS] =
                                                      {IVAHD0_HOST_SL2,
                                                       IVAHD1_HOST_SL2,
                                                       IVAHD2_HOST_SL2
                                                      };

static const XDAS_UInt32 resetControlAddress[SOC_TOTAL_IVAHDS] =
                                                        { IVA0_RESET_CONTROLLER,
                                                          IVA1_RESET_CONTROLLER,
                                                          IVA2_RESET_CONTROLLER
                                                        };

static const XDAS_UInt32 mboxIntrIndex[SOC_TOTAL_IVAHDS] =
                                                     { IVA0_MBX_INTR_VEC_IDX,
                                                       IVA1_MBX_INTR_VEC_IDX,
                                                       IVA2_MBX_INTR_VEC_IDX
                                                     };

static const XDAS_UInt32 mboxIntrEnableMask[SOC_TOTAL_IVAHDS] =
                                                     { IVA0_MBX_INTR_EN_MASK,
                                                       IVA1_MBX_INTR_EN_MASK,
                                                       IVA2_MBX_INTR_EN_MASK
                                                     };
#else
static const XDAS_UInt32 regBaseAdderss[SOC_TOTAL_IVAHDS] =
                                                         {IVAHD0_HOST_L2_BASE};

static const XDAS_UInt32 memBaseAddress[SOC_TOTAL_IVAHDS] = {IVAHD0_HOST_SL2};

static const XDAS_UInt32 resetControlAddress[SOC_TOTAL_IVAHDS] =
                                                        {IVA0_RESET_CONTROLLER};

static const XDAS_UInt32 mboxIntrIndex[SOC_TOTAL_IVAHDS] =
                                                       {IVA0_MBX_INTR_VEC_IDX};

static const XDAS_UInt32 mboxIntrEnableMask[SOC_TOTAL_IVAHDS] =
                                                       {IVA0_MBX_INTR_EN_MASK};
#endif

/**
********************************************************************************
 *  @fn     RMAN_FreeResources
 *  @brief   This function Frees the resources acquired
 *
 *  @param[in] handle                        : Alg handle
 *
 *  @return none
********************************************************************************
*/
void RMAN_FreeResources(IALG_Handle handle);
void RMAN_DeactivateAllResources(IALG_Handle handle);

#endif /* _TESTAPP_RMANCONFIG_H_ */

