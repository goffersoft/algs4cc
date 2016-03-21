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
#include "cstdout.h"
#include "cstdin.h"
#include "cstdout_test.h"
#include "codeclean.h"

using com::goffersoft::codeclean::codeclean;
using com::goffersoft::codeclean::testsuite;
using edu::princeton::cs::algs4::cstdout_testsuite;
using edu::princeton::cs::algs4::cstdout;

int test_main(int argc, const char **argv) {
    codeclean tests;
    tests.add_testsuite(cstdout_testsuite());
    tests.run();

    bool a = true;
    bool& b = a;
    const bool& c = a;
    bool* d = &a;
    const bool* e = &a;

    cstdout::println(27);
    cstdout::println(a);
    cstdout::println(b);
    cstdout::println(c);
    cstdout::println(d);
    cstdout::println(e);
    cstdout::println(*d);
    cstdout::println(*e);

    cstdout::printf("%d %s\n", 5, "hello");

    int x = 17;
    int y = 23;
    int sum = x + y;
    cstdout::println("Hello, World");
    cstdout::printf("%d + %d = %d\n", x, y, sum);
    cstdout s;  
    s.println("Hello, World");
    s.printf("%d + %d = %d\n", x, y, sum);

    return 0;
}
