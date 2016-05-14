/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the edge class types.
 *
 ******************************************************************************/
#ifndef __FLOW_EDGE_TESTCASES_H__
#define __FLOW_EDGE_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "codeclean.h"
#include "flow_edge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::sort;
using std::bind;
using std::stringstream;
using std::string;
using std::invalid_argument;

using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

using edu::princeton::cs::algs4::flow_edge_base;
using edu::princeton::cs::algs4::flow_edge;

class flow_edge_testcase1 : public testcase {
    public :
        flow_edge_testcase1(const string& name = "flow_edge_base - all tests") :
                           testcase(name) {
            add_test(bind(&flow_edge_testcase1::test1, this),
                     "sizeof(flow_edge_base) == 24 test");
            add_test(bind(&flow_edge_testcase1::test2, this),
                     "constructor-(v, w, flow, capacity) test");
            add_test(bind(&flow_edge_testcase1::test3, this),
                     "constructor-(v, w, flow, capacity) exception test");
            add_test(bind(&flow_edge_testcase1::test4, this),
                     "constructor-(v, w, capacity) test");
            add_test(bind(&flow_edge_testcase1::test5, this),
                     "constructor-(cin - with flow) test");
            add_test(bind(&flow_edge_testcase1::test6, this),
                     "constructor-(cin - without flow) test");
            add_test(bind(&flow_edge_testcase1::test7, this),
                          "get_from method test");
            add_test(bind(&flow_edge_testcase1::test8, this),
                          "get_to method test");
            add_test(bind(&flow_edge_testcase1::test9, this),
                          "get_other method test");
            add_test(bind(&flow_edge_testcase1::test10, this),
                          "get_other method exception test");
            add_test(bind(&flow_edge_testcase1::test11, this),
                          "get_flow method test");
            add_test(bind(&flow_edge_testcase1::test12, this),
                          "get_capacity method test");
            add_test(bind(&flow_edge_testcase1::test13, this),
                          "get_residual_capacity_to - forward method test");
            add_test(bind(&flow_edge_testcase1::test14, this),
                          "get_residual_capacity_to - backward method test");
            add_test(bind(&flow_edge_testcase1::test15, this),
                          "get_residual_capacity_to - exception method test");
            add_test(bind(&flow_edge_testcase1::test16, this),
                          "add_residual_flow_to - forward method test");
            add_test(bind(&flow_edge_testcase1::test17, this),
                          "add_residual_flow_to - backward method test");
            add_test(bind(&flow_edge_testcase1::test18, this),
                          "add_residual_flow_to - exception method test");
            add_test(bind(&flow_edge_testcase1::test19, this),
                          "add_residual_flow_to - exception method test");
            add_test(bind(&flow_edge_testcase1::test20, this),
                     "equals(flow_edge_base) method test");
            add_test(bind(&flow_edge_testcase1::test21, this),
                     "!equals(flow_edge_base) method test");
            add_test(bind(&flow_edge_testcase1::test22, this),
                     "==(flow_edge_base) method test");
            add_test(bind(&flow_edge_testcase1::test23, this),
                     "!=(flow_edge_base) method test");
            add_test(bind(&flow_edge_testcase1::test24, this),
                     "cmp_by_capacity - ascending static method test");
            add_test(bind(&flow_edge_testcase1::test25, this),
                     "cmp_by_capacity - descending static method test");
            add_test(bind(&flow_edge_testcase1::test26, this),
                     "cmp_by_flow - ascending static method test");
            add_test(bind(&flow_edge_testcase1::test27, this),
                     "cmp_by_flow - descending static method test");
        }

        bool test1() {
            return test::ccassert(sizeof(flow_edge_base) == 24);
        }

        bool test2() {
            flow_edge_base e(2, 3, 10, 5.3);
            return test::ccassert_equals(string("2 -> 3 5.3/10"),
                                                string(e));
        }

