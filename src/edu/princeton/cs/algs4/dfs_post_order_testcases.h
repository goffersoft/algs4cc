/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __DFS_POST_ORDER_TESTCASES_H__
#define __DFS_POST_ORDER_TESTCASES_H__

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

#include "dfs_post_order.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;
using std::range_error;
using std::deque;

using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

using edu::princeton::cs::algs4::udgraph;
using edu::princeton::cs::algs4::digraph;
using edu::princeton::cs::algs4::weighted_udgraph;
using edu::princeton::cs::algs4::weighted_digraph;
using edu::princeton::cs::algs4::flow_network;

using edu::princeton::cs::algs4::dfs_post_order;

class dfs_post_order_testcase1 : public testcase {
    public :
        dfs_post_order_testcase1(const string& name =
                    "dfs_post_order - udgraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_post_order_testcase1::test1, this),
                     "post(v) method - test");
            add_test(bind(&dfs_post_order_testcase1::test2, this),
                     "post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase1::test3, this),
                     "post() method - test");
            add_test(bind(&dfs_post_order_testcase1::test4, this),
                     "set_graph method test");
            add_test(bind(&dfs_post_order_testcase1::test5, this),
                     "reverse_post(v) method");
            add_test(bind(&dfs_post_order_testcase1::test6, this),
                     "reverse_post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase1::test7, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_post_order<udgraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.post(0) == 6 &&
                       dfs_post_order.post(1) == 4 &&
                       dfs_post_order.post(2) == 5 &&
                       dfs_post_order.post(3) == 0 &&
                       dfs_post_order.post(4) == 2 &&
                       dfs_post_order.post(5) == 3 &&
                       dfs_post_order.post(6) == 1 &&
                       dfs_post_order.post(7) == 8 &&
                       dfs_post_order.post(8) == 7 &&
                       dfs_post_order.post(9) == 12 &&
                       dfs_post_order.post(10) == 11 &&
                       dfs_post_order.post(11) == 9 &&
                       dfs_post_order.post(12) == 10);
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_post_order<udgraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.post(20);
                      }
                   );
        }

        bool test3() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_post_order<udgraph> dfs_post_order(g, true);
            deque<udgraph::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8, 7, 11, 12, 10, 9};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test4() {
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
            dfs_post_order<udgraph> dfs_post_order(g1);
            deque<udgraph::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8, 7,
                   11, 12, 10, 9, 13, 14};

            dfs_post_order.set_graph(g2);

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_post_order<udgraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.reverse_post(0) == 6 &&
                       dfs_post_order.reverse_post(1) == 8 &&
                       dfs_post_order.reverse_post(2) == 7 &&
                       dfs_post_order.reverse_post(3) == 12 &&
                       dfs_post_order.reverse_post(4) == 10 &&
                       dfs_post_order.reverse_post(5) == 9 &&
                       dfs_post_order.reverse_post(6) == 11 &&
                       dfs_post_order.reverse_post(7) == 4 &&
                       dfs_post_order.reverse_post(8) == 5 &&
                       dfs_post_order.reverse_post(9) == 0 &&
                       dfs_post_order.reverse_post(10) == 1 &&
                       dfs_post_order.reverse_post(11) == 3 &&
                       dfs_post_order.reverse_post(12) == 2);
        }

        bool test6() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_post_order<udgraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.reverse_post(20);
                      }
                   );
        }

        bool test7() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_post_order<udgraph> dfs_post_order(g, true);
            deque<udgraph::vertex_type>
                d1{9, 10, 12, 11, 7, 8, 0, 2, 1, 5, 4, 6, 3};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.reverse_post()));
        }
};

