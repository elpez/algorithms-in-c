#include <stdlib.h>
#include "algorithms.h"


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
    quicksort_helper(array, 0, n-1);
}

void quicksort_helper(int array[], size_t start, size_t end) {
    if (start < end) {
        size_t s = partition(array, start, end);
        quicksort_helper(array, start, s);
        quicksort_helper(array, s+1, end);
    }
}

size_t partition(int array[], size_t start, size_t end) {
    /* Note: this partition algorithm is closely based on the one in the Wikipedia article for
     * quicksort.
     */
    int pivot = array[start];
    size_t i = start - 1;
    size_t j = end + 1;
    while (1) {
        /* Set i to be the first element in the array greater than the pivot. */
        do {
            i++;
        } while (array[i] < pivot && i < end);
        /* Set j to be the last element in the array less than the pivot. */
        do {
            j--;
        } while (array[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(array, i, j);
    }
}


/* Given the two lists of the same set of unique points, one in ascending order of the x-coordinate
 * and the other in ascending order of the y-coordinate, return the distance between the two closest
 * points.
 *
 *   Idea: Draw a vertical line through the median of the x-coordinates of the point, so that
 *   half the points lie to the left of it and half the points lie to the right of it. Recursively
 *   find the closest pairs in each half. The minimum of the two closest pairs, d, is not
 *   necessarily the answer, though, because there could be a closer pair that spans the median.
 *   Determine if any such pairs exist, and return their distance if found, otherwise d.
 *
 *   Time analysis: The recurrence relation is clearly T(n) = 2T(n/2) + f(n), since the algorithm
 *   divides the problem in half and recurses on each half. The question then becomes, what is
 *   the complexity of the dividing and combining steps? Dividing is clearly linear since the entire
 *   array needs to be copied into two halves. Combining looks like it's quadratic, because it has
 *   a nested loop. However, the geometry of the problem guarantees that the inner loop body will
 *   run no more than 5 times, so combining is also linear. Thus, by the master method the overall
 *   complexity is O(n log n), which is a significant improvement over the brute force method.
 *
 *   Space analysis: O(n), to make the copies of the arrays needed for the recursive calls.
 */
double closest_pair(Point sorted_by_x[], Point sorted_by_y[], size_t n) {
    if (n > 3) {
        size_t right_n = n / 2;
        size_t left_n = n - right_n;
        Point* right_sorted_x = safe_malloc(right_n * sizeof *right_sorted_x);
        Point* right_sorted_y = safe_malloc(right_n * sizeof *right_sorted_y);
        for (size_t i = 0; i < right_n; i++) {
            right_sorted_x[i] = sorted_by_x[left_n + i];
            right_sorted_y[i] = sorted_by_y[left_n + i];
        }
        Point* left_sorted_x = safe_malloc(left_n * sizeof *left_sorted_x);
        Point* left_sorted_y = safe_malloc(left_n * sizeof *left_sorted_y);
        for (size_t i = 0; i < left_n; i++) {
            left_sorted_x[i] = sorted_by_x[i];
            left_sorted_y[i] = sorted_by_y[i];
        }
        /* Recursively compute the closest pairs from the left and the right points. */
        double d_left = closest_pair(left_sorted_x, left_sorted_y, left_n);
        double d_right = closest_pair(right_sorted_x, right_sorted_y, right_n);
        double d = fmin(d_left, d_right);
        double m = sorted_by_x[left_n - 1].x;
        Point* points_near_median = safe_malloc(n * sizeof *points_near_median);
        size_t num_near_median = 0;
        for (size_t i = 0; i < n; i++) {
            Point p = sorted_by_y[i];
            if (abs(p.x - m) < d) {
                points_near_median[num_near_median++] = p;
            }
        }
        double d_sq = d*d;
        /* Find any pairs of points between the two halves that are closer than the closest pairs
         * in either half alone. This looks like a quadratic loop, but it's really not!
         */
        for (size_t i = 0; i < num_near_median - 2; i++) {
            size_t k = i + 1;
            double tmp = pow(points_near_median[k].y - points_near_median[i].y, 2);
            while (k <= num_near_median - 1 && tmp < d_sq) {
                d_sq = fmin(tmp + pow(points_near_median[k].x - points_near_median[i].x, 2), d_sq);
                k++;
            }
        }
        free(right_sorted_x);
        free(right_sorted_y);
        free(left_sorted_x);
        free(left_sorted_y);
        free(points_near_median);
        return sqrt(d_sq);
    } else {
        return closest_pair_brute_force(sorted_by_x, n);
    }
}
