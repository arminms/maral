// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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

#ifndef MARAL_TRAITS_HPP
#include <maral/traits.hpp>
#endif // MARAL_TRAITS_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning chain id to nodes.
///
/// \param T Type of the character to be used as name (e.g. char, char16_t,
/// char32_t, ...).
/// \remarks
/// chainid is a structural policy class that allows assigning a chain id to a
/// node (usually molecule node), so it can be accessed or changed later.

template <typename T>
    class chainid
{
public:
/// \name Construction
//@{
    chainid(const T& id = T())
    :   id_(id)
    {}
//@}

/// \name Attributes
//@{
    T chain_id() const
    {   return id_;   }

    void chain_id(const T& id)
    {   id_ = id;   }
//@}

// Implementation
protected:
    T id_;
};

}}    // namespaces

#endif    // MARAL_POLICIES_CHAINID_HPP

