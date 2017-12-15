/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2009 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/

/**
 *  \file vpsdrv_tvp7002.h
 *
 *  \brief TVP7002 decoder interface file.
 */

#ifndef _VPSDRV_TVP7002_H_
#define _VPSDRV_TVP7002_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Vps_tvp7002Init(void);
Int32 Vps_tvp7002DeInit(void);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _VPSDRV_TVP7002_H_ */
