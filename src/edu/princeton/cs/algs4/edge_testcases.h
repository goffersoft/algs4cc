/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the edge class types.
 *
 ******************************************************************************/
#ifndef __EDGE_TESTCASES_H__
#define __EDGE_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "codeclean.h"
#include "edge.h"

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

using edu::princeton::cs::algs4::edge_base;
using edu::princeton::cs::algs4::edge;

class edge_testcase1 : public testcase {
    public :
        edge_testcase1(const string& name = "edge_base - all tests") :
                           testcase(name) {
            add_test(bind(&edge_testcase1::test1, this),
                     "sizeof(edge_base) <= 8 test");
            add_test(bind(&edge_testcase1::test2, this),
                     "constructor-(v,w) test");
            add_test(bind(&edge_testcase1::test3, this),
                     "constructor-(cin) test");
            add_test(bind(&edge_testcase1::test4, this),
                          "get_first method test");
            add_test(bind(&edge_testcase1::test5, this),
                          "get_second method test");
            add_test(bind(&edge_testcase1::test6, this),
                     "equals(edge_base) method test");
            add_test(bind(&edge_testcase1::test7, this),
                     "!equals(edge_base) method test");
            add_test(bind(&edge_testcase1::test8, this),
                     "==(edge_base) method test");
            add_test(bind(&edge_testcase1::test9, this),
                     "!=(edge_base) method test");
            add_test(bind(&edge_testcase1::test10, this),
                     "cmp_by_first_vertex - ascending static method test");
            add_test(bind(&edge_testcase1::test11, this),
                     "cmp_by_first_vertex - descending static method test");
            add_test(bind(&edge_testcase1::test12, this),
                     "cmp_by_second_vertex - ascending static method test");
            add_test(bind(&edge_testcase1::test13, this),
                     "cmp_by_second_vertex - descending static method test");
            add_test(bind(&edge_testcase1::test14, this),
                          "get_other method test");
            add_test(bind(&edge_testcase1::test15, this),
                          "get_other method exception test");
        }

        bool test1() {
            return test::ccassert(sizeof(edge_base) <= 8);
        }

        bool test2() {
            edge_base e(2, 3);
            return test::ccassert_equals(string("2 ?-? 3"), string(e)); 
        }

