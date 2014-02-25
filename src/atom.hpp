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
/// \file atom.hpp
/// \brief Include file for \b atom nodes of different \b models.
///
/// \b atom.hpp is the include file that defines \b atom nodes of different \b
/// data \b models (e.g. atom_h_node, atom_r_node, atom_n_node, etc).

#ifndef MARAL_ATOM_HPP_INCLUDED_
#define MARAL_ATOM_HPP_INCLUDED_

namespace maral {

template
<
    typename    Model
,   typename    Position_Type
,   typename... Policies
>
    class  atom_h_node
:   public model::leaf_node<Model>
,   public policies::named<std::string>
,   public policies::ordered<unsigned>
,   public policies::position<Position_Type>
,   public Policies...
{
//    static_assert(
//        std::is_same<policies::position<Position_Type>,Policies...>::value,
//        "position policy already used :(");

public:
/// \name Construction
//@{
    atom_h_node(
        Policies&&... policies
//        type_traits<Policies&&...>::const_reference vars
    ,   const std::string& name
    ,   unsigned ordinal = 1
    ,   const Position_Type& pos = Position_Type() )
    :   Policies(policies)...
//    :   Policies(vars)...
    ,   named(name)
    ,   ordered(ordinal)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   out << name() << ", " << ordinal(); }
};

}    // namespace maral

#endif    // MARAL_ATOM_HPP_INCLUDED_
