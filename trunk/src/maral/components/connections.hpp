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

#include <unordered_map>
#include <unordered_set>

#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>

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
public:
    typedef T* value_type;

/// \name Construction
//@{
    connections_component()
    {}
//@}

////////////////////////////////////////////////////////////////////////////////

    template <class BondType>
        class const_bond_iterator
    :   public boost::iterator_facade
    <
        const_bond_iterator<BondType>
    ,   BondType* const
    ,   boost::forward_traversal_tag
    ,   BondType*
    >
    {
    public:
        const_bond_iterator()
        {}

        explicit const_bond_iterator(
            const std::unordered_set<T*>& col
        ,   bool end = false)
        :   pos_(end ? col.end() : col.begin())
        {}

        BondType* operator->()
        {   return reinterpret_cast<BondType*>(*pos_);   }
        const BondType* operator->() const
        {   return reinterpret_cast<BondType*>(*pos_);   }

    private:
        friend class boost::iterator_core_access;

        void increment()
        {   ++pos_;   }

        bool equal(const_bond_iterator const& other) const
        {   return (this->pos_ == other.pos_);   }

        BondType* const dereference() const
        {   return reinterpret_cast<BondType*>(*pos_);   }

        typename std::unordered_set<T*>::const_iterator pos_;
    };

////////////////////////////////////////////////////////////////////////////////

    template <class AtomType>
        class const_neighbor_iterator
    :   public boost::iterator_facade
    <
        const_neighbor_iterator<AtomType>
    ,   AtomType* const
    ,   boost::forward_traversal_tag
    ,   AtomType*
    >
    {
    public:
        const_neighbor_iterator()
        {}

        explicit const_neighbor_iterator(
            const std::unordered_map<T*, std::unordered_set<T*>>* col
        ,   AtomType* atm
        ,   bool end = false)
        :   pos_(end ? col->at(atm).end() : col->at(atm).begin())
        ,   col_(col)
        ,   atm_(atm)
        {}

        AtomType* operator->()
        {   return reinterpret_cast<AtomType*>(*pos_);   }
        const AtomType* operator->() const
        {   return reinterpret_cast<AtomType*>(*pos_);   }

    private:
        friend class boost::iterator_core_access;

        void increment()
        {   ++pos_;   }

        bool equal(const_neighbor_iterator<AtomType> const& other) const
        {   return (this->pos_ == other.pos_);   }

        AtomType* const dereference() const
        {
            for (auto nbr : col_->at(*pos_))
                if (nbr != atm_)
                    return reinterpret_cast<AtomType*>(nbr);
            return nullptr;
        }

        typename std::unordered_set<T*>::const_iterator pos_;
        const std::unordered_map<T*, std::unordered_set<T*>>* col_;
        AtomType* atm_;
    };

////////////////////////////////////////////////////////////////////////////////

/// \name Operations
//@{
    void add_bond(T* bnd, T* at1, T* at2)
    {
        BOOST_ASSERT_MSG(
               bnd != nullptr
            || at1 != nullptr
            || at2 != nullptr, "null pointer!");
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

    T* get_neighbor(T* bnd, T* atm) const
    {
        BOOST_ASSERT_MSG(
               bnd != nullptr
            || atm != nullptr, "null pointer!");
        for (auto nbr : connection_table_[bnd])
            if (nbr != atm)
                return nbr;
        return nullptr;
    }

    template <class AtomType>
    boost::iterator_range<const_neighbor_iterator<AtomType>>
        get_neighbors(AtomType* atm) const
    {
        BOOST_ASSERT_MSG(atm, "null pointer!");
        return boost::make_iterator_range(
            const_neighbor_iterator<AtomType>(&connection_table_, atm)
        ,   const_neighbor_iterator<AtomType>(&connection_table_, atm, true));
    }

    template <class BondType>
    boost::iterator_range<const_bond_iterator<BondType>>
        get_bonds(T* atm) const
    {
        BOOST_ASSERT_MSG(atm, "null pointer!");
        return boost::make_iterator_range(
            const_bond_iterator<BondType>(connection_table_[atm])
        ,   const_bond_iterator<BondType>(connection_table_[atm], true));
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

////////////////////////////////////////////////////////////////////////////////
// Implementation

//#include <maral/components/connections.ipp>

}}    // maral::component

#endif    // MARAL_COMPONENTS_CONNECTIONS_HPP

