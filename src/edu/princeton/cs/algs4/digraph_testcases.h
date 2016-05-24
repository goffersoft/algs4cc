/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __DIGRAPH_TESTCASES_H__
#define __DIGRAPH_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "codeclean.h"
#include "digraph.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;
using std::invalid_argument;

using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

using edu::princeton::cs::algs4::digraph;
using edu::princeton::cs::algs4::diedge_base;

class digraph_testcase1 : public testcase {
    public :
        digraph_testcase1(const string& name = "digraph - all tests") :
                           testcase(name) {
            add_test(bind(&digraph_testcase1::test1, this),
                     "constructor-(num_v) test");
            add_test(bind(&digraph_testcase1::test2, this),
                     "constructor-(cin) test");
            add_test(bind(&digraph_testcase1::test3, this),
                     "constructor-(cin) exception test");
            add_test(bind(&digraph_testcase1::test4, this),
                     "degree method test");
            add_test(bind(&digraph_testcase1::test5, this),
                     "min_degree method test");
            add_test(bind(&digraph_testcase1::test6, this),
                     "max_degree method test");
            add_test(bind(&digraph_testcase1::test7, this),
                     "avg_degree method test");
            add_test(bind(&digraph_testcase1::test8, this),
                     "has_vertex method test");
            add_test(bind(&digraph_testcase1::test9, this),
                     "has_edge method test");
            add_test(bind(&digraph_testcase1::test9_1, this),
                     "has_edge(diedge_base) method test");
            add_test(bind(&digraph_testcase1::test10, this),
                     "has_edge method exception test");
            add_test(bind(&digraph_testcase1::test10_1, this),
                     "has_edge(diedge_base) method exception test");
            add_test(bind(&digraph_testcase1::test11, this),
                     "has_edge method exception test");
            add_test(bind(&digraph_testcase1::test11_1, this),
                     "has_edge(diedge_base) method exception test");
            add_test(bind(&digraph_testcase1::test12, this),
                     "add_edge(v,w) method test");
            add_test(bind(&digraph_testcase1::test13, this),
                     "add_edge(v,w) method exception test");
            add_test(bind(&digraph_testcase1::test14, this),
                     "add_edge(v,w) method exception test");
            add_test(bind(&digraph_testcase1::test15, this),
                     "add_edge(diedge_base) method test");
            add_test(bind(&digraph_testcase1::test16, this),
                     "add_edge(diedge_base) method exception test");
            add_test(bind(&digraph_testcase1::test17, this),
                     "add_edge(diedge_base) method exception test");
            add_test(bind(&digraph_testcase1::test18, this),
                     "get_edges(all vertices) method test");
            add_test(bind(&digraph_testcase1::test19, this),
                     "get_edges(single vertex) method test");
            add_test(bind(&digraph_testcase1::test20, this),
                     "get_edges(range of vertices) method test");
            add_test(bind(&digraph_testcase1::test21, this),
                     "get_edges(single vertex) method exception test");
            add_test(bind(&digraph_testcase1::test22, this),
                     "get_edges(vertex range) method exception test");
            add_test(bind(&digraph_testcase1::test23, this),
                     "get_edges(vertex range) method exception test");
            add_test(bind(&digraph_testcase1::test24, this),
                     "reverse method test");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
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
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      [&g]() {
                          g.add_edge(diedge_base(5,1)); 
                      }
                   );
        }

        bool test18() {
            stringstream s("4 5\n0 1\n1 1\n"
                           "1 2\n1 3\n2 3");
            digraph g(s);

            vector<diedge_base> exp;
            exp.push_back(diedge_base(0, 1));
            exp.push_back(diedge_base(1, 1));
            exp.push_back(diedge_base(1, 2));
            exp.push_back(diedge_base(1, 3));
            exp.push_back(diedge_base(2, 3));

            auto edges = g.get_edges();

            return test::ccassert_array_equals(
                           exp, *edges,
                           [](const diedge_base& lhs,
                              const diedge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test19() {
            stringstream s("4 5\n0 1\n1 1\n"
                           "1 2\n1 3\n2 3");
            digraph g(s);

            vector<diedge_base> exp;
            exp.push_back(diedge_base(1, 1));
            exp.push_back(diedge_base(1, 2));
            exp.push_back(diedge_base(1, 3));

            auto edges = g.get_edges(1);

            return test::ccassert_array_equals(
                           exp, *edges,
                           [](const diedge_base& lhs,
                              const diedge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test20() {
            stringstream s("4 5\n0 1\n1 1\n"
                           "1 2\n1 3\n2 3");
            digraph g(s);

            vector<diedge_base> exp;
            exp.push_back(diedge_base(1, 1));
            exp.push_back(diedge_base(1, 2));
            exp.push_back(diedge_base(1, 3));
            exp.push_back(diedge_base(2, 3));

            auto edges = g.get_edges(1,2);

            return test::ccassert_array_equals(
                           exp, *edges,
                           [](const diedge_base& lhs,
                              const diedge_base& rhs){
                              return lhs.equals(rhs);
                              });
        }

        bool test21() {
            stringstream s("4 3\n1 2\n2 3\n3 1");
            digraph g(s);
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      [&g]() {
                          g.get_edges(4);
                      }
                   );
        }

        bool test22() {
            stringstream s("4 3\n1 2\n2 3\n3 1");
            digraph g(s);
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      [&g]() {
                          g.get_edges(0, 4); 
                      }
                   );
        }

        bool test23() {
            stringstream s("4 3\n1 2\n2 3\n3 1");
            digraph g(s);
            invalid_argument e("some exp");
            return test::ccassert_exception(
                      e,
                      [&g]() {
                          g.get_edges(4, 5); 
                      }
                   );
        }

        bool test24() {
            stringstream s("4 5\n0 1\n1 1\n"
                           "1 2\n1 3\n2 3");
            digraph g(s);

            vector<diedge_base> exp;
            exp.push_back(diedge_base(1, 0));
            exp.push_back(diedge_base(1, 1));
            exp.push_back(diedge_base(2, 1));
            exp.push_back(diedge_base(3, 1));
            exp.push_back(diedge_base(3, 2));

            auto g_reverse_ptr = g.reverse();

            auto edges = (*g_reverse_ptr).get_edges();

            return test::ccassert_array_equals(
                           exp, *edges,
                           [](const diedge_base& lhs,
                              const diedge_base& rhs){
                              return lhs.equals(rhs);
                              });
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

#endif /* __DIGRAPH_TESTCASES_H__ */
