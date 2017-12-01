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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"


/*****************************************************
 *   CHAPTER 3 - BRUTE FORCE and EXHAUSTIVE SEARCH   *
 *****************************************************/


/* Sort the elements of `array` in ascending order.
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


/****************************************
 *   CHAPTER 4 - DECREASE and CONQUER   *
 ****************************************/


/* Sort the elements of `array` in ascending order.
 *
 *   Idea: Recursively sort the first n-1 elements of the array, and then insert the last element
 *   into its proper position in the sorted array.
 *
 *   Time analysis: In the worst case (when the array is already sorted in descending order), the
 *   inner loop runs 1 + 2 + 3 + ... + n-1 times, so as with selection sort the time complexity is
 *   O(n^2).
 *
 *   Space analysis: O(1).
 */
void insertion_sort(int array[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        int v = array[i];
        size_t j = i-1;
        while (j >= 0 && array[j] > v) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = v;
    }
}


/* Return a position of `datum` in the sorted array, or -1 if `datum` is not present.
 *
 *   Idea: Consider the middle element. If the datum is smaller, then recursively consider the left
 *   half of the array. If the datum is larger, consider the right half.
 *
 *   Time analysis: Each iteration of the loop reduces the size of the array to be considered by
 *   half, so in the worst case the loop runs for the number of times that n can be divided by two.
 *   This number is within a constant of log n, so the time complexity is O(log n).
 *
 *   Space analysis: O(1).
 */
