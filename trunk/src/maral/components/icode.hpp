// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_ICODE_HPP
#define MARAL_COMPONENTS_ICODE_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning code for insertion of residues to
///  submolecule nodes.
///
/// \param CharT Type of the character to be used as iCode (e.g. char, char16_t,
/// char32_t, ...).
/// \remarks
/// icode is a structural component class that allows assigning a code for
/// insertion of residue (iCode) to a submolecule node, so it can be accessed or
/// changed later.

template <typename CharT = char>
    class icode_component
{
public:
/// \name Construction
//@{
    icode_component(CharT code = CharT(' '))
    :   icode_(code)
    {
        static_assert(
            std::is_integral<CharT>::value == true,
            "Only integral types are allowed :(");
	}
//@}

/// \name Attributes
//@{
    CharT icode() const
    {   return icode_;   }

    void icode(CharT code)
    {   icode_ = code;   }
//@}

// Implementation
private:
    CharT icode_;
};

template <typename CharT = char>
using icode = icode_component<CharT>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_ICODE_HPP
