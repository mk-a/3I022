#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf, *out;
  char nom[128];
  GNode *qt;
  float split_thresh = 400;
  float merge_thresh = 400;
  int xmin = 2, ymin = 2;
  int nb_region = 0;

  inr_init ( argc, argv, "1.0",
	     "[input] [output] [-min xmin ymin] -s seuil_split -m seuil_merge",
	     "segmentation par split puis merge");

  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if ( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "Codage non acceptable\n");
  buf = (unsigned char*) i_malloc( sizeof(unsigned char) * DIMX * DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_( &nf);

  igetopt1( "-s", "%f", &split_thresh);
  igetopt1("-m","%f", &merge_thresh);
  igetopt2( "-min", "%d", &xmin, "%d", &ymin);

  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);
  count_region(qt, &nb_region);

  fprintf( stderr, "stats image: mu = %g  v = %g nb_split_regions = %d",
	   ((region*)qt->data)->mu, ((region*)qt->data)->var, nb_region);


  /* Pour répondre l'exercice 1.2 */
  // split_print_regions( qt);


  /* Compléter cette partie pour répondre à la question
  */
  GSList* cells   = merge_list_regions(qt);
  GSList* merged  = merge(cells, merge_thresh);
  fprintf(stderr, " nb_merged_regions %d\n", g_slist_length(merged));

  out = (unsigned char*) i_malloc(sizeof(unsigned char)*DIMX*DIMY);
  merge_segment(merged, out, DIMX);

  outfileopt( nom);
  nf  = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, out);
  // fermnf_(&nf);


  /* Compléter cette partie pour répondre à la question
     1.4 : affichage des statistiques */

}
