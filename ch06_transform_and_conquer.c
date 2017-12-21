#include <stdbool.h>
#include "algorithms.h"


#define LEFT_CHILD(x) (2*(x)+1)
#define RIGHT_CHILD(x) (2*(x)+2)
#define PARENT(x) (((x)-1) / 2)


/* Sort the elements of `array` in ascending order.
 *
 *   Idea: Convert the array to a max heap and then successively delete the maximum element from the
 *   heap and put it at the end.
 *
 *   Time analysis: Heapification is O(n) (although the analysis below showing it to be O(n log n)
 *   does not change the final answer), so the running time is dominated by the n calls to the
 *   O(log n) heap_delete function, making it O(n log n) overall.
 *
 *   Space analysis: O(1).
 */
void heapsort(int array[], size_t n) {
    heapify(array, n);
    while (n > 0) {
        heap_delete(array, n--);
    }
}


/* Convert `array` to a heap, so that for every index i, array[i] >= array[2*i+1] and array[i] >=
 * array[2*i+2].
 *
 *   Idea: Enforce the heap invariant (using fix_heap) for each parent in the heap, starting with
 *   the last parent.
 *
 *   Time analysis: The O(log n) function fix_heap is called O(n) times, so heapify is no worse than
 *   O(n log n), which is enough to show that heapsort is O(n log n). A more detailed analysis of
 *   heapify would show that it is in fact O(n).
 *
 *   Space analysis: O(1).
 */
void heapify(int array[], size_t n) {
    /* Iterate over each parent in the heap. */
    for (int i = PARENT(n-1); i >= 0; i--) {
        fix_heap(i, array, n);
    }
}


/* Swap the maximum element of the heap to the end and fix the heap to maintain the invariant.
 *
 *   Time analysis: O(log n), same as fix_heap.
 *
 *   Space analysis: O(1), same as fix_heap.
 */
void heap_delete(int heap[], size_t n) {
    swap(heap, 0, n-1);
    fix_heap(0, heap, n-1);
}


/* Fix the sub-heap whose root is `index` so that it satisfies the heap invariant.
 *
 *   Idea: Keep swapping the element originally at index until it is larger than both its children.
 *
 *   Time analysis: In each iteration of the loop, the index goes down one level in the heap, so
 *   the loop can run no more times than the height of the heap, which is within a constant of
 *   log n, so the algorithm is O(log n).
 *
 *   Space analysis: O(1).
 */
void fix_heap(size_t index, int heap[], size_t n) {
    int v = heap[index];
    while (LEFT_CHILD(index) < n) {
        size_t j = LEFT_CHILD(index);
        if (j < n-1) {
            if (heap[j] < heap[j+1]) {
                j++;
            }
        }
        if (v >= heap[j]) {
            break;
        } else {
            heap[index] = heap[j];
            index = j;
        }
    }
    heap[index] = v;
}


int ch06_tests() {
    puts("\n=== CHAPTER 6 TESTS ===");
    int tests_failed = 0;

    /* HEAPSORT */
    puts("Testing heapsort");
    ASSERT(test_sorting_f(heapsort) == 0);

    return tests_failed;
}
