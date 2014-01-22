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
//    output.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation for all output stream operators of
//    \b maral.
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
    hierarchical* node)
{
    BOOST_ASSERT_MSG(node, "null pointer!");
    policies::has_name* named = dynamic_cast<policies::has_name*>(node);
    policies::ordered* numbered = dynamic_cast<policies::ordered*>(node);
    if (named && numbered)
        out << named->name() << ", " << numbered->ordinal();
    else if (named)
        out << named->name();
    else if (numbered)
        out << numbered->ordinal();
    else
        out << node;
    return out;
}

template
<
    typename    Model,
    typename... Policies
>
std::ostream& operator<< (
    std::ostream& out,
    atom_h_node<Model, Policies...>* atm)
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
std::ostream& operator<< (
    std::ostream& out,
    molecule_h_node<Model, Policies...>* mol)
{
    BOOST_ASSERT_MSG(mol, "null pointer!");
    out << mol->name() << ", " << mol->ordinal();
    return out;
}

/// @}

