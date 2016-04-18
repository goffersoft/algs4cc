/******************************************************************************
 *  Dependencies: none
 *
 *  data structure for bag (lightweight equivalent of std::multiset)
 *
 ******************************************************************************/
#ifndef __BAG_H__
#define __BAG_H__

#include <sstream>
#include <string>
#include <list>
#include <type_traits>

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::stringstream;
using std::endl;
using std::string;
using std::list;
using std::conditional;
using std::reference_wrapper;

/**
 **  The bag class represents a bag (or multiset) of
 **  generic items. It supports insertion and iterating over the
 **  items in arbitrary order.
 **  This implementation uses a std::list 
 **  The add, isEmpty, size operations take constant time.
 **  Iteration takes time proportional to the number of items.
 **
 **  the bag class can store a reference or value.
 **  to store references of type T in the bag use
 **     bag<T>::bag_rererence_type
 **  to store values of type T in the bag use
 **     bag<T>::bag_value_type
 **  typically auto would suffice for iterating over the items
 **  in a bag.
 **  incase iterator type is needed :
 **
 **  for iterating over a bag of references use
 **    bag<T, true>::iterator or bag<T>::reference_iterator;
 **    bag<T, true>::const_iterator or bag<T>::const_reference_iterator;
 **
 **  for iterating over a bag of values use
 **    bag<T, true>::iterator or bag<T>::value_iterator;
 **    bag<T, true>::const_iterator or bag<T>::const_value_iterator;
 **/
template<typename T, bool is_reference_type = true,
         typename L = list<typename conditional<
                                   is_reference_type,
                                   reference_wrapper<T>, T>::type > >
class bag {
    private :
        template<bool is_const_iterator> class bag_const_noconst_iterator;

    public :
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using const_reference = const T&;
        using const_pointer = const T*;
        using bag_reference_type = bag<T, true>;
        using bag_value_type = bag<T, false>;
        using iterator = bag_const_noconst_iterator<false>;
        using const_iterator = bag_const_noconst_iterator<true>;
        using reference_iterator =
                 typename bag_reference_type::iterator;
        using const_reference_iterator =
                 typename bag_reference_type::const_iterator;
        using value_iterator =
                 typename bag_value_type::iterator;
        using const_value_iterator =
                 typename bag_value_type::const_iterator;

        bag() {}

        bool is_empty() const { return list_of_items.empty(); }

        size_t size() const { return list_of_items.size(); }

        void add(typename conditional<is_reference_type,
                             reference,
                             const_reference>::type item) {
            list_of_items.emplace_back(item);
        }

        const_iterator cbegin() const { return const_iterator(list_of_items.cbegin()); }

        const_iterator cend() const { return const_iterator(list_of_items.cend()); }

        const_iterator begin() const { return const_iterator(list_of_items.begin()); }

        const_iterator end() const { return const_iterator(list_of_items.end()); }

        iterator begin() { return iterator(list_of_items.begin()); }

        iterator end() { return iterator(list_of_items.end()); }

        operator string() {
            stringstream ss;
            size_t col = 0;
            for(T& a : list_of_items) {
                if((col != 0) && ((col % 16) == 0)) {
                    ss << endl;
                }
                ss << a << " ";
            }
            ss << endl;
            return ss.str();
        }
    private :
        L list_of_items;

        template<bool is_const_iterator = true>
        class bag_const_noconst_iterator {
            public :
                using iterator_type =  typename conditional<is_const_iterator,
                                                   typename L::const_iterator,
                                                   typename L::iterator>::type;
                using value_reference_type =  typename conditional<is_const_iterator,
                                                                   const_reference,
                                                                   reference>::type;
                bag_const_noconst_iterator(iterator_type x) : it(x) {}
                bag_const_noconst_iterator(
                      const bag_const_noconst_iterator& that) : it(that.it) {}

                bool operator ==(const bag_const_noconst_iterator& that) const {
                    return (it == that.it);
                }

                bool operator !=(const bag_const_noconst_iterator& that) const {
                    return !(*this == that);
                }

                value_reference_type operator *() const { return *it; }
                
                bag_const_noconst_iterator<is_const_iterator>& operator ++() {
                    ++it;
                    return *this;
                }

                bag_const_noconst_iterator<is_const_iterator> operator ++(int) { 
                    bag_const_noconst_iterator<is_const_iterator> tmpit(*this);
                    ++(*this);
                    return tmpit;
                }
        
            private : 
                iterator_type it;
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

#endif /* __BAG_H__ */
