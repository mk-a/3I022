#include <inrimage/image.h>

void           writehuff ( char *name, float *his, int L, unsigned char *enc, int lenc, Fort_int lfmt[]);
unsigned char* readhuff  ( char *name, Fort_int lfmt[], float **his, int *L, int *lbuf);
