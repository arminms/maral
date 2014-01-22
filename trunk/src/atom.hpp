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

namespace maral
{

template
<
    typename    Model,
    typename... Policies
>
    class  atom_h_node
:   public model::leaf_node<Model>
,   public policies::has_name
,   public policies::ordered
,   public Policies...
{
public:
/// \name Construction
//@{
    atom_h_node(
        Policies&&... policies,
        const std::string& name,
        unsigned ordinal = 1)
    :   Policies(policies)...
    ,   has_name(name)
    ,   ordered(ordinal)
    {}
//@}
};

}    // namespace maral

#endif    // MARAL_ATOM_HPP_INCLUDED_
