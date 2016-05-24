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
#ifndef __DFS_BASE_H__
#define __DFS_BASE_H__

#include <iostream>
#include <vector>
#include <stack>

#include "search_base.h"
#include "graph_base.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::vector;
using std::stack;

using edu::princeton::cs::algs4::search_base;
using edu::princeton::cs::algs4::graph_base;

/**
 ** The base for all dfs search algorithms 
 **
 ** implements the generic dfs algorithm
 ** (non-recursvie version)
 **/
template<typename G>
class dfs_base : public search_base<G> {
    public :
        using typename search_base<G>::graph_type;
        using typename search_base<graph_type>::vertex_type;
        using typename search_base<graph_type>::set_func_type;
        using typename search_base<graph_type>::check_func_type;
        using typename search_base<graph_type>::adj_func_type;
        using typename search_base<graph_type>::proc_func_type;
        using typename search_base<graph_type>::setup_func_type;
        using typename search_base<graph_type>::gset_func_type;
        using typename search_base<graph_type>::gcheck_func_type;
        using typename search_base<graph_type>::gproc_func_type;
        using typename search_base<graph_type>::gsetup_func_type;
        using search_base<graph_type>::setup_func_null;
        using search_base<graph_type>::proc_func_null;
        using search_base<graph_type>::gsetup_func_null;
        using search_base<graph_type>::gproc_func_null;

        /** this is a non recursive implementation of the dfs algorithm
         ** args
         **     s - start_vertex
         **     set_visited(node) -
         **         set the node to visited for future reference 
         **         check to see if a node is visited or not
         **     get_adj(parent, node, first_flag ) -
         **         Get the next adj node associated with this parent node.
         **         first_flag is  set to true to indicate first call to
         **         this function for a given parent. first_flag set to false
         **         otherwise.
         **         The function sets node to the next adjacent node to process
         **     node_pre_proc(parent, node) -
         **         called before starting dfs on a node. 
         **     init(node) -
         **         a particular node starting dfs. (no adjacents visited)
         **     complete(node) -
         **         a particular node starting dfs.(all adjacents visited)
         **     node_post_proc(parent, node) -
         **         done with dfs on a node. 
         **
         ** pseudo code for the recursive dfs
         ** dfs_recursive(s, set_visited_func,
         **               visited_func, get_adj_func,
         **               init_func, node_pre_proc_func,
         **               node_post_proc_func, complete_func)
         **     set_visited_func(s);
         **     node_pre_proc_func(s, s);
         **     init_func(s);
         **     vertex_type a = s;
         **     bool first = true;
         **     while(get_adj(s, a, first)) {
         **         first = false;
         **         if(!visited(a)) {
         **             node_pre_proc_func(s, a);
         **             generic_dfs(a, set_visited_func, visited_func,
         **                         get_adj_func, init_func, node_pre_proc_func,
         **                         node_post_proc_func, complete_func);
         **             node_post_proc_func(s, a);
         **     }
         **     complete_func(s);
         **     node_post_proc_func(s, s);
         ** }
         **/
        static void generic_dfs(const vertex_type& s,
                                const set_func_type& set_visited,
                                const check_func_type& visited,
                                const adj_func_type& get_adj,
                                const setup_func_type& init = setup_func_null,
                                const proc_func_type& node_pre_proc = proc_func_null,
                                const proc_func_type& node_post_proc = proc_func_null,
                                const setup_func_type& complete = setup_func_null) {
            stack<vertex_type> dfs_stack;
            dfs_stack.emplace(const_cast<vertex_type&>(s));
            node_pre_proc(s, s);
            init(s);
            set_visited(s);
            vertex_type* parent = &dfs_stack.top();
            vertex_type v;
            bool first = true;
            while(!dfs_stack.empty()) {
                if (get_adj(*parent, v, first)) {
                    if(!visited(v)) {
                        node_pre_proc(*parent, v);
                        dfs_stack.emplace(v);
                        parent = &dfs_stack.top();
                        first = true;
                        init(v);
                        set_visited(v);
                    } else {
                        first = false;
                    }
                } else {
                    vertex_type tmp = dfs_stack.top();
                    dfs_stack.pop();
                    first = false;
                    complete(tmp);
                    if(!dfs_stack.empty()) {
                        parent = &dfs_stack.top();
                        node_post_proc(*parent, tmp);
                    } else {
                        node_post_proc(tmp, tmp);
                    }
                }
            }
        }

