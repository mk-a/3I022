#include "splitmerge.h"

/* tme 8 */
int predsplit( region *r, float threshold) {
  if(!r){
    fprintf(stderr, "Error in predsplit(): NULL pointer argument.\n");
    return 0;
  }
  return r->var > threshold;
}

/* tme 9 */
int predmerge( region *a, region *b, float thresh) {
  if(!a || !b){
    fprintf(stderr, "Error in predmerge(): NULL pointer argument.\n");
    return 0;
  }

  float mu, var;
  int n, na, nb;
  na = a->n; //a->x * a->y;
  nb = b->n; //b->x * b->y;
  n = na + nb;

  mu = (1. / n ) * ( a->mu * na + b->mu * nb );
  var = (1./n)*( (na*(pow(a->mu,2)+ pow(a->var,2)) ) + (nb*(pow(b->mu,2)+ pow(b->var,2)) ) ) - pow(mu,2);
  // printf("var %f\n", var);
  if (var < thresh){
    a->n = n;
    a->mu = mu;
    a->var = var;
    return 1;
  }
  else return 0;
}
