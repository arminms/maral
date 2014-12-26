// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_HAS_POLICY_HPP
#define MARAL_HAS_POLICY_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

#if BOOST_WORKAROUND(__clang_major__, BOOST_TESTED_AT(3))

#define GENERATE_HAS_POLICY(policy)                                            \
                                                                               \
template < class T >                                                           \
class HasPolicy_##policy                                                       \
{                                                                              \
private:                                                                       \
    template<typename U, U> struct Check;                                      \
    using Yes = char[2];                                                       \
    using  No = char[1];                                                       \
                                                                               \
    struct Fallback { int policy; };                                           \
    struct Derived : T, Fallback { };                                          \
                                                                               \
    template < class U >                                                       \
    static No& test (Check<int Fallback::*, &U::policy> *);                    \
    template < typename U >                                                    \
    static Yes& test ( U* );                                                   \
                                                                               \
public:                                                                        \
    BOOST_STATIC_CONSTEXPR bool RESULT =                                       \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
};                                                                             \
                                                                               \
template < class T >                                                           \
struct has_policy_##policy                                                     \
: public std::integral_constant<bool, HasPolicy_##policy<T>::RESULT>           \
{ };                                                                           \

#else

#define GENERATE_HAS_POLICY(policy)                                            \
                                                                               \
template < class T >                                                           \
class HasPolicy_##policy                                                       \
{                                                                              \
private:                                                                       \
    using Yes = char[2];                                                       \
    using  No = char[1];                                                       \
                                                                               \
    struct Fallback { int policy; };                                           \
    struct Derived : T, Fallback { };                                          \
                                                                               \
    template < class U >                                                       \
    static No& test ( decltype(U::policy)* );                                  \
    template < typename U >                                                    \
    static Yes& test ( U* );                                                   \
                                                                               \
public:                                                                        \
    BOOST_STATIC_CONSTEXPR bool RESULT =                                       \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
};                                                                             \
                                                                               \
template < class T >                                                           \
struct has_policy_##policy                                                     \
: public std::integral_constant<bool, HasPolicy_##policy<T>::RESULT>           \
{ };                                                                           \

#endif  //BOOST_WORKAROUND

GENERATE_HAS_POLICY(b_factor)           // creates has_policy_b_factor
GENERATE_HAS_POLICY(chainid)            // creates has_policy_chainid
GENERATE_HAS_POLICY(coordinates)        // creates has_policy_coordinates
GENERATE_HAS_POLICY(formal_charge)      // creates has_policy_formal_charge
GENERATE_HAS_POLICY(icode)              // creates has_policy_icode
GENERATE_HAS_POLICY(linked_position)    // creates has_policy_linked_position
GENERATE_HAS_POLICY(named)              // creates has_policy_named
GENERATE_HAS_POLICY(occupancy)          // creates has_policy_occupancy
GENERATE_HAS_POLICY(ordered)            // creates has_policy_ordered
GENERATE_HAS_POLICY(partial_charge)     // creates has_policy_partial_charge
GENERATE_HAS_POLICY(position)           // creates has_policy_position

}    // namespace maral

#endif    // MARAL_HAS_POLICY_HPP

