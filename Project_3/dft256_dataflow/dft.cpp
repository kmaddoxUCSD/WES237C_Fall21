#include<math.h>
#include "dft.h"
#include"coefficients256.h"
#include "hls_half.h"
#include "ap_int.h"
#include "hls_stream.h"


typedef half IN_TYPE; // Data type for the input signal
typedef half TEMP_TYPE; // Data type for the temporary variables

#define N 256 // DFT Size

void dataflow1(IN_TYPE vecIn[N], IN_TYPE vecOut[N])
{
	IN_TYPE c1[N], c2[N], c3[N], c4[N];
#pragma HLS dataflow
  funcA(vecIn, c1, c2);
  funcB(c1, c3);
  funcC(c2, c4);
  funcD(c3, c4, vecOut);
}

void dft(IN_TYPE sample_real[N], IN_TYPE sample_imag[N])
{//Write your code here
#pragma HLS latency min=2 max=4
	int i, j;
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
		#pragma HLS PIPELINE II=1
		temp_real[i] = 0;
		temp_imag[i] = 0;

		// Calculate the jth frequency sample sequentially
		for (j = 0; j < N; j += 1) {
			#pragma HLS PIPELINE II=1

			c = cos_coefficients_table[(ap_uint<8>) (i *j)];
			s = sin_coefficients_table[(ap_uint<8>)(i * j)];

			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			temp_real[i] += (sample_real[j] * c - sample_imag[j] * s);
			temp_imag[i] += (sample_real[j] * s + sample_imag[j] * c);
		}
	}

	// Perform an inplace DFT, i.e., copy result into the input arrays
	for (i = 0; i < N; i += 1) {
		#pragma HLS PIPELINE II=1
		sample_real[i] = temp_real[i];
		sample_imag[i] = temp_imag[i];
          		}
          	}

void funcA(TEMP_TYPE *in, TEMP_TYPE *out1, TEMP_TYPE *out2)
    {
    Loop0:
      for (int i = 0; i < N; i++)
      {
    #pragma HLS pipeline II=1 rewind
    //#pragma HLS pipeline rewind
    //#pragma HLS unroll factor = 2
    	TEMP_TYPE t = in[i] * 3;

        out1[i] = t;
        out2[i] = t;
      }
    }

void funcB(TEMP_TYPE *in, TEMP_TYPE *out)
    {
      for (int i = 0; i < N; i++)
      {
    #pragma HLS pipeline II=1 rewind
    //#pragma HLS pipeline rewind
    //#pragma HLS unroll factor = 2
        out[i] = in[i] + 25;
      }
    }

void funcC(TEMP_TYPE *in, TEMP_TYPE *out)
    {
      for (int i = 0; i < N; i++)
      {
    #pragma HLS pipeline II=1 rewind
    //#pragma HLS pipeline rewind
    //#pragma HLS unroll factor = 2
        out[i] = in[i] * 2;
      }
    }

void funcD(TEMP_TYPE *in1, TEMP_TYPE *in2, TEMP_TYPE *out)
    {

	  for (int i = 0; i < N; i++)
	  {
	#pragma HLS pipeline II=1 rewind
	//#pragma HLS pipeline rewind
	//#pragma HLS unroll factor = 2
        out[i] = in1[i] + in2[i] * 2;
      }
    }

