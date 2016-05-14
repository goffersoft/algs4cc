/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the edge class types.
 *
 ******************************************************************************/
#ifndef __WEIGHTED_UDEDGE_TESTCASES_H__
#define __WEIGHTED_UDEDGE_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "codeclean.h"
#include "weighted_udedge.h"

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

using edu::princeton::cs::algs4::weighted_udedge_base;
using edu::princeton::cs::algs4::weighted_udedge;

class weighted_udedge_testcase1 : public testcase {
    public :
        weighted_udedge_testcase1(const string& name = "weighted_udedge_base - all tests") :
                           testcase(name) {
            add_test(bind(&weighted_udedge_testcase1::test1, this),
                     "sizeof(weighted_udedge_base) <= 16 test");
            add_test(bind(&weighted_udedge_testcase1::test2, this),
                     "constructor-(v,w, wt) test");
            add_test(bind(&weighted_udedge_testcase1::test3, this),
                     "constructor-(cin) test");
            add_test(bind(&weighted_udedge_testcase1::test4, this),
                     "constructor-(edge_type) test");
            add_test(bind(&weighted_udedge_testcase1::test5, this),
                          "get_weight method test");
            add_test(bind(&weighted_udedge_testcase1::test6, this),
                          "conversion operator test");
            add_test(bind(&weighted_udedge_testcase1::test7, this),
                          "get_either method test");
            add_test(bind(&weighted_udedge_testcase1::test8, this),
                          "get_other method test");
            add_test(bind(&weighted_udedge_testcase1::test9, this),
                          "get_other method exception test");
            add_test(bind(&weighted_udedge_testcase1::test10, this),
                     "equals(weighted_udedge_base) method test");
            add_test(bind(&weighted_udedge_testcase1::test11, this),
                     "!equals(weighted_udedge_base) method test");
            add_test(bind(&weighted_udedge_testcase1::test12, this),
                     "==(weighted_udedge_base) method test");
            add_test(bind(&weighted_udedge_testcase1::test13, this),
                     "!=(weighted_udedge_base) method test");
        }

        bool test1() {
            return test::ccassert(sizeof(weighted_udedge_base) <= 16);
        }

        bool test2() {
            weighted_udedge_base e(2, 3, .5678);
            return test::ccassert_equals(string("2 <-> 3 0.5678"),
                                         string(e)); 
        }

