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

#ifndef VLIB_ORIGINALFAST12_DETECTCORNERS_CN_H_
#define VLIB_ORIGINALFAST12_DETECTCORNERS_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_orb.h"

void VLIB_originalfast12_score_cn(const uint8_t *i,
                                  int stride,
                                  CORBFeature *features,
                                  int n_features,
                                  int b);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_originalfast12_score_cn.h                            */
/* ======================================================================== */

