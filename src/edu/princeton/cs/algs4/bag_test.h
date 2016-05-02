/******************************************************************************
 *  Dependencies: none
 *
 *  test code for the bag class.
 *
 ******************************************************************************/
#ifndef __BAG_TEST__
#define __BAG_TEST__

#include <sstream>
#include <string>

#include "codeclean.h"
#include "bag.h"

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

class bag_testsuite : public testsuite {
    public :
        bag_testsuite(const string& name = "bag") :
                     testsuite(name) {
            add_testcase(testcase1());
            add_testcase(testcase2());
        }

    private :
        class testcase1 : public testcase {
            public :
                testcase1(const string& name = "bag - store values - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase1::test1, this),
                             "bag - iterate(begin/end) over bag of values test");
                    add_test(bind(&testcase1::test2, this),
                             "bag - iterate(const - begin/end) over bag of values test");
                    add_test(bind(&testcase1::test3, this),
                             "bag - iterate(const - cbegin/end) over bag of values test");
                    add_test(bind(&testcase1::test4, this),
                             "bag - bag to string conversion test");
                }

                bool test1() {
                    string s[] = {"value1"};
                    bag<string>::bag_value_type b;
                    for(auto v : s) {
                       b.push_back(v); 
                    }
                    bool retval = false;
                    for(bag<string>::value_iterator it = b.begin();
                        it != b.end(); ++it) {
                      string& v = *it;
                      retval = test::ccassert(static_cast<string *>(&v) != 
                                              static_cast<string *>(&(s[0])));
                    }
                    return retval;
                }

                bool test2() {
                    string s[] = {"value1"};
                    bag<string>::bag_value_type b;
                    for(auto v : s) {
                       b.push_back(v); 
                    }
                    const bag<string>::bag_value_type& b_const = b;
                    bool retval = false;
                    for(bag<string>::const_value_iterator it = b_const.begin();
                        it != b_const.end(); ++it) {
                      const string& v = *it;
                      retval = test::ccassert(static_cast<const string *>(&v) != 
                                              static_cast<const string *>(&(s[0])));
                    }
                    return retval;
                }

                bool test3() {
                    string s[] = {"value1"};
                    bag<string>::bag_value_type b;
                    for(auto v : s) {
                       b.push_back(v); 
                    }
                    bool retval = false;
                    for(bag<string>::const_value_iterator it = b.cbegin();
                        it != b.cend(); ++it) {
                      const string& v = *it;
                      retval = test::ccassert(static_cast<const string *>(&v) != 
                                              static_cast<const string *>(&(s[0])));
                    }
                    return retval;
                }

                bool test4() {
                    string s[] = {"value1", "value2", "value3" };
                    bag<string>::bag_value_type b;
                    stringstream ss;

                    for(auto v : s) {
                       b.push_back(v); 
                       ss << v << " ";
                    }
                    ss << endl;
                    
                    return test::ccassert(string(b) == ss.str());
                }
        };

        class testcase2 : public testcase {
            public :
                testcase2(const string& name = "bag - store references - all tests") : 
                                   testcase(name) {
                    add_test(bind(&testcase2::test1, this),
                             "bag - iterate(begin/end) over bag of references test");
                    add_test(bind(&testcase2::test2, this),
                             "bag - iterate(const - begin/end) over bag of references test");
                    add_test(bind(&testcase2::test3, this),
                             "bag - iterate(const - cbegin/end) over bag of references test");
                    add_test(bind(&testcase2::test4, this),
                             "bag - bag to string conversion test");
                }

                bool test1() {
                    string s[] = {"value1"};
                    bag<string>::bag_reference_type b;
                    for(auto& v : s) {
                       b.push_back(v); 
                    }
                    bool retval = false;
                    for(bag<string>::reference_iterator it = b.begin();
                        it != b.end(); ++it) {
                      string& v = *it;
                      retval = test::ccassert(static_cast<string *>(&v) == 
                                              static_cast<string *>(&(s[0])));
                    }
                    return retval;
                }

                bool test2() {
                    string s[] = {"value1"};
                    bag<string>::bag_reference_type b;
                    for(auto& v : s) {
                       b.push_back(v); 
                    }
                    const bag<string>::bag_reference_type& b_const = b;
                    bool retval = false;
                    for(bag<string>::const_reference_iterator it = b_const.begin();
                        it != b_const.end(); ++it) {
                      const string& v = *it;
                      retval = test::ccassert(static_cast<const string *>(&v) == 
                                              static_cast<const string *>(&(s[0])));
                    }
                    return retval;
                }

                bool test3() {
                    string s[] = {"value1"};
                    bag<string>::bag_reference_type b;
                    for(auto& v : s) {
                       b.push_back(v); 
                    }
                    bool retval = false;
                    for(bag<string>::const_reference_iterator it = b.cbegin();
                        it != b.cend(); ++it) {
                      const string& v = *it;
                      retval = test::ccassert(static_cast<const string *>(&v) == 
                                              static_cast<const string *>(&(s[0])));
                    }
                    return retval;
                }

                bool test4() {
                    string s[] = {"value1", "value2", "value3" };
                    bag<string>::bag_reference_type b;
                    stringstream ss;

                    for(auto& v : s) {
                       b.push_back(v); 
                       ss << v << " ";
                    }
                    ss << endl;
                    return test::ccassert(string(b) == ss.str());
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

#endif /* __BAG_TEST__ */
