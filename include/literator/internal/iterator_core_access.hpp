// (c) Copyright David Abrahams 2002.
// (c) Copyright Jeremy Siek 2002.
// (c) Copyright Thomas Witt 2002.
// (c) Copyright Chi-En Wu 2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LITERATOR_INTERNAL_ITERATOR_CORE_ACCESS_HPP_
#define LITERATOR_INTERNAL_ITERATOR_CORE_ACCESS_HPP_

namespace literator {

namespace internal {

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

}  // namespace internal

}  // namespace literator

#endif  // LITERATOR_INTERNAL_ITERATOR_CORE_ACCESS_HPP_
