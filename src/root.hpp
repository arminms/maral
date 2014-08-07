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

#ifndef MARAL_ROOT_HPP_INCLUDED_
#define MARAL_ROOT_HPP_INCLUDED_

namespace maral {

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

#endif    // MARAL_ROOT_HPP_INCLUDED_
