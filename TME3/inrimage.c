/*
 * LI316 - Introduction a l'imagerie numerique
 * Fichier template Inrimage
 */

#include <inrimage/image.h>

static char version[]="1.00";
static char usage[]="[input][output][-sb seuil]";
static char detail[]="";

void histogram(int his[256], unsigned char* buf, long size){
      if(!buf || !his) return;
      int i;
      for(i=0; i<256; i++) his[i]=0;
      for(i=0; i<size; i++) his[buf[i]]++;
}

void display_histogram(int his[256]){
      if(!his) return;
      int i;
      for(i=0; i<256; i++) printf("%3d    %5d\n",i,his[i] );
}


int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  int sb = 0, i, j, sh = 255;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);

  /* Lecture des options */
  igetopt1( "-sb", "%d", &sb);
  igetopt1( "-sh", "%d", &sh);
  infileopt( fname);

  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1 && NDIMV ==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc( NDIMX * NDIMY*sizeof(unsigned char));

  /* lecture image */
  c_lect( nf, NDIMY, buf);

  /* fermeture image */
  fermnf_( &nf);

  /* Traitement */
  for( j=0; j<NDIMY; j++)
    for( i=0; i<NDIMX; i++){
      if( buf[i+j*NDIMX] < sb)
      buf[i+j*NDIMX] = 0;
      else if (buf[i+j*NDIMX]>sh)
        buf[i+j*NDIMX]=255;
    }

  /* Ecriture de l'image */
  outfileopt( fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf);
  fermnf_( &nf);

  i_Free( (void*)&buf);
  return 0;
}
