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
#ifndef __DFS_POST_ORDER_H__
#define __DFS_POST_ORDER_H__

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <deque>
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
using std::deque;
using std::range_error;

using edu::princeton::cs::algs4::path_compute;
using edu::princeton::cs::algs4::dfs_base;

/**
 ** The dfs_post_order class represents a data type for
 ** determining depth-first search ordering of the
 ** vertices in a graph.
 ** The vertices are stored in post-order.
 ** That is, a vertex is considered for ordering only
 ** after all the adjacent vetices of the given 
 ** vertex have been visited.
 ** (a push_back as opposed to a push_front)
 ** This implementation uses depth-first search.
 ** The constructor takes time proportional to V + E
 ** (in the worst case),
 ** where V is the number of vertices and E is the number
 ** of edges.
 **/
template <typename G>
class dfs_post_order : public virtual dfs_base<G>,
                       public virtual path_compute<G> {
    public :
        using typename dfs_base<G>::graph_type;
        using typename dfs_base<graph_type>::vertex_type;
        using typename path_compute<graph_type>::iterable;
        using iterable_ptr = shared_ptr<iterable>;
        using reverse_post_iterable_ptr = unique_ptr<iterable>;
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

        dfs_post_order(const graph_type& g,
                  bool defer = false) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, 0, defer),
                post_array(new array_type[g.get_num_vertices()]),
                post_order(new iterable()),
                post_counter(0) {

            if(is_eager()) {
                compute();
            }
        }

        /**
         ** Returns the postorder number of vertex v.
         ** param : v the vertex
         ** return : the postorder number of vertex v
         **/
        order_type post(const vertex_type& v) {
            if (v >= get_graph().get_num_vertices()) {
                throw range_error("v out of range");
            }
            if(is_lazy()) {
                compute();
            }
            return post_array[v];
        }

        /**
         ** Returns the postorder number of vertex v.
         ** param : v the vertex
         ** return : the postorder number of vertex v
         **/
        order_type reverse_post(const vertex_type& v) {
            if (v >= get_graph().get_num_vertices()) {
                throw range_error("v out of range");
            }
            if(is_lazy()) {
                compute();
            }
            return get_graph().get_num_vertices() - post_array[v] - 1;
        }

        /**
         ** Returns the vertices in postorder.
         ** return the vertices in postorder, as an iterable of vertices
         **/
        iterable_ptr post() {
            if(is_lazy()) {
                compute();
            }
            return post_order;
        }

        /**
         ** return the vertices in reverse postorder, as an iterable of vertices
         **/
        reverse_post_iterable_ptr reverse_post() {
            if(is_lazy()) {
                compute();
            }
            iterable* rp = new iterable();
            for(auto& e : *(post())) {
                rp->push_front(e);
            }
            return reverse_post_iterable_ptr(rp);
        }

    protected :
        using array_type = order_type;
        using array_type_ptr = unique_ptr<array_type[]>;

        dfs_post_order(const graph_type& g,
                  bool defer, bool base) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, 0, defer),
                post_array(new array_type[g.get_num_vertices()]),
                post_order(new iterable()),
                post_counter(0) {
            if(is_eager() && !base ) {
                compute();
            }
        }

        array_type_ptr get_post_array() const {
            return post_array;
        }

        const array_type get_post_array(
                     const vertex_type& v) const {
            return post_array[v];
        }

        void set_post_array(const vertex_type& v,
                           const array_type& val) {
            post_array[v] = val;
        }

        void set_post_array(const vertex_type& v) {
            post_array[v] = post_counter++;
        }

        const array_type& get_post_counter() const {
            return post_counter;
        }

        void set_post_counter(const array_type& val) {
            post_counter = val;
        }

        void inc_post_counter() {
            post_counter++;
        }

        void dec_post_counter() {
            post_counter--;
        }

        iterable_ptr get_post_order() {
            return post_order;
        }

        void set_post_order_front(const vertex_type& v) {
            post_order->push_front(v);
        }

        void set_post_order_back(const vertex_type& v) {
            post_order->push_back(v);
        }

        void reset() override {
            (*post_order).clear();   
            post_counter = 0;
            if(get_graph().get_num_vertices() != get_visited().size()) {
                post_array.reset(new array_type[
                                      get_graph().get_num_vertices()]);
            } else {
                memset(post_array.get(), 0x0,
                       get_graph().get_num_vertices());
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
                        gsetup_func_null,
                        gproc_func_null,
                        gproc_func_null,
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            set_post_array(v);
                            set_post_order_back(v);
                        }); 
                }
            }
        }

    private :
        array_type_ptr post_array; // pre[v]    = preorder  number of v
        iterable_ptr post_order;  // vertices in preorder
        array_type post_counter;  // counter or preorder numbering
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

#endif /* __DFS_POST_ORDER_H__ */
