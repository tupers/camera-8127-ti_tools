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

#ifndef VLIB_MOG_1CH_32_CN_H_
#define VLIB_MOG_1CH_32_CN_H_ 1

void VLIB_MOG_1Ch_updateComponents_32_cn(const uint8_t *restrict Im,
                                         int32_t *restrict mu,
                                         int32_t *restrict var,
                                         int16_t *restrict wt,
                                         const int32_t delta,
                                         uint32_t *restrict currMask,
                                         const int32_t imSize,
                                         const int32_t rho,
                                         const int16_t alpha,
                                         const int32_t ini_var,
                                         const int16_t ini_wt,
                                         uint8_t *restrict compNum);

void VLIB_MOG_1Ch_replaceWeakestComponent_32_cn(const uint8_t *restrict im,
                                                int32_t *restrict mu,
                                                int32_t *restrict var,
                                                int16_t *restrict wt,
                                                uint8_t *restrict compNum,
                                                uint32_t *restrict updateMask,
                                                const int32_t ini_var,
                                                const int16_t ini_wt,
                                                int32_t im_size);

void VLIB_MOG_1Ch_thresholdImage_32_cn(const int16_t *restrict wt,
                                       const uint8_t *restrict compNum,
                                       const int16_t T,
                                       uint32_t *restrict Im_mask,
                                       const int32_t im_size);

void VLIB_MOG_1Ch_sortComponents_32_cn(int32_t *restrict mu,
                                       int16_t *restrict wt,
                                       int32_t *restrict var,
                                       const int32_t im_size);

#endif /* VLIB_MOG_1CH_32_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_MOG_1Ch_32_cn.h                                      */
/* ======================================================================== */

