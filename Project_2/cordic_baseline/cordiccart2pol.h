#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#define NO_ITER 16

typedef int   coef_t;
typedef float data_t;
typedef float acc_t;
typedef double COS_SIN_TYPE;
typedef double THETA_TYPE;


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif
