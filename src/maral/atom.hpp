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
        data_model::hierarchical
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Components...
{
public:
    typedef atom_host<data_model::hierarchical, Components...> self_type;

/// \name Construction
//@{
    atom_host()
    {   any_name(boost::any("ATOM"), has_name_component<self_type>()); }

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
            "need component::name for setting atom name :(");
        any_name(name, has_name_component<self_type>());
        static_assert(
            has_order_component<self_type>::value,
            "need component::order for setting atom ordinal :(");
        any_ordinal(ordinal, has_order_component<self_type>());
        static_assert(
            has_pos_or_lnk_pos<self_type>::value,
            "need component::position for setting atom center :(");
        any_position(pos, has_pos_or_lnk_pos<self_type>());
    }
//@}

private:
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
            BOOST_ASSERT_MSG(0, "need a string type as the 1st argument!");
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
            BOOST_ASSERT_MSG(0, "need an integer type as the 2nd argument!");
    }
    void any_ordinal(const boost::any& ordinal, std::false_type)
    {}

    void any_position(const boost::any& pos, std::true_type)
    {
        if (boost::any_cast<decltype(self_type::get_center())>(&pos))
            self_type::center() =
                boost::any_cast<decltype(self_type::get_center())>(pos);
        else
            BOOST_ASSERT_MSG(0, "need a positon type as the 3rd argument!");
    }
    void any_position(const boost::any& pos, std::false_type)
    {}

    template <class T>
    struct has_pos_or_lnk_pos
    :   public std::integral_constant
    <   bool,
        has_position_component<T>::value
    ||  has_linked_position_component<T>::value
    >
    {};
};

}    // namespace maral

#endif    // MARAL_ATOM_HPP
