// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_BOND_HPP
#define MARAL_BOND_HPP

#ifndef MARAL_HIERARCHICAL_HPP
#include <maral/hierarchical.hpp>
#endif // MARAL_HIERARCHICAL_HPP

#ifndef MARAL_COMPONENT_HPP
#include <maral/component.hpp>
#endif // MARAL_COMPONENT_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename AtomType
,   typename ...Components
>
    class  bond_host
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename AtomType
,   typename ...Components
>
    class bond_host
    <
        AtomType
    ,   data_model::hierarchical
    ,   Components...
    >
:   public data_model::leaf_node<data_model::hierarchical>
,   public Components...
{
public:
    typedef bond_host<AtomType, data_model::hierarchical, Components...>
        self_type;

/// \name Construction
//@{
    bond_host(AtomType* at1, AtomType* at2)
    {
        static_assert(
            has_connections_component<AtomType>::value,
            "atom_host needs component::connections to work :(");
        static_assert(
            has_connections_component<self_type>::value,
            "bond_host needs component::connections to work :(");
        BOOST_ASSERT_MSG(at1, "null pointer!");
        BOOST_ASSERT_MSG(at2, "null pointer!");
        add_bond(this, at1, at2);
    }
//@}

/// \name Attributes
//@{
    AtomType* src()
    {
        static_assert(
            has_connections_component<self_type>::value,
            "bond_host needs component::connections to work :(");
        return (AtomType*)bond_1st_atom(this);
    }

    AtomType* dst()
    {   return (AtomType*)bond_2nd_atom(this);  }
//@}

// Implementation
private:
    virtual bool do_change_parent(
        data_model::composite_node<data_model::hierarchical>* new_parent)
    {
        if (new_parent == nullptr)
            remove_bond(this);
        parent_ = new_parent;
        return true;
    }

    virtual void do_print(std::ostream& out) const
    {}
    //{   format_traits<bond_host>::type::print_bond(out, this);  }

    virtual void do_scan(std::istream& in)
    {}
    //{   format_traits<bond_host>::type::scan_bond(in, this);  }

};

////////////////////////////////////////////////////////////////////////////////

template<typename AtomType, typename ...Components>
std::ostream& operator<< (
    std::ostream& out
,   const entity<bond_host<AtomType, data_model::hierarchical, Components...>>&
        bond)
{
    BOOST_ASSERT_MSG(bond.get() , "null bond!");
    bond->print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

template<typename AtomType, typename ...Components>
std::istream& operator>> (
    std::istream& in
,   entity<bond_host<AtomType, data_model::hierarchical, Components...>>& bond)
{
    BOOST_ASSERT_MSG(bond.get() , "null bond!");
    bond->scan(in);
    return in;
}

////////////////////////////////////////////////////////////////////////////////

template <class BondType, class AtomType>
inline void make(
    AtomType* at1
,   AtomType* at2)
{
    BOOST_ASSERT_MSG(
        at1->parent() != nullptr
    ||  at2->parent() != nullptr
    ,   "Parent required for adding bond!");
    entity<BondType> bnd(new BondType(at1, at2));
    at1->common_ancestor(at2)->add(std::move(bnd));
}

template <class BondType, class AtomType, template <class> class AtomIterator>
inline void make(
    AtomIterator<AtomType> itr1
,   AtomIterator<AtomType> itr2)
{
    BOOST_ASSERT_MSG(
        itr1->parent() != nullptr
    ||  itr2->parent() != nullptr
    ,   "Parent required for adding bond!");
    entity<BondType> bnd(new BondType(*itr1, *itr2));
    (*itr1)->common_ancestor(*itr2)->add(std::move(bnd));
}

}    // namespace maral

#endif    // MARAL_BOND_HPP
