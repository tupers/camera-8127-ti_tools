/*
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
 */

/**
 *  @file   ti/syslink/family/hlos/knl/ti81xx/Platform_qnx.c
 *
 *  @brief  Implementation of Platform initialization logic.
 */

/* Standard header files */
#include <ti/syslink/Std.h>

/* Utilities & Osal headers */
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/utils/OsalPrint.h>
#include <ti/syslink/inc/knl/OsalThread.h>
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/Cfg.h>
#include <ti/syslink/utils/IpcMemMgr.h>
#include <ti/syslink/inc/_SysLink.h>

/* SysLink device specific headers */
#include <ti/syslink/inc/knl/Dm8168IpcInt.h>
#include <ti/syslink/inc/knl/Dm8168DspPwr.h>
#include <ti/syslink/inc/knl/Dm8168DspProc.h>
#include <ti/syslink/inc/knl/Dm8168M3VideoProc.h>
#include <ti/syslink/inc/knl/Dm8168M3DssProc.h>
#include <ti/syslink/inc/knl/Dm8168DucatiPwr.h>

/* Module level headers */
#include <ti/ipc/SharedRegion.h>
#include <ti/ipc/ListMP.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/HeapBufMP.h>
#include <ti/ipc/NameServer.h>
#include <ti/ipc/SharedRegion.h>

#include <ti/syslink/inc/_FrameQ.h>
#include <ti/syslink/ipc/_FrameQBufMgr.h>
#include <ti/syslink/ProcMgr.h>
#include <ti/syslink/inc/_ProcMgr.h>
#include <ti/syslink/inc/knl/Platform.h>
#include <ti/syslink/inc/ElfLoader.h>

#include <ti/syslink/inc/_Notify.h>    /* for auto-setting of USE_SYSLINK_NOTIFY */

#if defined (USE_SYSLINK_NOTIFY)
#include <ti/syslink/inc/_MultiProc.h>
#include <ti/syslink/inc/NotifyDriverShm.h>
#else
#include <syslink/multiproc.h>
#include <syslink/notify.h>
#include <syslink/_notify.h>
#include <syslink/notify_shm_drv.h>
#endif

#include <ti/syslink/inc/_GateMP_qnx.h>
#include <ti/syslink/inc/GatePeterson.h>
#include <ti/syslink/inc/GateHWSpinlock_qnx.h>

#include <ti/syslink/inc/TransportShm.h>
#if defined (SYSLINK_TRANSPORT_SHMNOTIFY)
#include <ti/syslink/inc/TransportShmNotify.h>
#endif
#if defined (SYSLINK_TRANSPORT_SHMCIRC)
#include <ti/syslink/inc/TransportShmCirc.h>
#endif

#if defined (SYSLINK_NOTIFYDRIVER_CIRC)
#include <ti/syslink/inc/NotifyDriverCirc.h>
#endif

#include <ti/syslink/inc/_NameServer.h>
#include <ti/syslink/inc/_SharedRegion.h>
#include <ti/syslink/inc/_MessageQ.h>
#include <ti/syslink/inc/_HeapBufMP.h>
#include <ti/syslink/inc/_HeapMemMP.h>
#include <ti/syslink/inc/_ListMP.h>
#include <ti/syslink/inc/NameServerRemote.h>
#include <ti/syslink/inc/NameServerRemoteNotify.h>
#include <ti/syslink/inc/ClientNotifyMgr.h>
#include <ti/syslink/utils/IHeap.h>

#include <ti/ipc/Ipc.h>
#include <ti/syslink/inc/_Ipc.h>
#include <ti/syslink/inc/knl/IpcKnl.h>

/* this macro is only used on Linux builds */
#ifndef EXPORT_SYMBOL
#define EXPORT_SYMBOL(s)
#endif

/* ProcMgr friend function */
extern ProcMgr_Handle _ProcMgr_getHandle(UInt16 procId);


/** ============================================================================
 *  Macros.
 *  ============================================================================
 */
#define RESETVECTOR_SYMBOL          "_Ipc_ResetVector"


/* This tag is used as an identifier by Ipc_readConfig
 * to get different modules' configuration on slave
 */
#define SLAVE_CONFIG_TAG            0xDADA0000

/* Defines used for timeout value for start/stopCallback. Note that
 * the loop iterates LOOPCNT times but sleeps for SLEEPTIME only once
 * every 4096 iterations. Increase the DETACH_LOOPCNT if the remote
 * processor needs more time to shutdown.
 */
#define ATTACH_LOOPCNT          0x1388000   /* total sleep time = 5 sec */
#define ATTACH_SLEEPTIME        1           /* msec */
#define DETACH_LOOPCNT          0x2BC000    /* total sleep time = 0.7 sec */
#define DETACH_SLEEPTIME        1           /* msec */
#define CFG_LOOPCNT             40          /* total sleep time = 0.4 sec */
#define CFG_SLEEPTIME           10          /* msec */

/** ============================================================================
 *  Application specific configuration, please change these value according to
 *  your application's need.
 *  ============================================================================
 */

/* this type must match the same in ti/syslink/ipc/rtos/Syslink.c */
typedef struct {
    UInt16      sharedRegionNumEntries;
    UInt16      terminateEventLineId;
    UInt32      terminateEventId;
} Syslink_SlaveModuleConfig;

typedef struct {
    UInt16      lineId;
    UInt32      eventId;
} TerminateEventConfig;

 /* This structure is used to get different modules' configuration on host
 * to match it with that of Slaves'
 */
typedef struct Platform_ModuleConfig {
    UInt16      sharedRegionNumEntries;
} Platform_ModuleConfig;

/*!
 *  @brief  Structure defining config parameters for overall System.
 */
typedef struct Platform_Config {
    IpcMemMgr_Config                ipcMemMgrConfig;

#if defined (USE_SYSLINK_NOTIFY)
    MultiProc_Config                multiProcConfig;
    /*!< Multiproc config parameter */
#else
    struct multiproc_config         multiProcConfig;
#endif

    GateMP_Config                   gateMPConfig;
    /*!< GateMP config parameter */

    GateHWSpinlock_Config           gateHWSpinlockConfig;
    /*!< Gatepeterson config parameter */

    GatePeterson_Config             gatePetersonConfig;
    /*!< Gatepeterson config parameter */

    SharedRegion_Config             sharedRegionConfig;
    /*!< SharedRegion config parameter */

    MessageQ_Config                 messageQConfig;
    /*!< MessageQ config parameter */

#if defined (USE_SYSLINK_NOTIFY)
    Notify_Config            notifyConfig;
#else
    struct notify_config            notifyConfig;
    /*!< Notify config parameter */
#endif

    ProcMgr_Config                  procMgrConfig;
    /*!< Processor manager config parameter */

    ElfLoader_Config                elfLoaderConfig;
    /*!< Elf loader config parameter */

    HeapBufMP_Config                heapBufConfig;
    /*!< Heap Buf config parameter */

    HeapMemMP_Config                heapMemMPConfig;
    /*!< Heap MemMP config parameter */

    ListMP_Config                   listMPConfig;
    /*!<ListMP config parameter */

    TransportShm_Config             messageQTransportShmConfig;
    /*!< TransportShm config parameter */

#if defined (SYSLINK_TRANSPORT_SHMNOTIFY)
    TransportShmNotify_Config       messageQTransportShmNotifyConfig;
    /*!< TransportShmNotify config parameter */
#endif /* if defined (SYSLINK_TRANSPORT_SHMNOTIFY) */

#if defined (SYSLINK_TRANSPORT_SHMCIRC)
    TransportShmCirc_Config         messageQTransportShmCircConfig;
    /*!< TransportShmCirc config parameter */
#endif /* if defined (SYSLINK_TRANSPORT_SHMCIRC) */

#if defined (USE_SYSLINK_NOTIFY)
    NotifyDriverShm_Config          notifyDriverShmConfig;
    /*!< NotifyDriverShm config parameter */
#else
    struct notify_shm_drv_config    notifyDriverShmConfig;
#endif

#if defined (SYSLINK_NOTIFYDRIVER_CIRC)
    NotifyDriverCirc_Config         notifyDriverCircConfig;
    /*!< NotifyDriverCirc config parameter */
#endif /* if defined (SYSLINK_NOTIFYDRIVER_CIRC) */

    NameServerRemoteNotify_Config   nameServerRemoteNotifyConfig;
    /*!< NameServerRemoteNotify config parameter */

    ClientNotifyMgr_Config          cliNotifyMgrCfgParams;
    /*!< ClientNotifyMgr config parameter */

    FrameQBufMgr_Config             frameQBufMgrCfgParams;
    /*!< FrameQBufMgr config parameter */

    FrameQ_Config                   frameQCfgParams;
    /*!< FrameQ config parameter */
} Platform_Config;


/* Struct embedded into slave binary */
typedef struct Platform_SlaveConfig {
    UInt32  cacheLineSize;
    UInt32  brOffset;
    UInt32  sr0MemorySetup;
    UInt32  setupMessageQ;
    UInt32  setupNotify;
    UInt32  procSync;
    UInt32  numSRs;
} Platform_SlaveConfig;

/* Shared region configuration */
typedef struct Platform_SlaveSRConfig {
    UInt32 entryBase;
    UInt32 entryLen;
    UInt32 ownerProcId;
    UInt32 id;
    UInt32 createHeap;
    UInt32 cacheLineSize;
} Platform_SlaveSRConfig;

