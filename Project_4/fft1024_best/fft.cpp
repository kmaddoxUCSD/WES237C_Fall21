/*
This is traditional 2-radix DIT FFT algorithm implementation.
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	Out_R, Out_I[]: Real and Imag parts of Complex signal
*/

#include "fft.h"

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);

template<int stage>
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);

void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);


void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
#pragma HLS interface ap_ctrl_chain port=return
#pragma HLS dataflow

	  DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
#pragma HLS array_partition variable=Stage1_R cyclic factor=16 dim=1
#pragma HLS array_partition variable=Stage1_I cyclic factor=16 dim=1
	  DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
#pragma HLS array_partition variable=Stage2_R cyclic factor=16 dim=1
#pragma HLS array_partition variable=Stage2_I cyclic factor=16 dim=1
	  DTYPE Stage3_R[SIZE], Stage3_I[SIZE];
#pragma HLS array_partition variable=Stage3_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage3_I cyclic factor=8 dim=1
	  DTYPE Stage4_R[SIZE], Stage4_I[SIZE];
#pragma HLS array_partition variable=Stage4_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage4_I cyclic factor=8 dim=1
	  DTYPE Stage5_R[SIZE], Stage5_I[SIZE];
#pragma HLS array_partition variable=Stage5_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage5_I cyclic factor=8 dim=1
	  DTYPE Stage6_R[SIZE], Stage6_I[SIZE];
#pragma HLS array_partition variable=Stage6_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage6_I cyclic factor=8 dim=1
	  DTYPE Stage7_R[SIZE], Stage7_I[SIZE];
#pragma HLS array_partition variable=Stage7_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage7_I cyclic factor=8 dim=1
	  DTYPE Stage8_R[SIZE], Stage8_I[SIZE];
#pragma HLS array_partition variable=Stage8_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage8_I cyclic factor=8 dim=1
	  DTYPE Stage9_R[SIZE], Stage9_I[SIZE];
#pragma HLS array_partition variable=Stage9_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage9_I cyclic factor=8 dim=1
	  DTYPE Stage10_R[SIZE], Stage10_I[SIZE];
#pragma HLS array_partition variable=Stage10_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=Stage10_I cyclic factor=8 dim=1
#pragma HLS array_partition variable=OUT_R cyclic factor=8 dim=1
#pragma HLS array_partition variable=OUT_I cyclic factor=8 dim=1

  bit_reverse(X_R, X_I, Stage1_R, Stage1_I);

  fft_stage_first(Stage1_R, Stage1_I, Stage2_R, Stage2_I);
//#pragma HLS pipeline II=1
  fft_stages<2>(Stage2_R, Stage2_I, Stage3_R, Stage3_I);
  fft_stages<3>(Stage3_R, Stage3_I, Stage4_R, Stage4_I);
  fft_stages<4>(Stage4_R, Stage4_I, Stage5_R, Stage5_I);
  fft_stages<5>(Stage5_R, Stage5_I, Stage6_R, Stage6_I);
  fft_stages<6>(Stage6_R, Stage6_I, Stage7_R, Stage7_I);
  fft_stages<7>(Stage7_R, Stage7_I, Stage8_R, Stage8_I);
  fft_stages<8>(Stage8_R, Stage8_I, Stage9_R, Stage9_I);
  fft_stages<9>(Stage9_R, Stage9_I, Stage10_R, Stage10_I);
  fft_stage_last(Stage10_R, Stage10_I, OUT_R, OUT_I);
}
unsigned int reverse_bits(unsigned int input) {
  int i, rev = 0;
  for (i = 0; i < M; i++) {
//#pragma HLS pipeline II=2
    rev = (rev << 1) | (input & 1);
    input = input >> 1;
  }
  return rev;
}

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
//Insert your code here
	  unsigned int reversed;
	  unsigned int i;

//#pragma HLS DEPENDENCE variable=OUT_I intra WAW false
//#pragma HLS DEPENDENCE variable=OUT_R intra WAW false
	  for (int i = 0; i < SIZE; i++) {
#pragma HLS pipeline II=2
		  reversed = reverse_bits(i); // Find the bit reversed index
	    if (i < reversed) {
	      // Swap the real values
	      OUT_R[i] = X_R[reversed];
	      OUT_R[reversed] = X_R[i];

	      // Swap the imaginary values
	      OUT_I[i] = X_I[reversed];
	      OUT_I[reversed] = X_I[i];
	    } else if (i == reversed) {
	      // Swap the real values
	      OUT_R[i] = X_R[reversed];

	      // Swap the imaginary values
	      OUT_I[i] = X_I[reversed];
	    }
	  }
	}
