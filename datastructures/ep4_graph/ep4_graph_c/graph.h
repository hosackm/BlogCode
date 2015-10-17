#ifndef __GRAPH_H__
#define __GRAPH_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int element;
typedef struct graph_s *graph;
typedef struct vertex_s *vertex;
typedef struct edge_s *edge;

graph graph_create();
void graph_destroy(graph g);

void graph_add_vertex(graph g, element value);
void graph_add_edge(graph g, element src, element dst);

int graph_reachable(graph g, element src, element dst);

void graph_list_vertices(graph g);
void graph_list_edges(graph g);

#ifdef __cplusplus
}
#endif

#endif /* __GRAPH_H__ */
