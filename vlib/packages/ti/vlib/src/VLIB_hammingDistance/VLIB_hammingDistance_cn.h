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

#ifndef VLIB_HAMMINGDISTANCE_CN_H_
#define VLIB_HAMMINGDISTANCE_CN_H_ 1

void VLIB_hammingDistance_cn(const uint8_t *pString1,
                             const uint8_t *pString2,
                             uint32_t xSize,
                             uint32_t ySize,
                             uint32_t mode,
                             uint32_t xPitch,
                             uint32_t *pHammingDistance);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_hammingDistance_cn.h                                 */
/* ======================================================================== */

