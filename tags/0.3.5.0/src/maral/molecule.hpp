// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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

#ifndef MARAL_POLICIES_NAMED_HPP
#include <maral/policies/named.hpp>
#endif // MARAL_POLICIES_NAMED_HPP

#ifndef MARAL_POLICIES_ORDERED_HPP
#include <maral/policies/ordered.hpp>
#endif // MARAL_POLICIES_ORDERED_HPP

#ifndef MARAL_POLICIES_POSITION_HPP
#include <maral/policies/position.hpp>
#endif // MARAL_POLICIES_POSITION_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class  molecule_node
:   public Policies...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class molecule_node
    <
        data_model::hierarchical
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Policies...
{
private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<molecule_node>::type::print_mol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<molecule_node>::type::scan_mol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename ...Policies
>
    class molecule_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_node(
        const StringType& name = "MOL")
    :   policy::named<StringType>(name)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<molecule_node>::type::print_mol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<molecule_node>::type::scan_mol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename ...Policies
>
    class molecule_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::ordered<OrdinalType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::ordered<OrdinalType>
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_node(
        const StringType& name = "MOL"
    ,   OrdinalType ordinal = 1)
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<molecule_node>::type::print_mol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<molecule_node>::type::scan_mol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    PositionType
,   typename ...Policies
>
    class molecule_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::position<PositionType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::position<PositionType>
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_node(
        const StringType& name = "MOL"
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<molecule_node>::type::print_mol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<molecule_node>::type::scan_mol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename    PositionType
,   typename ...Policies
>
    class molecule_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::ordered<OrdinalType>
    ,   policy::position<PositionType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::ordered<OrdinalType>
,   public policy::position<PositionType>
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_node(
        const StringType& name = "MOL"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<molecule_node>::type::print_mol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<molecule_node>::type::scan_mol(in, this);  }
};

}    // namespace maral

#endif    // MARAL_MOLECULE_HPP