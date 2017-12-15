/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_ORB_COMPUTERBRIEF_CN_H_
#define VLIB_ORB_COMPUTERBRIEF_CN_H_ 1

#include "../common/VLIB_types.h"


uint32_t VLIB_ORB_computeRBrief_cn(uint32_t *intgrlImg,
                                   uint16_t intgrlImgPitch,
                                   uint16_t imgWidth,
                                   uint16_t imgHeight,
                                   uint32_t *featuresLoc,
                                   uint8_t *featuresWedge,
                                   uint32_t numFeatures,
                                   int32_t *relativePattern,
                                   uint8_t *outFeatureDesc);

#endif
/* ======================================================================== */
/*  End of file:  VLIB_ORB_computeRBrief_cn.h                               */
/* ======================================================================== */