/*! @brief structure for platform instance */
typedef struct Platform_Object {
    /*!< Flag to indicate platform initialization status */
    ProcMgr_Handle                pmHandle;
    /*!< Handle to the ProcMgr instance used */
    union {
        struct {
            DM8168DSPPROC_Handle pHandle;
            /*!< Handle to the Processor instance used */
            DM8168DSPPWR_Handle  pwrHandle;
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle    ldrHandle;
            /*!< Handle to the Loader instance used */
        } dsp;
        struct {
            DM8168VIDEOM3PROC_Handle pHandle;
            /*!< Handle to the Processor instance used */
            DM8168DUCATIPWR_Handle  pwrHandle;
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle        ldrHandle;
            /*!< Handle to the Loader instance used */
        } m3video;
        struct {
            DM8168VPSSM3PROC_Handle pHandle;
            /*!< Handle to the Processor instance used */
            DM8168DUCATIPWR_Handle  pwrHandle;
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle      ldrHandle;
            /*!< Handle to the Loader instance used */
        } m3vpss;
    } sHandles;
    /*!< Slave specific handles */
    Platform_SlaveConfig          slaveCfg;
    /*!< Slave embedded config */
    Platform_SlaveSRConfig *      slaveSRCfg;
    /*!< Shared region details from slave */
    UInt16                        refCount;
    /*!< Reference count for whether to wait for slave-side Ipc_stop */
    UInt8               *bslaveAdditionalReg;
    /*!< To keep track of  additional shared regions configured in the slave */
} Platform_Object, *Platform_Handle;


/*! @brief structure for platform instance */
typedef struct Platform_Module_State {
    Bool              multiProcInitFlag;
    /*!< MultiProc Initialize flag */
    Bool              gateMPInitFlag;
    /*!< GateMP Initialize flag */
    Bool              gateHWSpinlockInitFlag;
    /*!< Gatepeterson Initialize flag */
    Bool              gatePetersonInitFlag;
    /*!< Gatepeterson Initialize flag */
    Bool              sharedRegionInitFlag;
    /*!< SHAREDREGION Initialize flag */
    Bool              listMpInitFlag;
    /*!< ListMP Initialize flag */
    Bool              messageQInitFlag;
    /*!< MessageQ Initialize flag */
    Bool              notifyInitFlag;
    /*!< Notify Initialize flag */
    Bool              procMgrInitFlag;
    /*!< Processor manager Initialize flag */
    Bool              elfLoaderInitFlag;
    /*!< Elf loader Initialize flag */
    Bool              heapBufInitFlag;
    /*!< HeapBufMP Initialize flag */
    Bool              heapMemMPInitFlag;
    /*!< HeapMemMP Initialize flag */
    Bool              nameServerInitFlag;
    /*!< nameServerRemoteNotify Initialize flag */
    Bool              listMPInitFlag;
    /*!< LISTMPSHAREDMEMORY Initialize flag */
    Bool              messageQTransportShmInitFlag;
    /*!< messageQTransportShm Initialize flag */
#if defined (SYSLINK_TRANSPORT_SHMNOTIFY)
    Bool              messageQTransportShmNotifyInitFlag;
    /*!< messageQTransportShmNotify Initialize flag */
#endif /* if defined (SYSLINK_TRANSPORT_SHMNOTIFY) */
#if defined (SYSLINK_TRANSPORT_SHMCIRC)
    Bool              messageQTransportShmCircInitFlag;
    /*!< messageQTransportShmCirc Initialize flag */
#endif /* if defined (SYSLINK_TRANSPORT_SHMCIRC) */
    Bool              notifyDriverShmInitFlag;
    /*!< notifyDriverShm Initialize flag */
#if defined (SYSLINK_NOTIFYDRIVER_CIRC)
    Bool              notifyDriverCircInitFlag;
    /*!< notifyDriverCirc Initialize flag */
#endif /* if defined (SYSLINK_NOTIFYDRIVER_CIRC) */
    Bool              nameServerRemoteNotifyInitFlag;
    /*!< nameServerRemoteNotify Initialize flag */
    Bool              clientNotifyMgrInitFlag;
    /*!< clientNotifierMgr Initialize flag */
    Bool              frameQBufMgrInitFlag;
    /*!< frameQBufMgr Initialize flag */
    Bool              frameQInitFlag;
    /*!< frameQ Initialize flag */
    Bool              platformInitFlag;
    /*!< Flag to indicate platform initialization status */
    Platform_ModuleConfig hostModuleConfig;
    /*!< Configuration of various Modules' parameters on host */
    TerminateEventConfig termEvtAry[3];
    /*!< Terminate Event configuration array */
} Platform_Module_State;


/* =============================================================================
 * GLOBALS
 * =============================================================================
 */
#if defined (USE_SYSLINK_NOTIFY)
static Platform_Object Platform_objects [MultiProc_MAXPROCESSORS];
#else
static Platform_Object Platform_objects [MULTIPROC_MAXPROCESSORS];
#endif
static Platform_Module_State Platform_Module_state;
static Platform_Module_State * Platform_module = &Platform_Module_state;


Int32 _Platform_setup  (void);
Int32 _Platform_destroy (void);

extern String ProcMgr_sysLinkCfgParams;

/** ============================================================================
 *  APIs.
 *  ============================================================================
 */
/* Function to read slave memory */
Int32
_Platform_readSlaveMemory (UInt16   procId,
                           UInt32   addr,
                           Ptr      value,
                           UInt32 * numBytes);

/* Function to write slave memory */
Int32
_Platform_writeSlaveMemory (UInt16   procId,
                            UInt32   addr,
                            Ptr      value,
                            UInt32 * numBytes);
/*!
 *  @brief      Function to get tyhe default values for confiurations.
 *
 *  @param      config   Configuration values.
 */
Void
Platform_getConfig (Platform_Config * config)
{
    GT_1trace (curTrace, GT_ENTER, "Platform_getConfig", config);

    GT_assert (curTrace, (config != NULL));

#if !defined(SYSLINK_BUILD_OPTIMIZE)
    if (config == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_getConfig",
                             Platform_E_INVALIDARG,
                             "Argument of type (Platform_getConfig *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */

        /* get the IpcMemMgr default config */
        IpcMemMgr_getConfig(&config->ipcMemMgrConfig);

#if defined (USE_SYSLINK_NOTIFY)
        /* Get the gatepeterson default config */
        MultiProc_getConfig (&config->multiProcConfig);
#else
        /* Get the gatepeterson default config */
        multiproc_get_config (&config->multiProcConfig);
#endif
        /* Get the gatepeterson default config */
        GatePeterson_getConfig (&config->gatePetersonConfig);

        /* Get the sharedregion default config */
        SharedRegion_getConfig (&config->sharedRegionConfig);

        /* Get the MESSAGEQ default config */
        MessageQ_getConfig (&config->messageQConfig);

#if defined (USE_SYSLINK_NOTIFY)
        /* Get the NOTIFY default config */
        Notify_getConfig (&config->notifyConfig);
#else
        /* Get the NOTIFY default config */
        notify_get_config (&config->notifyConfig);
#endif
        /* Get the PROCMGR default config */
        ProcMgr_getConfig (&config->procMgrConfig);

        /* Get the ElfLoader default config */
        ElfLoader_getConfig (&config->elfLoaderConfig);

        /* Get the HeapBufMP default config */
        HeapBufMP_getConfig (&config->heapBufConfig);

        /* Get the HeapMemMP default config */
        HeapMemMP_getConfig (&config->heapMemMPConfig);

        /* Get the LISTMPSHAREDMEMORY default config */
        ListMP_getConfig (&config->listMPConfig);

        /* Get the MESSAGEQTRANSPORTSHM default config */
        TransportShm_getConfig (&config->messageQTransportShmConfig);

#if defined (SYSLINK_TRANSPORT_SHMNOTIFY)
        /* Get the MESSAGEQTRANSPORTSHMNOTIFY default config */
        TransportShmNotify_getConfig (&config->messageQTransportShmNotifyConfig);
#endif /* if defined (SYSLINK_TRANSPORT_SHMNOTIFY) */

#if defined (SYSLINK_TRANSPORT_SHMCIRC)
        /* Get the MESSAGEQTRANSPORTSHMCIRC default config */
        TransportShmCirc_getConfig (&config->messageQTransportShmCircConfig);
#endif /* if defined (SYSLINK_TRANSPORT_SHMCIRC) */

#if defined (USE_SYSLINK_NOTIFY)
        NotifyDriverShm_getConfig(&config->notifyDriverShmConfig);
#else
            /* Get the NOTIFYSHMDRIVER default config */
        notify_shm_drv_get_config (&config->notifyDriverShmConfig);
#endif

#if defined (SYSLINK_NOTIFYDRIVER_CIRC)
        /* Get the NOTIFYDRIVERCIRC default config */
        NotifyDriverCirc_getConfig (&config->notifyDriverCircConfig);
#endif /* if defined (SYSLINK_NOTIFYDRIVER_CIRC) */

        /* Get the NAMESERVERREMOTENOTIFY default config */
        NameServerRemoteNotify_getConfig(&config->nameServerRemoteNotifyConfig);

        /* Get the ClientNotifyMgr default config */
        ClientNotifyMgr_getConfig (&config->cliNotifyMgrCfgParams) ;

        /*  Get the FrameQBufMgr default config */
        FrameQBufMgr_getConfig (&config->frameQBufMgrCfgParams) ;

        /*  Get the FrameQ default config */
        FrameQ_getConfig (&config->frameQCfgParams) ;

#if !defined(SYSLINK_BUILD_OPTIMIZE)
    }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "Platform_getConfig");
}

