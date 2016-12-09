// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_ZIP_ITERATOR_HPP_
#define LITERATOR_ZIP_ITERATOR_HPP_

#include <iterator>
#include <tuple>

#include "internal/zip_iterator_base.hpp"

namespace literator {

/************************************************
 * Declaration: class zip_iterator<Is...>
 ************************************************/

template <typename... Iterators>
class zip_iterator : public internal::zip_iterator_base<Iterators...> {
 private:  // Private Type(s)
    friend class iterator_core_access;
    using super_t = typename internal::zip_iterator_base<Iterators...>;

 public:  // Public Methods(s)
    zip_iterator() = default;
    explicit zip_iterator(Iterators... its)
        : its_(its...) { /* do nothing */ }

 private:  // Private Method(s)
    typename super_t::reference dereference() const {
        auto f = [](auto const &it) -> decltype(auto) { return *it; };
        return internal::fmap(f, its_);
    }

    template <typename... OtherIterators>
    bool equal(zip_iterator<OtherIterators...> const &it) const {
        return its_ == it.its_;
    }

    void advance(typename super_t::difference_type n) {
        auto f = [n](auto &it) { std::advance(it, n); };
        internal::for_each(f, its_);
    }

    void increment() {
        auto f = [](auto &it) { ++it; };
        internal::for_each(f, its_);
    }

    void decrement() {
        auto f = [](auto &it) { --it; };
        internal::for_each(f, its_);
    }

    template <typename... OtherIterators>
    typename super_t::difference_type distance_to(zip_iterator<OtherIterators...> const &it) const {
        return std::get<0>(it.its_) - std::get<0>(its_);
    }

 private:  // Private Properties(s)
    std::tuple<Iterators...> its_;
};  // class zip_iterator<Is...>

/************************************************
 * Declaration: Non-member Function(s)
 ************************************************/

template <typename... Iterators>
inline zip_iterator<Iterators...>
make_zip_iterator(Iterators... its) {
    return zip_iterator<Iterators...>(its...);
}

}  // namespace literator

#endif  // LITERATOR_ZIP_ITERATOR_HPP_
