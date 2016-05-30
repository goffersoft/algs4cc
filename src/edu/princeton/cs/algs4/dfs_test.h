/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the graph class types.
 *
 ******************************************************************************/
#ifndef __DFS_TEST_H__
#define __DFS_TEST_H__

#include "codeclean.h"

#include "dfs_testcases.h"
#include "dfs_paths_testcases.h"
#include "dfs_pre_order_testcases.h"
#include "dfs_post_order_testcases.h"
#include "dfs_reverse_post_order_testcases.h"
#include "dfs_order_testcases.h"
#include "cc_testcases.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using com::goffersoft::codeclean::testsuite;

using edu::princeton::cs::algs4::dfs_testcase1;
using edu::princeton::cs::algs4::dfs_testcase2;
using edu::princeton::cs::algs4::dfs_testcase3;
using edu::princeton::cs::algs4::dfs_testcase4;
using edu::princeton::cs::algs4::dfs_testcase5;

using edu::princeton::cs::algs4::dfs_paths_testcase1;
using edu::princeton::cs::algs4::dfs_paths_testcase2;
using edu::princeton::cs::algs4::dfs_paths_testcase3;
using edu::princeton::cs::algs4::dfs_paths_testcase4;
using edu::princeton::cs::algs4::dfs_paths_testcase5;

using edu::princeton::cs::algs4::dfs_pre_order_testcase1;
using edu::princeton::cs::algs4::dfs_pre_order_testcase2;
using edu::princeton::cs::algs4::dfs_pre_order_testcase3;
using edu::princeton::cs::algs4::dfs_pre_order_testcase4;
using edu::princeton::cs::algs4::dfs_pre_order_testcase5;

using edu::princeton::cs::algs4::dfs_post_order_testcase1;
using edu::princeton::cs::algs4::dfs_post_order_testcase2;
using edu::princeton::cs::algs4::dfs_post_order_testcase3;
using edu::princeton::cs::algs4::dfs_post_order_testcase4;
using edu::princeton::cs::algs4::dfs_post_order_testcase5;

using edu::princeton::cs::algs4::dfs_reverse_post_order_testcase1;
using edu::princeton::cs::algs4::dfs_reverse_post_order_testcase2;
using edu::princeton::cs::algs4::dfs_reverse_post_order_testcase3;
using edu::princeton::cs::algs4::dfs_reverse_post_order_testcase4;
using edu::princeton::cs::algs4::dfs_reverse_post_order_testcase5;

using edu::princeton::cs::algs4::dfs_order_testcase1;
using edu::princeton::cs::algs4::dfs_order_testcase2;
using edu::princeton::cs::algs4::dfs_order_testcase3;
using edu::princeton::cs::algs4::dfs_order_testcase4;
using edu::princeton::cs::algs4::dfs_order_testcase5;

using edu::princeton::cs::algs4::cc_testcase1;
using edu::princeton::cs::algs4::cc_testcase2;
using edu::princeton::cs::algs4::cc_testcase3;

class dfs_testsuite : public testsuite {
    public :
        dfs_testsuite(const string& name = "dfs") :
                             testsuite(name) {
            add_testcase(dfs_testcase1());
            add_testcase(dfs_testcase2());
            add_testcase(dfs_testcase3());
            add_testcase(dfs_testcase4());
            add_testcase(dfs_testcase5());

            add_testcase(dfs_paths_testcase1());
            add_testcase(dfs_paths_testcase2());
            add_testcase(dfs_paths_testcase3());
            add_testcase(dfs_paths_testcase4());
            add_testcase(dfs_paths_testcase5());

            add_testcase(dfs_pre_order_testcase1());
            add_testcase(dfs_pre_order_testcase2());
            add_testcase(dfs_pre_order_testcase3());
            add_testcase(dfs_pre_order_testcase4());
            add_testcase(dfs_pre_order_testcase5());

            add_testcase(dfs_post_order_testcase1());
            add_testcase(dfs_post_order_testcase2());
            add_testcase(dfs_post_order_testcase3());
            add_testcase(dfs_post_order_testcase4());
            add_testcase(dfs_post_order_testcase5());

            add_testcase(dfs_reverse_post_order_testcase1());
            add_testcase(dfs_reverse_post_order_testcase2());
            add_testcase(dfs_reverse_post_order_testcase3());
            add_testcase(dfs_reverse_post_order_testcase4());
            add_testcase(dfs_reverse_post_order_testcase5());

            add_testcase(dfs_order_testcase1());
            add_testcase(dfs_order_testcase2());
            add_testcase(dfs_order_testcase3());
            add_testcase(dfs_order_testcase4());
            add_testcase(dfs_order_testcase5());

            add_testcase(cc_testcase1());
            add_testcase(cc_testcase2());
            add_testcase(cc_testcase3());
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

#endif /* __DFS_TEST_H__ */
