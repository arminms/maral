// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_CONNECTIONS_HPP
#define MARAL_COMPONENTS_CONNECTIONS_HPP

#include <vector>
#include <unordered_map>

#include <boost/range/algorithm/remove.hpp>
//#include <boost/range/algorithm/find.hpp>

#ifndef MARAL_TRAITS_HPP
#include <maral/traits.hpp>
#endif // MARAL_TRAITS_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning position to nodes.
///
/// \param T Type of the point to be used for the position (e.g. mtl::point3f,
/// mtl::point2d, ...).
/// \remarks
/// \b position is a structural component class that allows assigning a position
/// to a node, so it can be accessed or changed later.

template <class AtomType = void>
    class connections_component
{
    //static_assert(
    //    pntvec_traits<T>::extent::den > 1,
    //    "Need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    connections_component()
    {}
//@}

/// \name Attributes
//@{
//@}

/// \name Operations
//@{
    void add_connection(AtomType* a1, AtomType* a2)
    {
        if (0 == connection_table_.count(a1))
            connection_table_[a1] = std::vector<AtomType*>();
        connection_table_[a1].push_back(a2);
        if (0 == connection_table_.count(a2))
            connection_table_[a2] = std::vector<AtomType*>();
        connection_table_[a2].push_back(a1);
    }

    void remove_connection(AtomType* a1, AtomType* a2)
    {
        auto search = connection_table_.find(a1);
        if (search != connection_table_.end())
            boost::remove(search->second, a2);
        else
            return;
        search = connection_table_.find(a2);
        if (search != connection_table_.end())
            boost::remove(search->second, a1);
    }

    bool have_connection(AtomType* a1, AtomType* a2) const
    {
        auto search = connection_table_.find(a1);
        if (search != connection_table_.end())
            //return (boost::find(search->second, a2) != search->second.end());
            return (std::find(search->second.begin(), search->second.end(), a2)
                !=  search->second.end());
        else
            return false;
    }
//@}

// Implementation
private:
    static std::unordered_map<AtomType*, std::vector<AtomType*>>
        connection_table_;
};

template <class AtomType>
    std::unordered_map<AtomType*, std::vector<AtomType*>>
        connections_component<AtomType>::connection_table_;

template <typename AtomType = void>
using connections = connections_component<AtomType>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_CONNECTIONS_HPP

