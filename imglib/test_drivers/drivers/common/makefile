ifndef IMGLIB_INSTALL_DIR
    IMGLIB_INSTALL_DIR = ../../..
endif

include $(IMGLIB_INSTALL_DIR)/Rules.make

TARGET = $(notdir $(CURDIR))
CUR_DIR = "."
# Comment this out if you want to see full compiler and linker output.
VERBOSE = @
#BUILD_TYPE = Release
export CODEGEN_INSTALL_DIR	

LFILE = ../common/kernel_test.cmd
INCLUDES = -i$(CODEGEN_INSTALL_DIR)/include  \
           -i../common                       \
           -i$(IMGLIB_INSTALL_DIR)/include      
MAP_FILE = $(BUILD_TYPE)/$(TARGET).map

EXE = $(BUILD_TYPE)/$(TARGET).out

#Set Compiler and Linker flags based on Configuration specified 
ifeq ($(BUILD_TYPE), Release)
    LD_FLAGS 	+= -z -c -heap 0x10000 -stack 0x2000 -m $(MAP_FILE) -o$(EXE) -w -x -i $(CODEGEN_INSTALL_DIR)/lib  
    C_FLAGS	+= -o3 $(INCLUDES) -mv6400+ -fr"$(BUILD_TYPE)" -fs"$(BUILD_TYPE)" -ft"$(BUILD_TYPE)" -d"__TI_EABI__=0" -q  -k -ml3 -mw -mi
endif
ifeq ($(BUILD_TYPE), Release_elf)
    LD_FLAGS 	+= --abi=eabi -z -c -heap 0x10000 -stack 0x2000 -m $(MAP_FILE) -o$(EXE) -w -x -i $(CODEGEN_INSTALL_DIR)/lib 
    C_FLAGS	+= --abi=eabi -o3 $(INCLUDES) -mv6400+ -fr"$(BUILD_TYPE)" -fs"$(BUILD_TYPE)" -ft"$(BUILD_TYPE)" -q  -k -ml3 -mw -mi
endif

COMPILE.c = $(VERBOSE) $(CODEGEN_INSTALL_DIR)/bin/cl6x $(C_FLAGS)
LINK.c = $(VERBOSE) $(CODEGEN_INSTALL_DIR)/bin/cl6x $(LD_FLAGS)

SOURCES = $(wildcard *.c) 

HEADERS = $(wildcard *.h) $(wildcard ../common/*.h) $(wildcard ../../../../include/*.h)
OBJFILES = $(SOURCES:%.c=$(BUILD_TYPE)/%.obj) 
           
COMMON_OBJ = $(SOURCES:%.c=$(BUILD_TYPE)/%.obj)


.PHONY: clean install 

all:	TARGET

TARGET: $(OBJFILES)

$(BUILD_TYPE)/%.obj: %.c $(HEADERS) 
	@echo Compiling $@ from $<..
	@echo $(COMPILE.c) $(INCLUDES)$<
	@echo mkdir -p $(BUILD_TYPE)
	@mkdir -p $(BUILD_TYPE)
	@chmod 777 $(BUILD_TYPE)
	$(COMPILE.c) $(INCLUDES) $<

$(BUILD_TYPE)/%.obj:%.c $(HEADERS) 
	@echo Compiling $@ from $<..
	@mkdir -p $(BUILD_TYPE)
	@echo $(COMPILE.c) $(INCLUDES)$<
	$(COMPILE.c) $(INCLUDES) $<

clean:
	@echo Removing generated files..
	$(VERBOSE) -$(RM) -r $(BUILD_TYPE) *~ *.d .dep
