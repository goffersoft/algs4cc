/** 
 **
 ** This is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This software is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this software. If not, see <http://www.gnu.org/licenses/>.
 **
 **/
#include "codeclean.h"
#include "cstdout_test.h"
#include "cstdin_test.h"
#include "bag_test.h"
#include "edge_test.h"
#include "graph_test.h"
#include "dfs_test.h"
#include "union_find_test.h"

using com::goffersoft::codeclean::codeclean;
using com::goffersoft::codeclean::testsuite;
using edu::princeton::cs::algs4::cstdout_testsuite;
using edu::princeton::cs::algs4::cstdin_testsuite;
using edu::princeton::cs::algs4::bag_testsuite;
using edu::princeton::cs::algs4::edge_testsuite;
using edu::princeton::cs::algs4::graph_testsuite;
using edu::princeton::cs::algs4::dfs_testsuite;
using edu::princeton::cs::algs4::union_find_testsuite;

int test_main(int argc, const char **argv) {
    codeclean tests;
    tests.add_testsuite(cstdout_testsuite());
    tests.add_testsuite(cstdin_testsuite());
    tests.add_testsuite(bag_testsuite());
    tests.add_testsuite(edge_testsuite());
    tests.add_testsuite(graph_testsuite());
    tests.add_testsuite(dfs_testsuite());
    tests.add_testsuite(union_find_testsuite());
    tests.run();
    tests.print_report();

    return 0;
}
