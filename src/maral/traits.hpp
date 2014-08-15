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
/// \file traits.hpp
/// \brief Include file for type traits templates.
///
/// \b traits.hpp is the include file that defines templates for type traits.

#ifndef MARAL_TRAITS_HPP
#define MARAL_TRAITS_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
// pntvec_traits

template<typename T>
    struct pntvec_traits
{
    typedef pntvec_traits<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<sizeof(value_type),sizeof(self_type)> extent;
};

////////////////////////////////////////////////////////////////////////////////
// Partial Specializations

template<typename T>
    struct pntvec_traits< mtl::point2<T> >
{
    typedef typename mtl::point2<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,2> extent;
};

template<typename T>
    struct pntvec_traits< mtl::point3<T> >
{
    typedef typename mtl::point3<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,3> extent;
};

template<typename T>
    struct pntvec_traits< mtl::vector2<T> >
{
    typedef typename mtl::vector2<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,2> extent;
};

template<typename T>
    struct pntvec_traits< mtl::vector3<T> >
{
    typedef typename mtl::vector3<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,3> extent;
};

//template<typename T>
//    struct pntvec_traits< std::vector<T> >
//{
//    typedef typename std::vector<T> self_type;
//    typedef T value_type;
//    typedef const T& const_reference;
//    typedef T& reference;
//    typedef std::ratio<0,0> extent;
//};

////////////////////////////////////////////////////////////////////////////////
// node_traits

template<typename T>
    struct policy_traits
{
    typedef policy_traits<T> self_type;
    typedef T value_type;
};

////////////////////////////////////////////////////////////////////////////////
// node_traits

template<typename T>
    struct node_traits
{
    typedef node_traits<T> self_type;
    typedef T value_type;
};

}    // namespace maral

#endif    // MARAL_TRAITS_HPP
