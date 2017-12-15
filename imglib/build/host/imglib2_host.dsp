# Microsoft Developer Studio Project File - Name="imglib_host" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=imglib_host - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "imglib2_host.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "imglib2_host.mak" CFG="imglib_host - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "imglib_host - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "imglib_host - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "imglib_host"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "imglib_host - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "imglib_host - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_HOST_BUILD" /D "NOASSUME" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\host\imglib2_host_rebuild.lib"

!ENDIF 

# Begin Target

# Name "imglib_host - Win32 Release"
# Name "imglib_host - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\kernels\c\host_build.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_boundary_16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_boundary_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_clipping_16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_11x11_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_11x11_i8_c8s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_3x3_i16_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_3x3_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_3x3_i8_c8s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_5x5_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_5x5_i8_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_5x5_i8_c8s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_7x7_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_7x7_i8_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_conv_7x7_i8_c8s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_11x11_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_11x11_i8_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_3x3_i16_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_3x3_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_3x3_i8_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_3x3_i8_c8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_5x5_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_gen_i16s_c16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_corr_gen_iq_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_dilate_bin_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_erode_bin_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_errdif_bin_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_errdif_bin_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_fdct_8x8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_histogram_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_histogram_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_idct_8x8_12q4_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_mad_16x16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_mad_8x8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_median_3x3_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_median_3x3_16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_median_3x3_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_mpeg2_vld_inter_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_mpeg2_vld_intra_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_mpeg2_vld_tables.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_perimeter_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_perimeter_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_pix_expand_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_pix_sat_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_quantize_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sad_16x16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sad_8x8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sobel_3x3_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sobel_3x3_16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sobel_3x3_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sobel_5x5_16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_sobel_7x7_16s_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_gt2max_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_gt2max_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_gt2thr_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_gt2thr_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_le2min_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_le2min_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_le2thr_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_thr_le2thr_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_wave_horz_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_wave_vert_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_yc_demux_be16_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_yc_demux_be16_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_yc_demux_le16_16_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_yc_demux_le16_8_c.c
# End Source File
# Begin Source File

SOURCE=..\..\kernels\c\IMG_ycbcr422pl_to_rgb565_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
