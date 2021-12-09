
#include "hls_half.h"

typedef half DTYPE;
#define SIZE 256 		/* SIZE OF DFT */

void dft(DTYPE sample_real[SIZE], DTYPE sample_imag[SIZE]);

void funcA(DTYPE *in1, DTYPE *in2, DTYPE *out1, DTYPE *out2);

void funcB(DTYPE *in, DTYPE *out);

void funcC(DTYPE *in, DTYPE *out);

void funcD(DTYPE *in1, DTYPE *in2, DTYPE *out1, DTYPE *out2);
