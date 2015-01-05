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
class Has_##component                                                          \
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
struct has_##component                                                         \
: public std::integral_constant<bool, Has_##component<T>::RESULT>              \
{ };                                                                           \

#else

#define GENERATE_HAS_COMPONENT(component)                                      \
                                                                               \
template < class T >                                                           \
class Has_##component                                                          \
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
struct has_##component                                                         \
: public std::integral_constant<bool, Has_##component<T>::RESULT>              \
{ };                                                                           \

#endif  //BOOST_WORKAROUND

GENERATE_HAS_COMPONENT(atomic_number_component)   // creates atomic_number_component
GENERATE_HAS_COMPONENT(b_factor_component)        // creates has_b_factor_component
GENERATE_HAS_COMPONENT(chainid_component)         // creates has_chainid_component
GENERATE_HAS_COMPONENT(coordinates_component)     // creates has_coordinates_component
GENERATE_HAS_COMPONENT(covalent_radius_component) // creates has_covalent_radius_component
GENERATE_HAS_COMPONENT(formal_charge_component)   // creates has_formal_charge_component
GENERATE_HAS_COMPONENT(icode_component)           // creates has_icode_component
GENERATE_HAS_COMPONENT(linked_position_component) // creates has_linked_position_component
GENERATE_HAS_COMPONENT(name_component)            // creates has_name_component
GENERATE_HAS_COMPONENT(occupancy_component)       // creates has_occupancy_component
GENERATE_HAS_COMPONENT(order_component)           // creates has_order_component
GENERATE_HAS_COMPONENT(partial_charge_component)  // creates has_partial_charge_component
GENERATE_HAS_COMPONENT(position_component)        // creates has_position_component

}    // namespace maral

#endif    // MARAL_COMPONENT_HPP

