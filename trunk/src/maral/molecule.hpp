// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_MOLECULE_HPP
#define MARAL_MOLECULE_HPP

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
    class  molecule_host
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class molecule_host
    <
        datamodel::hierarchical
    ,   Components...
    >
:   public datamodel::composite_node<datamodel::hierarchical>
,   public Components...
{
public:
    typedef molecule_host<datamodel::hierarchical, Components...> self_type;

/// \name Construction
//@{
    molecule_host()
    {}

    molecule_host(const boost::any& name)
    {
        static_assert(
            has_name_component<self_type>::value,
            "need component::name for setting a name :(");
        any_name(name, has_name_component<self_type>());
    }
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<molecule_host>::type::print_mol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<molecule_host>::type::scan_mol(in, this);  }

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
};

////////////////////////////////////////////////////////////////////////////////

template<typename ...Components>
std::ostream& operator<< (
    std::ostream& out
,   const entity<molecule_host<datamodel::hierarchical, Components...>>& mol)
{
    BOOST_ASSERT_MSG(mol.get() , "null molecule!");
    mol->print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

template<typename ...Components>
std::istream& operator>> (
    std::istream& in
,   entity<molecule_host<datamodel::hierarchical, Components...>>& mol)
{
    BOOST_ASSERT_MSG(mol.get() , "null molecule!");
    mol->scan(in);
    return in;
}

}    // namespace maral

#endif    // MARAL_MOLECULE_HPP
