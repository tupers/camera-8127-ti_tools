#!/bin/bash

#* ======================================================================== *#
#*  TEXAS INSTRUMENTS, INC.                                                 *#
#*                                                                          *#
#*  IMGLIB-2  DSP Image/Video Processing Library                            *#
#*                                                                          *#
#*      Release:        Revision 2.0.1                                      *#
#*      Snapshot date:  6-May-2008                                          *#
#*                                                                          *#
#*  This library contains proprietary intellectual property of Texas        *#
#*  Instruments, Inc.  The library and its source code are protected by     *#
#*  various copyrights, and portions may also be protected by patents or    *#
#*  other legal protections.                                                *#
#*                                                                          *#
#*  This software is licensed for use with Texas Instruments TMS320         *#
#*  family DSPs.  This license was provided to you prior to installing      *#
#*  the software.  You may review this license by consulting the file       *#
#*  TI_license.PDF which accompanies the files in this library.             *#
#* ------------------------------------------------------------------------ *#
#*          Copyright (C) 2008 Texas Instruments, Incorporated.             *#
#*                          All Rights Reserved.                            *#
#* ======================================================================== *#

echo "Extra build options: $1"

cd ../

for kernel in IMG_boundary_16s IMG_boundary_8 IMG_clipping_16s IMG_conv_11x11_i16s_c16s IMG_conv_11x11_i8_c8s IMG_conv_3x3_i16s_c16s IMG_conv_3x3_i8_c8s IMG_conv_5x5_i16s_c16s IMG_conv_5x5_i8_c16s IMG_conv_5x5_i8_c8s IMG_conv_7x7_i16s_c16s IMG_conv_7x7_i8_c16s IMG_conv_7x7_i8_c8s IMG_corr_11x11_i16s_c16s IMG_corr_11x11_i8_c16s IMG_corr_3x3_i16s_c16s IMG_corr_3x3_i8_c16s IMG_corr_3x3_i8_c8 IMG_corr_5x5_i16s_c16s IMG_corr_gen_i16s_c16s IMG_corr_gen_iq IMG_histogram_16 IMG_histogram_8 IMG_median_3x3_16s IMG_median_3x3_8 IMG_perimeter_16 IMG_perimeter_8 IMG_pix_expand IMG_pix_sat IMG_sobel_3x3_16s IMG_sobel_3x3_8 IMG_sobel_5x5_16s IMG_sobel_7x7_16s IMG_thr_gt2max_8 IMG_thr_gt2thr_8 IMG_thr_le2min_8 IMG_thr_le2thr_8 IMG_ycbcr422pl_to_rgb565 IMG_yc_demux_be16_8 IMG_yc_demux_le16_8
	
	
do
	echo
	echo
	echo Building $kernel
	cd $kernel;
	make -f ../common/make_kernel.mk -j 4 K_NAME=$kernel $1;
	cd ..;
done

for kernel in  IMG_conv_3x3_i16_c16s IMG_median_3x3_16 IMG_sobel_3x3_16 IMG_thr_gt2max_16 IMG_thr_gt2thr_16 IMG_thr_le2min_16 IMG_thr_le2thr_16 IMG_yc_demux_be16_16 IMG_yc_demux_le16_16
do
	echo
	echo
	echo Building $kernel
	cd $kernel;
	make -f ../common/make_kernel.mk -j 4 K_NAME=$kernel SA=YES $1;
	cd ..;
done


#IMG_boundary_16s
#IMG_boundary_8
#IMG_clipping_16s
#IMG_conv_11x11_i16s_c16s
#IMG_conv_11x11_i8_c8s
#IMG_conv_3x3_i16s_c16s
#IMG_conv_3x3_i8_c8s
#IMG_conv_5x5_i16s_c16s
#IMG_conv_5x5_i8_c16s
#IMG_conv_5x5_i8_c8s
#IMG_conv_7x7_i16s_c16s
#IMG_conv_7x7_i8_c16s
#IMG_conv_7x7_i8_c8s
#IMG_corr_11x11_i16s_c16s
#IMG_corr_11x11_i8_c16s
#IMG_corr_3x3_i16s_c16s
#IMG_corr_3x3_i8_c16s
#IMG_corr_3x3_i8_c8
#IMG_corr_5x5_i16s_c16s
#IMG_corr_gen_i16s_c16s
#IMG_corr_gen_iq
#IMG_histogram_16
#IMG_histogram_8
#IMG_median_3x3_16s
#IMG_median_3x3_8
#IMG_perimeter_16
#IMG_perimeter_8
#IMG_pix_expand
#IMG_pix_sat
#IMG_sobel_3x3_16s
#IMG_sobel_3x3_8
#IMG_sobel_5x5_16s
#IMG_sobel_7x7_16s
#IMG_thr_gt2max_8
#IMG_thr_gt2thr_8
#IMG_thr_le2min_8
#IMG_thr_le2thr_8
#IMG_ycbcr422pl_to_rgb565
#IMG_yc_demux_be16_8
#IMG_yc_demux_le16_8


#	IMG_boundary_16s IMG_boundary_8 IMG_clipping_16s IMG_conv_11x11_i16s_c16s IMG_conv_11x11_i8_c8s IMG_conv_3x3_i16s_c16s IMG_conv_3x3_i8_c8s IMG_conv_5x5_i16s_c16s IMG_conv_5x5_i8_c16s IMG_conv_5x5_i8_c8s IMG_conv_7x7_i16s_c16s IMG_conv_7x7_i8_c16s IMG_conv_7x7_i8_c8s IMG_corr_11x11_i16s_c16s IMG_corr_11x11_i8_c16s IMG_corr_3x3_i16s_c16s IMG_corr_3x3_i8_c8 IMG_corr_5x5_i16s_c16s IMG_histogram_16 IMG_histogram_8 IMG_sobel_3x3_16s IMG_sobel_3x3_8 IMG_sobel_5x5_16s IMG_sobel_7x7_16s IMG_thr_gt2max_8 IMG_thr_gt2thr_8 IMG_thr_le2min_8 IMG_thr_le2thr_8 
