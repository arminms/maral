// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ALGORITHMS_RMSD_HPP
#define MARAL_ALGORITHMS_RMSD_HPP

#include <vector>

//#include <boost/foreach.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/distance.hpp>

namespace maral {

template<class AtomRange>
inline typename pntvec_traits<decltype(
    std::declval<std::remove_pointer
    <typename AtomRange::value_type>::type>().get_center())>::value_type
rmsd(
    const AtomRange& rng1
,   const AtomRange& rng2)
{
    typedef typename pntvec_traits<decltype(
        std::declval<std::remove_pointer
        <typename AtomRange::value_type>::type>().get_center())>::value_type
        return_type;

    auto n = boost::distance(rng1);
    BOOST_ASSERT_MSG(n == boost::distance(rng2),
        "Size of two ranges must be equal!");

    return_type sum = return_type(0);

    //auto atm1 = *boost::begin(rng1);
    //auto atm2 = *boost::begin(rng2);
    //BOOST_FOREACH(boost::tie(atm1, atm2), boost::combine(rng1, rng2))
    //    sum += distance2(atm1->center(), atm2->center());

    for (auto tup : boost::combine(rng1, rng2))
    {
        typename AtomRange::value_type atm1, atm2;
        boost::tie(atm1, atm2) = tup;
        sum += distance2(atm1->center(), atm2->center());
    }

    return sqrt(sum/n);
}

}   // maral

#endif    // MARAL_ALGORITHMS_RMSD_HPP
