/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __GRAPH_TEST__
#define __GRAPH_TEST__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "codeclean.h"
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
using std::range_error;
using std::invalid_argument;

using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;
using com::goffersoft::codeclean::utils;

using edu::princeton::cs::algs4::udgraph;
using edu::princeton::cs::algs4::digraph;
using edu::princeton::cs::algs4::weighted_udgraph;
using edu::princeton::cs::algs4::weighted_digraph;
using edu::princeton::cs::algs4::flow_network;

class graph_testsuite : public testsuite {
    public :
        graph_testsuite(const string& name = "graph") :
                             testsuite(name) {
            add_testcase(testcase1());
            add_testcase(testcase2());
            add_testcase(testcase3());
            add_testcase(testcase4());
            add_testcase(testcase5());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "udgraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this),
                             "constructor-(num_v) test");
                    add_test(bind(&testcase1::test2, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase1::test3, this),
                             "constructor-(cin) exception test");
                }

                bool test1() {
                    udgraph g(2);
                    return test::ccassert(
                              g.get_num_vertices() == 2 &&
                              g.get_num_edges() == 0);
                }

                bool test2() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph *g;
                    test::mock_stdin(
                        s,
                        [&g]() -> void {
                            g = new udgraph();
                        });
                     
                    bool retval = test::ccassert_equals(
                                       string("num vertices : 4\n"
                                              "num edges : 3\n"
                                              "0: \n1: 2 3 \n"
                                              "2: 1 3 \n3: 2 1 \n"),
                                       string(*g));
                    delete g;
                    return retval;
                }

                bool test3() {
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
                                  stringstream s("2 3\n1 2\n2 3\n3 1");
                                  test::mock_stdin(
                                      s,
                                      []() -> void {
                                          udgraph g(cin);
                                  });
                           });
                }
        };

        class testcase2 : public testcase {
            public :
                testcase2(const string& name = "digraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase2::test1, this),
                             "constructor-(num_v) test");
                    add_test(bind(&testcase2::test2, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase2::test3, this),
                             "constructor-(cin) exception test");
                }

                bool test1() {
                    digraph g(2);
                    return test::ccassert(
                              g.get_num_vertices() == 2 &&
                              g.get_num_edges() == 0);
                }

                bool test2() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph *g;
                    test::mock_stdin(
                        s,
                        [&g]() -> void {
                            g = new digraph();
                        });
                     
                    bool retval = test::ccassert_equals(
                                       string("num vertices : 4\n"
                                             "num edges : 3\n"
                                             "0: \n"
                                             "1: 2 \n"
                                             "2: 3 \n"
                                             "3: 1 \n"),
                                       string(*g));
                    delete g;
                    return retval;
                }

                bool test3() {
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
                                  stringstream s("2 3\n1 2\n2 3\n3 1");
                                  test::mock_stdin(
                                      s,
                                      []() -> void {
                                          digraph g(cin);
                                  });
                           });
                }
        };

        class testcase3 : public testcase {
            public :
                testcase3(const string& name = "weighted_udgraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase3::test1, this),
                             "constructor-(num_v) test");
                    add_test(bind(&testcase3::test2, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase3::test3, this),
                             "constructor-(cin) exception test");
                }

                bool test1() {
                    weighted_udgraph g(2);
                    return test::ccassert(
                              g.get_num_vertices() == 2 &&
                              g.get_num_edges() == 0);
                }

                bool test2() {
                    stringstream s("4 3\n1 2 .987\n"
                                   "2 3 1.2\n3 1 90.87");
                    weighted_udgraph *g;
                    test::mock_stdin(
                        s,
                        [&g]() -> void {
                            g = new weighted_udgraph();
                        });
                     
                    bool retval = test::ccassert_equals(
                                       string("num vertices : 4\n"
                                              "num edges : 3\n"
                                              "0: \n"
                                              "1: (1 <-> 2 0.987) "
                                                 "(3 <-> 1 90.87) \n"
                                              "2: (1 <-> 2 0.987) "
                                                 "(2 <-> 3 1.2) \n"
                                              "3: (2 <-> 3 1.2) "
                                                 "(3 <-> 1 90.87) \n"),
                                       string(*g));
                    delete g;
                    return retval;
                }

                bool test3() {
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
                                  stringstream s("2 3\n1 2 8.987\n"
                                                 "2 3 9.2\n3 1 90.87");
                                  test::mock_stdin(
                                      s,
                                      []() -> void {
                                          weighted_udgraph g(cin);
                                  });
                              });
                }
        };

        class testcase4 : public testcase {
            public :
                testcase4(const string& name = "weighted_digraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase4::test1, this),
                             "constructor-(num_v) test");
                    add_test(bind(&testcase4::test2, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase4::test3, this),
                             "constructor-(cin) exception test");
                }

                bool test1() {
                    weighted_digraph g(2);
                    return test::ccassert(
                              g.get_num_vertices() == 2 &&
                              g.get_num_edges() == 0);
                }

                bool test2() {
                    stringstream s("4 3\n1 2 .987\n2 3 1.2\n3 1 90.87");
                    weighted_digraph *g;
                    test::mock_stdin(
                        s,
                        [&g]() -> void {
                            g = new weighted_digraph();
                        });
                     
                    bool retval = test::ccassert_equals(
                                       string("num vertices : 4\n"
                                              "num edges : 3\n"
                                              "0: \n"
                                              "1: (1 -> 2 0.987) \n"
                                              "2: (2 -> 3 1.2) \n"
                                              "3: (3 -> 1 90.87) \n"),
                                       string(*g));
                    delete g;
                    return retval;
                }

                bool test3() {
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
                                 stringstream s("2 3\n1 2 .987\n"
                                                "2 3 1.2\n3 1 90.87");
                                  test::mock_stdin(
                                      s,
                                      []() -> void {
                                          weighted_digraph g(cin);
                                  });
                           });
                }
        };

        class testcase5 : public testcase {
            public :
                testcase5(const string& name = "flow_network - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase5::test1, this),
                             "constructor-(num_v) test");
                    add_test(bind(&testcase5::test2, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase5::test3, this),
                             "constructor-(cin) - no flow data test");
                    add_test(bind(&testcase5::test4, this),
                             "constructor-(cin) exception test");
                }

                bool test1() {
                    flow_network g(2);
                    return test::ccassert(
                              g.get_num_vertices() == 2 &&
                              g.get_num_edges() == 0);
                }

                bool test2() {
                    stringstream s("4 3\n1 2 2 .987\n"
                                   "2 3 3.2 1.2\n"
                                   "3 1 100 90.87");
                    flow_network *g;
                    test::mock_stdin(
                        s,
                        [&g]() -> void {
                            g = new flow_network();
                        });
                    bool retval = test::ccassert_equals(
                                       string("num vertices : 4\n"
                                              "num edges : 3\n"
                                              "0: \n"
                                              "1: (1 -> 2 0.987/2) "
                                                 "(3 -> 1 90.87/100) \n"
                                              "2: (1 -> 2 0.987/2) "
                                                 "(2 -> 3 1.2/3.2) \n"
                                              "3: (2 -> 3 1.2/3.2) "
                                                 "(3 -> 1 90.87/100) \n"),
                                       string(*g));
                    delete g;
                    return retval;
                }

                bool test3() {
                    stringstream s("4 3\n1 2 2\n"
                                   "2 3 3.2\n"
                                   "3 1 100");
                    flow_network *g;
                    test::mock_stdin(
                        s,
                        [&g]() -> void {
                            g = new flow_network(cin, false);
                        });
                    bool retval = test::ccassert_equals(
                                       string("num vertices : 4\n"
                                              "num edges : 3\n"
                                              "0: \n"
                                              "1: (1 -> 2 0/2) "
                                                 "(3 -> 1 0/100) \n"
                                              "2: (1 -> 2 0/2) "
                                                 "(2 -> 3 0/3.2) \n"
                                              "3: (2 -> 3 0/3.2) "
                                                 "(3 -> 1 0/100) \n"),
                                       string(*g));
                    delete g;
                    return retval;
                }

                bool test4() {
                    invalid_argument e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
                                 stringstream s("4 3\n1 2 2 .987\n"
                                                "2 3 3.2 1.2\n"
                                                "3 1 80 90.87");
                                  test::mock_stdin(
                                      s,
                                      []() -> void {
                                          flow_network g(cin);
                                  });
                           });
                }
        };
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

#endif /* __GRAPH_TEST__ */
