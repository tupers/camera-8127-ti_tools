#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.Arm9{1,0,4.9,0
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9.dep
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9.dep: ;
endif

package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9: package/package_ti.sdo.edma3.drv.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c  -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -s oe9 $< -C   -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se9: package/package_ti.sdo.edma3.drv.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 -n $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -s oe9 $< -C  -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9.dep
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9.dep: ;
endif

package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9: src/edma3_drv_init.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c  -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -s oe9 $< -C   -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.se9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.se9: src/edma3_drv_init.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 -n $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -s oe9 $< -C  -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.se9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.se9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.se9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9.dep
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9.dep: ;
endif

package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9: src/edma3_drv_basic.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c  -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -s oe9 $< -C   -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.se9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.se9: src/edma3_drv_basic.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 -n $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -s oe9 $< -C  -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.se9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.se9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.se9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9.dep
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9.dep: ;
endif

package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9: src/edma3_drv_adv.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c  -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -s oe9 $< -C   -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.se9: | .interfaces
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.se9: src/edma3_drv_adv.c lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle9 -n $< ...
	$(ti.targets.arm.elf.Arm9.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -s oe9 $< -C  -n -s --symdebug:none -qq -pdsw225 -me -mv5e --abi=eabi -eo.oe9 -ea.se9    -Dxdc_target_name__=Arm9 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.Arm9.rootDir)/include/rts -I$(ti.targets.arm.elf.Arm9.rootDir)/include  -fs=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/arm9/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.se9: export C_DIR=
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.se9: PATH:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)
package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.se9: Path:=$(ti.targets.arm.elf.Arm9.rootDir)/bin/;$(PATH)

clean,e9 ::
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.se9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.se9
	-$(RM) package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.se9

lib/arm9/release/ti.sdo.edma3.drv.ae9: package/lib/lib/arm9/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe9 package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_init.oe9 package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_basic.oe9 package/lib/lib/arm9/release/ti.sdo.edma3.drv/src/edma3_drv_adv.oe9 lib/arm9/release/ti.sdo.edma3.drv.ae9.mak

clean::
	-$(RM) lib/arm9/release/ti.sdo.edma3.drv.ae9.mak
