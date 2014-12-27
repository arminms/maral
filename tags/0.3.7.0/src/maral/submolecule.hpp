// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$
/// node.

#ifndef MARAL_SUBMOLECULE_HPP
#define MARAL_SUBMOLECULE_HPP

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
    class  submolecule_host
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class submolecule_host
    <
        data_model::hierarchical
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Components...
{
public:
    typedef submolecule_host<data_model::hierarchical, Components...> self_type;

/// \name Construction
//@{
    submolecule_host()
    {   any_name(boost::any("SUBMOL"), has_name_component<self_type>()); }

    submolecule_host(const boost::any& name)
    {
        static_assert(
            has_name_component<self_type>::value,
            "need component::name for setting a name :(");
        any_name(name, has_name_component<self_type>());
    }

    submolecule_host(
        const boost::any& name
    ,   const boost::any& ordinal)
    {
        static_assert(
            has_name_component<self_type>::value,
            "need component::name for setting a name :(");
        any_name(name, has_name_component<self_type>());
        static_assert(
            has_order_component<self_type>::value,
            "need component::order for setting an ordinal :(");
        any_ordinal(ordinal, has_order_component<self_type>());
    }
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_host>::type::print_submol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<submolecule_host>::type::scan_submol(in, this);  }

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
    void any_ordinal(const boost::any& n, std::false_type)
    {}
};

}    // namespace maral

#endif    // MARAL_SUBMOLECULE_HPP
