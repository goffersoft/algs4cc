/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent an edge in a graph.
 *
 ******************************************************************************/
#ifndef __EDGE_H__
#define __EDGE_H__

#include <iostream>
#include <sstream>
#include <string>

#include "object.h"
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

using edu::princeton::cs::algs4::cstdin;
using com::goffersoft::core::object;

/**
 **  The edge_base class represents a edge and is the base class
 **  Each edge consists of two integers (naming the two vertices).
 **  The data type provides methods for accessing the two endpoints
 **  of the edge.  
 **  2 comparision functions are provided incase this class needs to
 **  be sorted by the first or the second end-point.
 **
 **  Memory <= 8 bytes (4 + 4).
 **  This is an immutable class.
 **/
class edge_base {
    public :
        using vertex_type = uint32_t;
        using edge_type = edge_base;

        edge_base(const vertex_type& first,
                  const vertex_type& second) :
             first(first),
             second(second) {}

        edge_base(istream& is = cin) :
            first(cstdin::read_uint32(is)),
            second(cstdin::read_uint32(is)) {}

        const vertex_type get_first() const {
            return first;
        }

        const vertex_type& get_second() const {
            return second;
        }

        static int32_t cmp_by_first_vertex(
                           const edge_type& lhs,
                           const edge_type& rhs) {
            if(&lhs == &rhs)
                return 0;
            return utils::cmp(lhs.get_first(), lhs.get_second(),
                              rhs.get_first(), rhs.get_second());
        };

        static int32_t cmp_by_second_vertex(
                           const edge_type& lhs,
                           const edge_type& rhs) {
            if(&lhs == &rhs)
                return 0;
            return utils::cmp(lhs.get_second(), lhs.get_first(),
                              rhs.get_second(), rhs.get_first());
        };

        bool is_equal(const edge_type& that) const {
            return ( this->first == that.first &&
                     this->second == that.second);
        }

        string to_string() const {
            stringstream ss;
            utils::print_data(ss, first) << " ?-? ";
            utils::print_data(ss, second);

            return ss.str();
        }

    private :
        const vertex_type first;
        const vertex_type second;
};

/**
 **  The edge class represents a edge as a set of 2 vertices.
 **  Each edge consists of two integers (naming the two vertices).
 **  The data type provides methods for accessing the two endpoints
 **  of the edge.  
 **  the edge class derives from the edge_base class and the object class.
 **  the object class provides the =, !=, <, >, <=, >= operators. 
 **  the edge_base class provides data related to the end-points.
 **  the edge class allows you to change the compare by function that
 **  would then change the behavior of the <, >, ... operations.
 **
 **  Memory <= 24 bytes (sizeof(edge_base)(8) + 8 + 8).
 **/
class edge : public edge_base, public object {
    public :
        using edge_type = edge;
        using base_edge_type = edge_base;
        using cmp_func_type = int32_t(const base_edge_type&,
                                      const base_edge_type&);

        edge(const vertex_type& first,
             const vertex_type& second) :
             edge_base(first, second) {}

        edge(istream& is = cin) : edge_base(is) {}

        const cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(const cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const edge_type& that) const {
            return cmp_func(*this, that);
        }

    protected:
        bool is_equal(const object& obj) const override {
            const edge_type& that = static_cast<const edge_type&>(obj);

            return edge_base::is_equal(that);
        }

        int32_t cmp(const object& obj) const override {
            const edge_type& that = static_cast<const edge_type&>(obj);

            return cmp(that);
        }
 
        string to_string() const override {
            return edge_base::to_string();
        }

    private :
        const cmp_func_type* cmp_func = &cmp_by_first_vertex;
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

#endif /* __EDGE_H__ */
