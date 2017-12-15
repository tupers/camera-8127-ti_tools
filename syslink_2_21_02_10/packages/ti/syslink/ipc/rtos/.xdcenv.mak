#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /opt/Project/Camera/Source/ipnc_rdk/../ti_tools/ipc_1_25_03_15/packages;/opt/Project/Camera/Source/ipnc_rdk/../ti_tools/bios_6_37_01_24/packages;/opt/Project/Camera/Source/ipnc_rdk/../ti_tools/syslink_2_21_02_10/packages
override XDCROOT = /opt/Project/Camera/Source/ti_tools/xdctools_3_25_05_94
override XDCBUILDCFG = /opt/Project/Camera/Source/ti_tools/syslink_2_21_02_10/packages/_config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = DEVICE=TI814X SYSLINK_BUILD_OPTIMIZE=1 CGT_C674_ELF_DIR=/opt/Project/Camera/Source/ipnc_rdk/../ti_tools/cgt6x_7_4_6 CGT_M3_ELF_DIR=/opt/Project/Camera/Source/ipnc_rdk/../ti_tools/cgt470_5_1_3 CGT_A8_ELF_DIR= DEVICE_VARIANT=TI814X TI81XXDSP_DMTIMER_FREQ=20000000
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /opt/Project/Camera/Source/ipnc_rdk/../ti_tools/ipc_1_25_03_15/packages;/opt/Project/Camera/Source/ipnc_rdk/../ti_tools/bios_6_37_01_24/packages;/opt/Project/Camera/Source/ipnc_rdk/../ti_tools/syslink_2_21_02_10/packages;/opt/Project/Camera/Source/ti_tools/xdctools_3_25_05_94/packages;../../../..
HOSTOS = Linux
endif
