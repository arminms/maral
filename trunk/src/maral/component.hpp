// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENT_HPP
#define MARAL_COMPONENT_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

#if BOOST_WORKAROUND(__clang_major__, BOOST_TESTED_AT(3))

#define GENERATE_HAS_COMPONENT(component)                                      \
                                                                               \
template < class T >                                                           \
class HasComponent_##component                                                 \
{                                                                              \
private:                                                                       \
    template<typename U, U> struct Check;                                      \
    using Yes = char[2];                                                       \
    using  No = char[1];                                                       \
                                                                               \
    struct Fallback { int component; };                                        \
    struct Derived : T, Fallback { };                                          \
                                                                               \
    template < class U >                                                       \
    static No& test (Check<int Fallback::*, &U::component> *);                 \
    template < typename U >                                                    \
    static Yes& test ( U* );                                                   \
                                                                               \
public:                                                                        \
    BOOST_STATIC_CONSTEXPR bool RESULT =                                       \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
};                                                                             \
                                                                               \
template < class T >                                                           \
struct has_component_##component                                               \
: public std::integral_constant<bool, HasComponent_##component<T>::RESULT>     \
{ };                                                                           \

#else

#define GENERATE_HAS_COMPONENT(component)                                      \
                                                                               \
template < class T >                                                           \
class HasComponent_##component                                                 \
{                                                                              \
private:                                                                       \
    using Yes = char[2];                                                       \
    using  No = char[1];                                                       \
                                                                               \
    struct Fallback { int component; };                                        \
    struct Derived : T, Fallback { };                                          \
                                                                               \
    template < class U >                                                       \
    static No& test ( decltype(U::component)* );                               \
    template < typename U >                                                    \
    static Yes& test ( U* );                                                   \
                                                                               \
public:                                                                        \
    BOOST_STATIC_CONSTEXPR bool RESULT =                                       \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
};                                                                             \
                                                                               \
template < class T >                                                           \
struct has_component_##component                                               \
: public std::integral_constant<bool, HasComponent_##component<T>::RESULT>     \
{ };                                                                           \

#endif  //BOOST_WORKAROUND

GENERATE_HAS_COMPONENT(b_factor)           // creates has_component_b_factor
GENERATE_HAS_COMPONENT(chainid)            // creates has_component_chainid
GENERATE_HAS_COMPONENT(coordinates)        // creates has_component_coordinates
GENERATE_HAS_COMPONENT(formal_charge)      // creates has_component_formal_charge
GENERATE_HAS_COMPONENT(icode)              // creates has_component_icode
GENERATE_HAS_COMPONENT(linked_position)    // creates has_component_linked_position
GENERATE_HAS_COMPONENT(named)              // creates has_component_named
GENERATE_HAS_COMPONENT(occupancy)          // creates has_component_occupancy
GENERATE_HAS_COMPONENT(ordered)            // creates has_component_ordered
GENERATE_HAS_COMPONENT(partial_charge)     // creates has_component_partial_charge
GENERATE_HAS_COMPONENT(position)           // creates has_component_position

}    // namespace maral

#endif    // MARAL_COMPONENT_HPP

