/******************************************************************************
 *  Dependencies: none
 *
 *  G= Graph is made up of a set of vertices connected by edges.
 *  V= Vertex is a point on a Graph
 *  E= Edge connects two Vertices
 *  P= Path is a sequence of vertices connected by edges
 *  C= Cycle is a Path where the first and last Vertex are the same
 *  D= Degree of a Vertex is the number of edges sourced at that Vertex
 *  L= length of a path is the number of edges cvonnecting 2 vertices
 *  two Vertices are Connected if there is a path between them.
 *  Conencted Components is a subset of the Graph where all
 *  vertices are connected to each other
 *
 ******************************************************************************/
#include "graph_base.h"
#include "edge.h"

using edu::princeton::cs::algs4::graph_base;
using edu::princeton::cs::algs4::edge_base;

template<>
typename graph_base::vertex_type
graph_base::get_vertex<edge_base>(
         const typename graph_base::vertex_type& v,
         const edge_base& e) {
    return e.get_other(v);
}
