#*******************************************************************************
#* FILE PURPOSE: Top level makefile for Creating Kernel CCS Projects
#*******************************************************************************
#* FILE NAME: ccsmake.mk
#*
#* DESCRIPTION: Defines Compiler tools paths, CCS path and rule to create and build CCS projects 
#*
#*
#* This is an auto-generated file             
#*******************************************************************************
#*
# (Mandatory) Specify where various tools are installed.

# CCSCGTVER   - C6x Code Generation version to be used for building CCS project
export CCSCGTVER ?= 7.4.2

# CCS_INSTALL_DIR   - TI Code Composer Studio install directory
export CCSV5_INSTALL_DIR ?= C:/ti/ccsv5

ifneq ($(findstring $(CCSVERSION), CCSV5),)
	export CCS_INSTALL_DIR ?= $(CCSV5_INSTALL_DIR)
	export ECLIPSE_CMD ?= "$(CCS_INSTALL_DIR)/eclipse/eclipsec.exe" -noSplash
	export CDTFILE ?= .cproject
endif

# Common Macros used in make

ifndef RMDIR
export RMDIR = DEL /Q /F /S
endif

# PHONY Targets
.PHONY: all clean cleanall .projects 

# FORCE Targets
FORCE: 

# all rule
all: .executables
.executables: .projects
.projects:
.xdcenv.mak:
Package.mak:
package.bld:

#############################################################

# Rule to Build Project HoughLinesDemo_674_LE_COFF

#############################################################

.projects: HoughLinesDemo/HoughLinesDemo_674_LE_COFF

HoughLinesDemo/HoughLinesDemo_674_LE_COFF: HoughLinesDemo/HoughLinesDemo_674_LE_COFF/.project

HoughLinesDemo/HoughLinesDemo_674_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/HoughLinesDemo_674_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name HoughLinesDemo_674_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO/BinImageToEdgelist.c\
 -ccs.linkFile EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO/draw_line.c\
 -ccs.linkFile EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO/hough_wrapper.c\
 -ccs.linkFile EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO/pgmwrite.c\
 -ccs.linkFile EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO/VLIB_testHoughForLines_data.c\
 -ccs.linkFile EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO/lnk.cmd\
 -ccs.setCompilerOptions "-mv6740 -k -mw -Dti_targets_C674 --mem_model:data=far -i../../../../packages -g  -i../../../../ -i../../" @configurations Debug -ccs.setCompilerOptions "-mv6740 -k -mw -Dti_targets_C674 --mem_model:data=far -i../../../../packages -o3 --symdebug:none  -i../../../../ -i../../" @configurations Release -ccs.location HoughLinesDemo/HoughLinesDemo_674_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO "C:/nightlybuilds/vlib/ti/vlib/vlib/examples/HoughLinesDemo" \

	echo EXT_ROOT__HOUGHLINESDEMO_674_LE_COFF_HOUGHLINESDEMO=.././ >> HoughLinesDemo/HoughLinesDemo_674_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/HoughLinesDemo_674_LE_COFF"
	-@ echo Project HoughLinesDemo_674_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/HoughLinesDemo_674_LE_COFF"

clean::
	-$(RMDIR) "HoughLinesDemo/HoughLinesDemo_674_LE_COFF"


#############################################################

# Rule to Build Project RegressionTest_674_LE_COFF

#############################################################

.projects: Regression/RegressionTest_674_LE_COFF

Regression/RegressionTest_674_LE_COFF: Regression/RegressionTest_674_LE_COFF/.project

Regression/RegressionTest_674_LE_COFF/.project: .xdcenv.mak Package.bld Package.mak
	$(ECLIPSE_CMD)  -data "C:/Temp/workspace/RegressionTest_674_LE_COFF" -application com.ti.ccstudio.apps.projectCreate \
 -ccs.name RegressionTest_674_LE_COFF\
 -ccs.device com.ti.ccstudio.deviceModel.C6000.CustomC6000Device\
 -ccs.endianness little\
 -ccs.kind com.ti.ccstudio.managedbuild.core.ProjectKind_Executable \
 -ccs.outputType executable -ccs.linkFile EXT_ROOT__REGRESSIONTEST_674_LE_COFF_REGRESSION/main.c\
 -ccs.linkFile EXT_ROOT__REGRESSIONTEST_674_LE_COFF_REGRESSION/lnk.cmd\
 -ccs.setCompilerOptions "-mv6740 -k -mw -Dti_targets_C674 --mem_model:data=far -i../../../../packages -D__ONESHOTTEST -g  -i../../../../ -i../../" @configurations Debug -ccs.setCompilerOptions "-mv6740 -k -mw -Dti_targets_C674 --mem_model:data=far -i../../../../packages -D__ONESHOTTEST -o3 --symdebug:none  -i../../../../ -i../../" @configurations Release -ccs.location Regression/RegressionTest_674_LE_COFF\
 -ccs.overwrite full \
 -ccs.rts libc.a \
 -ccs.cgtVersion $(CCSCGTVER)\
 -ccs.outputFormat coff\
 -ccs.definePathVariable EXT_ROOT__REGRESSIONTEST_674_LE_COFF_REGRESSION "C:/nightlybuilds/vlib/ti/vlib/vlib/examples/Regression" \

	echo EXT_ROOT__REGRESSIONTEST_674_LE_COFF_REGRESSION=.././ >> Regression/RegressionTest_674_LE_COFF/macros.ini
	-$(RMDIR) "C:/Temp/workspace/RegressionTest_674_LE_COFF"
	-@ echo Project RegressionTest_674_LE_COFF Completed ...
	-@ echo ########################################
	-$(RMDIR) "C:/Temp/workspace/RegressionTest_674_LE_COFF"

clean::
	-$(RMDIR) "Regression/RegressionTest_674_LE_COFF"