        /** This api customizes the generic_dfs api and 
         ** should be used for all graph related dfs searches
         ** (that is, if the graph is pre-determined and available)
         **/
        static void generic_dfs(const graph_type& g,
                                const vertex_type& s,
                                const gset_func_type& set_visited,
                                const gcheck_func_type& visited,
                                const gsetup_func_type& init = gsetup_func_null,
                                const gproc_func_type& node_pre_proc = gproc_func_null,
                                const gproc_func_type& node_post_proc = gproc_func_null,
                                const gsetup_func_type& complete = gsetup_func_null) {
            stack<typename graph_type::adj_const_iterator> its;
            typename graph_type::adj_const_iterator it = g.get_adj(0).begin();
            generic_dfs(s,
                        [&g, &set_visited](const vertex_type& v) {
                            set_visited(g, v);
                        },
                        [&g, &visited](const vertex_type& v) {
                            return visited(g, v);
                        },
                        [&g, &its, &it](const vertex_type& parent,
                                        vertex_type& v, bool first) {
                            if(first) {
                                it = g.get_adj(parent).begin();
                            }
                            if(it == g.get_adj(parent).end()) {
                                if(!first) {
                                    its.pop();
                                }
                                if(!its.empty()) {
                                    it = its.top();
                                }
                                return false;
                            }
                            v = graph_base::get_vertex(parent, *it);
                            ++it;
                            if(first) {
                                its.push(it);
                            }
                            return true; 
                        },
                        [&g, &init](const vertex_type& v) {
                        #ifdef __DFS_DEBUG__
                            std::cout << "init : dfs on v="
                                      << v << std::endl;
                        #endif
                            init(g, v);
                    
                        },
                        [&g, &node_pre_proc](const vertex_type& parent,
                                             const vertex_type& v) {
                        #ifdef __DFS_DEBUG__
                            if(&v == &parent) {
                                std::cout << "node_pre_proc : *** dfs start : "
                                          << " start vertex = " << v
                                          << " ***" << std::endl;
                            } else {
                                std::cout << "node_pre_proc : starting dfs on v="
                                          << v << " parent="
                                          << parent << std::endl;
                            }
                        #endif
                            node_pre_proc(g, parent, v);
                        },
                        [&g, &node_post_proc](const vertex_type& parent,
                                              const vertex_type& v) {
                        #ifdef __DFS_DEBUG__
                            if(&v == &parent) {
                                std::cout << "node_pre_proc : *** dfs end : "
                                          << " start vertex = " << v
                                          << " ***" << std::endl;
                            } else {
                                std::cout << "node_post_proc : completed dfs on v="
                                          << v << " parent="
                                          << parent << std::endl;
                            }
                        #endif
                            node_post_proc(g, parent, v);
                        },
                        [&g, &complete](const vertex_type& v) {
                        #ifdef __DFS_DEBUG__
                            std::cout << "complete : dfs on v="
                                      << v << std::endl;
                        #endif
                            complete(g, v);
                        });
        }

    protected :
        dfs_base(const size_t num_vertices) {
            visited_bitmap = vector<bool>(num_vertices);
        }

        void reset(size_t num_vertices) {
            if(num_vertices != visited_bitmap.size()) {
                visited_bitmap.clear();
                visited_bitmap.resize(num_vertices, false);
            } else {
                visited_bitmap.assign(visited_bitmap.size(), false);
            }
        }

        vector<bool>& get_visited() {
            return visited_bitmap;
        }

        bool visited(const vertex_type& v) const {
            return visited_bitmap[v];
        }

        void set_visited(const vertex_type& v) {
            visited_bitmap[v] = true;
        }

        void clear_visited(const vertex_type& v) {
            visited_bitmap[v] = false;
        }

    private :
        vector<bool> visited_bitmap;
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

#endif /* __DFS_BASE_H__ */
