#include <stdlib.h>
#include <math.h>
void hisn( float *his, unsigned char *buf, long size) {
  //calcul l'histogramme normalisé pour un codage 8bits nuance de gris
  //his doit déja être alloué
  for(int i=0; i<256; i++) his[i] = 0;     //initialisation de l'histogramme à 0
  for(int i=0; i<size; i++) his[buf[i]]++;  // incrémentation des valeurs
  for(int i=0; i<256; i++) his[i]/=size;      // normalisation
}


double entropie(float* his){
  //calcul de l'entropie de l'image a partir de son histogramme normalisé
  // pour une image codage 8 bits nuance de gris
  double ent = 0.;
  for(int i=0; i<256; i++)
    if( his[i] ) // his[i]!=0
        ent -= his[i] * log2(his[i]);

  return ent;
}
