#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"


unsigned char* readpgm( char *nom, int *w, int *h) {
  char line[5];
  unsigned char *buf = NULL;
  FILE *fp = fopen( nom, "r");

  if( fp == NULL) return NULL;
  fgets( line, 4, fp);
  if( *line == 'P' && *(line+1) == '5') {
    int c;
    if( (c=fgetc(fp)) == '#')
      while( (c=fgetc(fp)) != '\n');
    else
      ungetc(c,fp);
    fscanf( fp, "%d %d\n%d\n", w, h, &c);
    buf = malloc(sizeof(char)**w**h);
    fread( buf, sizeof(char), *w**h, fp);
  } else
    fprintf( stderr, "readpgm: %s has an unsupported format\n", nom);
  fclose( fp);
  return buf;
}



int writepgm( char *nom, unsigned char *buf, int w, int h) {
  FILE *fp = fopen( nom, "w");

  if( fp != NULL) {
    fprintf( fp, "P5\n%d %d\n255\n", w, h);
    fwrite( buf, sizeof(char), w*h, fp);
    fclose( fp);
    return 1;
  }
  fprintf(stderr,"writepgm: write error with %s\n", nom);
  return 0;
}
