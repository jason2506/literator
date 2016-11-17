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
class iterator_adaptor
: public internal::iterator_adaptor_base<
    Derived, Base, Value, Category, Reference, Difference
> {
    friend class iterator_core_access;

 public:  // Public Types(s)
    typedef Base base_type;

 public:  // Public Methods(s)
    iterator_adaptor() = default;
    explicit iterator_adaptor(base_type const &it);

    base_type const &base() const;

 protected:  // Protected Type(s)
    using super_t = typename internal::iterator_adaptor_base<
        Derived, Base, Value, Category, Reference, Difference
    >;

 protected:  // Protected Method(s)
    base_type &base();

 private:  // Private Method(s)
    typename super_t::reference dereference() const;
    void increment();
    void decrement();
    void advance(typename super_t::difference_type n);

    template <typename I, typename B, typename V, typename C, typename R, typename D>
    typename super_t::difference_type
    distance_to(iterator_adaptor<I, B, V, C, R, D> const &it) const;

    template <typename I, typename B, typename V, typename C, typename R, typename D>
    bool equal(iterator_adaptor<I, B, V, C, R, D> const &it) const;

 private:  // Private Properties(s)
    base_type it_;
};  // class iterator_adaptor<I, B, V, C, R, D>

/************************************************
 * Implementation: class iterator_adaptor<I, B, V, C, R, D>
 ************************************************/

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline iterator_adaptor<I, B, V, C, R, D>::iterator_adaptor(base_type const &it)
    : it_(it) {
    // do nothing
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline typename iterator_adaptor<I, B, V, C, R, D>::base_type const &
iterator_adaptor<I, B, V, C, R, D>::base() const {
    return it_;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline typename iterator_adaptor<I, B, V, C, R, D>::base_type &
iterator_adaptor<I, B, V, C, R, D>::base() {
    return it_;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline typename iterator_adaptor<I, B, V, C, R, D>::super_t::reference
iterator_adaptor<I, B, V, C, R, D>::dereference() const {
    return *it_;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline void iterator_adaptor<I, B, V, C, R, D>::increment() {
    ++it_;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline void iterator_adaptor<I, B, V, C, R, D>::decrement() {
    --it_;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
inline void iterator_adaptor<I, B, V, C, R, D>::advance(typename super_t::difference_type n) {
    it_ += n;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
template <typename I2, typename B2, typename V2, typename C2, typename R2, typename D2>
inline typename iterator_adaptor<I, B, V, C, R, D>::super_t::difference_type
iterator_adaptor<I, B, V, C, R, D>::distance_to(
        iterator_adaptor<I2, B2, V2, C2, R2, D2> const &it) const {
    return it.base() - it_;
}

template <typename I, typename B, typename V, typename C, typename R, typename D>
template <typename I2, typename B2, typename V2, typename C2, typename R2, typename D2>
inline bool iterator_adaptor<I, B, V, C, R, D>::equal(
        iterator_adaptor<I2, B2, V2, C2, R2, D2> const &it) const {
    return it.base() == it_;
}

}  // namespace literator

#endif  // LITERATOR_ITERATOR_ADAPTOR_HPP_
