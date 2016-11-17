// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_FILTER_ITERATOR_BASE_HPP_
#define LITERATOR_INTERNAL_FILTER_ITERATOR_BASE_HPP_

#include <iterator>
#include <type_traits>

#include "../iterator_adaptor.hpp"

namespace literator {

// forward declaration
template <typename Predicate, typename Iterator>
class filter_iterator;

namespace internal {

/************************************************
 * Declaration: class filter_iterator_base<P, I>
 ************************************************/

template <typename Predicate, typename Iterator>
using filter_iterator_base = iterator_adaptor<
    filter_iterator<Predicate, Iterator>,
    Iterator,
    use_default,
    typename std::conditional<
        std::is_convertible<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::random_access_iterator_tag
        >::value,
        std::bidirectional_iterator_tag,
        use_default
    >::type
>;

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_FILTER_ITERATOR_BASE_HPP_
