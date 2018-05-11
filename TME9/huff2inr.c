#include <inrimage/image.h>
#include "huffman.h"
#include <stdlib.h>
#include "huffio.h"

int main( int *argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf, *buf_enc;
  char nom[128];
  float *his;
  int L, lenc;
  char **table;
  inr_init( argc, argv, "", "", "");

  infileopt( nom);

  /* lecture de l'image encodee */
  buf_enc = readhuff(nom, lfmt, &his, &L, &lenc);

  /* creation de la table */
  table = (char**) malloc(L * sizeof(char*));
  hufftable(his, table, L);


  /* decodage image */
  buf = (unsigned char *) malloc(DIMX * DIMY * sizeof(char));
  huffdec( buf, buf_enc, lenc*8, table, L);


  /* ecriture image */
  outfileopt(nom);
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, buf);
  fermnf_(&nf);



  return 0;
}
