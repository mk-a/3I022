#include "splitmerge.h"


/* TME8 */
static
region *creer_region( unsigned char *buf, int ix, int iy, int x, int y, int dimx) {
  region *r = (region *) g_malloc( sizeof(region));

  r->ix = ix;
  r->iy = iy;
  r->x  = x;
  r->y  = y;

  /* calcul des moyenne et variance de la region*/

  r -> n = r->x * r->y;
  r -> mu = r-> var = 0;

  for(int i = ix; i < ix+x; i++){
    for(int j = iy; j < iy+y; j++){
      r->mu += buf[i + j*dimx];
    }
  }
  r->mu /= r->n;

  for(int i=ix; i< ix+x; i++){
    for(int j=iy; j< iy+y; j++){
      r->var +=pow(buf[i+j*dimx]-r->mu,2);
    }
  }
  r->var /= r->n;
  // printf("x=%d y=%dmu= %f var= %f\n",r->mu, r->var );
  return r;
}


static
void split_rec( unsigned char *buf, int dimx, GNode *noeud, float t, int xmin, int ymin) {
  region *r = noeud -> data;
  region *sreg;
  if( r->x/2 >= xmin && r->y/2 >= ymin &&
      r->x % 2 == 0 && r->y % 2 == 0 &&
      predsplit( r, t) ) {
    sreg = creer_region( buf,r->ix,r->iy,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix+r->x/2,r->iy,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix,r->iy+r->y/2,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix+r->x/2,r->iy+r->y/2,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
  }
}


GNode *split( unsigned char *buf, int dimx, int dimy, float threshold,
	      int xmin, int ymin) {
  region *racine;
  GNode *qt;
  racine = creer_region( buf, 1, 1, dimx, dimy, dimx);
  qt = g_node_new(racine);
  split_rec( buf, dimx, qt, threshold, xmin, ymin);
  return qt;
}
