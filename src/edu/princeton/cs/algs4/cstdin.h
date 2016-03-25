/******************************************************************************
 *  Dependencies: none
 *
 *  Reads data of various types from standard input.
 *
 ******************************************************************************/
#ifndef __CSTDIN__
#define __CSTDIN__

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <math.h>
#include <climits>

#include "utils.h"

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::vector;
using std::forward;
using std::istream;
using std::cin;
using std::endl;
using std::flush;
using std::string;
using std::isspace;
using std::equal;
using std::begin;
using std::ios_base;
using std::numeric_limits;

using com::goffersoft::core::utils;

/**
 ** The cstdin class provides static methods for reading strings
 ** and numbers from standard input.
 ** These functions fall into one of four categories:
 **   1) - those for reading individual tokens from standard input,
 **        one at a time, and converting each to a number,
 **        string, or boolean
 **   2) - those for reading characters from standard input,
 **        one at a time
 **   3) - those for reading lines from standard input,
 **        one at a time
 **   4) - those for reading a sequence of values of the
 **        same type from standard input,
 **        and returning the values in an array
 **
 ** Generally, it is best not to mix functions from the different
 ** categories in the same program. 
 ** You can use the following methods to read numbers,
 ** strings, and booleans from standard input:
 **    1) - read_uint8()
 **    2) - read_uint16()
 **    3) - read_uint32()
 **    4) - read_uint64()
 **    5) - read_int8()
 **    6) - read_int16()
 **    7) - read_int32()
 **    8) - read_int64()
 **    9) - read_bool()
 **   10) - read_string()
 **   11) - read_float()
 **   12) - read_double()
 **   13) - read_long_double()
 ** Each method skips over any input that is whitespace.
 ** Then, it reads the next token and attempts to convert
 ** it into a value of the specified type. If it succeeds,
 ** it returns that value.
 ** for function 1 thru 9  an exception is thrown on error.
 **   ios_base::failure::failure on error
 ** for 11 thru 13 nan is returned.
 **     
 ** Whitespace includes spaces, tabs, and newlines;
 ** A token is a maximal sequence of non-whitespace characters.
 **
 ** Reading characters from standard input, one at a time.
 ** You can use the following two methods to read characters
 ** from standard input:
 **    1) - has_next_char()
 **    2) - read_char()
 ** The first method returns true if standard input has more
 ** input (including whitespace). The second method reads and
 ** returns the next character of input on standard 
 ** input (possibly a whitespace character).
 ** As an example, the following code fragment reads characters
 ** from standard input,
 ** one character at a time, and prints it to standard output.
 ** while (!stdin::has_next_char()) {
 **     char c = stdin::read_char();
 **     stdout::print(c);
 ** }
 **
 ** Reading lines from standard input, one at a time.
 ** You can use the following two methods to read
 ** lines from standard input:
 **    1) - has_next_line()}
 **    2) - read_line()}
 ** The first method returns true if standard input
 ** has more input (including whitespace).
 ** The second method reads and returns the remaining
 ** portion of the next line of input on standard
 ** input (possibly whitespace),
 ** discarding the trailing line separator.
 ** A line separator is defined to be one of
 ** the following strings:
 ** {\n - Linux, \r - old Macintosh,
 ** \r\n - Windows,
 ** As an example, the following code fragment reads text
 ** from standard input, one line at a time, and prints it
 ** to standard output.
 ** while (!stdin::has_next_line()) {
 **     string line = stdin::read_line();
 **     stdout::println(line);
 ** }
 **
 ** Reading a sequence of values of the same type from
 ** standard input.
 ** You can use the following methods
 ** to read a sequence numbers, strings, or booleans
 ** (all of the same type) from standard input:
 **    1) - read_all_uint8s()
 **    2) - read_all_uint16s()
 **    3) - read_all_uint32s()
 **    4) - read_all_uint64s()
 **    5) - read_all_int8s()
 **    6) - read_all_int16s()
 **    7) - read_all_int32s()
 **    8) - read_all_int64s()
 **    9) - read_all_bools()
 **   10) - read_all_strings()
 **   11) - read_all_floats()
 **   12) - read_all_doubles()
 **   13) - read_all_long_doubles()
 **   13) - read_all_lines()
 **   13) - read_all()
 ** The above methods read of all of remaining tokens
 ** on standard input converts the tokens to values of
 ** the specified type and returns a vector of the
 ** specified type. The read_all_lines() method reads
 ** all remaining lines on standard input and returns
 ** them as an vector of strings. The read_all method
 ** reads all remaining input on standard input and
 ** returns it as a string. As an example, the following
 ** code fragment reads all of the remaining tokens from
 ** standard input and returns them as an vector of strings.
 ** vector<string> = stdin::read_all_strings();
 **
 ** Using standard input
 ** Standard input is fundamental operating system
 ** abstraction, on Mac OS X, Windows, and Linux.
 ** The methods in cstdin are blocking, which means
 ** that they will wait until you enter input on
 ** standard input. If your program has a loop that
 ** repeats until standard input is empty,
 ** you must signal that the input is finished.
 ** To do so, depending on your operating system and IDE,
 ** use either {@code <Ctrl-d>} or {@code <Ctrl-z>},
 ** on its own line. If you are redirecting standard
 ** input from a file, you will not need to do anything
 ** to signal that the input is finished.
 **
 ** Known bugs.
 **
 ** Reference. 
 ** For additional documentation,
 ** see http://introcs.cs.princeton.edu/15inout - Section 1.5 of
 ** Introduction to Programming in Java: An Interdisciplinary Approach<
 ** by Robert Sedgewick and Kevin Wayne.
 **
 ** author Prakash Easwar 
 **/
