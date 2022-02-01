
#include<math.h>
#include"coefficients1024.h"
#include "hls_half.h"
#include "ap_int.h"

typedef float IN_TYPE; // Data type for the input signal
typedef float TEMP_TYPE; // Data type for the temporary variables

#define N 1024 // DFT Size

void dft(DTYPE sample_real[N], DTYPE sample_imag[N], DTYPE sample_temp[N])
{//Write your code here
#pragma HLS array_partition variable=sample_real block factor=2 dim=2
#pragma HLS array_partition variable=sample_imag block factor=2 dim=2

	int i, j;
	DTYPE c_0, s_0;
	DTYPE c_1, s_1;

	// Temporary arrays to hold the intermediate frequency domain results
	TEMP_TYPE temp_real[N] = {0};
	TEMP_TYPE temp_imag[N] = {0};

	//The ARRAY_RESHAPE directive reforms the array with a vertical mode of remapping,
	//and is used to reduce the number of block RAM consumed while providing parallel access to the data.
#pragma HLS ARRAY_RESHAPE variable=temp_real type=block factor=2 dim=1
#pragma HLS ARRAY_RESHAPE variable=temp_imag type=cyclic factor=2 dim=1

	// Calculate the jth frequency sample sequentially
	for (j = 0; j < N; j += 2) {
#pragma HLS unroll factor=2

		// Calculate each frequency domain sample iteratively
		for (i = 0; i < N;i += 1) {

#pragma HLS PIPELINE II=2
			c_0 = cos_coefficients_table[(ap_uint<8>)(i * j)];
			s_0 = cos_coefficients_table[(ap_uint<8>)(i * j)];
			c_1 = cos_coefficients_table[(ap_uint<8>)((i) * (j + 1))];
			s_1 = cos_coefficients_table[(ap_uint<8>)((i) * (j+1))];
		}
	}
	// Perform an inplace DFT, i.e., copy result into the input arrays
	for (i = 0; i < N; i += 1) {
		#pragma HLS PIPELINE II=1
		sample_real[i] = temp_real[i];
		sample_imag[i] = temp_imag[i];
	}
}
