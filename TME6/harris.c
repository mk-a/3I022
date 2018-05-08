#include "functions.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  float *bufI, *bufH;
  float kappa = 0.02, sigma = 2, t=0.001;
  // char* fname_in = strdup(argv[1]);
  // char* fname_out = strdup(argv[2]);
	char nom[128];
	inr_init( argc, argv, "", "", "");

  infileopt( nom);
  /* lecture en mode flottant => fonctionne avec tout type d'image */
  nf = c_image( nom, "e", "", lfmt);
  bufI = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  c_lecflt( nf, DIMY, bufI);
  fermnf_( &nf);

  /* paramètres utiles au futur filtre Harris */
  igetopt1( "-K", "%f", &kappa);
  igetopt1( "-s", "%f", &sigma);
  igetopt1( "-t", "%f", &t);
  bufH = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  /* traitement */
	harris(bufH, bufI, DIMX, DIMY, kappa, sigma, t);

  /* sauvegarde, au format virgule flottante */
  outfileopt( nom);
  TYPE =  REELLE; BSIZE = sizeof(float);
  nf = c_image( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, bufH);

  fermnf_( &nf);

  i_Free( (void*)&bufI);
  i_Free( (void*)&bufH);
}
