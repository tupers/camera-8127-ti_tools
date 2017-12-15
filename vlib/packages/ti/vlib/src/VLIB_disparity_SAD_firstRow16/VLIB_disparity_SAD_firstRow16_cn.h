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

#ifndef VLIB_DISPARITY_SAD_FIRSTROW16_CN_H_
#define VLIB_DISPARITY_SAD_FIRSTROW16_CN_H_ 1


int32_t VLIB_disparity_SAD_firstRow16_cn(const uint16_t *restrict leftImage,
                                         const uint16_t *restrict rightImage,
                                         uint32_t *restrict currentCost,
                                         uint32_t *restrict minCost,
                                         uint32_t *restrict pScratch,
                                         int8_t *restrict disparity,
                                         int32_t currentDisplacement,
                                         int32_t width,
                                         int32_t pitch,
                                         int32_t disparityWindowSize);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_disparity_SAD_firstRow16_cn.h                        */
/* ======================================================================== */

