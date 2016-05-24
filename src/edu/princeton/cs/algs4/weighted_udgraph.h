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
#ifndef __WEIGHTED_UDGRAPH_H__
#define __WEIGHTED_UDGRAPH_H__

#include <iostream>

#include "cstdin.h"
#include "weighted_udedge.h"
#include "weighted_graph.h"
#include "bag.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::istream;
using std::cin;

using edu::princeton::cs::algs4::weighted_udedge_base;
using edu::princeton::cs::algs4::weighted_graph;
using edu::princeton::cs::algs4::bag;

using com::goffersoft::core::object;

/**
 ** The graph class represents a weighted undirected graph. 
 ** This class derives from graph base class.
 **/
class weighted_udgraph :
             public weighted_graph<weighted_udedge_base> {
    public :
        using base_type = weighted_graph<weighted_udedge_base>;
        using weighted_graph::add_edge;

        weighted_udgraph(const size_t& num_vertices) :
                              base_type(num_vertices) {}

        weighted_udgraph(istream& is = cin) :
                                  base_type(is, false) {}

        void add_edge(const vertex_type& v,
                      const vertex_type& w,
                      const weight_type& wt) override {
            validate_input(v, w);
            add_edge(v, w, wt, false);
        }

        void add_edge(const edge_type& e) override {
            validate_input(((weighted_edge_base)e).get_first(),
                            ((weighted_edge_base)e).get_second());
            add_edge(e, false);
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

#endif /* __WEIGHTED_UDGRAPH_H__ */
