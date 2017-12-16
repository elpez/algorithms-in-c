#pragma once

#include <stddef.h>
#include <math.h>


/***********************
 *   DATA STRUCTURES   *
 ***********************/


struct Vertex;
typedef struct VertexList_rec {
    struct Vertex* v;
    struct VertexList_rec* next;
} VertexList;


typedef struct Vertex {
    char val;
    VertexList* neighbors;
} Vertex;


typedef struct {
    size_t n;
    Vertex* vertices;
} Graph;


typedef struct {
    double x, y;
} Point;


/*****************************************************
 *   CHAPTER 3 - BRUTE FORCE and EXHAUSTIVE SEARCH   *
 *****************************************************/

void selection_sort(int array[], size_t n);

long long linear_search(int array[], size_t n, int datum);

double closest_pair_brute_force(Point points[], size_t n);


/****************************************
 *   CHAPTER 4 - DECREASE and CONQUER   *
 ****************************************/


void insertion_sort(int array[], size_t n);

long long binary_search(int array[], size_t n, int datum);

int* depth_first_search(const Graph* g);


/**************************************
 *   CHAPTER 5 - DIVIDE and CONQUER   *
 **************************************/


void merge_sort(int array[], size_t n);
void merge(int left[], size_t left_len, int right[], size_t right_len, int target[]);

void quicksort(int array[], size_t n);
void quicksort_helper(int array[], size_t start, size_t end);
size_t partition(int array[], size_t start, size_t end);

double closest_pair(Point sorted_by_x[], Point sorted_by_y[], size_t n);


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/


void swap(int array[], size_t i, size_t j);

int* copy_array(int source[], size_t start, size_t end);
int array_eq(size_t n, int array[], ...);
void print_array(int array[], size_t n);

#define distance_squared(p1, p2) (pow((p1).x - (p2).x, 2) + pow((p1).y - (p2).y, 2))


/* Construct a graph from a string of single-letter vertex names and a string of space-separated
 * edges, e.g. "AB BC".
 *
 * The first argument should be either DIRECTED or UNDIRECTED depending on how you want the edges
 * string to be interpreted.
 *
 * All graphs allocated with this function must be passed to graph_free when they are no longer
 * needed, to prevent memory leaks.
 */
enum GraphType { DIRECTED, UNDIRECTED };
Graph* graph_from_string(enum GraphType, const char* vertices, const char* edges);

/* Add a directed edge to the graph. */
void graph_add_edge(Graph* g, char from, char to);

/* Free all memory associated with a graph, including all of its vertices. */
void graph_free(Graph*);

/* Free the vertex list, but not the vertices themselves. */
void vertex_list_free(VertexList* p);

/* Print the vertices and edges of the graph as strings. */
void print_graph(const Graph*);


/* "Safe" memory allocators that will never return NULL pointers. */
void* safe_malloc(size_t);
void* safe_calloc(size_t, size_t);
void* safe_realloc(void*, size_t);
