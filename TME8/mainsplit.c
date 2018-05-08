#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf, *out;
  char nom[128];
  GNode *qt;
  float split_thresh = 10;
  int xmin = 2, ymin = 2;
  int nb_region = 0;

  inr_init ( argc, argv, "1.0",
	     "[input] [output] [-min xmin ymin] -s seuil",
	     "segmentation par split");

  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if ( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "Codage non acceptable\n");
  buf = (unsigned char*) i_malloc(DIMX*DIMY);
  out = (unsigned char*) i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_( &nf);

  igetopt1( "-s", "%f", &split_thresh);
  igetopt2( "-min", "%d", &xmin, "%d", &ymin);

  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);
  count_region(qt, &nb_region);

  fprintf( stderr, "stats image: mu = %g  v = %g nb_region = %d\n",
	   ((region*)qt->data)->mu, ((region*)qt->data)->var, nb_region);


  /* Pour répondre l'exercice 1.2 */

  /* Compléter cette partie pour répondre à la question
  */
  split_segment(qt,out,DIMX);

  outfileopt( nom);
  nf  = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, out);
  fermnf_(&nf);


  /* Compléter cette partie pour répondre à la question
     1.4 : affichage des statistiques */

}
