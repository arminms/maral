// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ALGORITHMS_REMOVE_IF_HPP
#define MARAL_ALGORITHMS_REMOVE_IF_HPP

#include <list>

#include <boost/range/distance.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>

namespace maral {

template<class ForwardRange, class UnaryPredicate>
inline void remove_if(const ForwardRange& rng, UnaryPredicate pred = true)
{
    std::list<typename ForwardRange::value_type> remove_list;
    boost::copy(rng
    |   boost::adaptors::filtered(pred)
    ,   back_inserter(remove_list));

    // first eliminating redundant entries from the list
    auto pos = remove_list.begin();
    auto prev_item = pos;
    while (pos != remove_list.end())
    {
        if ((*pos)->has_ancestor(*prev_item))
            pos = remove_list.erase(pos);
        else
        {
            prev_item = pos;
            ++pos;
        }
    }
    // now actually removing the entties
    for (auto item : remove_list)
        item->parent()->remove(item);
}

}   // maral

#endif    // MARAL_ALGORITHMS_REMOVE_IF_HPP
