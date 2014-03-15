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
/// \file molecule.hpp
/// \brief Include file for \b molecule nodes of different \b models.
///
/// \b molecule.hpp is the include file that defines \b molecule nodes of
/// different \b data \b models (e.g. molecule_h_node, molecule_r_node,
/// molecule_n_node, etc).

#ifndef MARAL_MOLECULE_HPP_INCLUDED_
#define MARAL_MOLECULE_HPP_INCLUDED_

namespace maral {

template
<
    typename    Model,
    typename... Policies
>
    class molecule_h_node
:   public model::composite_node<Model>
,   public policies::named<std::string>
,   public policies::ordered<unsigned>
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_h_node(
        //Policies&&... policies,
        const std::string& name,
        unsigned ordinal = 1)
    //:   Policies(policies)...
    :   named(name)
    ,   ordered(ordinal)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {   out << name() << ", " << ordinal(); }
};

}    // namespace maral

#endif    // MARAL_MOLECULE_HPP_INCLUDED_