/*!
 *  @brief      Function to override the default confiuration values.
 *
 *  @param      config   Configuration values.
 */
Int32
Platform_overrideConfig (Platform_Config * config)
{
    Int32  status = Platform_S_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "Platform_overrideConfig", config);

    GT_assert (curTrace, (config != NULL));

#if !defined(SYSLINK_BUILD_OPTIMIZE)
    if (config == NULL) {
        /*! @retval Platform_E_INVALIDARG Argument of type
         *  (Platform_Config *) passed is null*/
        status = Platform_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_overrideConfig",
                             status,
                             "Argument of type (Platform_getConfig *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */

#if defined (USE_SYSLINK_NOTIFY)
#if !defined (SYSLINK_VARIANT_TI813X)
        /* Override the gatepeterson default config */
        config->multiProcConfig.numProcessors = 4;
        config->multiProcConfig.id            = 3;
        String_cpy (config->multiProcConfig.nameList [0],
                    "DSP");
        String_cpy (config->multiProcConfig.nameList [1],
                    "VIDEO-M3");
        String_cpy (config->multiProcConfig.nameList [2],
                    "VPSS-M3");
        String_cpy (config->multiProcConfig.nameList [3],
                    "HOST");
#else
        config->multiProcConfig.numProcessors = 3;
        config->multiProcConfig.id            = 2;
        String_cpy (config->multiProcConfig.nameList [0],
                    "VIDEO-M3");
        String_cpy (config->multiProcConfig.nameList [1],
                    "VPSS-M3");
        String_cpy (config->multiProcConfig.nameList [2],
                    "HOST");
#endif
#else
        /* Currently multiproc in knl does not allow setting proc names */
#endif
        /* Override the gatepeterson default config */

        /* Override the Sharedregion default config */
        config->sharedRegionConfig.cacheLineSize = 128;

        /* Override the LISTMP default config */

        /* Override the MESSAGEQ default config */

        /* Override the NOTIFY default config */

        /* Override the PROCMGR default config */

        /* Override the HeapBuf default config */

        /* Override the LISTMPSHAREDMEMORY default config */

        /* Override the MESSAGEQTRANSPORTSHM default config */
        /* Override the MESSAGEQTRANSPORTSHMNOTIFY default config */
        /* Override the MESSAGEQTRANSPORTSHMCIRC default config */

        /* Override the NOTIFYSHMDRIVER default config */
        /* Override the NOTIFYDRIVERCIRC default config */

        /* Override the NAMESERVERREMOTENOTIFY default config */

        /* Override the  ClientNotifyMgr default config */
        /* Override the  FrameQBufMgr default config */

        /* Override the FrameQ default config */


#if !defined(SYSLINK_BUILD_OPTIMIZE)
    }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_ENTER, "Platform_overrideConfig", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}

/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
Platform_setup (void)
{
    Int32               status = Platform_S_SUCCESS;
    Platform_Config     _config;
    Platform_Config *   config;
#if defined (USE_SYSLINK_NOTIFY)
    Dm8168IpcInt_Config dm8168cfg;
#endif

    Platform_getConfig (&_config);
    config = &_config;

    Platform_overrideConfig (config);

    /* IpcMemMgr setup */
    if (status >= 0) {

        status = IpcMemMgr_setup(&config->ipcMemMgrConfig);

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_setup",
                    status, "IpcMemMgr_setup failed");
        }
    }

    /* build the syslink config database */
    if (status >= 0) {
        Int i;
        Ptr ptr;
        SysLink_ModuleCfg *elem;

        for (i = 0; i < SysLink_modCfgAryLen; i++) {
            elem = &SysLink_modCfgAry[i];
            IpcMemMgr_acquire(elem->name, elem->size, &ptr, NULL);
            Memory_copy(ptr, elem->cfg, elem->size);
        }
    }

    /* MultiProc setup */
    if (status >= 0) {
#if defined (USE_SYSLINK_NOTIFY)
        status = MultiProc_setup(&config->multiProcConfig);
#else
        status = multiproc_setup(&config->multiProcConfig);
#endif

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_setup",
                    status, "MultiProc_setup failed");
        }
    }

