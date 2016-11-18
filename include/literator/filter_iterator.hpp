// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_FILTER_ITERATOR_HPP_
#define LITERATOR_FILTER_ITERATOR_HPP_

#include "internal/filter_iterator_base.hpp"

namespace literator {

/************************************************
 * Declaration: class filter_iterator<P, I>
 ************************************************/

template <typename Predicate, typename Iterator>
class filter_iterator : public internal::filter_iterator_base<Predicate, Iterator> {
    friend class iterator_core_access;

 private:  // Private Type(s)
    using super_t = typename internal::filter_iterator_base<Predicate, Iterator>;

 public:  // Public Methods(s)
    filter_iterator() = default;
    filter_iterator(Predicate f, Iterator it, Iterator end = Iterator())
        : super_t(it), pred_(f), end_(end) { satisfy_predicate(); }

 private:  // Private Method(s)
    void increment() {
        ++(this->base());
        satisfy_predicate();
    }

    void decrement() {
        while (!this->pred_(*--(this->base()))) {
            // do nothing
        }
    }

    void satisfy_predicate() {
        while (this->base() != end_ && !this->pred_(*(this->base()))) {
            ++(this->base());
        }
    }

 private:  // Private Properties(s)
    Predicate pred_;
    Iterator end_;
};  // class filter_iterator<P, I>

/************************************************
 * Declaration: Non-member Function(s)
 ************************************************/

template <typename Predicate, typename Iterator>
inline filter_iterator<Predicate, Iterator>
make_filter_iterator(Predicate f, Iterator x, Iterator end) {
    return filter_iterator<Predicate, Iterator>(f, x, end);
}

}  // namespace literator

#endif  // LITERATOR_FILTER_ITERATOR_HPP_
