#include "linkedlist2.h"

void addPoint(list_point_t** list, int ix, int iy, int ir){
  //insertion at the head of the list
  if(!list){
    fprintf(stderr, "Error in addPoint(), NULL pointer argument\n");
    return;
  }

  list_point_t* new = (list_point_t*) malloc(sizeof(list_point_t));
  if(!new){
    fprintf(stderr, "Error in addPoint(), malloc failure\n");
    return;
  }
  new->next   = *list;
  new->ix = ix;
  new->iy = iy;
  new->ir = ir;
  *list = new;
}


void addValue(list_value_t** list, int value, int ix, int iy, int ir){
  // ordered insertion
  if(!list){
    fprintf(stderr, "Error in addValue(), NULL pointer argument\n");
    return;
  }

  if(!*list || (*list)->value < value){
    // the linked list is empty or the new value is greater than the current maximum
    // insertion at the head of the list

    list_value_t* new = (list_value_t*) malloc(sizeof(list_value_t));
    if(!new){
      fprintf(stderr, "Error in addValue(), malloc failure\n");
      return;
    }
    new->value  = value;
    new->next   = *list;
    new->points  = NULL;
    addPoint(&(new->points), ix, iy, ir);
    *list = new;
    return;
  }
  list_value_t* current = *list;
  list_value_t* prev;

  while(current && value < current->value){
    prev = current;
    current = current->next;
  }

  if(!current){ // end of the chain, we need to add a new value
    list_value_t* new = (list_value_t*) malloc(sizeof(list_value_t));
    if(!new){
      fprintf(stderr, "Error in addValue(), malloc failure\n");
      return;
    }
    new->value  = value;
    new->next   = NULL;
    new->points = NULL;
    addPoint(&(new->points), ix, iy, ir);
    prev->next = new;
    return;
  }

  if(current->value == value) {// the value already exists, we only need to add a new point
    addPoint( &(current->points), ix, iy, ir);
    return;
  }
  //the value does not exist yet, we need to add the value
  list_value_t* new = (list_value_t*) malloc(sizeof(list_value_t));
  if(!new){
    fprintf(stderr, "Error in addValue(), malloc failure\n");
    return;
  }
  new->value  = value;
  new->next   = prev->next;
  new->points  = NULL;
  addPoint(&(new->points), ix, iy, ir);
  prev->next = new;
  return;
}

void displayListValue(list_value_t* list){
  if(!list) return;
  printf("%d:  ",list->value);
  displayListPoint(list->points);
  printf("\n");
  displayListValue(list->next);
}

void displayListPoint(list_point_t* list){
  if(!list) return;
  printf("(%d, %d, %d)  ",list->ix, list->iy, list->ir);
  displayListPoint(list->next);
}

void freeListValue(list_value_t* list){
  if(!list) return;
  freeListValue(list->next);
  freeListPoint(list->points);
  free(list);
}

void freeListPoint(list_point_t* list){
  if(!list) return;
  freeListPoint(list->next);
  free(list);
}
