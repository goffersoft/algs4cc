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
#ifndef __FLOW_NETWORK_H__
#define __FLOW_NETWORK_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "graph_base.h"
#include "bag.h"
#include "cstdin.h"
#include "flow_edge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::vector;
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
using edu::princeton::cs::algs4::flow_edge;

class flow_network : public graph_base {
    public :
        using edge_type = flow_edge_base;
        using adj_type = shared_ptr<edge_type>;
        using adj_iterable =
            typename bag<adj_type >::bag_value_type;
        using adj_iterator = typename adj_iterable::iterator;
        using adj_const_iterator = typename adj_iterable::const_iterator;
        using graph_type = vector<adj_iterable>;
        using edge_iterable = vector<edge_type>;
        using edge_iterable_ptr = unique_ptr<edge_iterable>;

        flow_network(const size_t& nvertices) :
                 graph_base(nvertices) {
            grep = graph_type(get_num_vertices());
        }

        flow_network(istream& is = cin,
                     bool init_flow_data = true) :
                 graph_base(is) {
            grep = graph_type(get_num_vertices());
            create_graph(is, init_flow_data);
        }

        flow_network(const flow_network& g) :
                   graph_base(g.get_num_vertices(),
                              g.get_num_edges()) {
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
                                             e->get_capacity(),
                                             e->get_flow())); 
                    } else if(((edge_base)(*e)).get_second() == v) {
                        edges->push_back(edge_type(v,
                                             ((edge_base)(*e)).get_first(),
                                             e->get_capacity(),
                                             e->get_flow()));
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
                if(((edge_type)(*a)).get_to() == w) {
                    return true;
                }
            }
            return false; 
        }

        bool has_edge(const edge_type& e) const {
            validate_input(e.get_from(), e.get_to());

            for(auto& a : get_adj(e.get_from())) {
                if(((edge_type)(*a)).get_to() == e.get_to()) {
                    return true;
                }
            }
            return false;
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

        virtual void add_edge(const edge_type& e,
                              bool inc_edge_count = true) { 
            validate_input(e.get_from(), e.get_to());
            edge_type* tmp = new edge_type(e);
            add_edge(tmp, inc_edge_count);
        }

        virtual void add_edge(const vertex_type& v,
                              const vertex_type& w,
                              const flow_edge::flow_type& flow,
                              const flow_edge::capacity_type& capacity,
                              bool inc_edge_count = true) {
            validate_input(v, w);
            edge_type* tmp = new edge_type(v, w, flow, capacity);
            add_edge(tmp, inc_edge_count);
        }

        virtual void add_edge(const vertex_type& v,
                              const vertex_type& w,
                              const flow_edge::capacity_type& capacity,
                              bool inc_edge_count = true) {
            add_edge(v, w, 0, capacity, inc_edge_count);
        }

    protected :

        void add_edge(edge_type* e,
                      bool inc_edge_count = true) {
            adj_type tmp(e);
            grep[e->get_from()].push_back(tmp);
            if(e->get_from() != e->get_to())
                grep[e->get_to()].push_back(tmp);
            if(inc_edge_count)
                set_num_edges(get_num_edges() + 1);
        }

        size_t get_num_adj(const vertex_type& v) const override {
            return grep[v].size();
        }

    private :
        graph_type grep;

        void create_graph(istream& is, bool init_flow_data) {
            for(size_t i = 0; i < get_num_edges(); i++) {
                add_edge(edge_type(is, init_flow_data), false);
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

#endif /* __FLOW_NETWORK_H__ */
