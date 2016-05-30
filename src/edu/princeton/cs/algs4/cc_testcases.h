/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __CC_TESTCASES_H__
#define __CC_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <deque>

#include "codeclean.h"
#include "cc.h"
#include "udgraph.h"
#include "digraph.h"
#include "weighted_udgraph.h"
#include "weighted_digraph.h"
#include "flow_network.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;
using std::invalid_argument;
using std::deque;

using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

using edu::princeton::cs::algs4::cc;
using edu::princeton::cs::algs4::udgraph;
using edu::princeton::cs::algs4::digraph;
using edu::princeton::cs::algs4::weighted_udgraph;
using edu::princeton::cs::algs4::weighted_digraph;
using edu::princeton::cs::algs4::flow_network;

class cc_testcase1 : public testcase {
    public :
        cc_testcase1(const string& name = "cc - udgraph - all tests") :
                           testcase(name) {
            add_test(bind(&cc_testcase1::test1, this),
                     "get_count method test");
            add_test(bind(&cc_testcase1::test2, this),
                     "get_id(v) method - exception test");
            add_test(bind(&cc_testcase1::test3, this),
                     "get_id(v) method - test");
            add_test(bind(&cc_testcase1::test4, this),
                     "get_size(v) method - exception test");
            add_test(bind(&cc_testcase1::test5, this),
                     "get_size(v) method test");
            add_test(bind(&cc_testcase1::test6, this),
                     "is_connected(v*, w) method - exception test");
            add_test(bind(&cc_testcase1::test7, this),
                     "is_connected(v, w*) method - exception test");
            add_test(bind(&cc_testcase1::test8, this),
                     "is_connected(v*, w*) method - exception test");
            add_test(bind(&cc_testcase1::test9, this),
                     "is_connected(v, w) method - test");
            add_test(bind(&cc_testcase1::test10, this),
                     "get_cc(cid) method - exception test");
            add_test(bind(&cc_testcase1::test11, this),
                     "get_cc(cid) method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            return test::ccassert_equals((size_t)3, cc.get_count());
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            invalid_argument e("some exp");

            return test::ccassert_exception(
                      e,
                      [&cc]() {
                          cc.get_id(13);
                      }
                 );
        }

        bool test3() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc_test(g);

            return test::ccassert_equals((cc<udgraph>::component_id_type)2,
                                         cc_test.get_id(12));
        }

        bool test4() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            invalid_argument e("some exp");

            return test::ccassert_exception(
                      e,
                      [&cc]() {
                          cc.get_size(13);
                      }
                 );
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc_test(g);

            return test::ccassert_equals((size_t)7,
                                         cc_test.get_size(6));
        }

        bool test6() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            invalid_argument e("some exp");

            return test::ccassert_exception(
                      e,
                      [&cc]() {
                          cc.is_connected(13, 3);
                      }
                 );
        }

        bool test7() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            invalid_argument e("some exp");

            return test::ccassert_exception(
                      e,
                      [&cc]() {
                          cc.is_connected(1, 20);
                      }
                 );
        }

        bool test8() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            invalid_argument e("some exp");

            return test::ccassert_exception(
                      e,
                      [&cc]() {
                          cc.is_connected(13, 20);
                      }
                 );
        }

        bool test9() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc_test(g);

            return test::ccassert(cc_test.is_connected(4, 6) == true &&
                                  cc_test.is_connected(7, 9) == false);
        }

        bool test10() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc(g);

            invalid_argument e("some exp");

            return test::ccassert_exception(
                      e,
                      [&cc]() {
                          cc.get_cc(3);
                      }
                 );
        }

        bool test11() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            cc<udgraph> cc_test(g);
            deque<udgraph::vertex_type>
                d1{0, 1, 2, 3, 4, 5, 6};

            return test::ccassert_array_equals(d1,
                                         *(cc_test.get_cc(0)));
        }
};

class cc_testcase2 : public testcase {
    public :
        cc_testcase2(const string& name = "cc - weighted_udgraph - all tests") :
                           testcase(name) {
            add_test(bind(&cc_testcase2::test1, this),
                     "get_count method test");
            add_test(bind(&cc_testcase2::test2, this),
                     "get_id(v) method - test");
            add_test(bind(&cc_testcase2::test3, this),
                     "get_size(v) method test");
            add_test(bind(&cc_testcase2::test4, this),
                     "is_connected(v, w) method - test");
            add_test(bind(&cc_testcase2::test5, this),
                     "get_cc(cid) method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            cc<weighted_udgraph> cc_test(g);

            return test::ccassert_equals((size_t)3, cc_test.get_count());
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            cc<weighted_udgraph> cc_test(g);

            return test::ccassert_equals((cc<weighted_udgraph>::component_id_type)2,
                                         cc_test.get_id(12));
        }

        bool test3() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            cc<weighted_udgraph> cc_test(g);

            return test::ccassert_equals((size_t)7,
                                         cc_test.get_size(6));
        }

        bool test4() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            cc<weighted_udgraph> cc_test(g);

            return test::ccassert(cc_test.is_connected(4, 6) == true &&
                                  cc_test.is_connected(7, 9) == false);
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            cc<weighted_udgraph> cc_test(g);
            deque<weighted_udgraph::vertex_type>
                d1{0, 1, 2, 3, 4, 5, 6};

            return test::ccassert_array_equals(d1,
                                         *(cc_test.get_cc(0)));
        }
};

class cc_testcase3 : public testcase {
    public :
        cc_testcase3(const string& name = "cc - flow_network - all tests") :
                           testcase(name) {
            add_test(bind(&cc_testcase3::test1, this),
                     "get_count method test");
            add_test(bind(&cc_testcase3::test2, this),
                     "get_id(v) method - test");
            add_test(bind(&cc_testcase3::test3, this),
                     "get_size(v) method test");
            add_test(bind(&cc_testcase3::test4, this),
                     "is_connected(v, w) method - test");
            add_test(bind(&cc_testcase3::test5, this),
                     "get_cc(cid) method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            cc<flow_network> cc_test(g);

            return test::ccassert_equals((size_t)3, cc_test.get_count());
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            cc<flow_network> cc_test(g);

            return test::ccassert_equals((cc<flow_network>::component_id_type)2,
                                         cc_test.get_id(12));
        }

        bool test3() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            cc<flow_network> cc_test(g);

            return test::ccassert_equals((size_t)7,
                                         cc_test.get_size(6));
        }

        bool test4() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            cc<flow_network> cc_test(g);

            return test::ccassert(cc_test.is_connected(4, 6) == true &&
                                  cc_test.is_connected(7, 9) == false);
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            cc<flow_network> cc_test(g);
            deque<udgraph::vertex_type>
                d1{0, 1, 2, 3, 4, 5, 6};

            return test::ccassert_array_equals(d1,
                                         *(cc_test.get_cc(0)));
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

#endif /* __CC_TESTCASES_H__ */
