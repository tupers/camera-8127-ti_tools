#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.elf.C66{1,0,7.2,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66.dep
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66.dep: ;
endif

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66: package/package_ti.sdo.edma3.rm.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.se66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.se66: package/package_ti.sdo.edma3.rm.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.se66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66.dep
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66.dep: ;
endif

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66: src/configs/edma3_tci6638k2k_cfg.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.se66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.se66: src/configs/edma3_tci6638k2k_cfg.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.se66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66.dep
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66.dep: ;
endif

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66: src/edma3resmgr.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.se66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.se66: src/edma3resmgr.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.se66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66.dep
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66.dep: ;
endif

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66: src/edma3_rm_gbl_data.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.se66: | .interfaces
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.se66: src/edma3_rm_gbl_data.c lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src -fr=./package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.se66: export C_DIR=
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

clean,e66 ::
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.se66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.se66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.se66
	-$(RM) package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.se66

lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66: package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oe66 package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/configs/edma3_tci6638k2k_cfg.oe66 package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3resmgr.oe66 package/lib/lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oe66 lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak

clean::
	-$(RM) lib/tci6638k2k-evm/66/debug/ti.sdo.edma3.rm.ae66.mak
