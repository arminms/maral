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
/// \file maral/atom.hpp
/// \brief Include file for \b atom nodes.
///
/// \b maral/atom.hpp is the include file that defines \b atom node.

#ifndef MARAL_ATOM_HPP
#define MARAL_ATOM_HPP

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
{};

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
    ,   policies::named<StringType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public data_model::leaf_node<data_model::hierarchical>
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
    atom_node(
        const StringType& name = "ATOM"
    ,   const PositionType& pos = PositionType().zero())
    :   policies::named<StringType>(name)
    ,   policies::position<PositionType>(pos)
    {}
//@}
private:
    virtual void do_print(std::ostream& out) const
    {
        using namespace policies;
        auto parent = data_model::leaf_node<data_model_type>::parent();
        std::string trail = (parent->children()->back() == this)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                       ? "    "
                       : "   |";
        }
        boost::reverse(trail);
        out << trail
            << std::setw(4) << policies::named<StringType>::name() << ' '
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
    class atom_node
    <
        data_model::hierarchical
    ,   policies::named<StringType>
    ,   policies::ordered<OrdinalType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public data_model::leaf_node<data_model::hierarchical>
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
    atom_node(
        const StringType& name = "ATOM"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    ,   policies::position<PositionType>(pos)
    {}
//@}
private:
    virtual void do_print(std::ostream& out) const
    {
        using namespace policies;
        auto parent = data_model::leaf_node<data_model_type>::parent();
        std::string trail = (parent->children()->back() == this)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                       ? "    "
                       : "   |";
        }
        boost::reverse(trail);
        out << trail
            << std::setw(5) << policies::ordered<OrdinalType>::ordinal() << ". "
            << std::setw(4) << policies::named<StringType>::name() << ' '
            << mtl::horizontal
            << policies::position<PositionType>::get_center();
    }
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::string> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a atom node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_s3f>("ATOM", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<atom_s3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3f>
> atom_s3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a atom node with name and position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_w3f>("ATOM", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<atom_w3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3f>
> atom_w3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::string> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a atom node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_s3d>("ATOM", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<atom_s3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3d>
> atom_s3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a atom node with name and position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_w3d>("ATOM", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<atom_w3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3d>
> atom_w3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a atom node with name, serial number and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_su3f>("ATOM", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<atom_su3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> atom_su3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a atom node with name, serial number and position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_wu3f>("ATOM", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<atom_wu3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> atom_wu3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a atom node with name, serial number and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_su3d>("ATOM", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<atom_su3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> atom_su3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief atom node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a atom node with name, serial number and position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<atom_wu3d>("ATOM", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<atom_wu3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef atom_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> atom_wu3d;

}    // namespace maral

#endif    // MARAL_ATOM_HPP
