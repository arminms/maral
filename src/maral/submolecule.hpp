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

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class  submolecule_node
:   public Policies...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class submolecule_node
    <
        data_model::hierarchical
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Policies...
{
private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<submolecule_node>::type::scan_submol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename ...Policies
>
    class submolecule_node
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
    submolecule_node(
        const StringType& name = "SUBMOL")
    :   policy::named<StringType>(name)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<submolecule_node>::type::scan_submol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename ...Policies
>
    class submolecule_node
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
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   OrdinalType ordinal = 1)
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<submolecule_node>::type::scan_submol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    PositionType
,   typename ...Policies
>
    class submolecule_node
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
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<submolecule_node>::type::scan_submol(in, this);  }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename    PositionType
,   typename ...Policies
>
    class submolecule_node
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
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   policy::named<StringType>(name)
    ,   policy::ordered<OrdinalType>(ordinal)
    ,   policy::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<submolecule_node>::type::scan_submol(in, this);  }
};

}    // namespace maral

#endif    // MARAL_SUBMOLECULE_HPP
