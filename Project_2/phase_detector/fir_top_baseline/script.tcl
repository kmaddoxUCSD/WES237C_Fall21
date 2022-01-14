############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fir_top_baseline
set_top fir
add_files fir.cpp
add_files -tb fir_test.cpp
add_files -tb input_i.dat
add_files -tb input_q.dat
add_files -tb out.gold.dat
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 10 -name default
//#source "./fir_top_baseline/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
