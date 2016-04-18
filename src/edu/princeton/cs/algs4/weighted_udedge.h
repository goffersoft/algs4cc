/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent a weighted undirected edge in a graph.
 *
 ******************************************************************************/
#ifndef __WEIGHTED_UDEDGE_H__
#define __WEIGHTED_UDEDGE_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "object.h"
#include "weighted_edge.h"
#include "bag.h"
#include "cstdin.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::istream;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::invalid_argument;
using std::move;

using edu::princeton::cs::algs4::bag;
using edu::princeton::cs::algs4::cstdin;
using com::goffersoft::core::object;
using edu::princeton::cs::algs4::weighted_edge_base;

/**
 **  the weighted_udedge_base class represents a
 **  weighted undirected edge in an
 **  edge_weighted_graph. Each edge consists of two integers
 **  (naming the two vertices) and a real-value weight. The data type
 **  provides methods for accessing the two endpoints of the edge and
 **  the weight.
 **  cmp_by_weight method compares 2 weighted_edges by
 **  ascending order of weight.
 **
 **  Memory <= sizeof(weighted_edge) (16 bytes)
 **  This is am immutable class.
 **/
class weighted_udedge_base {
    public :
        using udedge_type = weighted_udedge_base;
        using edge_type = weighted_edge_base;
        using vertex_type = edge_type::vertex_type;
        using weight_type = edge_type::weight_type;

        weighted_udedge_base(const vertex_type& v,
                             const vertex_type& w,
                             const weight_type& weight) :
             e(v, w, weight) {}

        weighted_udedge_base(const edge_type& e) : e(e) {}

        weighted_udedge_base(istream& is = cin) : e(is) {}

        const vertex_type get_either() const {
            return e.get_first();
        }

        const vertex_type get_other(const vertex_type& v) const {
            if(e.get_first() == v) {
                return e.get_second();
            } else if(e.get_second() == v) {
                return e.get_first();
            } else {
                throw invalid_argument( "invalid argument : v"
                                        "not member of this edge");
            }
        }

        const weight_type get_weight() const {
            return e.get_weight();
        }

        operator edge_type() const {
            return e;
        }

        static int32_t cmp_by_weight(const udedge_type& lhs,
                                     const udedge_type& rhs) {
            return edge_type::cmp_by_weight(edge_type(lhs),
                                            edge_type(rhs));
        }

        static int32_t cmp_by_weight_descending(
                                     const udedge_type& lhs,
                                     const udedge_type& rhs) {
            return edge_type::cmp_by_weight_descending(
                             edge_type(lhs),
                             edge_type(rhs));
        }

        bool is_equal(const udedge_type& that) const {
            return e.is_equal(that.e);
        }
 
        string to_string() const {
            stringstream ss;

            ss << e.get_first() << " <-> "
               << e.get_second() << " "
               << e.get_weight();

            return ss.str();
        }

    protected :

        const edge_type& get_edge() const {
            return e;
        }

    private :
        const edge_type e;
};

/**
 **  The weighted_udedge class represents a undirected edge as
 **  a set of 2 vertices and a real value.
 **  Each edge consists of two integers (naming the two vertices)
 **  and a real value weight.
 **  The data type provides methods for accessing the two endpoints
 **  of the edge and the weight associated with this edge.
 **  the weighted_udedge class derives from the weighted_udedge_base
 **  class and the object class.
 **  the object class provides the =, !=, <, >, <=, >= string
 **  operators.
 **  the weighted_udedge_base class provides data related
 **  to the end-points.
 **  the weighted_udedge class allows you to change the compare by
 **  function that would then change the behavior of the <, >, ...
 **  operations.
 **
 **  Memory <= sizeof(weighted_udedge_base)(16) + 8 + 8.
 **/
class weighted_udedge : public weighted_udedge_base, public object {
    public :
        using udedge_type = weighted_udedge;
        using base_edge_type = weighted_udedge_base;
        using cmp_func_type = int32_t(const base_edge_type&,
                                      const base_edge_type&);

        weighted_udedge(const vertex_type& v,
                        const vertex_type& w,
                        const weight_type& weight) :
             weighted_udedge_base(v, w, weight) {}

        weighted_udedge(const edge_type& e) :
             weighted_udedge_base(e) {}

        weighted_udedge(istream& is = cin) :
             weighted_udedge_base(is) {}

        const cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(const cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const udedge_type& that) const {
            return cmp_func(*this, that);
        }

    protected :
        bool is_equal(const object& obj) const override {
            const udedge_type& that = static_cast<const udedge_type&>(obj);
            return weighted_udedge_base::is_equal(that);
        }

        int32_t cmp(const object& obj) const override {
            const udedge_type& that = static_cast<const udedge_type&>(obj);
            return cmp(that);
        }

        string to_string() const override {
            return weighted_udedge_base::to_string();
        }

    private :
        const cmp_func_type* cmp_func = &cmp_by_weight;
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

#endif /* __WEIGHTED_UDEDGE_H__ */
