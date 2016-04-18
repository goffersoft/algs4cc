/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the edge class types.
 *
 ******************************************************************************/
#ifndef __EDGE_TEST__
#define __EDGE_TEST__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "codeclean.h"
#include "edge.h"
#include "weighted_edge.h"
#include "weighted_udedge.h"
#include "weighted_diedge.h"
#include "flow_edge.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;
using std::invalid_argument;

using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;
using com::goffersoft::codeclean::utils;

using edu::princeton::cs::algs4::flow_edge_base;
using edu::princeton::cs::algs4::flow_edge;
using edu::princeton::cs::algs4::weighted_diedge_base;
using edu::princeton::cs::algs4::weighted_diedge;
using edu::princeton::cs::algs4::weighted_udedge_base;
using edu::princeton::cs::algs4::weighted_udedge;
using edu::princeton::cs::algs4::weighted_edge_base;
using edu::princeton::cs::algs4::weighted_edge;
using edu::princeton::cs::algs4::edge_base;
using edu::princeton::cs::algs4::edge;

class edge_testsuite : public testsuite {
    public :
        edge_testsuite(const string& name = "edge") :
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
                testcase1(const string& name = "edge_base - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this),
                             "sizeof(edge_base) <= 8 test");
                    add_test(bind(&testcase1::test2, this),
                             "constructor-(v,w) test");
                    add_test(bind(&testcase1::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase1::test4, this),
                                  "get_first method test");
                    add_test(bind(&testcase1::test5, this),
                                  "get_second method test");
                }

                bool test1() {
                    return test::ccassert(sizeof(edge_base) <= 8);
                }

                bool test2() {
                    edge_base e(2, 3);
                    return test::ccassert_equals(string("2 ?-? 3"), e.to_string()); 
                }

                bool test3() {
                    stringstream s("2 3");
                    edge_base *e;
                    test::mock_stdin(
                        s,
                        [&e]() -> void {
                            e = new edge_base();
                        });
                     
                    bool retval = test::ccassert_equals(string("2 ?-? 3"), e->to_string()); 
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

        };

        class testcase2 : public testcase {
            public :
                testcase2(const string& name = "edge - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase2::test1, this),
                             "sizeof(edge) <= 24 test");
                    add_test(bind(&testcase2::test2, this),
                             "constructor-(v,w) test");
                    add_test(bind(&testcase2::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase2::test4, this),
                             "get_cmp_func method test");
                    add_test(bind(&testcase2::test5, this),
                             "set_cmp_func method test");
                    add_test(bind(&testcase2::test6, this),
                             "equals(object) method test");
                    add_test(bind(&testcase2::test7, this),
                             "!equals(object) method test");
                    add_test(bind(&testcase2::test8, this),
                             "==(object) method test");
                    add_test(bind(&testcase2::test9, this),
                             "!=(object) method test");
                    add_test(bind(&testcase2::test10, this),
                             ">(object) method test");
                    add_test(bind(&testcase2::test11, this),
                             ">=(object) method test");
                    add_test(bind(&testcase2::test12, this),
                             "<(object) method test");
                    add_test(bind(&testcase2::test13, this),
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
                    edge e1(2, 4);
                    edge e2(2, 3);
                    edge::cmp_func_type& c = e1.get_cmp_func();
                    return test::ccassert(c(e1, e2) > 0);
                }

                bool test5() {
                    edge e1(2, 3);
                    edge e2(3, 3);
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

        class testcase3 : public testcase {
            public :
                testcase3(const string& name = "weighted_edge_base - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase3::test1, this),
                             "sizeof(weighted_edge_base) <= 16 test");
                    add_test(bind(&testcase3::test2, this),
                             "constructor-(v,w, wt) test");
                    add_test(bind(&testcase3::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase3::test4, this),
                                  "get_weight method test");
                }

                bool test1() {
                    return test::ccassert(sizeof(weighted_edge_base) <= 16);
                }

                bool test2() {
                    weighted_edge_base e(2, 3, 3.1);
                    return test::ccassert_equals(string("2 ?-? 3 3.1"), e.to_string()); 
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
                                                        e->to_string()); 
                    delete e;
                    return retval;
                }

                bool test4() {
                    weighted_edge_base e(2, 3, 3.0);
                    return test::ccassert(utils::cmp_equal(e.get_weight(),
                                        weighted_edge_base::weight_type(3.0)));
                }
        };

        class testcase4 : public testcase {
            public :
                testcase4(const string& name = "weighted_edge - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase4::test1, this),
                             "sizeof(weighted_edge) <= 32 test");
                    add_test(bind(&testcase4::test2, this),
                             "constructor-(v,w, wt) test");
                    add_test(bind(&testcase4::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase4::test4, this),
                             "get_cmp_func method test");
                    add_test(bind(&testcase4::test5, this),
                             "set_cmp_func method test");
                    add_test(bind(&testcase4::test6, this),
                             "equals(object) method test");
                    add_test(bind(&testcase4::test7, this),
                             "!equals(object) method test");
                    add_test(bind(&testcase4::test8, this),
                             "==(object) method test");
                    add_test(bind(&testcase4::test9, this),
                             "!=(object) method test");
                    add_test(bind(&testcase4::test10, this),
                             ">(object) method test");
                    add_test(bind(&testcase4::test11, this),
                             ">=(object) method test");
                    add_test(bind(&testcase4::test12, this),
                             "<(object) method test");
                    add_test(bind(&testcase4::test13, this),
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
                    e1.set_cmp_func(
                           weighted_edge::cmp_by_weight_descending);
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

        class testcase5 : public testcase {
            public :
                testcase5(const string& name = "weighted_udedge_base - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase5::test1, this),
                             "sizeof(weighted_udedge_base) <= 16 test");
                    add_test(bind(&testcase5::test2, this),
                             "constructor-(v,w, wt) test");
                    add_test(bind(&testcase5::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase5::test4, this),
                             "constructor-(edge_type) test");
                    add_test(bind(&testcase5::test5, this),
                                  "get_weight method test");
                    add_test(bind(&testcase5::test6, this),
                                  "conversion operator test");
                    add_test(bind(&testcase5::test7, this),
                                  "get_either method test");
                    add_test(bind(&testcase5::test8, this),
                                  "get_other method test");
                    add_test(bind(&testcase5::test9, this),
                                  "get_other method exception test");
                }

                bool test1() {
                    return test::ccassert(sizeof(weighted_udedge_base) <= 16);
                }

                bool test2() {
                    weighted_udedge_base e(2, 3, .5678);
                    return test::ccassert_equals(string("2 <-> 3 0.5678"),
                                                 e.to_string()); 
                }

                bool test3() {
                    stringstream s("2 3 .5678");
                    weighted_udedge_base *e;
                    test::mock_stdin(
                        s,
                        [&e]() -> void {
                            e = new weighted_udedge_base();
                        });
                     
                    bool retval = test::ccassert_equals(string("2 <-> 3 0.5678"),
                                                        e->to_string()); 
                    delete e;
                    return retval;
                }

                bool test4() {
                    weighted_edge_base e1(2, 3, .5678);
                    weighted_udedge_base e(e1);
                    return test::ccassert_equals(string("2 <-> 3 0.5678"),
                                                 e.to_string()); 
                }

                bool test5() {
                    weighted_udedge_base e(2, 3, 3.0);
                    return test::ccassert(utils::cmp_equal(e.get_weight(),
                                        weighted_edge_base::weight_type(3.0)));
                }

                bool test6() {
                    weighted_udedge_base e(2, 3, 3.1);
                    return test::ccassert_equals(string("2 ?-? 3 3.1"),
                                                 weighted_udedge_base::edge_type(e).to_string()); 
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
        };

        class testcase6 : public testcase {
            public :
                testcase6(const string& name = "weighted_udedge - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase6::test1, this),
                             "sizeof(weighted_udedge) <= 32 test");
                    add_test(bind(&testcase6::test2, this),
                             "constructor-(v,w, wt) test");
                    add_test(bind(&testcase6::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase6::test4, this),
                             "constructor-(edge_type) test");
                    add_test(bind(&testcase6::test5, this),
                             "get_cmp_func method test");
                    add_test(bind(&testcase6::test6, this),
                             "set_cmp_func method test");
                    add_test(bind(&testcase6::test7, this),
                             "equals(object) method test");
                    add_test(bind(&testcase6::test8, this),
                             "!equals(object) method test");
                    add_test(bind(&testcase6::test9, this),
                             "==(object) method test");
                    add_test(bind(&testcase6::test10, this),
                             "!=(object) method test");
                    add_test(bind(&testcase6::test11, this),
                             ">(object) method test");
                    add_test(bind(&testcase6::test12, this),
                             ">=(object) method test");
                    add_test(bind(&testcase6::test13, this),
                             "<(object) method test");
                    add_test(bind(&testcase6::test14, this),
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
                    e1.set_cmp_func(
                           weighted_udedge::cmp_by_weight_descending);
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

        class testcase7 : public testcase {
            public :
                testcase7(const string& name = "weighted_diedge_base - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase7::test1, this),
                             "sizeof(weighted_diedge_base) <= 16 test");
                    add_test(bind(&testcase7::test2, this),
                             "constructor-(v,w, wt) test");
                    add_test(bind(&testcase7::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase7::test4, this),
                             "constructor-(edge_type) test");
                    add_test(bind(&testcase7::test5, this),
                                  "get_weight method test");
                    add_test(bind(&testcase7::test6, this),
                                  "conversion operator test");
                    add_test(bind(&testcase7::test7, this),
                                  "get_from method test");
                    add_test(bind(&testcase7::test8, this),
                                  "get_to method test");
                }

                bool test1() {
                    return test::ccassert(sizeof(weighted_diedge_base) <= 16);
                }

                bool test2() {
                    weighted_diedge_base e(2, 3, .5678);
                    return test::ccassert_equals(string("2 -> 3 0.5678"),
                                                 e.to_string()); 
                }

                bool test3() {
                    stringstream s("2 3 .5678");
                    weighted_diedge_base *e;
                    test::mock_stdin(
                        s,
                        [&e]() -> void {
                            e = new weighted_diedge_base();
                        });
                     
                    bool retval = test::ccassert_equals(string("2 -> 3 0.5678"),
                                                        e->to_string()); 
                    delete e;
                    return retval;
                }

                bool test4() {
                    weighted_edge_base e1(2, 3, .5678);
                    weighted_diedge_base e(e1);
                    return test::ccassert_equals(string("2 -> 3 0.5678"),
                                                 e.to_string()); 
                }

                bool test5() {
                    weighted_diedge_base e(2, 3, 3.0);
                    return test::ccassert(utils::cmp_equal(e.get_weight(),
                                        weighted_edge_base::weight_type(3.0)));
                }

                bool test6() {
                    weighted_diedge_base e(2, 3, 3.1);
                    return test::ccassert_equals(string("2 ?-? 3 3.1"),
                                                 weighted_diedge_base::edge_type(e).to_string()); 
                }

                bool test7() {
                    weighted_diedge_base e(2, 3, 3.0);
                    return test::ccassert_equals(e.get_from(),
                                          weighted_diedge_base::vertex_type(2));
                }

                bool test8() {
                    weighted_diedge_base e(2, 3, 3.0);
                    return test::ccassert_equals(e.get_to(),
                                          weighted_diedge_base::vertex_type(3));
                }
        };

        class testcase8 : public testcase {
            public :
                testcase8(const string& name = "weighted_diedge - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase8::test1, this),
                             "sizeof(weighted_diedge) <= 32 test");
                    add_test(bind(&testcase8::test2, this),
                             "constructor-(v,w, wt) test");
                    add_test(bind(&testcase8::test3, this),
                             "constructor-(cin) test");
                    add_test(bind(&testcase8::test4, this),
                             "constructor-(edge_type) test");
                    add_test(bind(&testcase8::test5, this),
                             "get_cmp_func method test");
                    add_test(bind(&testcase8::test6, this),
                             "set_cmp_func method test");
                    add_test(bind(&testcase8::test7, this),
                             "equals(object) method test");
                    add_test(bind(&testcase8::test8, this),
                             "!equals(object) method test");
                    add_test(bind(&testcase8::test9, this),
                             "==(object) method test");
                    add_test(bind(&testcase8::test10, this),
                             "!=(object) method test");
                    add_test(bind(&testcase8::test11, this),
                             ">(object) method test");
                    add_test(bind(&testcase8::test12, this),
                             ">=(object) method test");
                    add_test(bind(&testcase8::test13, this),
                             "<(object) method test");
                    add_test(bind(&testcase8::test14, this),
                             "<=(object) method test");
                }

                bool test1() {
                    return test::ccassert(sizeof(weighted_diedge) <= 32);
                }

                bool test2() {
                    weighted_diedge e(2, 3, .5678);
                    return test::ccassert_equals(string("2 -> 3 0.5678"),
                                                        string(e)); 
                }

                bool test3() {
                    stringstream s("2 3 .5678");
                    weighted_diedge *e;
                    test::mock_stdin(
                        s,
                        [&e]() -> void {
                            e = new weighted_diedge();
                        });
                     
                    bool retval = test::ccassert_equals(string("2 -> 3 0.5678"),
                                                        string(*e)); 
                    delete e;
                    return retval;
                }

                bool test4() {
                    weighted_edge_base e1(2, 3, .5678);
                    weighted_diedge e(e1);
                    return test::ccassert_equals(string("2 -> 3 0.5678"),
                                                 string(e)); 
                }

                bool test5() {
                    weighted_diedge e1(3, 3, .8456);
                    weighted_diedge e2(3, 3, 0.7456);
                    weighted_diedge::cmp_func_type& c =
                                           e1.get_cmp_func();
                    return test::ccassert(c(e1, e2) > 0);
                }

                bool test6() {
                    weighted_diedge e1(3, 3, .8456);
                    weighted_diedge e2(3, 3, 0.7456);
                    e1.set_cmp_func(
                           weighted_diedge::cmp_by_weight_descending);
                    weighted_diedge::cmp_func_type& c =
                                              e1.get_cmp_func();
                    return test::ccassert(c(e1, e2) < 0);
                }

                bool test7() {
                    weighted_diedge e1(3, 3, .7456);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(
                              (e1.equals(e2) == true) &&
                              (e1.equals(e1) == true)
                                         );
                }

                bool test8() {
                    weighted_diedge e1(3, 3, .456);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(
                              e1.equals(e2) == false
                                         );
                }

                bool test9() {
                    weighted_diedge e1(3, 3, .7456);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(e1 == e2 && e1 == e1);
                }

                bool test10() {
                    weighted_diedge e1(3, 3, .456);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(e1 != e2 && !(e1 != e1));
                }

                bool test11() {
                    weighted_diedge e1(3, 3, .7456);
                    weighted_diedge e2(3, 3, 0.6);
                    return test::ccassert(e1 > e2 && !(e1 > e1));
                }

                bool test12() {
                    weighted_diedge e1(3, 3, .7456);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(e1 >= e2 && (e1 >= e1));
                }

                bool test13() {
                    weighted_diedge e1(3, 3, .6);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(e1 < e2 && !(e1 < e1));
                }

                bool test14() {
                    weighted_diedge e1(3, 3, .6);
                    weighted_diedge e2(3, 3, 0.7456);
                    return test::ccassert(e1 <= e2 && (e1 <= e1));
                }
        };

        class testcase9 : public testcase {
            public :
                testcase9(const string& name = "flow_edge_base - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase9::test1, this),
                             "sizeof(flow_edge_base) == 24 test");
                    add_test(bind(&testcase9::test2, this),
                             "constructor-(v, w, flow, capacity) test");
                    add_test(bind(&testcase9::test3, this),
                             "constructor-(v, w, flow, capacity) exception test");
                    add_test(bind(&testcase9::test4, this),
                             "constructor-(v, w, capacity) test");
                    add_test(bind(&testcase9::test5, this),
                             "constructor-(cin - with flow) test");
                    add_test(bind(&testcase9::test6, this),
                             "constructor-(cin - without flow) test");
                    add_test(bind(&testcase9::test7, this),
                                  "get_from method test");
                    add_test(bind(&testcase9::test8, this),
                                  "get_to method test");
                    add_test(bind(&testcase9::test9, this),
                                  "get_other method test");
                    add_test(bind(&testcase9::test10, this),
                                  "get_other method exception test");
                    add_test(bind(&testcase9::test11, this),
                                  "get_flow method test");
                    add_test(bind(&testcase9::test12, this),
                                  "get_capacity method test");
                    add_test(bind(&testcase9::test13, this),
                                  "get_residual_capacity_to - forward method test");
                    add_test(bind(&testcase9::test14, this),
                                  "get_residual_capacity_to - backward method test");
                    add_test(bind(&testcase9::test15, this),
                                  "get_residual_capacity_to - exception method test");
                    add_test(bind(&testcase9::test16, this),
                                  "add_residual_flow_to - forward method test");
                    add_test(bind(&testcase9::test17, this),
                                  "add_residual_flow_to - backward method test");
                    add_test(bind(&testcase9::test18, this),
                                  "add_residual_flow_to - exception method test");
                    add_test(bind(&testcase9::test19, this),
                                  "add_residual_flow_to - exception method test");
                }

                bool test1() {
                    return test::ccassert(sizeof(flow_edge_base) == 24);
                }

                bool test2() {
                    flow_edge_base e(2, 3, 10, 5.3);
                    return test::ccassert_equals(string("2 -> 3 5.3/10"),
                                                        e.to_string());
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
                                                        e.to_string());
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
                                                        e->to_string()); 
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
                                                        e->to_string()); 
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
        };

        class testcase10 : public testcase {
            public :
                testcase10(const string& name = "flow_edge - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase10::test1, this),
                             "sizeof(flow_edge) == 40 test");
                    add_test(bind(&testcase10::test2, this),
                             "constructor-(v, w, flow, capacity) test");
                    add_test(bind(&testcase10::test3, this),
                             "constructor-(v, w, flow, capacity) exception test");
                    add_test(bind(&testcase10::test4, this),
                             "constructor-(v, w, capacity) test");
                    add_test(bind(&testcase10::test5, this),
                             "constructor-(cin - with flow) test");
                    add_test(bind(&testcase10::test6, this),
                             "constructor-(cin - without flow) test");
                    add_test(bind(&testcase10::test7, this),
                             "get_cmp_func method test");
                    add_test(bind(&testcase10::test8, this),
                             "set_cmp_func method test");
                    add_test(bind(&testcase10::test9, this),
                             "equals(object) method test");
                    add_test(bind(&testcase10::test10, this),
                             "!equals(object) method test");
                    add_test(bind(&testcase10::test11, this),
                             "==(object) method test");
                    add_test(bind(&testcase10::test12, this),
                             "!=(object) method test");
                    add_test(bind(&testcase10::test13, this),
                             ">(object) method test");
                    add_test(bind(&testcase10::test14, this),
                             ">=(object) method test");
                    add_test(bind(&testcase10::test15, this),
                             "<(object) method test");
                    add_test(bind(&testcase10::test16, this),
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
                    flow_edge e2(4, 3, 10, 5);
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

#endif /* __EDGE_TEST__ */
