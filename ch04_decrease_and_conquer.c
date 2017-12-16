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
