#include <inrimage/image.h>
#include "huffman.h"
#include <stdlib.h>
#include "huffio.h"

int main( int *argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];

  unsigned char *buf, *buf_enc;

  char nom[128];
  int L = 256; // taille tableau his
  float *his    = (float*) malloc(L * sizeof(float)); // histogramme normalisé de l'image
  char **table  = (char**) malloc(L * sizeof(char*)); // table de huffman

  inr_init( argc, argv, "", "", "");

  /* Lecture image 1 octet */
  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if( BSIZE != 1 || TYPE != FIXE)
    imerror( 6, "Codage non accepte\n");
  buf     = (unsigned char*) i_malloc(DIMX*DIMY);
  buf_enc = (unsigned char*) i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_(&nf);

  /* Appel a histn() */
  hisn(his, buf, DIMX*DIMY);
  /* Calcul table de Huffman */
  hufftable(his, table, L);
  // for(int i=0; i<L; i++) printf("%s\n",table[i] );

  /* encodage image */
  int size = huffenc( buf_enc, buf, DIMX*DIMY, table);

  /* ecriture image */
  outfileopt(nom);

  writehuff( nom, his, L, buf_enc, (size+7)/8, lfmt );

  return 0;
}
