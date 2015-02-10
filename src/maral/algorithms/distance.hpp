// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ALGORITHMS_DISTANCE_HPP
#define MARAL_ALGORITHMS_DISTANCE_HPP

#include <utility>

namespace maral {

template <class EntityType>
inline
typename pntvec_traits<decltype(
    std::declval<const EntityType>().get_center())>::value_type
distance(
    const EntityType* one
,   const EntityType* two)
{
    return distance(one->get_center(), two->get_center());
}

template <class ForwardIterator>
inline
typename pntvec_traits<decltype(
    std::declval<std::remove_pointer
    <typename ForwardIterator::value_type>::type>().
    get_center())>::value_type
distance(
    const ForwardIterator& one
,   const ForwardIterator& two)
{
    return distance(one->get_center(), two->get_center());
}

}   // maral

#endif    // MARAL_ALGORITHMS_DISTANCE_HPP
