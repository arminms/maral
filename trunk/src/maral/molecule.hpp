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

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class  molecule_node
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Components
>
    class molecule_node
    <
        data_model::hierarchical
    ,   Components...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public Components...
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
,   typename ...Components
>
    class molecule_node
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
    molecule_node(
        const StringType& name = "MOL")
    :   component::named<StringType>(name)
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
,   typename ...Components
>
    class molecule_node
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
    molecule_node(
        const StringType& name = "MOL"
    ,   OrdinalType ordinal = 1)
    :   component::named<StringType>(name)
    ,   component::ordered<OrdinalType>(ordinal)
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
,   typename ...Components
>
    class molecule_node
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
    molecule_node(
        const StringType& name = "MOL"
    ,   const PositionType& pos = PositionType().zero())
    :   component::named<StringType>(name)
    ,   component::position<PositionType>(pos)
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
,   typename ...Components
>
    class molecule_node
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
    molecule_node(
        const StringType& name = "MOL"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   component::named<StringType>(name)
    ,   component::ordered<OrdinalType>(ordinal)
    ,   component::position<PositionType>(pos)
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
