#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.C674{1,0,7.2,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674.dep
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674.dep: ;
endif

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674: package/package_ti.sdo.edma3.rm.sample.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.s674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.s674: package/package_ti.sdo.edma3.rm.sample.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.s674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674.dep
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674.dep: ;
endif

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674: src/platforms/sample_c6748_cfg.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.s674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.s674: src/platforms/sample_c6748_cfg.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.s674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674.dep
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674.dep: ;
endif

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674: src/platforms/sample_c6748_int_reg.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.s674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.s674: src/platforms/sample_c6748_int_reg.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.s674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674.dep
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674.dep: ;
endif

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674: src/sample_cs.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.s674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.s674: src/sample_cs.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.s674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674.dep
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674.dep: ;
endif

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674: src/sample_init.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.s674: | .interfaces
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.s674: src/sample_init.c lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo  -DCHIP_C6748 -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src -fr=./package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.s674: export C_DIR=
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

clean,674 ::
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.s674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.s674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.s674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.s674
	-$(RM) package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.s674

lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674: package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/package/package_ti.sdo.edma3.rm.sample.o674 package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_cfg.o674 package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/platforms/sample_c6748_int_reg.o674 package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_cs.o674 package/lib/lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample/src/sample_init.o674 lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak

clean::
	-$(RM) lib/c6748-evm/674/release/ti.sdo.edma3.rm.sample.a674.mak
