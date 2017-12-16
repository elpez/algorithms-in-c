#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"


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
            printf("%c%c ", c, p->v->val);
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
    int* ret = safe_malloc(n * sizeof *ret);
    for (size_t i = 0; i < n; i++) {
        ret[i] = source[start+i];
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


/* Add a directed edge to the graph. */
void graph_add_edge(Graph* g, char from, char to) {
    /* Find the vertices in the graph's vertex list. */
    Vertex* from_vertex = NULL;
    Vertex* to_vertex = NULL;
    for (size_t i = 0; i < g->n; i++) {
        if (g->vertices[i].val == from) {
            from_vertex = &g->vertices[i];
        }
        if (g->vertices[i].val == to) {
            to_vertex = &g->vertices[i];
        }
    }
    if (from_vertex == NULL || to_vertex == NULL) return;
    /* Make sure the edge doesn't actually exist. */
    VertexList* ptr = from_vertex->neighbors;
    while (ptr != NULL) {
        if (ptr->v == to_vertex) {
            return;
        }
        ptr = ptr->next;
    }
    /* Construct the new entry in the vertex's edge list. */
    VertexList* new_ptr = safe_malloc(sizeof *new_ptr);
    new_ptr->v = to_vertex;
    new_ptr->next = from_vertex->neighbors;
    from_vertex->neighbors = new_ptr;
}


Graph* graph_from_string(enum GraphType typ, const char* vertices, const char* edges) {
    Graph* ret = safe_malloc(sizeof *ret);
    ret->n = strlen(vertices);
    ret->vertices = safe_malloc(ret->n * sizeof *ret->vertices);
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


void* safe_malloc(size_t size) {
    void* ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "MEMORY ERROR in malloc: exiting immediately.\n");
        exit(1);
    }
    return ret;
}


void* safe_calloc(size_t num, size_t size) {
    void* ret = calloc(num, size);
    if (ret == NULL) {
        fprintf(stderr, "MEMORY ERROR in calloc: exiting immediately.\n");
        exit(1);
    }
    return ret;
}


void* safe_realloc(void* ptr, size_t size) {
    void* ret = realloc(ptr, size);
    if (ret == NULL) {
        fprintf(stderr, "MEMORY ERROR in realloc: exiting immediately.\n");
        exit(1);
    }
    return ret;
}