/* Initialize PROCMGR */
    if (status >= 0) {
        status = ProcMgr_setup (&(config->procMgrConfig));
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ProcMgr_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->procMgrInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

/* Initialize SharedRegion */
    if (status >= 0) {
        status = SharedRegion_setup (&config->sharedRegionConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "SharedRegion_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->sharedRegionInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (USE_SYSLINK_NOTIFY)
    /* Initialize IpcInt required for Notify. */
    if (status >= 0) {
        /* Do the IPC interrupts setup for the full platform (cfg is not used) */
        Dm8168IpcInt_setup (&dm8168cfg);
    }
#endif

/* Initialize NOTIFYDRIVERSHM */
    if (status >= 0) {
#if defined (USE_SYSLINK_NOTIFY)
        status = NotifyDriverShm_setup (&config->notifyDriverShmConfig);
#else
        status = notify_shm_drv_setup ((struct notify_shm_drv_config *)
                                        &config->notifyDriverShmConfig);
#endif
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "NotifyDriverShm_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->notifyDriverShmInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (SYSLINK_NOTIFYDRIVER_CIRC)
/* Initialize NOTIFYDRIVERCIRC */
    if (status >= 0) {
        status = NotifyDriverCirc_setup (&config->notifyDriverCircConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "NotifyDriverCirc_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->notifyDriverCircInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* if defined (SYSLINK_NOTIFYDRIVER_CIRC) */

/* Initialize NOTIFY */
    if (status >= 0) {
#if defined (USE_SYSLINK_NOTIFY)
        status = Notify_setup (&config->notifyConfig);
#else
        status = notify_setup (&config->notifyConfig);
#endif
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "Notify_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->notifyInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

/* Initialize NAMESERVER */
    if (status >= 0) {
        status = NameServer_setup ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "NameServer_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->nameServerInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Initialize Platform */
    if (status >= 0) {
        status = GatePeterson_setup (&config->gatePetersonConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "GatePeterson_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->gatePetersonInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* GateHWSpinlock setup */
    if (status >= 0) {
        status = GateHWSpinlock_setup();

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_setup",
                    status, "GateHWSpinlock_setup failed");
        }
        else {
            Platform_module->gateHWSpinlockInitFlag = TRUE;
        }
    }

    /* GateMP setup */
    if (status >= 0) {
        status = GateMP_setup();

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_setup",
                    status, "GateMP_setup failed");
            status = Platform_E_FAIL;
        }
        else {
            Platform_module->gateMPInitFlag = TRUE;
        }
    }

/* Intialize MESSAGEQ */
    if (status >= 0) {
        status = MessageQ_setup (&config->messageQConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "MessageQ_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Intialize Elf loader */
    if (status >= 0) {
        status = ElfLoader_setup (&config->elfLoaderConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ElfLoader_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->elfLoaderInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Intialize heap buf */
    if (status >= 0) {
        status = HeapBufMP_setup (&config->heapBufConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "HeapBufMP_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->heapBufInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

/* Intialize heap MemMP */
    if (status >= 0) {
        status = HeapMemMP_setup (&config->heapMemMPConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "HeapMemMP_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->heapMemMPInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

/* Get the LISTMPSHAREDMEMORY default config */
    if (status >= 0) {
        status = ListMP_setup (&config->listMPConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ListMP_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->listMPInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }


/* Get the MESSAGEQTRANSPORTSHM default config */
    if (status >= 0) {
        status = TransportShm_setup (&config->messageQTransportShmConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "TransportShm_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQTransportShmInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (SYSLINK_TRANSPORT_SHMNOTIFY)
/* Get the MESSAGEQTRANSPORTSHMNOTIFY default config */
    if (status >= 0) {
        status = TransportShmNotify_setup (
                                    &config->messageQTransportShmNotifyConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "TransportShmNotify_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQTransportShmNotifyInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* if defined (SYSLINK_TRANSPORT_SHMNOTIFY) */


#if defined (SYSLINK_TRANSPORT_SHMCIRC)
/* Get the MESSAGEQTRANSPORTSHMCIRC default config */
    if (status >= 0) {
        status = TransportShmCirc_setup (
                                    &config->messageQTransportShmCircConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "TransportShmCirc_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQTransportShmCircInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* if defined (SYSLINK_TRANSPORT_SHMCIRC) */

/* Get the NAMESERVERREMOTENOTIFY default config */
    if (status >= 0) {
        status = NameServerRemoteNotify_setup (
                                     &config->nameServerRemoteNotifyConfig);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "NameServerRemoteNotify_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->nameServerRemoteNotifyInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Get the ClientNotifyMgr default config */
    if (status >= 0) {
        status = ClientNotifyMgr_setup (&config->cliNotifyMgrCfgParams);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ClientNotifyMgr_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->clientNotifyMgrInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }


    /* Get the FrameQBufMgr default config */
    if (status >= 0) {
        status = FrameQBufMgr_setup (&config->frameQBufMgrCfgParams);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "FrameQBufMgr_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->frameQBufMgrInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Get the FrameQ default config */
    if (status >= 0) {
        status = FrameQ_setup (&config->frameQCfgParams);
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "FrameQ_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->frameQInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    if (status >= 0) {
        Memory_set (Platform_objects,
                    0,
                    (sizeof (Platform_Object) * MultiProc_getNumProcessors()));
    }

    if (status >= 0) {
        status = _Platform_setup ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "_Platform_setup failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->platformInitFlag = TRUE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
    if (status >= 0) {
        /* Store SharedRegion numEntries configuration on Host to compare with
        *  the value configured on slaves
        */
        Platform_module->hostModuleConfig.sharedRegionNumEntries =
                                        config->sharedRegionConfig.numEntries;

    }
    return status;
}

/*!
 *  @brief      Function to destroy the System.
 *
 *  @sa         Platform_setup
 */
Int32
Platform_destroy (void)
{
    Int32  status = Platform_S_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "Platform_destroy");

    /* Finalize Platform-specific destroy */
    if (Platform_module->platformInitFlag == TRUE) {
        status = _Platform_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "Platform_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->platformInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize Frame module */
    if (Platform_module->frameQInitFlag == TRUE) {
        status = FrameQ_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "FrameQ_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->frameQInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize FrameQBufMgr module */
    if (Platform_module->frameQBufMgrInitFlag == TRUE) {
        status = FrameQBufMgr_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "FrameQBufMgr_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->frameQBufMgrInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize ClientNotifyMgr module */
    if (Platform_module->clientNotifyMgrInitFlag == TRUE) {
        status = ClientNotifyMgr_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ClientNotifyMgr_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->clientNotifyMgrInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }


    /* Finalize NAMESERVERREMOTENOTIFY */
    if (Platform_module->nameServerRemoteNotifyInitFlag == TRUE) {
        status = NameServerRemoteNotify_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "NameServerRemoteNotify_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->nameServerRemoteNotifyInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (SYSLINK_TRANSPORT_SHMCIRC)
    /* Finalize MESSAGEQTRANSPORTSHMCIRC */
    if (Platform_module->messageQTransportShmCircInitFlag == TRUE) {
        status = TransportShmCirc_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "TransportShmCirc_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQTransportShmCircInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* if defined (SYSLINK_TRANSPORT_SHMCIRC) */

#if defined (SYSLINK_TRANSPORT_SHMNOTIFY)
    /* Finalize MESSAGEQTRANSPORTSHMNOTIFY */
    if (Platform_module->messageQTransportShmNotifyInitFlag == TRUE) {
        status = TransportShmNotify_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "TransportShmNotify_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQTransportShmNotifyInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* if defined (SYSLINK_TRANSPORT_SHMNOTIFY) */

    /* Finalize MESSAGEQTRANSPORTSHM */
    if (Platform_module->messageQTransportShmInitFlag == TRUE) {
        status = TransportShm_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "TransportShm_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQTransportShmInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize LISTMPSHAREDMEMORY */
    if (Platform_module->listMPInitFlag == TRUE) {
        status = ListMP_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ListMP_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->listMPInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize heap buf */
    if (Platform_module->heapBufInitFlag == TRUE) {
        status = HeapBufMP_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "HeapBufMP_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->heapBufInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize heap MemMP */
    if (Platform_module->heapMemMPInitFlag == TRUE) {
        status = HeapMemMP_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "HeapMemMP_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->heapMemMPInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize elf loader */
    if (Platform_module->elfLoaderInitFlag == TRUE) {
        status = ElfLoader_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ElfLoader_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->elfLoaderInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize MESSAGEQ */
    if (Platform_module->messageQInitFlag == TRUE) {
        status = MessageQ_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "MessageQ_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->messageQInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize GatePeterson */
    if (Platform_module->gatePetersonInitFlag == TRUE) {
        status = GatePeterson_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "GatePeterson_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->gatePetersonInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize GateHWSpinlock */
    if (Platform_module->gateHWSpinlockInitFlag == TRUE) {
        status = GateHWSpinlock_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "GateHWSpinlock_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->gateHWSpinlockInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    if (Platform_module->gateMPInitFlag == TRUE) {
        status = GateMP_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "GateMP_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->gateMPInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize NAMESERVER */
    if (Platform_module->nameServerInitFlag == TRUE) {
        status = NameServer_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "NameServer_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->nameServerInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize NOTIFY */
    if (Platform_module->notifyInitFlag == TRUE) {
#if defined (USE_SYSLINK_NOTIFY)
        status = Notify_destroy ();
#else
        status = notify_destroy ();
#endif
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "Notify_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->notifyInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (SYSLINK_NOTIFYDRIVER_CIRC)
    /* Finalize NOTIFYDRIVERCIRC */
    if (Platform_module->notifyDriverCircInitFlag == TRUE) {
            status = NotifyDriverCirc_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "NotifyDriverCirc_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->notifyDriverCircInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* if defined (SYSLINK_NOTIFYDRIVER_CIRC) */

    /* Finalize NOTIFYSHMDRIVER */
    if (Platform_module->notifyDriverShmInitFlag == TRUE) {
#if defined (USE_SYSLINK_NOTIFY)
        status = NotifyDriverShm_destroy ();
#else
        status = notify_shm_drv_destroy ();
#endif
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "NotifyDriverShm_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->notifyDriverShmInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (USE_SYSLINK_NOTIFY)
    Dm8168IpcInt_destroy ();
#endif

    /* Finalize SharedRegion */
    if (Platform_module->sharedRegionInitFlag == TRUE) {
        status = SharedRegion_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "SharedRegion_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->sharedRegionInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Finalize PROCMGR */
    if (Platform_module->procMgrInitFlag == TRUE) {
        status = ProcMgr_destroy ();
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ProcMgr_destroy failed!");
        }
        else {
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
            Platform_module->procMgrInitFlag = FALSE;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

#if defined (USE_SYSLINK_NOTIFY)
    /* Finalize MultiProc */
    status = MultiProc_destroy ();
#else
    /* Finalize MultiProc */
    status = multiproc_destroy ();
#endif

#if !defined(SYSLINK_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_destroy",
                             status,
                             "MultiProc_destroy failed!");
    }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */

    if (status >= 0) {
        Memory_set (Platform_objects,
                    0,
                    (sizeof (Platform_Object) * MultiProc_getNumProcessors()));
    }

    GT_1trace (curTrace, GT_LEAVE, "Platform_destroy", status);

    /*! @retval Platform_S_SUCCESS Operation successful */
    return status;
}

/*
 * union _Platform_setup_Local exists so that we don't waste stack or
 * alloc'ed memory on storage for things that exist for just a few
 * statements of the function _Platform_setup().  The *PROC_Params
 * elements are large and variably sized, depending on the macro
 * ProcMgr_MAX_MEMORY_REGIONS.
 */
typedef union _Platform_setup_Local {
    ProcMgr_Params           params;
    DM8168DSPPROC_Config     dspProcConfig;
    DM8168VIDEOM3PROC_Config videoProcConfig;
    DM8168VPSSM3PROC_Config  vpssProcConfig;
    DM8168DSPPWR_Config      dspPwrConfig;
    DM8168DUCATIPWR_Config   videoPwrConfig;
    DM8168DUCATIPWR_Config   vpssPwrConfig;
    DM8168DSPPROC_Params     dspProcParams;
    DM8168VIDEOM3PROC_Params videoProcParams;
    DM8168VPSSM3PROC_Params  vpssProcParams;
    DM8168DSPPWR_Params      dspPwrParams;
    DM8168DUCATIPWR_Params   videoPwrParams;
    DM8168DUCATIPWR_Params   vpssPwrParams;
    ElfLoader_Params         elfLoaderParams;
} _Platform_setup_Local;

/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
_Platform_setup (void)
{
    Int32                   status = Platform_S_SUCCESS;
    _Platform_setup_Local   *lv;
    UInt16                  procId;
    Platform_Handle         handle;

    GT_0trace (curTrace, GT_ENTER, "_Platform_setup");

    lv = Memory_alloc(NULL, sizeof(_Platform_setup_Local), 0, NULL);
    if (lv == NULL) {
        status = Platform_E_FAIL;
        GT_setFailureReason (curTrace,
                                GT_4CLASS,
                                "_Platform_setup",
                                status,
                                "Memory_alloc failed");
        goto ret;
    }

#if !defined (SYSLINK_VARIANT_TI813X)
    /* Get MultiProc ID by name. */
    procId = MultiProc_getId ("DSP");

    handle = &Platform_objects [procId];
    DM8168DSPPROC_getConfig (&lv->dspProcConfig);
    status = DM8168DSPPROC_setup (&lv->dspProcConfig);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_setup",
                             status,
                             "DM8168DSPPROC_setup failed!");
    }
    else {
        DM8168DSPPWR_getConfig (&lv->dspPwrConfig);
        status = DM8168DSPPWR_setup (&lv->dspPwrConfig);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "DM8168DSPPWR_setup failed!");
        }
    }

    if (status >= 0) {
        /* Create an instance of the Processor object for
         * DM8168DSP */
        DM8168DSPPROC_Params_init (NULL, &lv->dspProcParams);
        handle->sHandles.dsp.pHandle = DM8168DSPPROC_create (procId,
                                                          &lv->dspProcParams);

        /* Create an instance of the ELF Loader object */
        ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
        handle->sHandles.dsp.ldrHandle =
                                       ElfLoader_create (procId,
                                                         &lv->elfLoaderParams);

        /* Create an instance of the PwrMgr object for DM8168DSP */
        DM8168DSPPWR_Params_init (&lv->dspPwrParams);
        handle->sHandles.dsp.pwrHandle = DM8168DSPPWR_create (procId,
                                                &lv->dspPwrParams);

        if (handle->sHandles.dsp.pHandle == NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "DM8168DSPPROC_create failed!");
        }
        else if (handle->sHandles.dsp.ldrHandle ==  NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "Failed to create loader instance!");
        }
        else if (handle->sHandles.dsp.pwrHandle ==  NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "DM8168DSPPWR_create failed!");
        }
        else {
            /* Initialize parameters */
            ProcMgr_Params_init (NULL, &lv->params);
            lv->params.procHandle = handle->sHandles.dsp.pHandle;
            lv->params.loaderHandle = handle->sHandles.dsp.ldrHandle;
            lv->params.pwrHandle = handle->sHandles.dsp.pwrHandle;
            String_cpy (lv->params.rstVectorSectionName,
                        RESETVECTOR_SYMBOL);
            handle->pmHandle = ProcMgr_create (procId, &lv->params);
            if (handle->pmHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "ProcMgr_create failed!");
            }
        }
    }
#endif /* #if !defined (SYSLINK_VARIANT_TI813X) */

    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("VIDEO-M3");

        handle = &Platform_objects [procId];
        DM8168VIDEOM3PROC_getConfig (&lv->videoProcConfig);
        status = DM8168VIDEOM3PROC_setup (&lv->videoProcConfig);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "DM8168VIDEOM3PROC_setup failed!");
        }
        else {
            DM8168DUCATIPWR_getConfig (&lv->videoPwrConfig);
            status = DM8168DUCATIPWR_setup (&lv->videoPwrConfig);
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "DM8168DUCATIPWR_setup failed!");
            }
        }

        if (status >= 0) {
            /* Create an instance of the Processor object for
             * DM8168VIDEOM3 */
            DM8168VIDEOM3PROC_Params_init (NULL, &lv->videoProcParams);
            handle->sHandles.m3video.pHandle = DM8168VIDEOM3PROC_create (
                                                        procId,
                                                        &lv->videoProcParams);

            /* Create an instance of the ELF Loader object */
            ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
            handle->sHandles.m3video.ldrHandle = ElfLoader_create (procId,
                                                        &lv->elfLoaderParams);

            /* Create an instance of the PwrMgr object for DM8168VIDEOM3 */
            DM8168DUCATIPWR_Params_init (&lv->videoPwrParams);
            handle->sHandles.m3video.pwrHandle = DM8168DUCATIPWR_create (
                                                         procId,
                                                         &lv->videoPwrParams);

            if (handle->sHandles.m3video.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "DM8168VIDEOM3PROC_create failed!");
            }
            else if (handle->sHandles.m3video.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else if (handle->sHandles.m3video.pwrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "DM8168DUCATIPWR_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &lv->params);
                lv->params.procHandle = handle->sHandles.m3video.pHandle;
                lv->params.loaderHandle = handle->sHandles.m3video.ldrHandle;
                lv->params.pwrHandle = handle->sHandles.m3video.pwrHandle;
                String_cpy (lv->params.rstVectorSectionName,
                            RESETVECTOR_SYMBOL);
                handle->pmHandle = ProcMgr_create (procId, &lv->params);
                if (handle->pmHandle == NULL) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_setup",
                                         status,
                                         "ProcMgr_create failed!");
                }
            }
        }
    }

    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("VPSS-M3");

        handle = &Platform_objects [procId];
        DM8168VPSSM3PROC_getConfig (&lv->vpssProcConfig);
        status = DM8168VPSSM3PROC_setup (&lv->vpssProcConfig);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "DM8168VPSSM3PROC_setup failed!");
        }
        else {
            DM8168DUCATIPWR_getConfig (&lv->vpssPwrConfig);
            status = DM8168DUCATIPWR_setup (&lv->vpssPwrConfig);
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "DM8168DUCATIPWR_setup failed!");
            }
        }

        if (status >= 0) {
            /* Create an instance of the Processor object for
             * DM8168VPSSM3 */
            DM8168VPSSM3PROC_Params_init (NULL, &lv->vpssProcParams);
            handle->sHandles.m3vpss.pHandle = DM8168VPSSM3PROC_create (procId,
                                                         &lv->vpssProcParams);

            /* Create an instance of the ELF Loader object */
            ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
            handle->sHandles.m3vpss.ldrHandle = ElfLoader_create (procId,
                                                        &lv->elfLoaderParams);

            /* Create an instance of the PwrMgr object for DM8168VPSSM3 */
            DM8168DUCATIPWR_Params_init (&lv->vpssPwrParams);
            handle->sHandles.m3vpss.pwrHandle = DM8168DUCATIPWR_create (
                                                           procId,
                                                           &lv->vpssPwrParams);

            if (handle->sHandles.m3vpss.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "DM8168VPSSM3PROC_create failed!");
            }
            else if (handle->sHandles.m3vpss.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else if (handle->sHandles.m3vpss.pwrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "DM8168DUCATIPWR_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &lv->params);
                lv->params.procHandle = handle->sHandles.m3vpss.pHandle;
                lv->params.loaderHandle = handle->sHandles.m3vpss.ldrHandle;
                lv->params.pwrHandle = handle->sHandles.m3vpss.pwrHandle;
                String_cpy (lv->params.rstVectorSectionName,
                            RESETVECTOR_SYMBOL);
                handle->pmHandle = ProcMgr_create (procId, &lv->params);
                if (handle->pmHandle == NULL) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_setup",
                                         status,
                                         "ProcMgr_create failed!");
                }
            }
        }
    }

    Memory_free(NULL, lv, sizeof(_Platform_setup_Local));

ret:
    GT_1trace (curTrace, GT_LEAVE, "_Platform_setup", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}

/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
_Platform_destroy (void)
{
    Int32           status    = Platform_S_SUCCESS;
    Int32           tmpStatus = Platform_S_SUCCESS;
    Platform_Handle handle;

    GT_0trace (curTrace, GT_ENTER, "_Platform_destroy");

#if !defined (SYSLINK_VARIANT_TI813X)
    /* ------------------------- DSP cleanup -------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("DSP")];
    if (handle->pmHandle != NULL) {
        status = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (status >= 0));
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
        }
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.dsp.pwrHandle != NULL) {
        tmpStatus = DM8168DSPPWR_delete (&handle->sHandles.dsp.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "DM8168DSPPWR_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.dsp.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.dsp.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.dsp.pHandle != NULL) {
        tmpStatus = DM8168DSPPROC_delete (&handle->sHandles.dsp.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "DM8168DSPPROC_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = DM8168DSPPWR_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "DM8168DSPPWR_destroy failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    tmpStatus = DM8168DSPPROC_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "DM8168DSPPROC_destroy failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }
#endif /* #if !defined (SYSLINK_VARIANT_TI813X) */
    /* ------------------------- VIDEOM3 cleanup ------------------------------ */
    handle = &Platform_objects [MultiProc_getId ("VIDEO-M3")];
    if (handle->pmHandle != NULL) {
        tmpStatus = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.m3video.pwrHandle != NULL) {
        tmpStatus = DM8168DUCATIPWR_delete (&handle->sHandles.m3video.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "DM8168DUCATIPWR_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.m3video.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.m3video.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.m3video.pHandle != NULL) {
        tmpStatus = DM8168VIDEOM3PROC_delete (&handle->sHandles.m3video.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "DM8168VIDEOM3PROC_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = DM8168DUCATIPWR_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "DM8168DUCATIPWR_destroy failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    tmpStatus = DM8168VIDEOM3PROC_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "DM8168VIDEOM3PROC_destroy failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    /* ------------------------- VPSSM3 cleanup -------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("VPSS-M3")];
    if (handle->pmHandle != NULL) {
        tmpStatus = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.m3vpss.pwrHandle != NULL) {
        tmpStatus = DM8168DUCATIPWR_delete (&handle->sHandles.m3vpss.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "DM8168DUCATIPWR_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.m3vpss.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.m3vpss.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.m3vpss.pHandle != NULL) {
        tmpStatus = DM8168VPSSM3PROC_delete (&handle->sHandles.m3vpss.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "DM8168VPSSM3PROC_delete failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = DM8168DUCATIPWR_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "DM8168DUCATIPWR_destroy failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    tmpStatus = DM8168VPSSM3PROC_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(SYSLINK_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "DM8168VPSSM3PROC_destroy failed!");
#endif /* if !defined(SYSLINK_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "_Platform_destroy", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}

/*!
 *  @brief      Function called by ProcMgr when slave is in loaded state.
 *
 *  @param      arg   Registered argument.
 */
Int32 Platform_loadCallback(UInt16 procId, Ptr arg)
{
    Int32                   status = Platform_S_SUCCESS;
    Platform_Handle         handle;
    UInt32                  start;
    UInt32                  numBytes;
    SharedRegion_Entry      entry;
    UInt32                  mAddr;
    ProcMgr_AddrInfo        ai;
    Ipc_Params              iParams;
    Int                     i;
    UInt32                  mapMask;
    UInt32                  fileId;
    Char                    str[64];
    ProcMgr_AttachParams    attachParams;

    GT_2trace(curTrace, GT_ENTER,
        "Platform_loadCallback: prodId=%d, arg=0x%08x", procId, arg);

    /* TODO: enter gate */
    /* TODO: reference count by procId */

    handle = (Platform_Handle)&Platform_objects[procId];

    /* acquire the reset vector address */
    if (arg != NULL) {
        start = (*(UInt32 *)arg); /* arg is reset vector in slave va */

        /* Call ProcMgr_attach as slave has already been loaded */
        ProcMgr_getAttachParams (handle->pmHandle, &attachParams);
        /*
         * Power up the SysLink peripherals but do not boot if external loader
         * is used.
         */
        attachParams.bootMode = ProcMgr_BootMode_NoBoot;
        status = ProcMgr_attach(handle->pmHandle, &attachParams);
        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
                status, "ProcMgr_attach failed");
            goto leave;
        }
    }
    else {
        /* read the reset vector symbol from slave binary */
        fileId = ProcMgr_getLoadedFileId(handle->pmHandle);

        status = ProcMgr_getSymbolAddress(handle->pmHandle, fileId,
            RESETVECTOR_SYMBOL, &start);

        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
                status, "ProcMgr_getSymbolAddress failed");
            goto leave;
        }
    }

    /* read the slave's embedded configuration structure */
    numBytes = sizeof(Platform_SlaveConfig);

    status = _Platform_readSlaveMemory(procId, start, &handle->slaveCfg,
        &numBytes);

    if (status < 0) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
            status, "_Platform_readSlaveMemory failed");
        goto leave;
    }

    /* read the slave shared region config */
    if (handle->slaveCfg.numSRs > 0) {

        /* allocate space for slave's shared region configuration */
        numBytes = handle->slaveCfg.numSRs * sizeof(Platform_SlaveSRConfig);
        handle->slaveSRCfg = Memory_alloc(NULL, numBytes, 0, NULL);

        if (handle->slaveSRCfg == NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS,
                "Platform_loadCallback", status, "Memory_alloc failed");
            goto leave;
        }

        /* allocate space for new region flag array */
        handle->bslaveAdditionalReg = Memory_calloc(NULL,
            (handle->slaveCfg.numSRs * sizeof(UInt8)), 0, NULL);

        if (handle->bslaveAdditionalReg == NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS,
                "Platform_loadCallback", status, "Memory_calloc failed");
            goto leave;
        }

        /* read the slave's embedded shared region configuration */
        status = _Platform_readSlaveMemory(procId,
            start + sizeof(Platform_SlaveConfig), handle->slaveSRCfg,
            &numBytes);

        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS,
                "Platform_loadCallback", status,
                "_Platform_readSlaveMemory failed");
            goto leave;
        }
    }

    /* create and ipc instance */
    iParams.setupMessageQ = handle->slaveCfg.setupMessageQ;
    iParams.setupNotify   = handle->slaveCfg.setupNotify;
    iParams.procSync      = handle->slaveCfg.procSync;

    status = Ipc_create(procId, &iParams);

    if (status < 0) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
            status, "Ipc_create failed");
        goto leave;
    }

    /* add new shared region entries to table */
    for (i = 0; i < handle->slaveCfg.numSRs; i++) {
        GT_2trace(curTrace, GT_1CLASS, "handle->slaveSRCfg[%d].entryBase %p\n",
            i, handle->slaveSRCfg[i].entryBase);

        /* get entry from table */
        status = SharedRegion_getEntry(handle->slaveSRCfg[i].id, &entry);

        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
                status, "SharedRegion_getEntry failed");
            goto leave;
        }

        /* if entry already started, validate properties on new entry */
        if (entry.isValid) {
            if (entry.len != handle->slaveSRCfg[i].entryLen) {
                status = -1;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "Platform_loadCallback", status,
                    "length of slave region does not match host entry");
                goto leave;
            }
            if (entry.ownerProcId != handle->slaveSRCfg[i].ownerProcId) {
                status = -1;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "Platform_loadCallback", status,
                    "owner of slave region does not match host entry");
                goto leave;
            }
            if (entry.createHeap != handle->slaveSRCfg[i].createHeap) {
                status = -1;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "Platform_loadCallback", status,
                    "createHeap of slave region does not match host entry");
                goto leave;
            }
        }

        /* translate the slave address to master physical address */
        status = ProcMgr_translateAddr(handle->pmHandle, (Ptr *)&mAddr,
            ProcMgr_AddrType_MasterPhys, (Ptr)handle->slaveSRCfg[i].entryBase,
            ProcMgr_AddrType_SlaveVirt);

        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason (curTrace, GT_4CLASS, "Platform_loadCallback",
                status, "ProcMgr_translateAddr failed");
            goto leave;
        }

        /* setup address info structure for shared region */
        ai.addr[ProcMgr_AddrType_MasterPhys] = mAddr;
        ai.addr[ProcMgr_AddrType_SlaveVirt] = handle->slaveSRCfg[i].entryBase;
        ai.size = handle->slaveSRCfg[i].entryLen;
        ai.isCached = FALSE;

        /* check for shared region cache override param */
        sprintf(str, "SharedRegion.entry[%d].cacheEnable=",
                handle->slaveSRCfg[i].id);

        status = Cfg_propBool(str, ProcMgr_sysLinkCfgParams, &ai.isCached);

        if (!status) {
            GT_2trace(curTrace, GT_1CLASS, "Platform_loadCallback:\n"
                "    Found SharedRegion.entry[%d].cacheEnable"
                " configuration value %d\n", handle->slaveSRCfg[i].id,
                ai.isCached);
        }
        else {
            GT_1trace(curTrace, GT_1CLASS, "Platform_loadCallback:\n"
                "    No SharedRegion.entry[%d].cacheEnable configuration "
                "value found, using default FALSE\n",
                handle->slaveSRCfg[i].id);
        }

        GT_5trace(curTrace, GT_1CLASS, "Platform_loadCallback:\n"
            "    Mapping SharedRegion %d\n"
            "    addr[ProcMgr_AddrType_MasterPhys] [0x%x]\n"
            "    addr[ProcMgr_AddrType_SlaveVirt]  [0x%x]\n"
            "    size                              [0x%x]\n"
            "    isCached                          [%d]\n",
            handle->slaveSRCfg[i].id, ai.addr[ProcMgr_AddrType_MasterPhys],
            ai.addr[ProcMgr_AddrType_SlaveVirt], ai.size, ai.isCached);

        /* if entry already started, validate cache property on new entry */
        if (entry.isValid) {
            if (entry.cacheEnable != ai.isCached) {
                status = -1;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "Platform_loadCallback", status,
                    "cannot change cache property of existing shared region");
                goto leave;
            }
        }

        /* always map region into slave virtual address space */
        mapMask = ProcMgr_SLAVEVIRT;

        /* map region into kernel only if region has a heap */
        if ((Bool)handle->slaveSRCfg[i].createHeap) {
            mapMask |= ProcMgr_MASTERKNLVIRT;
        }

        /* map the shared region as requested */
        status = ProcMgr_map(handle->pmHandle, mapMask, &ai,
            ProcMgr_AddrType_MasterPhys);

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS,
                "Platform_loadCallback", status, "ProcMgr_map failed!");
            goto leave;
        }

        /* if entry already started, validate base address on new entry */
        if (entry.isValid && entry.cacheEnable) {
            if (entry.base != (Ptr)ai.addr[ProcMgr_AddrType_MasterKnlVirt]) {
                status = -1;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "Platform_loadCallback", status,
                    "inconsistent entry base address");
                goto leave;
            }
        }

        /* add new entry to shared region table */
        if (!entry.isValid) {

            /* If the entry has a heap, set the entry base address to the
             * kernel virtual address; otherwise use the master physical
             * address.
             */
            if (handle->slaveSRCfg[i].createHeap) {
                entry.base = (Ptr)ai.addr[ProcMgr_AddrType_MasterKnlVirt];
            }
            else {
                entry.base = (Ptr)mAddr;
            }
            entry.len = handle->slaveSRCfg[i].entryLen;
            entry.ownerProcId = handle->slaveSRCfg[i].ownerProcId;
/* TODO */  entry.cacheLineSize = handle->slaveSRCfg[i].cacheLineSize;
            entry.isValid = TRUE;
            entry.cacheEnable = ai.isCached;
            entry.createHeap = handle->slaveSRCfg[i].createHeap;

            /* if shared region already started, add new entry */
            if (_SharedRegion_isStarted()) {
                status = SharedRegion_setEntry(handle->slaveSRCfg[i].id,&entry);

                if (status < 0) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason(curTrace, GT_4CLASS,
                        "Platform_loadCallback", status,
                        "SharedRegion_setEntry failed");
                    goto leave;
                }
                handle->bslaveAdditionalReg[i] = TRUE;
            }
            else {
                _SharedRegion_setEntry(handle->slaveSRCfg[i].id, &entry);
            }
        }
        else {
            /* set existing shared region entry to update reference count */
            if (_SharedRegion_isStarted()) {
                status = SharedRegion_setEntry(
                    handle->slaveSRCfg[i].id, &entry);

                if (status < 0) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason(curTrace, GT_4CLASS,
                        "Platform_loadCallback", status,
                        "SharedRegion_setEntry failed");
                    goto leave;
                }
                handle->bslaveAdditionalReg[i] = TRUE;
            }
            else {
                /* should never get here */
                GT_assert(curTrace, TRUE);
            }
        }
    } /* for (each shared region entry) */

    /* update slave's configuration */
    numBytes = sizeof(Platform_SlaveConfig);
    handle->slaveCfg.sr0MemorySetup = 1;  /* set ready flag */

    status = _Platform_writeSlaveMemory(procId, start, &handle->slaveCfg,
        &numBytes);

    if (status < 0) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
            status, "_Platform_writeSlaveMemory failed");
        goto leave;
    }

    /* start all ipc modules */
    status = Ipc_start();

    if (status < 0) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_loadCallback",
            status, "Ipc_start failed");
        goto leave;
    }

    /* increase refCount for number of successful loadCallbacks */
    handle->refCount++;

