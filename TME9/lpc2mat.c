#include <inrimage/image.h>
#include "lpc.h"

int main( int argc, char **argv) {
  char nom[128];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *in, *out;

  inr_init(argc, argv, "1.0", "[in][out]", "encodage predicteur lineaire du premier ordre");

  
  infileopt( nom);
  nf = image_(nom,  "e", "", lfmt);
  if( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "codage non accepte\n");
  in = i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, in);
  fermnf_(&nf);

  out = i_malloc(DIMX*DIMY);
  lpc2mat( out, in, DIMX, DIMY);

  /* l'image de sortie n'est pas signée */
  if( EXP <0) EXP = -EXP;
  outfileopt(nom);
  nf = image_(nom,"c", "", lfmt);
  c_ecr( nf, DIMY, out);
  fermnf_(&nf);

  return 0;
}



