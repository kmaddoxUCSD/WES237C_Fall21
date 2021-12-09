#include<math.h>
#include "dft.h"
#include"coefficients256.h"
#include "hls_half.h"
#include "ap_int.h"
#include "hls_stream.h"


typedef half IN_TYPE; // Data type for the input signal
typedef half TEMP_TYPE; // Data type for the temporary variables

#define N 256 // DFT Size

void dft(IN_TYPE sample_real[N], IN_TYPE sample_imag[N], IN_TYPE vecIn[N], IN_TYPE vecOut[N])
{//Write your code here
	  TEMP_TYPE c1[N], c2[N], c3[N], c4[N];
	#pragma HLS dataflow

	  funcA(vecIn, c1, c2);
	  funcB(c1, c3);
	  funcC(c2, c4);
	  funcD(c3, c4, vecOut);
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
	Loop0:
	  for (int i = 0; i < N; i++)
	  {
	#pragma HLS pipeline II=1 rewind
	//#pragma HLS pipeline rewind
	//#pragma HLS unroll factor = 2
	    out[i] = in[i] + 25;
	  }
	}

	void funcC(TEMP_TYPE *in, TEMP_TYPEt *out)
	{
	Loop0:
	  for (TEMP_TYPE i = 0; i < N; i++)
	  {
	#pragma HLS pipeline II=1 rewind
	//#pragma HLS pipeline rewind
	//#pragma HLS unroll factor = 2
	    out[i] = in[i] * 2;
	  }
	}

	void funcD(TEMP_TYPE *in1, TEMP_TYPE *in2, TEMP_TYPE *out)
	{
	Loop0:
	  for (int i = 0; i < N; i++)
	  {
	#pragma HLS pipeline II=1 rewind
	//#pragma HLS pipeline rewind
	//#pragma HLS unroll factor = 2
	    out[i] = in1[i] + in2[i] * 2;
	  }
	}
