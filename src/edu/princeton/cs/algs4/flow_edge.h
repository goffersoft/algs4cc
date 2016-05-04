/******************************************************************************
 *  Dependencies: none
 *
 *  code to represent a flow edge in a flow network.
 *
 ******************************************************************************/
#ifndef __FLOW_EDGE_H__
#define __FLOW_EDGE_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include <cmath>

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
using std::invalid_argument;
using std::function;
using std::isnan;
using std::isinf;

using edu::princeton::cs::algs4::cstdin;
using edu::princeton::cs::algs4::edge;
using com::goffersoft::core::object;

/**
 ** The flow_edge_base class represents a capacitated edge with a
 ** flow in a flow_network. Each edge consists of two integers
 ** (naming the two vertices), a real-valued capacity, and a real-valued
 ** flow. The data type provides methods for accessing the two endpoints
 ** of the directed edge and the flow/capacity.
 ** It also provides methods for changing the amount of flow on the edge
 ** and determining the residual capacity of the edge.
 **
 **  Memory <= 24 bytes (sizeof(edge_base)(8) + 8 + 8).
 **/
class flow_edge_base {
    public :
        using flow_edge_type = flow_edge_base;
        using edge_type = edge_base;
        using vertex_type = edge_type::vertex_type;
        using flow_type = double;
        using capacity_type = double;

        flow_edge_base(const vertex_type& first,
                       const vertex_type& second,
                       const capacity_type& capacity,
                       const capacity_type& flow = 0.0) :
             e(first, second),
             capacity(capacity),
             flow(flow) {
            validate_input(flow, capacity, "");
        }

        flow_edge_base(istream& is = cin,
                       bool init_flow_data = true) :
             e(is),
             capacity(cstdin::read_double(is)) {
            if(init_flow_data)
                flow = cstdin::read_double(is);
            else
                flow = 0.0;
            validate_input(flow, capacity, "");
        }

        const vertex_type get_from() const {
            return e.get_first();
        }

        const vertex_type get_to() const {
            return e.get_second();
        }

        const vertex_type get_other(const vertex_type& v) {
            return e.get_other(v);
        }

        const flow_type get_flow() const {
            return flow;
        }

        const capacity_type get_capacity() const {
            return capacity;
        }
        
        /**
         ** Increases the flow on the edge in the direction
         ** to the given vertex.
         ** If vertex is the tail vertex, this increases the
         ** flow on the edge by delta
         ** if vertex is the head vertex, this decreases the
         ** flow on the edge by delta
         ** throws invalid_argument exception if vertex is not
         ** one of the endpoints of the edge
         ** throws invalid_argument exception if >delta makes
         ** the flow on on the edge either negative or larger
         ** than its capacity
         ** throws invalid_argument exception if delta is NaN
         **/
        void add_residual_flow_to(const vertex_type& v,
                                  const flow_type& delta) {
            if(isnan(delta) || isinf(delta)) {
                throw invalid_argument("delta must be a valid "
                                       "floating point number");
            }
            if(v == get_from()) {
                flow -= delta;
            } else if(v == get_to()) {
                flow += delta;
            } else {
                throw invalid_argument("v is not a member of this edge");
            }
            validate_input(flow, capacity, "delta flow violates data_integrity");
        }

        /**
         ** Returns the residual capacity of the edge in the direction
         ** to the given vertex.
         ** return the residual capacity of the edge in the
         ** direction to the given vertex
         ** If vertex is the tail vertex, the residual capacity equals
         ** get_capacity() - get_flow()
         ** if vertex is the head vertex, the residual capacity equals
         ** flow().
         ** throws invalid_argument exception if vertex is not one of
         ** the endpoints of the edge
         **/
        const capacity_type get_residual_capacity_to(
                                  const vertex_type& v) {
            if(v == get_from()) {
                return flow;
            } else if(v == get_to()) {
                return (capacity - flow);
            } else {
                throw invalid_argument("v is not a member of this edge");
            }
        }

        operator edge_type() const {
            return e;
        }

