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

#include "internal/iterator_facade_helpers.hpp"

namespace literator {

/************************************************
 * Declaration: struct iterator_core_access
 ************************************************/

struct iterator_core_access {
    template <typename Facade>  // NOLINTNEXTLINE(runtime/references)
    static typename Facade::reference dereference(Facade &f) {
        return f.dereference();
    }

    template <typename Facade>  // NOLINTNEXTLINE(runtime/references)
    static void increment(Facade &f) { return f.increment(); }

    template <typename Facade>  // NOLINTNEXTLINE(runtime/references)
    static void decrement(Facade &f) { return f.decrement(); }

    template <typename Facade>  // NOLINTNEXTLINE(runtime/references)
    static void advance(Facade &f, typename Facade::difference_type n) {
        return f.advance(n);
    }

    template <typename Facade1, typename Facade2>
    static typename Facade1::difference_type
    distance_from(Facade1 const &f1, Facade2 const &f2) {
        return f1.distance_to(f2);
    }

    template <typename Facade1, typename Facade2>
    static bool equal(Facade1 const &f1, Facade2 const &f2) {
        return f1.equal(f2);
    }
};  // struct iterator_core_access

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
class iterator_facade {
 private:  // Private Type(s)
    using associated_types = internal::iterator_facade_types<Value, Reference>;

    using operator_arrow_dispatch = internal::operator_arrow_dispatch<
        Reference,
        typename associated_types::pointer
    >;

    using postfix_increment_result = typename internal::postfix_increment_result<
        Derived,
        Value,
        Reference,
        Category
    >::type;

    using operator_brackets_dispatch = typename internal::operator_brackets_dispatch<
        Derived,
        Value,
        Reference
    >;

 public:  // Public Type(s)
    using value_type = typename std::remove_const<Value>::type;
    using iterator_category = Category;
    using reference = Reference;
    using pointer = typename operator_arrow_dispatch::result_type;
    using difference_type = Difference;

 public:  // Public Method(s)
    Derived &operator++() {
        iterator_core_access::increment(this->derived());
        return this->derived();
    }

    Derived operator++(int) {
        postfix_increment_result it(this->derived);
        ++(*this);
        return it;
    }

    Derived &operator--() {
        iterator_core_access::decrement(this->derived());
        return this->derived();
    }

    Derived operator--(int) {
        auto it = this->derived();
        --(*this);
        return it;
    }

    Derived &operator+=(difference_type n) {
        iterator_core_access::advance(this->derived(), n);
        return this->derived();
    }

    Derived &operator-=(difference_type n) {
        iterator_core_access::advance(this->derived(), -n);
        return this->derived();
    }

    Derived operator+(difference_type n) const {
        auto it = this->derived();
        return it += n;
    }

    Derived operator-(difference_type n) const {
        auto it = this->derived();
        return it -= n;
    }

    reference operator*() const {
        return iterator_core_access::dereference(this->derived());
    }

    pointer operator->() const {
        return operator_arrow_dispatch::apply(*(this->derived()));
    }

    typename operator_brackets_dispatch::result_type
    operator[](difference_type n) const {
        return operator_brackets_dispatch::apply(this->derived() + n);
    }

 private:  // Private Method(s)
    Derived &derived() {
        return *static_cast<Derived *>(this);
    }

    Derived const &derived() const {
        return *static_cast<Derived const *>(this);
    }
};  // class iterator_facade<I, V, C, R, D>

/************************************************
 * Declaration: Non-member Function(s)
 ************************************************/

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline bool operator==(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::equal(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs));
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline bool operator!=(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return !iterator_core_access::equal(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs));
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline bool operator<(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                      iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) < 0;
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline bool operator>(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                      iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) > 0;
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline bool operator<=(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) <= 0;
}

template <
    typename I1, typename T1, typename C1, typename R1, typename D1,
    typename I2, typename T2, typename C2, typename R2, typename D2
>
inline bool operator>=(iterator_facade<I1, T1, C1, R1, D1> const &lhs,
                       iterator_facade<I2, T2, C2, R2, D2> const &rhs) {
    return iterator_core_access::distance_from(
        *static_cast<I1 const *>(&lhs),
        *static_cast<I2 const *>(&rhs)) >= 0;
}

}  // namespace literator

#endif  // LITERATOR_ITERATOR_FACADE_HPP_