        bool test3() {
            stringstream s("2 3");
            edge_base *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new edge_base();
                });
             
            bool retval = test::ccassert_equals(string("2 ?-? 3"), string(*e)); 
            delete e;
            return retval;
        }

        bool test4() {
            edge_base e(2, 3);
            return test::ccassert_equals(e.get_first(), edge_base::vertex_type(2)); 
        }

        bool test5() {
            edge_base e(2, 3);
            return test::ccassert_equals(e.get_second(), edge_base::vertex_type(3)); 
        }

        bool test6() {
            edge_base e1(3, 3);
            edge_base e2(3, 3);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test7() {
            edge_base e1(3, 3);
            edge_base e2(4, 3);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test8() {
            edge_base e1(3, 3);
            edge_base e2(3, 3);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test9() {
            edge_base e1(3, 2);
            edge_base e2(3, 3);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test10() {
            vector<edge_base> edges_act;
            vector<edge_base> edges_exp;
            edges_act.push_back(edge_base(0, 1));
            edges_act.push_back(edge_base(1, 0));
            edges_act.push_back(edge_base(1, 1));
            edges_act.push_back(edge_base(1, 2));
            edges_act.push_back(edge_base(1, 3));
            edges_act.push_back(edge_base(2, 1));
            edges_act.push_back(edge_base(2, 3));
            edges_act.push_back(edge_base(3, 1));
            edges_act.push_back(edge_base(3, 2));

            edges_exp.push_back(edge_base(0, 1));
            edges_exp.push_back(edge_base(1, 0));
            edges_exp.push_back(edge_base(1, 1));
            edges_exp.push_back(edge_base(1, 2));
            edges_exp.push_back(edge_base(1, 3));
            edges_exp.push_back(edge_base(2, 1));
            edges_exp.push_back(edge_base(2, 3));
            edges_exp.push_back(edge_base(3, 1));
            edges_exp.push_back(edge_base(3, 2));
            sort(edges_act.begin(), edges_act.end(),
                 [](const edge_base& lhs,
                    const edge_base& rhs) {
                     return edge_base::
                            cmp_by_first_vertex(lhs, rhs) < 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const edge_base& lhs,
                              const edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test11() {
            vector<edge_base> edges_act;
            vector<edge_base> edges_exp;
            edges_act.push_back(edge_base(0, 1));
            edges_act.push_back(edge_base(1, 0));
            edges_act.push_back(edge_base(1, 1));
            edges_act.push_back(edge_base(1, 2));
            edges_act.push_back(edge_base(1, 3));
            edges_act.push_back(edge_base(2, 1));
            edges_act.push_back(edge_base(2, 3));
            edges_act.push_back(edge_base(3, 1));
            edges_act.push_back(edge_base(3, 2));

            edges_exp.push_back(edge_base(3, 2));
            edges_exp.push_back(edge_base(3, 1));
            edges_exp.push_back(edge_base(2, 3));
            edges_exp.push_back(edge_base(2, 1));
            edges_exp.push_back(edge_base(1, 3));
            edges_exp.push_back(edge_base(1, 2));
            edges_exp.push_back(edge_base(1, 1));
            edges_exp.push_back(edge_base(1, 0));
            edges_exp.push_back(edge_base(0, 1));
            sort(edges_act.begin(), edges_act.end(),
                 [](const edge_base& lhs,
                    const edge_base& rhs) {
                     return edge_base::
                            cmp_by_first_vertex(lhs, rhs) > 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const edge_base& lhs,
                              const edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test12() {
            vector<edge_base> edges_act;
            vector<edge_base> edges_exp;
            edges_act.push_back(edge_base(0, 1));
            edges_act.push_back(edge_base(1, 0));
            edges_act.push_back(edge_base(1, 1));
            edges_act.push_back(edge_base(1, 2));
            edges_act.push_back(edge_base(1, 3));
            edges_act.push_back(edge_base(2, 1));
            edges_act.push_back(edge_base(2, 3));
            edges_act.push_back(edge_base(3, 1));
            edges_act.push_back(edge_base(3, 2));

            edges_exp.push_back(edge_base(1, 0));
            edges_exp.push_back(edge_base(0, 1));
            edges_exp.push_back(edge_base(1, 1));
            edges_exp.push_back(edge_base(2, 1));
            edges_exp.push_back(edge_base(3, 1));
            edges_exp.push_back(edge_base(1, 2));
            edges_exp.push_back(edge_base(3, 2));
            edges_exp.push_back(edge_base(1, 3));
            edges_exp.push_back(edge_base(2, 3));
            sort(edges_act.begin(), edges_act.end(),
                 [](const edge_base& lhs,
                    const edge_base& rhs) {
                     return edge_base::
                            cmp_by_second_vertex(lhs, rhs) < 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const edge_base& lhs,
                              const edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test13() {
            vector<edge_base> edges_act;
            vector<edge_base> edges_exp;
            edges_act.push_back(edge_base(0, 1));
            edges_act.push_back(edge_base(1, 0));
            edges_act.push_back(edge_base(1, 1));
            edges_act.push_back(edge_base(1, 2));
            edges_act.push_back(edge_base(1, 3));
            edges_act.push_back(edge_base(2, 1));
            edges_act.push_back(edge_base(2, 3));
            edges_act.push_back(edge_base(3, 1));
            edges_act.push_back(edge_base(3, 2));

            edges_exp.push_back(edge_base(2, 3));
            edges_exp.push_back(edge_base(1, 3));
            edges_exp.push_back(edge_base(3, 2));
            edges_exp.push_back(edge_base(1, 2));
            edges_exp.push_back(edge_base(3, 1));
            edges_exp.push_back(edge_base(2, 1));
            edges_exp.push_back(edge_base(1, 1));
            edges_exp.push_back(edge_base(0, 1));
            edges_exp.push_back(edge_base(1, 0));
            sort(edges_act.begin(), edges_act.end(),
                 [](const edge_base& lhs,
                    const edge_base& rhs) {
                     return edge_base::
                            cmp_by_second_vertex(lhs, rhs) > 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const edge_base& lhs,
                              const edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test14() {
            edge_base e(2, 3);
            return test::ccassert(e.get_other(2) ==
                                  edge_base::vertex_type(3) || 
                                  e.get_other(3) ==
                                  edge_base::vertex_type(2));
        }

        bool test15() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                         edge_base e(2, 3);
                         e.get_other(4);
                      });
        }
};

class edge_testcase2 : public testcase {
    public :
        edge_testcase2(const string& name = "edge - all tests") : 
                           testcase(name) {
            add_test(bind(&edge_testcase2::test1, this),
                     "sizeof(edge) <= 24 test");
            add_test(bind(&edge_testcase2::test2, this),
                     "constructor-(v,w) test");
            add_test(bind(&edge_testcase2::test3, this),
                     "constructor-(cin) test");
            add_test(bind(&edge_testcase2::test4, this),
                     "get_cmp_func method test");
            add_test(bind(&edge_testcase2::test5, this),
                     "set_cmp_func method test");
            add_test(bind(&edge_testcase2::test6, this),
                     "equals(object) method test");
            add_test(bind(&edge_testcase2::test7, this),
                     "!equals(object) method test");
            add_test(bind(&edge_testcase2::test8, this),
                     "==(object) method test");
            add_test(bind(&edge_testcase2::test9, this),
                     "!=(object) method test");
            add_test(bind(&edge_testcase2::test10, this),
                     ">(object) method test");
            add_test(bind(&edge_testcase2::test11, this),
                     ">=(object) method test");
            add_test(bind(&edge_testcase2::test12, this),
                     "<(object) method test");
            add_test(bind(&edge_testcase2::test13, this),
                     "<=(object) method test");
        }

        bool test1() {
            return test::ccassert(sizeof(edge) <= 24);
        }

        bool test2() {
            edge e(2, 3);
            return test::ccassert_equals(string("2 ?-? 3"), string(e)); 
        }

        bool test3() {
            stringstream s("2 3");
            edge *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new edge();
                });
             
            bool retval = test::ccassert_equals(string("2 ?-? 3"), string(*e)); 
            delete e;
            return retval;
        }

        bool test4() {
            edge e1(3, 4);
            edge e2(2, 3);
            edge::cmp_func_type& c = e1.get_cmp_func();
            return test::ccassert(c(e1, e2) > 0);
        }

        bool test5() {
            edge e1(2, 3);
            edge e2(3, 4);
            e1.set_cmp_func(edge::cmp_by_second_vertex);
            edge::cmp_func_type& c = e1.get_cmp_func();
            return test::ccassert(c(e1, e2) < 0);
        }

        bool test6() {
            edge e1(3, 3);
            edge e2(3, 3);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test7() {
            edge e1(3, 3);
            edge e2(4, 3);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test8() {
            edge e1(3, 3);
            edge e2(3, 3);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test9() {
            edge e1(3, 2);
            edge e2(3, 3);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test10() {
            edge e1(3, 4);
            edge e2(3, 3);
            return test::ccassert(e1 > e2 && !(e1 > e1));
        }

        bool test11() {
            edge e1(3, 3);
            edge e2(3, 3);
            return test::ccassert(e1 >= e2 && (e1 >= e1));
        }

        bool test12() {
            edge e1(3, 3);
            edge e2(3, 4);
            e1.set_cmp_func(edge::cmp_by_second_vertex);
            return test::ccassert(e1 < e2 && !(e1 < e1));
        }

        bool test13() {
            edge e1(3, 3);
            edge e2(3, 3);
            e1.set_cmp_func(edge::cmp_by_second_vertex);
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

#endif /* __EDGE_TESTCASES_H__ */
