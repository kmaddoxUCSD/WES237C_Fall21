############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Project_DFT
set_top dft
add_files ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/dft_test.cpp
add_files ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/dft.h
add_files ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/dft.cpp
add_files ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/coefficients256.h
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/script.tcl -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/out.gold.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/directives.tcl -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../../../../Desktop/WES237C_Fall2021/Read_the_docs-master-2/project_files/project3/dft_256_precomputed/dft_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 10 -name default
source "./Project_DFT/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
