#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>
/* Data structures*/



typedef struct Point{
	//linked list used in function findmax() in order to easily find the n first local maxima
	int itheta;
	int irho;
	struct Point* next;
}	list_point_t;


typedef struct Value{
	int value;
	struct Value* next;
	list_point_t* points;
} list_value_t;

void addPoint(list_point_t** list, int itheta, int irho);
void addValue(list_value_t** list, int value, int itheta, int irho);
void displayListValue(list_value_t* list);
void displayListPoint(list_point_t* list);
void freeListValue(list_value_t* list);
void freeListPoint(list_point_t* list);
#endif
