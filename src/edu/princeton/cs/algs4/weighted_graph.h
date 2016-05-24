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
#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "graph_base.h"
#include "bag.h"
#include "cstdin.h"
#include "edge.h"

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
using std::shared_ptr;
using std::unique_ptr;

using edu::princeton::cs::algs4::bag;
using edu::princeton::cs::algs4::cstdin;
using edu::princeton::cs::algs4::edge;
using edu::princeton::cs::algs4::graph_base;

/**
 ** The graph class represents an abstract base class
 ** for all weighted graph types. This class contains
 ** abstract methods that must be overridden by the derived
 ** classes.
 **   add_edge - add an edge to the graph 
 ** The class contains public methods common to all 
 ** weighted graph type objects 
 **/
template<typename E>
class weighted_graph : public graph_base {
    public :
        using edge_type = E;
        using weight_type = typename edge_type::weight_type;
        using adj_ptr_type = shared_ptr<edge_type>;
        using adj_type = adj_ptr_type;
        using adj_iterable =
            typename bag<adj_type >::bag_value_type;
        using edge_iterable = vector<edge_type>;
        using edge_iterable_ptr = unique_ptr<edge_iterable>;
        using adj_iterator =
            typename adj_iterable::iterator;
        using adj_const_iterator =
            typename adj_iterable::const_iterator;
        using graph_type = vector<adj_iterable >;

        weighted_graph(const size_t& nvertices) :
                 graph_base(nvertices) {
            grep = graph_type(get_num_vertices());
        }

        weighted_graph(istream& is, bool directed) :
                    graph_base(is) {
            grep = graph_type(get_num_vertices());
            create_graph(is, directed);
        }

        weighted_graph(const weighted_graph<edge_type>& g) :
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

        edge_iterable_ptr get_edges(
               const vertex_type& start_vertex,
               const vertex_type& end_vertex) const {
            validate_input(start_vertex, end_vertex);
            edge_iterable *edges = new edge_iterable();

            for(size_t v = start_vertex; v <= end_vertex; v++) {
                for(auto& e : get_adj(v)) {
                    if(((edge_base)(*e)).get_first() == v) {
                        edges->push_back(edge_type(v,
                                             ((edge_base)(*e)).get_second(),
                                             e->get_weight())); 
                    } else if(((edge_base)(*e)).get_second() == v) {
                        edges->push_back(edge_type(v,
                                             ((edge_base)(*e)).get_first(),
                                             e->get_weight()));
                    }
                }
            }

            return edge_iterable_ptr(edges);
        }

        edge_iterable_ptr get_edges() const {
            return get_edges(0, get_num_vertices() - 1);
        }

        edge_iterable_ptr get_edges(const vertex_type& v) const {
            return get_edges(v, v);
        }

        bool has_edge(const vertex_type& v,
                      const vertex_type& w) const override {
            validate_input(v, w);

            for(auto& a : get_adj(v)) {
                if(((weighted_edge_base)(*a)).get_first() == w ||
                   ((weighted_edge_base)(*a)).get_second() == w) {
                    return true;
                }
            }
            return false; 
        }

        bool has_edge(const edge_type& e) {
            const vertex_type v = edge_base(e).get_first();
            const vertex_type w = edge_base(e).get_second();

            return has_edge(v, w);
        }

        operator string() const {
            stringstream ss;
            ss << "num vertices : " << get_num_vertices() << endl;
            ss << "num edges : " << get_num_edges() << endl;
            vertex_type v = 0;
            for(auto& b : grep) {
                ss << v << ": ";
                for(auto& w : b) {
                    ss << "(" << *w << ") ";
                }
                ss << endl;
                v++;
            }
            return ss.str(); 
        }

        virtual void add_edge(const vertex_type& v,
                              const vertex_type& w,
                              const weight_type& wt) = 0;

        virtual void add_edge(const edge_type& e) = 0;

    protected :

        size_t get_num_adj(const vertex_type& v) const override {
            return grep[v].size();
        }

        void add_edge(const vertex_type& v,
                      const vertex_type& w,
                      const weight_type& wt,
                      bool directed,
                      bool inc_edge_count = true) {
            edge_type* e = new edge_type(v, w, wt);
            adj_type tmp(e);
            grep[v].push_back(tmp);
            if(!directed && (v != w)) {
                grep[w].push_back(tmp);
            }
            if(inc_edge_count)
                set_num_edges(get_num_edges() + 1);
        }

        void add_edge(const weighted_edge_base& e,
                      bool directed,
                      bool inc_edge_count = true) {
            add_edge(e.get_first(),
                     e.get_second(),
                     e.get_weight(),
                     directed,
                     inc_edge_count);
        }

    private :
        graph_type grep;

        void create_graph(istream& is, bool directed) {
            for(size_t i = 0; i < get_num_edges(); i++) {
                weighted_edge_base e(is);
                validate_input(e.get_first(), e.get_second());
                add_edge(e, directed, false);
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

#endif /* __WEIGHTED_GRAPH_H__ */