        bool equals(const flow_edge_type& that) const {
            return (e.equals((edge_type)that) &&
                    utils::cmp_equal(this->flow,
                                     that.flow) &&
                    utils::cmp_equal(this->capacity,
                                     that.capacity));
        }

        operator string() const {
            stringstream ss;

            ss << get_from() << " -> "
               << get_to() << " ";
            utils::print_data(ss, flow) << "/";
            utils::print_data(ss, capacity);

            return ss.str();
        }

        bool operator ==(const flow_edge_type& that) const {
            if(this == &that)
                return true;

            return (cmp_by_flow(*this, that) == 0);
        }

        bool operator !=(const flow_edge_type& that) const {
            return !(*this == that);
        }

        friend ostream& operator <<(ostream& os,
                                   const flow_edge_type& e) {
            return os << string(e);
        }

        static int32_t cmp_by_flow(const flow_edge_type& lhs,
                                   const flow_edge_type& rhs) {
            return utils::cmp(lhs.flow, lhs.capacity,
                              rhs.flow, rhs.capacity);
        };

	static int32_t cmp_by_capacity(const flow_edge_type& lhs,
                                       const flow_edge_type& rhs) {
            return utils::cmp(lhs.capacity, lhs.flow,
                              rhs.capacity, rhs.flow);
        };

    private :
        edge_type e;
        capacity_type capacity;
        flow_type flow;

        static void validate_input(const flow_type& flow,
                                  const capacity_type& capacity,
                                  const string& prefix) {
            if(utils::cmp(flow, 0.0) < 0 ||
               utils::cmp(capacity, 0.0) < 0 ||
               utils::cmp(flow, capacity) > 0) {
                throw invalid_argument(prefix + "\n" +
                                       "flow must be > 0 " +
                                       "capacity  must be > 0 " +
                                       "and flow <= capacity");
            }
        }
};

/**
 ** The flow_edge class represents a capacitated edge with a
 ** flow in a flow_network. Each edge consists of two integers
 ** (naming the two vertices), a real-valued capacity, and a real-valued
 ** flow.
 ** The data type provides methods for accessing the two endpoints
 ** of the edge and its associated flow/capacity.
 ** the flow_edge class derives from the flow_edge_base class
 ** and the object class.
 ** the object class provides the =, !=, <, >, <=, >= operators. 
 ** the flow_edge_base class provides data related to the end-points.
 ** the flow_edge class allows you to change the compare
 ** by function that would then change the behavior of the
 ** <, >, ... operations.
 **
 **  Memory <= 40 bytes (sizeof(flow_edge_base)(24) + 8 + 8).
 **/
class flow_edge : public flow_edge_base, public object {
    public :
        using object::operator string;
        using object::equals;
        using object::operator ==;
        using object::operator !=;
        using flow_edge_type = flow_edge;
        using flow_edge_base_type = flow_edge_base;
        using cmp_func_type = int32_t(const flow_edge_base_type&,
                                      const flow_edge_base_type&);

        flow_edge(const vertex_type& first,
                  const vertex_type& second,
                  const capacity_type& capacity,
                  const capacity_type& flow = 0.0) :
             flow_edge_base(first, second,
                            capacity, flow) {}

        flow_edge(istream& is = cin,
                  bool init_flow_data = true) :
            flow_edge_base(is, init_flow_data) {};

        cmp_func_type& get_cmp_func() const {
            return *cmp_func;
        }

        void set_cmp_func(cmp_func_type& cmp_func) {
            this->cmp_func = &cmp_func;
        }

        int32_t cmp(const flow_edge_type& that) const {
            return cmp_func(*this, that);
        }

    protected:
        bool is_equal(const object& obj) const override {
            const flow_edge_type& that =
                      static_cast<const flow_edge_type&>(obj);

            return flow_edge_base::equals(that);
        }

        int cmp(const object& obj) const override {
            const flow_edge_type& that =
                      static_cast<const flow_edge_type&>(obj);
            return cmp(that);
        }
 
        string to_string() const override {
            return flow_edge_base::operator string();
        }

    private :
        cmp_func_type* cmp_func = &cmp_by_flow;
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

#endif /* __FLOW_EDGE_H__ */
