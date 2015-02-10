// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ALGORITHMS_REMOVE_HPP
#define MARAL_ALGORITHMS_REMOVE_HPP

#include <list>

//#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/copy.hpp>

namespace maral {

template<class ForwardRange>
inline void remove(const ForwardRange& rng)
{
    //auto parent = *(rng.begin());
    //for (auto item : rng
    //    |   boost::adaptors::filtered(
    //    [&] (ForwardRange::value_type item)
    //    {
    //        bool r = !parent->is_ancestor_of(item);
    //        if (r) parent = item;
    //        return r;
    //    } ) )
    //    item->parent()->remove(item);

    std::list<typename ForwardRange::value_type> remove_list;
    boost::copy(rng
    ,   back_inserter(remove_list));

    // first eliminating redundant entries from the list
    auto pos = remove_list.begin();
    auto prev_item = pos;
    while (pos != remove_list.end())
    {
        if ((*prev_item)->is_ancestor_of(*pos))
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

//template<class ForwardRange, class UnaryPredicate>
//inline void remove(ForwardRange& rng, UnaryPredicate pred = true)
//{
//    std::list<ForwardRange::value_type> remove_list;
//    boost::copy(rng
//    |   boost::adaptors::filtered(pred)
//    ,   back_inserter(remove_list));
//    for (auto item : remove_list)
//        item->parent()->remove(item);
//}

}   // maral

#endif    // MARAL_ALGORITHMS_REMOVE_HPP
