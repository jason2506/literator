// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_ITERATOR_FACADE_HPP_
#define LITERATOR_ITERATOR_FACADE_HPP_

#include <cstddef>

#include "internal/iterator_core_access.hpp"
#include "internal/iterator_facade_base.hpp"

namespace literator {

using internal::iterator_core_access;

/************************************************
 * Declaration: class iterator_facade<I, T, C, R, D>
 ************************************************/

template <
    typename Derived,
    typename Value,
    typename Category,
    typename Reference = Value &,
    typename Difference = std::ptrdiff_t
>
class iterator_facade : public internal::iterator_facade_base<
    Derived,
    Value,
    Category,
    Reference,
    Difference,
    std::is_convertible<Category, std::bidirectional_iterator_tag>::value,
    std::is_convertible<Category, std::random_access_iterator_tag>::value
> { /* empty */ };  // class iterator_facade<I, V, C, R, D>

/************************************************
 * Declaration: Non-member Function(s)
 ************************************************/

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline internal::enable_if_interoperable_t<I1, I2, bool>
operator==(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::equal(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs));
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline internal::enable_if_interoperable_t<I1, I2, bool>
operator!=(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return !iterator_core_access::equal(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs));
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline internal::enable_if_interoperable_and_random_access_iterator_t<I1, I2, bool>
operator<(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                      iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) < 0;
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline internal::enable_if_interoperable_and_random_access_iterator_t<I1, I2, bool>
operator>(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                      iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) > 0;
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline internal::enable_if_interoperable_and_random_access_iterator_t<I1, I2, bool>
operator<=(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) <= 0;
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline internal::enable_if_interoperable_and_random_access_iterator_t<I1, I2, bool>
operator>=(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) >= 0;
}

}  // namespace literator

#endif  // LITERATOR_ITERATOR_FACADE_HPP_
