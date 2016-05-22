/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the union_find class.
 *
 ******************************************************************************/
#ifndef __UNION_FIND_TEST_H__
#define __UNION_FIND_TEST_H__

#include <iostream>
#include <sstream>
#include <string>

#include "codeclean.h"
#include "union_find.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::bind;
using std::stringstream;
using std::string;

using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

using edu::princeton::cs::algs4::union_find;

class union_find_testsuite : public testsuite {
    public :
        union_find_testsuite(const string& name = "union_find") :
                              testsuite(name) { 
            add_testcase(testcase1());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "union_find- all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this),
                             "constructor test");

                    add_test(bind(&testcase1::test2, this),
                             "set_union method(p*,q) - exception test");
                    add_test(bind(&testcase1::test3, this),
                             "set_union method(p,q*) - exception test");
                    add_test(bind(&testcase1::test4, this),
                             "set_union method(p*,q*) - exception test");
                    add_test(bind(&testcase1::test5, this),
                             "set_union method(p,q) - test");

                    add_test(bind(&testcase1::test10, this),
                             "is_connected method(p*,q) - exception test");
                    add_test(bind(&testcase1::test11, this),
                             "is_connected method(p,q*) - exception test");
                    add_test(bind(&testcase1::test12, this),
                             "is_connected method(p*,q*) - exception test");
                    add_test(bind(&testcase1::test13, this),
                             "is_connected method(p,q) - test");

                    add_test(bind(&testcase1::test16, this),
                             "find method(p) - exception test");
                    add_test(bind(&testcase1::test17, this),
                             "find method(p) - test");
                }

                bool test1() {
                    union_find uf = union_find(10);

                    return test::ccassert(uf.get_num_sites() == 10 &&
                                          uf.get_count() == 10 &&
                                          uf.find(0) == 0 &&
                                          uf.find(1) == 1 &&
                                          uf.find(2) == 2 &&
                                          uf.find(3) == 3 &&
                                          uf.find(4) == 4 &&
                                          uf.find(5) == 5 &&
                                          uf.find(6) == 6 &&
                                          uf.find(7) == 7 &&
                                          uf.find(8) == 8 &&
                                          uf.find(9) == 9);
                }

                bool test2() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.set_union(10, 9);
                              }
                           );
                }

                bool test3() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.set_union(0, 20);
                              }
                           );
                }

                bool test4() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.set_union(10, 20);
                              }
                           );
                }

                bool test5() {
                    union_find uf = union_find(10);
                    uf.set_union(2,3);
                    return test::ccassert(
                                    uf.is_connected(1,2) == false &&
                                    uf.is_connected(2,3) == true &&
                                    uf.is_connected(3,4) == false &&
                                    uf.get_count() == 9);
                }

                bool test10() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.is_connected(10, 9);
                              }
                           );
                }

                bool test11() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.is_connected(0, 20);
                              }
                           );
                }

                bool test12() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.is_connected(10, 20);
                              }
                           );
                }

                bool test13() {
                    union_find uf = union_find(10);
                    uf.set_union(2,3);
                    uf.set_union(5,6);
                    uf.set_union(8,9);
                    return test::ccassert(
                                    uf.is_connected(1,2) == false &&
                                    uf.is_connected(2,3) == true &&
                                    uf.is_connected(3,4) == false &&
                                    uf.is_connected(4,5) == false &&
                                    uf.is_connected(5,6) == true &&
                                    uf.is_connected(6,7) == false &&
                                    uf.is_connected(7,8) == false &&
                                    uf.is_connected(8,9) == true &&
                                    uf.get_count() == 7);
                }

                bool test16() {
                    union_find uf = union_find(10);

                    invalid_argument e("some exp");

                    return test::ccassert_exception(
                              e,
                              [&uf]() {
                                  uf.find(10);
                              }
                           );
                }

                bool test17() {
                    union_find uf = union_find(10);
                    uf.set_union(2,3);
                    uf.set_union(5,6);
                    uf.set_union(8,9);
                    uf.set_union(2,9);
                    uf.set_union(2,5);

                    return test::ccassert(
                                    uf.find(1) != uf.find(2) &&
                                    uf.find(3) != uf.find(4) &&
                                    uf.find(4) != uf.find(5) &&
                                    uf.find(2) == uf.find(3) &&
                                    uf.find(2) == uf.find(5) &&
                                    uf.find(2) == uf.find(6) &&
                                    uf.find(2) == uf.find(8) &&
                                    uf.find(2) == uf.find(9));
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

#endif /* __UNION_FIND_TEST_H__ */
