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
#ifndef __PATH_H__
#define __PATH_H__

#include <deque>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>

#include "compute_base.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::unique_ptr;
using std::function;
using std::deque;
using std::invalid_argument;

using edu::princeton::cs::algs4::compute_base;

/**
 ** The path_compute class represents the base class
 ** for all graph search algorithms. This class contains
 ** methods and data that apply to all grpah types and 
 ** all search algorithms. This is an abstract class.
 ** Specifcally
 ** 1) setting a new start vertex.
 ** 2) lazy vs eager evaluation (inherited from compute_base)
 ** 3) forced execution of the search algorithm 
 **    (inherited from compute_base)
 **
 ** eager evalution -
 **               the search algorithm is executed in the 
 **               constructor and whenever the following changes
 **               a) start vertex (set/get)_start_vertex
 **               b) changing from lazy to eager. (is/set_eager method)
 **                  (inherited from the compute_base class)
 **               c) explicitly calling the recompute method
 **                  (inherited from the compute_base class)
 **
 ** is_eager() method checks whether the eager mode is set.
 **                  (inherited from the compute_base class)
 **  
 ** lazy evalution - the search algorithm is not executed in the 
 **                   constructor.
 **                   the search algorithm is executed whenever the
 **                   data dependent on the search algorithm is requested
 **                   by a client.
 **                  (inherited from the compute_base class)
 **
 ** recompute method - forces a re-run of the search algorithm.
 **                    (inherited from the compute_base class)
 **
 ** This class implements the abstract method
 ** inherited from the compute_base class
 **    compute method
 **
 ** derived classes must override the following methods.
 **     a) reset method - This is a protected method
 **                 (inherited from the compute_base class)
 **                 re-initialize any data structures defined
 **                 in the concrete derived classes before
 **                 running the search algorithm
 **     b) compute_path method -
 **           This is a protected method must be overridden
 **           by the concrete derived classes.
 **  
 ** All implementation of search algorithms should inherit from this 
 ** abstract class.
 **
 ** The protected constructor method for this class provides way to
 ** set the eager/lazy mode via a boolean variable (defer)
 ** defer = true => lazy
 ** defer = false => eager
 **/
template<typename G>
class path_compute : public compute_base {
    public :
        using graph_type = G;
        using vertex_type = typename graph_type::vertex_type;
        using iterable = deque<vertex_type>;

        vertex_type get_start_vertex() const { return vstart; }

        void set_start_vertex(const vertex_type& v) {
            if(get_start_vertex() == v) {
                return;
            }
            validate_input(v);
            vstart = v;
            reset();
            clear_eval();
            if(is_eager()) {
                compute();
            }
        }

        const graph_type& get_graph() const { return *gptr; }

        void set_graph(const graph_type& g) {
            gptr = const_cast<graph_type*>(&g); 
            if (get_start_vertex() >=
                g.get_num_vertices()) {
                set_start_vertex(0);
            }
            clear_eval();
            reset();
            if(is_eager()) {
                compute();
            }
        }
    protected :

        path_compute(const graph_type& g,
                     const vertex_type s,
                     bool defer = false) :
                       compute_base(defer),
                       vstart(s),
                       gptr(const_cast<graph_type*>(&g)) {}

        /**
         ** Internal method to validate the input data
         **
         ** params  : v the integer representing one vertex 
         ** throws  : invalid_argument exception unless
         **           0 <= v < G.num_vertices()
         **/
        void validate_input(const vertex_type& v) const {
            if (v >= get_graph().get_num_vertices()) {
                throw invalid_argument("v >= G.num_Vertices()");
            }
        }

        /**
         ** Internal method to validate the input data
         **
         ** param  : p the integer representing one vertex 
         ** param  : q the integer representing the other vertex
         ** throws : invalid_argument exception unless
         **          both 0 <= v < G.num_vertices() and
         **               0 <= w < G.num_vertices()
         **/
        void validate_input(const vertex_type& v,
                           const vertex_type& w) const {
            if ( (v >= get_graph().get_num_vertices()) ||
                 (w >= get_graph().get_num_vertices())) {
                throw invalid_argument( "invalid argument :"
                                         "v and w >= G.num_Vertices()");
            } else if (v >= get_graph().get_num_vertices()) {
                throw invalid_argument( "invalid argument :"
                                         "v >= num_sites");
            } else if (w >= get_graph().get_num_vertices()) {
                throw invalid_argument( "invalid argument :"
                                         "w >= num_sites");
            }
        }

        virtual void compute_path(const graph_type& g,
                                  const vertex_type& s) = 0;

        void compute() override {
            if(!get_eval()) {
                compute_path(get_graph(),
                             get_start_vertex());
                set_eval();
            }
        }

    private :
        vertex_type vstart;
        graph_type* gptr;
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

#endif /* __PATH_H__ */
