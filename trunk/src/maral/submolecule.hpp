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
    typename ...Components
>
    class  submolecule_node
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class submolecule_node
    <
        data_model::hierarchical
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Components...
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
,   typename ...Components
>
    class submolecule_node
    <
        data_model::hierarchical
    ,   component::named<StringType>
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public component::named<StringType>
,   public Components...
{
public:
/// \name Construction
//@{
    submolecule_node(
        const StringType& name = "SUBMOL")
    :   component::named<StringType>(name)
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
,   typename ...Components
>
    class submolecule_node
    <
        data_model::hierarchical
    ,   component::named<StringType>
    ,   component::ordered<OrdinalType>
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public component::named<StringType>
,   public component::ordered<OrdinalType>
,   public Components...
{
public:
/// \name Construction
//@{
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   OrdinalType ordinal = 1)
    :   component::named<StringType>(name)
    ,   component::ordered<OrdinalType>(ordinal)
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
,   typename ...Components
>
    class submolecule_node
    <
        data_model::hierarchical
    ,   component::named<StringType>
    ,   component::position<PositionType>
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public component::named<StringType>
,   public component::position<PositionType>
,   public Components...
{
public:
/// \name Construction
//@{
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   const PositionType& pos = PositionType().zero())
    :   component::named<StringType>(name)
    ,   component::position<PositionType>(pos)
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
,   typename ...Components
>
    class submolecule_node
    <
        data_model::hierarchical
    ,   component::named<StringType>
    ,   component::ordered<OrdinalType>
    ,   component::position<PositionType>
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public component::named<StringType>
,   public component::ordered<OrdinalType>
,   public component::position<PositionType>
,   public Components...
{
public:
/// \name Construction
//@{
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   component::named<StringType>(name)
    ,   component::ordered<OrdinalType>(ordinal)
    ,   component::position<PositionType>(pos)
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
