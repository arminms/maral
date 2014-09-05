// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_HAS_MEMBER_HPP
#define MARAL_HAS_MEMBER_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

#if BOOST_WORKAROUND(__clang_major__, BOOST_TESTED_AT(3))

#define GENERATE_HAS_MEMBER(member)                                            \
                                                                               \
template < class T >                                                           \
class HasMember_##member                                                       \
{                                                                              \
private:                                                                       \
    template<typename U, U> struct Check;                                      \
    using Yes = char[2];                                                       \
    using  No = char[1];                                                       \
                                                                               \
    struct Fallback { int member; };                                           \
    struct Derived : T, Fallback { };                                          \
                                                                               \
    template < class U >                                                       \
    static No& test (Check<int Fallback::*, &U::member> *);                    \
    template < typename U >                                                    \
    static Yes& test ( U* );                                                   \
                                                                               \
public:                                                                        \
    BOOST_STATIC_CONSTEXPR bool RESULT =                                       \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
};                                                                             \
                                                                               \
template < class T >                                                           \
struct has_member_##member                                                     \
: public std::integral_constant<bool, HasMember_##member<T>::RESULT>           \
{ };                                                                           \

#else

#define GENERATE_HAS_MEMBER(member)                                            \
                                                                               \
template < class T >                                                           \
class HasMember_##member                                                       \
{                                                                              \
private:                                                                       \
    using Yes = char[2];                                                       \
    using  No = char[1];                                                       \
                                                                               \
    struct Fallback { int member; };                                           \
    struct Derived : T, Fallback { };                                          \
                                                                               \
    template < class U >                                                       \
    static No& test ( decltype(U::member)* );                                  \
    template < typename U >                                                    \
    static Yes& test ( U* );                                                   \
                                                                               \
public:                                                                        \
    BOOST_STATIC_CONSTEXPR bool RESULT =                                       \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
};                                                                             \
                                                                               \
template < class T >                                                           \
struct has_member_##member                                                     \
: public std::integral_constant<bool, HasMember_##member<T>::RESULT>           \
{ };                                                                           \

#endif  //BOOST_WORKAROUND

////////////////////////////////////////////////////////////////////////////////
// Generation for different policies

GENERATE_HAS_MEMBER(name)       // Creates 'has_member_name'
GENERATE_HAS_MEMBER(ordinal)    // Creates 'has_member_ordinal'
GENERATE_HAS_MEMBER(position)   // Creates 'has_member_position'
GENERATE_HAS_MEMBER(chainid)   // Creates 'has_member_chainid'

}    // namespace maral

#endif    // MARAL_HAS_MEMBER_HPP

