#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

struct vertex_s {
    element elem;
    int visited;
    struct edge_s *edges;
    struct vertex_s *next;
};

struct edge_s {
    struct vertex_s *to;
    struct edge_s *next;
};

struct graph_s {
    struct vertex_s *vertices;
};

static int _reachable(vertex start, element dst);

graph graph_create()
{
    struct graph_s *g = malloc(sizeof(struct graph_s));
    g->vertices = NULL;

    return g;
}

void graph_destroy(graph g)
{
    vertex v = g->vertices;
    vertex v2;
    edge e, e2;

    if(!v)
        return;

    /* iterate over all vertices */
    for(; v != NULL; v = v->next)
    {
        printf("Freeing vertex @ %p\n", v);
        v2 = v;
        /* Free all edges */
        for(e = v2->edges; e != NULL; e = e->next)
        {
            printf("Freeing edge @ %p\n", e);
            e2 = e;
            free(e2);
        }

        /* Free vertex */
        free(v2);
    }
}

void graph_add_vertex(graph g, element value)
{
    /* Operate on graphs vertices list */
    vertex vert = g->vertices;

    if (!vert)
    {
        /* empty list, add first vertex */
        vert = malloc(sizeof(struct vertex_s));
        vert->next = NULL;
        vert->elem = value;
        vert->edges = NULL;
        vert->visited = 0;
        g->vertices = vert;
    } 
    else
    {
        /* find end of list */
        for(; vert->next != NULL; vert = vert->next);

        /* Allocate and initialize vertex */
        vert->next = malloc(sizeof(struct vertex_s));
        vert->next->elem = value;
        vert->next->next = NULL;
        vert->next->edges = NULL;
        vert->visited = 0;
    }
}

void graph_add_edge(graph g, element src, element dst)
{
    vertex p_from, p_to;
    edge e;

    /*
     * Check For
     * =========
     * null pointers
     * src != dst
     * src and dst in g
     */

    /* Find vertex src in graph g */
    for (p_from = g->vertices; p_from != NULL; p_from = p_from->next)
    {
        /* found a match */
        if(p_from->elem == src)
        {
            for(p_to = g->vertices; p_to != NULL; p_to = p_to->next)
            {
                if(p_to->elem == dst)
                {
                    /* append to edges */
                    e = p_from->edges;
                    if(!e)
                    {
                        e = malloc(sizeof(struct edge_s));
                        e->next = NULL;
                        e->to = p_to;
                        p_from->edges = e;
                    }
                    else
                    {
                        for(; e->next != NULL; e = e->next);
                        e->next = malloc(sizeof(struct edge_s));
                        e->next->next = NULL;
                        e->next->to = p_to;
                    }
                }
            }
        }
    }
}

int graph_reachable(graph g, element src, element dst)
{
    vertex vert, start = NULL;

    /* Set all vertices visited value to 0 */
    for(vert = g->vertices; vert != NULL; vert = vert->next)
    {
        vert->visited = 0;
        if(vert->elem == src)
            start = vert;
    }

    if(!start)
        return 0;

    return _reachable(start, dst);
}

static int _reachable(vertex start, element dst)
{
    edge e;

    if(start->visited == 1)
        return 0;

    if(start->elem == dst)
        return 1;

    start->visited = 1;

    for(e = start->edges; e != NULL; e = e->next)
    {
        return _reachable(e->to, dst);
    }

    return 0;
}

/*
 *  Helper Printing Functions
 */
void graph_list_vertices(graph g)
{
    int i;
    vertex vert = g->vertices;

    printf("Graph Vertices[");

    for(i = 0; vert != NULL; vert = vert->next, ++i)
    {
        if (i > 0)
            printf(", ");
        //printf("%d", vert->elem);
        printf("(visited=%d, elem=%d)", vert->visited, vert->elem);
    }
    printf("]\n");
}

void graph_list_edges(graph g)
{
    /* Set all visited's to 0 */
    vertex vert;
    edge e;
    int i, j;

    for(vert = g->vertices, i = 0; vert != NULL; vert = vert->next, ++i)
    {
        printf("Vertex %d Edges[", i);
        for(e = vert->edges, j = 0; e != NULL; e = e->next, ++j)
        {
            if (j > 0)
            {
                printf(", ");
            }
            printf("%d->%d", vert->elem, e->to->elem);
        }
        printf("]\n");
    }

}
