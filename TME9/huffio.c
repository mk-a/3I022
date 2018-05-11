/* Huffman: entrées/sorties */
#include <stdio.h>
#include <stdlib.h>
#include "huffio.h"

struct huffhead {
  int dimx, dimy, dimz, dimv, bsize;
  int lhuf;
  size_t lenc;
};

/**
 * Ecrit une image compressé par huffman dans un format binaire.
 * @param name nom du fichier à écrire
 * @param his histogramme normalisé
 * @param L   taille du tableau his
 * @param enc tampon de l'image encodée
 * @param lenc taille du tampon encbuf (en octet)
 * @param lfmt format de l'image décodée.
 */

void writehuff( char *name, float *his, int L, unsigned char *enc, int lenc, Fort_int lfmt[] ) {
  struct huffhead head = {NDIMX, NDIMY, NDIMZ, NDIMV, BSIZE};
  FILE *fp;

  fp = *name != '>' ? fopen( name, "wb") : stdout;

  head.lhuf = L;
  head.lenc = lenc;
  fwrite( &head, sizeof(struct huffhead), 1, fp);
  fwrite( his, sizeof(float), L, fp);
  fwrite( enc, 1, lenc, fp);

  if( *name != '>') fclose(fp);
}

/**
 * Lit une image compressé par huffman.
 * @param name fichier à décoder
 * @param lfmt format de l'image décodée
 * @param his histogramme normalisé de l'image
 * @param L taille de histogramme
 * @oaram lenc taille du tampon retournée
 * @return adresse du tampon de l'image encodée
 */

unsigned char* readhuff( char *name, Fort_int lfmt[], float **his, int *L,
			 int *lenc) {
  struct huffhead head;
  unsigned char *buf;
  FILE *fp = *name != '<' ?  fopen( name, "r") : stdin;
  fread( &head, sizeof(struct huffhead), 1, fp);
  NDIMX = head.dimx;
  NDIMY = head.dimy;
  NDIMZ = head.dimz;
  NDIMV = head.dimv;
  BSIZE = head.bsize;
  TYPE = FIXE;
  EXP = 200;
  DIMX = NDIMX*NDIMV;
  DIMY = NDIMY*NDIMZ;
  *L = head.lhuf;
  *lenc = head.lenc;

  *his = (float *) malloc(sizeof(float)**L);
  fread( *his, sizeof(float), *L, fp);

  buf = (unsigned char *)malloc( head.lenc);
  fread( buf, 1, head.lenc, fp);

  if( *name != '<') fclose( fp);
  return buf;
}
