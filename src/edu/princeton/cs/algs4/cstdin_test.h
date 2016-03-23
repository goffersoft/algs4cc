/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the cstdin class.
 *
 ******************************************************************************/
#ifndef __CSTDIN_TEST__
#define __CSTDIN_TEST__

#include <iostream>
#include <sstream>
#include <string>

#include "codeclean.h"

#include "cstdin.h"

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

using edu::princeton::cs::algs4::cstdin;

class cstdin_testsuite : public testsuite {
    public :
        cstdin_testsuite(const string& name = "cstdin") :
                              testsuite(name) {
            add_testcase(testcase1());
            add_testcase(testcase2());
            add_testcase(testcase3());
            add_testcase(testcase4());
            add_testcase(testcase5());
            add_testcase(testcase6());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "has_next - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this),
                                  "has_next - cin !eof test");
                    add_test(bind(&testcase1::test2, this),
                                  "has_next - cin eof test");
                    add_test(bind(&testcase1::test3, this),
                                  "has_next - cin ws eof test");
                    add_test(bind(&testcase1::test4, this),
                                  "has_next - stdin instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test2() {
                    stringstream s("");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next();
                        });
                    return test::ccassert_equals(false, retval);
                }

                bool test3() {
                    stringstream s("\0\a\b\f\t\r\n\v    ");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next();
                        });
                    return test::ccassert_equals(false, retval); 
                }

                bool test4() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.has_next();
                        });
                    return test::ccassert_equals(true, retval); 
                }
        };

        class testcase2 : public testcase {
            public :
                testcase2(const string& name = "has_next_char - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase2::test1, this),
                                  "has_next_char - cin !eof test");
                    add_test(bind(&testcase2::test2, this),
                                  "has_next_char - cin eof test");
                    add_test(bind(&testcase2::test3, this),
                                  "has_next_char - cin ws test");
                    add_test(bind(&testcase2::test4, this),
                                  "has_next_char - stdin instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next_char();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test2() {
                    stringstream s("");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next_char();
                        });
                    return test::ccassert_equals(false, retval);
                }

                bool test3() {
                    stringstream s("    ");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next_char();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test4() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.has_next_char();
                        });
                    return test::ccassert_equals(true, retval); 
                }
        };

        class testcase3 : public testcase {
            public :
                testcase3(const string& name = "is_empty - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase3::test1, this),
                                  "is_empty - cin !eof test");
                    add_test(bind(&testcase3::test2, this),
                                  "is_empty - cin eof test");
                    add_test(bind(&testcase3::test3, this),
                                  "is_empty - cin ws test");
                    add_test(bind(&testcase3::test4, this),
                                  "is_empty - stdin instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::is_empty();
                        });
                    return test::ccassert_equals(false, retval); 
                }

                bool test2() {
                    stringstream s("");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::is_empty();
                        });
                    return test::ccassert_equals(true, retval);
                }

                bool test3() {
                    stringstream s("\0\a\b\f\t\r\n\v    ");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::is_empty();
                        });
                    return test::ccassert_equals(true, retval);
                }

                bool test4() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.is_empty();
                        });
                    return test::ccassert_equals(false, retval); 
                }
        };

        class testcase4 : public testcase {
            public :
                testcase4(const string& name = "read_next - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase4::test1, this),
                                  "read_next - cin !eof test");
                    add_test(bind(&testcase4::test2, this),
                                  "read_next - cin !eof ws test");
                    add_test(bind(&testcase4::test3, this),
                                  "read_next - cin eof test");
                    add_test(bind(&testcase4::test4, this),
                                  "read_next - cin ws test");
                    add_test(bind(&testcase4::test5, this),
                                  "read_next- stdin instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_next();
                        });
                    return test::ccassert_equals(string("Hello"), retval); 
                }

                bool test2() {
                    stringstream s("\t\r\n Hello   ");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_next();
                        });
                    return test::ccassert_equals(string("Hello"), retval); 
                }

                bool test3() {
                    stringstream s("");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_next();
                        });
                    return test::ccassert_equals(string(""), retval);
                }

                bool test4() {
                    stringstream s("\0\a\b\f\t\r\n\v    ");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_next();
                        });
                    return test::ccassert_equals(string(""), retval);
                }

                bool test5() {
                    stringstream s("Hello");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_next();
                        });
                    return test::ccassert_equals(string("Hello"), retval); 
                }
        };

        class testcase5 : public testcase {
            public :
                testcase5(const string& name = "has_next_line - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase5::test1, this),
                                  "has_next_line - cin !eof test");
                    add_test(bind(&testcase5::test2, this),
                                  "has_next_line - cin eof test");
                    add_test(bind(&testcase5::test3, this),
                                  "has_next_line - cin ws test");
                    add_test(bind(&testcase5::test4, this),
                                  "has_next_line - stdin instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next_line();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test2() {
                    stringstream s("");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next_line();
                        });
                    return test::ccassert_equals(false, retval);
                }

                bool test3() {
                    stringstream s("\a\b\f\t\r\n\v    ");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::has_next_line();
                        });
                    return test::ccassert_equals(true, retval);
                }

                bool test4() {
                    stringstream s("Hello");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.has_next_line();
                        });
                    return test::ccassert_equals(true, retval); 
                }
        };

        class testcase6 : public testcase {
            public :
                testcase6(const string& name = "read_line - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase6::test1, this),
                                  "read_line - cin !eof test");
                    add_test(bind(&testcase6::test2, this),
                                  "read_line - cin eof test");
                    add_test(bind(&testcase6::test3, this),
                                  "read_line - cin \\r test");
                    add_test(bind(&testcase6::test4, this),
                                  "read_line - cin \\n test");
                    add_test(bind(&testcase6::test5, this),
                                  "read_line - cin \\r\\n test");
                    add_test(bind(&testcase6::test6, this),
                                  "read_line - stdin instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_line();
                        });
                    return test::ccassert_equals(string("Hello"), retval); 
                }

                bool test2() {
                    stringstream s("");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_line();
                        });
                    return test::ccassert_equals(string(""), retval);
                }

                bool test3() {
                    stringstream s("Hello\r    ");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_line();
                        });
                    return test::ccassert_equals(string("Hello"), retval);
                }

                bool test4() {
                    stringstream s("Hello\n    ");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_line();
                        });
                    return test::ccassert_equals(string("Hello"), retval);
                }

                bool test5() {
                    stringstream s("Hello\r\n    ");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_line();
                        });
                    return test::ccassert_equals(string("Hello"), retval);
                }

                bool test6() {
                    stringstream s("Hello");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_line();
                        });
                    return test::ccassert_equals(string("Hello"), retval); 
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

#endif /* __CSTDIN_TEST__ */
