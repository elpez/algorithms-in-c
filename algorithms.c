/*  Welcome! This file contains C implementations of many of the algorithms presented in Anany
 *  Levitin's textbook "Introduction to the Design and Analysis of Algorithms." The file, like the
 *  textbook, organizes algorithms into seven design classes: brute-force, decrease-and-conquer,
 *  divide-and-conquer, dynamic programming, the greedy technique, and iterative improvement. The
 *  file is intended to be read sequentially, but I have tried to document my code comprehensively
 *  enough that you may read the implementation of any particular algorithm in isolation.
 *
 *  Each algorithm is preceded by a comment that (a) documents its usage as a C function, (b)
 *  sketches the idea of the algorithm in prose, and (c) analyzes the time and space complexity.
 *  Details of the algorithm's implementation are documented as inline comments in the code.
 *
 *  Basic knowledge of C is required to understand these algorithms. I have avoided hacks and
 *  optimizations whenever they would reduce the clarity of the code, and I have made some
 *  simplifications of implementation, for example only writing sorting algorithms for arrays of
 *  integers. For these two reasons, the functions here should not be taken as substitutes for
 *  canonical implementations.
 *
 *  The bulk of this file consists of the algorithms themselves. At the bottom are implementations
 *  of the utility functions defined in algorithms.h, and a test suite and main function.
 */

#include <stdio.h>
#include "algorithms.h"


/*****************************************************
 *   CHAPTER 3 - BRUTE FORCE and EXHAUSTIVE SEARCH   *
 *****************************************************/


/* Sort the elements of `array` in place.
 *
 *   Idea: Find the smallest number and swap it with the first element. Find the second smallest
 *   number and swap it with the second element, and so on until the list is sorted.
 *
 *   Time analysis: The outer loop runs n times, so n swaps are made. When i=0, the inner loop
 *   runs n-1 times, when i=1 n-2 times, and so on for a total of n-1 + n-2 + ... + 1 times,
 *   which equals n(n-1)/2. This is asymptotically equivalent to n^2, so O(n^2) comparisons are
 *   made. Therefore the overall time complexity is O(n^2).
 *
 *   Space analysis: No extra space is used, so O(1).
 */
void selection_sort(int array[], size_t n) {
    /* On each run of this loop, the smallest number in array[i...n] is found and swapped with
     * array[i].
     */
    for (size_t i = 0; i < n; i++) {
        int minimum = array[i];
        size_t minimum_pos = i;
        /* This loop finds the smallest number in array[i...n]. */
        for (size_t j = i+1; j < n; j++) {
            if (array[j] < minimum) {
                minimum = array[j];
                minimum_pos = j;
            }
        }
        swap(array, i, minimum_pos);
    }
}


/* Return the first position of `datum` in the array, or -1 if `datum` is not present.
 *
 *   Idea: Examine each element in turn.
 *
 *   Time analysis: In the worst case, the datum is not in the array and every element is examined,
 *   so O(n).
 *
 *   Space analysis: O(1).
 */
long long linear_search(int array[], size_t n, int datum) {
    for (size_t i = 0; i < n; i++) {
        if (array[i] == datum)
            return i;
    }
    return -1;
}


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/


void swap(int array[], size_t i, size_t j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


/***************************
 *   TEST SUITE and MAIN   *
 ***************************/


/* This is defined as a macro to preserve the line number. It assumes the existence of a variable
 * tests_failed, which it updates.
 */
#define ASSERT(cond) \
    if (!(cond)) { \
        printf("Failed test \"%s\" at line %d in %s\n", #cond, __LINE__, __FILE__); \
        tests_failed++; \
    }


/* Return 1 if the array is sorted in ascending order, 0 otherwise. */
int is_sorted(int* data, size_t n) {
    for (size_t i = 0; i < n-1; i++) {
        if (data[i] > data[i+1]) {
            return 0;
        }
    }
    return 1;
}


typedef void sorting_f(int*, size_t);

/* Run the sorting test suite against an arbitrary sorting function. */
int test_sorting_f(sorting_f f) {
    int data[] = {-8, 99, 7, 8, 9, -2, 0, 1, 4, 59, 42, 10};
    size_t n = 12;
    f(data, n);
    if (is_sorted(data, n)) {
        return 0;
    } else {
        return 1;
    }
}


void run_tests(void) {
    int tests_failed = 0;

    /* SELECTION SORT */
    ASSERT(test_sorting_f(selection_sort) == 0);

    /* LINEAR SEARCH */
    int data[] = {1, 2, 3, 4, 3};
    ASSERT(linear_search(data, 5, 3) == 2);
    ASSERT(linear_search(data, 5, 1) == 0);
    ASSERT(linear_search(data, 5, 7) == -1);

    if (tests_failed > 0) {
        printf("FAILED %d tests.\n", tests_failed);
    } else {
        printf("PASSED all tests.\n");
    }
}


int main(int argc, char* argv[]) {
    run_tests();
    return 0;
}
