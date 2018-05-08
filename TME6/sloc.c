/*
 * Calcul et affichage de maxima locaux dans une image
 */
#include <inrimage/image.h>



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


/* calcul des max locaux: à vous ! (question 1) */
void seuilloc( float *out, float *in, int dimx, int dimy, float seuil) {
  if(!in || !out){
    fprintf(stderr, "Error in local_maxima(), NULL pointer argument\n");
    return;
  }
  int imin, imax, jmin, jmax;
  for(int j=0; j<dimy; j++){
    for (int i=0; i<dimx; i++){
      if(local_maxima(in,dimx,dimy,i,j) && in[i + j*dimx]>seuil) {

        if(j <= 1) jmin =0;
        else jmin = j-2;

        if (i <= 1) imin = 0;
        else imin = i-2;

        if( j >= dimy-2) jmax = dimy -1;
        else jmax = j + 2 ;

        if (i >= dimx-2) imax = dimx-1;
        else imax = i+2;

        for(int i1 = imin; i1<= imax; i1++)
          printf("%d %d\n",i1+1, j+1);
        for(int j1 = jmin; j1<= jmax; j1++)
            printf("%d %d\n",i+1, j1+1);
        // printf("##!draw(L %d %d %d %d , L %d %d %d %d )\n",imin+1, j+1, imax+1, j+1, i+1, jmin+1, i+1, jmax+1 );

        // printf("%d %d\n",i+1,j+1 );// Exercice 2 question 2
        out[i + j*dimx] = 1;
      }
      else out[i + j*dimx ]=0;
    }
  }
}

int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  float *bufI, *bufO;
  float seuil = 0.5;
  char nom[128];

  inr_init( argc, argv, "", "", "");

  infileopt( nom);
  nf = c_image( nom, "e", "", lfmt);
  bufI = (float*)i_malloc( sizeof(float)*DIMX*DIMY);
  c_lecflt( nf, DIMY, bufI);
  fermnf_( &nf);

  bufO = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  /* traitement */
  igetopt1( "-n", "%f", &seuil);
  seuilloc( bufO, bufI, DIMX, DIMY, seuil);


  /* sauvegarde, pour répondre à la question 1 */
  outfileopt( nom);
  TYPE = PACKEE; BSIZE = -1; EXP=0;
  nf = c_image( nom, "c", "", lfmt);
  c_ecrflt( nf, DIMY, bufO);
  fermnf_( &nf);


  /* affichage des coordonnées des max locaux, pour
     répondre à la question 2: à vous ! */



  i_Free( (void*)&bufI);
  i_Free( (void*)&bufO);

  return 0;
}
