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


/* Traverse the graph depth-first and return a heap-allocated array indicating the order in which
 * each vertex was visited, starting at 1, so if A[7] = 2 then the eighth vertex (g->vertices[7])
 * was the second vertex visited.
 *
 *  Idea: Mark each vertex of the graph with 0. Visit the first vertex, mark it with 1, then visit
 *  that vertex's first (unmarked) neighbor, mark it with 2, and continue until you reach a dead
 *  end. Backtrack to a vertex with unmarked neighbors and continue from there.
 *
 *  Time analysis: Every vertex must be visited, and each edge of every vertex must be considered,
 *  so the time complexity is O(|E| + |V|).
 *
 *  Space analysis: O(|V|) for the counts array and vertex stack.
 */
int* depth_first_search(const Graph* g) {
    #define STACK_POP() (stack[--end_of_stack])
    #define STACK_PUSH(val) stack[end_of_stack++] = (val)
    if (g == NULL) return NULL;
    size_t end_of_stack = 0;
    Vertex** stack = safe_malloc(g->n * sizeof *stack);
    int* counts = safe_calloc(g->n, sizeof *counts);
    int max_count = 0;
    /* Start at each vertex (this ensures that every component is visited). */
    for (size_t i = 0; i < g->n; i++) {
        if (counts[i] > 0)
            continue;
        STACK_PUSH(g->vertices + i);
        while (end_of_stack > 0) {
            Vertex* this_vertex = STACK_POP();
            size_t this_index = this_vertex - g->vertices;
            if (counts[this_index] == 0) {
                counts[this_index] = ++max_count;
                VertexList* p = this_vertex->neighbors;
                /* Push all adjacents vertices onto the stack. */
                while (p != NULL) {
                    STACK_PUSH(p->v);
                    p = p->next;
                }
            }
        }
    }
    free(stack);
    return counts;
}


/* Traverse the graph breadth-first and return a heap-allocated array indicating the order in which
 * each vertex was visited, starting at 1, so if A[7] = 2 then the eighth vertex (g->vertices[7])
 * was the second vertex visited.
 *
 *  Idea: Same idea as depth-first search, except use a queue instead of a stack so that every
 *  neighbor of a vertex is visited before any other vertex is.
 *
 *  Time analysis: Every vertex must be visited, and each edge of every vertex must be considered,
 *  so the time complexity is O(|E| + |V|).
 *
 *  Space analysis: O(|V|) for the counts array and vertex queue.
 */
int* breadth_first_search(const Graph* g) {
    #define QUEUE_PUT(x) queue[tail++ % g->n] = (x)
    #define QUEUE_POP() (queue[head++ % g->n])
    Vertex** queue = safe_malloc(g->n * sizeof *queue);
    size_t head = 0, tail = 0;
    int* counts = safe_calloc(g->n, sizeof *counts);
    int max_count = 0;
    /* Start at each vertex (this ensures that every component is visited). */
    for (size_t i = 0; i < g->n; i++) {
        if (counts[i] > 0)
            continue;
        QUEUE_PUT(g->vertices + i);
        while (head != tail) {
            Vertex* this_vertex = QUEUE_POP();
            size_t this_index = this_vertex - g->vertices;
            if (counts[this_index] == 0) {
                counts[this_index] = ++max_count;
                VertexList* p = this_vertex->neighbors;
                /* Push all adjacents vertices onto the stack. */
                while (p != NULL) {
                    QUEUE_PUT(p->v);
                    p = p->next;
                }
            }
        }
    }
    free(queue);
    return counts;
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

    /* DEPTH-FIRST SEARCH */
    puts("Testing depth-first search");
    Graph* g = graph_from_string(DIRECTED, "ABCDEFG", "AB AC BG BE CF DA DB DC DF DG GF");
    int* counts = depth_first_search(g);
    /* Expected order: A, B, G, F, E, C, D */
    ASSERT(array_eq(7, counts, 1, 2, 6, 7, 5, 4, 3));
    free(counts);

    /* BREADTH-FIRST SEARCH */
    puts("Testing breadth-first search");
    counts = breadth_first_search(g);
    /* Expected order: A, C, B, F, E, G, D */
    ASSERT(array_eq(7, counts, 1, 3, 2, 7, 5, 4, 6));
    free(counts);
    graph_free(g);

    return tests_failed;
}
