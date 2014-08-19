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

#ifndef MARAL_MTL_POINT_HPP
#include <maral/mtl/point.hpp>
#endif // MARAL_MTL_POINT_HPP

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
//public:
//    typedef data_model::hierarchical data_model_type;
//
///// \name Construction
////@{
//    root_node(
//        const typename policy_traits<Policies>::value_type&... args)
//    :   Policies<typename policy_traits<Policies>::value_type>...(args)
//    {}
////@}

    virtual void do_print(std::ostream& out) const
    {   out << "ROOT";  }
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
    ,   policies::named<StringType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policies::named<StringType>
,   public Policies...
{
public:
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;

/// \name Construction
//@{
    root_node(
        const StringType& name = "ROOT")
    :   policies::named<StringType>(name)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   out << policies::named<StringType>::name(); }
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
    ,   policies::named<StringType>
    ,   policies::ordered<OrdinalType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policies::named<StringType>
,   public policies::ordered<OrdinalType>
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
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        out << policies::ordered<OrdinalType>::ordinal() << ". "
            << policies::named<StringType>::name();
    }
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
    ,   policies::named<StringType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policies::named<StringType>
,   public policies::position<PositionType>
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
    :   policies::named<StringType>(name)
    ,   policies::position<PositionType>(pos)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        out << policies::named<StringType>::name()
            << mtl::horizontal
            << policies::position<PositionType>::get_center();
    }
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
    ,   policies::named<StringType>
    ,   policies::ordered<OrdinalType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public policies::named<StringType>
,   public policies::ordered<OrdinalType>
,   public policies::position<PositionType>
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
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    ,   policies::position<PositionType>(pos)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        out << policies::ordered<OrdinalType>::ordinal() << ". "
            << policies::named<StringType>::name()
            << mtl::horizontal
            << policies::position<PositionType>::get_center();
    }
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed only of policies::named<std::string>
///
/// Convenient type to define a root node with only a name.
/// \par Example:
/// \code auto rt = make_node<root_s>("root node"); \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::string>
> root_s;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed only of policies::named<std::wstring>
///
/// Convenient type to define a root node with only a name (wide version).
/// \par Example:
/// \code auto rt = make_node<root_w>("root node"); \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
> root_w;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::string> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a root node with name and serial number.
/// \par Example:
/// \code
/// auto rt1 = make_node<root_su>("root", 1);
/// auto rt2 = make_node<root_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
> root_su;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::wstring> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a root node with name and serial number (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<root_su>("root", 1);
/// auto rt2 = make_node<root_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
> root_wu;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::string> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a root node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<root_s3f>("root", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<root_s3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3f>
> root_s3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a root node with name and position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<root_w3f>("root", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<root_w3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3f>
> root_w3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::string> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a root node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<root_s3d>("root", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<root_s3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3d>
> root_s3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a root node with name and position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<root_w3d>("root", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<root_w3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3d>
> root_w3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a root node with name, serial number and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<root_su3f>("root", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<root_su3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> root_su3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a root node with name, serial number and position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<root_wu3f>("root", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<root_wu3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> root_wu3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a root node with name, serial number and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<root_su3d>("root", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<root_su3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> root_su3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief root node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a root node with name, serial number and position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<root_wu3d>("root", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<root_wu3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef root_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> root_wu3d;

}    // namespace maral

#endif    // MARAL_ROOT_HPP
