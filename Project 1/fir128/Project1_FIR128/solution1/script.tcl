############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Project1_FIR128
set_top fir
add_files fir.cpp
add_files fir.h
add_files -tb fir.cpp
add_files -tb fir_test.cpp
add_files -tb input.dat
add_files -tb out.gold.dat
open_solution "solution1" -flow_target vitis
set_part {xcvu29p-fsga2577-2L-e}
create_clock -period 10 -name default
config_interface -m_axi_alignment_byte_size 64 -m_axi_latency 64 -m_axi_max_widen_bitwidth 512
config_rtl -register_reset_num 3
#source "./Project1_FIR128/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
