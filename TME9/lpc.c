#include <stdio.h>

void mat2lpc( char *out, unsigned char *in, int dimx, int dimy) {
  if(!out || !in) {
    fprintf(stderr, "Error in mat2lpc, NULL pointer argument\n");
    return;
  }
  //out = I - Î except for the first column where out = I
  for(int j=0; j< dimy; j++){
    out[j*dimx] = in[j*dimx];
    for(int i =1; i< dimx; i++){
      out[i + j*dimx] = in[i + j*dimx] - in[i-1 + j*dimx];
    }
  }
}

void lpc2mat( unsigned char *out, char *in, int dimx, int dimy) {
  if(!out || !in) {
    fprintf(stderr, "Error in lpc2mat, NULL pointer argument\n");
    return;
  }
  for(int j=0; j< dimy; j++){
    out[j*dimx] = in[j*dimx];
    for(int i =1; i< dimx; i++){
      out[i + j*dimx] = in[i + j*dimx] + out[i-1 + j*dimx];
    }
  }

}
