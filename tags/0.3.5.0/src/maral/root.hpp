// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ROOT_HPP
#define MARAL_ROOT_HPP

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
    class  root_node
:   public Policies...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class root_node
    <
        data_model::hierarchical
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public Policies...
{
    virtual void do_print(std::ostream& out) const
    {   format_traits<root_node>::type::print_root(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<root_node>::type::scan_root(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename StringType
,   typename ...Policies
>
    class root_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public Policies...
{
public:
/// \name Construction
//@{
    root_node(
        const StringType& name = "ROOT")
    :   policy::named<StringType>(name)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<root_node>::type::print_root(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<root_node>::type::scan_root(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename ...Policies
>
    class root_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::ordered<OrdinalType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::ordered<OrdinalType>
,   public Policies...
{
public:
/// \name Construction
//@{
    root_node(
        const StringType& name = "ROOT"
    ,   OrdinalType ordinal = 1)
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<root_node>::type::print_root(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<root_node>::type::scan_root(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    PositionType
,   typename ...Policies
>
    class root_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::position<PositionType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::position<PositionType>
,   public Policies...
{
public:
/// \name Construction
//@{
    root_node(
        const StringType& name = "ROOT"
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<root_node>::type::print_root(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<root_node>::type::scan_root(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename    PositionType
,   typename ...Policies
>
    class root_node
    <
        data_model::hierarchical
    ,   policy::named<StringType>
    ,   policy::ordered<OrdinalType>
    ,   policy::position<PositionType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policy::named<StringType>
,   public policy::ordered<OrdinalType>
,   public policy::position<PositionType>
,   public Policies...
{
public:
/// \name Construction
//@{
    root_node(
        const StringType& name = "ROOT"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<root_node>::type::print_root(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<root_node>::type::scan_root(in, this);  }
};

}    // namespace maral

#endif    // MARAL_ROOT_HPP