leave:
    /* if error, release resources in reverse order of acquisition */
    if (status < 0) {
        /* TODO: release map entries acquired in for loop */
        /* TODO: if Ipc_start failed, slave already running, what now? */
        if (handle->bslaveAdditionalReg != NULL) {
            Memory_free(NULL, handle->bslaveAdditionalReg,
                handle->slaveCfg.numSRs * sizeof(UInt8));
            handle->bslaveAdditionalReg = NULL;
        }
        if (handle->slaveSRCfg != NULL) {
            Memory_free(NULL, handle->slaveSRCfg,
                handle->slaveCfg.numSRs * sizeof(Platform_SlaveSRConfig));
            handle->slaveSRCfg = NULL;
        }
    }
    GT_1trace(curTrace, GT_LEAVE, "Platform_loadCallback: [0x%08x]", status);

    return (status);
}
EXPORT_SYMBOL(Platform_loadCallback);

/*!
 *  @brief      Function called by ProcMgr when slave is in started state.
 *              In case of self boot mode, slave and host both has to create
 *              the notifyDriver outside of SysMgr context. Since an event is
 *              sent to slave to indicate that HOST has done initialization on
 *              its side and it is safe for slave to do the rest of
 *              initialization.
 *              TBD: logic would change completely in the final system.
 *              TBD: update other slave about this slave's state change.
 *
 *  @param      arg   Registered argument.
 */
