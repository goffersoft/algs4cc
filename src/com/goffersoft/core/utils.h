/** 
 **
 ** This file is part of algs4cc.
 **
 ** algs4cc is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** algs4cc is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with algs4cc. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the utils class of the algs4cc project.
 ** This class cannot be instantiated. Has a bunch of static
 ** helper functions
 **/
#ifndef __UTILS_H__
#define __UTILS_H__

#include<cctype>

namespace com {
namespace goffersoft {
namespace core {

class utils {
    public :
        utils() = delete;

        static bool strequals_igncase(unsigned char a,
                                      unsigned char b) {
            return tolower(a) == tolower(b);
        };
};

} //com
} //goffersoft
} //core

#endif /* __UTILS_H__ */
