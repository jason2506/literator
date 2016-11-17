// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_ITERATOR_ADAPTOR_BASE_HPP_
#define LITERATOR_INTERNAL_ITERATOR_ADAPTOR_BASE_HPP_

#include <iterator>

#include "../iterator_facade.hpp"

#include "use_default.hpp"

namespace literator {

namespace internal {

/************************************************
 * Declaration: class iterator_adaptor_base<I, B, V, C, R, D>
 ************************************************/

template <
    typename Derived,
    typename Base,
    typename Value,
    typename Category,
    typename Reference,
    typename Difference
>
using iterator_adaptor_base = iterator_facade<
    Derived,

    typename get_with_default<
        Value,
        typename std::iterator_traits<Base>::value_type
    >::type,

    typename get_with_default<
        Category,
        typename std::iterator_traits<Base>::iterator_category
    >::type,

    typename get_with_default<
        Reference,
        typename std::iterator_traits<Base>::reference
    >::type,

    typename get_with_default<
        Difference,
        typename std::iterator_traits<Base>::difference_type
    >::type
>;

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_ITERATOR_ADAPTOR_BASE_HPP_
