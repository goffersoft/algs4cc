/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __DFS_TEST__
#define __DFS_TEST__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <deque>

#include "codeclean.h"
#include "udgraph.h"
#include "digraph.h"
#include "weighted_udgraph.h"
#include "weighted_digraph.h"
#include "flow_network.h"
#include "dfs.h"
#include "dfs_paths.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;
using std::range_error;
using std::deque;

using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;
using com::goffersoft::codeclean::utils;

using edu::princeton::cs::algs4::udgraph;
using edu::princeton::cs::algs4::digraph;
using edu::princeton::cs::algs4::weighted_udgraph;
using edu::princeton::cs::algs4::weighted_digraph;
using edu::princeton::cs::algs4::flow_network;
using edu::princeton::cs::algs4::dfs;
using edu::princeton::cs::algs4::dfs_paths;

class dfs_testsuite : public testsuite {
    public :
        dfs_testsuite(const string& name = "dfs") :
                             testsuite(name) {
            add_testcase(testcase1());
            add_testcase(testcase2());
            add_testcase(testcase3());
            add_testcase(testcase4());
            add_testcase(testcase5());
            add_testcase(testcase6());
            add_testcase(testcase7());
            add_testcase(testcase8());
            add_testcase(testcase9());
            add_testcase(testcase10());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "dfs - udgraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase1::test2, this),
                             "count method - test");
                    add_test(bind(&testcase1::test3, this),
                             "set_start_vertex method test");
                    add_test(bind(&testcase1::test4, this),
                             "set_start_vertex method exception test");
                    add_test(bind(&testcase1::test5, this),
                             "recompute method test");
                    add_test(bind(&testcase1::test6, this),
                             "get_graph method test");
                    add_test(bind(&testcase1::test7, this),
                             "set_graph method test");
                }

                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs<udgraph> dfs(g, 6, true);
                    deque<udgraph::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<udgraph::vertex_type> d2;

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs<udgraph> dfs(g, 6);
                    return test::ccassert_equals(dfs.get_count(), size_t(7));
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs<udgraph> dfs(g, 3);
                    deque<udgraph::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<udgraph::vertex_type> d2;

                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs<udgraph> dfs(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs]() {
                                  dfs.set_start_vertex(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs<udgraph> dfs(g, 6);
                    deque<udgraph::vertex_type> d1{7, 8};
                    deque<udgraph::vertex_type> d2;

                    dfs.set_lazy();
                    dfs.set_start_vertex(8);
                    dfs.recompute();

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test6() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs<udgraph> dfs(g, 6, true);
                    return test::ccassert_equals(&dfs.get_graph(),
                                                 (const udgraph *)&g);
                }

                bool test7() {
                    stringstream s1("13 11\n"
                                   "0 5\n4 3\n0 1\n9 12\n"
                                   "5 4\n0 2\n11 12\n9 10\n"
                                   "7 8\n9 11\n5 3\n");
                    stringstream s2("15 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g1(s1);
                    udgraph g2(s2);
                    dfs<udgraph> dfs(g1, 3, true);
                    deque<udgraph::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<udgraph::vertex_type> d2;

                    dfs.set_graph(g2);
                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g2.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }
        };

        class testcase2 : public testcase {
            public :
                testcase2(const string& name = "dfs - digraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase2::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase2::test2, this),
                             "count method - test");
                    add_test(bind(&testcase2::test3, this),
                             "set_start_vertex method test");
                    add_test(bind(&testcase2::test4, this),
                             "set_start_vertex method exception test");
                    add_test(bind(&testcase2::test5, this),
                             "recompute method test");
                    add_test(bind(&testcase2::test6, this),
                             "get_graph method test");
                    add_test(bind(&testcase2::test7, this),
                             "set_graph method test");
                }

                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs<digraph> dfs(g, 6, true);
                    deque<digraph::vertex_type> d1{3, 4, 6};
                    deque<digraph::vertex_type> d2;

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs<digraph> dfs(g, 6);
                    return test::ccassert_equals(dfs.get_count(), size_t(3));
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs<digraph> dfs(g, 3);
                    deque<digraph::vertex_type> d1{3, 4, 6};
                    deque<digraph::vertex_type> d2;

                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs<digraph> dfs(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs]() {
                                  dfs.set_start_vertex(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs<digraph> dfs(g, 6);
                    deque<digraph::vertex_type> d1{8};
                    deque<digraph::vertex_type> d2;

                    dfs.set_lazy();
                    dfs.set_start_vertex(8);
                    dfs.recompute();

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test6() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs<digraph> dfs(g, 6, true);
                    return test::ccassert_equals(&dfs.get_graph(),
                                                 (const digraph *)&g);
                }

                bool test7() {
                    stringstream s1("13 11\n"
                                   "0 5\n4 3\n0 1\n9 12\n"
                                   "5 4\n0 2\n11 12\n9 10\n"
                                   "7 8\n9 11\n5 3\n");
                    stringstream s2("15 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g1(s1);
                    digraph g2(s2);
                    dfs<digraph> dfs(g1, 3, true);
                    deque<digraph::vertex_type> d1{3, 4, 6};
                    deque<digraph::vertex_type> d2;

                    dfs.set_graph(g2);
                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g2.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }
        };

        class testcase3 : public testcase {
            public :
                testcase3(const string& name = "dfs - weighted_udgraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase3::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase3::test2, this),
                             "count method - test");
                    add_test(bind(&testcase3::test3, this),
                             "set_start_vertex method test");
                    add_test(bind(&testcase3::test4, this),
                             "set_start_vertex method exception test");
                    add_test(bind(&testcase3::test5, this),
                             "recompute method test");
                    add_test(bind(&testcase3::test6, this),
                             "get_graph method test");
                    add_test(bind(&testcase3::test7, this),
                             "set_graph method test");
                }

                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs<weighted_udgraph> dfs(g, 6, true);
                    deque<weighted_udgraph::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<weighted_udgraph::vertex_type> d2;

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs<weighted_udgraph> dfs(g, 6);
                    return test::ccassert_equals(dfs.get_count(), size_t(7));
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs<weighted_udgraph> dfs(g, 3);
                    deque<weighted_udgraph::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<weighted_udgraph::vertex_type> d2;

                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs<weighted_udgraph> dfs(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs]() {
                                  dfs.set_start_vertex(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs<weighted_udgraph> dfs(g, 6);
                    deque<weighted_udgraph::vertex_type> d1{7, 8};
                    deque<weighted_udgraph::vertex_type> d2;

                    dfs.set_lazy();
                    dfs.set_start_vertex(8);
                    dfs.recompute();

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test6() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs<weighted_udgraph> dfs(g, 6, true);
                    return test::ccassert_equals(&dfs.get_graph(),
                                                 (const weighted_udgraph *)&g);
                }

                bool test7() {
                    stringstream s1("13 11\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "7 8 5\n9 11 7\n5 3 9\n");
                    stringstream s2("15 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g1(s1);
                    weighted_udgraph g2(s2);
                    dfs<weighted_udgraph> dfs(g1, 3, true);
                    deque<weighted_udgraph::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<weighted_udgraph::vertex_type> d2;

                    dfs.set_graph(g2);
                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g2.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }
        };

        class testcase4 : public testcase {
            public :
                testcase4(const string& name = "dfs - weighted_digraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase4::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase4::test2, this),
                             "count method - test");
                    add_test(bind(&testcase4::test3, this),
                             "set_start_vertex method test");
                    add_test(bind(&testcase4::test4, this),
                             "set_start_vertex method exception test");
                    add_test(bind(&testcase4::test5, this),
                             "recompute method test");
                    add_test(bind(&testcase4::test6, this),
                             "get_graph method test");
                    add_test(bind(&testcase4::test7, this),
                             "set_graph method test");
                }

                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs<weighted_digraph> dfs(g, 6, true);
                    deque<weighted_digraph::vertex_type> d1{3, 4, 6};
                    deque<weighted_digraph::vertex_type> d2;

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs<weighted_digraph> dfs(g, 6);
                    return test::ccassert_equals(dfs.get_count(), size_t(3));
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs<weighted_digraph> dfs(g, 3);
                    deque<weighted_digraph::vertex_type> d1{3, 4, 6};
                    deque<weighted_digraph::vertex_type> d2;

                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs<weighted_digraph> dfs(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs]() {
                                  dfs.set_start_vertex(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs<weighted_digraph> dfs(g, 6);
                    deque<weighted_digraph::vertex_type> d1{8};
                    deque<weighted_digraph::vertex_type> d2;

                    dfs.set_lazy();
                    dfs.set_start_vertex(8);
                    dfs.recompute();

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test6() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs<weighted_digraph> dfs(g, 6, true);
                    return test::ccassert_equals(&dfs.get_graph(),
                                                 (const weighted_digraph *)&g);
                }

                bool test7() {
                    stringstream s1("13 11\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "7 8 5\n9 11 7\n5 3 9\n");
                    stringstream s2("15 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g1(s1);
                    weighted_digraph g2(s2);
                    dfs<weighted_digraph> dfs(g1, 3, true);
                    deque<weighted_digraph::vertex_type> d1{3, 4, 6};
                    deque<weighted_digraph::vertex_type> d2;

                    dfs.set_graph(g2);
                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g2.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }
        };

        class testcase5 : public testcase {
            public :
                testcase5(const string& name = "dfs - flow_network - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase5::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase5::test2, this),
                             "count method - test");
                    add_test(bind(&testcase5::test3, this),
                             "set_start_vertex method test");
                    add_test(bind(&testcase5::test4, this),
                             "set_start_vertex method exception test");
                    add_test(bind(&testcase5::test5, this),
                             "recompute method test");
                    add_test(bind(&testcase5::test6, this),
                             "get_graph method test");
                    add_test(bind(&testcase5::test7, this),
                             "set_graph method test");
                }

                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs<flow_network> dfs(g, 6, true);
                    deque<flow_network::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<flow_network::vertex_type> d2;

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs<flow_network> dfs(g, 6);
                    return test::ccassert_equals(dfs.get_count(), size_t(7));
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs<flow_network> dfs(g, 3);
                    deque<flow_network::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<flow_network::vertex_type> d2;

                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs<flow_network> dfs(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs]() {
                                  dfs.set_start_vertex(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs<flow_network> dfs(g, 6);
                    deque<flow_network::vertex_type> d1{7, 8};
                    deque<flow_network::vertex_type> d2;

                    dfs.set_lazy();
                    dfs.set_start_vertex(8);
                    dfs.recompute();

                    for(size_t x = 0; x < g.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }

                bool test6() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs<flow_network> dfs(g, 6, true);
                    return test::ccassert_equals(&dfs.get_graph(),
                                                 (const flow_network*)&g);
                }

                bool test7() {
                    stringstream s1("13 11\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    stringstream s2("15 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g1(s1);
                    flow_network g2(s2);
                    dfs<flow_network> dfs(g1, 3, true);
                    deque<flow_network::vertex_type> d1{0, 1, 2, 3, 4, 5, 6};
                    deque<flow_network::vertex_type> d2;

                    dfs.set_graph(g2);
                    dfs.set_start_vertex(6);

                    for(size_t x = 0; x < g2.get_num_vertices(); x++) {
                        if(dfs.has_path(x)) {
                            d2.push_back(x);
                        }
                    }
                    return test::ccassert_array_equals(d1, d2);
                }
        };

        class testcase6 : public testcase {
            public :
                testcase6(const string& name =
                            "dfs_paths - udgraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase6::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase6::test2, this),
                             "has_path method - exception test");
                    add_test(bind(&testcase6::test3, this),
                             "path_to method - test");
                    add_test(bind(&testcase6::test4, this),
                             "path_to method - exception test");
                    add_test(bind(&testcase6::test5, this),
                             "set_graph method test");
                }
                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs_paths<udgraph> dfs_paths(g, 6, true);
                    return test::ccassert(
                               dfs_paths.has_path(0) == true &&
                               dfs_paths.has_path(1) == true &&
                               dfs_paths.has_path(2) == true &&
                               dfs_paths.has_path(3) == true &&
                               dfs_paths.has_path(4) == true &&
                               dfs_paths.has_path(5) == true &&
                               dfs_paths.has_path(6) == true &&
                               dfs_paths.has_path(7) == false &&
                               dfs_paths.has_path(8) == false &&
                               dfs_paths.has_path(9) == false &&
                               dfs_paths.has_path(10) == false &&
                               dfs_paths.has_path(11) == false &&
                               dfs_paths.has_path(12) == false );
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs_paths<udgraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.has_path(20);
                              }
                           );
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs_paths<udgraph> dfs_paths(g, 6);
                    deque<udgraph::vertex_type> d1{6, 4, 3, 5, 0, 1};

                    return test::ccassert_array_equals(
                                   d1, *(dfs_paths.path_to(1)));
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g(s);
                    dfs_paths<udgraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.path_to(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s1("13 11\n"
                                   "0 5\n4 3\n0 1\n9 12\n"
                                   "5 4\n0 2\n11 12\n9 10\n"
                                   "7 8\n9 11\n5 3\n");
                    stringstream s2("15 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    udgraph g1(s1);
                    udgraph g2(s2);
                    dfs_paths<udgraph> dfs_paths(g1, 6, true);
                    deque<udgraph::vertex_type> d1{3, 4, 6, 0, 5};

                    dfs_paths.set_graph(g2);
                    dfs_paths.set_start_vertex(3);

                    return test::ccassert_array_equals(d1, *(dfs_paths.path_to(5)));
                }
        };

        class testcase7 : public testcase {
            public :
                testcase7(const string& name =
                            "dfs_paths - digraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase7::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase7::test2, this),
                             "has_path method - exception test");
                    add_test(bind(&testcase7::test3, this),
                             "path_to method - test");
                    add_test(bind(&testcase7::test4, this),
                             "path_to method - exception test");
                    add_test(bind(&testcase7::test5, this),
                             "set_graph method test");
                }
                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs_paths<digraph> dfs_paths(g, 6, true);
                    return test::ccassert(
                               dfs_paths.has_path(0) == false &&
                               dfs_paths.has_path(1) == false &&
                               dfs_paths.has_path(2) == false &&
                               dfs_paths.has_path(3) == true &&
                               dfs_paths.has_path(4) == true &&
                               dfs_paths.has_path(5) == false &&
                               dfs_paths.has_path(6) == true &&
                               dfs_paths.has_path(7) == false &&
                               dfs_paths.has_path(8) == false &&
                               dfs_paths.has_path(9) == false &&
                               dfs_paths.has_path(10) == false &&
                               dfs_paths.has_path(11) == false &&
                               dfs_paths.has_path(12) == false );
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs_paths<digraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.has_path(20);
                              }
                           );
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs_paths<digraph> dfs_paths(g, 6);
                    deque<digraph::vertex_type> d1{6, 4, 3};

                    return test::ccassert_array_equals(
                                   d1, *(dfs_paths.path_to(3)));
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g(s);
                    dfs_paths<digraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.path_to(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s1("13 11\n"
                                   "0 5\n4 3\n0 1\n9 12\n"
                                   "5 4\n0 2\n11 12\n9 10\n"
                                   "7 8\n9 11\n5 3\n");
                    stringstream s2("15 13\n"
                                   "0 5\n4 3\n0 1\n9 12\n6 4\n"
                                   "5 4\n0 2\n11 12\n9 10\n0 6\n"
                                   "7 8\n9 11\n5 3\n");
                    digraph g1(s1);
                    digraph g2(s2);
                    dfs_paths<digraph> dfs_paths(g1, 6, true);
                    deque<digraph::vertex_type> d1{0, 5, 4, 3};

                    dfs_paths.set_graph(g2);
                    dfs_paths.set_start_vertex(0);

                    return test::ccassert_array_equals(d1, *(dfs_paths.path_to(3)));
                }
        };

        class testcase8 : public testcase {
            public :
                testcase8(const string& name =
                            "dfs_paths - weighted_udgraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase8::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase8::test2, this),
                             "has_path method - exception test");
                    add_test(bind(&testcase8::test3, this),
                             "path_to method - test");
                    add_test(bind(&testcase8::test4, this),
                             "path_to method - exception test");
                    add_test(bind(&testcase8::test5, this),
                             "set_graph method test");
                }
                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs_paths<weighted_udgraph> dfs_paths(g, 6, true);
                    return test::ccassert(
                               dfs_paths.has_path(0) == true &&
                               dfs_paths.has_path(1) == true &&
                               dfs_paths.has_path(2) == true &&
                               dfs_paths.has_path(3) == true &&
                               dfs_paths.has_path(4) == true &&
                               dfs_paths.has_path(5) == true &&
                               dfs_paths.has_path(6) == true &&
                               dfs_paths.has_path(7) == false &&
                               dfs_paths.has_path(8) == false &&
                               dfs_paths.has_path(9) == false &&
                               dfs_paths.has_path(10) == false &&
                               dfs_paths.has_path(11) == false &&
                               dfs_paths.has_path(12) == false );
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs_paths<weighted_udgraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.has_path(20);
                              }
                           );
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs_paths<weighted_udgraph> dfs_paths(g, 6);
                    deque<weighted_udgraph::vertex_type> d1{6, 4, 3, 5, 0, 1};

                    return test::ccassert_array_equals(
                                   d1, *(dfs_paths.path_to(1)));
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g(s);
                    dfs_paths<weighted_udgraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.path_to(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s1("13 11\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "7 8 5\n9 11 7\n5 3 9\n");
                    stringstream s2("15 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_udgraph g1(s1);
                    weighted_udgraph g2(s2);
                    dfs_paths<weighted_udgraph> dfs_paths(g1, 6, true);
                    deque<weighted_udgraph::vertex_type> d1{3, 4, 6, 0, 5};

                    dfs_paths.set_graph(g2);
                    dfs_paths.set_start_vertex(3);

                    return test::ccassert_array_equals(d1, *(dfs_paths.path_to(5)));
                }
        };

        class testcase9 : public testcase {
            public :
                testcase9(const string& name =
                            "dfs_paths - weighted_digraph - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase9::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase9::test2, this),
                             "has_path method - exception test");
                    add_test(bind(&testcase9::test3, this),
                             "path_to method - test");
                    add_test(bind(&testcase9::test4, this),
                             "path_to method - exception test");
                    add_test(bind(&testcase9::test5, this),
                             "set_graph method test");
                }

                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs_paths<weighted_digraph> dfs_paths(g, 6, true);
                    return test::ccassert(
                               dfs_paths.has_path(0) == false &&
                               dfs_paths.has_path(1) == false &&
                               dfs_paths.has_path(2) == false &&
                               dfs_paths.has_path(3) == true &&
                               dfs_paths.has_path(4) == true &&
                               dfs_paths.has_path(5) == false &&
                               dfs_paths.has_path(6) == true &&
                               dfs_paths.has_path(7) == false &&
                               dfs_paths.has_path(8) == false &&
                               dfs_paths.has_path(9) == false &&
                               dfs_paths.has_path(10) == false &&
                               dfs_paths.has_path(11) == false &&
                               dfs_paths.has_path(12) == false );
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs_paths<weighted_digraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.has_path(20);
                              }
                           );
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs_paths<weighted_digraph> dfs_paths(g, 6);
                    deque<weighted_digraph::vertex_type> d1{6, 4, 3};

                    return test::ccassert_array_equals(
                                   d1, *(dfs_paths.path_to(3)));
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g(s);
                    dfs_paths<weighted_digraph> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.path_to(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s1("13 11\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "7 8 5\n9 11 7\n5 3 9\n");
                    stringstream s2("15 13\n"
                                   "0 5 .56\n4 3 2\n0 1 3.2\n"
                                   "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                                   "0 2 10\n11 12 5.6\n9 10 23.4\n"
                                   "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
                    weighted_digraph g1(s1);
                    weighted_digraph g2(s2);
                    dfs_paths<weighted_digraph> dfs_paths(g1, 6, true);
                    deque<weighted_digraph::vertex_type> d1{0, 5, 4, 3};

                    dfs_paths.set_graph(g2);
                    dfs_paths.set_start_vertex(0);

                    return test::ccassert_array_equals(d1, *(dfs_paths.path_to(3)));
                }
        };

        class testcase10 : public testcase {
            public :
                testcase10(const string& name =
                            "dfs_paths - flow_network - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase10::test1, this),
                             "has_path method - test");
                    add_test(bind(&testcase10::test2, this),
                             "has_path method - exception test");
                    add_test(bind(&testcase10::test3, this),
                             "path_to method - test");
                    add_test(bind(&testcase10::test4, this),
                             "path_to method - exception test");
                    add_test(bind(&testcase10::test5, this),
                             "set_graph method test");
                }
                bool test1() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs_paths<flow_network> dfs_paths(g, 6, true);
                    return test::ccassert(
                               dfs_paths.has_path(0) == true &&
                               dfs_paths.has_path(1) == true &&
                               dfs_paths.has_path(2) == true &&
                               dfs_paths.has_path(3) == true &&
                               dfs_paths.has_path(4) == true &&
                               dfs_paths.has_path(5) == true &&
                               dfs_paths.has_path(6) == true &&
                               dfs_paths.has_path(7) == false &&
                               dfs_paths.has_path(8) == false &&
                               dfs_paths.has_path(9) == false &&
                               dfs_paths.has_path(10) == false &&
                               dfs_paths.has_path(11) == false &&
                               dfs_paths.has_path(12) == false );
                }

                bool test2() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs_paths<flow_network> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.has_path(20);
                              }
                           );
                }

                bool test3() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs_paths<flow_network> dfs_paths(g, 6);
                    deque<flow_network::vertex_type> d1{6, 4, 3, 5, 0, 1};

                    return test::ccassert_array_equals(
                                   d1, *(dfs_paths.path_to(1)));
                }

                bool test4() {
                    stringstream s("13 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g(s);
                    dfs_paths<flow_network> dfs_paths(g, 3);
                    range_error e("some exp");
                    return test::ccassert_exception(
                              e,
                              [&dfs_paths]() {
                                  dfs_paths.path_to(20);
                              }
                           );
                }

                bool test5() {
                    stringstream s1("13 11\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    stringstream s2("15 13\n"
                                   "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                                   "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                                   "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                                   "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
                    flow_network g1(s1);
                    flow_network g2(s2);
                    dfs_paths<flow_network> dfs_paths(g1, 6, true);
                    deque<weighted_udgraph::vertex_type> d1{3, 4, 6, 0, 5};

                    dfs_paths.set_graph(g2);
                    dfs_paths.set_start_vertex(3);

                    return test::ccassert_array_equals(d1, *(dfs_paths.path_to(5)));
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

#endif /* __DFS_TEST__ */
