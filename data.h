#ifndef DATA_H
#define DATA_H


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


typedef struct {
    double x, y;
} Point;

#endif
