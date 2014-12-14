// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_TRAITS_HPP
#define MARAL_TRAITS_HPP

#include <ratio>

#ifndef MARAL_MTL_POINT_HPP
#include <maral/mtl/point.hpp>
#endif // MARAL_MTL_POINT_HPP

#ifndef MARAL_MTL_VECTOR_HPP
#include <maral/mtl/vector.hpp>
#endif // MARAL_MTL_VECTOR_HPP

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

////////////////////////////////////////////////////////////////////////////////
// format_traits

template<typename T>
    struct format_traits
{
    typedef typename T::format_type type;
};

}    // namespace maral

#endif    // MARAL_TRAITS_HPP
