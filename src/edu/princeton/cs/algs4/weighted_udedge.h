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
#include "udedge.h"
#include "bag.h"
#include "cstdin.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::ostream;
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
using com::goffersoft::core::utils;
using edu::princeton::cs::algs4::weighted_edge_base;
using edu::princeton::cs::algs4::udedge_base;

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
class weighted_udedge_base : public udedge_base {
    public :
        using udedge_type = weighted_udedge_base;
        using udedge_base_type = udedge_base;
        using vertex_type = udedge_base_type::vertex_type;
        using weight_type = weighted_edge_base::weight_type;

        weighted_udedge_base(const vertex_type& v,
                             const vertex_type& w,
                             const weight_type& weight) :
             udedge_base(v, w), weight(weight) {}

        weighted_udedge_base(const weighted_edge_base& e) :
             udedge_base(e.get_first(),
                         e.get_second()),
                         weight(e.get_weight()) {}

        weighted_udedge_base(istream& is = cin) :
             udedge_base(is),
             weight(weighted_edge_base::read_weight(is)) {}

        const weight_type get_weight() const {
            return weight;
        }

        operator weighted_edge_base() const {
            vertex_type x = get_either();
            vertex_type y = get_other(x);
            return weighted_edge_base(x, y, weight);
        }

        bool equals(const udedge_type& that) const {
            return (udedge_base::equals(that) &&
                    utils::cmp_equal(weight,
                                    that.weight));
        }

        operator string() const {
            stringstream ss;

            ss << udedge_base_type::operator string() 
               << " " << weight;

            return ss.str();
        }

        bool operator ==(const udedge_type& that) const {
            if(this == &that)
                return true;

            return (cmp_by_weight(*this, that) == 0);
        }

        bool operator !=(const udedge_type& that) const {
            return !(*this == that);
        }

        friend ostream& operator <<(ostream& os,
                                   const udedge_type& e) {
            return os << string(e);
        }

        static int32_t cmp_by_weight(const udedge_type& lhs,
                                     const udedge_type& rhs) {
            return utils::cmp(lhs.weight, rhs.weight);
        }

        static int32_t cmp_by_weight_descending(
                                     const udedge_type& lhs,
                                     const udedge_type& rhs) {
            return -utils::cmp(lhs.weight, rhs.weight);
        }

    private :
        const weight_type weight;
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
        using object::operator string;
        using object::equals;
        using object::operator ==;
        using object::operator !=;
        using udedge_type = weighted_udedge;
        using udedge_base_type = weighted_udedge_base;
        using cmp_func_type = int32_t(const udedge_base_type&,
                                      const udedge_base_type&);

        weighted_udedge(const vertex_type& v,
                        const vertex_type& w,
                        const weight_type& weight) :
             weighted_udedge_base(v, w, weight) {}

        weighted_udedge(const weighted_edge_base& e) :
             weighted_udedge_base(e) {}

        weighted_udedge(istream& is = cin) :
             weighted_udedge_base(is) {}

        cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const udedge_type& that) const {
            return cmp_func(*this, that);
        }

    protected :
        bool is_equal(const object& obj) const override {
            const udedge_type& that = static_cast<const udedge_type&>(obj);
            return weighted_udedge_base::equals(that);
        }

        int32_t cmp(const object& obj) const override {
            const udedge_type& that = static_cast<const udedge_type&>(obj);
            return cmp(that);
        }

        string to_string() const override {
            return weighted_udedge_base::operator string();
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

#endif /* __WEIGHTED_UDEDGE_H__ */
