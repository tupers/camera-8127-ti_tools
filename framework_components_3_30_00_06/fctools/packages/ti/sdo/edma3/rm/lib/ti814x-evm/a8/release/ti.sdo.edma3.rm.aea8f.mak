#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.A8F{1,0,4.9,0
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f.dep
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f.dep: ;
endif

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f: package/package_ti.sdo.edma3.rm.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c  -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -s oea8f $< -C   -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.sea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.sea8f: package/package_ti.sdo.edma3.rm.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f -n $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -s oea8f $< -C  -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.sea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.sea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.sea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f.dep
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f.dep: ;
endif

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f: src/configs/edma3_ti814x_cfg.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c  -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -s oea8f $< -C   -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.sea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.sea8f: src/configs/edma3_ti814x_cfg.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f -n $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -s oea8f $< -C  -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.sea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.sea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.sea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f.dep
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f.dep: ;
endif

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f: src/edma3resmgr.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c  -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -s oea8f $< -C   -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.sea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.sea8f: src/edma3resmgr.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f -n $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -s oea8f $< -C  -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.sea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.sea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.sea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f.dep
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f.dep: ;
endif

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f: src/edma3_rm_gbl_data.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c  -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -s oea8f $< -C   -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.sea8f: | .interfaces
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.sea8f: src/edma3_rm_gbl_data.c lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clea8f -n $< ...
	$(ti.targets.arm.elf.A8F.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -s oea8f $< -C  -n -s --symdebug:none -qq -pdsw225 --neon --endian=little -mv7A8 --abi=eabi -eo.oea8f -ea.sea8f   -Dxdc_target_name__=A8F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.A8F.rootDir)/include/rts -I$(ti.targets.arm.elf.A8F.rootDir)/include  -fs=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src -fr=./package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.sea8f: export C_DIR=
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.sea8f: PATH:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.sea8f: Path:=$(ti.targets.arm.elf.A8F.rootDir)/bin/;$(PATH)

clean,ea8f ::
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.sea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.sea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.sea8f
	-$(RM) package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.sea8f

lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f: package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/package/package_ti.sdo.edma3.rm.oea8f package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/configs/edma3_ti814x_cfg.oea8f package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3resmgr.oea8f package/lib/lib/ti814x-evm/a8/release/ti.sdo.edma3.rm/src/edma3_rm_gbl_data.oea8f lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak

clean::
	-$(RM) lib/ti814x-evm/a8/release/ti.sdo.edma3.rm.aea8f.mak
