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
#ifndef __DFS_PRE_ORDER_H__
#define __DFS_PRE_ORDER_H__

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

#include "dfs_base.h"
#include "path.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

using edu::princeton::cs::algs4::path_compute;
using edu::princeton::cs::algs4::search_base;
using edu::princeton::cs::algs4::graph_base;
using edu::princeton::cs::algs4::dfs_base;

/**
 ** The dfs_pre_order class represents a data type for
 ** determining depth-first search ordering of the
 ** vertices in a graph.
 ** This vertices are stored in pre-order.
 ** That is, the order in which they are visited.
 ** This implementation uses depth-first search.
 ** The constructor takes time proportional to V + E
 ** (in the worst case),
 ** where V is the number of vertices and E is the number
 ** of edges.
 **/
template <typename G>
class dfs_pre_order : public virtual dfs_base<G>,
                      public virtual path_compute<G> {
    public :
        using typename dfs_base<G>::graph_type;
        using typename dfs_base<graph_type>::vertex_type;
        using typename path_compute<graph_type>::iterable;
        using iterable_ptr = shared_ptr<iterable>;
        using order_type = uint32_t;
        using dfs_base<graph_type>::get_visited;
        using dfs_base<graph_type>::set_visited;
        using dfs_base<graph_type>::visited;
        using dfs_base<graph_type>::generic_dfs;
        using dfs_base<graph_type>::gsetup_func_null;
        using dfs_base<graph_type>::gproc_func_null;
        using path_compute<graph_type>::is_eager;
        using path_compute<graph_type>::is_lazy;
        using path_compute<graph_type>::compute;
        using path_compute<graph_type>::get_graph;
        using path_compute<graph_type>::validate_input;
        
        //No need to initialize all entries of the array to 0
        //as the dfs algotihm sets all entries of the array
        //upon completion
        dfs_pre_order(const graph_type& g,
                      bool defer = false) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, 0, defer),
                pre_array(new array_type[g.get_num_vertices()]),
                pre_order(new iterable()),
                pre_counter(0) {
            if(is_eager()) {
                compute();
            }
        }

        /**
         ** Returns the preorder number of vertex v.
         ** param : v the vertex
         ** return : the preorder number of vertex v
         **/
        order_type pre(const vertex_type& v) {
            validate_input(v);
            if(is_lazy()) {
                compute();
            }
            return pre_array[v];
        }

        /**
         ** return the vertices in preorder, as an iterable of vertices
         **/
        iterable_ptr pre() {
            if(is_lazy()) {
                compute();
            }
            return pre_order;
        }

    protected :
        using array_type = order_type;
        using array_type_ptr = unique_ptr<array_type[]>;

        //No need to initialize all entries of the array to 0
        //as the dfs algotihm sets all entries of the array
        //upon completion
        dfs_pre_order(const graph_type& g,
                      bool defer, bool base) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, 0, defer),
                pre_array(new array_type[g.get_num_vertices()]),
                pre_order(new iterable()),
                pre_counter(0) {
            if(is_eager() && !base) {
                compute();
            }
        }

        array_type_ptr get_pre_array() const {
            return pre_array;
        }

        const array_type get_pre_array(
                     const vertex_type& v) const {
            return pre_array[v];
        }

        void set_pre_array(const vertex_type& v,
                           const array_type& val) {
            pre_array[v] = val;
        }

        void set_pre_array(const vertex_type& v) {
            pre_array[v] = pre_counter++;
        }

        const array_type& get_pre_counter() const {
            return pre_counter;
        }

        void set_pre_counter(const array_type& val) {
            pre_counter = val;
        }

        void inc_pre_counter() {
            pre_counter++;
        }

        void dec_pre_counter() {
            pre_counter--;
        }

        void set_pre_order_front(const vertex_type& v) {
            pre_order->push_front(v);
        }

        void set_pre_order_back(const vertex_type& v) {
            pre_order->push_back(v);
        }

        void reset() override {
            (*pre_order).clear();   
            pre_counter = 0;
            if(get_graph().get_num_vertices() != get_visited().size()) {
                //No need to initialize all entries of the array to 0
                //as the dfs algotihm sets all entries of the array
                //upon completion
                pre_array.reset(new array_type[
                                      get_graph().get_num_vertices()]);
            }
            dfs_base<graph_type>::reset(get_graph().get_num_vertices());
        }

        void compute_path(const graph_type& g,
                          const vertex_type& s) override {
            for(size_t vv = 0; vv < get_graph().get_num_vertices(); vv++) {
                if(!visited(vv)) {
                    generic_dfs(g, vv,
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            set_visited(v);
                        },
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            return visited(v);
                        },
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            set_pre_array(v);
                            set_pre_order_back(v);
                        },
                        gproc_func_null,
                        gproc_func_null,
                        gsetup_func_null); 
                }
            }
        }

    private :
        array_type_ptr pre_array; // pre[v]    = preorder  number of v
        iterable_ptr pre_order;   // vertices in preorder
        array_type pre_counter;   // counter or preorder numbering
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

#endif /* __DFS_PRE_ORDER_H__ */
