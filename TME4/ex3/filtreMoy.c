#include "filtreMoy.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  if(argc!=4){
    fprintf(stderr, "Error arguments. 3 expected:\n %s -d \033[4mnn\033[0m output.inr\nWhere nn is the dimension of the filter\n",argv[0]);
    return -1;
  }
  int dim = atoi(argv[2]);
  if(dim<1){
    fprintf(stderr, "Error, dimension must be positive.\n");
    return -2;
  }
  FILE* fp= fopen(argv[3],"w");
  if(!fp){
    fprintf(stderr, "Error. Could not open the file: %s\n",argv[3]);
    return -3;
  }
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++)
      fprintf(fp, "%f ",(1./(dim*dim)));
    fprintf(fp, "\n");
  }
  return 0;
}
