
#include "hls_half.h"

typedef half DTYPE;
#define SIZE 256 		/* SIZE OF DFT */

void dft(DTYPE sample_real[SIZE], DTYPE sample_imag[SIZE]);

void dataflow1(DTYPE vecIn[SIZE], DTYPE vecOut[SIZE]);

// Sub functions
void funcA(DTYPE f1In[SIZE], DTYPE f1Out[SIZE], DTYPE f1bisOut[SIZE]);
void funcB(DTYPE f2In[SIZE], DTYPE f2Out[SIZE]);
void funcC(DTYPE f3In[SIZE], DTYPE f3Out[SIZE]);
void funcD(DTYPE f4In[SIZE], DTYPE f4bisIn[SIZE], DTYPE f4Out[SIZE]);
