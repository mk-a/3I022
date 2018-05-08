#include "seuillage.h"
#include <stdio.h>


void seuillage(unsigned char* buf, long size, int bas, int haut){
  if(!buf){
    fprintf(stderr, "Error. NULL pointer\n");
    return;
  }
  if(bas<0 || haut>255 || bas>=haut){
    fprintf(stderr, "Error arguments\n");
    return;
  }
  for(int i=0; i<size; i++){
    if(buf[i]<=bas) buf[i]=0;
    if(buf[i]>=haut) buf[i]=255;
  }
}
