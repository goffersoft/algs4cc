/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent a directed edge in a graph.
 *
 ******************************************************************************/
#ifndef __DIEDGE_H__
#define __DIEDGE_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "object.h"
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

using edu::princeton::cs::algs4::edge_base;
using com::goffersoft::core::object;

/**
 **  the diedge_base class represents a
 **  directed edge in a graph. Each edge consists of two integers
 **  (naming the two vertices). The data type
 **  provides methods for accessing the two endpoints of the edge
 **  cmp_by_<>_vertex methods compares 2 edges by
 **  ascending/descending order of vertex.
 **
 **  Memory <= sizeof(edge) (8 bytes)
 **  This is am immutable class.
 **/
class diedge_base {
    public :
        using diedge_type = diedge_base;
        using edge_type = edge_base;
        using vertex_type = edge_type::vertex_type;

        diedge_base(const vertex_type& v,
                    const vertex_type& w) :
             e(v, w) {}

        diedge_base(const edge_type& e) : e(e) {}

        diedge_base(istream& is = cin) : e(is) {}

        const vertex_type get_from() const {
            return e.get_first();
        }

        const vertex_type get_to() const {
            return e.get_second();
        }

        operator edge_type() const {
            return e;
        }

        bool equals(const diedge_type& that) const {
            return e.equals(that.e);
        }
 
        operator string() const {
            stringstream ss;

            ss << e.get_first() << " -> "
               << e.get_second();

            return ss.str();
        }

        bool operator ==(const diedge_type& that) const {
            if(this == &that)
                return true;

            return (e == that.e);
        }

        bool operator !=(const diedge_type& that) const {
            return !(*this == that);
        }

        friend ostream& operator <<(ostream& os,
                                   const diedge_type& e) {
            return os << string(e);
        }

        static int32_t cmp_by_first_vertex(
                           const diedge_type& lhs,
                           const diedge_type& rhs) {
            return edge_type::cmp_by_first_vertex(lhs, rhs);
        }

        static int32_t cmp_by_first_vertex_descending(
                           const diedge_type& lhs,
                           const diedge_type& rhs) {
            return edge_type::cmp_by_first_vertex_descending(lhs, rhs);
        }

        static int32_t cmp_by_second_vertex(
                           const diedge_type& lhs,
                           const diedge_type& rhs) {
            return edge_type::cmp_by_second_vertex(lhs, rhs);
        }

        static int32_t cmp_by_second_vertex_descending(
                           const diedge_type& lhs,
                           const diedge_type& rhs) {
            return edge_type::cmp_by_second_vertex_descending(lhs, rhs);
        }

    protected :

        const edge_type& get_edge() const {
            return e;
        }

    private :
        const edge_type  e;
};

/**
 **  The diedge class represents a directed edge as
 **  a set of 2 vertices.
 **  Each edge consists of two integers (naming the two vertices).
 **  The data type provides methods for accessing the two endpoints
 **  of the edge.
 **  the diedge class derives from the diedge_base
 **  class and the object class.
 **  the object class provides the =, !=, <, >, <=, >= string
 **  operators.
 **  the diedge_base class provides data related
 **  to the end-points.
 **  the diedge class allows you to change the compare by
 **  function that would then change the behavior of the <, >, ...
 **  operations.
 **
 **  Memory <= sizeof(diedge_base)(8) + 8 + 8.
 **/
class diedge : public diedge_base, public object {
    public :
        using object::operator string;
        using object::equals;
        using object::operator ==;
        using object::operator !=;
        using diedge_type = diedge;
        using base_edge_type = diedge_base;
        using cmp_func_type = int32_t(const base_edge_type&,
                                      const base_edge_type&);

        diedge(const vertex_type& v,
               const vertex_type& w) :
             diedge_base(v, w) {}

        diedge(const edge_type& e) : diedge_base(e){}

        diedge(istream& is = cin) : diedge_base(is) {}

        cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const diedge_type& that) const {
            return cmp_func(*this, that);
        }

    protected :
        bool is_equal(const object& obj) const override {
            const diedge_type& that = static_cast<const diedge_type&>(obj);
            return diedge_base::equals(that);
        }

        int32_t cmp(const object& obj) const override {
            const diedge_type& that = static_cast<const diedge_type&>(obj);
            return cmp(that);
        }

        string to_string() const override {
            return diedge_base::operator string();
        }

    private :
        cmp_func_type* cmp_func = &cmp_by_first_vertex;
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

#endif /* __DIEDGE_H__ */
