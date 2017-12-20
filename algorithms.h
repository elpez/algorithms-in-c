#pragma once

#include <stdio.h>
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


/* Traverse the graph depth-first and return a heap-allocated array indicating the order in which
 * each vertex was visited, starting at 1.
 */
int* depth_first_search(const Graph* g);

/* Traverse the graph breadth-first and return a heap-allocated array indicating the order in which
 * each vertex was visited, starting at 1.
 */
int* breadth_first_search(const Graph* g);


/****************************************
 *   CHAPTER 4 - DECREASE and CONQUER   *
 ****************************************/

/* Sort the elements of `array` in ascending order. */
void insertion_sort(int array[], size_t n);

/* Return a position of `datum` in the sorted array, or -1 if `datum` is not present. */
long long binary_search(int array[], size_t n, int datum);


/* Return an ordering of a directed acyclic graph so that all edges point forwards along the
 * ordering. The return value is a malloc'd array `ranks` where `ranks[i]` is equal to the i'th
 * vertex's position in the sort. Multiple vertices may receive the same rank.
 */
int* topological_sort(const Graph* g);


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


/*****************************************
 *   CHAPTER 6 - TRANSFORM and CONQUER   *
 *****************************************/

/* Sort the elements of `array` in ascending order. */
void heapsort(int array[], size_t n);
void heapify(int array[], size_t n);
void heap_delete(int heap[], size_t n);
void fix_heap(size_t index, int heap[], size_t n);


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/

void swap(int array[], size_t i, size_t j);

int* copy_array(int source[], size_t start, size_t end);

/* Return 1 if the array of size `n` is equal to the `n` variadic arguments. */
int array_eq(size_t n, int array[], ...);

/* Print the array to stdout, followed by a line break. */
void print_array(int array[], size_t n);

/* Return 1 if the array is sorted in ascending order, 0 otherwise. */
int is_sorted(int* data, size_t n);

#define distance_squared(p1, p2) (pow((p1).x - (p2).x, 2) + pow((p1).y - (p2).y, 2))

/* "Safe" memory allocators that will never return NULL pointers. */
void* safe_malloc(size_t);
void* safe_calloc(size_t, size_t);
void* safe_realloc(void*, size_t);

/* Run the sorting test suite against an arbitrary sorting function. */
typedef void sorting_f(int*, size_t);
int test_sorting_f(sorting_f f);

/* This is defined as a macro to preserve the line number. It assumes the existence of a variable
 * tests_failed, which it updates.
 */
#define ASSERT(cond) \
    if (!(cond)) { \
        printf("*  Failed test \"%s\" at line %d in %s\n", #cond, __LINE__, __FILE__); \
        tests_failed++; \
    }



/******************
 *   TEST SUITE   *
 ******************/

int ch03_tests(void);
int ch04_tests(void);
int ch05_tests(void);
int ch06_tests(void);
