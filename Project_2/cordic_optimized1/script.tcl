############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Project2_CORDIC
set_top cordic
add_files cordic/HLS/cordic/cordiccart2pol.h
add_files cordic/HLS/cordic/cordiccart2pol.cpp
add_files -tb cordic/HLS/cordic/cordiccart2pol_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/Users/kevinmaddox/AppData/Roaming/Xilinx/Vitis/Project2_CORDIC/Project2_CORDIC_RTL/cordic.zip -rtl verilog
source "./Project2_CORDIC/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Users/kevinmaddox/AppData/Roaming/Xilinx/Vitis/Project2_CORDIC/Project2_CORDIC_RTL/cordic.zip
