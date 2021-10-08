/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"
#include "ap_int.h"
#include <iostream>

void fir ( data_t *y, data_t x )
{

	//coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	ap_int<10> c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	//#pragma HLS array_partition variable=c block factor=4
	#pragma HLS array_partition variable=c dim2 complete
	//#pragma HLS array_partition variable=c dim2 cyclic factor=16
	/*4 a factor of 128; Block partitioning creates smaller arrays from consecutive blocks of the original array.
	This effectively splits the array into N equal blocks, where N is the integer defined by the factor= argument.*/

	// Write your code here
	static
		//data_t shift_reg[N]; //This array is declared static since the data must be persistent across multiple calls to the function.
		ap_int<10> shift_reg[N];
		//acc_t acc;
		ap_int<10> acc;
		int i;

		acc = 0;
		Shift_Accum_Loop:

		for(i = N -1; i >= 0; i--){
			#pragma HLS pipeline II=3

			/*if (i == 0){
				acc += x* c[0];
				shift_reg[0] = x;
			}else{*/
				shift_reg[i] = shift_reg[i - 1];
				acc += shift_reg[i] * c[i];
		}
		*y = acc;
		/*TDL:
		for (i = N − 1; i > 1; i = i − 2){

			shift reg[i] = shift reg[i − 1];
			shift reg[i − 1] = shift reg[i − 2];
		}
		if (i == 1) {
		shift reg[1] = shift reg[0];
		}
		shift reg[0] = x;
	}*/





