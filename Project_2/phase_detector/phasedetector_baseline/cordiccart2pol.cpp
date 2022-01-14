#include "phasedetector.h"
#include <stdio.h>


data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000};//,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};//,1.52588E-05, 7.62939E-06, 3.8147E-06, 1.90735E-06};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320};//,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};//,1.52587890613158E-05, 7.62939453110197E-06, 3.81469726560650E-06, 1.90734863281019E-06};



data_t Scale_factor =  0.6072529350088812561694;



void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS PIPELINE II=2


	// Write your code here

	data_t current_x = x;
	data_t current_y = y;
	data_t acc_angle = 0;
	data_t tmp_x = 0;

    data_t rotation = 1.5707963268;

	//1. Rotate the initial vector into either Quadrant I or IV
	if( current_x < 0 )  //Check if initial vector is in quadrant II or III
	 {
		//rotate by +/- 90 degrees
	    tmp_x = current_x;
		if( current_y > 0)  //if initial vector is in quadrant II, then rotate it to quadrant I
	      {
			current_x = current_y;
			current_y = -tmp_x;
			acc_angle = -rotation;
		  }
		else   //if initial vector is in quadrant III, then rotate it to quadrant IV
		  {
			current_x = -current_y;
			current_y = tmp_x;
			acc_angle = rotation;
          }
	  }
	 else   //If initial vector is in quadrant I or IV
	  {
		acc_angle = 0.0;
	  }

	for(int i = 0; i < NO_ITER; i++)
	   {


		tmp_x = current_x;

		if(current_y >= 0.0)
		 {
		   current_x = current_x + current_y*Kvalues[i];
		   current_y = current_y - tmp_x*Kvalues[i];
		   acc_angle = acc_angle - angles[i];
		 }
		 else
		 {
		   current_x = current_x - current_y*Kvalues[i];
		   current_y = current_y + tmp_x*Kvalues[i];
           acc_angle = acc_angle + angles[i];
		 }
	   }



	   *theta = -acc_angle;
	   *r = current_x * Scale_factor;


}
