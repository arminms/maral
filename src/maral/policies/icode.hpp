// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_ICODE_HPP
#define MARAL_POLICIES_ICODE_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning code for insertion of residues to
///  submolecule nodes.
///
/// \param T Type of the character to be used as iCode (e.g. char, char16_t,
/// char32_t, ...).
/// \remarks
/// icode is a structural policy class that allows assigning a code for
/// insertion of residue (iCode) to a submolecule node, so it can be accessed or
/// changed later.

template <typename T>
    class icode
{
public:
/// \name Construction
//@{
    icode(T code = T(' '))
    :   icode_(code)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_integral<T>::value == true,
            "only integral types are allowed :(");
	}
//@}

/// \name Attributes
//@{
    T get_icode() const
    {   return icode_;   }

    void set_icode(T code)
    {   icode_ = code;   }
//@}

// Implementation
private:
    T icode_;
};

}   // namespace policy

GENERATE_HAS_POLICY(icode)   // creates has_policy_icode

}    // namespace maral

#endif    // MARAL_POLICIES_ICODE_HPP