Int32
Platform_startCallback (UInt16 procId, Ptr arg)
{
    Int32 status = Platform_S_SUCCESS;
    Syslink_SlaveModuleConfig slaveModuleConfig;
    UInt32  startTimeout;

    GT_2trace (curTrace, GT_ENTER, "Platform_startCallback", procId, arg);

    /* TODO: enter gate */
    startTimeout = 0;

    /* Attach to slave cores */
    do {
        startTimeout++;
        status = Ipc_attach(procId);

        if ((status == Ipc_E_NOTREADY) && ((startTimeout & 0xFFF) == 0)) {
            OsalThread_sleep(ATTACH_SLEEPTIME);
        }
    } while ((status == Ipc_E_NOTREADY) && (startTimeout < ATTACH_LOOPCNT));

    /* Check timeout value */
    if (startTimeout >= ATTACH_LOOPCNT) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_startCallback",
            status, "Ipc_attach timeout");
        goto end;
    }

    /* Reset timeout value */
    startTimeout = 0;

    /* Get shared region max numEntries from Slave */
    do {
        if (startTimeout > 0) {
            OsalThread_sleep(CFG_SLEEPTIME);
        }

        status = Ipc_readConfig(procId, SLAVE_CONFIG_TAG,
                (Ptr)&slaveModuleConfig, sizeof(Syslink_SlaveModuleConfig));

    } while ((status == Ipc_E_FAIL) && (++startTimeout < CFG_LOOPCNT));

    /* Check timeout value */
    if (startTimeout >= CFG_LOOPCNT) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_startCallback",
            status, "Ipc_readConfig timeout");
        goto end;
    }

    GT_assert (curTrace,
              (    Platform_module->hostModuleConfig.sharedRegionNumEntries
               ==  slaveModuleConfig.sharedRegionNumEntries));

    if (    Platform_module->hostModuleConfig.sharedRegionNumEntries
        !=  slaveModuleConfig.sharedRegionNumEntries) {

        status = Platform_E_FAIL;
        GT_setFailureReason (curTrace,
                     GT_4CLASS,
                     "Platform_startCallback",
                     status,
                     "SharedRegion numEntries did not match with slave side");

        GT_4trace (curTrace,
                   GT_4CLASS,
                   "Platform_startCallback:\n"
                   "    Master procId = [%u]\n"
                   "    Slave  procId = [%u]\n"
                   "    SharedRegion numEntries on (Hlos)Master = [%u]\n"
                   "    SharedRegion numEntries on  (Rtos)Slave = [%u]\n",
                   MultiProc_self(),
                   procId,
                   Platform_module->hostModuleConfig.sharedRegionNumEntries,
                   slaveModuleConfig.sharedRegionNumEntries);
    }

    /* TODO: leave gate */

    /* save the terminate event configuration for this remote processor */
    Platform_module->termEvtAry[procId].eventId =
            slaveModuleConfig.terminateEventId;
    Platform_module->termEvtAry[procId].lineId =
            slaveModuleConfig.terminateEventLineId;

