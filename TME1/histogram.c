#include "histogram.h"
#include <stdio.h>


void histogram(int his[256], unsigned char* buf, long size){
      if(!buf || !his) return;
      int i;
      for(i=0; i<256; i++) his[i]=0;
      for(i=0; i<size; i++) his[buf[i]]++;
}

void display_histogram(int his[256]){
      if(!his) return;
      int i;
      for(i=0; i<256; i++) printf("%3d    %5d\n",i,his[i] );
}
