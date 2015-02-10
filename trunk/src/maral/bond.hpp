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
    ,   datamodel::hierarchical
    ,   Components...
    >
:   public datamodel::leaf_node<datamodel::hierarchical>
,   public Components...
{
public:
    typedef bond_host<AtomType, datamodel::hierarchical, Components...>
        self_type;
    typedef AtomType atom_type;
    typedef component::connections<hierarchical> connections_type;
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
        self_type::add_bond(this, at1, at2);
    }
//@}

/// \name Attributes
//@{
    AtomType* src()
    {
        static_assert(
            has_connections_component<self_type>::value,
            "bond_host needs component::connections to work :(");
        return (AtomType*)self_type::bond_1st_atom(this);
    }

    AtomType* dst()
    {   return (AtomType*)self_type::bond_2nd_atom(this);  }

    AtomType* neighbor(AtomType* atm)
    {   return (AtomType*)self_type::get_neighbor(this, atm);  }
//@}

// Implementation
    virtual ~bond_host()
    {   self_type::remove_bond(this);   }

private:
    virtual bool do_change_parent(
        datamodel::composite_node<datamodel::hierarchical>* new_parent)
    {
        if (new_parent == nullptr)
            self_type::remove_bond(this);
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
,   const entity<bond_host<AtomType, datamodel::hierarchical, Components...>>&
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
,   entity<bond_host<AtomType, datamodel::hierarchical, Components...>>& bond)
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
    if (!at1->is_connected_to(at2))
    {
        entity<BondType> bnd(new BondType(at1, at2));
        at1->common_ancestor(at2)->add(std::move(bnd));
    }
}

//template <class BondType, class AtomType, template <class> class AtomIterator>
//inline void make(
//    const AtomIterator<AtomType*>& itr1
//,   const AtomIterator<AtomType*>& itr2)
//{
//    BOOST_ASSERT_MSG(
//        itr1->parent() != nullptr
//    ||  itr2->parent() != nullptr
//    ,   "Parent required for adding bond!");
//    if (!itr1->is_connected_to(*itr2))
//    {
//        entity<BondType> bnd(new BondType(*itr1, *itr2));
//        (*itr1)->common_ancestor(*itr2)->add(std::move(bnd));
//    }
//}

}    // namespace maral

#endif    // MARAL_BOND_HPP
