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
/// \file maral/molecule.hpp
/// \brief Include file for \b molecule node.
///
/// \b maral/molecule.hpp is the include file that defines \b molecule node.

#ifndef MARAL_MOLECULE_HPP
#define MARAL_MOLECULE_HPP

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;
    typedef OrdinalType ordinal_type;

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;
    typedef PositionType position_type;

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
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;
    typedef OrdinalType ordinal_type;
    typedef PositionType position_type;

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
