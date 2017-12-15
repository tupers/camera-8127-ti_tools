/*
 *  Copyright (c) 2010-2011, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

/*
*  @file timm_osal_task.h
*  The osal header file defines 
*  @path
*
*/
/* -------------------------------------------------------------------------- */
/* =========================================================================
 *!
 *! Revision History
 *! ===================================
 *! 0.1: Created the first draft version, ksrini@ti.com
 * ========================================================================= */

#ifndef _TIMM_OSAL_TASK_H_
#define _TIMM_OSAL_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
* Includes
*******************************************************************************/

#include "timm_osal_types.h"
#include "timm_osal_error.h"


#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


#define TASK_NAME_SIZE 20

/**
* TIMM_OSAL_TASK describe the different task information
*/
typedef struct TIMM_OSAL_TASK
{
    /** Handle to the task context structure */
    Task_Handle   task;
    /** Name of the task */
    TIMM_OSAL_S8  name[TASK_NAME_SIZE + 1];
    /** Pointer to the task stack memory */
    TIMM_OSAL_PTR stackPtr;
    /** Size of the task stack */
    TIMM_OSAL_S32 stackSize;
    /** task priority */
    TIMM_OSAL_S32 priority;
    /** flag to check if task got created */
    TIMM_OSAL_BOOL isCreated;
} TIMM_OSAL_TASK;

/*******************************************************************************
* Tasks
*******************************************************************************/

/**
* prototype for the task function
*/
typedef void (*TIMM_OSAL_TaskProc)(TIMM_OSAL_U32 argc, TIMM_OSAL_PTR argv);



/* ===========================================================================*/
/**
 * @fn TIMM_OSAL_CreateTask() - Create a new task.
 *
 *  @ param pTask               :Handle of the task to be created.
 *
 *  @ param pFunc               :Task entry function.
 *
 *  @ param uArgc               :argc for the task entry function.
 *
 *  @ param uArgv               :argv for the task entry function.
 *
 *  @ param uStackSize          :Size of the task stack.
 *
 *  @ param uPriority           :Task priority.
 *
 *  @ param pName               :Task name.
 */
/* ===========================================================================*/
TIMM_OSAL_ERRORTYPE TIMM_OSAL_CreateTask (TIMM_OSAL_PTR *pTask,
                                          TIMM_OSAL_TaskProc pFunc,
                                          TIMM_OSAL_U32 uArgc,
                                          TIMM_OSAL_PTR pArgv,
                                          TIMM_OSAL_U32 uStackSize,
                                          TIMM_OSAL_U32 uPriority,
                                          TIMM_OSAL_S8 *pName);


/* ===========================================================================*/
/**
 * @fn TIMM_OSAL_CreateTaskExtn() - Create a new task.
 *
 *  @ param pTask               :Handle of the task to be created.
 *
 *  @ param pFunc               :Task entry function.
 *
 *  @ param uArgc               :argc for the task entry function.
 *
 *  @ param uArgv               :argv for the task entry function.
 *
 *  @ param uStackSize          :Size of the task stack.
 *
 *  @ param uPriority           :Task priority.
 *
 *  @ param pName               :Task name.
 *
 *  @ param hStackHeapHandle    :Task stack heap handle.
 */
/* ===========================================================================*/
TIMM_OSAL_ERRORTYPE TIMM_OSAL_CreateTaskExtn (TIMM_OSAL_PTR *pTask,
                                          TIMM_OSAL_TaskProc pFunc,
                                          TIMM_OSAL_U32 uArgc,
                                          TIMM_OSAL_PTR pArgv,
                                          TIMM_OSAL_U32 uStackSize,
                                          TIMM_OSAL_U32 uPriority,
                                          TIMM_OSAL_S8 *pName,
                                          TIMM_OSAL_PTR hStackHeapHandle);


/* ===========================================================================*/
/**
 * @fn TIMM_OSAL_DeleteTask() - Deletes a previously created task.
 *
 *  @ param pTask               :Handle of the task to be deleted.                                              
 */
/* ===========================================================================*/
TIMM_OSAL_ERRORTYPE TIMM_OSAL_DeleteTask (TIMM_OSAL_PTR pTask);



/* ===========================================================================*/
/**
 * @fn TIMM_OSAL_SleepTask() - Task goes to sleep for the specified time.
 *
 *  @ param mSec               :Time in msec for which task goes to sleep.
 */
/* ===========================================================================*/
TIMM_OSAL_ERRORTYPE TIMM_OSAL_SleepTask (TIMM_OSAL_U32 mSec);


/* ========================================================================== */
/**
* @fn TIMM_OSAL_ExitTask
*
* @see
*/
/* ========================================================================== */

TIMM_OSAL_ERRORTYPE TIMM_OSAL_ExitTask (TIMM_OSAL_PTR pTask, void *value_ptr);

/* ========================================================================== */
/**
* @fn TIMM_OSAL_Task_yield - yield to other tasks
*
*/
/* ========================================================================== */

TIMM_OSAL_ERRORTYPE TIMM_OSAL_Task_yield ();

/* ========================================================================== */
/**
* @fn TIMM_OSAL_Task_newpri
*
* @see set new Priority.
*      Note: This is available only in Sys BIOS.
*/    
/* ========================================================================== */
TIMM_OSAL_ERRORTYPE TIMM_OSAL_Task_newpri ( TIMM_OSAL_PTR pTask, 
                                            TIMM_OSAL_S32 sNewPriority );
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TIMM_OSAL_TASK_H_ */