class dfs_post_order_testcase2 : public testcase {
    public :
        dfs_post_order_testcase2(const string& name =
                    "dfs_post_order - digraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_post_order_testcase2::test1, this),
                     "post(v) method - test");
            add_test(bind(&dfs_post_order_testcase2::test2, this),
                     "post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase2::test3, this),
                     "post() method - test");
            add_test(bind(&dfs_post_order_testcase2::test4, this),
                     "set_graph method test");
            add_test(bind(&dfs_post_order_testcase2::test5, this),
                     "reverse_post(v) method");
            add_test(bind(&dfs_post_order_testcase2::test6, this),
                     "reverse_post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase2::test7, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_post_order<digraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.post(0) == 6 &&
                       dfs_post_order.post(1) == 3 &&
                       dfs_post_order.post(2) == 4 &&
                       dfs_post_order.post(3) == 0 &&
                       dfs_post_order.post(4) == 1 &&
                       dfs_post_order.post(5) == 2 &&
                       dfs_post_order.post(6) == 5 &&
                       dfs_post_order.post(7) == 8 &&
                       dfs_post_order.post(8) == 7 &&
                       dfs_post_order.post(9) == 12 &&
                       dfs_post_order.post(10) == 10 &&
                       dfs_post_order.post(11) == 11 &&
                       dfs_post_order.post(12) == 9);
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_post_order<digraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.post(20);
                      }
                   );
        }

        bool test3() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_post_order<digraph> dfs_post_order(g, true);
            deque<digraph::vertex_type>
                d1{3, 4, 5, 1, 2, 6, 0,
                   8, 7, 12, 10, 11, 9};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test4() {
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
            dfs_post_order<digraph> dfs_post_order(g1);
            deque<digraph::vertex_type>
                d1{3, 4, 5, 1, 2, 6, 0, 8,
                   7, 12, 10, 11, 9, 13, 14};

            dfs_post_order.set_graph(g2);

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_post_order<digraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.reverse_post(0) == 6 &&
                       dfs_post_order.reverse_post(1) == 9 &&
                       dfs_post_order.reverse_post(2) == 8 &&
                       dfs_post_order.reverse_post(3) == 12 &&
                       dfs_post_order.reverse_post(4) == 11 &&
                       dfs_post_order.reverse_post(5) == 10 &&
                       dfs_post_order.reverse_post(6) == 7 &&
                       dfs_post_order.reverse_post(7) == 4 &&
                       dfs_post_order.reverse_post(8) == 5 &&
                       dfs_post_order.reverse_post(9) == 0 &&
                       dfs_post_order.reverse_post(10) == 2 &&
                       dfs_post_order.reverse_post(11) == 1 &&
                       dfs_post_order.reverse_post(12) == 3);
        }

        bool test6() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_post_order<digraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.reverse_post(20);
                      }
                   );
        }

        bool test7() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_post_order<digraph> dfs_post_order(g, true);
            deque<digraph::vertex_type>
                d1{9, 11, 10, 12, 7, 8,
                   0, 6, 2, 1, 5, 4, 3};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.reverse_post()));
        }
};

