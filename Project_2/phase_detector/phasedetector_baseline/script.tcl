############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project phasedetector_baseline
set_top phasedetector
add_files cordiccart2pol.cpp
add_files fir.cpp
add_files phasedetector.cpp
add_files -tb input_i.dat
add_files -tb input_q.dat
add_files -tb out.gold.dat
add_files -tb phasedetector_test.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
//source "./phasedetector_optimized1/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
