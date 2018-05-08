#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void convol( float *out, float *in, int dimx, int dimy, float *noy, int n, int m);
void deriv_x(float* out, float* in, int dimx, int dimy);
void deriv_y(float* out, float* in, int dimx, int dimy);
void gaussian(float sigma, float* G, int n);
int local_maxima(float* in,int dimx, int dimy,int x, int y);
void harris(float* out, float* in, int dimx, int dimy, float kappa, float sigma, float t);


#endif
