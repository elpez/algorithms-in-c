#pragma once

#include <stddef.h>
#include <math.h>
#include "data_structures.h"


/*****************************************************
 *   CHAPTER 3 - BRUTE FORCE and EXHAUSTIVE SEARCH   *
 *****************************************************/

/* Sort the elements of `array` in ascending order. */
void selection_sort(int array[], size_t n);

/* Return the first position of `datum` in the array, or -1 if `datum` is not present. */
long long linear_search(int array[], size_t n, int datum);

/* Given the two lists of the same set of unique points, one in ascending order of the x-coordinate
 * and the other in ascending order of the y-coordinate, return the distance between the two closest
 * points.
 */
double closest_pair_brute_force(Point points[], size_t n);


/****************************************
 *   CHAPTER 4 - DECREASE and CONQUER   *
 ****************************************/

/* Sort the elements of `array` in ascending order. */
void insertion_sort(int array[], size_t n);

/* Return a position of `datum` in the sorted array, or -1 if `datum` is not present. */
long long binary_search(int array[], size_t n, int datum);


/* Traverse the graph depth-first and return an array indicating the order in which each vertex was
 * visited, starting at 1.
 */
int* depth_first_search(const Graph* g);


/**************************************
 *   CHAPTER 5 - DIVIDE and CONQUER   *
 **************************************/

/* Sort the elements of `array` in ascending order. */
void merge_sort(int array[], size_t n);
void merge(int left[], size_t left_len, int right[], size_t right_len, int target[]);

/* Sort the elements of `array` in ascending order. */
void quicksort(int array[], size_t n);
void quicksort_helper(int array[], size_t start, size_t end);
size_t partition(int array[], size_t start, size_t end);

/* Given the two lists of the same set of unique points, one in ascending order of the x-coordinate
 * and the other in ascending order of the y-coordinate, return the distance between the two closest
 * points.
 */
double closest_pair(Point sorted_by_x[], Point sorted_by_y[], size_t n);


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/


void swap(int array[], size_t i, size_t j);

int* copy_array(int source[], size_t start, size_t end);
int array_eq(size_t n, int array[], ...);
void print_array(int array[], size_t n);

#define distance_squared(p1, p2) (pow((p1).x - (p2).x, 2) + pow((p1).y - (p2).y, 2))


/* "Safe" memory allocators that will never return NULL pointers. */
void* safe_malloc(size_t);
void* safe_calloc(size_t, size_t);
void* safe_realloc(void*, size_t);
