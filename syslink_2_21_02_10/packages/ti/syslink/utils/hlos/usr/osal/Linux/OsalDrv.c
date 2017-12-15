/*
 *  @file   OsalDrv.c
 *
 *  @brief      User-side OS-specific implementation of OsalDrv driver for Linux
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2012, Texas Instruments Incorporated
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



#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/inc/TraceDrvDefs.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Dev.h>
#include <ti/syslink/inc/usr/Linux/OsalDrv.h>
#include <ti/syslink/inc/OsalDrvDefs.h>


/** ============================================================================
 *  Macros and types
 *  ============================================================================
 */
/*!
 *  @brief  Driver name for OsalDrv.
 */
#define OSALDRV_DRIVER_NAME         "/dev/syslinkipc_Osal"


/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @brief  Driver handle for OsalDrv in this process.
 */
static Int32 OsalDrv_handle = -1;

/*!
 *  @brief  Reference count for the driver handle.
 */
static UInt32 OsalDrv_refCount = 0;


/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/*!
 *  @brief  Function to open the OsalDrv driver.
 *
 *  @sa     OsalDrv_close
 */
Int
OsalDrv_open (Void)
{
    Int status      = OSALDRV_SUCCESS;
    int osStatus    = 0;

    GT_0trace (curTrace, GT_ENTER, "OsalDrv_open");

    if (OsalDrv_refCount == 0) {
        /* TBD: Protection for refCount. */
        OsalDrv_refCount++;

        OsalDrv_handle = Dev_pollOpen (OSALDRV_DRIVER_NAME, O_SYNC | O_RDWR);
        if (OsalDrv_handle < 0) {
            perror ("OsalDrv driver open: " OSALDRV_DRIVER_NAME);
            /*! @retval OSALDRV_E_OSFAILURE Failed to open OsalDrv driver with
                        OS */
            status = OSALDRV_E_OSFAILURE;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OsalDrv_open",
                                 status,
                                 "Failed to open OsalDrv driver with OS!");
        }
        else {
            osStatus = fcntl (OsalDrv_handle, F_SETFD, FD_CLOEXEC);
            if (osStatus != 0) {
                /*! @retval OSALDRV_E_OSFAILURE Failed to set file descriptor
                                                flags */
                status = OSALDRV_E_OSFAILURE;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "OsalDrv_open",
                                     status,
                                     "Failed to set file descriptor flags!");
            }
        }
    }
    else {
        OsalDrv_refCount++;
    }

    GT_1trace (curTrace, GT_LEAVE, "OsalDrv_open", status);

    /*! @retval OSALDRV_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief  Function to close the OsalDrv driver.
 *
 *  @sa     OsalDrv_open
 */