class dfs_post_order_testcase3 : public testcase {
    public :
        dfs_post_order_testcase3(const string& name =
                    "dfs_post_order - weighted_udgraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_post_order_testcase3::test1, this),
                     "post(v) method - test");
            add_test(bind(&dfs_post_order_testcase3::test2, this),
                     "post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase3::test3, this),
                     "post() method - test");
            add_test(bind(&dfs_post_order_testcase3::test4, this),
                     "set_graph method test");
            add_test(bind(&dfs_post_order_testcase3::test5, this),
                     "reverse_post(v) method");
            add_test(bind(&dfs_post_order_testcase3::test6, this),
                     "reverse_post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase3::test7, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_post_order<weighted_udgraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.post(0) == 6 &&
                       dfs_post_order.post(1) == 4 &&
                       dfs_post_order.post(2) == 5 &&
                       dfs_post_order.post(3) == 0 &&
                       dfs_post_order.post(4) == 2 &&
                       dfs_post_order.post(5) == 3 &&
                       dfs_post_order.post(6) == 1 &&
                       dfs_post_order.post(7) == 8 &&
                       dfs_post_order.post(8) == 7 &&
                       dfs_post_order.post(9) == 12 &&
                       dfs_post_order.post(10) == 11 &&
                       dfs_post_order.post(11) == 9 &&
                       dfs_post_order.post(12) == 10);
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_post_order<weighted_udgraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.post(20);
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
            dfs_post_order<weighted_udgraph> dfs_post_order(g, true);
            deque<weighted_udgraph::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8, 7, 11, 12, 10, 9};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test4() {
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
            dfs_post_order<weighted_udgraph> dfs_post_order(g1);
            deque<weighted_udgraph::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8, 7,
                   11, 12, 10, 9, 13, 14};

            dfs_post_order.set_graph(g2);

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_post_order<weighted_udgraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.reverse_post(0) == 6 &&
                       dfs_post_order.reverse_post(1) == 8 &&
                       dfs_post_order.reverse_post(2) == 7 &&
                       dfs_post_order.reverse_post(3) == 12 &&
                       dfs_post_order.reverse_post(4) == 10 &&
                       dfs_post_order.reverse_post(5) == 9 &&
                       dfs_post_order.reverse_post(6) == 11 &&
                       dfs_post_order.reverse_post(7) == 4 &&
                       dfs_post_order.reverse_post(8) == 5 &&
                       dfs_post_order.reverse_post(9) == 0 &&
                       dfs_post_order.reverse_post(10) == 1 &&
                       dfs_post_order.reverse_post(11) == 3 &&
                       dfs_post_order.reverse_post(12) == 2);
        }

        bool test6() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_post_order<weighted_udgraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.reverse_post(20);
                      }
                   );
        }

        bool test7() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_post_order<weighted_udgraph> dfs_post_order(g, true);
            deque<weighted_udgraph::vertex_type>
                d1{9, 10, 12, 11, 7, 8, 0, 2, 1, 5, 4, 6, 3};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.reverse_post()));
        }
};

class dfs_post_order_testcase4 : public testcase {
    public :
        dfs_post_order_testcase4(const string& name =
                    "dfs_post_order - weighted_digraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_post_order_testcase4::test1, this),
                     "post(v) method - test");
            add_test(bind(&dfs_post_order_testcase4::test2, this),
                     "post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase4::test3, this),
                     "post() method - test");
            add_test(bind(&dfs_post_order_testcase4::test4, this),
                     "set_graph method test");
            add_test(bind(&dfs_post_order_testcase4::test5, this),
                     "reverse_post(v) method");
            add_test(bind(&dfs_post_order_testcase4::test6, this),
                     "reverse_post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase4::test7, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_post_order<weighted_digraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.post(0) == 6 &&
                       dfs_post_order.post(1) == 3 &&
                       dfs_post_order.post(2) == 4 &&
                       dfs_post_order.post(3) == 0 &&
                       dfs_post_order.post(4) == 1 &&
                       dfs_post_order.post(5) == 2 &&
                       dfs_post_order.post(6) == 5 &&
                       dfs_post_order.post(7) == 8 &&
                       dfs_post_order.post(8) == 7 &&
                       dfs_post_order.post(9) == 12 &&
                       dfs_post_order.post(10) == 10 &&
                       dfs_post_order.post(11) == 11 &&
                       dfs_post_order.post(12) == 9);
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_post_order<weighted_digraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.post(20);
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
            dfs_post_order<weighted_digraph> dfs_post_order(g, true);
            deque<weighted_digraph::vertex_type>
                d1{3, 4, 5, 1, 2, 6, 0,
                   8, 7, 12, 10, 11, 9};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test4() {
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
            dfs_post_order<weighted_digraph> dfs_post_order(g1);
            deque<weighted_digraph::vertex_type>
                d1{3, 4, 5, 1, 2, 6, 0, 8,
                   7, 12, 10, 11, 9, 13, 14};

            dfs_post_order.set_graph(g2);

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_post_order<weighted_digraph> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.reverse_post(0) == 6 &&
                       dfs_post_order.reverse_post(1) == 9 &&
                       dfs_post_order.reverse_post(2) == 8 &&
                       dfs_post_order.reverse_post(3) == 12 &&
                       dfs_post_order.reverse_post(4) == 11 &&
                       dfs_post_order.reverse_post(5) == 10 &&
                       dfs_post_order.reverse_post(6) == 7 &&
                       dfs_post_order.reverse_post(7) == 4 &&
                       dfs_post_order.reverse_post(8) == 5 &&
                       dfs_post_order.reverse_post(9) == 0 &&
                       dfs_post_order.reverse_post(10) == 2 &&
                       dfs_post_order.reverse_post(11) == 1 &&
                       dfs_post_order.reverse_post(12) == 3);
        }

        bool test6() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_post_order<weighted_digraph> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.reverse_post(20);
                      }
                   );
        }

        bool test7() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_post_order<weighted_digraph> dfs_post_order(g, true);
            deque<weighted_digraph::vertex_type>
                d1{9, 11, 10, 12, 7, 8,
                   0, 6, 2, 1, 5, 4, 3};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.reverse_post()));
        }
};

