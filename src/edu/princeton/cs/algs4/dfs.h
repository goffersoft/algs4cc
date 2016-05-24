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
#ifndef __DFS_H__
#define __DFS_H__

#include <iostream>

#include "dfs_base.h"
#include "path.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {


using edu::princeton::cs::algs4::path_compute;
using edu::princeton::cs::algs4::dfs_base;

/**
 ** The dfs class represents a data type for
 ** determining the vertices connected to a given source vertex
 ** in any graph using the depth first search algorithm.
 ** This implementation uses depth-first search.
 ** The constructor takes time proportional to V + E
 ** (in the worst case),
 ** where V is the number of vertices and E is the
 ** number of edges.
 ** It uses extra space (not including the graph) proportional to V
 **
 **/
template <typename G>
class dfs : public dfs_base<G>,
            public path_compute<G> {
    public :
        using typename dfs_base<G>::graph_type;
        using typename dfs_base<graph_type>::vertex_type;
        using dfs_base<graph_type>::set_visited;
        using dfs_base<graph_type>::visited;
        using dfs_base<graph_type>::generic_dfs;
        using dfs_base<graph_type>::gsetup_func_null;
        using path_compute<graph_type>::is_eager;
        using path_compute<graph_type>::is_lazy;
        using path_compute<graph_type>::compute;
        using path_compute<graph_type>::get_graph;
        using path_compute<graph_type>::get_start_vertex;
        using path_compute<graph_type>::validate_input;

        dfs(const graph_type& g,
            const vertex_type& s,
            bool defer = false) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, s, defer),
                count(0) {
            if(is_eager()) {
                compute();
            }
        }

        /**
         ** Is there a path between the source vertex s
         ** and vertex v
         ** param v the vertex
         ** return true if there is a path, false otherwise
         **/
        bool has_path(const vertex_type& v) {
            validate_input(v);
            if(is_lazy()) {
                compute();
            }
            return visited(v);
        }

        /**
         ** Returns the number of vertices connected to the
         ** source vertex s
         **/
        size_t get_count() {
            if(is_lazy()) {
                compute();
            }
            return count;
        }

    protected :
        void reset() override {
            dfs_base<graph_type>::reset(get_graph().get_num_vertices());
            count = 0;
        }

        void compute_path(const graph_type& g,
                          const vertex_type& s) override {
            generic_dfs(g, s,
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            set_visited(v);
                        },
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            return visited(v);
                        },
                        [this](const graph_type& g,
                               const vertex_type& start_vertex) {
                            count++; 
                        });
        }

    private :
        size_t count;
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

#endif /* __DFS_H__ */
