#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>
#include "linkedlist2.h"


int local_maxima(int* in,int dimx, int dimy, int dimz, int x, int y, int z){
  //return if (x,y) is a local maxima in in
  if(!in){
    fprintf(stderr, "Error in local_maxima(), NULL pointer argument\n");
    return 0;
  }

  if(!(x>=0 && x<dimx) || !(y>=0 && y<dimy) || !(z>=0 && z<dimz) ){
    fprintf(stderr, "Error in local_maxima(), out of bounds arguments\n");
    return 0;
  }

  int imin, imax, jmin, jmax, kmin, kmax;
  if(x == 0) imin = 0;
  else imin = x-1;

  if(x==dimx-1) imax = x;
  else  imax = x+1;

  if(y == 0) jmin = 0;
  else jmin = y-1;

  if(y==dimy-1) jmax = y;
  else  jmax = y+1;

  if(z == 0) kmin = 0;
  else kmin = z-1;

  if(z==dimz-1) kmax = z;
  else  kmax = z+1;

  for(int k = kmin; k <= kmax; k++)
    for(int j = jmin; j <= jmax; j++)
      for(int i = imin; i <= imax; i++)
        if(in[i+ j*dimx + k*dimx*dimy]> in[x + y*dimx + z*dimx*dimy]) return 0;
  return 1;
}



// return if the the pixel (ix,iy) belongs to the circle of center (x,y) and of radius r
// with the tolerance: tolerance
int pixelincircle(int ix, int iy, float x, float y, float r, float tolerance){
  return fabs( sqrt( (x - ix)*(x - ix) + (y - iy)*(y - iy) ) - r) <= tolerance;
}


int *houghCircle( int *nx, int *ny, int* nr, float dx, float dy, float dr, float tolerance, unsigned char *bufin, int dimx, int dimy) {
	if(!nx || !ny || !nr || !bufin){
		fprintf(stderr, "Error in hough(): NULL pointer argument.\n");
		return NULL;
	}
  float rmax = sqrt(dimx*dimx + dimy*dimy)/2;
  //I consider that the highest radius possible is equal to the half of the diagonal
	*nx  = (int) (dimx / dx);
	*ny  = (int) (dimy / dy);
  *nr  = (int) (rmax / dr);

	int* acc = (int*) calloc( (*nx)*(*ny)*(*nr), sizeof(int));
	if(!acc){
		fprintf(stderr, "Error in hough(), malloc failure.\n");
		return NULL;
	}

  for(int ix  = 0  ; ix < *nx ; ix++){
    fprintf(stderr,"%d/%d\n",ix,*nx );
    int x = (dimx * ix) / *nx;
    //where ix represents the index of x in the buffer and x the abscissa of the center of the circle
    for(int iy  = 0  ; iy < *ny ; iy++){
      int y = (dimy * iy) / *ny;
      for(int ir = 0  ; ir < *nr ; ir++){
        int r = (rmax * ir) / *nr;
        for(int i = 0 ; i < dimx ; i++){
          for(int j = 0 ; j < dimy ; j++){
            if( bufin[i + j*dimx]>200){
              if( pixelincircle(i,j,x,y,r, tolerance) ){
                acc[ix + iy * *nx + ir * *nx * *ny]++;
              }
            }
          }
        }
      }
    }
  }
  return acc;
}


void drawCircle(int x, int y, int r){
  printf("##!draw(a %d %d %d)\n",x-r+1, y-r+1, 2*r);
}


void findmax( int *acc, int nx, int ny, int nr, double dx, double dy, double dr, int n, int dimx, int dimy) {
 if(!acc){
   fprintf(stderr, "Error in findmax(): NULL pointer argument.\n");
   return;
 }

 list_value_t* values = NULL;

 for(int ix=0; ix<nx; ix++)
  for(int iy=0; iy<ny; iy++)
    for(int ir=0; ir<nr; ir++)
      addValue(&values,	acc[ix + iy * nx + ir * nx * ny], ix, iy, ir);

 list_value_t* current_value = values;
 if(!values) return;
 list_point_t* current_point = values->points;
 while(n && current_value){
   if(local_maxima(acc,nx, ny, nr, current_point->ix, current_point->iy, current_point->ir)){
     int x = dx * current_point->ix;
     int y = dy * current_point->iy;
     int r = dr * current_point->ir;
     drawCircle(x,y,r);
     n--;
   }
   current_point = current_point->next;
   if(!current_point){
     current_value = current_value->next;
     if(current_value) current_point = current_value->points;
   }
 }
 freeListValue(values);

}


int main(int argc, char *argv[]) {
  Fort_int lfmt[9];
  struct image *nf;
  char nom[256];
  unsigned char *buf;
  int *acc;
  float tolerance = 5;
  float dx=3, dy=3, dr=1;
  int nx, ny, nr; //size of each dimension of the accumulator
  int n = 25; // find 25 circle

  inr_init( argc, argv, "1.0", "[input][output] options",
	    "Compute the Hough transform for circles. Options are\n"
	    "		-t %f: tolerance\n"
      "		-sx %f: increment size for x\n"
      "		-sy %f: increment size for y\n"
	    "		-sr %f: increment size for radius\n"
			"		-n %d number of circles to find\n");

  infileopt(nom);

	 igetopt1( "-t", "%f", &tolerance);
	 igetopt1( "-sx", "%f", &dx);
	 igetopt1( "-sy", "%f", &dy);
	 igetopt1( "-sr", "%f", &dr);
	 igetopt1( "-n", "%d", &n);

  /* lecture image: c'est une image de contours codée sur 1 octet */
  nf = image_(nom,"e","",lfmt);
  if( BSIZE != 1 || TYPE != FIXE) //si l'image n'est pas code sur 1 octet avec virgule fixe
    imerror( 6, "Codage non accepté\n");
  buf= (unsigned char*)i_malloc(DIMX*DIMY*sizeof(unsigned char));
  c_lect(nf, NDIMY, buf);
  fermnf_(&nf);


  /* à compléter: lecture des paramètres de l'algo, question 3 */


  /* calcul de l'accumulateur de Hough */

  acc = houghCircle( &nx, &ny, &nr, dx, dy, dr, tolerance, buf, DIMX,DIMY);
	findmax(acc, nx, ny, nr, dx, dy, dr, n, DIMX, DIMY);

  /* écriture de l'accumulateur (pour répondre à la question 3) */

  outfileopt( nom);
  NDIMX = DIMX  = nx;
  NDIMY = DIMY  = ny;
  NDIMZ = NDIMV = nr;
  /* codage sur 4 octets en virgule fixe */
  BSIZE=sizeof(int);TYPE=FIXE;EXP=0;
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, acc);
  fermnf_(&nf);

	free(acc);

  return 0;

}