class dfs_post_order_testcase5 : public testcase {
    public :
        dfs_post_order_testcase5(const string& name =
                    "dfs_post_order - flow_network - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_post_order_testcase5::test1, this),
                     "post(v) method - test");
            add_test(bind(&dfs_post_order_testcase5::test2, this),
                     "post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase5::test3, this),
                     "post() method - test");
            add_test(bind(&dfs_post_order_testcase5::test4, this),
                     "set_graph method test");
            add_test(bind(&dfs_post_order_testcase5::test5, this),
                     "reverse_post(v) method");
            add_test(bind(&dfs_post_order_testcase5::test6, this),
                     "reverse_post(v) method - exception test");
            add_test(bind(&dfs_post_order_testcase5::test7, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_post_order<flow_network> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.post(0) == 6 &&
                       dfs_post_order.post(1) == 4 &&
                       dfs_post_order.post(2) == 5 &&
                       dfs_post_order.post(3) == 0 &&
                       dfs_post_order.post(4) == 2 &&
                       dfs_post_order.post(5) == 3 &&
                       dfs_post_order.post(6) == 1 &&
                       dfs_post_order.post(7) == 8 &&
                       dfs_post_order.post(8) == 7 &&
                       dfs_post_order.post(9) == 12 &&
                       dfs_post_order.post(10) == 11 &&
                       dfs_post_order.post(11) == 9 &&
                       dfs_post_order.post(12) == 10);
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_post_order<flow_network> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.post(20);
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
            dfs_post_order<flow_network> dfs_post_order(g, true);
            deque<flow_network::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8, 7, 11, 12, 10, 9};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test4() {
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
            dfs_post_order<flow_network> dfs_post_order(g1);
            deque<flow_network::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8, 7,
                   11, 12, 10, 9, 13, 14};

            dfs_post_order.set_graph(g2);

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.post()));
        }

        bool test5() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_post_order<flow_network> dfs_post_order(g);

            return test::ccassert(
                       dfs_post_order.reverse_post(0) == 6 &&
                       dfs_post_order.reverse_post(1) == 8 &&
                       dfs_post_order.reverse_post(2) == 7 &&
                       dfs_post_order.reverse_post(3) == 12 &&
                       dfs_post_order.reverse_post(4) == 10 &&
                       dfs_post_order.reverse_post(5) == 9 &&
                       dfs_post_order.reverse_post(6) == 11 &&
                       dfs_post_order.reverse_post(7) == 4 &&
                       dfs_post_order.reverse_post(8) == 5 &&
                       dfs_post_order.reverse_post(9) == 0 &&
                       dfs_post_order.reverse_post(10) == 1 &&
                       dfs_post_order.reverse_post(11) == 3 &&
                       dfs_post_order.reverse_post(12) == 2);
        }

        bool test6() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_post_order<flow_network> dfs_post_order(g);
            range_error e("some exp");
            return test::ccassert_exception(
                      e,
                      [&dfs_post_order]() {
                          dfs_post_order.reverse_post(20);
                      }
                   );
        }

        bool test7() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_post_order<flow_network> dfs_post_order(g, true);
            deque<flow_network::vertex_type>
                d1{9, 10, 12, 11, 7, 8, 0, 2, 1, 5, 4, 6, 3};

            return test::ccassert_array_equals(
                           d1, *(dfs_post_order.reverse_post()));
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

#endif /* __DFS_POST_ORDER_TESTCASES_H__ */
