/******************************************************************************
 *  Dependencies: none
 *
 *  Weighted quick-union by rank with path compression by halving.
 ******************************************************************************/
#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <stdexcept>
#include <memory>

namespace edu {
namespace princeton {
namespace cs {
namespace algs4 {

using std::invalid_argument;
using std::unique_ptr;

/**
 ** The union_find class represents a union-find
 ** data type (also known as the disjoint-sets
 ** data type).
 ** It supports the set_union and find operations,
 ** along with a is_connected operation for determining
 ** whether two sites are in the same component and a
 ** count operation that returns the total number of
 ** components.
 ** 
 ** The union-find data type models connectivity among
 ** a set of N sites, named 0 through N - 1.
 ** The is-connected-to relation must be an equivalence
 ** relation
 ** Reflexive: p is connected to p.
 ** Symmetric: p is connected to q,
 **            then q is connected to p.
 ** Transitive: If p is connected to q
 **             and q is connected to r
 **             then p is connected to r.
 **
 ** An equivalence relation partitions the sites into
 ** equivalence classes(or components). In this case,
 ** two sites are in the same component if and only if
 ** they are connected. Both sites and components are
 ** identified with integers between 0 and N-1. Initially,
 ** there are N components, with each site in its own component.
 ** The component identifier of a component(also known as the
 ** root, canonical element, leader, or set representative)
 ** is one of the sites in the component: two sites have the same
 ** component identifier if and only if they are
 ** in the same component.
 **
 ** set_union(p, q) - adds a connection between the two sites
 **               p and q.
 **               If p and q are in different components,
 **               then it replaces these two components
 **               with a new component that is the union of
 **               the two.
 ** find(p) - returns the component identifier of the component
 **           containing p.
 ** is_connected(p, q) - returns true if both p and q
 **                   are in the same component, and
 **                   false otherwise.
 ** count() - returns the number of components.
 ** 
 ** The component identifier of a component can change
 ** only when the component itself changes during a call to
 ** set_union. it cannot change during a call to find,
 ** is_connected, or count.
 **
 ** This implementation uses weighted quick union by rank
 ** with path compression by halving.
 ** Initializing a data structure with N sites takes linear time.
 ** Afterwards, the set_union, find, and is_connected
 ** operations take logarithmic time (in the worst case) and the
 ** count operation takes constant time. Moreover, the amortized
 ** time per set_union, find, and is_connected operation has inverse
 ** Ackermann complexity.
 **/
template<typename S = uint32_t,
         typename C = uint32_t,
         typename R = uint8_t>
class union_find_t {
    public :
        using site_id_type = S;
        using site_id_type_ptr = unique_ptr<site_id_type[]>;
        using component_id_type = C;
        using rank_type = R;
        using rank_type_ptr = unique_ptr<rank_type[]>;
        
        /**
         ** Initializes an empty union-find data structure
         ** with N sites 0 through N-1.
         ** Each site is initially in its own component.
         **
         ** params : N the number of sites
         **/
        union_find_t(size_t num_sites) :
            sites(new site_id_type[num_sites]),
            ranks(new rank_type[num_sites]),
            count(num_sites), n_sites(num_sites) {
            for(size_t i = 0; i < num_sites; i++) {
                ranks[i] = 0;
                sites[i] = i;
            }
        }

        /**
         ** Merges the component containing site p
         ** with the the component containing site q.
         **
         ** param  : p the integer representing one site
         ** param  : q the integer representing the other site
         ** throws : invalid_argument exception unless
         **          both 0 <= p <= N< and 0 <= q <= N
         **/
        void set_union(const site_id_type& p,
                       const site_id_type& q) {
            validate_data(p, q);
            site_id_type root_p = get_root(p);
            site_id_type root_q = get_root(q);

            if (root_p == root_q) return;

            if(ranks[root_p] < ranks[root_q]) {
                sites[root_p] = root_q;
            } else if(ranks[root_p] > ranks[root_q]) {
                sites[root_q] = root_p;
            } else {
                sites[root_q] = root_p;
                ranks[root_p]++;
            }
            count--;
        }
         
        /**
         ** Returns the component identifier for the component
         ** containing site p.
         **
         ** params  : p the integer representing one site
         ** returns : the component identifier for the component
         **           containing site p
         ** throws  : invalid_argument exception unless 0 <= p <= N
         **/
        component_id_type
             find(const site_id_type& p) {
            validate_data(p);
            return get_root(p);
        }

        bool is_connected(const site_id_type& p,
                          const site_id_type& q) {
            validate_data(p, q);
            return (get_root(p) == get_root(q));
        }

        /**
         ** Returns the number of components.
         **
         ** returns : the number of components(between 1 and N)
         **/
        size_t get_count() const {
            return count;
        }

        /**
         ** Returns the number of number of configured sites.
         **
         ** returns : the number of configured sites (N)
         **/
        size_t get_num_sites() const {
            return n_sites;
        }

    private :
        site_id_type_ptr sites;
        rank_type_ptr ranks;
        size_t count;
        size_t n_sites;

        /**
         ** Internal method to validate the input data
         **
         ** params  : p the integer representing one site
         ** throws  : invalid_argument exception unless 0 <= p <= N
         **/
        void validate_data(const site_id_type& p) const {
            if (p >= n_sites) {
                throw invalid_argument( "invalid argument :"
                                         "p >= num_sites");
            }
        }

        /**
         ** Internal method to validate the input data
         **
         ** param  : p the integer representing one site
         ** param  : q the integer representing the other site
         ** throws : invalid_argument exception unless
         **          both 0 <= p <= N< and 0 <= q <= N
         **/
        void validate_data(const site_id_type& p,
                           const site_id_type& q) const {
            if ( (p >= n_sites) &&
                 (q >= n_sites) ) {
                throw invalid_argument( "invalid argument :"
                                         "p and q >= num_sites");
            } else if (p >= n_sites) {
                throw invalid_argument( "invalid argument :"
                                         "p >= num_sites");
            } else if (q >= n_sites) {
                throw invalid_argument( "invalid argument :"
                                         "q >= num_sites");
            }
        }

        /**
         ** Internal method to get the root (component) of
         ** a given site
         **
         ** param   : p the integer representing one site
         ** returns : the component id of a given site.
         ** 
         ** Assumes input data is valid.
         **/
        component_id_type get_root(const site_id_type& p) {
            site_id_type root = p;
            while ( root != sites[root]) {
                sites[root] = sites[sites[root]];
                root = sites[root];
            }
            return root;
        }
};

class union_find : public union_find_t<> {
    public :
        using union_find_t<>::union_find_t;
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

#endif /* __UNION_FIND_H__ */

