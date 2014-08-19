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
/// \file maral/model.hpp
/// \brief Include file for \b model node.
///
/// \b maral/model.hpp is the include file that defines \b model node.

#ifndef MARAL_MODEL_HPP
#define MARAL_MODEL_HPP

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
    class  model_node
:   public Policies...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class model_node
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
    class model_node
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
    model_node(
        const StringType& name = "MODEL")
    :   policies::named<StringType>(name)
    {}
//@}

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
    class model_node
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
    model_node(
        const StringType& name = "MODEL"
    ,   OrdinalType ordinal = 1)
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    {}
//@}

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
    class model_node
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
    model_node(
        const StringType& name = "MODEL"
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
    class model_node
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
    model_node(
        const StringType& name = "MODEL"
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
/// \brief model node composed only of policies::named<std::string>
///
/// Convenient type to define a model node with only a name.
/// \par Example:
/// \code auto rt = make_node<model_s>("model node"); \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::string>
> model_s;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed only of policies::named<std::wstring>
///
/// Convenient type to define a model node with only a name (wide version).
/// \par Example:
/// \code auto rt = make_node<model_w>("model node"); \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
> model_w;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::string> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a model node with name and serial number.
/// \par Example:
/// \code
/// auto rt1 = make_node<model_su>("MODEL", 1);
/// auto rt2 = make_node<model_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
> model_su;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::wstring> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a model node with name and serial number (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<model_su>("MODEL", 1);
/// auto rt2 = make_node<model_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
> model_wu;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::string> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a model node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<model_s3f>("MODEL", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<model_s3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3f>
> model_s3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a model node with name and position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<model_w3f>("MODEL", point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<model_w3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3f>
> model_w3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::string> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a model node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<model_s3d>("MODEL", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<model_s3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3d>
> model_s3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a model node with name and position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<model_w3d>("MODEL", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<model_w3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3d>
> model_w3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a model node with name, serial number and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<model_su3f>("MODEL", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<model_su3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> model_su3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a model node with name, serial number and position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<model_wu3f>("MODEL", 1, point3f(0.0f, 0.0f, 0.0f));
/// auto rt2 = make_node<model_wu3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> model_wu3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a model node with name, serial number and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<model_su3d>("MODEL", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<model_su3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> model_su3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief model node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a model node with name, serial number and position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<model_wu3d>("MODEL", 1, point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<model_wu3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef model_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> model_wu3d;

}    // namespace maral

#endif    // MARAL_MODEL_HPP
