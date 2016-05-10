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
#ifndef __SEARCH_BASE_H__
#define __SEARCH_BASE_H__

#include <functional>

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::function;
using std::stack;

template<typename G>
class search_base {
    public :
        using graph_type = G;
        using vertex_type = typename graph_type::vertex_type;

        using gproc_func_type = function<void(const graph_type& g,
                                             const vertex_type&,
                                             const vertex_type&)>;
        using gsetup_func_type = function<void(const graph_type& g,
                                             const vertex_type&)>;

        using gcheck_func_type = function<bool(const graph_type&,
                                               const vertex_type&)>;
        using gset_func_type = function<void(const graph_type&,
                                             const vertex_type&)>;

        using proc_func_type = function<void(const vertex_type&,
                                             const vertex_type&)>;
        using setup_func_type = function<void(const vertex_type&)>;
        using adj_func_type = function<bool(const vertex_type&,
                                            vertex_type&,
                                            bool)>;

        using check_func_type = function<bool(const vertex_type&)>;
        using set_func_type = function<void(const vertex_type&)>;

        static const gsetup_func_type gsetup_func_null; 
        static const gproc_func_type gproc_func_null; 

        static const setup_func_type setup_func_null; 
        static const proc_func_type proc_func_null; 
};

template <typename G>
const typename search_base<G>::gsetup_func_type
    search_base<G>::gsetup_func_null =
        [](const typename search_base<G>::graph_type& g,
           const typename search_base<G>::vertex_type& v){};

template <typename G>
const typename search_base<G>::gproc_func_type
    search_base<G>::gproc_func_null =
        [](const typename search_base<G>::graph_type& g,
           const typename search_base<G>::vertex_type& start_vertex,
           const typename search_base<G>::vertex_type& v){};

template <typename G>
const typename search_base<G>::setup_func_type
    search_base<G>::setup_func_null =
        [](const typename search_base<G>::vertex_type& v){};

template <typename G>
const typename search_base<G>::proc_func_type
    search_base<G>::proc_func_null =
        [](const typename search_base<G>::vertex_type& start_vertex,
           const typename search_base<G>::vertex_type& v){};

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

#endif /* __SEARCH_BASE_H__ */
