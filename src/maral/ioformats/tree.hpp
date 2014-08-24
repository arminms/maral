////////////////////////////////////////////////////////////////////////////////
//
//                                  MARAL
//            (Molecular Architectural Record & Assembly Library)
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//------------------------------------------------------------------------------
/// \file maral/ioformats/tree.hpp
/// \brief Include file for the tree i/o format.
///
/// \b maral/ioformats/tree.hpp is the header file for the tree input/output
/// format.

#ifndef MARAL_IOFORMATS_TREE_HPP
#define MARAL_IOFORMATS_TREE_HPP

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <type_traits>

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
    class tree_format
:   public Base<Rt,Md,Mo,Sm,At>
{
public:
    tree_format()
    :   Base<Rt,Md,Mo,Sm,At>()
    {}

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt) const;
    //virtual void do_print_model(std::ostream& out, const Md* md) const;
    //virtual void do_print_mol(std::ostream& out, const Mo* mo) const;
    //virtual void do_print_submol(std::ostream& out, const Sm* sm) const;
    //virtual void do_print_atom(std::ostream& out, const At* at) const;

    void print_root_name(std::ostream& out, const Rt* rt, std::true_type) const;
    void print_root_name(std::ostream& out, const Rt* rt, std::false_type) const;
    void print_root_order(std::ostream& out, const Rt* rt, std::true_type) const;
    void print_root_order(std::ostream& out, const Rt* rt, std::false_type) const;
    void print_root_pos(std::ostream& out, const Rt* rt, std::true_type) const;
    void print_root_pos(std::ostream& out, const Rt* rt, std::false_type) const;
};

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

GENERATE_HAS_MEMBER(name)       // Creates 'has_member_name'
GENERATE_HAS_MEMBER(ordinal)    // Creates 'has_member_ordinal'
GENERATE_HAS_MEMBER(position)     // Creates 'has_member_position'

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/ioformats/tree.ipp>

}    // namespace maral

#endif // MARAL_IOFORMATS_TREE_HPP
