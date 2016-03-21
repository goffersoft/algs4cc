#ifndef __CSTDOUT_TEST__
#define __CSTDOUT_TEST__

#include <iostream>
#include <string>

#include "codeclean.h"

#include "cstdout.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::shared_ptr;
using std::function;
using std::bind;
using std::cerr;
using std::string;
using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

class cstdout_testsuite : public testsuite {
    public :
        cstdout_testsuite(const string& name = "cstdout") :
                              testsuite(name) { 
            add_testcase(testcase1());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "println - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this), "lvalue test");
                    add_test(bind(&testcase1::test2, this), "rvalue test");
                }

                bool test1() {
                    string output = test::capture_stdout(
                         []() -> void { cstdout::println(27); });
                    test::ccassert_equals(string("27\n"), output); 
                    return true;
                }

                bool test2() {
                    string output = test::capture_stdout(
                         []() -> void { int i = 27; cstdout::println(i); });
                    test::ccassert_equals(string("27\n"), output); 
                    return true;
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

#endif /* __CSTDOUT_TEST__ */
