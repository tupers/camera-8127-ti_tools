/*
********************************************************************************
* HDVICP2.0 Based JPEG Encoder
*
* "HDVICP2.0 Based JPEG Encoder" is software module developed for
* TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
* by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      jpegenc_ti_alg_create.c
*
* @brief     This file contains a simple implementation of the ALG_create API
*            operation.
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Vasudev]
*
********************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <stdlib.h>
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>

/*--------------------- program files ----------------------------------------*/

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

/**
********************************************************************************
*  @fn     ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
*
*  @brief  This function does required memory allocation for the algorithm
*
*  @param[in]  fxns        :  Pointer to Alg Functions structure.
*
*  @param[in,out]  p       :  Algorithm instance handle.
*
*  @param[in]  params      :  Pointer to Algorithm params structure required
*                            for mem alloc
*
*  @return     Pointer to the created algorithm or NULL
********************************************************************************
*/
ALG_Handle ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
{
  IALG_MemRec *memTab;
  Int n;
  ALG_Handle alg;
  IALG_Fxns *fxnsPtr;

  if (fxns != NULL)
  {
    /*------------------------------------------------------------------------*/
    /*   Get the number of memory requirements required by the clients        */
    /*   If not specified, This function will allocate default memory record  */
    /*------------------------------------------------------------------------*/
    n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc(): IALG_DEFMEMRECS;

    if ((memTab = (IALG_MemRec*)malloc(n *sizeof(IALG_MemRec))))
    {
      /*----------------------------------------------------------------------*/
      /*   Allocate memory requested by the user & return the pointer to      */
      /*   starting address of the memory chunk being allocated               */
      /*----------------------------------------------------------------------*/
      n = fxns->algAlloc(params, &fxnsPtr, memTab);
      if (n <= 0)
      {
        return (NULL);
      }

      if (_ALG_allocMemory(memTab, n))
      {
        /*--------------------------------------------------------------------*/
        /*   Allocate the starting address of memory being allocated to the   */
        /*   handle of the algorithm instance                                 */
        /*--------------------------------------------------------------------*/
        alg = (IALG_Handle)memTab[0].base;

        alg->fxns = fxns;

        /*--------------------------------------------------------------------*/
        /*   Initialize the memory being allocated                            */
        /*--------------------------------------------------------------------*/
        if (fxns->algInit(alg, memTab, p, params) == IALG_EOK)
        {
          free(memTab);
          return (alg);
        }

        /*--------------------------------------------------------------------*/
        /*   Free the memory being allocated                                  */
        /*--------------------------------------------------------------------*/
        fxns->algFree(alg, memTab);
        _ALG_freeMemory(memTab, n);
      }

      free(memTab);
    }
  }

  return (NULL);
}

/**
********************************************************************************
*  @fn     ALG_delete(ALG_Handle alg)
*
*  @brief  ALG_Delete API Implementation
*
*  @param  alg      : Handle to Algorithm
*
*  @return none
********************************************************************************
*/
Void ALG_delete(ALG_Handle alg)
{
  IALG_MemRec *memTab;
  Int n;
  IALG_Fxns *fxns;

  if (alg != NULL && alg->fxns != NULL)
  {
    fxns = alg->fxns;

    /*------------------------------------------------------------------------*/
    /*   Get the number of memory requirements required by the clients        */
    /*   If not specified, This function will allocate default memory record  */
    /*------------------------------------------------------------------------*/
    n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc(): IALG_DEFMEMRECS;

    if ((memTab = (IALG_MemRec*)malloc(n *sizeof(IALG_MemRec))))
    {
      /*----------------------------------------------------------------------*/
      /*   Allocate memtab base address with handle to algorithm instance     */
      /*----------------------------------------------------------------------*/
      memTab[0].base = alg;

      /*----------------------------------------------------------------------*/
      /*   Free the number of memory records used by the algorithm instance   */
      /*----------------------------------------------------------------------*/
      n = fxns->algFree(alg, memTab);
      _ALG_freeMemory((IALG_MemRec*)memTab, n);

      free(memTab);
    }
  }
}

