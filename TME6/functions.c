#include "functions.h"



/*
 * Convolution 2D.
 * Important: les bords de l'image ne sont pas traités!
 */
void convol( float *out, float *in, int dimx, int dimy, float *noy, int n, int m) {
  int i,j,x,y;
  double s;
  int n2 = n/2, m2 = m/2;

  for( y=0; y<dimy; y++)
    for( x=0; x<dimx; x++) {
      s = 0.;
      for( j=-m2; j<=m2; j++)
        for( i=-n2; i<=n2; i++)
          if( x>=i && y>=j && x-i<dimx && y-j<dimy)
            s += in[(x-i)+dimx*(y-j)] * noy[i+n2+(j+m2)*n];
      *out++ = s;
    }
}

void deriv_x(float* out, float* in, int dimx, int dimy){
  if(!out || !in){
    fprintf(stderr, "Error in deriv_x(), NULL pointer argument\n");
    return;
  }
  float* noy = (float*) malloc(9 * sizeof(float));

  if(!noy){
    fprintf(stderr, "Error in deriv_x(), malloc failure\n");
    return;
  }
  noy[0] = -1;
  noy[1] = 0;
  noy[2] = 1;

  noy[3] = -2;
  noy[4] = 0;
  noy[5] = 2;

  noy[6] = -1;
  noy[7] = 0;
  noy[8] = 1;

  convol(out, in, dimx, dimy, noy, 3, 3);
  free(noy);
}


void deriv_y(float* out, float* in, int dimx, int dimy){
  if(!out || !in){
    fprintf(stderr, "Error in deriv_y(), NULL pointer argument\n");
    return;
  }
  float* noy = (float*) malloc(9 * sizeof(float));

  if(!noy){
    fprintf(stderr, "Error in deriv_y(), malloc failure\n");
    return;
  }
  noy[0] = -1;
  noy[1] = -2;
  noy[2] = -1;

  noy[3] = 0;
  noy[4] = 0;
  noy[5] = 0;

  noy[6] = 1;
  noy[7] = 2;
  noy[8] = 1;

  convol(out, in, dimx, dimy, noy, 3, 3);
  free(noy);
}

void gaussian(float sigma, float* G, int n){
  if(!G){
    fprintf(stderr, "Error in gaussian(), NULL pointer argument\n");
    return;
  }
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      G[i+n*j] = (1.0/ (2 * M_PI * sigma * sigma)) * exp( -((i-n/2)*(i-n/2) + (j-n/2) * (j - n/2)) / (2* sigma * sigma) );
}

int local_maxima(float* in,int dimx, int dimy,int x, int y){
  //return if (x,y) is a local maxima in in
  if(!in){
    fprintf(stderr, "Error in local_maxima(), NULL pointer argument\n");
    return 0;
  }

  if(!(x>=0 && x<dimx) || !(y>=0 && y<dimy) ){
    fprintf(stderr, "Error in local_maxima(), invalid argument value\n");
    return 0;
  }

  int imin, imax, jmin, jmax;
  if(x == 0) imin = 0;
  else imin = x-1;

  if(x==dimx-1) imax = x;
  else  imax = x+1;

  if(y == 0) jmin = 0;
  else jmin = y-1;

  if(y==dimy-1) jmax = y;
  else  jmax = y+1;

  for(int j = jmin; j <= jmax; j++)
    for(int i = imin; i <= imax; i++)
      if(in[i+j*dimx]> in[x+y*dimx]) return 0;
  return 1;
}


void harris(float* out, float* in, int dimx, int dimy, float kappa, float sigma, float t){
  if(!out || !in){
    fprintf(stderr, "Error in harris(), NULL pointer argument\n");
    return;
  }

  int n =(int) 2 * ceil(3 * sigma) + 1;

  float* Ix   = (float*) malloc(dimx*dimy*sizeof(float));
  float* Iy   = (float*) malloc(dimx*dimy*sizeof(float));
  float* A11  = (float*) malloc(dimx*dimy*sizeof(float));
  float* A22  = (float*) malloc(dimx*dimy*sizeof(float));
  float* A12  = (float*) malloc(dimx*dimy*sizeof(float));
  float* R    = (float*) calloc(dimx*dimy,sizeof(float));
  float* tmp  = (float*) malloc(dimx*dimy*sizeof(float)); //tempoary buffer
  float* noy  = (float*) malloc(n*n*sizeof(float));

  if(!Ix || !Iy || !A11 || !A12 || !A22 || !R || !tmp || !noy){
    fprintf(stderr, "Error in harris(), malloc failure\n");
    return;
  }
  //create the gaussian kernel
  gaussian(sigma, noy, n);

  //create Ix and Iy
  deriv_x(Ix,in,dimx,dimy);
  deriv_y(Iy,in,dimx,dimy);

  //create A11
  for(int j=0; j<dimy; j++){
    for(int i=0; i<dimx; i++){
      tmp[i+dimx*j] = Ix[i+dimx*j]*Ix[i+dimx*j];
    }
  }
  convol(A11, tmp, dimx, dimy, noy, n, n);

  //create A22
  for(int j=0; j<dimy; j++){
    for(int i=0; i<dimx; i++){
      tmp[i+dimx*j] = Iy[i+dimx*j]*Iy[i+dimx*j];
    }
  }
  convol(A22, tmp, dimx, dimy, noy, n, n);

  //create A12
  for(int j=0; j<dimy; j++){
    for(int i=0; i<dimx; i++){
      tmp[i+dimx*j] = Ix[i+dimx*j]*Iy[i+dimx*j];
    }
  }
  convol(A12, tmp, dimx, dimy, noy, n, n);

  //create R
  for(int j=0; j<dimy; j++)
    for(int i=0; i<dimx; i++)
      R[i+dimx*j] = A11[i+dimx*j] * A22[i+dimx*j] - A12[i+dimx*j] * A12[i+dimx*j] - kappa *
                    (A11[i+dimx*j]+A22[i+dimx*j]) * (A11[i+dimx*j]+A22[i+dimx*j]);


  //
  for(int j=0; j<dimy; j++){
    for(int i=0; i<dimx; i++){
      if(local_maxima(R, dimx, dimy,i,j) && R[i + j*dimx] > t) out[i + j*dimx]=1;
      else out[i + j*dimx]=0;
    }
  }

  
  free(Ix);
  free(Iy);
  free(A11);
  free(A12);
  free(A22);
  free(R);
  free(tmp);
  free(noy);


}
