#------------------------------------------------------------------------------------------------
# Global Path Setup for Dependent components
#------------------------------------------------------------------------------------------------

# PATH Along which the dsplipc674x is installed
IMGLIB_INSTALL_DIR = /home/user/TI8168/imglib

# Where the Code Gen is installed.
CODEGEN_INSTALL_DIR =/home/user/TI8168/cgt_7_0_2

# BUILD TYPE Selects the configuration for which the library needs to be built
# OPTION 1: Release : This builds the COFF version of the Library
# OPTION 2: Release_elf: This builds the ELF verison of the Library
BUILD_TYPE= Release

#PATH on the OS where the binaries need to be installed
#Any user defined path can be used to install these binaries
EXEC_DIR= /home/user/imglib_install
