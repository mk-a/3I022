#include <inrimage/image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char version[]="1.00";
static char usage[]="[input][output][-sb seuil]";
static char detail[]="";


int compar(const void* a, const void* b){
  int* a2 = (int*) a;
  int* b2 = (int*) b;
  if(*a2==*b2) return 0;
  else if (*a2<*b2) return -1;
  else return +1;
}

void swap(unsigned char* a, unsigned char*b){
  unsigned char tmp = *a;
  *a=*b;
  *b=tmp;
}

void triBulle(unsigned char* array){
  int a=1;
  while(a){
    a=0;
    for(int i=0; i<8; i++){
      if(array[i]>array[i+1]){
        swap(&array[i],&array[i+1]);
        a=1;
        break;
      }
    }
  }
}



int main( int argc, char **argv) {
  if(argc!=3){
    fprintf(stderr, "Error. Expected 2 argument. %d given. Usage :\n",argc-1 );
    fprintf(stderr, "%s input output\n", argv[0]);
    return 1;
  }
  char *fname=strdup(argv[1]);
  char *fname2=strdup(argv[2]);
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf, *buf2;
  int sb = 0, i, j;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);

  /* Lecture des options */
  igetopt1( "-sb", "%d", &sb);
  infileopt( fname);

  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc( NDIMX * NDIMY * NDIMV *  sizeof(unsigned char));

  //creation d'un second buffer temporaire
  buf2 = (unsigned char*)i_malloc( NDIMX * NDIMY * NDIMV * sizeof(unsigned char));

  /* lecture image */
  c_lect( nf, NDIMY, buf);

  /* fermeture image */
  fermnf_( &nf);
  // if(NDIMV!=1){
  //   fprintf(stderr, "Erreur. Trop de composantes\n");
  //   return 2;
  // }

  /* Traitement */


// traitement pour n composantes
  /*
  for( j=0; j<NDIMY; j++){
    for( i=0; i<NDIMX; i++){
      for( int v = 0; v < NDIMV; v++){
        unsigned char tmp [9];
        for( int j2=-1; j2<2; j2++){
          for(int i2= -1; i2<2; i2++){
            int j3, i3;
            if( ((j==0) && (j2==-1)) || ((j == NDIMY-1) && (j2==1)) )
              j3=j;
            else
              j3=j+j2;
            if( ((i==0) && (i2==-1)) || ((i == NDIMY-1) && (i2==1)) )
              i3=i;
            else
              i3=i+i2;

            printf("yo\n");
            tmp[ (j2+1)*3 + i2 + 1] = buf[j3*DIMX*NDIMV+i3*NDIMV+v];
            printf("ya\n");
            // printf("i =  %d\n",(j2+1)*3 + i2 + 1 );
            printf("i= %d j= %d i2= %d  j2= %d  i3= %d  j3= %d  v= %d\n",i, j,i2,j2,i3 , j3, v );
            // for(int k =0; k<9; k++) printf("%d  ",tmp[k] );
            // printf("\n");
            // qsort(tmp, 9, sizeof(unsigned char),&(compar));
            triBulle(tmp);
            // for(int k =0; k<9; k++) printf("%d  ",tmp[k] );
            // printf("\n");
            buf2[j*DIMX*NDIMV+i*NDIMV+v]=tmp[5];

          }
        }
      }
    }
  }*/

  for( j=0; j<NDIMY; j++)
    for( i=0; i<NDIMX; i++){
        unsigned char tmp [9];
        for( int j2=-1; j2<2; j2++)
          for(int i2= -1; i2<2; i2++){
            int j3, i3;
            if(j==0 || j == NDIMY-1 )
            j3=j;
            else
            j3=j+j2;
            if(i==0 || i == NDIMY-1 )
            i3=i;
            else
            i3=i+i2;

            tmp[ (j2+1)*3 + i2 + 1] = buf[j3*DIMX+i3];
            triBulle(tmp);
            buf2[j*DIMX+i]=tmp[5];





          }

      }



  /* Ecriture de l'image */
  outfileopt( fname2);
  nf = image_(fname2, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf2);
  fermnf_( &nf);

  i_Free( (void*)&buf);
  return 0;
}
