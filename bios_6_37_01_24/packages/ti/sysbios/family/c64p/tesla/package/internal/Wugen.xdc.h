/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-z63
 */

#ifndef ti_sysbios_family_c64p_tesla_Wugen__INTERNAL__
#define ti_sysbios_family_c64p_tesla_Wugen__INTERNAL__

#ifndef ti_sysbios_family_c64p_tesla_Wugen__internalaccess
#define ti_sysbios_family_c64p_tesla_Wugen__internalaccess
#endif

#include <ti/sysbios/family/c64p/tesla/Wugen.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* applyMasks */
#undef ti_sysbios_family_c64p_tesla_Wugen_applyMasks
#define ti_sysbios_family_c64p_tesla_Wugen_applyMasks ti_sysbios_family_c64p_tesla_Wugen_applyMasks__F

/* disableDma */
#undef ti_sysbios_family_c64p_tesla_Wugen_disableDma
#define ti_sysbios_family_c64p_tesla_Wugen_disableDma ti_sysbios_family_c64p_tesla_Wugen_disableDma__F

/* disableEvent */
#undef ti_sysbios_family_c64p_tesla_Wugen_disableEvent
#define ti_sysbios_family_c64p_tesla_Wugen_disableEvent ti_sysbios_family_c64p_tesla_Wugen_disableEvent__F

/* enableDma */
#undef ti_sysbios_family_c64p_tesla_Wugen_enableDma
#define ti_sysbios_family_c64p_tesla_Wugen_enableDma ti_sysbios_family_c64p_tesla_Wugen_enableDma__F

/* enableEvent */
#undef ti_sysbios_family_c64p_tesla_Wugen_enableEvent
#define ti_sysbios_family_c64p_tesla_Wugen_enableEvent ti_sysbios_family_c64p_tesla_Wugen_enableEvent__F

/* getMasks */
#undef ti_sysbios_family_c64p_tesla_Wugen_getMasks
#define ti_sysbios_family_c64p_tesla_Wugen_getMasks ti_sysbios_family_c64p_tesla_Wugen_getMasks__F

/* ierToMasks */
#undef ti_sysbios_family_c64p_tesla_Wugen_ierToMasks
#define ti_sysbios_family_c64p_tesla_Wugen_ierToMasks ti_sysbios_family_c64p_tesla_Wugen_ierToMasks__F

/* hwiRegisterHook */
#define Wugen_hwiRegisterHook ti_sysbios_family_c64p_tesla_Wugen_hwiRegisterHook__I

/* hwiCreateHook */
#define Wugen_hwiCreateHook ti_sysbios_family_c64p_tesla_Wugen_hwiCreateHook__I

/* hwiBeginHook */
#define Wugen_hwiBeginHook ti_sysbios_family_c64p_tesla_Wugen_hwiBeginHook__I

/* intToIrq */
#define Wugen_intToIrq ti_sysbios_family_c64p_tesla_Wugen_intToIrq__I

/* evtToIrq */
#define Wugen_evtToIrq ti_sysbios_family_c64p_tesla_Wugen_evtToIrq__I

/* intToEvt */
#define Wugen_intToEvt ti_sysbios_family_c64p_tesla_Wugen_intToEvt__I

/* Module_startup */
#undef ti_sysbios_family_c64p_tesla_Wugen_Module_startup
#define ti_sysbios_family_c64p_tesla_Wugen_Module_startup ti_sysbios_family_c64p_tesla_Wugen_Module_startup__F

/* Instance_init */
#undef ti_sysbios_family_c64p_tesla_Wugen_Instance_init
#define ti_sysbios_family_c64p_tesla_Wugen_Instance_init ti_sysbios_family_c64p_tesla_Wugen_Instance_init__F

/* Instance_finalize */
#undef ti_sysbios_family_c64p_tesla_Wugen_Instance_finalize
#define ti_sysbios_family_c64p_tesla_Wugen_Instance_finalize ti_sysbios_family_c64p_tesla_Wugen_Instance_finalize__F

/* module */
#define Wugen_module ((ti_sysbios_family_c64p_tesla_Wugen_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_c64p_tesla_Wugen_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sysbios_family_c64p_tesla_Wugen__cplusplus)
#define module ((ti_sysbios_family_c64p_tesla_Wugen_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_c64p_tesla_Wugen_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_family_c64p_tesla_Wugen_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_family_c64p_tesla_Wugen_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_family_c64p_tesla_Wugen_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_family_c64p_tesla_Wugen_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_family_c64p_tesla_Wugen_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_family_c64p_tesla_Wugen_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_family_c64p_tesla_Wugen_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_family_c64p_tesla_Wugen_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_family_c64p_tesla_Wugen_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_family_c64p_tesla_Wugen_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_family_c64p_tesla_Wugen_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_family_c64p_tesla_Wugen_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_family_c64p_tesla_Wugen_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_family_c64p_tesla_Wugen_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_family_c64p_tesla_Wugen_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_family_c64p_tesla_Wugen_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_family_c64p_tesla_Wugen_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_family_c64p_tesla_Wugen_Module_GateProxy_query


#endif /* ti_sysbios_family_c64p_tesla_Wugen__INTERNAL____ */
