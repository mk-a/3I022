typedef unsigned char uchar;

void hisn      ( float *his, uchar *buf, long size);

void hufftable ( float *his, char **table, int L) ;

int  huffenc   ( uchar *out, uchar *in, long size, char **table);
void huffdec   ( uchar *out, uchar *in, long sin, char **table, int ncode);
