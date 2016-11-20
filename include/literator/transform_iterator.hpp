// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_TRANSFORM_ITERATOR_HPP_
#define LITERATOR_TRANSFORM_ITERATOR_HPP_

#include "internal/transform_iterator_base.hpp"

namespace literator {

/************************************************
 * Declaration: class transform_iterator<F, I, R, V>
 ************************************************/

template <
    typename Transform,
    typename Iterator,
    typename Reference = use_default,
    typename Value = use_default
>
class transform_iterator : public internal::transform_iterator_base<
    Transform, Iterator, Reference, Value
> {
    friend class iterator_core_access;

 private:  // Private Type(s)
    using super_t = typename internal::transform_iterator_base<
        Transform, Iterator, Reference, Value
    >;

 public:  // Public Methods(s)
    transform_iterator() = default;
    transform_iterator(Transform f, Iterator it)
        : super_t(it), f_(f) { /* do nothing */ }

 private:  // Private Method(s)
    typename super_t::reference dereference() const {
        return f_(*this->base_reference());
    }

 private:  // Private Properties(s)
    Transform f_;
};  // class transform_iterator<F, I, R, V>

/************************************************
 * Declaration: Non-member Function(s)
 ************************************************/

template <typename Transform, typename Iterator>
inline transform_iterator<Transform, Iterator>
make_transform_iterator(Transform f, Iterator it) {
    return transform_iterator<Transform, Iterator>(f, it);
}

}  // namespace literator

#endif  // LITERATOR_TRANSFORM_ITERATOR_HPP_
