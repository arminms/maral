// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ATOM_HPP
#define MARAL_ATOM_HPP

#ifndef MARAL_HIERARCHICAL_HPP
#include <maral/hierarchical.hpp>
#endif // MARAL_HIERARCHICAL_HPP

#ifndef MARAL_COMPONENT_HPP
#include <maral/component.hpp>
#endif // MARAL_COMPONENT_HPP

#ifndef MARAL_COMPONENTS_CONNECTIONS_HPP
#include <maral/components/connections.hpp>
#endif // MARAL_COMPONENTS_CONNECTIONS_HPP

#ifndef MARAL_UNITS_HPP
#include <maral/units.hpp>
#endif // MARAL_UNITS_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class  atom_host
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class atom_host
    <
        datamodel::hierarchical
    ,   Components...
    >
:   public datamodel::leaf_node<datamodel::hierarchical>
,   public Components...
{
public:
    typedef atom_host<datamodel::hierarchical, Components...> self_type;

/// \name Construction
//@{
    atom_host()
    {}

    atom_host(const boost::any& name)
    {
        static_assert(
            has_name_component<self_type>::value,
            "need component::name for setting atom name :(");
        any_name(name, has_name_component<self_type>());
    }

    atom_host(
        const boost::any& name
    ,   const boost::any& ordinal)
    {
        static_assert(
            has_name_component<self_type>::value,
            "need component::name for setting atom name :(");
        any_name(name, has_name_component<self_type>());
        static_assert(
            has_order_component<self_type>::value,
            "need component::order for setting atom ordinal :(");
        any_ordinal(ordinal, has_order_component<self_type>());
    }

    atom_host(
        const boost::any& name
    ,   const boost::any& ordinal
    ,   const boost::any& pos)
    {
        static_assert(
            has_name_component<self_type>::value,
            "Need component::name for setting atom name :(");
        any_name(name, has_name_component<self_type>());
        static_assert(
            has_order_component<self_type>::value,
            "Need component::order for setting atom ordinal :(");
        any_ordinal(ordinal, has_order_component<self_type>());
        static_assert(
            has_position<self_type>::value,
            "Need component::position for setting atom center :(");
        any_position(pos, has_position<self_type>());
    }
//@}
    auto covalent_radius() -> decltype(units::angstroms(0.0f))
    {
        return units::angstroms(get_covalent_radius
            (has_covalent_radius<self_type>()));
    }

    bool is_connected_to(self_type* atm)
    {
        return has_connection(atm, has_connections_component<self_type>());
    }

    boost::iterator_range
        <component::connections<hierarchical>::const_neighbor_iterator<self_type>>
        neighbors()
    {   return self_type::get_neighbors(this);  }

    template <class BondType>
    boost::iterator_range
        <component::connections<hierarchical>::const_bond_iterator<BondType>>
        bonds()
    {   return self_type::template get_bonds<BondType>(this);  }

    virtual ~atom_host()
    {
        remove_atom_connections(nullptr,
            has_connections_component<self_type>());
    }

private:
    virtual bool do_change_parent(
        datamodel::composite_node<datamodel::hierarchical>* np)
    {
        remove_atom_connections(np, has_connections_component<self_type>());
        parent_ = np;
        return true;
    }

    virtual void do_print(std::ostream& out) const
    {   format_traits<atom_host>::type::print_atom(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<atom_host>::type::scan_atom(in, this);  }

    void any_name(const boost::any& name, std::true_type)
    {
        if (boost::any_cast<const char *>(&name))
            self_type::name(boost::any_cast<const char *>(name));
        else if (boost::any_cast<decltype(self_type::name())>(&name))
            self_type::name(boost::any_cast<decltype(self_type::name())>(name));
        else
            BOOST_ASSERT_MSG(0, "Need a string type as the 1st argument!");
    }
    void any_name(const boost::any& name, std::false_type)
    {}

    void any_ordinal(const boost::any& ordinal, std::true_type)
    {
        if (boost::any_cast<int>(&ordinal))
            self_type::ordinal(boost::any_cast<int>(ordinal));
        else if (boost::any_cast<decltype(self_type::ordinal())>(&ordinal))
            self_type::ordinal(
                boost::any_cast<decltype(self_type::ordinal())>(ordinal));
        else
            BOOST_ASSERT_MSG(0, "Need an integer type as the 2nd argument!");
    }
    void any_ordinal(const boost::any& ordinal, std::false_type)
    {}

    void any_position(const boost::any& pos, std::true_type)
    {
        if (boost::any_cast<decltype(self_type::get_center())>(&pos))
            self_type::center() =
                boost::any_cast<decltype(self_type::get_center())>(pos);
        else
            BOOST_ASSERT_MSG(0, "Need a positon type as the 3rd argument!");
    }
    void any_position(const boost::any& pos, std::false_type)
    {}

    float get_covalent_radius(std::true_type)
    {   return (float)self_type::z_2_covalent_radius(self_type::atomic_number()); }

    float get_covalent_radius(std::false_type)
    {
        static_assert(has_covalent_radius<self_type>::value,
            "Need both atomic_number and covalent_radius components :(");
        return 0;
    }

    bool has_connection(self_type* atm, std::true_type)
    {   return self_type::have_connection(this, atm);   }
    bool has_connection(self_type* atm, std::false_type)
    {   return false;   }

    void remove_atom_connections(
        datamodel::composite_node<datamodel::hierarchical>* np
    ,   std::true_type)
    {   if (np == nullptr) self_type::remove_atom(this);  }
    void remove_atom_connections(
        datamodel::composite_node<datamodel::hierarchical>* np
    ,   std::false_type)
    {}

    template <class T>
    struct has_position
    :   public std::integral_constant
    <   bool,
        has_position_component<T>::value
    ||  has_linked_position_component<T>::value
    >
    {};

    template <class T>
    struct has_covalent_radius
    :   public std::integral_constant
    <   bool,
        has_atomic_number_component<T>::value
    &&  has_covalent_radius_component<T>::value
    >
    {};
};

////////////////////////////////////////////////////////////////////////////////

template<typename ...Components>
std::ostream& operator<< (
    std::ostream& out
,   const entity<atom_host<datamodel::hierarchical, Components...>>& atm)
{
    BOOST_ASSERT_MSG(atm.get() , "null atom!");
    atm->print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

template<typename ...Components>
std::istream& operator>> (
    std::istream& in
,   entity<atom_host<datamodel::hierarchical, Components...>>& atm)
{
    BOOST_ASSERT_MSG(atm.get() , "null atom!");
    atm->scan(in);
    return in;
}

}    // namespace maral

#endif    // MARAL_ATOM_HPP
