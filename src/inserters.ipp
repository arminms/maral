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
//    policies::named<std::string>* name =
//        dynamic_cast<policies::named<std::string>*>(node);
//    policies::ordered* numbered = dynamic_cast<policies::ordered*>(node);
//    if (name && numbered)
//        out << name->name() << ", " << numbered->ordinal();
//    else if (name)
//        out << name->name();
//    else if (numbered)
//        out << numbered->ordinal();
//    else
//        out << node;
    node->print(out);
    return out;
}

template
<
    typename    Model,
    typename... Policies
>
inline std::ostream& operator<< (
    std::ostream& out,
    const atom_h_node<Model, Policies...>* atm)
{
    BOOST_ASSERT_MSG(atm, "null pointer!");
    out << atm->name() << ", " << atm->ordinal();
    return out;
}

template
<
    typename    Model,
    typename... Policies
>
inline std::ostream& operator<< (
    std::ostream& out,
    const molecule_h_node<Model, Policies...>* mol)
{
    BOOST_ASSERT_MSG(mol, "null pointer!");
    out << mol->name() << ", " << mol->ordinal();
    return out;
}

/// @}

