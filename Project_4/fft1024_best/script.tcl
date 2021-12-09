############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Project4_FFT_Stages
set_top fft
add_files ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master/project_files/project4/FFT/HLS/2_Skeleton_Restructured/fft.cpp
add_files ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master/project_files/project4/FFT/HLS/2_Skeleton_Restructured/fft.h
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master/project_files/project4/FFT/HLS/2_Skeleton_Restructured/directives.tcl -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master/project_files/project4/FFT/HLS/2_Skeleton_Restructured/fft_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master/project_files/project4/FFT/HLS/2_Skeleton_Restructured/out.gold.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master/project_files/project4/FFT/HLS/2_Skeleton_Restructured/script.tcl -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/Users/kevinmaddox/Documents/WES237C_FA21_A00/fft_S.zip -rtl verilog
source "./Project4_FFT_Stages/solution1/directives.tcl"
csim_design -O
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Users/kevinmaddox/Documents/WES237C_FA21_A00/fft_S.zip
