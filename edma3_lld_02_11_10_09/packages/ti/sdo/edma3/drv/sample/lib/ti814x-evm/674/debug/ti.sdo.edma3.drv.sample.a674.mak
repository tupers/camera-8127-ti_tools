#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.C674{1,0,7.2,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674.dep
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674.dep: ;
endif

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674: package/package_ti.sdo.edma3.drv.sample.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.s674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.s674: package/package_ti.sdo.edma3.drv.sample.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.s674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674.dep
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674.dep: ;
endif

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674: src/platforms/sample_ti814x_cfg.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.s674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.s674: src/platforms/sample_ti814x_cfg.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.s674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674.dep
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674.dep: ;
endif

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674: src/platforms/sample_ti814x_int_reg.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.s674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.s674: src/platforms/sample_ti814x_int_reg.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.s674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674.dep
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674.dep: ;
endif

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674: src/sample_cs.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.s674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.s674: src/sample_cs.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.s674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674.dep
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674.dep: ;
endif

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674: src/sample_init.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.s674: | .interfaces
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.s674: src/sample_init.c lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -D_DEBUG_=1 -DCHIP_TI814X -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_2_3 -g  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src -fr=./package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.s674: export C_DIR=
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

clean,674 ::
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.s674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.s674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.s674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.s674
	-$(RM) package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.s674

lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674: package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/package/package_ti.sdo.edma3.drv.sample.o674 package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_cfg.o674 package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/platforms/sample_ti814x_int_reg.o674 package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_cs.o674 package/lib/lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample/src/sample_init.o674 lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak

clean::
	-$(RM) lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674.mak
