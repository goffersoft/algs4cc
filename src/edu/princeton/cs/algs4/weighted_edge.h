/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent a weighted_edge in a graph.
 *
 ******************************************************************************/
#ifndef __WEIGHTED_EDGE_H__
#define __WEIGHTED_EDGE_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "object.h"
#include "cstdin.h"
#include "edge.h"

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

using edu::princeton::cs::algs4::cstdin;
using edu::princeton::cs::algs4::edge_base;
using com::goffersoft::core::object;
using com::goffersoft::core::utils;

/**
 **  the weighted_edge_base class represents a weighted edge in an
 **  edge_weighted_graph. Each edge consists of two integers
 **  (naming the two vertices) and a real-value weight. The data type
 **  provides methods for accessing the two endpoints of the edge and
 **  the weight.
 **  2 cmp_by_weight methods compares 2 weighted_edges by
 **  ascending/descending order of weight.
 **
 **  Memory <= 16 bytes(sizeof(edge_base) + 8)
 **  This is am immutable class.
 **/
class weighted_edge_base : public edge_base {
    public :
        using edge_type = weighted_edge_base;
        using weight_type = double;

        weighted_edge_base(const vertex_type& first,
                           const vertex_type& second,
                           const weight_type& weight) :
             edge_base(first, second),
             weight(weight) {}

        weighted_edge_base(istream& is = cin) :
           edge_base(is),
           weight(read_weight(is)) {}

        const weight_type get_weight() const {
            return weight;
        }

        bool equals(const edge_type& that) const {
            return (edge_base::equals(that) &&
                    utils::cmp_equal(this->weight,
                                     that.weight));
        }
 
        operator string() const {
            stringstream ss;

            ss << edge_base::operator string() << " ";
            utils::print_data(ss, get_weight());

            return ss.str();
        }

        bool operator ==(const edge_type& that) const {
            if(this == &that)
                return true;

            return cmp_by_weight(*this, that);
        }

        bool operator !=(const edge_type& that) const {
            return !(*this == that);
        }

        friend ostream& operator <<(ostream& os,
                                   const edge_type& e) {
            return os << string(e);
        }

        static weight_type read_weight(istream& is = cin) {
            return cstdin::read_double(is);
        }

        static int32_t cmp_by_weight(const edge_type& lhs,
                                     const edge_type& rhs) {
            return utils::cmp(lhs.weight, rhs.weight);
        }

        static int32_t cmp_by_weight_descending(
                                     const edge_type& lhs,
                                     const edge_type& rhs) {
            return -utils::cmp(lhs.weight, rhs.weight);
        }
    private :
        const weight_type weight;
};

/**
 **  The weighted_edge class represents a edge as a set of 2 vertices.
 **  Each edge consists of two integers (naming the two vertices)
 **  and a real value weight.
 **  The data type provides methods for accessing the two endpoints
 **  of the edge and the weight associated with this edge.
 **  the weighted_edge class derives from the weighted_edge_base
 **  class and the object class.
 **  the object class provides the =, !=, <, >, <=, >= string
 **  operators. 
 **  the weighted_edge_base class provides data related
 **  to the end-points.
 **  the weighted_edge class allows you to change the compare by
 **  function that would then change the behavior of the <, >, ...
 **  operations.
 **
 **  Memory <= 32 bytes (sizeof(weighted_edge_base) + 8 + 8).
 **/
class weighted_edge : public weighted_edge_base, public object {
    public :
        using object::operator string;
        using object::equals;
        using object::operator ==;
        using object::operator !=;
        using edge_type = weighted_edge;
        using base_edge_type = weighted_edge_base;
        using cmp_func_type = int32_t(const base_edge_type&,
                                      const base_edge_type&);

        weighted_edge(const vertex_type& first,
                      const vertex_type& second,
                      const weight_type& weight) :
             weighted_edge_base(first, second, weight) {}

        weighted_edge(istream& is = cin) :
           weighted_edge_base(is) {}

        cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const edge_type& that) const {
            return cmp_func(*this, that);
        }

    protected:
        bool is_equal(const object& obj) const override {
            const edge_type& that = static_cast<const edge_type&>(obj);

            return weighted_edge_base::equals(that);
        }

        int32_t cmp(const object& obj) const override {
            const edge_type& that = static_cast<const edge_type&>(obj);

            return cmp(that);
        }
 
        string to_string() const override {
            return weighted_edge_base::operator string();
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

#endif /* __WEIGHTED_EDGE_H__ */
