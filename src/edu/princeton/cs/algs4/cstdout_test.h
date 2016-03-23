/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the cstdout class.
 *
 ******************************************************************************/
#ifndef __CSTDOUT_TEST__
#define __CSTDOUT_TEST__

#include <iostream>
#include <sstream>
#include <string>

#include "codeclean.h"

#include "cstdout.h"

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

class cstdout_testsuite : public testsuite {
    public :
        cstdout_testsuite(const string& name = "cstdout") :
                              testsuite(name) { 
            add_testcase(testcase1());
            add_testcase(testcase2());
            add_testcase(testcase3());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "println - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this), "rvalue test");
                    add_test(bind(&testcase1::test2, this), "lvalue test");
                    add_test(test3("ref test"));
                    add_test(bind(&testcase1::test4, this), "const char *");
                    add_test(bind(&testcase1::test5, this), "stdout instance test");
                    add_test(bind(&testcase1::test6, this), "pointer value test");
                    add_test(bind(&testcase1::test7, this), "const pointer value test");
                }

                bool test1() {
                    string output = test::capture_stdout(
                         []() -> void { cstdout::println(27); });
                    return test::ccassert_equals(string("27\n"), output); 
                }

                bool test2() {
                    string output = test::capture_stdout(
                         []() -> void { int i = 27; cstdout::println(i); });
                    return test::ccassert_equals(string("27\n"), output); 
                }

                class test3 : public test {
                     public :
                         test3(): test(){}
                         test3(const string& name): test(name){}
                         test3& clone() const override {
                             return *new test3(*this);
                         }

                         bool run() {
                             string output = test::capture_stdout(
                                  []() -> void {
                                       bool i = true;
                                       bool& j = i;
                                       cstdout::println(j);
                                  });
                             return test::ccassert_equals(string("1\n"), output); 
                         }
                };

                bool test4() {
                    string output = test::capture_stdout(
                        []() -> void {
                            bool i = true;
                            const bool& j = i;
                            cstdout::println(j);
                        });
                    return test::ccassert_equals(string("1\n"), output); 
                }

                bool test5() {
                    string output = test::capture_stdout(
                        []() -> void {
                            cstdout out;
                            const char* s = "Hello World";
                            out.println(s);
                        });
                    return test::ccassert_equals(string("Hello World\n"), output); 
                }

                bool test6() {
                    bool a = true;
                    bool* b = &a;
                    string output = test::capture_stdout(
                         [b]() -> void { cstdout::println(b); });
                    stringstream s;
                    s << b << endl;
                    return test::ccassert_equals(s.str(), output); 
                }

                bool test7() {
                    bool a = true;
                    const bool* b = &a;
                    string output = test::capture_stdout(
                         [b]() -> void { cstdout::println(b); });
                    stringstream s;
                    s << b << endl;
                    return test::ccassert_equals(s.str(), output); 
                }
        };
        class testcase2 : public testcase {
            public :
                testcase2(const string& name = "printf - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase2::test1, this), "multiple args test");
                    add_test(bind(&testcase2::test2, this), "instance test");
                }
                bool test1() {
                    string output = test::capture_stdout(
                        []() -> void {
                            const char* s = "Hello World";
                            uint32_t a = 27;
                            uint32_t b = 28;
                            uint32_t sum = a + b;
                            cstdout::printf("%s, sum of (%d+%d)=%d\n", s, a, b, sum);
                        });
                    return test::ccassert_equals(
                      string("Hello World, sum of (27+28)=55\n"), output); 
                }

                bool test2() {
                    string output = test::capture_stdout(
                        []() -> void {
                            cstdout out;
                            const char* s = "Hello World";
                            uint32_t a = 27;
                            uint32_t b = 28;
                            uint32_t sum = a + b;
                            out.printf("%s, sum of (%d+%d)=%d\n", s, a, b, sum);
                        });
                    return test::ccassert_equals(
                      string("Hello World, sum of (27+28)=55\n"), output); 
                }
        };
        class testcase3 : public testcase {
            public :
                testcase3(const string& name = "print - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase3::test1, this), "rvalue test");
                    add_test(bind(&testcase3::test2, this), "lvalue test");
                    add_test(bind(&testcase3::test3, this), "ref test");
                    add_test(bind(&testcase3::test4, this), "const ref test");
                    add_test(bind(&testcase3::test5, this), "const char *");
                }
                bool test1() {
                    string output = test::capture_stdout(
                         []() -> void { cstdout::print(27); });
                    return test::ccassert_equals(string("27"), output); 
                }
                bool test2() {
                    string output = test::capture_stdout(
                         []() -> void { int i = 27; cstdout::print(i); });
                    return test::ccassert_equals(string("27"), output); 
                }
                bool test3() {
                    string output = test::capture_stdout(
                         []() -> void { int j=27; int& i=j; cstdout::print(i); });
                    return test::ccassert_equals(string("27"), output); 
                }
                bool test4() {
                    string output = test::capture_stdout(
                         []() -> void { int j=27; const int& i=j; cstdout::print(i); });
                    return test::ccassert_equals(string("27"), output); 
                }
                bool test5() {
                    string output = test::capture_stdout(
                         []() -> void { const char* i="Hello"; cstdout::print(i); });
                    return test::ccassert_equals(string("Hello"), output); 
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
