#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"


/* This is defined as a macro to preserve the line number. It assumes the existence of a variable
 * tests_failed, which it updates.
 */
#define ASSERT(cond) \
    if (!(cond)) { \
        printf("Failed test \"%s\" at line %d in %s\n", #cond, __LINE__, __FILE__); \
        tests_failed++; \
    }


/* Return 1 if the array is sorted in ascending order, 0 otherwise. */
int is_sorted(int* data, size_t n);


/* Return 1 if the array of size `n` is equal to the `n` variadic arguments. */
int array_eq(size_t n, int array[], ...);


/* Run the sorting test suite against an arbitrary sorting function. */
typedef void sorting_f(int*, size_t);
int test_sorting_f(sorting_f f);


void run_tests(void) {
    int tests_failed = 0;

    /* SELECTION SORT */
    ASSERT(test_sorting_f(selection_sort) == 0);

    /* LINEAR SEARCH */
    int ls_data[] = {1, 2, 3, 4, 3};
    ASSERT(linear_search(ls_data, 5, 3) == 2);
    ASSERT(linear_search(ls_data, 5, 1) == 0);
    ASSERT(linear_search(ls_data, 5, 7) == -1);

    /* BRUTE-FORCE CLOSEST PAIR */
    Point points[] = { {7, 3}, {7, 1}, {2, 3}, {3, 1} };
    ASSERT(closest_pair_brute_force(points, 4) == 2);

    /* INSERTION SORT */
    ASSERT(test_sorting_f(insertion_sort) == 0);

    /* BINARY SEARCH */
    int bs_data[] = {-7, 4, 8, 9, 17};
    ASSERT(binary_search(bs_data, 5, -7) == 0);
    ASSERT(binary_search(bs_data, 5, 4) == 1);
    ASSERT(binary_search(bs_data, 5, 8) == 2);
    ASSERT(binary_search(bs_data, 5, 9) == 3);
    ASSERT(binary_search(bs_data, 5, 17) == 4);
    ASSERT(binary_search(bs_data, 5, 42) == -1);

    /* DEPTH-FIRST SEARCH */
    Graph* g = graph_from_string(DIRECTED, "ABCDEFG", "AB AC BG BE CF DA DB DC DF DG GF");
    int* counts = depth_first_search(g);
    /* Expected order: A, B, G, F, E, C, D */
    ASSERT(array_eq(7, counts, 1, 2, 6, 7, 5, 4, 3));
    free(counts);
    graph_free(g);

    /* MERGE SORT */
    ASSERT(test_sorting_f(merge_sort) == 0);

    /* QUICKSORT */
    ASSERT(test_sorting_f(quicksort) == 0);

    /* CLOSEST PAIR */
    Point points_by_x[] = { {2, 3}, {3, 1}, {7, 3}, {7, 1} };
    Point points_by_y[] = { {3, 1}, {7, 1}, {2, 3}, {7, 3} };
    ASSERT(closest_pair(points_by_x, points_by_y, 4) == 2);

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


int is_sorted(int* data, size_t n) {
    for (size_t i = 0; i < n-1; i++) {
        if (data[i] > data[i+1]) {
            return 0;
        }
    }
    return 1;
}


int array_eq(size_t n, int array[], ...) {
    va_list args;
    va_start(args, array);
    for (size_t i = 0; i < n; i++) {
        int x = va_arg(args, int);
        if (array[i] != x) {
            return 0;
        }
    }
    return 1;
}


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
