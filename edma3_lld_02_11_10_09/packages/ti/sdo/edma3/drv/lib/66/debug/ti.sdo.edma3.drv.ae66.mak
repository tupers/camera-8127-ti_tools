#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.elf.C66{1,0,7.2,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66.dep
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66.dep: ;
endif

package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66: package/package_ti.sdo.edma3.drv.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/package -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se66: package/package_ti.sdo.edma3.drv.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/package -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66.dep
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66.dep: ;
endif

package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66: src/edma3_drv_init.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/src -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.se66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.se66: src/edma3_drv_init.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/src -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.se66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66.dep
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66.dep: ;
endif

package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66: src/edma3_drv_basic.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/src -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.se66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.se66: src/edma3_drv_basic.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/src -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.se66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66.dep
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66.dep: ;
endif

package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66: src/edma3_drv_adv.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/src -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.se66: | .interfaces
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.se66: src/edma3_drv_adv.c lib/66/debug/ti.sdo.edma3.drv.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/66/debug/ti.sdo.edma3.drv/src -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo  -D_DEBUG_=1  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src -fr=./package/lib/lib/66/debug/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.se66: export C_DIR=
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)
package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.se66: Path:=$(ti.targets.elf.C66.rootDir)/bin/;$(PATH)

clean,e66 ::
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.se66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.se66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.se66
	-$(RM) package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.se66

lib/66/debug/ti.sdo.edma3.drv.ae66: package/lib/lib/66/debug/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.oe66 package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_init.oe66 package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_basic.oe66 package/lib/lib/66/debug/ti.sdo.edma3.drv/src/edma3_drv_adv.oe66 lib/66/debug/ti.sdo.edma3.drv.ae66.mak

clean::
	-$(RM) lib/66/debug/ti.sdo.edma3.drv.ae66.mak
