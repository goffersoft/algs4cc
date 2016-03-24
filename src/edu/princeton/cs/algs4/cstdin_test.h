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
            add_testcase(testcase7());
            add_testcase(testcase8());
            add_testcase(testcase9());
            add_testcase(testcase10());
            add_testcase(testcase11());
            add_testcase(testcase12());
            add_testcase(testcase13());
            add_testcase(testcase14());
            add_testcase(testcase15());
            add_testcase(testcase16());
            add_testcase(testcase17());
            add_testcase(testcase18());
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

        class testcase7 : public testcase {
            public :
                testcase7(const string& name = "read_char - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase7::test1, this),
                                  "read_char - read !eof test");
                    add_test(bind(&testcase7::test2, this),
                                  "read_char - instance test");
                }

                bool test1() {
                    stringstream s("Hello");
                    char retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_char();
                        });
                    return test::ccassert_equals('H', retval); 
                }

                bool test2() {
                    stringstream s("Hello");
                    char retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_char();
                        });
                    return test::ccassert_equals('H', retval); 
                }
        };

        class testcase8 : public testcase {
            public :
                testcase8(const string& name = "read_all - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase8::test1, this),
                                  "read_all - read !eof test");
                    add_test(bind(&testcase8::test2, this),
                                  "read_all - instance test");
                }

                bool test1() {
                    stringstream s("Hello World!\r\t\n");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_all();
                        });
                    return test::ccassert_equals(string("Hello World!\r\t\n"), retval); 
                }

                bool test2() {
                    stringstream s("Hello World!\r\t\n");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_all();
                        });
                    return test::ccassert_equals(string("Hello World!\r\t\n"), retval); 
                }
        };

        class testcase9 : public testcase {
            public :
                testcase9(const string& name = "read_string - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase9::test1, this),
                                  "read_string - read !eof test");
                    add_test(bind(&testcase9::test2, this),
                                  "read_string - instance test");
                }

                bool test1() {
                    stringstream s("Hello World!\r\t\n");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin::read_string();
                            retval = cstdin::read_string();
                        });
                    return test::ccassert_equals(string("World!"), retval); 
                }

                bool test2() {
                    stringstream s("Hello World!\r\t\n");
                    string retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_string();
                        });
                    return test::ccassert_equals(string("Hello"), retval); 
                }
        };

        class testcase10 : public testcase {
            public :
                testcase10(const string& name = "read_bool - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase10::test1, this),
                                  "read_bool - read !eof uppercase true test");
                    add_test(bind(&testcase10::test2, this),
                                  "read_bool - read !eof lowercase true test");
                    add_test(bind(&testcase10::test3, this),
                                  "read_bool - read !eof mixedcase true test");
                    add_test(bind(&testcase10::test4, this),
                                  "read_bool - read !eof uppercase false test");
                    add_test(bind(&testcase10::test5, this),
                                  "read_bool - read !eof lowercase false test");
                    add_test(bind(&testcase10::test6, this),
                                  "read_bool - read !eof mixedcase false test");
                    add_test(bind(&testcase10::test7, this),
                                  "read_bool - read !eof 1=true test");
                    add_test(bind(&testcase10::test8, this),
                                  "read_bool - read !eof 0=false test");
                    add_test(bind(&testcase10::test9, this),
                                  "read_bool - read bad value throw exp test");
                    add_test(bind(&testcase10::test10, this),
                                  "read_bool - instance test");
                }

                bool test1() {
                    stringstream s("TRUE\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test2() {
                    stringstream s("true\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test3() {
                    stringstream s("TRue\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test4() {
                    stringstream s("FALSE\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(false, retval); 
                }

                bool test5() {
                    stringstream s("false\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(false, retval); 
                }

                bool test6() {
                    stringstream s("FAlse\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(false, retval); 
                }

                bool test7() {
                    stringstream s("1\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(true, retval); 
                }

                bool test8() {
                    stringstream s("0\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_bool();
                        });
                    return test::ccassert_equals(false, retval); 
                }

                bool test9() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_bool();
                                      });
                              });
                }

                bool test10() {
                    stringstream s("true\r\t\n");
                    bool retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_bool();
                        });
                    return test::ccassert_equals(true, retval); 
                }
        };

        class testcase11 : public testcase {
            public :
                testcase11(const string& name = "read_uint8 - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase11::test1, this),
                                  "read_uint8 - read good uint8 test");
                    add_test(bind(&testcase11::test2, this),
                                  "read_uint8 - read uint8 max out of range");
                    add_test(bind(&testcase11::test3, this),
                                  "read_uint8 - read bad uint8 throw exp test");
                    add_test(bind(&testcase11::test4, this),
                                  "read_uint8 - instance test");
                }

                bool test1() {
                    stringstream s("128 \r\t\n");
                    uint8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint8();
                        });
                    return test::ccassert_equals((uint8_t)128, retval); 
                }

                bool test2() {
                    stringstream s;
                    s << UCHAR_MAX + 1 << "\r\t\n";
                    uint8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint8();
                        });
                    return test::ccassert_equals((uint8_t)UCHAR_MAX, retval); 
                }

                bool test3() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("test\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_uint8();
                                      });
                              });
                }

                bool test4() {
                    stringstream s("128 \r\t\n");
                    uint8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_uint8();
                        });
                    return test::ccassert_equals((uint8_t)128, retval); 
                }
        };

        class testcase12 : public testcase {
            public :
                testcase12(const string& name = "read_int8 - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase12::test1, this),
                                  "read_int8 - read good int8>0 test");
                    add_test(bind(&testcase12::test2, this),
                                  "read_int8 - read good int8<0 test");
                    add_test(bind(&testcase12::test3, this),
                                  "read_int8 - read int8 min out of range");
                    add_test(bind(&testcase12::test4, this),
                                  "read_int8 - read int8 max out of range");
                    add_test(bind(&testcase12::test5, this),
                                  "read_int8 - read bad int8 throw exp test");
                    add_test(bind(&testcase12::test6, this),
                                  "read_int8 - instance test");
                }

                bool test1() {
                    stringstream s("96\r\t\n");
                    int8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int8();
                        });
                    return test::ccassert_equals((int8_t)96, retval); 
                }

                bool test2() {
                    stringstream s("-96\r\t\n");
                    int8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int8();
                        });
                    return test::ccassert_equals((int8_t)-96, retval); 
                }

                bool test3() {
                    stringstream s;
                    s << (int64_t)CHAR_MIN - 1 << "\r\t\n";
                    int8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int8();
                        });
                    return test::ccassert_equals((int8_t)CHAR_MIN, retval); 
                }

                bool test4() {
                    stringstream s;
                    s << (uint64_t)CHAR_MAX + 1 << "\r\t\n";
                    int8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int8();
                        });
                    return test::ccassert_equals((int8_t)CHAR_MAX, retval); 
                }

                bool test5() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_int8();
                                      });
                              });
                }

                bool test6() {
                    stringstream s("0xd\r\t\n");
                    int8_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_int8();
                        });
                    return test::ccassert_equals((int8_t)0xd, retval); 
                }
        };

        class testcase13 : public testcase {
            public :
                testcase13(const string& name = "read_uint16 - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase13::test1, this),
                                  "read_uint16 - read good uint16 test");
                    add_test(bind(&testcase13::test2, this),
                                  "read_uint16 - read uint16 max out of range");
                    add_test(bind(&testcase13::test3, this),
                                  "read_uint16 - read bad uint16 throw exp test");
                    add_test(bind(&testcase13::test4, this),
                                  "read_uint16 - instance test");
                }

                bool test1() {
                    stringstream s("50000 \r\t\n");
                    uint16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint16();
                        });
                    return test::ccassert_equals((uint16_t)50000, retval); 
                }

                bool test2() {
                    stringstream s;
                    s << USHRT_MAX + 1 << "\r\t\n";
                    uint16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint16();
                        });
                    return test::ccassert_equals((uint16_t)USHRT_MAX, retval); 
                }

                bool test3() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_uint16();
                                      });
                              });
                }

                bool test4() {
                    stringstream s("50000 \r\t\n");
                    uint16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_uint16();
                        });
                    return test::ccassert_equals((uint16_t)50000, retval); 
                }
        };

        class testcase14 : public testcase {
            public :
                testcase14(const string& name = "read_int16 - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase14::test1, this),
                                  "read_int16 - read good int16>0 test");
                    add_test(bind(&testcase14::test2, this),
                                  "read_int16 - read good int16<0 test");
                    add_test(bind(&testcase14::test3, this),
                                  "read_int16 - read int16 min out of range");
                    add_test(bind(&testcase14::test4, this),
                                  "read_int16 - read int16 max out of range");
                    add_test(bind(&testcase14::test5, this),
                                  "read_int16 - read bad int16 throw exp test");
                    add_test(bind(&testcase14::test6, this),
                                  "read_int16 - instance test");
                }

                bool test1() {
                    stringstream s("25000 \r\t\n");
                    int16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int16();
                        });
                    return test::ccassert_equals((int16_t)25000, retval); 
                }

                bool test2() {
                    stringstream s("-25000 \r\t\n");
                    int16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int16();
                        });
                    return test::ccassert_equals((int16_t)-25000, retval); 
                }

                bool test3() {
                    stringstream s;
                    s << (int64_t)SHRT_MIN - 1 << "\r\t\n";
                    int16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int16();
                        });
                    return test::ccassert_equals((int16_t)SHRT_MIN, retval); 
                }

                bool test4() {
                    stringstream s;
                    s << (uint64_t)SHRT_MAX + 1 << "\r\t\n";
                    int16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int16();
                        });
                    return test::ccassert_equals((int16_t)SHRT_MAX, retval); 
                }

                bool test5() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_int16();
                                      });
                              });
                }

                bool test6() {
                    stringstream s("0xfff\r\t\n");
                    int16_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_int16();
                        });
                    return test::ccassert_equals((int16_t)0xfff, retval); 
                }
        };

        class testcase15 : public testcase {
            public :
                testcase15(const string& name = "read_uint32 - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase15::test1, this),
                                  "read_uint32 - read good uint32 test");
                    add_test(bind(&testcase15::test2, this),
                                  "read_uint32 - read uint32 max out of range");
                    add_test(bind(&testcase15::test3, this),
                                  "read_uint32 - read bad uint32 throw exp test");
                    add_test(bind(&testcase15::test4, this),
                                  "read_uint32 - instance test");
                }

                bool test1() {
                    stringstream s("70000 \r\t\n");
                    uint32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint32();
                        });
                    return test::ccassert_equals((uint32_t)70000, retval); 
                }

                bool test2() {
                    stringstream s;
                    s << (uint64_t)UINT_MAX + 1 << "\r\t\n";
                    uint32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint32();
                        });
                    return test::ccassert_equals((uint32_t)UINT_MAX, retval); 
                }

                bool test3() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_uint32();
                                      });
                              });
                }

                bool test4() {
                    stringstream s("70000 \r\t\n");
                    uint32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_uint32();
                        });
                    return test::ccassert_equals((uint32_t)70000, retval); 
                }
        };

        class testcase16 : public testcase {
            public :
                testcase16(const string& name = "read_int32 - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase16::test1, this),
                                  "read_int32 - read good int32>0 test");
                    add_test(bind(&testcase16::test2, this),
                                  "read_int32 - read good int32<0 test");
                    add_test(bind(&testcase16::test3, this),
                                  "read_int32 - read int32 min out of range");
                    add_test(bind(&testcase16::test4, this),
                                  "read_int32 - read int32 max out of range");
                    add_test(bind(&testcase16::test5, this),
                                  "read_int32 - read bad int32 throw exp test");
                    add_test(bind(&testcase16::test6, this),
                                  "read_int32 - instance test");
                }

                bool test1() {
                    stringstream s("70000 \r\t\n");
                    int32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int32();
                        });
                    return test::ccassert_equals((int32_t)70000, retval); 
                }

                bool test2() {
                    stringstream s("-70000 \r\t\n");
                    int32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int32();
                        });
                    return test::ccassert_equals((int32_t)-70000, retval); 
                }

                bool test3() {
                    stringstream s;
                    s << (int64_t)INT_MIN - 1 << "\r\t\n";
                    int32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int32();
                        });
                    return test::ccassert_equals((int32_t)INT_MIN, retval); 
                }

                bool test4() {
                    stringstream s;
                    s << (uint64_t)INT_MAX + 1 << "\r\t\n";
                    int32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int32();
                        });
                    return test::ccassert_equals((int32_t)INT_MAX, retval); 
                }

                bool test5() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_int32();
                                      });
                              });
                }

                bool test6() {
                    stringstream s("0xffffff\r\t\n");
                    int32_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_int32();
                        });
                    return test::ccassert_equals((int32_t)0xffffff, retval); 
                }
        };


        class testcase17 : public testcase {
            public :
                testcase17(const string& name = "read_uint64 - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase17::test1, this),
                                  "read_uint64 - read good uint64 test");
                    add_test(bind(&testcase17::test2, this),
                                  "read_uint64 - read uint64 max out of range");
                    add_test(bind(&testcase17::test3, this),
                                  "read_uint64 - read bad uint64 throw exp test");
                    add_test(bind(&testcase17::test4, this),
                                  "read_uint64 - instance test");
                }

                bool test1() {
                    stringstream s("0xffffffffff \r\t\n");
                    uint64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint64();
                        });
                    return test::ccassert_equals((uint64_t)0xffffffffff, retval); 
                }

                bool test2() {
                    stringstream s("0xffffffffffffffffff\r\t\n");
                    uint64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_uint64();
                        });
                    return test::ccassert_equals((uint64_t)ULONG_MAX, retval); 
                }

                bool test3() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_uint64();
                                      });
                              });
                }

                bool test4() {
                    stringstream s("0xffffffffff\r\t\n");
                    uint64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_uint64();
                        });
                    return test::ccassert_equals((uint64_t)0xffffffffff, retval); 
                }
        };

        class testcase18 : public testcase {
            public :
                testcase18(const string& name = "read_int64 - all tests") :
                                   testcase(name) {
                    add_test(bind(&testcase18::test1, this),
                                  "read_int64 - read good int64>0 test");
                    add_test(bind(&testcase18::test2, this),
                                  "read_int64 - read good int64<0 test");
                    add_test(bind(&testcase18::test3, this),
                                  "read_int64 - read int64 max out of range");
                    add_test(bind(&testcase18::test4, this),
                                  "read_int64 - read bad int64 throw exp test");
                    add_test(bind(&testcase18::test5, this),
                                  "read_int64 - instance test");
                }

                bool test1() {
                    stringstream s("0x7fffffffff \r\t\n");
                    int64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int64();
                        });
                    return test::ccassert_equals((int64_t)0x7fffffffff, retval); 
                }

                bool test2() {
                    stringstream s("0xffffffffff \r\t\n");
                    int64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int64();
                        });
                    return test::ccassert_equals((int64_t)0xffffffffff, retval); 
                }

                bool test3() {
                    stringstream s("0xffffffffffffffffff\r\t\n");
                    int64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            retval = cstdin::read_int64();
                        });
                    return test::ccassert_equals((int64_t)LONG_MAX, retval); 
                }

                bool test4() {
                    std::ios_base::failure e("some exp");
                    return test::ccassert_exception(
                              e,
                              []() {
				  bool retval;
                                  stringstream s("tes\r\t\n");
                                  test::mock_stdin(
                                      s,
                                      [&retval]() -> void {
                                          retval = cstdin::read_int64();
                                      });
                              });
                }

                bool test5() {
                    stringstream s("0xffffffffff\r\t\n");
                    int64_t retval;
                    test::mock_stdin(
                        s,
                        [&retval]() -> void {
                            cstdin sin;
                            retval = sin.read_int64();
                        });
                    return test::ccassert_equals((int64_t)0xffffffffff, retval); 
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
