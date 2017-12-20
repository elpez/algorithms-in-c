#include <stdlib.h>
#include "algorithms.h"


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


/* Return an ordering of a directed acyclic graph so that all edges point forwards along the
 * ordering. The return value is a malloc'd array `ranks` where `ranks[i]` is equal to the i'th
 * vertex's position in the sort. Multiple vertices may receive the same rank.
 *
 *   Idea: Identify a "source," a vertex with no incoming edges. Give this vertex a rank of 0 and
 *   remove all its outgoing edges from the graph. Find another source in the new graph, and
 *   continue.
 *
 *   Time complexity: O(|V| + |E|).
 *
 *   Space complexity: O(|V|) for the queue and in_degrees array.
 */
int* topological_sort(const Graph* g) {
    int* in_degrees = safe_calloc(g->n, sizeof *in_degrees);
    int* ranks = safe_calloc(g->n, sizeof *ranks);
    /* Calculate the in-degree of each vertex. */
    for (size_t i = 0; i < g->n; i++) {
        for (VertexList* p = g->vertices[i].neighbors; p != NULL; p = p->next) {
            in_degrees[p->v - g->vertices]++;
        }
    }
    VertexQueue* queue = queue_new(g->n);
    /* Add sources (vertices with no incoming edges) to the queue. */
    for (size_t i = 0; i < g->n; i++) {
        if (in_degrees[i] == 0) {
            queue_push(queue, g->vertices + i);
        }
    }
    while (!queue_empty(queue)) {
        Vertex* source = queue_pop(queue);
        size_t source_index = (source - g->vertices);
        for (VertexList* p = source->neighbors; p != NULL; p = p->next) {
            size_t index = (p->v - g->vertices);
            /* Decrease in-degree since v is being removed from consideration. */
            in_degrees[index]--;
            ranks[index] = fmax(ranks[index], 1 + ranks[source_index]);
            if (in_degrees[index] == 0) {
                queue_push(queue, p->v);
            }
        }
    }
    queue_free(queue);
    free(in_degrees);
    return ranks;
}


int ch04_tests() {
    puts("\n=== CHAPTER 4 TESTS ===");
    int tests_failed = 0;

    /* INSERTION SORT */
    puts("Testing insertion sort");
    ASSERT(test_sorting_f(insertion_sort) == 0);

    /* BINARY SEARCH */
    puts("Testing binary search");
    int bs_data[] = {-7, 4, 8, 9, 17};
    ASSERT(binary_search(bs_data, 5, -7) == 0);
    ASSERT(binary_search(bs_data, 5, 4) == 1);
    ASSERT(binary_search(bs_data, 5, 8) == 2);
    ASSERT(binary_search(bs_data, 5, 9) == 3);
    ASSERT(binary_search(bs_data, 5, 17) == 4);
    ASSERT(binary_search(bs_data, 5, 42) == -1);

    /* TOPOLOGICAL SORTING */
    puts("Testing topological sorting");
    /* The graph from exercise 1a in section 4.2, page 142. */
    Graph* g = graph_from_string(DIRECTED, "ABCDEFG", "AC AB BG BE CF DG DF DC DB DA GF GE");
    int* ranks = topological_sort(g);
    /* Expected order: D, A, {B, C}, G, {E, F} */
    ASSERT(array_eq(7, ranks, 1, 2, 2, 0, 4, 4, 3));
    free(ranks);
    graph_free(g);

    return tests_failed;
}
