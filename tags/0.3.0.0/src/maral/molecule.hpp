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

#ifndef MARAL_MTL_POINT_HPP
#include <maral/mtl/point.hpp>
#endif // MARAL_MTL_POINT_HPP

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
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    StringType
,   typename ...Policies
>
    class molecule_node
    <
        data_model::hierarchical
    ,   policies::named<StringType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
,   public policies::named<StringType>
,   public Policies...
{
public:
    typedef data_model::hierarchical data_model_type;
    typedef StringType string_type;

/// \name Construction
//@{
    molecule_node(
        const StringType& name = "MOL")
    :   policies::named<StringType>(name)
    {}
//@}
private:
    virtual void do_print(std::ostream& out) const
    {
        using namespace policies;
        auto parent = data_model::composite_node<data_model_type>::parent();
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
            << this->name();
    }
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
    ,   policies::named<StringType>
    ,   policies::ordered<OrdinalType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
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
    molecule_node(
        const StringType& name = "MOL"
    ,   OrdinalType ordinal = 1)
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    {}
//@}
private:
    virtual void do_print(std::ostream& out) const
    {
        using namespace policies;
        auto parent = data_model::composite_node<data_model_type>::parent();
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
            << std::setw(2) << policies::ordered<OrdinalType>::ordinal() << ". "
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
    class molecule_node
    <
        data_model::hierarchical
    ,   policies::named<StringType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
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
    molecule_node(
        const StringType& name = "MOL"
    ,   const PositionType& pos = PositionType().zero())
    :   policies::named<StringType>(name)
    ,   policies::position<PositionType>(pos)
    {}
//@}
private:
    virtual void do_print(std::ostream& out) const
    {
        using namespace policies;
        auto parent = data_model::composite_node<data_model_type>::parent();
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
            << policies::named<StringType>::name() << ' '
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
    class molecule_node
    <
        data_model::hierarchical
    ,   policies::named<StringType>
    ,   policies::ordered<OrdinalType>
    ,   policies::position<PositionType>
    ,   Policies...
    >
:   public data_model::composite_node<data_model::hierarchical>
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
    molecule_node(
        const StringType& name = "MOL"
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
        auto parent = data_model::composite_node<data_model_type>::parent();
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
            << std::setw(2) << policies::ordered<OrdinalType>::ordinal() << ". "
            << policies::named<StringType>::name() << ' '
            << mtl::horizontal
            << policies::position<PositionType>::get_center();
    }
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed only of policies::named<std::string>
///
/// Convenient type to define a molecule node with only a name.
/// \par Example:
/// \code auto rt = make_node<molecule_s>("molecule node"); \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
> molecule_s;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed only of policies::named<std::wstring>
///
/// Convenient type to define a molecule node with only a name (wide version).
/// \par Example:
/// \code auto rt = make_node<molecule_w>("molecule node"); \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
> molecule_w;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::string> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a molecule node with name and serial number.
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_su>("MOL", 1);
/// auto rt2 = make_node<molecule_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
> molecule_su;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::wstring> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a molecule node with name and serial number (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_su>("MOL", 1);
/// auto rt2 = make_node<molecule_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
> molecule_wu;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::string> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a molecule node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_s3f>("MOL", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<molecule_s3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3f>
> molecule_s3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a molecule node with name and position (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_w3f>("MOL", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<molecule_w3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3f>
> molecule_w3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::string> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a molecule node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_s3d>("MOL", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<molecule_s3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3d>
> molecule_s3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a molecule node with name and position (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_w3d>("MOL", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<molecule_w3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3d>
> molecule_w3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a molecule node with name, serial number and
/// position.
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_su3f>("MOL", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<molecule_su3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> molecule_su3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a molecule node with name, serial number and
/// position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_wu3f>("MOL", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<molecule_wu3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> molecule_wu3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a molecule node with name, serial number and
/// position.
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_su3d>("MOL", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<molecule_su3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> molecule_su3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief molecule node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a molecule node with name, serial number and
/// position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<molecule_wu3d>("MOL", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<molecule_wu3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef molecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> molecule_wu3d;

}    // namespace maral

#endif    // MARAL_MOLECULE_HPP