class cstdin {

    private :
        /** helper function for
         ** uint[8,16,32,64]_t, int[8,16,32,64]_t,
         ** Reads the next token from standard input,
         ** parses it as an [u]int64, and returns the integer.
         ** return the next int64 on standard input
         ** int64_t - returns LONG_MIN, LONG_MAX if value is out of range
         ** uint64_t - returns ULONG_MAX if value is out of range
         ** throws ios_base::failure::failure on error
         **/
        template<typename T, typename F>
        static T read_xint64(istream& is, T& val, F conv_func) {
            string token = read_string(is);
            char *end;
            const char *p = token.c_str();
            val = conv_func(token.c_str(), &end, 0);

            if(p == end) {
                throw ios_base::failure(
                     "bad token '" + token +  "' in input");
            }
            return val;
        }

        /** helper function for
         ** float, double, long double
         ** Reads the next token from standard input,
         ** parses it as an type T, and returns T.
         ** return the next value of tyep T on standard input
         ** returns
         ** float - HUGE_VALF
         ** double - HUGE_VAL
         ** long double - HUGE_VALL
         ** if value is out of range
         ** returns on error
         ** float - nanf("1")
         ** double - nan("1")
         ** long double - nanl("1")
         **/
        template<typename T, typename F, typename N>
        static T read_xfld(istream& is, T& val,
                           F conv_func, N nan_func) {
            string token = read_string(is);
            char *end;
            const char *p = token.c_str();
            val = conv_func(token.c_str(), &end);

            if(p == end) {
                val = nan_func("1");
            }

            if(val > numeric_limits<T>::max())
                val = numeric_limits<T>::max();
            else if(val < -numeric_limits<T>::min())
                val = -numeric_limits<T>::min();
            
            return val;
        }
        
        /**
         ** Reads all remaining lines from standard input
         ** and returns them as an vector of T.
         ** return all remaining lines on standard input,
         ** as an vector of T 
         **/
        template<typename T, typename F, typename H>
        static vector<T> read_all_xtype(istream& is, vector<T>& val,
                                          F next_func, H has_next_func) {
            while(has_next_func(is)) {
                val.push_back(next_func(is));
            }
            return val;
        }

    public :
        /**
         ** Returns true if standard input has next 
         ** token.
         ** Use this method to know whether the next call
         ** to readString(), read_double(), etc will succeed.
         **
         ** return true if standard input has text token
         **         ; false if empty (or possible whitespace
         **/
        static bool has_next(istream& is = cin) {
            int ch;
            while((ch = is.peek()) >= 0) {
                if(!isspace(ch)) {
                    return true;
                }
                ch = is.get();
            }
            return false;
        }
    
