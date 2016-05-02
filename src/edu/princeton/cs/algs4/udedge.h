/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent a undirected edge in a graph.
 *
 ******************************************************************************/
#ifndef __UDEDGE_H__
#define __UDEDGE_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "object.h"
#include "edge.h"
#include "cstdin.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::istream;
using std::ostream;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::invalid_argument;
using std::move;

using edu::princeton::cs::algs4::cstdin;
using com::goffersoft::core::object;
using edu::princeton::cs::algs4::edge_base;

/**
 **  the udedge_base class represents a
 **  undirected edge in a graph.
 **  Each edge consists of two integers
 **  (naming the two vertices).
 **  The data type provides methods for accessing the two
 **  endpoints of the edge.
 **  cmp_by_<>_vertex methods compares 2 edges by
 **  ascending order of vertex.
 **
 **  Memory <= sizeof(edge_base) (8 bytes)
 **  This is am immutable class.
 **/
class udedge_base {
    public :
        using udedge_type = udedge_base;
        using edge_type = edge_base;
        using vertex_type = edge_type::vertex_type;

        udedge_base(const vertex_type& v,
                    const vertex_type& w) :
             e(v, w) {}

        udedge_base(const edge_type& e) : e(e) {}

        udedge_base(istream& is = cin) : e(is) {}

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

        operator edge_type() const {
            return e;
        }

        bool equals(const udedge_type& that) const {
            return e.equals(that.e);
        }
 
        operator string() const {
            stringstream ss;

            ss << e.get_first() << " <-> "
               << e.get_second();

            return ss.str();
        }

        bool operator ==(const udedge_type& that) const {
            if(this == &that)
                return true;

            return (e == that.e);
        }

        bool operator !=(const udedge_type& that) const {
            return !(*this == that);
        }

        friend ostream& operator <<(ostream& os,
                                   const udedge_base& e) {
            return os << string(e);
        }

        static int32_t cmp_by_first_vertex(
                           const udedge_type& lhs,
                           const udedge_type& rhs) {
            return edge_type::cmp_by_first_vertex(lhs, rhs);
        }

        static int32_t cmp_by_second_vertex(
                           const udedge_type& lhs,
                           const udedge_type& rhs) {
            return edge_type::cmp_by_second_vertex(lhs, rhs);
        }

    protected :

        const edge_type& get_edge() const {
            return e;
        }

    private :
        edge_type e;
};

/**
 **  The udedge class represents a undirected edge as
 **  a set of 2 vertices.
 **  Each edge consists of two integers (naming the two vertices).
 **  The data type provides methods for accessing the two endpoints
 **  of the edge associated with this edge.
 **  the udedge class derives from the udedge_base
 **  class and the object class.
 **  the object class provides the =, !=, <, >, <=, >= string
 **  operators.
 **  the udedge_base class provides data related
 **  to the end-points.
 **  the udedge class allows you to change the compare by
 **  function that would then change the behavior of the <, >, ...
 **  operations.
 **
 **  Memory <= sizeof(udedge_base)(8) + 8 + 8.
 **/
class udedge : public udedge_base, public object {
    public :
        using object::equals;
        using object::operator string;
        using object::operator ==;
        using object::operator !=;
        using udedge_type = udedge;
        using base_edge_type = udedge_base;
        using cmp_func_type = int32_t(const base_edge_type&,
                                      const base_edge_type&);

        udedge(const vertex_type& v,
               const vertex_type& w) :
             udedge_base(v, w) {}

        udedge(const edge_type& e) :
             udedge_base(e) {}

        udedge(istream& is = cin) :
             udedge_base(is) {}

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
            return udedge_base::equals(that);
        }

        int32_t cmp(const object& obj) const override {
            const udedge_type& that = static_cast<const udedge_type&>(obj);
            return cmp(that);
        }

        string to_string() const override {
            return udedge_base::operator string();
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

#endif /* __UDEDGE_H__ */