/*=======================BEGIN: FFT=========================*/
//stage 1
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
	//Insert your code here
	  int DFTpts = 1 << 1;    // DFT = 2^stage = points in sub DFT
	  int numBF = DFTpts / 2;     // Butterfly WIDTHS in sub-DFT
	  DTYPE c = W_real[0<<9];
	  DTYPE s = W_imag[0<<9];

	  // Compute butterflies that use same W**k
	  dft_loop:
	  for (int i = 0; i < SIZE; i += DFTpts) {
//#pragma HLS unroll factor=8
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE
		  int i_lower = i + numBF; // index of lower point in butterfly
	    // i: 0, 2, 4, ...
	    // i_lower: 1, 3, 5, ...
	    DTYPE xr_lower = X_R[i_lower];
	    DTYPE xi_lower = X_I[i_lower];
	    DTYPE temp_R = xr_lower * c - xi_lower * s;
	    DTYPE temp_I = xi_lower * c + xr_lower * s;
	    DTYPE xr = X_R[i];
	    DTYPE xi = X_I[i];
	    OUT_R[i_lower] = xr - temp_R;
	    OUT_I[i_lower] = xi - temp_I;
	    OUT_R[i] = xr + temp_R;
	    OUT_I[i] = xi + temp_I;
	  }
}

template<int stage>
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
//Insert your code here
  // stage 2-9
  const int DFTpts = 1 << stage;    // DFT = 2^stage = points in sub DFT
  // 4-512
  const int numBF = DFTpts / 2;     // Butterfly WIDTHS in sub-DFT
  const int loop_times = SIZE / DFTpts;
  // 2-2

  // Perform butterflies for j-th stage
  butterfly_loop:
  for (int j = 0; j < numBF; j++) {
#pragma HLS unroll factor=16
//#pragma HLS PIPELINE
#pragma HLS DEPENDENCE
    DTYPE c = W_real[j << (10 - stage)];
    DTYPE s = W_imag[j << (10 - stage)];

    // Compute butterflies that use same W**k
    // i and i_lower in all the loops are never the same,
    // covering 0-1024 all the elements when enumerating j
    dft_loop:
    for (int i_tmp = 0; i_tmp < loop_times; ++i_tmp) {
//#pragma HLS unroll factor=8
#pragma HLS PIPELINE
#pragma HLS DEPENDENCE
      int i = i_tmp * DFTpts + j;
      int i_lower = i + numBF; // index of lower point in butterfly
      DTYPE xr_lower = X_R[i_lower];
      DTYPE xi_lower = X_I[i_lower];
      DTYPE temp_R = xr_lower * c - xi_lower * s;
      DTYPE temp_I = xi_lower * c + xr_lower * s;
      DTYPE xr = X_R[i];
      DTYPE xi = X_I[i];
      OUT_R[i_lower] = xr - temp_R;
      OUT_I[i_lower] = xi - temp_I;
      OUT_R[i] = xr + temp_R;
      OUT_I[i] = xi + temp_I;
    }
  }
}

//last stage
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
	//Insert your code here
	  int DFTpts = 1 << 10;    // DFT = 2^stage = points in sub DFT
	  int numBF = DFTpts / 2;     // Butterfly WIDTHS in sub-DFT
	  // Perform butterflies for j-th stage

	  butterfly_loop:
	  for (int j = 0; j < numBF; j++) {
#pragma HLS unroll factor=16
//#pragma HLS PIPELINE
//#pragma HLS DEPENDENCE
		DTYPE c = W_real[j];
	    DTYPE s = W_imag[j];
	    // Compute butterflies that use same W**k
	    int i = j;
	    int i_lower = i + numBF; // index of lower point in butterfly
	    // i: 0, 1, 2, ...
	    // i_lower: 512, 513, ...
	    DTYPE xr_lower = X_R[i_lower];
	    DTYPE xi_lower = X_I[i_lower];
	    DTYPE temp_R = xr_lower * c - xi_lower * s;
	    DTYPE temp_I = xi_lower * c + xr_lower * s;
	    DTYPE xr = X_R[i];
	    DTYPE xi = X_I[i];
	    OUT_R[i_lower] = xr - temp_R;
	    OUT_I[i_lower] = xi - temp_I;
	    OUT_R[i] = xr + temp_R;
	    OUT_I[i] = xi + temp_I;
	  }
}
/*=======================END: FFT=========================*/