end:
    GT_1trace (curTrace, GT_LEAVE, "Platform_startCallback", status);

    return status;
}

EXPORT_SYMBOL(Platform_startCallback);

/*!
 *  @brief      Function called by ProcMgr when slave is in stopped state.
 *              TBD: logic would change completely in the final system.
 *
 *  @param      arg   Registered argument.
 */
Int32 Platform_stopCallback(UInt16 procId, Ptr arg)
{
    typedef struct {
        Ptr     basePhys;       /* MasterPhys */
        Ptr     baseKnl;        /* MasterKnlVirt */
        Ptr     baseSlave;      /* SlaveVirt */
        UInt32  mask;           /* unmap mask */
        Bool    cache;          /* cache enable */
    } UnmapInfo;

    Int32                   status = Platform_S_SUCCESS;
    UInt32                  i;
    UInt32                  mAddr;
    UInt32                  start;
    UInt32                  numBytes;
    UInt32                  detachTimeout;
    UInt32                  fileId;
    ProcMgr_AddrInfo        ai;
    Platform_Handle         handle;
    SharedRegion_Entry      entry;
    UnmapInfo *             uiAry = NULL;
    ProcMgr_State           procState;

    GT_2trace(curTrace, GT_ENTER, "Platform_stopCallback", procId, arg);

    handle = (Platform_Handle)&Platform_objects[procId];

    GT_assert(curTrace, (handle != NULL));

    /* acquire the reset vector address */
    if (arg != NULL) {
        start = (*(UInt32 *)arg); /* arg is reset vector in slave va */
    }
    else {
        /* read the reset vector symbol from slave binary */
        fileId = ProcMgr_getLoadedFileId(handle->pmHandle);

        status = ProcMgr_getSymbolAddress(handle->pmHandle, fileId,
            RESETVECTOR_SYMBOL, &start);

        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
                status, "ProcMgr_getSymbolAddress failed");
            goto leave;
        }
    }

    /* cache region information, cannot access data afte Ipc_stop() */
    uiAry = Memory_alloc(NULL,
        (sizeof(UnmapInfo) * handle->slaveCfg.numSRs), 0, NULL);

    if (uiAry == NULL) {
        status = Platform_E_FAIL;
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
            status, "Memory_alloc failed");
        goto leave;
    }

    for (i = 0; i < handle->slaveCfg.numSRs; i++) {
        status = SharedRegion_getEntry(handle->slaveSRCfg[i].id, &entry);

        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
                status, "SharedRegion_getEntry failed");
            goto leave;
        }

        /* always unmap region from slave virtual address space */
        uiAry[i].baseSlave = (Ptr)handle->slaveSRCfg[i].entryBase;
        uiAry[i].mask = ProcMgr_SLAVEVIRT;

        /* if region has a heap, then also unmap from kernel address space */
        if (entry.createHeap) {
            uiAry[i].mask |= ProcMgr_MASTERKNLVIRT;
            uiAry[i].baseKnl = entry.base;

            /* translate the slave address to master physical address */
            status = ProcMgr_translateAddr(handle->pmHandle, (Ptr *)&mAddr,
                ProcMgr_AddrType_MasterPhys,
                (Ptr)handle->slaveSRCfg[i].entryBase,
                ProcMgr_AddrType_SlaveVirt);

            if (status < 0) {
                status = Platform_E_FAIL;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "Platform_stopCallback", status,
                    "ProcMgr_translateAddr failed");
                goto leave;
            }

            uiAry[i].basePhys = (Ptr)mAddr;
        }
        else {
            uiAry[i].basePhys = entry.base;  /* MasterPhys */
            uiAry[i].baseKnl = NULL;
        }

        /* save the region's cache property */
        uiAry[i].cache = entry.cacheEnable;

        /* TODO: don't clearEntry for SR#0 */

        /* stop regions that were exclusively started for this slave */
        if (handle->bslaveAdditionalReg[i] == TRUE) {
            SharedRegion_clearEntry(handle->slaveSRCfg[i].id);
            handle->bslaveAdditionalReg[i] = FALSE;
        }
    }

    /* do IPC cleanup */
    detachTimeout = 0;

    do {
        detachTimeout++;
        status = Ipc_detach(procId);

        if ((status < 0) && ((detachTimeout & 0xFFF) == 0)) {
            OsalThread_sleep(DETACH_SLEEPTIME);
        }
    } while ((status < 0) && (detachTimeout < DETACH_LOOPCNT));

    if (detachTimeout >= DETACH_LOOPCNT) {
        GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
            status, "Ipc_detach timeout");
        /* don't exit, keep going */
    }

    /* wait for remote processor if it is running */
    procState = ProcMgr_getState(handle->pmHandle);

    if ((handle->refCount == 1) && (procState == ProcMgr_State_Running)) {

        /* check for IPC stop on slave until successful or times out */
        detachTimeout = 0;

        do {
            if (detachTimeout > 0) {
                OsalThread_sleep(CFG_SLEEPTIME);
            }

            /* read sr0MemorySetup */
            numBytes = sizeof(Platform_SlaveConfig);

            status = _Platform_readSlaveMemory(procId, start,
                    &handle->slaveCfg, &numBytes);

        } while ((handle->slaveCfg.sr0MemorySetup == 1)
                  && (++detachTimeout < CFG_LOOPCNT));

        if (detachTimeout >= CFG_LOOPCNT) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
                status, "Ipc_stop timeout - Ipc_stop not called by slave?");
            /* don't exit, keep going */
        }
    }

    Ipc_stop();

    /* now unmap slave's shared regions */
    for (i = 0; i < handle->slaveCfg.numSRs; i++) {

        /* setup address info structure for unmapping operation */
        ai.addr[ProcMgr_AddrType_MasterPhys] = (UInt32)uiAry[i].basePhys;
        ai.addr[ProcMgr_AddrType_SlaveVirt] = (UInt32)uiAry[i].baseSlave;
        ai.addr[ProcMgr_AddrType_MasterKnlVirt] = (UInt32)uiAry[i].baseKnl;
        ai.size = handle->slaveSRCfg[i].entryLen;
        ai.isCached = uiAry[i].cache;

        /* unmap the shared region as requested */
        status = ProcMgr_unmap(handle->pmHandle, uiAry[i].mask, &ai,
            ProcMgr_AddrType_MasterPhys);

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
                status, "ProcMgr_unmap failed!");
            goto leave;
        }

    } /* for (each shared region entry) */

    if (arg != NULL) {
        /*
         * Power down the SysLink peripherals.
         */
        status = ProcMgr_detach(handle->pmHandle);
        if (status < 0) {
            status = Platform_E_FAIL;
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_stopCallback",
                status, "ProcMgr_detach failed");
            goto leave;
        }
    }

    handle->refCount--;

