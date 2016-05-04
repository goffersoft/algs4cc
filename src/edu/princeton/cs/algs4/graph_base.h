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
#ifndef __GRAPH_BASE_H__
#define __GRAPH_BASE_H__

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <climits>
#include <type_traits>

#include "cstdin.h"
#include "edge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::is_same;
using std::istream;
using std::cin;
using std::endl;
using std::stringstream;
using std::range_error;
using std::numeric_limits;

using edu::princeton::cs::algs4::cstdin;
using edu::princeton::cs::algs4::edge_base;

/**
 ** The graph_base class represents an abstract base class
 ** for all graph types. This class contains
 ** abstract methods that must be overridden by the derived
 ** classes.
 **   has_edge - determine if the vertices repesent a edge
 **   get_num_adj - num adjacent vertices.
 ** The class contains public methods common to all graph
 ** type objects 
 **/
class graph_base {
    public :
        using vertex_type = uint32_t;

        graph_base(const size_t& num_vertices) {
            stringstream ss;
            ss << num_vertices << " " << 0 << endl;
            create_graph(ss);
        }

        graph_base(istream& is = cin) {
            create_graph(is);
        }

        size_t get_num_vertices() const {
            return nvertices;
        }

        size_t get_num_edges() const {
            return nedges;
        }

        size_t degree(const vertex_type& v) const {
            validate_input(v);
            return get_num_adj(v); 
        }

        bool has_vertex(const vertex_type& v) const {
            if (v >= get_num_vertices()) {
                return false;
            }
            return true;
        }

        size_t min_degree() const {
            size_t min = std::numeric_limits<size_t>::max();

            for(vertex_type i = 0; i < get_num_vertices(); i++) {
                size_t tmp = get_num_adj(i);
                if (tmp < min) min = tmp;
            }

            return min;
        }

        size_t max_degree() const {
            size_t max = 0;

            for(vertex_type i = 0; i < get_num_vertices(); i++) {
                size_t tmp = get_num_adj(i);
                if (tmp > max) max = tmp;
            }

            return max;
        }

        double avg_degree() const {
            double avg = 0.0;

            for(vertex_type i = 0; i < get_num_vertices(); i++) {
                avg += get_num_adj(i);
            }

            return avg/get_num_vertices();
        }

        virtual bool has_edge(const vertex_type& v,
                              const vertex_type& w) const = 0;

        virtual ~graph_base() {}

        template<typename E>
        static vertex_type get_vertex(const vertex_type& v,
                                      const E& e) {
            static_assert(is_same<E, vertex_type>::value,
                          "E must be one of vertex_type or edge_base");
            return e;
        }

    protected :
        graph_base(const size_t& num_vertices,
                   const size_t& num_edges) {
            stringstream ss;
            ss << num_vertices << " " << num_edges << endl;
            create_graph(ss);
        }

        virtual size_t get_num_adj(const vertex_type& v) const = 0;

        void set_num_edges(size_t num) {
            nedges = num;
        }

        void validate_input(const vertex_type& v,
                            const vertex_type& w) const {
            if (v >= get_num_vertices() ||
                w >= get_num_vertices()) {
                throw range_error("v or w out of range");
            }
        }

        void validate_input(const vertex_type& v) const {
            if (v >= get_num_vertices()) {
                throw range_error("v out of range");
            }
        }

    private :
        size_t nedges;
        size_t nvertices;

        void create_graph(istream& is) {
            nvertices = cstdin::read_uint32(is);
            nedges = cstdin::read_uint32(is);
        }
};

template<>
graph_base::vertex_type
graph_base::get_vertex<edge_base>(const graph_base::vertex_type& v,
                                  const edge_base& e);

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

#endif /* __GRAPH_BASE_H__ */
