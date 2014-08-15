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
// Filename:
//    inserters.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation of all stream inserters for \b Maral.
//------------------------------------------------------------------------------

/// \ingroup Output
/// \name Output Stream Operators
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out the stream to write to.
/// \param p the node type to output.
/// \remarks
/// Outputs a string representation of the given node to the
/// given output stream.

inline std::ostream& operator<< (
    std::ostream& out,
    const hierarchical* node)
{
    BOOST_ASSERT_MSG(node, "null pointer!");
    node->print(out);
    return out;
}

//template
//<
//    typename    Model
//,   typename    PositionType
//,   typename... Policies
//>
//inline std::ostream& operator<< (
//    std::ostream& out,
//    const atom_h_node<Model, PositionType, Policies...>* atm)
//{
//    BOOST_ASSERT_MSG(atm, "null pointer!");
//    auto parent = atm->parent();
//    std::string trail = (parent->children()->back() == atm)
//                      ? "---\\"
//                      : "---+";
//    while (parent)
//    {
//        auto prev_parent = parent;
//        parent = parent->parent();
//        if (parent)
//            trail += (parent->children()->back() == prev_parent)
//                   ? "    "
//                   : "   |";
//    }
//    boost::reverse(trail);
//    out << trail
//        << std::setw(5) << atm->ordinal() << ". "
//        << std::setw(4) << atm->name() << ' '
//        << mtl::horizontal
//        << atm->get_center();
//    return out;
//}
//
//template
//<
//    typename    Model,
//    typename... Policies
//>
//inline std::ostream& operator<< (
//    std::ostream& out,
//    const molecule_h_node<Model, Policies...>* mol)
//{
//    BOOST_ASSERT_MSG(mol, "null pointer!");
//    auto parent = mol->parent();
//    std::string trail = (parent->children()->back() == mol)
//                      ? "---\\"
//                      : "---+";
//    while (parent)
//    {
//        auto prev_parent = parent;
//        parent = parent->parent();
//        if (parent)
//            trail += (parent->children()->back() == prev_parent)
//                   ? "    "
//                   : "   |";
//    }
//    boost::reverse(trail);
//    out << trail
//        << std::setw(4) << mol->ordinal() << ". "
//        << mol->name();
//    return out;
//}

/// @}