leave:
    /* release resources which are no longer needed */
    if (handle->bslaveAdditionalReg != NULL) {
        Memory_free(NULL, handle->bslaveAdditionalReg,
            handle->slaveCfg.numSRs * sizeof (UInt8));
        handle->bslaveAdditionalReg = NULL;
    }
    if (handle->slaveSRCfg != NULL) {
        Memory_free(NULL, handle->slaveSRCfg,
            handle->slaveCfg.numSRs * sizeof (Platform_SlaveSRConfig));
        handle->slaveSRCfg = NULL;
    }
    if (uiAry != NULL) {
        Memory_free(NULL, uiAry, handle->slaveCfg.numSRs * sizeof(UnmapInfo));
        uiAry = NULL;
    }

    GT_1trace(curTrace, GT_LEAVE, "Platform_stopCallback", status);

    return(status);
}

/* TBD: since application has to call this API for now */
EXPORT_SYMBOL(Platform_stopCallback);

/*  ----------------------------------------------------------------------------
 *  Internal functions
 *  ----------------------------------------------------------------------------
 */
/* Function to read slave memory */
Int32
_Platform_readSlaveMemory (UInt16   procId,
                           UInt32   addr,
                           Ptr      value,
                           UInt32 * numBytes)
{
    Int              status = 0;
    Platform_Handle  handle;
    ProcMgr_AddrInfo aInfo;
    UInt32           mAddr;

    GT_4trace (curTrace, GT_ENTER, "_Platform_readSlaveMemory",
    procId, addr, value, numBytes);

    handle = (Platform_Handle) &Platform_objects [procId];

    /* Translate the slave address to master address */
    status = ProcMgr_translateAddr (handle->pmHandle,
                                    (Ptr *)&mAddr,
                                    ProcMgr_AddrType_MasterPhys,
                                    (Ptr)addr,
                                    ProcMgr_AddrType_SlaveVirt);
    if (status < 0) {
        status = Platform_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_readSlaveMemory",
                             status,
                             "ProcMgr_translateAddr failed");
    }
    else {
        status = ProcMgr_translateAddr (handle->pmHandle,
                                        (Ptr *)&mAddr,
                                        ProcMgr_AddrType_MasterKnlVirt,
                                        (Ptr)mAddr,
                                        ProcMgr_AddrType_MasterPhys);
        if (status >= 0) {
            Memory_copy (value, (Ptr) mAddr, *numBytes);
        }
        else {
            /* Map the address */
            aInfo.addr [ProcMgr_AddrType_MasterPhys] = mAddr;
            aInfo.addr [ProcMgr_AddrType_SlaveVirt]  = addr;
            aInfo.size = *numBytes;
            aInfo.isCached = FALSE;
            status = ProcMgr_map(handle->pmHandle,
                    ProcMgr_MASTERKNLVIRT,
                    &aInfo, ProcMgr_AddrType_MasterPhys);
            if (status < 0) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_readSlaveMemory",
                                     status,
                                     "ProcMgr_map failed");
            }
            else {
                Memory_copy (value,
                    (Ptr)aInfo.addr[ProcMgr_AddrType_MasterKnlVirt], *numBytes);
                /* Map the address */
                status = ProcMgr_unmap(handle->pmHandle,
                        ProcMgr_MASTERKNLVIRT,
                        &aInfo, ProcMgr_AddrType_MasterPhys);
                if (status < 0) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_readSlaveMemory",
                                         status,
                                         "ProcMgr_unmap failed");
                }
            }
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "_Platform_readSlaveMemory", status);

    return status;
}


/* Function to write slave memory */
Int32
_Platform_writeSlaveMemory (UInt16   procId,
                            UInt32   addr,
                            Ptr      value,
                            UInt32 * numBytes)
{
    Int              status = 0;
    Platform_Handle  handle;
    ProcMgr_AddrInfo aInfo;
    UInt32           mAddr;

    GT_4trace (curTrace, GT_ENTER, "_Platform_writeSlaveMemory",
    procId, addr, value, numBytes);

    handle = (Platform_Handle) &Platform_objects [procId];

    /* Translate the slave address to master address */
    status = ProcMgr_translateAddr (handle->pmHandle,
                                    (Ptr *)&mAddr,
                                    ProcMgr_AddrType_MasterPhys,
                                    (Ptr)addr,
                                    ProcMgr_AddrType_SlaveVirt);
    if (status < 0) {
        status = Platform_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_writeSlaveMemory",
                             status,
                             "ProcMgr_translateAddr failed");
    }
    else {
        status = ProcMgr_translateAddr (handle->pmHandle,
                                        (Ptr *)&mAddr,
                                        ProcMgr_AddrType_MasterKnlVirt,
                                        (Ptr)mAddr,
                                        ProcMgr_AddrType_MasterPhys);
       if (status >= 0) {
            Memory_copy ((Ptr) mAddr, value, *numBytes);
       }
       else {
            /* Map the address */
            aInfo.addr[ProcMgr_AddrType_MasterPhys] = mAddr;
            aInfo.addr[ProcMgr_AddrType_SlaveVirt] = addr;
            aInfo.size = *numBytes;
            aInfo.isCached = FALSE;
            status = ProcMgr_map(handle->pmHandle,
                    ProcMgr_MASTERKNLVIRT,
                    &aInfo, ProcMgr_AddrType_MasterPhys);
            if (status < 0) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_writeSlaveMemory",
                                     status,
                                     "ProcMgr_map failed");
            }
            else {
                Memory_copy ((Ptr) aInfo.addr[ProcMgr_AddrType_MasterKnlVirt],
                    value, *numBytes);

                /* Unmap the address */
                status = ProcMgr_unmap(handle->pmHandle,
                        ProcMgr_MASTERKNLVIRT, &aInfo,
                        ProcMgr_AddrType_MasterPhys);
                if (status < 0) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_writeSlaveMemory",
                                         status,
                                         "ProcMgr_unmap failed");
                }

            }
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "_Platform_writeSlaveMemory", status);

    return (status);
}

/*
 *  ======== Platform_terminateEventConfig ========
 */
Void Platform_terminateEventConfig(UInt16 procId, UInt32 *eventId,
        UInt16 *lineId)
{

    *eventId = Platform_module->termEvtAry[procId].eventId;
    *lineId = Platform_module->termEvtAry[procId].lineId;
}

Void Platform_terminateHandler(UInt16 procId)
{
    ProcMgr_Handle procHnd;

    procHnd = _ProcMgr_getHandle(procId);
    Platform_stopCallback(procId, NULL);
    ProcMgr_stop(procHnd);
}
