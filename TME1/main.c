#include <stdio.h>
#include <stdlib.h>
#include "histogram.h"
#include "pgm.h"
#include "etire.h"
#include <string.h>
#include "seuillage.h"

char* rename_path(char* path){
  if(!path) return NULL;
  char* new_path=(char*) malloc( ( strlen(path)+2 )*sizeof(char) );
  if(!new_path) return NULL;
  int i=0, j=0;
  while(path[i]){
    if(path[i]=='.'){
      new_path[j++]='_';
      new_path[j++]='2';
      new_path[j++]=path[i++];
    }
    else {
      new_path[j++]=path[i++];
    }
  }
  return new_path;
}

int main(int argc, char const *argv[]) {
  if(argc<2){
    fprintf(stderr, "1 argument is required.\n");
    return -1;
  }
  char* path= strdup(argv[1]);
  if(!path){
    fprintf(stderr, "Error strduo\n");
    return -2;
  }
  char* path2=rename_path(path);

  int w,h;
  unsigned char* img= readpgm(path,&w,&h);
  if(!img) return -1;

  int his[256], table[256];

  histogram(his,img,h*w);
  etire(table,his);

  seuillage(img,h*w,100,155);
  // applique(img,w*h,table);


  writepgm(path2,img,w,h);


  // display_histogram(his2);





return 0;
}
