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
#ifndef __CC_H__
#define __CC_H__

#include <memory>

#include "dfs_base.h"
#include "path.h"
#include "udgraph.h"
#include "weighted_udgraph.h"
#include "flow_network.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::unique_ptr;

using edu::princeton::cs::algs4::path_compute;
using edu::princeton::cs::algs4::dfs_base;

/**
 ** The cc class represents a data type for
 ** determining the connected components in
 ** a undirected (weighted, non-weighted,
 ** flow-network) graph.
 ** 1) The id operation determines in which
 **    connected component a given vertex lies
 ** 2) The connected operation determines whether
 **    two vertices are in the same connected
 **    component
 ** 3) the count operation determines the number
 **    of connected components
 ** 4) size operation determines the number of
 **    vertices in the connect component containing
 **    a given vertex.
 **
 ** The component identifier of a connected component
 ** is one of the vertices in the connected component:
 ** two vertices have the same component identifier if
 ** and only if they are in the same connected component.
 ** 
 ** This implementation uses depth-first search.
 **
 ** The constructor takes time proportional to V + E
 ** (in the worst case),
 ** where V is the number of vertices and
 ** E is the number of edges.
 ** Afterwards, the id, count, connected, and size
 ** operations take constant time.
 **
 **/
template<typename G>
class cc : public dfs_base<G>,
           public path_compute<G> {
    public :
        using typename dfs_base<G>::graph_type;
        using typename dfs_base<G>::vertex_type;
        using component_id_type = vertex_type;
        using path_compute<G>::is_eager;
        using path_compute<G>::is_lazy;
        using path_compute<G>::compute;
        using path_compute<G>::get_graph;
        using path_compute<G>::validate_input;
        using dfs_base<G>::get_visited;
        using dfs_base<G>::set_visited;
        using dfs_base<G>::visited;
        using dfs_base<G>::reset;
        using dfs_base<G>::gsetup_func_null;
        using dfs_base<G>::gproc_func_null;
        using typename path_compute<G>::iterable;
        using iterable_ptr = unique_ptr<iterable>;

        /**
         ** Computes the connected components of a graph G.
         **
         ** need to initialize all entries of the size array
         ** to 0 due to increment operation
         **
         ** param : graph_type
         **/
        cc(const graph_type& g,
           bool defer = false) :
                 dfs_base<graph_type>(g.get_num_vertices()),
                 path_compute<G>(g, 0, defer),
                 id_array(new array_type[g.get_num_vertices()]),
                 size_array(new array_type[g.get_num_vertices()]()) {

            static_assert(is_same<G, udgraph>::value ||
                          is_same<G, weighted_udgraph>::value ||
                          is_same<G, flow_network>::value,
                          "G must be one of udgraph,"
                          "weighted_udgraph, flow_network");

            if(is_eager()) {
                compute();
            }
        }
        
        /**
         ** Returns the number of connected components
         ** in the graph G
         **
         ** return : the number of connected components
         ** in the graph G
         **/
        size_t get_count() {
            if(is_lazy()) {
                compute();
            }

            return num_cc;
        }

        /**
         ** Returns the component id of the connected component
         ** containing vertex v.
         **
         ** param :  v the vertex
         ** return : the component id of the connected component
         **          containing vertex v
         ** throws  : invalid_argument exception unless
         **           0 <= v < G.num_vertices()
         **/
        const component_id_type& get_id(const vertex_type& v) {
            validate_input(v);
            if(is_lazy()) {
                compute();
            }
            return id_array[v];
        }

        /**
         ** Returns the number of vertices in the connected
         ** component containing vertex v.
         **
         ** param :  v the vertex
         ** return : the number of vertices in the connected
         **          component containing vertex v
         ** throws  : invalid_argument exception unless
         ** 0 <= v < G.num_vertices()
         **/
         size_t get_size(const vertex_type& v) {
            validate_input(v);
            if(is_lazy()) {
                compute();
            }
            return size_array[id_array[v]];
         }

        /**
         ** Returns true if vertices v and w are in the same
         ** connected component.
         **
         ** param : v one vertex
         ** param : w the other vertex
         ** return : true if vertices v and w are in the same
         **          connected component; false otherwise
         ** throws : invalid_argument exception unless
         **          both 0 <= v < G.num_vertices() and
         **               0 <= w < G.num_vertices()
         **/
        const bool is_connected(const vertex_type& v,
                                const vertex_type& w) {
            validate_input(v, w);
            if(is_lazy()) {
                compute();
            }
            return (id_array[v] == id_array[w]);
        }

        /**
         ** Returns the vertices in the connected component .
         **
         ** param :  the connected component id 
         **          0 <= cid < get_count()
         ** return : the the vertices in the connected
         **          component s an iterable
         ** throws  : invalid_argument exception unless
         **           0 <= cid < get_count()
         **/
        const iterable_ptr get_cc(const component_id_type& cid) {
            if(is_lazy()) {
                compute();
            }
            validate_component_id(cid);
            iterable* cc_array = new iterable();
            for(vertex_type v = 0; v < get_graph().get_num_vertices(); v++) {
                if(id_array[v] == cid) {
                    cc_array->push_back(v);
                }
            }
            return iterable_ptr(cc_array);
        }

    protected :
        using array_type = component_id_type;
        using array_type_ptr = unique_ptr<array_type[]>;

        void reset() override {
            if(get_graph().get_num_vertices() !=
               get_visited().size()) {
                id_array.reset(new array_type[
                               get_graph().get_num_vertices()]);
               // need to initialize all entries of the size array
               // to 0 due to increment operation
                size_array.reset(new array_type[
                                 get_graph().get_num_vertices()]());
            } else {
               // need to initialize all entries of the size array
               // to 0 due to increment operation
                memset(size_array.get(), 0x0,
                       get_graph().get_num_vertices()*sizeof(array_type));
            }
            dfs_base<graph_type>::reset(get_graph().get_num_vertices());
        }

        void compute_path(const graph_type& g, const vertex_type& s) override {
            num_cc = 0;
            for(size_t v = 0; v < g.get_num_vertices(); v++){
                if(!visited(v)) {
                    dfs<graph_type>::generic_dfs(g, v,
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            set_visited(v);
                        },
                        [this](const graph_type& g,
                               const vertex_type& v) {
                            return visited(v);
                        },
                        [this](const graph_type&,
                               const vertex_type& v) {
                            id_array[v] = num_cc;
                            size_array[num_cc]++;
                        },
                        gproc_func_null,
                        gproc_func_null,
                        gsetup_func_null);
                    num_cc++;
                }
            }
        }

    private :
        /**
         ** Internal method to validate the component id
         **
         ** params  : cid the integer representing component 
         ** throws  : invalid_argument exception unless
         **           0 <= cid < get_count()
         **/
        void validate_component_id(const component_id_type& cid) const {
            if (cid >= num_cc) {
                throw invalid_argument("cid >= get_count()");
            }
        }

        array_type_ptr id_array;   //id_array[v] = id of
                                   //connected component
                                   //containing v

        array_type_ptr size_array; //size_array[id] =
                                   //number of vertices
                                   //in a given component

        size_t num_cc;             // number of connected
                                   //components
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

#endif /* __CC_H__ */