Int
OsalDrv_close (Void)
{
    Int status      = OSALDRV_SUCCESS;
    int osStatus    = 0;

    GT_0trace (curTrace, GT_ENTER, "OsalDrv_close");

    /* TBD: Protection for refCount. */
    OsalDrv_refCount--;
    if (OsalDrv_refCount == 0) {
        osStatus = close (OsalDrv_handle);
        if (osStatus != 0) {
            perror ("OsalDrv driver close: " OSALDRV_DRIVER_NAME);
            /*! @retval OSALDRV_E_OSFAILURE Failed to open OsalDrv driver
                                            with OS */
            status = OSALDRV_E_OSFAILURE;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OsalDrv_close",
                                 status,
                                 "Failed to close OsalDrv driver with OS!");
        }
        else {
            OsalDrv_handle = 0;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "OsalDrv_close", status);

    /*! @retval OSALDRV_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief  Function to map a memory region specific to the driver.
 *
 *  @sa     OsalDrv_close,OsalDrv_open
 */
UInt32
OsalDrv_map (UInt32 addr, UInt32 size, Bool isCached)
{
    OsalDrv_CmdArgs mmapArgs;
    UInt32 pageSize = getpagesize ();
    UInt32 userAddr = (UInt32) NULL;
    UInt32 taddr;
    UInt32 tsize;
    Int status = 0;

    GT_0trace (curTrace, GT_ENTER, "OsalDrv_map");

    if (OsalDrv_refCount == 1) {
        if (isCached) {
            mmapArgs.physAddr = addr;
            status = OsalDrv_ioctl(CMD_OSALDRV_CACHEMMAP, &mmapArgs);
        }
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OsalDrv_map",
                                 OSALDRV_E_MAP,
                                 "Failed to setup map memory to user space!");
        }
        else {
#endif /* #if !defined(SYSLINK_BUILD_OPTIMIZE) */

            taddr = addr;
            tsize = size;
            /* Align the physical address to page boundary */
            tsize = tsize + (taddr % pageSize);
            taddr = taddr - (taddr % pageSize);

            userAddr = (UInt32) mmap (NULL,
                                      tsize,
                                      PROT_READ | PROT_WRITE,
                                      MAP_SHARED,
                                      OsalDrv_handle,
                                      (off_t) taddr);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            if (userAddr == (UInt32) MAP_FAILED) {
                userAddr = (UInt32)NULL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "OsalDrv_map",
                                     OSALDRV_E_MAP,
                                     "Failed to map memory to user space!");
            }
            else {
#endif /* #if !defined(SYSLINK_BUILD_OPTIMIZE) */
                /* Change the user address to reflect the actual user address
                 * of memory block mapped. This is done since during mmap
                 * memory block was shifted (+-) so that it is aligned to page
                 * boundary.
                 */
                userAddr = userAddr + (addr % pageSize);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            }
        }
#endif /* #if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "OsalDrv_map", userAddr);

    /*! @retval NULL Operation was successful. */
    /*! @retval valid-address Operation successfully completed. */
    return userAddr;
}


/*!
 *  @brief  Function to unmap a memory region specific to the driver.
 *
 *  @sa     OsalDrv_close,OsalDrv_open,OsalDrv_map
 */
Void
OsalDrv_unmap (UInt32 addr, UInt32 size)
{
    UInt32 pageSize = getpagesize ();
    UInt32 taddr;
    UInt32 tsize;


    GT_0trace (curTrace, GT_ENTER, "OsalDrv_unmap");

    if (OsalDrv_refCount == 1) {
        taddr = addr;
        tsize = size;

        /* Get the actual user address and size. Since these are modified at the
         * time of mmaping, to have memory block page boundary aligned.
         */
        tsize = tsize + (taddr % pageSize);
        taddr = taddr - (taddr % pageSize);
        munmap ((Void *) taddr, tsize);
    }

    GT_0trace (curTrace, GT_LEAVE, "OsalDrv_unmap");
}


/*!
 *  @brief  Function to invoke the APIs through ioctl.
 *
 *  @param  cmd     Command for driver ioctl
 *  @param  args    Arguments for the ioctl command
 *
 *  @sa
 */
Int
OsalDrv_ioctl (UInt32 cmd, Ptr args)
{
    Int status   = OSALDRV_SUCCESS;
    int osStatus;

    GT_2trace (curTrace, GT_ENTER, "OsalDrv_ioctl", cmd, args);

    GT_assert (curTrace, (OsalDrv_refCount > 0));

    osStatus = ioctl (OsalDrv_handle, cmd, args);
    if (osStatus < 0) {
        /*! @retval OSALDRV_E_OSFAILURE Driver ioctl failed */
        status = OSALDRV_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalDrv_ioctl",
                             status,
                             "Driver ioctl failed!");
    }
    else {
        /* First field in the structure is the API status. */
        status = ((TraceDrv_CmdArgs *) args)->apiStatus;
    }

    GT_1trace (curTrace, GT_LEAVE, "OsalDrv_ioctl", status);

    /*! @retval OSALDRV_SUCCESS Operation successfully completed. */
    return status;
}
