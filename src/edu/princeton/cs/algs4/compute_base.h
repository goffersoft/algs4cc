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
#ifndef __COMPUTE_BASE_H__
#define __COMPUTE_BASE_H__

#include <functional>

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::function;
using std::stack;

/**
 ** The compute_base class represents the base class
 ** for all search algorithms. This class contains
 ** methods and data that to control the execution
 ** of a search algorithm
 ** Specifcally
 ** 1) lazy vs eager evaluation 
 ** 2) forced execution of the search algorithm 
 **
 ** eager evalution - the search algorithm is executed in the 
 **                   constructor and whenever the following changes
 **                   a) changing from lazy to eager. (is/set_eager method)
 **                   b) explicitly calling the recompute method
 **
 ** is_eager() method checks whether the eager mode is set.
 **  
 ** lazy evalution - the search algorithm is not executed in the 
 **                   constructor.
 **                   the search algorithm is executed whenever the
 **                   data dependent on the search algorithm is requested
 **                   by a client.
 **
 ** recompute method - forces a re-run of the search algorithm.
 **
 ** derived classes must override the following methods.
 **     a) compute method
 **                 This is a protected method.
 **                 this methods essentially executes the
 **                 search algorithm.
 **                 in the eager mode, This method must
 **                 be called in the constructor of the
 **                 derived concrete class. 
 **                 in the lazy mode, This method must
 **                 be called in the data dependant methods
 **                 the get_eval/set_eval/clear_eval methods
 **                 determine/control if the search algorithm
 **                 has already been executed or if it needs
 **                 to be run again. The compute method must
 **                 check/set this variable accordingly.
 **                 to avoid unnecessary execution of the search
 **                 algorithm.
 **     b) reset method -
 **                 This is a protected method.
 **                 re-initialize any data structures defined
 **                 in the concrete derived classes before
 **                 running the search algorithm
 **/
class compute_base {
    public :
        compute_base(bool defer) :
            lazy(defer), eval(false) {}

        bool is_lazy() const { return lazy; }

        bool is_eager() const { return !is_lazy(); }

        void set_lazy() {
            if(lazy == true) {
                return;
            }
            lazy = true;
            eval = false;
            reset();
        }

        void set_eager() {
            if(lazy == false) {
                return;
            }
            lazy = false;
            eval = false;
            reset();
            compute();
        }

        void recompute() {
            eval = false;
            reset();
            compute();
        }

    protected :
        virtual void reset() = 0;
        virtual void compute() = 0;
        bool get_eval() const { return eval; }
        void set_eval() { eval = true; }
        void clear_eval() { eval = false; }

    private :
        bool lazy;
        bool eval;
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

#endif /* __COMPUTE_BASE_H__ */
