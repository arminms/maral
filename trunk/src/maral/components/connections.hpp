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

#include <unordered_set>
#include <unordered_map>

//#include <boost/range/algorithm/remove.hpp>
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

template <class T = void>
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
    void add_bond(T* bnd, T* at1, T* at2)
    {
        BOOST_ASSERT_MSG(
               bnd != nullptr
            || at1 != nullptr
            || at2 != nullptr, "null pointer!");
        if (have_connection(at1, at2)) return;
        connection_table_.emplace(bnd, std::unordered_set<T*>(2));
        connection_table_[bnd].insert(at1);
        connection_table_[bnd].insert(at2);
        connection_table_.emplace(at1, std::unordered_set<T*>(4));
        connection_table_[at1].insert(bnd);
        connection_table_.emplace(at2, std::unordered_set<T*>(4));
        connection_table_[at2].insert(bnd);
    }

    void remove_bond(T* bnd)
    {
        BOOST_ASSERT_MSG(bnd, "null pointer!");
        for (auto atm : connection_table_[bnd])
            connection_table_[atm].erase(bnd);
        connection_table_.erase(bnd);
    }

    void remove_atom(T* atm)
    {
        BOOST_ASSERT_MSG(atm, "null pointer!");
        for (auto bnd : connection_table_[atm])
        {
            for (auto nbr : connection_table_[bnd])
                if (nbr != atm)
                {
                    connection_table_[nbr].erase(bnd);
                    connection_table_.erase(bnd);
                    atm->common_ancestor(nbr)->remove(bnd);
                    break;
                }
        }
        connection_table_.erase(atm);
    }

    bool have_connection(T* at1, T* at2) const
    {
        BOOST_ASSERT_MSG(
               at1 != nullptr
            || at2 != nullptr, "null pointer!");
        for (auto bnd : connection_table_[at1])
            for (auto atm : connection_table_[bnd])
                if (atm == at2)
                    return true;
        return false;
    }

    T* bond_1st_atom(T* bnd) const
    {
        BOOST_ASSERT_MSG(bnd, "null pointer!");
        return *(connection_table_[bnd].begin());
    }

    T* bond_2nd_atom(T* bnd) const
    {
        BOOST_ASSERT_MSG(bnd, "null pointer!");
        return *(++connection_table_[bnd].begin());
    }
//@}

// Implementation
private:
    static std::unordered_map<T*, std::unordered_set<T*>>
        connection_table_;
};

template <class T>
    std::unordered_map<T*, std::unordered_set<T*>>
        connections_component<T>::connection_table_;

template <typename T = void>
using connections = connections_component<T>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_CONNECTIONS_HPP

