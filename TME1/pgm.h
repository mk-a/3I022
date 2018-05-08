#ifndef PGM_H
#define PGM_H

unsigned char *readpgm( char *nom, int *w, int *h);
int           writepgm( char *nom, unsigned char *buf, int w, int h);



#endif