        /**
         ** Returns true if standard input has more
         ** input (including whitespace). Use this method
         ** to know whether the next call readChar() will
         ** succeed. This method is functionally equivalent
         ** to has_next_line().
         **
         ** return true if standard input has more
         **             input (including whitespace);
         **        false otherwise
         **/
        static bool has_next_char(istream& is = cin) {
           return (is.peek() >= 0);
        }

        /**
         ** Returns true if standard input is empty
         ** (except possibly for whitespace).
         ** Use this method to know whether the next call
         ** to readString(), read_double(), etc will succeed.
         **
         ** return true if standard input is empty (except possibly
         **         for whitespace); false otherwise
         **/
        static bool is_empty(istream& is = cin) {
            return !has_next(is);
        }
        
        /**
         ** Reads the next token and returns the string.
         ** return the next string
         **/
        static string read_next(istream& is = cin) {
            int ch;
            string token;

            while((ch = is.peek()) >= 0) {
                if(!isspace(ch)) {
                    break;
                }
                ch = is.get();
            }

            while((ch = is.peek()) >= 0) {
                if(isspace(ch)) {
                    break;
                } else {
                    token += static_cast<char>(is.get());
                }
            }

            return token;
        }
 
        /**
         ** Returns true if standard input has a next line.
         ** Use this method to know whether the
         ** next call to readLine() will succeed.
         ** This method is functionally equivalent
         ** to has_next_char().
         **
         ** return true if standard input is empty;
         **        false otherwise
         **/
        static bool has_next_line(istream& is = cin) {
            return has_next_char(is);
        }
   
        /**
         ** Reads and returns the next line, excluding the line
         ** separator if present.  return the next line, excluding
         ** the line separator if present
         **/
        static string read_line(istream& is = cin) {
            string line;
            int ch;

            while((ch = is.get()) >= 0) {
                if((ch != '\r') &&
                   (ch != '\n')) {
                    line += static_cast<char>(ch);
                } else if(ch == '\n') {
                    break;
                } else {
                    if(is.peek() == '\n') {
                        ch = is.get();
                    }
                    break;
                }
            }
            return line;
        }
 
        /**
         ** Reads and returns the next character.
         ** return the next character
         **/
        static char read_char(istream& is = cin) {
            return static_cast<char>(is.get());
        }

        /**
         ** Reads and returns the remainder of the input, as a string.
         ** return the remainder of the input, as a string
         **/
        static string read_all(istream& is = cin) {
            string input;
            int ch;

            while((ch = is.get()) >= 0) {
                input += static_cast<char>(ch);
            }
            return input; 
        }
   
        /**
         ** Reads the next token  and returns the string.
         ** return the next string
         **/
        static string read_string(istream& is = cin) {
            return read_next(is);
        }
    
