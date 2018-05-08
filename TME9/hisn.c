#include <stdlib.h>

void hisn( float *his, unsigned char *buf, long size) {
  for(int i=0; i<256; i++) his[i] = 0;     //initialisation de l'histogramme à 0
  for(int i=0; i<size; i++) his[buf[i]]++;  // incrémentation des valeurs
  for(int i=0; i<256; i++) his[i]/=size;      // normalisation
}
