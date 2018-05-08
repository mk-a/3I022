#include "etire.h"
#include <stdio.h>


void etire(int table[256], int his[256]){
      if(!table || !his) return;
      unsigned char min=255,max=0;
      int i;
      for(i=0; i<256; i++){
            table[i]=0;
            if(i<min && his[i]>0) min=i;
            if(i>max && his[i]>0) max=i;
      }

      for(i=min; i<=max; i++)
            table[i]=(int)(((i-min)/(float)(max-min))*255);

}

void applique(unsigned char* buf, long size, int table[256]){
      if(!buf) return;
      int i;
      for(i=0; i<size; i++)
            buf[i]=table[buf[i]];


}
