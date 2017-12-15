#############################################################################
# Makefile                                                                  #
#                                                                           #
#  Make file to build image library                                         #
#############################################################################
#
#
#############################################################################
#                                                                           #
#   Copyright (C) 2010 Texas Instruments Incorporated                       #
#     http://www.ti.com/                                                    #
#                                                                           #
#############################################################################

ifndef IMGLIB_INSTALL_DIR
    IMGLIB_INSTALL_DIR = ../
endif

include $(IMGLIB_INSTALL_DIR)/Rules.make

TARGET= imglib

CUR_DIR = "."
# Comment this out if you want to see full compiler and linker output.
VERBOSE = @

export CODEGEN_INSTALL_DIR	

INCLUDES = -i$(CODEGEN_INSTALL_DIR)/include \
           -i$(IMGLIB_INSTALL_DIR)/include
MAP_FILE = $(BUILD_TYPE)/$(LTARGET).map
BUILD_TYPE_CN = $(BUILD_TYPE)_cn

#Set Compiler flags based on Configuration specified
ifeq ($(BUILD_TYPE), Release)
    C_FLAGS	+= -k -q -o3 -mw -d"__TI_EABI__=0" -mh256 -mi2000 -mv6400+
    ATARGET	 = $(BUILD_TYPE)/$(TARGET)_rebuild.l64P
    CTARGET      = $(BUILD_TYPE_CN)/$(TARGET)_cn_rebuild.l64P
endif
ifeq ($(BUILD_TYPE), Release_elf)
    C_FLAGS	+= --abi=eabi -k -q -o3 -mw -mh256 -mi2000 -mv6400+
    ATARGET	 = $(BUILD_TYPE)/$(TARGET)_elf_rebuild.l64P
    CTARGET      = $(BUILD_TYPE_CN)/$(TARGET)_cn_elf_rebuild.l64P
endif

#Set Compiler and Archiver paths and flags for the build
COMPILE.c = $(VERBOSE) $(CODEGEN_INSTALL_DIR)/bin/cl6x $(C_FLAGS)
AR.c	  = $(VERBOSE) $(CODEGEN_INSTALL_DIR)/bin/ar6x $(AR_FLAGS)

# C Sources to be built
CSRC = $(wildcard ../kernels/c/*_c.c)
ICSRC = $(wildcard ../kernels/intrinsic/*.c)

#Assembly source files to be built
ASMSRC = $(wildcard ../kernels/asm/*.asm)

#Serial Assembly source files to be built
SASMSRC = $(wildcard ../kernels/serial_asm/*.sa)
HEADERS =  $(wildcard ../include/*.h) $(wildcard $(CODEGEN_INSTALL_DIR)/include/*.h)        

#Object files to be built
COBJFILES = $(CSRC:../kernels/c/%.c=$(BUILD_TYPE_CN)/%.obj)
ICOBJFILES = $(ICSRC:../kernels/intrinsic/%.c=$(BUILD_TYPE)/%.obj)
ASMOBJ_FILES = $(ASMSRC:../kernels/asm/%.asm=$(BUILD_TYPE)/%.obj) 
SAOBJ_FILES = $(SASMSRC:../kernels/serial_asm/%.sa=$(BUILD_TYPE)/%.obj)
           
.PHONY: clean install 

all:	$(ATARGET) $(CTARGET)

$(ATARGET): $(ICOBJFILES) $(ASMOBJ_FILES) $(SAOBJ_FILES)
	@echo 
	@echo Archiving $@ ..
	@mkdir -p $(dir $@)
	@cd $(BUILD_TYPE)
	@echo $(AR.c) -r $@ $^
	$(AR.c) -r $@ $^

$(CTARGET): $(COBJFILES)
	@echo 
	@echo Archiving $@ ..
	@mkdir -p $(dir $@)
	@cd $(BUILD_TYPE_CN)
	@echo $(AR.c) -r $@ $^
	$(AR.c) -r $@ $^

$(BUILD_TYPE_CN)/%.obj:../kernels/c/%.c $(HEADERS) 
	@echo Compiling $@ from $<..
	@echo $(COMPILE.c) $(INCLUDES)$<
	@mkdir -p $(BUILD_TYPE_CN)
	@chmod 777 $(BUILD_TYPE_CN)
	$(COMPILE.c) -fr"$(BUILD_TYPE_CN)" -fs"$(BUILD_TYPE_CN)" -ft"$(BUILD_TYPE_CN)" $(INCLUDES) $<

$(BUILD_TYPE)/%.obj:../kernels/intrinsic/%.c $(HEADERS) 
	@echo Compiling $@ from $<..
	@echo $(COMPILE.c) $(INCLUDES)$<
	@mkdir -p $(BUILD_TYPE)
	@chmod 777 $(BUILD_TYPE)
	$(COMPILE.c) -fr"$(BUILD_TYPE)" -fs"$(BUILD_TYPE)" -ft"$(BUILD_TYPE)" $(INCLUDES) $<


$(BUILD_TYPE)/%.obj:../kernels/asm/%.asm $(HEADERS) 
	@echo Compiling $@ from $<..
	@echo $(COMPILE.c) $(INCLUDES)$<
	@mkdir -p $(BUILD_TYPE)
	@chmod 777 $(BUILD_TYPE)
	$(COMPILE.c) -fr"$(BUILD_TYPE)" -fs"$(BUILD_TYPE)" -ft"$(BUILD_TYPE)" $(INCLUDES) $<

$(BUILD_TYPE)/%.obj:../kernels/serial_asm/%.sa $(HEADERS) 
	@echo Compiling $@ from $<..
	@echo $(COMPILE.c) $(INCLUDES)$<
	@mkdir -p $(BUILD_TYPE)
	@chmod 777 $(BUILD_TYPE)
	$(COMPILE.c) -fr"$(BUILD_TYPE)" -fs"$(BUILD_TYPE)" -ft"$(BUILD_TYPE)" $(INCLUDES) $<

clean:
	@echo Removing generated files..
	$(VERBOSE) -$(RM) -r $(BUILD_TYPE) *~ *.d .dep
	$(VERBOSE) -$(RM) -r $(BUILD_TYPE_CN) *~ *.d .dep
