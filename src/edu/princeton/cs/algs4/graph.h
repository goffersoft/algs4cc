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
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

#include "bag.h"
#include "graph_base.h"
#include "cstdin.h"
#include "udedge.h"
#include "diedge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::istream;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::range_error;
using std::unique_ptr;

using edu::princeton::cs::algs4::bag;
using edu::princeton::cs::algs4::cstdin;
using edu::princeton::cs::algs4::graph_base;
using edu::princeton::cs::algs4::udedge_base;
using edu::princeton::cs::algs4::diedge_base;

/**
 ** The graph class represents an abstract base class
 ** for all unweighted graph types. This class contains
 ** abstract methods that must be overridden by the derived
 ** classes.
 **   add_edge - add an edge to the graph 
 ** The class contains public methods common to all 
 ** unweighted graph type objects 
 **/
class graph : public graph_base {
    public :
        template<typename E>
        using edge_iterable = vector<E>;
        template<typename E>
        using edge_iterable_ptr = unique_ptr<edge_iterable<E> >;
        using adj_iterable =
            typename bag<vertex_type>::bag_value_type;
        using adj_iterator =
            typename adj_iterable::iterator;
        using adj_const_iterator = typename adj_iterable::const_iterator;
        using graph_type = vector<adj_iterable>;

        graph(const size_t& nvertices) : 
                    graph_base(nvertices) {
            grep = graph_type(get_num_vertices());
        }

        graph(istream& is, bool directed) : 
                    graph_base(is) {
            grep = graph_type(get_num_vertices());
            create_graph(is, directed);
        }

        graph(const graph& g) :
              graph_base(g.get_num_vertices(), g.get_num_edges()) {
            grep = graph_type(get_num_vertices());

            for(size_t v = 0; v < get_num_vertices(); v++) {
                for(auto& a : g.get_adj(v)) {
                    grep[v].push_back(a);
                }
            }
        }

        const adj_iterable& get_adj(const vertex_type& v) const {
            validate_input(v);
            return grep[v];
        }

        bool has_edge(const vertex_type& v,
                      const vertex_type& w) const override {
            validate_input(v, w);

            for(auto& a : get_adj(v)) {
                if(a == w) {
                    return true;
                }
            }
            return false;
        }

        template<typename E>
        static bool has_edge(const graph &g, const E& e) {
            const vertex_type v = edge_base(e).get_first();
            const vertex_type w = edge_base(e).get_second();

            return g.has_edge(v, w);
        }

        template<typename E>
        static edge_iterable_ptr<E> get_edges(
                          const graph& g,
                          const vertex_type& start_vertex,
                          const vertex_type& end_vertex) {
            g.validate_input(start_vertex, end_vertex);
            edge_iterable<E> *edges =
                      new edge_iterable<E>();

            for(size_t v = start_vertex;
                v <= end_vertex; v++) {
                for(auto& w : g.get_adj(v)) {
                    edges->push_back(E(v, w));
                }
            }
            return edge_iterable_ptr<E>(edges);
        }

        template<typename E>
        static edge_iterable_ptr<E> get_edges(const graph& g) {
            return get_edges<E>(g, 0, g.get_num_vertices() - 1);
        }

        template<typename E>
        static edge_iterable_ptr<E> get_edges(const graph& g,
                                              const vertex_type& v) {
            return get_edges<E>(g, v, v);
        }

        operator string() const {
            stringstream ss;
            ss << "num vertices : " << get_num_vertices() << endl;
            ss << "num edges : " << get_num_edges() << endl;
            vertex_type v = 0;
            for(auto& b : grep) {
                ss << v << ": ";
                for(auto& w : b) {
                    ss << w << " ";
                }
                ss << endl;
                v++;
            }
            return ss.str();
        }

        virtual void add_edge(const vertex_type& v,
                              const vertex_type& w) = 0;

    protected :

        size_t get_num_adj(const vertex_type& v) const override {
            return grep[v].size();
        }

        void add_edge(const vertex_type& v,
                      const vertex_type& w,
                      bool directed,
                      bool inc_edge_count = true) {
            grep[v].push_back(w);
            if(!directed && v != w)
                grep[w].push_back(v);
            if(inc_edge_count)
                set_num_edges(get_num_edges() + 1);
        }

    private :
        graph_type grep;

        void create_graph(istream& is, bool directed) {
            for(size_t i = 0; i < get_num_edges(); i++) {
                vertex_type v = cstdin::read_uint32(is);
                vertex_type w = cstdin::read_uint32(is);
                validate_input(v, w);
                add_edge(v, w, directed, false);
            }
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

#endif /* __GRAPH_H__ */
