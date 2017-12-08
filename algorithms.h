#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <math.h>
#include "data.h"


/*****************************************************
 *   CHAPTER 3 - BRUTE FORCE and EXHAUSTIVE SEARCH   *
 *****************************************************/

void selection_sort(int array[], size_t n);

long long linear_search(int array[], size_t n, int datum);

double closest_pair_brute_force(Point points[], size_t n);


/****************************************
 *   CHAPTER 4 - DECREASE and CONQUER   *
 ****************************************/


void insertion_sort(int array[], size_t n);

long long binary_search(int array[], size_t n, int datum);

int* depth_first_search(const Graph* g);


/**************************************
 *   CHAPTER 5 - DIVIDE and CONQUER   *
 **************************************/


void merge_sort(int array[], size_t n);
void merge(int left[], size_t left_len, int right[], size_t right_len, int target[]);

void quicksort(int array[], size_t n);
void quicksort_helper(int array[], size_t start, size_t end);
size_t partition(int array[], size_t start, size_t end);

double closest_pair(Point sorted_by_x[], Point sorted_by_y[], size_t n);


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/


void swap(int array[], size_t i, size_t j);

int* copy_array(int source[], size_t start, size_t end);
int array_eq(size_t n, int array[], ...);
void print_array(int array[], size_t n);

#define distance_squared(p1, p2) (pow((p1).x - (p2).x, 2) + pow((p1).y - (p2).y, 2))

#endif
