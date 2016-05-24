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
#ifndef __DFS_PATHS_H__
#define __DFS_PATHS_H__

#include <iostream>
#include <vector>
#include <deque>
#include <memory>
#include <cstring>

#include "dfs_base.h"
#include "path.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::unique_ptr;
using std::vector;
using std::deque;

using edu::princeton::cs::algs4::path_compute;
using edu::princeton::cs::algs4::dfs_base;

/**
 ** The dfs_paths class represents a data type for finding
 ** paths from a source vertex s to every other vertex
 ** in a graph.
 ** This implementation uses depth-first search.
 ** The constructor takes time proportional to V + E,
 ** where V is the number of vertices and
 ** E is the number of edges.
 ** It uses extra space (not including the graph)
 ** proportional to V.
 **/
template <typename G>
class dfs_paths : public dfs_base<G>,
                  public path_compute<G> {
    public :
        using typename dfs_base<G>::graph_type;
        using typename dfs_base<graph_type>::vertex_type;
        using typename path_compute<graph_type>::iterable;
        using iterable_ptr = unique_ptr<iterable>;
        using dfs_base<graph_type>::get_visited;
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

        dfs_paths(const graph_type& g,
                  const vertex_type& s,
                  bool defer = false) :
                dfs_base<graph_type>(g.get_num_vertices()),
                path_compute<graph_type>(g, s, defer) {
            edge_to = vector<vertex_type>(g.get_num_vertices());
            if(is_eager()) {
                compute();
            }
        }

        /**
         ** Is there a path between the source vertex s and vertex v
         ** param : v the vertex
         ** return : true if there is a path, false otherwise
         **/
        bool has_path(const vertex_type& v) {
            validate_input(v);
            if(is_lazy()) {
                compute();
            }
            return visited(v);
        }

        /**
         ** Returns a path between the source vertex s and vertex v
         ** empty iterable if no such path exists.
         ** param : v the vertex
         ** return : the sequence of vertices on a path between the source vertex
         ** s and vertex v, as an Iterable
         **/
        iterable_ptr path_to(const vertex_type& v) {
            validate_input(v);
            if(is_lazy()) {
                compute();
            }
            iterable* path = new iterable();
            vertex_type  vv = v;
            if(visited(vv)) {
                while(vv != get_start_vertex()) {
                    path->push_front(vv);
                    vv = get_edge_to(vv);
                }
                path->push_front(get_start_vertex());
            }
            return iterable_ptr(path);
        }

    protected :
        void reset() override {
            if(get_graph().get_num_vertices() != get_visited().size()) {
                edge_to.clear();
                edge_to.resize(get_graph().get_num_vertices(), 0);
            } else {
                edge_to.assign(edge_to.size(), 0);
            }
            dfs_base<graph_type>::reset(get_graph().get_num_vertices());
        }

        void set_edge_to(const vertex_type& v,
                        const vertex_type& w) {
            edge_to[v] = w;
        }

        const vertex_type& get_edge_to(
                        const vertex_type& v) const {
            return edge_to[v];
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
                       gsetup_func_null,
                       [this](const graph_type& g,
                              const vertex_type& parent,
                              const vertex_type& v) {
                           set_edge_to(v, parent);
                       });
        }

    private :
        vector<vertex_type> edge_to;
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