        /**
         ** Reads the next token from standard input, parses it as a boolean,
         ** and returns the boolean.
         ** return the next boolean on standard input
         ** returns true or 1 for true,
         **            and false or 0 for false,
         ** ignoring case
         ** throws ios_base::failure::failure on error
         **/
        static bool read_bool(istream& is = cin) {
            bool throw_exp = false;
            bool val;
            string token = read_string(is);
            if(token.length() == 4) {
                if(equal(token.begin(),
                         token.end(),
                         begin("true"),
                         utils::strequals_igncase)) {
                   val = true;
                }
            } else if(token.length() == 5) {
                if(equal(token.begin(),
                          token.end(),
                          begin("false"),
                          utils::strequals_igncase)) {
                   val = false;
                }
            } else if(token.length() == 1) {
               if(token[0] == '1') {
                   val = true;
               } else if(token[0] == '0') {
                   val = false;
               } else {
                   throw_exp = true;
               }
            } else {
               throw_exp = true;
            }
            if(throw_exp) {
               throw ios_base::failure(
                     "bad boolean '" + token +  "' in input");
            }
            return val;
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an int64, and returns the integer.
         ** return the next int64 on standard input
         ** returns LONG_MIN, LONG_MAX if value is out of range
         ** throws ios_base::failure::failure on error
         **/
        static int64_t read_int64(istream& is = cin) {
            int64_t val;
            read_xint64(is, val, strtoll);
            return val;
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an uint64_t, and returns the integer.
         ** return the next uint64_t on standard input
         ** returns ULONG_MAX if value is
         ** out of range
         ** throws ios_base::failure::failure on error
         **/
        static uint64_t read_uint64(istream& is = cin) {
            uint64_t val;
            read_xint64(is, val, strtoull);
            return val;
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an int32, and returns the integer.
         ** return the next int32 on standard input
         ** returns INT_MIN, INT_MAX if value is out of range
         ** throws ios_base::failure::failure on error
         **/
        static int32_t read_int32(istream& is = cin) {
            int64_t val = read_int64(is);
            if (val <= static_cast<int64_t>(INT_MIN))
                return INT_MIN;
            if (val >= static_cast<int64_t>(INT_MAX))
                return INT_MAX;
            return static_cast<int32_t>(val);
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an uint32_t, and returns the integer.
         ** return the next uint32_t on standard input
         ** returns UINT_MAX if value is
         ** out of range
         ** throws ios_base::failure::failure on error
         **/
        static uint32_t read_uint32(istream& is = cin) {
            uint64_t val = read_uint64(is);
            if (val >= static_cast<uint64_t>(UINT_MAX))
                return UINT_MAX;
            return static_cast<uint32_t>(val);
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an int16, and returns the integer.
         ** return the next int16 on standard input
         ** returns USHRT_MIN, USHRT_MAX if value is out of range
         ** throws ios_base::failure::failure on error
         **/
        static int16_t read_int16(istream& is = cin) {
            int64_t val = read_int64(is);
            if (val <= static_cast<int64_t>(SHRT_MIN))
                return SHRT_MIN;
            if (val >= static_cast<int64_t>(SHRT_MAX))
                return SHRT_MAX;
            return static_cast<int16_t>(val);
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an uint16_t, and returns the integer.
         ** return the next uint16_t on standard input
         ** returns USHRT_MAX if value is out of range
         ** throws ios_base::failure::failure on error
         **/
        static uint16_t read_uint16(istream& is = cin) {
            uint64_t val = read_uint64(is);
            if (val >= static_cast<uint64_t>(USHRT_MAX))
                return USHRT_MAX;
            return static_cast<uint16_t>(val);
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an int8, and returns the integer.
         ** return the next int8 on standard input
         ** returns SCHAR_MIN, SCHAR_MAX if value is out of range
         ** throws ios_base::failure::failure on error
         **/
        static int8_t read_int8(istream& is = cin) {
            int64_t val = read_int64(is);
            if (val <= static_cast<int64_t>(SCHAR_MIN))
                return SCHAR_MIN;
            if (val >= static_cast<int64_t>(SCHAR_MAX))
                return SCHAR_MAX;
            return static_cast<int8_t>(val);
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an uint8_t, and returns the integer.
         ** return the next uint8_t on standard input
         ** returns UCHAR_MAX if value is
         ** out of range
         ** throws ios_base::failure::failure on error
         **/
        static uint8_t read_uint8(istream& is = cin) {
            uint64_t val = read_uint64(is);
            if (val >= static_cast<uint64_t>(UCHAR_MAX))
                return UCHAR_MAX;
            return static_cast<uint8_t>(val);
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an float , and returns the float.
         ** return the next float on standard input
         ** returns HUGE_VALF if value is
         ** out of range
         ** returns nanf("1") on error
         **/
        static float read_float(istream& is = cin) {
            float val;
            read_xfld(is, val, strtof, nanf);
            return val;
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an double, and returns the double.
         ** return the next double on standard input
         ** returns HUGE_VAL if value is
         ** out of range
         ** returns nan("1") on error
         **/
        static double read_double(istream& is = cin) {
            double val;
            read_xfld(is, val, strtod, nan);
            return val;
        }

        /**
         ** Reads the next token from standard input,
         ** parses it as an long double, and returns the long double.
         ** return the next long double on standard input
         ** returns HUGE_VALL if value is
         ** out of range
         ** returns nanl("1") on error
         **/
        static long double read_long_double(istream& is = cin) {
            long double val;
            read_xfld(is, val, strtold, nanl);
            return val;
        }
    
        /**
         ** Reads all remaining tokens from standard input
         ** and returns them as an array of strings.
         ** return all remaining tokens on standard input,
         ** as an array of strings
         **/
        static vector<string> read_all_strings(istream& is = cin) {
            vector<string> val;
            read_all_xtype(is, val, read_next, has_next);
            return val;
        }
    
         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of strings.
          ** return all remaining lines on standard input,
          ** as an array of strings
          **/
         static vector<string> read_all_lines(istream& is = cin) {
             vector<string> val;
             read_all_xtype(is, val, read_line, has_next_line);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of uint64.
          ** return all remaining lines on standard input,
          ** as an array of uint64
          ** throws ios_base::failure::failure on error
          **/
         static vector<uint64_t> read_all_uint64s(istream& is = cin) {
             vector<uint64_t> val;
             read_all_xtype(is, val, read_uint64, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of int64.
          ** return all remaining lines on standard input,
          ** as an array of int64
          ** throws ios_base::failure::failure on error
          **/
         static vector<int64_t> read_all_int64s(istream& is = cin) {
             vector<int64_t> val;
             read_all_xtype(is, val, read_int64, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of uint32.
          ** return all remaining lines on standard input,
          ** as an array of uint32
          ** throws ios_base::failure::failure on error
          **/
         static vector<uint32_t> read_all_uint32s(istream& is = cin) {
             vector<uint32_t> val;
             read_all_xtype(is, val, read_uint32, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of int32.
          ** return all remaining lines on standard input,
          ** as an array of int32
          ** throws ios_base::failure::failure on error
          **/
         static vector<int32_t> read_all_int32s(istream& is = cin) {
             vector<int32_t> val;
             read_all_xtype(is, val, read_int32, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of uint16.
          ** return all remaining lines on standard input,
          ** as an array of uint16
          ** throws ios_base::failure::failure on error
          **/
         static vector<uint16_t> read_all_uint16s(istream& is = cin) {
             vector<uint16_t> val;
             read_all_xtype(is, val, read_uint16, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of int16.
          ** return all remaining lines on standard input,
          ** as an array of int16
          ** throws ios_base::failure::failure on error
          **/
         static vector<int16_t> read_all_int16s(istream& is = cin) {
             vector<int16_t> val;
             read_all_xtype(is, val, read_int16, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of uint8.
          ** return all remaining lines on standard input,
          ** as an array of uint8
          ** throws ios_base::failure::failure on error
          **/
         static vector<uint8_t> read_all_uint8s(istream& is = cin) {
             vector<uint8_t> val;
             read_all_xtype(is, val, read_uint8, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of int8.
          ** return all remaining lines on standard input,
          ** as an array of int8
          ** throws ios_base::failure::failure on error
          **/
         static vector<int8_t> read_all_int8s(istream& is = cin) {
             vector<int8_t> val;
             read_all_xtype(is, val, read_int8, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of float.
          ** return all remaining lines on standard input,
          ** as an array of float
          **/
         static vector<float> read_all_floats(istream& is = cin) {
             vector<float> val;
             read_all_xtype(is, val, read_float, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of double.
          ** return all remaining lines on standard input,
          ** as an array of double
          **/
         static vector<double> read_all_doubles(istream& is = cin) {
             vector<double> val;
             read_all_xtype(is, val, read_double, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of long double.
          ** return all remaining lines on standard input,
          ** as an array of double
          **/
         static vector<long double> read_all_long_doubles(istream& is = cin) {
             vector<long double> val;
             read_all_xtype(is, val, read_long_double, has_next);
             return val;
         }

         /**
          ** Reads all remaining lines from standard input
          ** and returns them as an array of bool.
          ** return all remaining lines on standard input,
          ** as an array of bool
          ** throws ios_base::failure::failure on error
          **/
         static vector<bool> read_all_bools(istream& is = cin) {
             vector<bool> val;
             read_all_xtype(is, val, read_bool, has_next);
             return val;
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

#endif /* __CSTDIN__ */
