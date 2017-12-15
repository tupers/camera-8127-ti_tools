;* ======================================================================== *;
;*  TEXAS INSTRUMENTS, INC.                                                 *;
;*                                                                          *;
;*  IMGLIB-2  DSP Image/Video Processing Library                            *;
;*                                                                          *;
;*      Release:        Revision 2.1.0.0                                    *;
;*      Snapshot date:  21-August-2010                                      *;
;*                                                                          *;
;*  This library contains proprietary intellectual property of Texas        *;
;*  Instruments, Inc.  The library and its source code are protected by     *;
;*  various copyrights, and portions may also be protected by patents or    *;
;*  other legal protections.                                                *;
;*                                                                          *;
;*  This software is licensed for use with Texas Instruments TMS320         *;
;*  family DSPs.  This license was provided to you prior to installing      *;
;*  the software.  You may review this license by consulting the file       *;
;*  TI_license.PDF which accompanies the files in this library.             *;
;* ------------------------------------------------------------------------ *;
;*          Copyright (C) 2010 Texas Instruments, Incorporated.             *;
;*                          All Rights Reserved.                            *;
;* ======================================================================== *;


This file contains a brief description of the C64x+ TI Image Library and
how to use it.

The TI Routines are provided in source, as well as Little Endian C64x+
object and PC (VC++) library along with header files.

--------------------------------------------------------------------------------
Release Directory Structure

Execute the IMGLIB installer provided to obtain the following installation
directory structure.

-------------------------------------------------------------------------
Directories                 What the directories contain
-------------------------------------------------------------------------
IMGLIB
|
+--build                    project files to builds host/target lib
| |
| +--host
| +--target
|
+--docs                     library documentation
|
+--include                  header files
|
+--kernels                  Kernel sources in various flavors
| |
| +-- asm
| +-- c
| +-- intrinsics
| +-- serial_asm
|
+--lib                      host and target library
| |
| +--host
| +--target
|
+--test_drivers             test bench with reference input/output vectors
| |
| +--drivers                set of test-cases
|
|
+--README.txt               Top-level README file
|
+--TI_Software_Manifest.pdf           TI License Agreement file


---------------------------------------------------------------------------------
Enhancements from IMGLIB 2.0.1

- ELF support 
- CCS v4 projects
- Linux make file based build

---------------------------------------------------------------------------------
Minimum requirement

Code Generation tools

Note: For ELF based build minimum requirement for code gen tools is CGTools v7.x

--------------------------------------------------------------------------------
Using the TI Image Library 2 in In your Code.

1. Using the ImgLib in:
  - Code Composer studio:
    First you have to specify to the linker to link the IMG Library
    into your application.  You do this by going to
    "Project->Options->Linker->Include Libraries"
    and then specify the TI IMG library, "imglib2.l64P".

  - Using Command line tool for C64x+:
    You have to tell the linker to link your application with the IMG library.
    You can do this by using the linker -l option in your linker command file or
    at the linker command line, i.e -l imglib2.l64P

  - Host build in MS VC++ or a command line tool:
    For host build, the host library "imglib2_host.lib" should be linked with
    host project.

2. For each of your C files in which you plan to use a library function,
   you must include the appropriate header file for that function.
   For instance, to use the function "IMG_idct_8x8()", you must
   #include <IMG_idct_8x8.h> in your source file.

3. refer the IMGLIB-2 user guide provided with the package for further details.

--------------------------------------------------------------------------------

How do I Re-Build the Library?
    The following CCS and VC++ Project files are provided to rebuild the
    library.
    - imglib2.pjt      : To build c64x+ library from optimized source code
    - imglib2_cn.pjt   : To build c64x+ library from ANSI c code
    - imglib2_host.dsp : To build host library from ANSI c code

- Linux build: Set paths for code generation tools and the library install path
    execute "make all" to build all projects in the imglib package.


--------------------------------------------------------------------------------
********************************************************************************
Release Notes History
********************************************************************************
--------------------------------------------------------------------------------
Changes from release version 2.0.0

Bug Fix:
--------
- Assembly functions: The includede assembly functions could not ba called from
  the library. The bug was identified as incorrect labeling of those function.
  This has now been fixed.
- Documentation updates and correction.

Enhancements:
-------------
- Added profiling code to the test benches.

--------------------------------------------------------------------------------
Enhancements from ImgLib-1

1. Increased Functionality.
2. 8 and 16 bit version of functions.
3. Source code for all functions. Intrinsic C code for most of the functions.
4. Host (PC) library included for standard PC development and testing of code.
5. CCS and VC++ projects to rebuild library.
6. Test bench with reference input and output test-vectors. Test vectors
   designed to test range limit and corner cases.
7. Test setup provided makes user modification and testing of code easy.

********************************************************************************
* End of README.TXT
********************************************************************************

