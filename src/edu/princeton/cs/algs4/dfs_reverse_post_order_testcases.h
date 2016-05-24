/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __DFS_REVERSE_POST_ORDER_TESTCASES_H__
#define __DFS_REVERSE_POST_ORDER_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <deque>

#include "codeclean.h"

#include "udgraph.h"
#include "digraph.h"
#include "weighted_udgraph.h"
#include "weighted_digraph.h"
#include "flow_network.h"

#include "dfs_reverse_post_order.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;
using std::deque;

using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

using edu::princeton::cs::algs4::udgraph;
using edu::princeton::cs::algs4::digraph;
using edu::princeton::cs::algs4::weighted_udgraph;
using edu::princeton::cs::algs4::weighted_digraph;
using edu::princeton::cs::algs4::flow_network;

using edu::princeton::cs::algs4::dfs_reverse_post_order;

class dfs_reverse_post_order_testcase1 : public testcase {
    public :
        dfs_reverse_post_order_testcase1(const string& name =
                    "dfs_reverse_post_order - udgraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_reverse_post_order_testcase1::test1, this),
                     "post() method - test");
            add_test(bind(&dfs_reverse_post_order_testcase1::test2, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_reverse_post_order<udgraph>
                    dfs_reverse_post_order(g, true);
            deque<udgraph::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8,
                   7, 11, 12, 10, 9};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.post()));
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            udgraph g(s);
            dfs_reverse_post_order<udgraph>
                         dfs_reverse_post_order(g, true);
            deque<udgraph::vertex_type>
                d1{9, 10, 12, 11, 7, 8,
                   0, 2, 1, 5, 4, 6, 3};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.reverse_post()));
        }
};

class dfs_reverse_post_order_testcase2 : public testcase {
    public :
        dfs_reverse_post_order_testcase2(const string& name =
                    "dfs_reverse_post_order - digraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_reverse_post_order_testcase2::test1, this),
                     "post() method - test");
            add_test(bind(&dfs_reverse_post_order_testcase2::test2, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_reverse_post_order<digraph>
                           dfs_reverse_post_order(g, true);
            deque<digraph::vertex_type>
                d1{3, 4, 5, 1, 2, 6, 0,
                   8, 7, 12, 10, 11, 9};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.post()));
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5\n4 3\n0 1\n9 12\n6 4\n"
                           "5 4\n0 2\n11 12\n9 10\n0 6\n"
                           "7 8\n9 11\n5 3\n");
            digraph g(s);
            dfs_reverse_post_order<digraph>
                           dfs_reverse_post_order(g, true);
            deque<digraph::vertex_type>
                d1{9, 11, 10, 12, 7, 8,
                   0, 6, 2, 1, 5, 4, 3};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.reverse_post()));
        }
};

class dfs_reverse_post_order_testcase3 : public testcase {
    public :
        dfs_reverse_post_order_testcase3(const string& name =
                    "dfs_reverse_post_order - weighted_udgraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_reverse_post_order_testcase3::test1, this),
                     "post() method - test");
            add_test(bind(&dfs_reverse_post_order_testcase3::test2, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_reverse_post_order<weighted_udgraph>
                            dfs_reverse_post_order(g, true);
            deque<weighted_udgraph::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8,
                   7, 11, 12, 10, 9};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.post()));
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_udgraph g(s);
            dfs_reverse_post_order<weighted_udgraph>
                             dfs_reverse_post_order(g, true);
            deque<weighted_udgraph::vertex_type>
                d1{9, 10, 12, 11, 7, 8,
                   0, 2, 1, 5, 4, 6, 3};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.reverse_post()));
        }
};

class dfs_reverse_post_order_testcase4 : public testcase {
    public :
        dfs_reverse_post_order_testcase4(const string& name =
                    "dfs_reverse_post_order - weighted_digraph - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_reverse_post_order_testcase4::test1, this),
                     "post() method - test");
            add_test(bind(&dfs_reverse_post_order_testcase4::test2, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_reverse_post_order<weighted_digraph>
                           dfs_reverse_post_order(g, true);
            deque<weighted_digraph::vertex_type>
                d1{3, 4, 5, 1, 2, 6, 0,
                   8, 7, 12, 10, 11, 9};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.post()));
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 .56\n4 3 2\n0 1 3.2\n"
                           "9 12 4.8\n6 4 6.4\n5 4 .12\n"
                           "0 2 10\n11 12 5.6\n9 10 23.4\n"
                           "0 6 2\n7 8 5\n9 11 7\n5 3 9\n");
            weighted_digraph g(s);
            dfs_reverse_post_order<weighted_digraph>
                             dfs_reverse_post_order(g, true);
            deque<weighted_digraph::vertex_type>
                d1{9, 11, 10, 12, 7, 8,
                   0, 6, 2, 1, 5, 4, 3};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.reverse_post()));
        }
};

class dfs_reverse_post_order_testcase5 : public testcase {
    public :
        dfs_reverse_post_order_testcase5(const string& name =
                    "dfs_reverse_post_order - flow_network - all tests") :
                           testcase(name) {
            add_test(bind(&dfs_reverse_post_order_testcase5::test1, this),
                     "post() method - test");
            add_test(bind(&dfs_reverse_post_order_testcase5::test2, this),
                     "reverse_post() method - test");
        }

        bool test1() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_reverse_post_order<flow_network>
                            dfs_reverse_post_order(g, true);
            deque<flow_network::vertex_type>
                d1{3, 6, 4, 5, 1, 2, 0, 8,
                   7, 11, 12, 10, 9};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.post()));
        }

        bool test2() {
            stringstream s("13 13\n"
                           "0 5 5 .56\n4 3 10 2\n0 1 8 3.2\n"
                           "9 12 10 4.8\n6 4 20 6.4\n5 4 5 .12\n"
                           "0 2 20 10\n11 12 10 5.6\n9 10 35.6 23.4\n"
                           "0 6 10 2\n7 8 20 5\n9 11 30 7\n5 3 15 9\n");
            flow_network g(s);
            dfs_reverse_post_order<flow_network>
                              dfs_reverse_post_order(g, true);
            deque<flow_network::vertex_type>
                d1{9, 10, 12, 11, 7, 8,
                   0, 2, 1, 5, 4, 6, 3};
            return test::ccassert_array_equals(
                           d1, *(dfs_reverse_post_order.reverse_post()));
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

#endif /* __DFS_REVERSE_POST_ORDER_TESTCASES_H__ */
