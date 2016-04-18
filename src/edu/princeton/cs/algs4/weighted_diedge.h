/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent a weighted directed edge in a graph.
 *
 ******************************************************************************/
#ifndef __WEIGHTED_DIEDGE_H__
#define __WEIGHTED_DIEDGE_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "object.h"
#include "weighted_edge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::istream;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

using edu::princeton::cs::algs4::weighted_edge_base;
using com::goffersoft::core::object;

/**
 **  the weighted_diedge_base class represents a
 **  weighted directed edge in an
 **  edge_weighted_graph. Each edge consists of two integers
 **  (naming the two vertices) and a real-value weight. The data type
 **  provides methods for accessing the two endpoints of the edge and
 **  the weight.
 **  2 cmp_by_weight methods compares 2 weighted_edges by
 **  ascending/descending order of weight.
 **
 **  Memory <= sizeof(weighted_edge) (16 bytes)
 **  This is am immutable class.
 **/
class weighted_diedge_base {
    public :
        using diedge_type = weighted_diedge_base;
        using edge_type = weighted_edge_base;
        using vertex_type = edge_type::vertex_type;
        using weight_type = edge_type::weight_type;

        weighted_diedge_base(const vertex_type& v,
                             const vertex_type& w,
                             const weight_type& weight) :
             e(v, w, weight) {}

        weighted_diedge_base(const edge_type& e) : e(e) {}

        weighted_diedge_base(istream& is = cin) : e(is) {}

        const vertex_type get_from() const {
            return e.get_first();
        }

        const vertex_type get_to() const {
            return e.get_second();
        }

        const weight_type get_weight() const {
            return e.get_weight();
        }

        operator edge_type() const {
            return e;
        }

        static int32_t cmp_by_weight(const diedge_type& lhs,
                                     const diedge_type& rhs) {
            return edge_type::cmp_by_weight(edge_type(lhs),
                                            edge_type(rhs));
        }

        static int32_t cmp_by_weight_descending(
                                     const diedge_type& lhs,
                                     const diedge_type& rhs) {
            return edge_type::cmp_by_weight_descending(
                                     edge_type(lhs),
                                     edge_type(rhs));
        }

        bool is_equal(const diedge_type& that) const {
            return e.is_equal(that.e);
        }
 
        string to_string() const {
            stringstream ss;

            ss << e.get_first() << " -> "
               << e.get_second() << " "
               << e.get_weight();

            return ss.str();
        }

    protected :

        const edge_type& get_edge() const {
            return e;
        }

    private :
        const edge_type  e;
};

/**
 **  The weighted_diedge class represents a directed edge as
 **  a set of 2 vertices and a real value.
 **  Each edge consists of two integers (naming the two vertices)
 **  and a real value weight.
 **  The data type provides methods for accessing the two endpoints
 **  of the edge and the weight associated with this edge.
 **  the weighted_diedge class derives from the weighted_diedge_base
 **  class and the object class.
 **  the object class provides the =, !=, <, >, <=, >= string
 **  operators.
 **  the weighted_diedge_base class provides data related
 **  to the end-points.
 **  the weighted_diedge class allows you to change the compare by
 **  function that would then change the behavior of the <, >, ...
 **  operations.
 **
 **  Memory <= sizeof(weighted_diedge_base)(16) + 8 + 8.
 **/
class weighted_diedge : public weighted_diedge_base, public object {
    public :
        using diedge_type = weighted_diedge;
        using base_edge_type = weighted_diedge_base;
        using cmp_func_type = int32_t(const base_edge_type&,
                                      const base_edge_type&);

        weighted_diedge(const vertex_type& v,
                    const vertex_type& w,
                    const weight_type& weight) :
             weighted_diedge_base(v, w, weight) {}

        weighted_diedge(const edge_type& e) :
             weighted_diedge_base(e){}

        weighted_diedge(istream& is = cin) :
             weighted_diedge_base(is) {}

        cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const diedge_type& that) const {
            return edge_type::cmp_by_weight(this->get_edge(),
                                            that.get_edge());
        }

    protected :
        bool is_equal(const object& obj) const override {
            const diedge_type& that = static_cast<const diedge_type&>(obj);
            return weighted_diedge_base::is_equal(that);
        }

        int32_t cmp(const object& obj) const override {
            const diedge_type& that = static_cast<const diedge_type&>(obj);
            return cmp(that);
        }

        string to_string() const override {
            return weighted_diedge_base::to_string();
        }

    private :
        cmp_func_type* cmp_func = &cmp_by_weight;
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

#endif /* __WEIGHTED_DIEDGE_H__ */
