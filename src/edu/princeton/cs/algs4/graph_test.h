/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __GRAPH_TEST_H__
#define __GRAPH_TEST_H__

#include "codeclean.h"

#include "graph_base_testcases.h"
#include "udgraph_testcases.h"
#include "digraph_testcases.h"
#include "weighted_udgraph_testcases.h"
#include "weighted_digraph_testcases.h"
#include "flow_network_testcases.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;

using edu::princeton::cs::algs4::graph_base_testcase1;

using edu::princeton::cs::algs4::udgraph_testcase1;

using edu::princeton::cs::algs4::digraph_testcase1;

using edu::princeton::cs::algs4::weighted_udgraph_testcase1;

using edu::princeton::cs::algs4::weighted_digraph_testcase1;

using edu::princeton::cs::algs4::flow_network_testcase1;

class graph_testsuite : public testsuite {
    public :
        graph_testsuite(const string& name = "graph") :
                             testsuite(name) {
            add_testcase(graph_base_testcase1());

            add_testcase(udgraph_testcase1());

            add_testcase(digraph_testcase1());

            add_testcase(weighted_udgraph_testcase1());

            add_testcase(weighted_digraph_testcase1());

            add_testcase(flow_network_testcase1());
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

#endif /* __GRAPH_TEST_H__ */
