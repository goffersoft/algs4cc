/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the edge class types.
 *
 ******************************************************************************/
#ifndef __EDGE_TEST_H__
#define __EDGE_TEST_H__

#include "codeclean.h"

#include "edge_testcases.h"
#include "udedge_testcases.h"
#include "diedge_testcases.h"
#include "weighted_edge_testcases.h"
#include "weighted_udedge_testcases.h"
#include "weighted_diedge_testcases.h"
#include "flow_edge_testcases.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using com::goffersoft::codeclean::testsuite;

using edu::princeton::cs::algs4::edge_testcase1;
using edu::princeton::cs::algs4::edge_testcase2;

using edu::princeton::cs::algs4::udedge_testcase1;
using edu::princeton::cs::algs4::udedge_testcase2;

using edu::princeton::cs::algs4::diedge_testcase1;
using edu::princeton::cs::algs4::diedge_testcase2;

using edu::princeton::cs::algs4::weighted_diedge_testcase1;
using edu::princeton::cs::algs4::weighted_diedge_testcase2;

using edu::princeton::cs::algs4::weighted_udedge_testcase1;
using edu::princeton::cs::algs4::weighted_udedge_testcase2;

using edu::princeton::cs::algs4::weighted_edge_testcase1;
using edu::princeton::cs::algs4::weighted_edge_testcase2;

using edu::princeton::cs::algs4::flow_edge_testcase1;
using edu::princeton::cs::algs4::flow_edge_testcase2;

class edge_testsuite : public testsuite {
    public :
        edge_testsuite(const string& name = "edge") :
                             testsuite(name) {
            add_testcase(edge_testcase1());
            add_testcase(edge_testcase2());

            add_testcase(udedge_testcase1());
            add_testcase(udedge_testcase2());

            add_testcase(diedge_testcase1());
            add_testcase(diedge_testcase2());

            add_testcase(weighted_edge_testcase1());
            add_testcase(weighted_edge_testcase2());

            add_testcase(weighted_udedge_testcase1());
            add_testcase(weighted_udedge_testcase2());

            add_testcase(weighted_diedge_testcase1());
            add_testcase(weighted_diedge_testcase2());

            add_testcase(flow_edge_testcase1());
            add_testcase(flow_edge_testcase2());
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

#endif /* __EDGE_TEST_H__ */
