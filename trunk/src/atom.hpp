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

#ifndef MARAL_ATOM_HPP
#define MARAL_ATOM_HPP

namespace maral {

template
<
    typename    Model
//,   typename    StringType
,   typename    PositionType
,   typename... Policies
>
    class  atom_h_node
:   public model::leaf_node<Model>
,   public policies::named<std::string>
,   public policies::ordered<unsigned>
,   public policies::position<PositionType>
,   public Policies...
{
//    static_assert(
//        std::is_same<policies::position<Position_Type>,Policies...>::value,
//        "position policy already used :(");

public:
/// \name Construction
//@{
    atom_h_node(
        //Policies&&... policies
//        pntvec_traits<Policies&&...>::const_reference vars
        const std::string& name = ""
    ,   unsigned ordinal = 1
    ,   const PositionType& pos = PositionType().zero() )
//    :   Policies(policies)...
//    :   Policies(vars)...
    :   named(name)
    ,   ordered(ordinal)
    ,   policies::position<PositionType>(pos)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        auto parent = model::leaf_node<Model>::parent();
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
            << std::setw(5) << ordinal() << ". "
            << std::setw(4) << name() << ' '
            << mtl::horizontal
            << policies::position<PositionType>::get_center();
    }
};

}    // namespace maral

#endif    // MARAL_ATOM_HPP
