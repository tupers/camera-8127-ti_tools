#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.C674{1,0,7.2,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674.dep
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674.dep: ;
endif

package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674: package/package_ti.sdo.edma3.drv.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/package -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.s674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.s674: package/package_ti.sdo.edma3.drv.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/package -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/package -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.s674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674.dep
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674.dep: ;
endif

package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674: src/edma3_drv_init.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.s674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.s674: src/edma3_drv_init.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.s674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674.dep
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674.dep: ;
endif

package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674: src/edma3_drv_basic.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.s674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.s674: src/edma3_drv_basic.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.s674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674.dep
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674.dep: ;
endif

package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674: src/edma3_drv_adv.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/src -s o674 $< -C   -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.s674: | .interfaces
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.s674: src/edma3_drv_adv.c lib/674/release/ti.sdo.edma3.drv.a674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl674 -n $< ...
	$(ti.targets.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/674/release/ti.sdo.edma3.drv/src -s o674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 -eo.o674 -ea.s674  -mi10 -mo   -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_2_3 -O2  $(XDCINCS) -I$(ti.targets.C674.rootDir)/include -fs=./package/lib/lib/674/release/ti.sdo.edma3.drv/src -fr=./package/lib/lib/674/release/ti.sdo.edma3.drv/src
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.s674: export C_DIR=
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.s674: PATH:=$(ti.targets.C674.rootDir)/bin/;$(PATH)
package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.s674: Path:=$(ti.targets.C674.rootDir)/bin/;$(PATH)

clean,674 ::
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.s674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.s674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.s674
	-$(RM) package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.s674

lib/674/release/ti.sdo.edma3.drv.a674: package/lib/lib/674/release/ti.sdo.edma3.drv/package/package_ti.sdo.edma3.drv.o674 package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_init.o674 package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_basic.o674 package/lib/lib/674/release/ti.sdo.edma3.drv/src/edma3_drv_adv.o674 lib/674/release/ti.sdo.edma3.drv.a674.mak

clean::
	-$(RM) lib/674/release/ti.sdo.edma3.drv.a674.mak
