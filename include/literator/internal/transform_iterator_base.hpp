// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_TRANSFORM_ITERATOR_BASE_HPP_
#define LITERATOR_INTERNAL_TRANSFORM_ITERATOR_BASE_HPP_

#include <iterator>
#include <type_traits>

#include "use_default.hpp"

#include "../iterator_adaptor.hpp"

namespace literator {

// forward declaration
template <typename Transform, typename Iterator, typename Reference, typename Value>
class transform_iterator;

namespace internal {

/************************************************
 * Declaration: class transform_iterator_reference<F, I, R, V>
 ************************************************/

template <typename Transform, typename Iterator, typename Reference, typename Value>
using transform_iterator_reference = get_with_default_t<
    Reference,
    typename std::result_of<
        const Transform(typename std::iterator_traits<Iterator>::reference)
    >::type
>;

/************************************************
 * Declaration: class transform_iterator_base<F, I, R, V>
 ************************************************/

template <typename Transform, typename Iterator, typename Reference, typename Value>
using transform_iterator_base = iterator_adaptor<
    transform_iterator<Transform, Iterator, Reference, Value>,
    Iterator,
    get_with_default_t<
        Value,
        std::remove_reference<
            transform_iterator_reference<Transform, Iterator, Reference, Value>
        >
    >,
    use_default,
    transform_iterator_reference<Transform, Iterator, Reference, Value>
>;

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_TRANSFORM_ITERATOR_BASE_HPP_
