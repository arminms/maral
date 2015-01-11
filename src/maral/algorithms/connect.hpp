// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ALGORITHMS_CONNECT_HPP
#define MARAL_ALGORITHMS_CONNECT_HPP

#include <vector>

#include <boost/range/distance.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/sort.hpp>

namespace maral {

template<class BondType, class AtomRange, typename T = float>
inline void connect(
    const AtomRange& rng
,   T tolerance = T(0.45))
{
    std::vector<typename AtomRange::value_type> atoms;
    atoms.reserve(boost::distance(rng));
    boost::copy(rng, back_inserter(atoms));
    connect<BondType>(atoms, tolerance);
}

template<class BondType, class AtomType, typename T = float>
inline void connect(
    std::vector<AtomType>& atoms
,   T tolerance = T(0.45))
{
    boost::sort(atoms,
        [](const AtomType i, const AtomType j)
        { return ((*i)[2] < (*j)[2]); });

    for (unsigned i = 0 ; i < atoms.size() ; ++i)
    {
        for (unsigned j = i+1 ; j < atoms.size() ; ++j)
        {
            T cutoff = atoms[i]->covalent_radius().value()
                     + atoms[j]->covalent_radius().value()
                     + tolerance;
            T z_diff = (*atoms[j])[2] - (*atoms[i])[2];
            if (z_diff > cutoff)
                break;
            if (mtl::distance(atoms[i]->center(), atoms[j]->center()) < cutoff)
                make<BondType>(atoms[i], atoms[j]);
        }
    }
}

}   // maral

#endif    // MARAL_ALGORITHMS_CONNECT_HPP
