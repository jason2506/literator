// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_USE_DEFAULT_HPP_
#define LITERATOR_INTERNAL_USE_DEFAULT_HPP_

#include <type_traits>

namespace literator {

namespace internal {

/************************************************
 * Declaration: struct use_default
 ************************************************/

struct use_default;  // without definition

/************************************************
 * Declaration: type get_with_default<T, D>
 ************************************************/

template <typename T, typename Default>
using get_with_default_t = typename std::conditional<
    std::is_same<T, use_default>::value,
    Default,
    T
>;

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_USE_DEFAULT_HPP_
