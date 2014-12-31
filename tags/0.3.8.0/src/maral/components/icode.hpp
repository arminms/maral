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
/// \param T Type of the character to be used as iCode (e.g. char, char16_t,
/// char32_t, ...).
/// \remarks
/// icode is a structural component class that allows assigning a code for
/// insertion of residue (iCode) to a submolecule node, so it can be accessed or
/// changed later.

template <typename T>
    class icode_component
{
public:
/// \name Construction
//@{
    icode_component(T code = T(' '))
    :   icode_(code)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_integral<T>::value == true,
            "only integral types are allowed :(");
	}
//@}

/// \name Attributes
//@{
    T icode() const
    {   return icode_;   }

    void icode(T code)
    {   icode_ = code;   }
//@}

// Implementation
private:
    T icode_;
};

template <typename T>
using icode = icode_component<T>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_ICODE_HPP
