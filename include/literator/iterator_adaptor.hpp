// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_ITERATOR_ADAPTOR_HPP_
#define LITERATOR_ITERATOR_ADAPTOR_HPP_

#include "internal/use_default.hpp"
#include "internal/iterator_adaptor_base.hpp"

#include "iterator_facade.hpp"

namespace literator {

using internal::use_default;

/************************************************
 * Declaration: class iterator_adaptor<I, B, V, C, R, D>
 ************************************************/

template <
    typename Derived,
    typename Base,
    typename Value = use_default,
    typename Category = use_default,
    typename Reference = use_default,
    typename Difference = use_default
>
class iterator_adaptor : public internal::iterator_adaptor_base<
    Derived, Base, Value, Category, Reference, Difference
> {
    friend class iterator_core_access;

 public:  // Public Types(s)
    typedef Base base_type;

 public:  // Public Methods(s)
    iterator_adaptor() = default;
    explicit iterator_adaptor(base_type const &it)
        : it_(it) { /* do nothing */ }

    base_type const &base() const { return it_; }

 protected:  // Protected Method(s)
    base_type &base_reference() { return it_; }
    base_type const &base_reference() const { return it_; }

 protected:  // Protected Type(s)
    using super_t = typename internal::iterator_adaptor_base<
        Derived, Base, Value, Category, Reference, Difference
    >;

 private:  // Private Method(s)
    typename super_t::reference dereference() const { return *it_; }

    void increment() { ++it_; }
    void decrement() { --it_; }

    void advance(typename super_t::difference_type n) { it_ += n; }

    template <typename I, typename B, typename V, typename C, typename R, typename D>
    typename super_t::difference_type
    distance_to(iterator_adaptor<I, B, V, C, R, D> const &it) const {
        return it.base_reference() - it_;
    }

    template <typename I, typename B, typename V, typename C, typename R, typename D>
    bool equal(iterator_adaptor<I, B, V, C, R, D> const &it) const {
        return it.base_reference() == it_;
    }

 private:  // Private Properties(s)
    base_type it_;
};  // class iterator_adaptor<I, B, V, C, R, D>

}  // namespace literator

#endif  // LITERATOR_ITERATOR_ADAPTOR_HPP_