        bool test3() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                          flow_edge_base(2, 3, 10, 11.3);
                      });
        }

        bool test4() {
            flow_edge_base e(2, 3, 10);
            return test::ccassert_equals(string("2 -> 3 0/10"),
                                                string(e));
        }

        bool test5() {
            stringstream s("2 3 10.7, 5.3");
            flow_edge_base *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new flow_edge_base();
                });
             
            bool retval = test::ccassert_equals(string("2 -> 3 5.3/10.7"),
                                                string(*e)); 
            delete e;
            return retval;
        }

        bool test6() {
            stringstream s("2 3 10.7");
            flow_edge_base *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new flow_edge_base(cin, false);
                });
             
            bool retval = test::ccassert_equals(string("2 -> 3 0/10.7"),
                                                string(*e)); 
            delete e;
            return retval;
        }

        bool test7() {
            flow_edge_base e(2, 3, 3.0);
            return test::ccassert_equals(e.get_from(),
                                  flow_edge_base::vertex_type(2));
        }

        bool test8() {
            flow_edge_base e(2, 3, 3.0);
            return test::ccassert_equals(e.get_to(),
                                  flow_edge_base::vertex_type(3));
        }

        bool test9() {
            flow_edge_base e(2, 3, 3.0);
            return test::ccassert(e.get_other(2) ==
                                  flow_edge_base::vertex_type(3) || 
                                  e.get_other(3) ==
                                  flow_edge_base::vertex_type(2));
        }

        bool test10() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                         flow_edge_base e(2, 3, 3.0);
                         e.get_other(4);
                      });
        }

        bool test11() {
            flow_edge_base e(2, 3, 3.0, 1.2);
            return test::ccassert_equals(e.get_flow(),
                                  flow_edge_base::flow_type(1.2));
        }

        bool test12() {
            flow_edge_base e(2, 3, 3.0, 1.2);
            return test::ccassert_equals(e.get_capacity(),
                                  flow_edge_base::capacity_type(3.0));
        }

        bool test13() {
            flow_edge_base e(2, 3, 3.0, 1.2);
            return test::ccassert_equals(e.get_residual_capacity_to(3),
                                  flow_edge_base::capacity_type(1.8));
        }

        bool test14() {
            flow_edge_base e(2, 3, 3.0, 1.2);
            return test::ccassert_equals(e.get_residual_capacity_to(2),
                                  flow_edge_base::capacity_type(1.2));
        }

        bool test15() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                         flow_edge_base e(2, 3, 3.0);
                         e.get_residual_capacity_to(4);
                      });
        }

        bool test16() {
            flow_edge_base e(2, 3, 3.0, 1.2);
            e.add_residual_flow_to(3, 1);
            return test::ccassert_equals(e.get_residual_capacity_to(3),
                                  flow_edge_base::capacity_type(0.8));
        }

        bool test17() {
            flow_edge_base e(2, 3, 3.0, 1.2);
            e.add_residual_flow_to(2, 1);
            return test::ccassert_equals(e.get_residual_capacity_to(2),
                                  flow_edge_base::capacity_type(.2));
        }

        bool test18() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                         flow_edge_base e(2, 3, 3.0, 1);
                         e.add_residual_flow_to(3, 2.2);
                      });
        }

        bool test19() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                         flow_edge_base e(2, 3, 3.0, 1);
                         e.add_residual_flow_to(4, 2.2);
                      });
        }

        bool test20() {
            flow_edge_base e1(3, 3, 3.0, 1.2);
            flow_edge_base e2(3, 3, 3.0, 1.2);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test21() {
            flow_edge_base e1(3, 3, 3.0, 1.2);
            flow_edge_base e2(4, 3, 3.0, 1.2);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test22() {
            flow_edge_base e1(3, 3, 3.0, 1.2);
            flow_edge_base e2(3, 3, 3.0, 1.2);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test23() {
            flow_edge_base e1(3, 3, 3.0, 1.2);
            flow_edge_base e2(3, 3, 3.1, 1.2);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test24() {
            vector<flow_edge_base> edges_act;
            vector<flow_edge_base> edges_exp;

            edges_act.push_back(flow_edge_base(0, 1, 9));
            edges_act.push_back(flow_edge_base(1, 0, 8));
            edges_act.push_back(flow_edge_base(1, 1, 7));
            edges_act.push_back(flow_edge_base(1, 2, 6));
            edges_act.push_back(flow_edge_base(1, 3, 5));
            edges_act.push_back(flow_edge_base(2, 1, 5));
            edges_act.push_back(flow_edge_base(2, 3, 3));
            edges_act.push_back(flow_edge_base(3, 1, 2));
            edges_act.push_back(flow_edge_base(3, 2, 1));

            edges_exp.push_back(flow_edge_base(3, 2, 1));
            edges_exp.push_back(flow_edge_base(3, 1, 2));
            edges_exp.push_back(flow_edge_base(2, 3, 3));
            edges_exp.push_back(flow_edge_base(1, 3, 5));
            edges_exp.push_back(flow_edge_base(2, 1, 5));
            edges_exp.push_back(flow_edge_base(1, 2, 6));
            edges_exp.push_back(flow_edge_base(1, 1, 7));
            edges_exp.push_back(flow_edge_base(1, 0, 8));
            edges_exp.push_back(flow_edge_base(0, 1, 9));

            sort(edges_act.begin(), edges_act.end(),
                 [](const flow_edge_base& lhs,
                    const flow_edge_base& rhs) {
                     return flow_edge_base::
                            cmp_by_capacity(lhs, rhs) < 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const flow_edge_base& lhs,
                              const flow_edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test25() {
            vector<flow_edge_base> edges_act;
            vector<flow_edge_base> edges_exp;

            edges_act.push_back(flow_edge_base(0, 1, 1));
            edges_act.push_back(flow_edge_base(1, 0, 2));
            edges_act.push_back(flow_edge_base(1, 1, 3));
            edges_act.push_back(flow_edge_base(1, 2, 4));
            edges_act.push_back(flow_edge_base(1, 3, 5));
            edges_act.push_back(flow_edge_base(2, 1, 6));
            edges_act.push_back(flow_edge_base(2, 3, 7));
            edges_act.push_back(flow_edge_base(3, 1, 8));
            edges_act.push_back(flow_edge_base(3, 2, 9));

            edges_exp.push_back(flow_edge_base(3, 2, 9));
            edges_exp.push_back(flow_edge_base(3, 1, 8));
            edges_exp.push_back(flow_edge_base(2, 3, 7));
            edges_exp.push_back(flow_edge_base(2, 1, 6));
            edges_exp.push_back(flow_edge_base(1, 3, 5));
            edges_exp.push_back(flow_edge_base(1, 2, 4));
            edges_exp.push_back(flow_edge_base(1, 1, 3));
            edges_exp.push_back(flow_edge_base(1, 0, 2));
            edges_exp.push_back(flow_edge_base(0, 1, 1));

            sort(edges_act.begin(), edges_act.end(),
                 [](const flow_edge_base& lhs,
                    const flow_edge_base& rhs) {
                     return flow_edge_base::
                            cmp_by_capacity(lhs, rhs) > 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const flow_edge_base& lhs,
                              const flow_edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test26() {
            vector<flow_edge_base> edges_act;
            vector<flow_edge_base> edges_exp;

            edges_act.push_back(flow_edge_base(0, 1, 9, 7.5));
            edges_act.push_back(flow_edge_base(1, 0, 8, 6.5));
            edges_act.push_back(flow_edge_base(1, 1, 7, 5.4));
            edges_act.push_back(flow_edge_base(1, 2, 6, 4.3));
            edges_act.push_back(flow_edge_base(1, 3, 5, 3.9));
            edges_act.push_back(flow_edge_base(2, 1, 4, 3.9));
            edges_act.push_back(flow_edge_base(2, 3, 3, 2.3));
            edges_act.push_back(flow_edge_base(3, 1, 2, 1.7));
            edges_act.push_back(flow_edge_base(3, 2, 1, .8));

            edges_exp.push_back(flow_edge_base(3, 2, 1, .8));
            edges_exp.push_back(flow_edge_base(3, 1, 2, 1.7));
            edges_exp.push_back(flow_edge_base(2, 3, 3, 2.3));
            edges_exp.push_back(flow_edge_base(2, 1, 4, 3.9));
            edges_exp.push_back(flow_edge_base(1, 3, 5, 3.9));
            edges_exp.push_back(flow_edge_base(1, 2, 6, 4.3));
            edges_exp.push_back(flow_edge_base(1, 1, 7, 5.4));
            edges_exp.push_back(flow_edge_base(1, 0, 8, 6.5));
            edges_exp.push_back(flow_edge_base(0, 1, 9, 7.5));

            sort(edges_act.begin(), edges_act.end(),
                 [](const flow_edge_base& lhs,
                    const flow_edge_base& rhs) {
                     return flow_edge_base::
                            cmp_by_flow(lhs, rhs) < 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const flow_edge_base& lhs,
                              const flow_edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test27() {
            vector<flow_edge_base> edges_act;
            vector<flow_edge_base> edges_exp;

            edges_act.push_back(flow_edge_base(3, 2, 1, .8));
            edges_act.push_back(flow_edge_base(3, 1, 2, 1.7));
            edges_act.push_back(flow_edge_base(2, 3, 3, 2.3));
            edges_act.push_back(flow_edge_base(2, 1, 5, 3.9));
            edges_act.push_back(flow_edge_base(1, 3, 5, 3.9));
            edges_act.push_back(flow_edge_base(1, 2, 6, 4.3));
            edges_act.push_back(flow_edge_base(1, 1, 7, 5.4));
            edges_act.push_back(flow_edge_base(1, 0, 8, 6.5));
            edges_act.push_back(flow_edge_base(0, 1, 9, 7.5));

            edges_exp.push_back(flow_edge_base(0, 1, 9, 7.5));
            edges_exp.push_back(flow_edge_base(1, 0, 8, 6.5));
            edges_exp.push_back(flow_edge_base(1, 1, 7, 5.4));
            edges_exp.push_back(flow_edge_base(1, 2, 6, 4.3));
            edges_exp.push_back(flow_edge_base(2, 1, 5, 3.9));
            edges_exp.push_back(flow_edge_base(1, 3, 5, 3.9));
            edges_exp.push_back(flow_edge_base(2, 3, 3, 2.3));
            edges_exp.push_back(flow_edge_base(3, 1, 2, 1.7));
            edges_exp.push_back(flow_edge_base(3, 2, 1, .8));

            sort(edges_act.begin(), edges_act.end(),
                 [](const flow_edge_base& lhs,
                    const flow_edge_base& rhs) {
                     return flow_edge_base::
                            cmp_by_flow(lhs, rhs) > 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const flow_edge_base& lhs,
                              const flow_edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }
};

class flow_edge_testcase2 : public testcase {
    public :
        flow_edge_testcase2(const string& name = "flow_edge - all tests") :
                           testcase(name) {
            add_test(bind(&flow_edge_testcase2::test1, this),
                     "sizeof(flow_edge) == 40 test");
            add_test(bind(&flow_edge_testcase2::test2, this),
                     "constructor-(v, w, flow, capacity) test");
            add_test(bind(&flow_edge_testcase2::test3, this),
                     "constructor-(v, w, flow, capacity) exception test");
            add_test(bind(&flow_edge_testcase2::test4, this),
                     "constructor-(v, w, capacity) test");
            add_test(bind(&flow_edge_testcase2::test5, this),
                     "constructor-(cin - with flow) test");
            add_test(bind(&flow_edge_testcase2::test6, this),
                     "constructor-(cin - without flow) test");
            add_test(bind(&flow_edge_testcase2::test7, this),
                     "get_cmp_func method test");
            add_test(bind(&flow_edge_testcase2::test8, this),
                     "set_cmp_func method test");
            add_test(bind(&flow_edge_testcase2::test9, this),
                     "equals(object) method test");
            add_test(bind(&flow_edge_testcase2::test10, this),
                     "!equals(object) method test");
            add_test(bind(&flow_edge_testcase2::test11, this),
                     "==(object) method test");
            add_test(bind(&flow_edge_testcase2::test12, this),
                     "!=(object) method test");
            add_test(bind(&flow_edge_testcase2::test13, this),
                     ">(object) method test");
            add_test(bind(&flow_edge_testcase2::test14, this),
                     ">=(object) method test");
            add_test(bind(&flow_edge_testcase2::test15, this),
                     "<(object) method test");
            add_test(bind(&flow_edge_testcase2::test16, this),
                     "<=(object) method test");
        }

        bool test1() {
            return test::ccassert(sizeof(flow_edge) == 40);
        }

        bool test2() {
            flow_edge e(2, 3, 10, 5.3);
            return test::ccassert_equals(string("2 -> 3 5.3/10"),
                                                string(e));
        }

        bool test3() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                          flow_edge(2, 3, 10, 11.3);
                      });
        }

        bool test4() {
            flow_edge e(2, 3, 10);
            return test::ccassert_equals(string("2 -> 3 0/10"),
                                                string(e));
        }

        bool test5() {
            stringstream s("2 3 10.7, 5.3");
            flow_edge *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new flow_edge();
                });
             
            bool retval = test::ccassert_equals(string("2 -> 3 5.3/10.7"),
                                                string(*e));
            delete e;
            return retval;
        }

        bool test6() {
            stringstream s("2 3 10.7");
            flow_edge *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new flow_edge(cin, false);
                });
             
            bool retval = test::ccassert_equals(string("2 -> 3 0/10.7"),
                                                string(*e));
            delete e;
            return retval;
        }

        bool test7() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 5, 10, 4);
            flow_edge::cmp_func_type& c = e1.get_cmp_func();
            return test::ccassert(c(e1, e2) > 0);
        }

        bool test8() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 3, 20, 6);
            e1.set_cmp_func(flow_edge::cmp_by_capacity);
            flow_edge::cmp_func_type& c = e1.get_cmp_func();
            return test::ccassert(c(e1, e2) < 0);
        }

        bool test9() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(2, 4, 10, 5);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test10() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 3, 20, 6);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test11() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 3, 10, 5);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test12() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 3, 20, 6);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test13() {
            flow_edge e1(2, 4, 10, 6);
            flow_edge e2(4, 3, 20, 5);
            return test::ccassert(e1 > e2 && !(e1 > e1));
        }

        bool test14() {
            flow_edge e1(2, 4, 10, 6);
            flow_edge e2(4, 3, 20, 5);
            return test::ccassert(e1 >= e2 && (e1 >= e1));
        }

        bool test15() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 3, 20, 6);
            e1.set_cmp_func(flow_edge::cmp_by_capacity);
            return test::ccassert(e1 < e2 && !(e1 < e1));
        }

        bool test16() {
            flow_edge e1(2, 4, 10, 5);
            flow_edge e2(4, 3, 10, 6);
            e1.set_cmp_func(flow_edge::cmp_by_capacity);
            return test::ccassert(e1 <= e2 && (e1 <= e1));
        }
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

#endif /* __FLOW_EDGE_TESTCASES_H__ */
