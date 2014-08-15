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
/// \file root.hpp
/// \brief Include file for \b root node of different \b models.
///
/// \b root.hpp is the include file that defines \b root nodes of different \b
/// data \b models (e.g. root_h_node, root_r_node, root_n_node, etc).

#ifndef MARAL_ROOT_HPP
#define MARAL_ROOT_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class  root_base
:   public Policies...
{
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class root_base
    <
        model::hierarchical
    ,   Policies...
    >
:   public model::root_node<model::hierarchical>
,   public Policies...   
{
//public:
//    typedef model::hierarchical model_type;
//
///// \name Construction
////@{
//    root_base(
//        const typename policy_traits<Policies>::value_type&... args)
//    :   Policies<typename policy_traits<Policies>::value_type>...(args)
//    {}
////@}
//
//    virtual void do_print(std::ostream& out) const
//    {}
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename StringType
,   typename ...Policies
>
    class root_base
    <
        model::hierarchical
    ,   policies::named<StringType>
    ,   Policies...
    >
:   public model::root_node<model::hierarchical>
,   public policies::named<StringType>
,   public Policies...
{
public:
    typedef model::hierarchical model_type;
    typedef StringType string_type;

/// \name Construction
//@{
    root_base(
        const StringType& name = "")
    :   policies::named<StringType>(name)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   out << policies::named<StringType>::name() << " (root)"; }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    OrdinalType
,   typename ...Policies
>
    class root_base
    <
        model::hierarchical
    ,   policies::named<StringType>
    ,   policies::ordered<OrdinalType>
    ,   Policies...
    >
:   public model::root_node<model::hierarchical>
,   public policies::named<StringType>
,   public policies::ordered<OrdinalType>
,   public Policies...
{
public:
    typedef model::hierarchical model_type;
    typedef StringType string_type;
    typedef OrdinalType ordinal_type;

    static_assert(
        std::is_floating_point<OrdinalType>::value == false,
        "only integral types are allowed :(");

/// \name Construction
//@{
    root_base(
        const StringType& name = ""
    ,   OrdinalType ordinal = 1)
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   out << policies::ordered<OrdinalType>::ordinal() << ". " << policies::named<StringType>::name() << " (root)"; }
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename    PositionType
,   typename ...Policies
>
    class root_base
    <
        model::hierarchical
    ,   policies::named<StringType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public model::root_node<model::hierarchical>
,   public policies::named<StringType>
,   public policies::position<PositionType>
,   public Policies...
{
public:
    typedef model::hierarchical model_type;
    typedef StringType string_type;
    typedef PositionType position_type;

/// \name Construction
//@{
    root_base(
        const StringType& name = ""
    ,   const PositionType& pos = PositionType().zero())
    :   policies::named<StringType>(name)
    ,   policies::position<PositionType>(pos)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        out << policies::named<StringType>::name() << " (root) "
            << mtl::horizontal
            << policies::position<PositionType>::get_center();
    }
};

//template
//<
//    typename ...Policies
//>
//    struct node_traits
//<
//    root_base<std::string, unsigned, Policies...>
//>
//{
//    typedef root_base<std::string, unsigned, Policies...> self_type;
//    typedef std::string string_type;
//    typedef unsigned ordinal_type;
//
//    typedef model::hierarchical model_type;
//    typedef StringType string_type;
//    typedef OrdinalType ordinal_type;
//
//};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    Model,
    typename    NameType,
    typename... Policies
>
    class  root_h_node
:   public model::root_node<Model>
,   public policies::named<NameType>
,   public Policies...
{
public:
/// \name Construction
//@{
    root_h_node(
        const NameType& name)
    :   policies::named<NameType>(name)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   out << policies::named<NameType>::name() << " (root)"; }
};

}    // namespace maral

#endif    // MARAL_ROOT_HPP
