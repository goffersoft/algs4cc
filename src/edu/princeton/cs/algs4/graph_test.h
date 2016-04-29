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
using edu::princeton::cs::algs4::udedge_base;
using edu::princeton::cs::algs4::diedge_base;
using edu::princeton::cs::algs4::weighted_udedge_base;
using edu::princeton::cs::algs4::weighted_diedge_base;
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
                    add_test(bind(&testcase1::test4, this),
                             "degree method test");
                    add_test(bind(&testcase1::test5, this),
                             "min_degree method test");
                    add_test(bind(&testcase1::test6, this),
                             "max_degree method test");
                    add_test(bind(&testcase1::test7, this),
                             "avg_degree method test");
                    add_test(bind(&testcase1::test8, this),
                             "has_vertex method test");
                    add_test(bind(&testcase1::test9, this),
                             "has_edge method test");
                    add_test(bind(&testcase1::test9_1, this),
                             "has_edge(udedge_base) method test");
                    add_test(bind(&testcase1::test10, this),
                             "has_edge method exception test");
                    add_test(bind(&testcase1::test10_1, this),
                             "has_edge(udedge_base) method exception test");
                    add_test(bind(&testcase1::test11, this),
                             "has_edge method exception test");
                    add_test(bind(&testcase1::test11_1, this),
                             "has_edge(udedge_base) method exception test");
                    add_test(bind(&testcase1::test12, this),
                             "add_edge(v,w) method test");
                    add_test(bind(&testcase1::test13, this),
                             "add_edge(v,w) method exception test");
                    add_test(bind(&testcase1::test14, this),
                             "add_edge(v,w) method exception test");
                    add_test(bind(&testcase1::test15, this),
                             "add_edge(udedge_base) method test");
                    add_test(bind(&testcase1::test16, this),
                             "add_edge(udedge_base) method exception test");
                    add_test(bind(&testcase1::test17, this),
                             "add_edge(udedge_base) method exception test");
                    add_test(bind(&testcase1::test18, this),
                             "get_edges(all) method exception test");
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

                bool test4() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert_equals(size_t(2), g.degree(2));
                    return retval;
                }

                bool test5() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert_equals(size_t(1), g.min_degree());
                    return retval;
                }

                bool test6() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert_equals(size_t(4), g.max_degree());
                    return retval;
                }

                bool test7() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert_equals(double(2.25), g.avg_degree());
                    return retval;
                }

                bool test8() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert(g.has_vertex(0) == true &&
                                                 g.has_vertex(4) == false);
                    return retval;
                }

                bool test9() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                         udgraph::vertex_type(0),
                                         udgraph::vertex_type(1)) &&
                                      g.has_edge(
                                         udgraph::vertex_type(1),
                                         udgraph::vertex_type(0)) &&
                                      g.has_edge(
                                         udgraph::vertex_type(0),
                                         udgraph::vertex_type(2)) == false);
                    return retval;
                }

                bool test9_1() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    bool retval = test::ccassert(
                                 g.has_edge(udedge_base(0, 1)) &&
                                 g.has_edge(udedge_base(1, 0)) &&
                                 g.has_edge(udedge_base(0, 2)) == false);
                    return retval;
                }

                bool test10() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                     udgraph::vertex_type(1),
                                     udgraph::vertex_type(5));
                              }
                           );
                }

                bool test10_1() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(udedge_base(1,5)); 
                              }
                           );
                }

                bool test11() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                     udgraph::vertex_type(5),
                                     udgraph::vertex_type(1));
                              }
                           );
                }

                bool test11_1() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(udedge_base(5,1)); 
                              }
                           );
                }

                bool test12() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    g.add_edge(0, 2);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                         udgraph::vertex_type(0),
                                         udgraph::vertex_type(2)) &&
                                      g.has_edge(
                                         udgraph::vertex_type(2),
                                         udgraph::vertex_type(0)));
                    return retval;
                }

                bool test13() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(1,5);
                              }
                           );
                }

                bool test14() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(5,1); 
                              }
                           );
                }

                bool test15() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);
                    g.add_edge(udedge_base(0, 2));
                    bool retval = test::ccassert(
                                      g.has_edge(
                                         udgraph::vertex_type(0),
                                         udgraph::vertex_type(2)) &&
                                      g.has_edge(
                                         udgraph::vertex_type(2),
                                         udgraph::vertex_type(0)));
                    return retval;
                }

                bool test16() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(udedge_base(1,5));
                              }
                           );
                }

                bool test17() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(udedge_base(5,1)); 
                              }
                           );
                }

                bool test18() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    udgraph g(s);

                    bag<udedge_base>::bag_value_type exp;
                    exp.add(udedge_base(0, 1));
                    exp.add(udedge_base(1, 0));
                    exp.add(udedge_base(1, 1));
                    exp.add(udedge_base(1, 2));
                    exp.add(udedge_base(1, 3));
                    exp.add(udedge_base(2, 1));
                    exp.add(udedge_base(2, 3));
                    exp.add(udedge_base(3, 1));
                    exp.add(udedge_base(3, 2));

                    auto edges = g.get_edges();

                    return test::ccassert_array_equals(
                                   exp, *edges,
                                   [](const udedge_base& lhs,
                                      const udedge_base& rhs){
                                      return lhs.equals(rhs);
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
                    add_test(bind(&testcase2::test4, this),
                             "degree method test");
                    add_test(bind(&testcase2::test5, this),
                             "min_degree method test");
                    add_test(bind(&testcase2::test6, this),
                             "max_degree method test");
                    add_test(bind(&testcase2::test7, this),
                             "avg_degree method test");
                    add_test(bind(&testcase2::test8, this),
                             "has_vertex method test");
                    add_test(bind(&testcase2::test9, this),
                             "has_edge method test");
                    add_test(bind(&testcase2::test9_1, this),
                             "has_edge(diedge_base) method test");
                    add_test(bind(&testcase2::test10, this),
                             "has_edge method exception test");
                    add_test(bind(&testcase2::test10_1, this),
                             "has_edge(diedge_base) method exception test");
                    add_test(bind(&testcase2::test11, this),
                             "has_edge method exception test");
                    add_test(bind(&testcase2::test11_1, this),
                             "has_edge(diedge_base) method exception test");
                    add_test(bind(&testcase2::test12, this),
                             "add_edge(v,w) method test");
                    add_test(bind(&testcase2::test13, this),
                             "add_edge(v,w) method exception test");
                    add_test(bind(&testcase2::test14, this),
                             "add_edge(v,w) method exception test");
                    add_test(bind(&testcase2::test15, this),
                             "add_edge(diedge_base) method test");
                    add_test(bind(&testcase2::test16, this),
                             "add_edge(diedge_base) method exception test");
                    add_test(bind(&testcase2::test17, this),
                             "add_edge(diedge_base) method exception test");
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

                bool test4() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert_equals(size_t(1), g.degree(2));
                    return retval;
                }

                bool test5() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert_equals(size_t(0), g.min_degree());
                    return retval;
                }

                bool test6() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert_equals(size_t(3), g.max_degree());
                    return retval;
                }

                bool test7() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert_equals(double(1.25), g.avg_degree());
                    return retval;
                }

                bool test8() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert(g.has_vertex(0) == true &&
                                                 g.has_vertex(4) == false);
                    return retval;
                }

                bool test9() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                          digraph::vertex_type(0),
                                          digraph::vertex_type(1)) &&
                                      g.has_edge(
                                          digraph::vertex_type(1),
                                          digraph::vertex_type(0)) == false &&
                                      g.has_edge(
                                          digraph::vertex_type(0),
                                          digraph::vertex_type(2)) == false);
                    return retval;
                }

                bool test9_1() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    bool retval = test::ccassert(
                                 g.has_edge(diedge_base(0, 1)) &&
                                 g.has_edge(diedge_base(1, 0)) == false &&
                                 g.has_edge(diedge_base(0, 2)) == false);
                    return retval;
                }

                bool test10() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                     digraph::vertex_type(1),
                                     digraph::vertex_type(5));
                              }
                           );
                }

                bool test10_1() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(diedge_base(1,5)); 
                              }
                           );
                }

                bool test11() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                     digraph::vertex_type(5),
                                     digraph::vertex_type(1));
                              }
                           );
                }

                bool test11_1() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(diedge_base(5,1)); 
                              }
                           );
                }

                bool test12() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    g.add_edge(0, 2);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                          digraph::vertex_type(0),
                                          digraph::vertex_type(2)) &&
                                      g.has_edge(
                                          digraph::vertex_type(2),
                                          digraph::vertex_type(0)) == false);
                    return retval;
                }

                bool test13() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(1,5); 
                              }
                           );
                }

                bool test14() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(5,1); 
                              }
                           );
                }

                bool test15() {
                    stringstream s("4 5\n0 1\n1 1\n"
                                   "1 2\n1 3\n2 3");
                    digraph g(s);
                    g.add_edge(diedge_base(0, 2));
                    bool retval = test::ccassert(
                                      g.has_edge(
                                          digraph::vertex_type(0),
                                          digraph::vertex_type(2)) &&
                                      g.has_edge(
                                          digraph::vertex_type(2),
                                          digraph::vertex_type(0)) == false);
                    return retval;
                }

                bool test16() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(diedge_base(1,5));
                              }
                           );
                }

                bool test17() {
                    stringstream s("4 3\n1 2\n2 3\n3 1");
                    digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(diedge_base(5,1)); 
                              }
                           );
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
                    add_test(bind(&testcase3::test4, this),
                             "degree method test");
                    add_test(bind(&testcase3::test5, this),
                             "min_degree method test");
                    add_test(bind(&testcase3::test6, this),
                             "max_degree method test");
                    add_test(bind(&testcase3::test7, this),
                             "avg_degree method test");
                    add_test(bind(&testcase3::test8, this),
                             "has_vertex method test");
                    add_test(bind(&testcase3::test9, this),
                             "has_edge(v,w,wt) method test");
                    add_test(bind(&testcase3::test9_1, this),
                             "has_edge(weighted_udedge_base) method test");
                    add_test(bind(&testcase3::test10, this),
                             "has_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase3::test10_1, this),
                             "has_edge(weighted_udedge_base) method exception test");
                    add_test(bind(&testcase3::test11, this),
                             "has_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase3::test11_1, this),
                             "has_edge(weighted_udedge_base) method exception test");
                    add_test(bind(&testcase3::test12, this),
                             "add_edge(v,w,wt) method test");
                    add_test(bind(&testcase3::test13, this),
                             "add_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase3::test14, this),
                             "add_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase3::test15, this),
                             "add_edge(weighted_udedge_base) method test");
                    add_test(bind(&testcase3::test16, this),
                             "add_edge(weighted_udedge_base) method exception test");
                    add_test(bind(&testcase3::test17, this),
                             "add_edge(weighted_udedge_base) method exception test");
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

                bool test4() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert_equals(size_t(2), g.degree(2));
                    return retval;
                }

                bool test5() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert_equals(size_t(1), g.min_degree());
                    return retval;
                }

                bool test6() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert_equals(size_t(4), g.max_degree());
                    return retval;
                }

                bool test7() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert_equals(double(2.25), g.avg_degree());
                    return retval;
                }

                bool test8() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert(g.has_vertex(0) == true &&
                                                 g.has_vertex(4) == false);
                    return retval;
                }

                bool test9() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(0),
                                           weighted_udgraph::vertex_type(1)) &&
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(1),
                                           weighted_udgraph::vertex_type(0)) &&
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(0),
                                           weighted_udgraph::vertex_type(2)) == false);
                    return retval;
                }

                bool test9_1() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    bool retval = test::ccassert(
                                 g.has_edge(weighted_udedge_base(0, 1, 0)) &&
                                 g.has_edge(weighted_udedge_base(1, 0, 0)) &&
                                 g.has_edge(weighted_udedge_base(0, 2, 0)) == false);
                    return retval;
                }

                bool test10() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                       weighted_udgraph::vertex_type(1),
                                       weighted_udgraph::vertex_type(5));
                              }
                           );
                }

                bool test10_1() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(weighted_udedge_base(1,5, 0)); 
                              }
                           );
                }

                bool test11() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                       weighted_udgraph::vertex_type(5),
                                       weighted_udgraph::vertex_type(1));
                              }
                           );
                }

                bool test11_1() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(weighted_udedge_base(5,1,0)); 
                              }
                           );
                }

                bool test12() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    g.add_edge(0, 2, 2.3);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(0),
                                           weighted_udgraph::vertex_type(2)) &&
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(2),
                                           weighted_udgraph::vertex_type(0)));
                    return retval;
                }

                bool test13() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(1,5, 2.3); 
                              }
                           );
                }

                bool test14() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(5,1, 2.3); 
                              }
                           );
                }

                bool test15() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    g.add_edge(weighted_udedge_base(0, 2, 2.3));
                    bool retval = test::ccassert(
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(0),
                                           weighted_udgraph::vertex_type(2)) &&
                                      g.has_edge(
                                           weighted_udgraph::vertex_type(2),
                                           weighted_udgraph::vertex_type(0)));
                    return retval;
                }

                bool test16() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(weighted_udedge_base(1,5, 2.3));
                              }
                           );
                }

                bool test17() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_udgraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(weighted_udedge_base(5,1, 2.3));
                              }
                           );
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
                    add_test(bind(&testcase4::test4, this),
                             "degree method test");
                    add_test(bind(&testcase4::test5, this),
                             "min_degree method test");
                    add_test(bind(&testcase4::test6, this),
                             "max_degree method test");
                    add_test(bind(&testcase4::test7, this),
                             "avg_degree method test");
                    add_test(bind(&testcase4::test8, this),
                             "has_vertex method test");
                    add_test(bind(&testcase4::test9, this),
                             "has_edge(v,w,wt) method test");
                    add_test(bind(&testcase4::test9_1, this),
                             "has_edge(weighted_diedge_base) method test");
                    add_test(bind(&testcase4::test10, this),
                             "has_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase4::test10_1, this),
                             "has_edge(weighted_diedge_base) method exception test");
                    add_test(bind(&testcase4::test11, this),
                             "has_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase4::test11_1, this),
                             "has_edge(weighted_diedge_base) method exception test");
                    add_test(bind(&testcase4::test12, this),
                             "add_edge(v,w,wt) method test");
                    add_test(bind(&testcase4::test13, this),
                             "add_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase4::test14, this),
                             "add_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase4::test15, this),
                             "add_edge(weighted_diedge_base) method test");
                    add_test(bind(&testcase4::test16, this),
                             "add_edge(weighted_diedge_base) method exception test");
                    add_test(bind(&testcase4::test17, this),
                             "add_edge(weighted_diedge_base) method exception test");
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

                bool test4() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert_equals(size_t(1), g.degree(2));
                    return retval;
                }

                bool test5() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert_equals(size_t(0), g.min_degree());
                    return retval;
                }

                bool test6() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert_equals(size_t(3), g.max_degree());
                    return retval;
                }

                bool test7() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert_equals(double(1.25), g.avg_degree());
                    return retval;
                }

                bool test8() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert(g.has_vertex(0) == true &&
                                                 g.has_vertex(4) == false);
                    return retval;
                }

                bool test9() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                           weighted_digraph::vertex_type(0),
                                           weighted_digraph::vertex_type(1)) &&
                                      g.has_edge(
                                           weighted_digraph::vertex_type(1),
                                           weighted_digraph::vertex_type(0)) == false &&
                                      g.has_edge(
                                           weighted_digraph::vertex_type(0),
                                           weighted_digraph::vertex_type(2)) == false);
                    return retval;
                }

                bool test9_1() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    bool retval = test::ccassert(
                                 g.has_edge(weighted_diedge_base(0, 1, 0)) &&
                                 g.has_edge(weighted_diedge_base(1, 0, 0)) == false &&
                                 g.has_edge(weighted_diedge_base(0, 2, 0)) == false);
                    return retval;
                }

                bool test10() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                       weighted_digraph::vertex_type(1),
                                       weighted_digraph::vertex_type(5));
                              }
                           );
                }

                bool test10_1() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(weighted_diedge_base(1,5, 0)); 
                              }
                           );
                }

                bool test11() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(
                                       weighted_digraph::vertex_type(5),
                                       weighted_digraph::vertex_type(1));
                              }
                           );
                }

                bool test11_1() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(weighted_diedge_base(5,1,0)); 
                              }
                           );
                }

                bool test12() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    g.add_edge(0, 2, 2.3);
                    bool retval = test::ccassert(
                                      g.has_edge(
                                           weighted_digraph::vertex_type(0),
                                           weighted_digraph::vertex_type(2)) &&
                                      g.has_edge(
                                           weighted_digraph::vertex_type(2),
                                           weighted_digraph::vertex_type(0)) == false);
                    return retval;
                }

                bool test13() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(1,5, 2.3); 
                              }
                           );
                }

                bool test14() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(5,1, 2.3); 
                              }
                           );
                }

                bool test15() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    g.add_edge(weighted_diedge_base(0, 2, 2.3));
                    bool retval = test::ccassert(
                                      g.has_edge(
                                           weighted_digraph::vertex_type(0),
                                           weighted_digraph::vertex_type(2)) &&
                                      g.has_edge(
                                           weighted_digraph::vertex_type(2),
                                           weighted_digraph::vertex_type(0)) == false);
                    return retval;
                }

                bool test16() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(weighted_diedge_base(1,5, 2.3));
                              }
                           );
                }

                bool test17() {
                    stringstream s("4 5\n0 1 .23\n1 1 .34\n"
                                   "1 2 1.43\n1 3 3.4\n2 3 5");
                    weighted_digraph g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(weighted_diedge_base(5,1, 2.3));
                              }
                           );
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
                    add_test(bind(&testcase5::test5, this),
                             "degree method test");
                    add_test(bind(&testcase5::test6, this),
                             "min_degree method test");
                    add_test(bind(&testcase5::test7, this),
                             "max_degree method test");
                    add_test(bind(&testcase5::test8, this),
                             "avg_degree method test");
                    add_test(bind(&testcase5::test9, this),
                             "has_vertex method test");
                    add_test(bind(&testcase5::test10, this),
                             "has_edge(v,w,cap) method test");
                    add_test(bind(&testcase5::test10_1, this),
                             "has_edge(flow_edge_base) method test");
                    add_test(bind(&testcase5::test11, this),
                             "has_edge(v,w,cap) method exception test");
                    add_test(bind(&testcase5::test11_1, this),
                             "has_edge(flow_edge_base) method exception test");
                    add_test(bind(&testcase5::test12, this),
                             "has_edge(v,w,cap) method exception test");
                    add_test(bind(&testcase5::test12_1, this),
                             "has_edge(flow_edge_base) method exception test");
                    add_test(bind(&testcase5::test13, this),
                             "add_edge(v,w,wt) method test");
                    add_test(bind(&testcase5::test14, this),
                             "add_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase5::test15, this),
                             "add_edge(v,w,wt) method exception test");
                    add_test(bind(&testcase5::test16, this),
                             "add_edge(flow_edge_base) method test");
                    add_test(bind(&testcase5::test17, this),
                             "add_edge(flow_edge_base) method exception test");
                    add_test(bind(&testcase5::test18, this),
                             "add_edge(flow_edge_base) method exception test");
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

                bool test5() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert_equals(size_t(2), g.degree(2));
                    return retval;
                }

                bool test6() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert_equals(size_t(1), g.min_degree());
                    return retval;
                }

                bool test7() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert_equals(size_t(4), g.max_degree());
                    return retval;
                }

                bool test8() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert_equals(double(2.25), g.avg_degree());
                    return retval;
                }

                bool test9() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert(g.has_vertex(0) == true &&
                                                 g.has_vertex(4) == false);
                    return retval;
                }

                bool test10() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert(
                                      g.has_edge(0, 1) &&
                                      g.has_edge(1, 0) == false &&
                                      g.has_edge(0, 2) == false);
                    return retval;
                }

                bool test10_1() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    bool retval = test::ccassert(
                                     g.has_edge(flow_edge_base(0, 1, 3)) &&
                                     g.has_edge(flow_edge_base(1, 0, 3)) == false &&
                                     g.has_edge(flow_edge_base(0, 2, 3)) == false);
                    return retval;
                }

                bool test11() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(1,5); 
                              }
                           );
                }

                bool test11_1() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(flow_edge_base(1,5, 3)); 
                              }
                           );
                }

                bool test12() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(5,1);
                              }
                           );
                }

                bool test12_1() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.has_edge(flow_edge(5,1,3));
                              }
                           );
                }

                bool test13() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    g.add_edge(0, 2, 5, 2.3);
                    bool retval = test::ccassert(g.has_edge(0, 2) &&
                                                 g.has_edge(2, 0) == false);
                    return retval;
                }

                bool test14() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(1,5, 5.0, 2.3); 
                              }
                           );
                }

                bool test15() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(5,1, 5.0, 2.3); 
                              }
                           );
                }

                bool test16() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    g.add_edge(flow_edge_base(0, 2, 2.3));
                    bool retval = test::ccassert(g.has_edge(0, 2) &&
                                                 g.has_edge(2, 0) == false);
                    return retval;
                }

                bool test17() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(flow_edge_base(1,5, 5.0, 2.3));
                              }
                           );
                }

                bool test18() {
                    stringstream s("4 5\n0 1 .23 .1\n1 1 .34 .3\n"
                                   "1 2 1.43 .5\n1 3 3.4 1\n2 3 5 2");
                    flow_network g(s);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&g]() {
                                  g.add_edge(flow_edge_base(5,1, 5.0, 2.3));
                              }
                           );
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
