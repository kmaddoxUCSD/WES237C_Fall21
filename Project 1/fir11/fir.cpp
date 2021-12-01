/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.

	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fir.h"
#include <ap_cint.h>


void fir ( data_t *y, coef_t c[N], data_t x )
{
	//coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0,53};
	// Write your code here
#pragma HLS ARRAY_PARTITION variable=c type=complete

	static data_t shift_reg[N];
#pragma HLS ARRAY_PARTITION variable=shift_reg type=complete

	acc_t acc;
	int i;
	data_t data;
	acc = 0;

Shift_Accum_Loop:
	for (i = N-1; i >= 0; i--){
#pragma HLS UNROLL
		if (i == 0){
			shift_reg[0] = x;
			data = x;
		}
		else{
			shift_reg[i] = shift_reg[i - 1];
			data = shift_reg[i];
		}
		acc += data * c[i];
	}

	*y = acc;
}
