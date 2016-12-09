// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_ZIP_ITERATOR_BASE_HPP_
#define LITERATOR_INTERNAL_ZIP_ITERATOR_BASE_HPP_

#include <iterator>
#include <type_traits>
#include <tuple>

#include "../iterator_facade.hpp"

namespace literator {

// forward declaration
template <typename... Iterators>
class zip_iterator;

namespace internal {

/************************************************
 * Declaration: struct min_type<Ts...>
 ************************************************/

template <typename... Ts>
struct min_type;

template <typename T>
struct min_type<T> {
    using type = T;
};  // struct min_type<T>

template <typename T>
struct min_type<T, T> {
    using type = T;
};  // struct min_type<T, T>

template <typename T1, typename T2>
struct min_type<T1, T2> {
    using type = typename std::enable_if<
        std::is_convertible<T1, T2>::value ^ std::is_convertible<T2, T1>::value,
        typename std::conditional<
            std::is_convertible<T1, T2>::value,
            T2,
            T1
        >::type
    >::type;
};  // struct min_type<T1, T2>

template <typename T1, typename T2, typename... Ts>
struct min_type<T1, T2, Ts...> {
    using type = typename min_type<
        typename min_type<T1, T2>::type,
        Ts...
    >::type;
};  // struct min_type<T1, T2, Ts...>

/************************************************
 * Declaration: struct for_each_impl<N, F, Ts...>
 ************************************************/

template <std::size_t N, typename F, typename... Ts>
struct for_each_impl {
    void operator()(F f, std::tuple<Ts...> &t) {
        f(std::get<N>(t));
        for_each_impl<N + 1, F, Ts...>()(f, t);
    }
};  // struct for_each_impl<N, F, Ts...>

template <typename F, typename... Ts>
struct for_each_impl<sizeof...(Ts), F, Ts...> {
    void operator()(F f, std::tuple<Ts...> &t) {
        // do nothing
    }
};  // struct for_each_impl<sizeof...(Ts), F, Ts...>

/************************************************
 * Declaration: Helper Function(s)
 ************************************************/

template <typename F, typename... Ts, std::size_t... Is>
decltype(auto) fmap_impl(F f, std::tuple<Ts...> const &t, std::index_sequence<Is...>) {
    return std::forward_as_tuple(f(std::get<Is>(t))...);
}

template <typename F, typename... Ts>
decltype(auto) fmap(F f, std::tuple<Ts...> const &t) {
    return fmap_impl(f, t, std::make_index_sequence<sizeof...(Ts)>());
}

template <typename F, typename... Ts>
void for_each(F f, std::tuple<Ts...> &t) {
    for_each_impl<0, F, Ts...> apply;
    apply(f, t);
}

/************************************************
 * Declaration: class zip_iterator_reference<Is...>
 ************************************************/

template <typename... Iterators>
using zip_iterator_reference = std::tuple<typename std::iterator_traits<Iterators>::reference...>;

/************************************************
 * Declaration: class zip_iterator_base<Is...>
 ************************************************/

template <typename... Iterators>
using zip_iterator_base = iterator_facade<
    zip_iterator<Iterators...>,
    zip_iterator_reference<Iterators...>,
    typename min_type<
        std::random_access_iterator_tag,
        typename std::iterator_traits<Iterators>::iterator_category...
    >::type,
    zip_iterator_reference<Iterators...>,
    typename std::iterator_traits<
        typename std::tuple_element<0, std::tuple<Iterators...>>::type
    >::difference_type
>;

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_ZIP_ITERATOR_BASE_HPP_
