// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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

}    // namespace maral

#endif    // MARAL_HAS_POLICY_HPP

