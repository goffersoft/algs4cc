/******************************************************************************
 *  Dependencies: none
 *
 *  Writes data of various types to standard output.
 *
 ******************************************************************************/
#ifndef __CSTDOUT__
#define __CSTDOUT__

#include <iostream>
#include <string>
#include <cstring>
#include <cstdarg>

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::forward;
using std::ostream;
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::strlen;

/**
 ** This class provides methods for printing strings and numbers to standard output.
 ** To use this class, include cstdout.h in your
 ** Java classpath. If you used our autoinstaller, you should be all set.
 ** Otherwise, download
 ** Here is an example program that uses <code>StdOut</code>:
 ** int main(int argc, char** argv) {
 **    int a = 17;
 **    int b = 23;
 **    int sum = a + b;
 **    cstdout::println("Hello, World");
 **    cstdout::printf("%d + %d = %d\n", a, b, sum);
 **    cstdout s;
 **    cstdout.println("Hello, World");
 **    cstdout.printf("%d + %d = %d\n", a, b, sum);
 **     
 ** }
 ** This is a port of the java code provided by Robert Sedgewick
 **
 ** For additional documentation,
 ** see "http://introcs.cs.princeton.edu/15inout
 **     Section 1.5 of
 **     Introduction to Programming in Java: An Interdisciplinary Approach
 **     by Robert Sedgewick and Kevin Wayne.
 **
 ** author Prakash Easwar 
 **/
class cstdout {
   public :
       /**
        ** Terminates the current line by printing the line-separator string.
        **/ 
       static void println(ostream& os = cout) {
           os << endl; 
       }
        
       /**
        ** Prints an object to this output stream and then terminates the line.
        **
        ** param x the object to print
        **/
        template<typename T>
        static void println(T&& x, ostream& os = cout) {
            os << x << endl;
        }

        static void flush(ostream& os = cout) {
            os << std::flush;
        }

       /**
        ** Prints an object to this output stream.
        ** then flushes the output
        ** param x the object to print
        **/
        template<typename T>
        static void print(T&& x, ostream& os = cout) {
            os << x << std::flush;
        }

        template<ostream& os = cout, typename ...Args>
        static void printf(const char* fmt, Args&&... args) {
            os << format(fmt, forward<Args>(args)...) << std::flush;
        }

   private :
       //format into a string buffer
       //algorithm taken from stack overflow
       //http://stackoverflow.com/questions/1056411/
       //how-to-pass-variable-number-of-arguments-to-printf-sprintf
       static string format(const char *fmt, ...) {
           int size = strlen(fmt) * 2 + 50; //initial size 
           std::string str;
           va_list ap;
           while (1) {// Maximum two passes...
               str.resize(size);
               va_start(ap, fmt);
               int n = vsnprintf((char *)str.data(), size, fmt, ap);
               va_end(ap);
               if (n > -1 && n < size) {  // Everything worked
                   str.resize(n);
                   return str;
               }
               if (n > -1)  // Needed size returned
                   size = n + 1;   // For null char
               else
                   size *= 2;      // Guess at a larger size (OS specific)
           }
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

#endif /* __CSTDOUT__ */
