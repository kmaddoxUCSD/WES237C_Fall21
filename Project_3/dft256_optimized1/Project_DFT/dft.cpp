#include<math.h>
#include "dft.h"
#include"coefficients256.h"
#include "ap_int.h"
#include "hls_half.h"

typedef float IN_TYPE; // Data type for the input signal
typedef float TEMP_TYPE; // Data type for the temporary variables

#define N 256 // DFT Size

void dft(IN_TYPE sample_real[N], IN_TYPE sample_imag[N])
{//Write your code here
	#pragma HLS ARRAY_PARTITION variable=sample_real dim=2 type=complete
	#pragma HLS ARRAY_PARTITION variable=sample_imag type=complete

	int i, j;
	TEMP_TYPE w;
	TEMP_TYPE c, s;

	// Temporary arrays to hold the intermediate frequency domain results
	TEMP_TYPE temp_real[N];
	TEMP_TYPE temp_imag[N];
	//The ARRAY_RESHAPE directive reforms the array with a vertical mode of remapping,
	//and is used to reduce the number of block RAM consumed while providing parallel access to the data.
	#pragma HLS ARRAY_RESHAPE variable=temp_real type=block factor=2 dim=1
	#pragma HLS ARRAY_RESHAPE variable=temp_imag type=block factor=2 dim=1

	// Calculate each frequency domain sample iteratively
	for (i = 0; i < N; i += 1) {
		#pragma HLS PIPELINE II=2
		temp_real[i] = 0;
		temp_imag[i] = 0;

		// (2 * pi * i)/N
		w = (2.0 * 3.141592653589 / N)  * (TEMP_TYPE)i;

		// Calculate the jth frequency sample sequentially
		for (j = 0; j < N; j += 1) {
			#pragma HLS unroll factor=2
			// Utilize HLS tool to calculate sine and cosine values
			c = cos(j * w);
			s = -sin(j * w);

			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			temp_real[i] += (sample_real[j] * c - sample_imag[j] * s);
			temp_imag[i] += (sample_real[j] * s + sample_imag[j] * c);
		}
	}
	// Perform an inplace DFT, i.e., copy result into the input arrays
	for (i = 0; i < N; i += 1) {
		//#pragma HLS unroll factor=2
		sample_real[i] = temp_real[i];
		sample_imag[i] = temp_imag[i];
	}
}