long long binary_search(int array[], size_t n, int datum) {
    size_t start = 0, end = n;
    while (start < end) {
        size_t mid = (end + start) / 2;
        int midval = array[mid];
        if (midval == datum) {
            return mid;
        } else if (midval < datum) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return -1;
}


/* Traverse the graph depth-first and return an array indicating the order in which each vertex was
 * visited, starting at 1, so if A[7] = 2 then the eighth vertex (g->vertices[7]) was the second
 * vertex visited. The array is allocated with malloc and should be deallocated with free.
 *
 *  Idea: Mark each vertex of the graph with 0. Visit the first vertex, mark it with 1, then visit
 *  that vertex's first (unmarked) neighbor, mark it with 2, and continue until you reach a dead
 *  end. Backtrack to a vertex with unmarked neighbors and continue from there.
 *
 *  Time analysis: Every vertex must be visited, and each edge of every vertex must be considered,
 *  so the time complexity is O(|E| + |V|).
 *
 *  Space analysis: O(|V|) for the counts array.
 */
void depth_first_search_one_vertex(const Graph* g, size_t index, int counts[], int* max_count) {
    *max_count += 1;
    counts[index] = *max_count;
    VertexList* p = g->vertices[index].neighbors;
    while (p != NULL) {
        /* Only go to unvisited vertices. */
        if (counts[p->index] == 0) {
            depth_first_search_one_vertex(g, p->index, counts, max_count);
        }
        p = p->next;
    }
}

int* depth_first_search(const Graph* g) {
    if (g == NULL) return NULL;
    int* counts = calloc(g->n, sizeof *counts);
    int max_count = 0;
    if (counts == NULL) return NULL;
    /* Visit each component of the graph. */
    for (size_t i = 0; i < g->n; i++) {
        if (counts[i] == 0) {
            depth_first_search_one_vertex(g, i, counts, &max_count);
        }
    }
    return counts;
}


/**************************************
 *   CHAPTER 5 - DIVIDE and CONQUER   *
 **************************************/


/* Sort the elements of `array` in ascending order.
 *
 *   Idea: Recursively sort each half of the array, and then merge the two sorted halves them.
 *
 *   Time analysis: The recurrence relation for this algorithm is T(n) = 2*T(n/2) + O(n), since
 *   merging is linear. The time complexity is thus O(n log n) by the master method.
 *
 *   Space analysis: A copy of the array must be made prior to merging, which takes O(n) space.
 */
void merge_sort(int array[], size_t n) {
    if (n >= 2) {
        int* left = copy_array(array, 0, n/2);
        int* right = copy_array(array, n/2, n);
        merge_sort(left, n/2);
        merge_sort(right, n-n/2);
        merge(left, n/2, right, n-n/2, array);
        free(left);
        free(right);
    }
}


/* Merge the sorted arrays `left` and `right`, into `target`, which must be at least as long as
 * `left` and `right` combined.
 */
void merge(int left[], size_t left_len, int right[], size_t right_len, int target[]) {
    size_t left_index = 0, right_index = 0;
    while (left_index < left_len && right_index < right_len) {
        /* Take the smaller element from the fronts of the two arrays. */
        if (left[left_index] <= right[right_index]) {
            target[left_index+right_index] = left[left_index];
            left_index++;
        } else {
            target[left_index+right_index] = right[right_index];
            right_index++;
        }
    }
    /* Take any remaining elements from the two arrays (since one array might be one element longer
     * than the other).
     */
    while (left_index < left_len) {
        target[left_index+right_index] = left[left_index];
        left_index++;
    }
    while (right_index < right_len) {
        target[left_index+right_index] = right[right_index];
        right_index++;
    }
}


/* Sort the elements of `array` in ascending order.
 *
 *   Idea: Pick an arbitrary element, called the pivot. Put all smaller elements before the pivot
 *   in the array, and all larger elements after it. Recursively sort the two partitions of the
 *   array made by the pivot.
 *
 *   Time analysis: In the worst case, partitioning always reduce the array's size by 1, so n
 *   partitions, each of which take O(n) time, are needed, so the algorithm is O(n^2). In the
 *   average case, each partition divides the array roughly in half, and so log n partitions are
 *   performed, giving a complexity of O(n log n).
 *
 *   Space analysis: In this implementation, the worst case is O(n) since there may be as many as
 *   n recursive calls to quicksort_helper. More complicated implementations can get O(log n) space
 *   according to Wikipedia.
 */
void quicksort(int array[], size_t n) {
    quicksort_helper(array, 0, n);
}

void quicksort_helper(int array[], size_t start, size_t end) {
    if (start < end - 1) {
        size_t s = partition(array, start, end);
        quicksort_helper(array, start, s);
        quicksort_helper(array, s, end);
    }
}

size_t partition(int array[], size_t start, size_t end) {
    int pivot = array[start];
    size_t i = start + 1;
    size_t j = end - 1;
    do {
        /* Set i to be the first element in the array greater than the pivot. */
        while (array[i] < pivot && i < end-1) {
            i++;
        }
        /* Set j to be the last element in the array less than the pivot. */
        while (array[j] > pivot) {
            j--;
        }
        swap(array, i, j);
    } while (i < j);
    swap(array, i, j);
    swap(array, start, j);
    return (j == start) ? j+1 : j;
}


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/


/* Add a directed edge to the graph. */
void graph_add_edge(Graph* g, char from, char to) {
    /* Find the vertices in the graph's vertex list. */
    Vertex* from_vertex = NULL;
    long long to_index = -1;
    for (size_t i = 0; i < g->n; i++) {
        if (g->vertices[i].val == from) {
            from_vertex = &g->vertices[i];
        }
        if (g->vertices[i].val == to) {
            to_index = i;
        }
    }
    if (from_vertex == NULL || to_index == -1) return;
    /* Make sure the edge doesn't actually exist. */
    VertexList* ptr = from_vertex->neighbors;
    while (ptr != NULL) {
        if (ptr->index == to_index) {
            return;
        }
        ptr = ptr->next;
    }
    /* Construct the new entry in the vertex's edge list. */
    VertexList* new_ptr = malloc(sizeof *new_ptr);
    if (new_ptr) {
        new_ptr->index = to_index;
        new_ptr->next = from_vertex->neighbors;
        from_vertex->neighbors = new_ptr;
    }
}


Graph* graph_from_string(enum GraphType typ, const char* vertices, const char* edges) {
    Graph* ret = malloc(sizeof *ret);
    if (ret) {
        ret->n = strlen(vertices);
        ret->vertices = malloc(ret->n * sizeof *ret->vertices);
        if (ret->vertices) {
            /* Add the vertices. */
            for (size_t i = 0; i < ret->n; i++) {
                ret->vertices[i].val = vertices[i];
                ret->vertices[i].neighbors = NULL;
            }
            /* Add the edges. */
            size_t i = 0;
            size_t n = strlen(edges);
            while (i < n) {
                graph_add_edge(ret, edges[i], edges[i+1]);
                if (typ == UNDIRECTED) {
                    graph_add_edge(ret, edges[i+1], edges[i]);
                }
                i += 3;
            }
        }
    }
    return ret;
}


void vertex_list_free(VertexList* p) {
    if (p == NULL) return;
    vertex_list_free(p->next);
    free(p);
}


void graph_free(Graph* g) {
    if (g == NULL) return;
    for (size_t i = 0; i < g->n; i++) {
        vertex_list_free(g->vertices[i].neighbors);
    }
    free(g->vertices);
    free(g);
}


void print_graph(const Graph* g) {
    if (g == NULL) return;

    printf("NODES: ");
    for (size_t i = 0; i < g->n; i++) {
        printf("%c", g->vertices[i].val);
        if (i != g->n - 1) {
            printf(", ");
        } else {
            printf("\n");
        }
    }

    printf("EDGES: ");
    for (size_t i = 0; i < g->n; i++) {
        char c = g->vertices[i].val;
        VertexList* p = g->vertices[i].neighbors;
        while (p != NULL) {
            printf("%c%c ", c, g->vertices[p->index].val);
            p = p->next;
        }
    }
    printf("\n");
}


void swap(int array[], size_t i, size_t j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


int* copy_array(int source[], size_t start, size_t end) {
    size_t n = end - start;
    int* ret = malloc(n * sizeof *ret);
    if (ret) {
        for (size_t i = 0; i < n; i++) {
            ret[i] = source[start+i];
        }
    }
    return ret;
}


void print_array(int array[], size_t n) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
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
    int ls_data[] = {1, 2, 3, 4, 3};
    ASSERT(linear_search(ls_data, 5, 3) == 2);
    ASSERT(linear_search(ls_data, 5, 1) == 0);
    ASSERT(linear_search(ls_data, 5, 7) == -1);

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
    /* Expected order: A, C, F, B, E, G, D */
    ASSERT(array_eq(7, counts, 1, 4, 2, 7, 5, 3, 6));
    free(counts);
    graph_free(g);

    /* MERGE SORT */
    ASSERT(test_sorting_f(merge_sort) == 0);

    /* QUICKSORT */
    ASSERT(test_sorting_f(quicksort) == 0);

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
