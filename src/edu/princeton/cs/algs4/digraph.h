/******************************************************************************
 *  Dependencies: none
 *
 *  template header file
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
#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <iostream>
#include <stdexcept>
#include <memory>

#include "graph.h"
#include "diedge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::istream;
using std::cin;
using std::range_error;
using std::unique_ptr;

using edu::princeton::cs::algs4::graph;
using edu::princeton::cs::algs4::diedge_base;

/**
 ** The graph class represents a weighted directed graph. 
 ** This class derives from graph base class.
 **/
class digraph : public graph {
    public :
        using graph::add_edge;
        using graph::get_edges;
        using edge_type = diedge_base;
        using edge_iterable = graph::edge_iterable<edge_type>;

        digraph(const size_t& num_vertices) :
                graph(num_vertices) {}

        digraph(istream& is = cin) :
                graph(is, true) {}

        void add_edge(const vertex_type& v,
                      const vertex_type& w) override {
            if (v >= get_num_vertices() || w >= get_num_vertices()) {
                throw range_error("v or w out of range");
            }
	    add_edge(v, w, true);
        }

        unique_ptr<edge_iterable> get_edges() const {
            return get_edges<edge_type>(*this);
        }

        unique_ptr<digraph> reverse() const {
            digraph* g = new digraph(get_num_vertices());

            for(size_t v = 0; v < get_num_vertices(); v++) {
                for(auto& a : get_adj(v)) {
                    g->add_edge(a, v, true);
                }
            }
            return unique_ptr<digraph>(g);
        }
};

} //edu
} //princeton
} //cs
} //algs4

/******************************************************************************
 *  Copyright 2016, Prakash Easwar.
 *
 *  This file is part of algs4.so, ported to c++ from java
 *
 *      Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne,
 *      Addison-Wesley Professional, 2011, ISBN 0-321-57351-X.
 *      http://algs4.cs.princeton.edu
 *
 *  algs4.so is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.so is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with algs4.so.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/

#endif /* __DIGRAPH_H__ */
