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
