////////////////////////////////////////////////////////////////////////////////
//
//                                  MARAL
//            (Molecular Architectural Record & Assembly Library)
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//------------------------------------------------------------------------------
/// \file maral/root.hpp
/// \brief Include file for \b root node.
///
/// \b maral/root.hpp is the include file that defines \b root node.

#ifndef MARAL_ROOT_HPP
#define MARAL_ROOT_HPP

#ifndef MARAL_HIERARCHICAL_HPP
#include <maral/hierarchical.hpp>
#endif // MARAL_HIERARCHICAL_HPP

#ifndef MARAL_POLICIES_HPP
#include <maral/policies.hpp>
#endif // MARAL_POLICIES_HPP

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;
    typedef OrdinalType ordinal_type;

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;
    typedef PositionType position_type;

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;
    typedef OrdinalType ordinal_type;
    typedef PositionType position_type;

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
