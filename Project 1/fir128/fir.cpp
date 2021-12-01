/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fir.h"
//#include <ap_cint.h>


void fir ( data_t *y, data_t x, coef_t c[N] )
{

	// Write your code here
#pragma HLS ARRAY_PARTITION variable=c type=complete

	static data_t shift_reg[N];
//#pragma HLS ARRAY_PARTITION variable=shift_reg type=cyclic

	acc_t acc;
	int i;

	acc = 0;

	TDL:
#pragma HLS DEPENDENCE variable=shift_reg type=inter //Solution: These dependencies are visualized in the schedule viewer l to help the user understand. Break up these dependencies in the user code.
	for (i = N - 1; i > 0; i--){
#pragma HLS pipeline II=1
		shift_reg[i] = shift_reg[i - 1];
	}

	shift_reg[0] = x;

	MAC:
	for (i = N - 1; i >= 2; i -= 3){
#pragma HLS PIPELINE

		acc += shift_reg[i] * c[i] + shift_reg[i - 1] * c[i - 1] + shift_reg[i - 2] * c[i - 2] + shift_reg[i - 3] * c[i - 3];
	}
	for (i = N - 1; i > 0; i--){
#pragma HLS PIPELINE

		acc += shift_reg[i] * c[i];
	}

	*y = acc;
}


//coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

