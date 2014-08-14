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
/// \brief Include file for \b atom nodes of different \b models.
///
/// \b atom.hpp is the include file that defines \b atom nodes of different \b
/// data \b models (e.g. atom_h_node, atom_r_node, atom_n_node, etc).

#ifndef MARAL_TRAITS_HPP
#define MARAL_TRAITS_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
// type_traits

template<typename T>
    struct type_traits
{
    typedef type_traits<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<sizeof(value_type),sizeof(self_type)> extent;
};

////////////////////////////////////////////////////////////////////////////////
// Partial Specializations

template<typename T>
    struct type_traits< mtl::point2<T> >
{
    typedef typename mtl::point2<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,2> extent;
};

template<typename T>
    struct type_traits< mtl::point3<T> >
{
    typedef typename mtl::point3<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,3> extent;
};

template<typename T>
    struct type_traits< mtl::vector2<T> >
{
    typedef typename mtl::vector2<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,2> extent;
};

template<typename T>
    struct type_traits< mtl::vector3<T> >
{
    typedef typename mtl::vector3<T> self_type;
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef std::ratio<1,3> extent;
};

//template<typename T>
//    struct type_traits< std::vector<T> >
//{
//    typedef typename std::vector<T> self_type;
//    typedef T value_type;
//    typedef const T& const_reference;
//    typedef T& reference;
//    typedef std::ratio<0,0> extent;
//};

}    // namespace maral

#endif    // MARAL_TRAITS_HPP
