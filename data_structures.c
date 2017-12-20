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


VertexStack* stack_new(size_t n) {
    VertexStack* ret = safe_malloc(sizeof* ret);
    ret->data = safe_malloc(n * sizeof *ret->data);
    ret->len = 0;
    ret->capacity = n;
    return ret;
}


void stack_free(VertexStack* stack) {
    free(stack->data);
    free(stack);
}


Vertex* stack_pop(VertexStack* stack) {
    return stack->data[--stack->len];
}


void stack_push(VertexStack* stack, Vertex* v) {
    stack->data[stack->len++] = v;
}


bool stack_empty(const VertexStack* stack) {
    return stack->len == 0;
}


VertexQueue* queue_new(size_t n) {
    VertexQueue* ret = safe_malloc(sizeof *ret);
    ret->data = safe_malloc(n * sizeof *ret->data);
    ret->head = ret->tail = 0;
    ret->capacity = n;
    return ret;
}


void queue_free(VertexQueue* queue) {
    free(queue->data);
    free(queue);
}


Vertex* queue_pop(VertexQueue* queue) {
    return queue->data[queue->tail++ % queue->capacity];
}


void queue_push(VertexQueue* queue, Vertex* v) {
    queue->data[queue->head++ % queue->capacity] = v;
}


bool queue_empty(const VertexQueue* queue) {
    return queue->head == queue->tail;
}
