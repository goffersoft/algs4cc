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
#ifndef __DFS_REVERSE_POST_H__
#define __DFS_REVERSE_POST_H__

#include <iostream>
#include <memory>

#include "dfs_post_order.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::unique_ptr;

using edu::princeton::cs::algs4::dfs_post_order;
using edu::princeton::cs::algs4::dfs_base;
using edu::princeton::cs::algs4::path_compute;

/**
 ** The dfs_post_order class represents a data type for
 ** determining depth-first search ordering of the
 ** vertices in a graph.
 ** This vertices are stored in post-order.
 ** That is, a vertex is considered for ordering only
 ** after all the adjacent vetices of the given 
 ** vertex have been visited but in reverse.
 ** (a push_front as opposed to a push_back)
 ** This implementation uses depth-first search.
 ** The constructor takes time proportional to V + E
 ** (in the worst case),
 ** where V is the number of vertices and E is the number
 ** of edges.
 **/
template <typename G>
class dfs_reverse_post_order : public dfs_post_order<G> {
    public :
        using graph_type = G;
        using vertex_type = typename graph_type::vertex_type;
        using typename dfs_post_order<graph_type>::iterable;
        using typename dfs_post_order<graph_type>::iterable_ptr;
        using post_iterable_ptr = unique_ptr<iterable>;
        using typename dfs_post_order<graph_type>::order_type;
        using dfs_post_order<graph_type>::get_visited;
        using dfs_post_order<graph_type>::set_visited;
        using dfs_post_order<graph_type>::visited;
        using dfs_post_order<graph_type>::generic_dfs;
        using dfs_post_order<graph_type>::gsetup_func_null;
        using dfs_post_order<graph_type>::gproc_func_null;
        using dfs_post_order<graph_type>::get_post_array;
        using dfs_post_order<graph_type>::set_post_array;
        using dfs_post_order<graph_type>::set_post_order_front;
        using dfs_post_order<graph_type>::get_post_order;
        using dfs_post_order<graph_type>::is_eager;
        using dfs_post_order<graph_type>::is_lazy;
        using dfs_post_order<graph_type>::compute;
        using dfs_post_order<graph_type>::get_graph;
        using dfs_post_order<graph_type>::post;
        using dfs_post_order<graph_type>::reverse_post;

        dfs_reverse_post_order(const graph_type& g,
                               bool defer = false) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, 0, defer),
                dfs_post_order<graph_type>(g, defer, true) {
            if(is_eager()) {
                compute();
            }
        }

        /**
         ** Returns the vertices in reverse postorder.
         ** return the vertices in reverse postorder, as an iterable of vertices
         **/
        iterable_ptr reverse_post() {
             if(is_lazy()) {
                 compute();
             }
             return get_post_order();
        }

        /**
         ** return the vertices in postorder, as an iterable of vertices
         **/
        post_iterable_ptr post() {
            if(is_lazy()) {
                compute();
            }
            iterable* rp = new iterable();
            for(auto& e : *(get_post_order())) {
                rp->push_front(e);
            }
            return post_iterable_ptr(rp);
        }

    protected :
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
                            set_post_order_front(v);
                        }); 
                }
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

#endif /* __DFS_REVERSE_POST_H__ */
