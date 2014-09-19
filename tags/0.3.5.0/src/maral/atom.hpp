// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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
    class  atom_node
:   public Policies...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class atom_node
    <
        data_model::hierarchical
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Policies...
{
private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<atom_node>::type::print_atom(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<atom_node>::type::scan_atom(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    PositionType
,   typename ...Policies
>
    class atom_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::position<PositionType>
    ,   Policies...
    >
:   public data_model::leaf_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::position<PositionType>
,   public Policies...
{
public:
/// \name Construction
//@{
    atom_node(
        const StringType& name = "ATOM"
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<atom_node>::type::print_atom(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<atom_node>::type::scan_atom(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename    PositionType
,   typename ...Policies
>
    class atom_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::ordered<OrdinalType>
    ,   policy::position<PositionType>
    ,   Policies...
    >
:   public data_model::leaf_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::ordered<OrdinalType>
,   public policy::position<PositionType>
,   public Policies...
{
public:
/// \name Construction
//@{
    atom_node(
        const StringType& name = "ATOM"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    ,   policy::position<PositionType>(pos)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   format_traits<atom_node>::type::print_atom(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<atom_node>::type::scan_atom(in, this);  }
};

}    // namespace maral

#endif    // MARAL_ATOM_HPP
