/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the edge class types.
 *
 ******************************************************************************/
#ifndef __WEIGHTED_EDGE_TESTCASES_H__
#define __WEIGHTED_EDGE_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "codeclean.h"
#include "weighted_edge.h"

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
using com::goffersoft::codeclean::utils;

using edu::princeton::cs::algs4::weighted_edge_base;
using edu::princeton::cs::algs4::weighted_edge;

class weighted_edge_testcase1 : public testcase {
    public :
        weighted_edge_testcase1(const string& name = "weighted_edge_base - all tests") :
                           testcase(name) {
            add_test(bind(&weighted_edge_testcase1::test1, this),
                     "sizeof(weighted_edge_base) <= 16 test");
            add_test(bind(&weighted_edge_testcase1::test2, this),
                     "constructor-(v,w, wt) test");
            add_test(bind(&weighted_edge_testcase1::test3, this),
                     "constructor-(cin) test");
            add_test(bind(&weighted_edge_testcase1::test4, this),
                          "get_weight method test");
            add_test(bind(&weighted_edge_testcase1::test5, this),
                     "equals(weighted_edge_base) method test");
            add_test(bind(&weighted_edge_testcase1::test6, this),
                     "!equals(weighted_edge_base) method test");
            add_test(bind(&weighted_edge_testcase1::test7, this),
                     "==(weighted_edge_base) method test");
            add_test(bind(&weighted_edge_testcase1::test8, this),
                     "!=(weighted_edge_base) method test");
            add_test(bind(&weighted_edge_testcase1::test9, this),
                     "cmp_by_weight - ascending static method test");
            add_test(bind(&weighted_edge_testcase1::test10, this),
                     "cmp_by_weight - descending static method test");
        }

        bool test1() {
            return test::ccassert(sizeof(weighted_edge_base) <= 16);
        }

        bool test2() {
            weighted_edge_base e(2, 3, 3.1);
            return test::ccassert_equals(string("2 ?-? 3 3.1"), string(e)); 
        }

