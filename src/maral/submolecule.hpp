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
/// \file maral/submolecule.hpp
/// \brief Include file for \b submolecule node.
///
/// \b maral/submolecule.hpp is the include file that defines \b submolecule
/// node.

#ifndef MARAL_SUBMOLECULE_HPP
#define MARAL_SUBMOLECULE_HPP

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
    submolecule_node(
        const StringType& name = "SUBMOL")
    :   policies::named<StringType>(name)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }
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
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   OrdinalType ordinal = 1)
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }
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
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   const PositionType& pos = PositionType().zero())
    :   policies::named<StringType>(name)
    ,   policies::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }
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
    submolecule_node(
        const StringType& name = "SUBMOL"
    ,   OrdinalType ordinal = 1
    ,   const PositionType& pos = PositionType().zero())
    :   policies::named<StringType>(name)
    ,   policies::ordered<OrdinalType>(ordinal)
    ,   policies::position<PositionType>(pos)
    {}
//@}

private:
    virtual void do_print(std::ostream& out) const
    {   format_traits<submolecule_node>::type::print_submol(out, this);  }
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed only of policies::named<std::string>
///
/// Convenient type to define a submolecule node with only a name.
/// \par Example:
/// \code auto rt = make_node<submolecule_s>("submolecule node"); \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
> submolecule_s;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed only of policies::named<std::wstring>
///
/// Convenient type to define a submolecule node with only a name (wide
/// version).
/// \par Example:
/// \code auto rt = make_node<submolecule_w>("submolecule node"); \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
> submolecule_w;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::string> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a submolecule node with name and serial number.
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_su>("SUBMOL", 1);
/// auto rt2 = make_node<submolecule_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
> submolecule_su;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::wstring> and
/// policies::ordered<unsigned>
///
/// Convenient type to define a submolecule node with name and serial number
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_su>("SUBMOL", 1);
/// auto rt2 = make_node<submolecule_su>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
> submolecule_wu;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::string> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a submolecule node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_s3f>("SUBMOL", point3f(0f, 0f, 0f));
/// auto rt2 = make_node<submolecule_s3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3f>
> submolecule_s3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3f>
///
/// Convenient type to define a submolecule node with name and position (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_w3f>("SUBMOL", point3f(0f, 0f, 0f));
/// auto rt2 = make_node<submolecule_w3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3f>
> submolecule_w3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::string> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a submolecule node with name and position.
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_s3d>("SUBMOL", point3d(0d, 0d, 0d));
/// auto rt2 = make_node<submolecule_s3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::position<mtl::point3d>
> submolecule_s3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::wstring> and
/// policies::position<mtl::point3d>
///
/// Convenient type to define a submolecule node with name and position (wide
/// version).
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_w3d>("SUBMOL", point3d(0.0, 0.0, 0.0));
/// auto rt2 = make_node<submolecule_w3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::position<mtl::point3d>
> submolecule_w3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a submolecule node with name, serial number and
/// position.
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_su3f>("SUBMOL", 1, point3f(0f, 0f, 0f));
/// auto rt2 = make_node<submolecule_su3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> submolecule_su3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3f>
///
/// Convenient type to define a submolecule node with name, serial number and
/// position
/// (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_wu3f>("SUBMOL", 1, point3f(0f, 0f, 0f));
/// auto rt2 = make_node<submolecule_wu3f>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3f>
> submolecule_wu3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::string>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a submolecule node with name, serial number and
/// position.
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_su3d>("SUBMOL", 1, point3d(0, 0, 0));
/// auto rt2 = make_node<submolecule_su3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::string>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> submolecule_su3d;

////////////////////////////////////////////////////////////////////////////////
/// \brief submolecule node composed of policies::named<std::wstring>,
/// policies::ordered<unsigned> and policies::position<mtl::point3d>
///
/// Convenient type to define a submolecule node with name, serial number and
/// position (wide version).
/// \par Example:
/// \code
/// auto rt1 = make_node<submolecule_wu3d>("SUBMOL", 1, point3d(0, 0, 0));
/// auto rt2 = make_node<submolecule_wu3d>();
/// assert(rt1->name() == rt2->name();
/// assert(rt1->ordinal() == rt2->ordinal();
/// assert(rt1->center() == rt2->center();
/// \endcode

typedef submolecule_node
<
    data_model::hierarchical
,   policies::named<std::wstring>
,   policies::ordered<unsigned>
,   policies::position<mtl::point3d>
> submolecule_wu3d;

}    // namespace maral

#endif    // MARAL_SUBMOLECULE_HPP
