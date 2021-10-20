#include "cordiccart2pol.h"
#include "ap_int.h"

#include <math.h>

#include <iostream>

using namespace std;

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};

//float cordic_phase = 0.463;

//The cordic_phase array holds the angle for the current rotation
THETA_TYPE cordic_phase [ NO_ITER ] = { 45, 25.56, 14.036, 7.125, 3.576, 1.790, 0.895 };


void cordic( THETA_TYPE theta , COS_SIN_TYPE & s , COS_SIN_TYPE & c )
{
	#pragma HLS pipeline II=1
	//Set the initial vector that we will rotate
	//current_cos = I;current = Q
	COS_SIN_TYPE current_cos = 0.60735;
	COS_SIN_TYPE current_sin = 0.0;

	// This loop iteratively rotates the initial vector to nd the
	// sine and cosine values corresponding to the input theta angle
	for (int j = 0; j < NO_ITER; j++) {


		// Multiply previous iteration by 2^(−j). This is equivalent to
		// a right shift by j on a xed−point number.

		COS_SIN_TYPE cos_shift = (int)current_cos >> j;
		COS_SIN_TYPE sin_shift = (int)current_sin >> j;

		// Determine if we are rotating by a positive or negative angle
		if(theta >= 0) {

		// Perform the rotation
		current_cos = current_cos - sin_shift;
		current_sin = current_sin + cos_shift;

		// Determine the new theta
		theta = theta - cordic_phase[j];
		} else {

		// Perform the rotation
		current_cos = current_cos + sin_shift;
		current_sin = current_sin - cos_shift;

		// Determine the new theta
		theta = theta + cordic_phase[j];
		}

	s = current_sin ; c = current_cos ;
	}
}
