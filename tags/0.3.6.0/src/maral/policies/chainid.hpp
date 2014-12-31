// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_CHAINID_HPP
#define MARAL_POLICIES_CHAINID_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning chain id to nodes.
///
/// \param T Type of the character to be used as chain id (e.g. char, char16_t,
/// char32_t, wchar_t, ...).
/// \remarks
/// chainid is a structural policy class that allows assigning a chain id to a
/// node (usually molecule node), so it can be accessed or changed later.

template <typename T>
    class chainid
{
public:
/// \name Construction
//@{
    chainid(T id = T(' '))
    :   id_(id)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_integral<T>::value == true,
            "only integral types are allowed :(");
	}
//@}

/// \name Attributes
//@{
    T get_chain_id() const
    {   return id_;   }

    void set_chain_id(T id)
    {   id_ = id;   }
//@}

// Implementation
private:
    T id_;
};

}   // namespace policy

GENERATE_HAS_POLICY(chainid)   // creates has_policy_chainid

}    // namespace maral

#endif    // MARAL_POLICIES_CHAINID_HPP