        bool test3() {
            stringstream s("2 3 3.1");
            weighted_edge_base *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new weighted_edge_base();
                });
             
            bool retval = test::ccassert_equals(string("2 ?-? 3 3.1"),
                                                string(*e)); 
            delete e;
            return retval;
        }

        bool test4() {
            weighted_edge_base e(2, 3, 3.0);
            return test::ccassert(utils::cmp_equal(e.get_weight(),
                                weighted_edge_base::weight_type(3.0)));
        }

        bool test5() {
            weighted_edge_base e1(3, 3, 3.0);
            weighted_edge_base e2(3, 3, 3.0);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test6() {
            weighted_edge_base e1(3, 3, 3.0);
            weighted_edge_base e2(4, 3, 3.0);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test7() {
            weighted_edge_base e1(3, 3, 3.0);
            weighted_edge_base e2(3, 3, 3.0);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test8() {
            weighted_edge_base e1(3, 3, 3.1);
            weighted_edge_base e2(3, 3, 3.0);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test9() {
            vector<weighted_edge_base> edges_act;
            vector<weighted_edge_base> edges_exp;

            edges_act.push_back(weighted_edge_base(0, 1, 9));
            edges_act.push_back(weighted_edge_base(1, 0, 8));
            edges_act.push_back(weighted_edge_base(1, 1, 7));
            edges_act.push_back(weighted_edge_base(1, 2, 6));
            edges_act.push_back(weighted_edge_base(1, 3, 5));
            edges_act.push_back(weighted_edge_base(2, 1, 5));
            edges_act.push_back(weighted_edge_base(2, 3, 3));
            edges_act.push_back(weighted_edge_base(3, 1, 2));
            edges_act.push_back(weighted_edge_base(3, 2, 1));

            edges_exp.push_back(weighted_edge_base(3, 2, 1));
            edges_exp.push_back(weighted_edge_base(3, 1, 2));
            edges_exp.push_back(weighted_edge_base(2, 3, 3));
            edges_exp.push_back(weighted_edge_base(1, 3, 5));
            edges_exp.push_back(weighted_edge_base(2, 1, 5));
            edges_exp.push_back(weighted_edge_base(1, 2, 6));
            edges_exp.push_back(weighted_edge_base(1, 1, 7));
            edges_exp.push_back(weighted_edge_base(1, 0, 8));
            edges_exp.push_back(weighted_edge_base(0, 1, 9));

            sort(edges_act.begin(), edges_act.end(),
                 [](const weighted_edge_base& lhs,
                    const weighted_edge_base& rhs) {
                     return weighted_edge_base::
                            cmp_by_weight(lhs, rhs) < 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const weighted_edge_base& lhs,
                              const weighted_edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test10() {
            vector<weighted_edge_base> edges_act;
            vector<weighted_edge_base> edges_exp;

            edges_act.push_back(weighted_edge_base(0, 1, 1));
            edges_act.push_back(weighted_edge_base(1, 0, 2));
            edges_act.push_back(weighted_edge_base(1, 1, 3));
            edges_act.push_back(weighted_edge_base(1, 2, 5));
            edges_act.push_back(weighted_edge_base(1, 3, 5));
            edges_act.push_back(weighted_edge_base(2, 1, 6));
            edges_act.push_back(weighted_edge_base(2, 3, 7));
            edges_act.push_back(weighted_edge_base(3, 1, 8));
            edges_act.push_back(weighted_edge_base(3, 2, 9));

            edges_exp.push_back(weighted_edge_base(3, 2, 9));
            edges_exp.push_back(weighted_edge_base(3, 1, 8));
            edges_exp.push_back(weighted_edge_base(2, 3, 7));
            edges_exp.push_back(weighted_edge_base(2, 1, 6));
            edges_exp.push_back(weighted_edge_base(1, 2, 5));
            edges_exp.push_back(weighted_edge_base(1, 3, 5));
            edges_exp.push_back(weighted_edge_base(1, 1, 3));
            edges_exp.push_back(weighted_edge_base(1, 0, 2));
            edges_exp.push_back(weighted_edge_base(0, 1, 1));

            sort(edges_act.begin(), edges_act.end(),
                 [](const weighted_edge_base& lhs,
                    const weighted_edge_base& rhs) {
                     return weighted_edge_base::
                            cmp_by_weight(lhs, rhs) > 0;
                 });
            return test::ccassert_array_equals(
                           edges_exp, edges_act,
                           [](const weighted_edge_base& lhs,
                              const weighted_edge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }
};

class weighted_edge_testcase2 : public testcase {
    public :
        weighted_edge_testcase2(const string& name = "weighted_edge - all tests") :
                           testcase(name) {
            add_test(bind(&weighted_edge_testcase2::test1, this),
                     "sizeof(weighted_edge) <= 32 test");
            add_test(bind(&weighted_edge_testcase2::test2, this),
                     "constructor-(v,w, wt) test");
            add_test(bind(&weighted_edge_testcase2::test3, this),
                     "constructor-(cin) test");
            add_test(bind(&weighted_edge_testcase2::test4, this),
                     "get_cmp_func method test");
            add_test(bind(&weighted_edge_testcase2::test5, this),
                     "set_cmp_func method test");
            add_test(bind(&weighted_edge_testcase2::test6, this),
                     "equals(object) method test");
            add_test(bind(&weighted_edge_testcase2::test7, this),
                     "!equals(object) method test");
            add_test(bind(&weighted_edge_testcase2::test8, this),
                     "==(object) method test");
            add_test(bind(&weighted_edge_testcase2::test9, this),
                     "!=(object) method test");
            add_test(bind(&weighted_edge_testcase2::test10, this),
                     ">(object) method test");
            add_test(bind(&weighted_edge_testcase2::test11, this),
                     ">=(object) method test");
            add_test(bind(&weighted_edge_testcase2::test12, this),
                     "<(object) method test");
            add_test(bind(&weighted_edge_testcase2::test13, this),
                     "<=(object) method test");
        }

        bool test1() {
            return test::ccassert(sizeof(weighted_edge) <= 32);
        }

        bool test2() {
            weighted_edge e(2, 3, 3.1);
            return test::ccassert_equals(string("2 ?-? 3 3.1"), string(e)); 
        }

        bool test3() {
            stringstream s("2 3 3.1");
            weighted_edge *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new weighted_edge();
                });
             
            bool retval = test::ccassert_equals(string("2 ?-? 3 3.1"), string(*e)); 
            delete e;
            return retval;
        }

        bool test4() {
            weighted_edge e1(3, 3, .8456);
            weighted_edge e2(3, 3, 0.7456);
            weighted_edge::cmp_func_type& c =
                                   e1.get_cmp_func();
            return test::ccassert(c(e1, e2) > 0);
        }

        bool test5() {
            weighted_edge e1(3, 3, .8456);
            weighted_edge e2(3, 3, 0.7456);
            auto cmp_desc_fn =
               [](const weighted_edge_base& lhs,
                  const weighted_edge_base& rhs) {
                   return -weighted_edge::
                             cmp_by_weight(lhs, rhs);
               };
            e1.set_cmp_func(*cmp_desc_fn);
            weighted_edge::cmp_func_type& c =
                                   e1.get_cmp_func();
            return test::ccassert(c(e1, e2) < 0);
        }

        bool test6() {
            weighted_edge e1(3, 3, .7456);
            weighted_edge e2(3, 3, 0.7456);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test7() {
            weighted_edge e1(3, 3, .456);
            weighted_edge e2(3, 3, 0.7456);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test8() {
            weighted_edge e1(3, 3, .7456);
            weighted_edge e2(3, 3, 0.7456);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test9() {
            weighted_edge e1(3, 3, .456);
            weighted_edge e2(3, 3, 0.7456);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test10() {
            weighted_edge e1(3, 3, .7456);
            weighted_edge e2(3, 3, 0.6);
            return test::ccassert(e1 > e2 && !(e1 > e1));
        }

        bool test11() {
            weighted_edge e1(3, 3, .7456);
            weighted_edge e2(3, 3, 0.7456);
            return test::ccassert(e1 >= e2 && (e1 >= e1));
        }

        bool test12() {
            weighted_edge e1(3, 3, .6);
            weighted_edge e2(3, 3, 0.7456);
            return test::ccassert(e1 < e2 && !(e1 < e1));
        }

        bool test13() {
            weighted_edge e1(3, 3, .6);
            weighted_edge e2(3, 3, 0.7456);
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

#endif /* __WEIGHTED_EDGE_TESTCASES_H__ */
