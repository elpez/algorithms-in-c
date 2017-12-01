#ifndef ALGORITHMS_H
#define ALGORITHMS_H


/******************
 *   DATA TYPES   *
 ******************/


typedef struct VertexList_rec {
    /* The index of the vertex in the graph's vertices array. */
    size_t index;
    struct VertexList_rec* next;
} VertexList;


typedef struct {
    char val;
    VertexList* neighbors;
} Vertex;


typedef struct {
    size_t n;
    Vertex* vertices;
} Graph;


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


/*****************************************************
 *   CHAPTER 3 - BRUTE FORCE and EXHAUSTIVE SEARCH   *
 *****************************************************/

void selection_sort(int array[], size_t n);

long long linear_search(int array[], size_t n, int datum);


/****************************************
 *   CHAPTER 4 - DECREASE and CONQUER   *
 ****************************************/


void insertion_sort(int array[], size_t n);

long long binary_search(int array[], size_t n, int datum);

void depth_first_search_one_vertex(const Graph* g, size_t index, int counts[], int* max_count);
int* depth_first_search(const Graph* g);


/**************************************
 *   CHAPTER 5 - DIVIDE and CONQUER   *
 **************************************/


void merge_sort(int array[], size_t n);
void merge(int left[], size_t left_len, int right[], size_t right_len, int target[]);

void quicksort(int array[], size_t n);
void quicksort_helper(int array[], size_t start, size_t end);
size_t partition(int array[], size_t start, size_t end);


/*************************
 *   UTILITY FUNCTIONS   *
 *************************/


void swap(int array[], size_t i, size_t j);

int* copy_array(int source[], size_t start, size_t end);
int array_eq(size_t n, int array[], ...);
void print_array(int array[], size_t n);

#endif