        bool test3() {
            stringstream s("2 3 .5678");
            weighted_udedge_base *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new weighted_udedge_base();
                });
             
            bool retval = test::ccassert_equals(
                                  string("2 <-> 3 0.5678"),
                                  string(*e)); 
            delete e;
            return retval;
        }

        bool test4() {
            weighted_edge_base e1(2, 3, .5678);
            weighted_udedge_base e(e1);
            return test::ccassert_equals(string("2 <-> 3 0.5678"),
                                         string(e)); 
        }

        bool test5() {
            weighted_udedge_base e(2, 3, 3.0);
            return test::ccassert(utils::cmp_equal(e.get_weight(),
                                weighted_edge_base::weight_type(3.0)));
        }

        bool test6() {
            weighted_udedge_base e(2, 3, 3.1);
            return test::ccassert_equals(
                     string("2 ?-? 3 3.1"),
                     string(static_cast<weighted_edge_base>(e))); 
        }

        bool test7() {
            weighted_udedge_base e(2, 3, 3.0);
            return test::ccassert(e.get_either() ==
                                  weighted_udedge_base::vertex_type(2) || 
                                  e.get_either() ==
                                  weighted_udedge_base::vertex_type(3));
        }

        bool test8() {
            weighted_udedge_base e(2, 3, 3.0);
            return test::ccassert(e.get_other(2) ==
                                  weighted_udedge_base::vertex_type(3) || 
                                  e.get_other(3) ==
                                  weighted_udedge_base::vertex_type(2));
        }

        bool test9() {
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      []() {
                         weighted_udedge_base e(2, 3, 3.0);
                         e.get_other(4);
                      });
        }

        bool test10() {
            weighted_udedge_base e1(3, 3, 3.0);
            weighted_udedge_base e2(3, 3, 3.0);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test11() {
            weighted_udedge_base e1(3, 3, 3.0);
            weighted_udedge_base e2(4, 3, 3.0);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test12() {
            weighted_udedge_base e1(3, 3, 3.0);
            weighted_udedge_base e2(3, 3, 3.0);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test13() {
            weighted_udedge_base e1(3, 3, 3.0);
            weighted_udedge_base e2(3, 3, 3.1);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }
};

class weighted_udedge_testcase2 : public testcase {
    public :
        weighted_udedge_testcase2(const string& name = "weighted_udedge - all tests") :
                           testcase(name) {
            add_test(bind(&weighted_udedge_testcase2::test1, this),
                     "sizeof(weighted_udedge) <= 32 test");
            add_test(bind(&weighted_udedge_testcase2::test2, this),
                     "constructor-(v,w, wt) test");
            add_test(bind(&weighted_udedge_testcase2::test3, this),
                     "constructor-(cin) test");
            add_test(bind(&weighted_udedge_testcase2::test4, this),
                     "constructor-(edge_type) test");
            add_test(bind(&weighted_udedge_testcase2::test5, this),
                     "get_cmp_func method test");
            add_test(bind(&weighted_udedge_testcase2::test6, this),
                     "set_cmp_func method test");
            add_test(bind(&weighted_udedge_testcase2::test7, this),
                     "equals(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test8, this),
                     "!equals(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test9, this),
                     "==(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test10, this),
                     "!=(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test11, this),
                     ">(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test12, this),
                     ">=(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test13, this),
                     "<(object) method test");
            add_test(bind(&weighted_udedge_testcase2::test14, this),
                     "<=(object) method test");
        }

        bool test1() {
            return test::ccassert(sizeof(weighted_udedge) <= 32);
        }

        bool test2() {
            weighted_udedge e(2, 3, .5678);
            return test::ccassert_equals(string("2 <-> 3 0.5678"),
                                         string(e)); 
        }

        bool test3() {
            stringstream s("2 3 .5678");
            weighted_udedge *e;
            test::mock_stdin(
                s,
                [&e]() -> void {
                    e = new weighted_udedge();
                });
             
            bool retval = test::ccassert_equals(string("2 <-> 3 0.5678"),
                                                string(*e)); 
            delete e;
            return retval;
        }

        bool test4() {
            weighted_edge_base e1(2, 3, .5678);
            weighted_udedge e(e1);
            return test::ccassert_equals(string("2 <-> 3 0.5678"),
                                         string(e)); 
        }

        bool test5() {
            weighted_udedge e1(3, 3, .8456);
            weighted_udedge e2(3, 3, 0.7456);
            weighted_udedge::cmp_func_type& c =
                                   e1.get_cmp_func();
            return test::ccassert(c(e1, e2) > 0);
        }

        bool test6() {
            weighted_udedge e1(3, 3, .8456);
            weighted_udedge e2(3, 3, 0.7456);
            auto cmp_desc_fn =
               [](const weighted_udedge_base& lhs,
                  const weighted_udedge_base& rhs) {
                   return -weighted_udedge::
                             cmp_by_weight(lhs, rhs);
               };
            e1.set_cmp_func(*cmp_desc_fn);
            weighted_udedge::cmp_func_type& c =
                                      e1.get_cmp_func();
            return test::ccassert(c(e1, e2) < 0);
        }
        bool test7() {
            weighted_udedge e1(3, 3, .7456);
            weighted_udedge e2(3, 3, 0.7456);
            return test::ccassert(
                      (e1.equals(e2) == true) &&
                      (e1.equals(e1) == true)
                                 );
        }

        bool test8() {
            weighted_udedge e1(3, 3, .456);
            weighted_udedge e2(3, 3, 0.7456);
            return test::ccassert(
                      e1.equals(e2) == false
                                 );
        }

        bool test9() {
            weighted_udedge e1(3, 3, .7456);
            weighted_udedge e2(3, 3, 0.7456);
            return test::ccassert(e1 == e2 && e1 == e1);
        }

        bool test10() {
            weighted_udedge e1(3, 3, .456);
            weighted_udedge e2(3, 3, 0.7456);
            return test::ccassert(e1 != e2 && !(e1 != e1));
        }

        bool test11() {
            weighted_udedge e1(3, 3, .7456);
            weighted_udedge e2(3, 3, 0.6);
            return test::ccassert(e1 > e2 && !(e1 > e1));
        }

        bool test12() {
            weighted_udedge e1(3, 3, .7456);
            weighted_udedge e2(3, 3, 0.7456);
            return test::ccassert(e1 >= e2 && (e1 >= e1));
        }

        bool test13() {
            weighted_udedge e1(3, 3, .6);
            weighted_udedge e2(3, 3, 0.7456);
            return test::ccassert(e1 < e2 && !(e1 < e1));
        }

        bool test14() {
            weighted_udedge e1(3, 3, .6);
            weighted_udedge e2(3, 3, 0.7456);
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

#endif /* __WEIGHTED_UDEDGE_TESTCASES_H__ */
