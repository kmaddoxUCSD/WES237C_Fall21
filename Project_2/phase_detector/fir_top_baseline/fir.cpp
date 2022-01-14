/*
	Filename: fir.cpp
		Complex FIR or Match filter
		firI1 and firI2 share coef_t c[N]
		firQ1 and firQ2 share coef_t c[N]
		
	INPUT:
		I: signal for I sample
		I: signal for Q sample

	OUTPUT:
		X: filtered output
		Y: filtered output

*/

#include "fir.h"
#include <stdio.h>

void firI1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};

	static data_t shift_reg[N]={0};
	acc_t acc;
	ap_int<8> i;

#pragma HLS PIPELINE II=2
	acc = 0;
	Shift_Accum_Loop:

	for(i=N-1;i>=0;i--){


		if(i==0){
			acc+=x*c[0];
			shift_reg[0]=x;
		}
		else
		{
			shift_reg[i]=shift_reg[i-1];
			acc+=shift_reg[i]*c[i];
		}
	}
	*y=acc;





}


void firI2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};


	static data_t shift_reg[N]={0};
	acc_t acc;
	ap_int<8> i;

#pragma HLS PIPELINE II=2
	acc = 0;
	Shift_Accum_Loop:

	for(i=N-1;i>=0;i--){


		if(i==0){
			acc+=x*c[0];
			shift_reg[0]=x;
		}
		else
		{
			shift_reg[i]=shift_reg[i-1];
			acc+=shift_reg[i]*c[i];
		}
	}
	*y=acc;


}




void firQ1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};


	static data_t shift_reg[N]={0};
	acc_t acc;
	ap_int<8> i;

#pragma HLS PIPELINE II=2
	acc = 0;
	Shift_Accum_Loop:

	for(i=N-1;i>=0;i--){


		if(i==0){
			acc+=x*c[0];
			shift_reg[0]=x;
		}
		else
		{
			shift_reg[i]=shift_reg[i-1];
			acc+=shift_reg[i]*c[i];
		}
	}
	*y=acc;


	
}

void firQ2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};


	static data_t shift_reg[N]={0};
	acc_t acc;
	ap_int<8> i;

#pragma HLS PIPELINE II=2
	acc = 0;
	Shift_Accum_Loop:

	for(i=N-1;i>=0;i--){


		if(i==0){
			acc+=x*c[0];
			shift_reg[0]=x;
		}
		else
		{
			shift_reg[i]=shift_reg[i-1];
			acc+=shift_reg[i]*c[i];
		}
	}
	*y=acc;



}


void fir (
  data_t I,
  data_t Q,

  data_t *X,
  data_t *Y
  ) {


	// Write your code here
    data_t Iin_Ifir, Qin_Qfir, Qin_Ifir, Iin_Qfir;// = {0};

	firI1(&Iin_Ifir, I);
	firQ1(&Qin_Qfir, Q);

	firI2(&Qin_Ifir, Q);
	firQ2(&Iin_Qfir, I);


	//Calculate X
	*X = Iin_Ifir + Qin_Qfir;

	//Calculate Y
	*Y = Qin_Ifir - Iin_Qfir;
}


