/*
	Filename: phasedetector.cpp
		Phase detector

	INPUT:
		I: signal for I sample
		Q: signal for Q sample
		length: array size

	OUTPUT:
		R: Radius
		Theta: Angle

*/

#include "phasedetector.h"

void phasedetector (data_t *I, data_t *Q, data_t *R,data_t *Theta,int length)
 {
#pragma HLS PIPELINE II=2

	float X, Y;
	float I_input, Q_input;
	float R_output, Theta_output;


	for (unsigned int i=0; i < length; i++)
	{


		I_input = *(I+i);
	    Q_input = *(Q+i);


	    fir(I_input, Q_input, &X, &Y);
		cordiccart2pol(X, Y, &R_output, &Theta_output);


		*(R+i) = R_output;
		*(Theta+i) = Theta_output;
	}


 }




