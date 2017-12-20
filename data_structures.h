#pragma once

#include <stdbool.h>


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
    size_t n;
    char* vals;
    /* An array of length n^2 where each true entry (i, j) indicates an edge between i and j. */
    bool* edges;
} GraphMatrix;


typedef struct {
    double x, y;
} Point;


/* Used for depth-first searching a graph. */
typedef struct {
    size_t len, capacity;
    Vertex** data;
} VertexStack;


/* Used for breadth-first searching a graph. */
typedef struct {
    size_t head, tail, capacity;
    Vertex** data;
} VertexQueue;


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


VertexStack* stack_new(size_t);
void stack_free(VertexStack*);
Vertex* stack_pop(VertexStack*);
void stack_push(VertexStack*, Vertex*);
bool stack_empty(const VertexStack*);


VertexQueue* queue_new(size_t);
void queue_free(VertexQueue*);
Vertex* queue_pop(VertexQueue*);
void queue_push(VertexQueue*, Vertex*);
bool queue_empty(const VertexQueue*);
