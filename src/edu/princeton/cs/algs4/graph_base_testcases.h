/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __GRAPH_BASE_TESTCASES_H__
#define __GRAPH_BASE_TESTCASES_H__

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "codeclean.h"

#include "graph_base.h"
#include "edge.h"
#include "udedge.h"
#include "diedge.h"
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

using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;
using com::goffersoft::codeclean::utils;

using edu::princeton::cs::algs4::edge_base;
using edu::princeton::cs::algs4::edge;
using edu::princeton::cs::algs4::udedge_base;
using edu::princeton::cs::algs4::udedge;
using edu::princeton::cs::algs4::diedge_base;
using edu::princeton::cs::algs4::diedge;
using edu::princeton::cs::algs4::weighted_edge_base;
using edu::princeton::cs::algs4::weighted_edge;
using edu::princeton::cs::algs4::weighted_udedge_base;
using edu::princeton::cs::algs4::weighted_udedge;
using edu::princeton::cs::algs4::weighted_diedge_base;
using edu::princeton::cs::algs4::weighted_diedge;

class graph_base_testcase1 : public testcase {
    public :
        graph_base_testcase1(const string& name = "graph_base - all tests") :
                           testcase(name) {
            add_test(bind(&graph_base_testcase1::test1, this),
                     "get_vertex(vertex_type, vertex_type) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test2, this),
                     "get_vertex(vertex_type, edge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test3, this),
                     "get_vertex(vertex_type, edge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test4, this),
                     "get_vertex(vertex_type, edge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test5, this),
                     "get_vertex(vertex_type, edge) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test6, this),
                     "get_vertex(vertex_type, udedge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test7, this),
                     "get_vertex(vertex_type, udedge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test8, this),
                     "get_vertex(vertex_type, udedge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test9, this),
                     "get_vertex(vertex_type, udedge) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test10, this),
                     "get_vertex(vertex_type, diedge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test11, this),
                     "get_vertex(vertex_type, diedge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test12, this),
                     "get_vertex(vertex_type, diedge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test13, this),
                     "get_vertex(vertex_type, diedge) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test14, this),
                     "get_vertex(vertex_type, weighted_edge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test15, this),
                     "get_vertex(vertex_type, weighted_edge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test16, this),
                     "get_vertex(vertex_type, weighted_edge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test17, this),
                     "get_vertex(vertex_type, weighted_edge) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test18, this),
                     "get_vertex(vertex_type, weighted_udedge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test19, this),
                     "get_vertex(vertex_type, weighted_udedge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test20, this),
                     "get_vertex(vertex_type, weighted_udedge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test21, this),
                     "get_vertex(vertex_type, weighted_udedge) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test22, this),
                     "get_vertex(vertex_type, weighted_diedge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test23, this),
                     "get_vertex(vertex_type, weighted_diedge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test24, this),
                     "get_vertex(vertex_type, weighted_diedge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test25, this),
                     "get_vertex(vertex_type, weighted_diedge) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test26, this),
                     "get_vertex(vertex_type, flow_edge_base) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test27, this),
                     "get_vertex(vertex_type, flow_edge_base) "
                     "static method exception test");
            add_test(bind(&graph_base_testcase1::test28, this),
                     "get_vertex(vertex_type, flow_edge) "
                     "static method test");
            add_test(bind(&graph_base_testcase1::test29, this),
                     "get_vertex(vertex_type, flow_edge) "
                     "static method exception test");
        }

        bool test1() {
            return test::ccassert(graph_base::get_vertex(
                                     graph_base::vertex_type(2),
                                     graph_base::vertex_type(3)) == 3);
        }

        bool test2() {
            edge_base e(2, 3);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), e) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), e) == 2);
        }

        bool test3() {
            edge_base e(2, 3);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, e); 
                      }
                   );
        }

        bool test4() {
            edge e(2, 3);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test5() {
            edge e(2, 3);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test6() {
            udedge_base e(2, 3);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test7() {
            udedge_base e(2, 3);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test8() {
            udedge e(2, 3);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test9() {
            udedge e(2, 3);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test10() {
            diedge_base e(2, 3);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test11() {
            diedge_base e(2, 3);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test12() {
            diedge e(2, 3);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test13() {
            diedge e(2, 3);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test14() {
            weighted_edge_base e(2, 3, 3.4);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test15() {
            weighted_edge_base e(2, 3, 3.4);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test16() {
            weighted_edge e(2, 3, 3.4);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test17() {
            weighted_edge e(2, 3, 3.4);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test18() {
            weighted_udedge_base e(2, 3, 3.4);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test19() {
            weighted_udedge_base e(2, 3, 3.4);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test20() {
            weighted_udedge e(2, 3, 3.4);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test21() {
            weighted_udedge e(2, 3, 3.4);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test22() {
            weighted_diedge_base e(2, 3, 3.4);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test23() {
            weighted_diedge_base e(2, 3, 3.4);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test24() {
            weighted_diedge e(2, 3, 3.4);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test25() {
            weighted_diedge e(2, 3, 3.4);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test26() {
            flow_edge_base e(2, 3, 3.4, 2.1);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test27() {
            flow_edge_base e(2, 3, 3.4, 2.1);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
        }

        bool test28() {
            flow_edge e(2, 3, 3.4, 2.1);
            return test::ccassert(graph_base::get_vertex(
                                        graph_base::vertex_type(2), edge_base(e)) == 3 &&
                                  graph_base::get_vertex(
                                        graph_base::vertex_type(3), edge_base(e)) == 2);
        }

        bool test29() {
            flow_edge e(2, 3, 3.4, 2.1);
            invalid_argument ex("some exp");
            return test::ccassert_exception(
                      ex,
                      [&e]() {
                          graph_base::get_vertex(4, edge_base(e)); 
                      }
                   );
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

#endif /* __GRAPH_BASE_TESTCASES_H__ */
