/*
	Filename: fir_test.h
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Testbench file
		Calls fir() function from fir.cpp
		Compares the output from fir() with out.gold.dat
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fir.h"

int main () {
  const int    SAMPLES=600;
  FILE         *fp, *fin;

  data_t signal, output;
  int i, ramp_up;

  signal = 0;
  ramp_up = 1;
  
  coef_t taps[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53};


  fin=fopen("input.dat","r");
  fp=fopen("out.dat","w");

  for (i=0;i<SAMPLES;i++) {
	fscanf(fin,"%d",&signal);

	//Call the HLS block
    fir(&output,taps,signal);

    // Save the results.
    fprintf(fp,"%d\n",output);
    printf("%i %d %d\n",i,signal,output);
  }

  fclose(fp);
  fclose(fin);


  //Comparing results with the golden output.
  printf ("Comparing against output data \n");
    if (system("diff -w out.dat out.gold.dat")) {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
  	fprintf(stdout, "*******************************************\n");
       return 1;
    } else {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "PASS: The output matches the golden output!\n");
  	fprintf(stdout, "*******************************************\n");
       return 0;
    }

}

