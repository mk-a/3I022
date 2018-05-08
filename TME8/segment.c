#include "splitmerge.h"
#include <stdio.h>


typedef struct {
  unsigned char* buf;
  int dimx;
} img_t;


/* TME 8 exercice 1.3 */

static gboolean draw_region(GNode* noeud, img_t* img){
  region* r = noeud->data;
  for(int i=r->ix; i<r->ix+r->x; i++)
    for(int j=r->iy; j< r->iy + r->y; j++)
      img->buf[i + j * img->dimx] = (unsigned char) r->mu;

  return 0;
}



void split_segment( GNode *qt, unsigned char *buf, int dimx) {
  // paint dans le buffer chaque cellule avec sa nuance de gris moyenne

  img_t img;
  img.buf   = buf;
  img.dimx  = dimx;
  g_node_traverse( qt, G_PRE_ORDER, G_TRAVERSE_LEAVES,-1, (GNodeTraverseFunc) draw_region, &img);

  }




/* TME 9 exercice 7 */
void merge_segment( GSList *regions, unsigned char *buf, int dimx) {
  for( GSList* reg = regions; reg != NULL; reg = reg->next ){
    region* r = reg->data;
    int n   = r->n;
    float mu  = r->mu;
    for( GSList* vois = r->merged; vois != NULL; vois = vois->next ){
      r     = vois->data;
      mu    = ( 1. / (n + r->n) ) * (mu * n    +   r->n * r->mu);
      n     = n + r->n;
    }
    r = reg->data;
    for(int i = (r->ix) ; i < (r->ix + r->x); i++){
      for(int j = (r->iy) ; j < (r->iy + r->y); j++){
        buf[i + j * dimx] = (unsigned char) mu;
      }
    }

    for(GSList* vois = r->merged; vois != NULL; vois = vois->next ){
      r = vois->data;
      for(int i=r->ix; i<r->ix+r->x; i++)
        for(int j=r->iy; j< r->iy + r->y; j++)
          buf[i + j * dimx] = (unsigned char) mu;
      // vois=vois->next;
      // printf("nb voisins : %d\n", g_slist_length(vois) );
      // vois = g_slist_remove( vois, r);

    }
    // printf("nb regions : %d\n", g_slist_length(regions) );
    // regions = g_slist_remove(regions, vois);
  }
}
