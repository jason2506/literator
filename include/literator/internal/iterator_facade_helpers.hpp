// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_ITERATOR_FACADE_HELPERS_HPP_
#define LITERATOR_INTERNAL_ITERATOR_FACADE_HELPERS_HPP_

#include <iterator>
#include <memory>
#include <type_traits>

namespace literator {

namespace internal {

/************************************************
 * Declaration: struct is_reference_to_const<R>
 ************************************************/

template <typename Reference>
struct is_reference_to_const {
    static constexpr bool value = false;
};  // struct is_reference_to_const<R>

template <typename T>
struct is_reference_to_const<T const &> {
    static constexpr bool value = true;
};  // struct is_reference_to_const<T const &>

/************************************************
 * Declaration: struct iterator_writability_disabled<V, R>
 ************************************************/

template <typename Value, typename Reference>
struct iterator_writability_disabled {
    static constexpr bool value =
        std::is_const<Value>::value ||
        std::is_const<Reference>::value ||
        is_reference_to_const<Reference>::value;
};  // struct iterator_writability_disabled<V, R>

/************************************************
 * Declaration: struct is_non_proxy_reference<R, V>
 ************************************************/

template <typename Reference, typename Value>
struct is_non_proxy_reference {
    static constexpr bool value = std::is_convertible<
        typename std::remove_reference<Reference>::type const volatile *,
        Value const volatile *
    >::value;
};  // struct is_non_proxy_reference<R, V>

/************************************************
 * Declaration: struct iterator_facade_types<V, R>
 ************************************************/

template <typename Value, typename Reference>
struct iterator_facade_types {
    using value_type = typename std::remove_const<Value>::type;
    using pointer = typename std::conditional<
        iterator_writability_disabled<Value, Reference>::value,
        std::add_pointer<value_type const>,
        std::add_pointer<value_type>
    >::type;
};  // struct iterator_facade_types<V, R>

/************************************************
 * Declaration: class postfix_increment_proxy<I>
 ************************************************/

template <typename Iterator>
class postfix_increment_proxy {
 public:  // Public Type(s)
    using value_type = typename std::iterator_traits<Iterator>::value_type;

 public:  // Public Method(s)
    explicit postfix_increment_proxy(Iterator const &it)
        : val_(*it) { /* empty */ }

    value_type &operator*() const {
        return this->val_;
    }

 private:  // Private Property(ies)
    mutable value_type val_;
};  // class postfix_increment_proxy<I>

/************************************************
 * Declaration: class writable_postfix_increment_proxy<I>
 ************************************************/

template <typename Iterator>
class writable_postfix_increment_proxy {
 public:  // Public Type(s)
    using value_type = typename std::iterator_traits<Iterator>::value_type;

 public:  // Public Method(s)
    explicit writable_postfix_increment_proxy(Iterator const &it)
        : val_(*it), it_(it) { /* empty */ }

    writable_postfix_increment_proxy const &operator*() const {
        return *this;
    }

    operator value_type &() const {
        return val_;
    }

    template <typename T>
    T const &operator=(T const &x) const {
        *(this->it_) = x;
        return x;
    }

    template <typename T>  // NOLINTNEXTLINE(runtime/references)
    T &operator=(T &x) const {
        *(this->it_) = x;
        return x;
    }

    operator Iterator const &() const {
        return it_;
    }

 private:  // Private Property(ies)
    mutable value_type val_;
    Iterator it_;
};  // class writable_postfix_increment_proxy<I>

/************************************************
 * Declaration: struct postfix_increment_result<I, V, R, C>
 ************************************************/

template <typename Iterator, typename Value, typename Reference, typename Category>
struct postfix_increment_result {
    using type = typename std::conditional<
        std::is_convertible<
            Reference,
            typename std::add_lvalue_reference<Value const>::type &&
        >::value
        &&
        !std::is_convertible<
            Category,
            std::forward_iterator_tag
        >::value,

        typename std::conditional<
            is_non_proxy_reference<Reference, Value>::value,
            postfix_increment_proxy<Iterator>,
            writable_postfix_increment_proxy<Iterator>
        >::type,

        Iterator
    >::type;
};  // struct postfix_increment_result<I, V, R, C>

/************************************************
 * Declaration: struct operator_arrow_dispatch<R, P>
 ************************************************/

template <typename Reference, typename Pointer>
struct operator_arrow_dispatch {
    struct proxy {
        explicit proxy(Reference const &x)
            : ref_(x) { /* empty */ }

        Reference* operator->() { return std::addressof(ref_); }
        operator Reference*()   { return std::addressof(ref_); }

        Reference ref_;
    };  // struct operator_arrow_dispatch<R, P>::proxy

    using result_type = proxy;
    static result_type apply(Reference const &x) {
        return result_type(x);
    }
};  // struct operator_arrow_dispatch<R, P>

template <typename T, typename Pointer>
struct operator_arrow_dispatch<T &, Pointer> {
    using result_type = Pointer;
    // NOLINTNEXTLINE(runtime/references)
    static result_type apply(T &x) {
        return std::addressof(x);
    }
};  // struct operator_arrow_dispatch<T &, P>

/************************************************
 * Declaration: class operator_brackets_proxy<I>
 ************************************************/

template <typename Iterator>
class operator_brackets_proxy {
 public:  // Public Type(s)
    using value_type = typename Iterator::value_type;
    using reference = typename Iterator::reference;

 public:  // Public Method(s)
    explicit operator_brackets_proxy(Iterator const &it)
        : it_(it) { /* empty */ }

    operator reference() const {
        return *it_;
    }

    operator_brackets_proxy &operator=(value_type const &val) {
        *it_ = val;
        return *this;
    }

 private:  // Private Property(ies)
    Iterator it_;
};  // class operator_brackets_proxy<I>

/************************************************
 * Declaration: class operator_brackets_dispatch<I, V, R>
 ************************************************/

template <typename Iterator, typename Value, typename Reference, typename Enabled = void>
struct operator_brackets_dispatch {
    using result_type = operator_brackets_proxy<Iterator>;
    static result_type apply(Iterator const &it) {
        return result_type(it);
    }
};  // struct operator_brackets_dispatch<I, V, R, E>

template <typename Iterator, typename Value, typename Reference>
struct operator_brackets_dispatch<
    Iterator, Value, Reference,
    typename std::enable_if<
        iterator_writability_disabled<Value, Reference>::value
            && std::is_pod<Value>::value
    >::type
> {
    using result_type = Value;
    static result_type apply(Iterator const &it) {
        return *it;
    }
};  // struct operator_brackets_dispatch<I, V, R>

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_ITERATOR_FACADE_HELPERS_HPP_
