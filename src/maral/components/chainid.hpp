// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_CHAINID_HPP
#define MARAL_COMPONENTS_CHAINID_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning chain id to nodes.
///
/// \param CharT Type of the character to be used as chain id (e.g. char,
/// char16_t, char32_t, wchar_t, ...).
/// \remarks
/// chainid is a structural component class that allows assigning a chain id to
/// a node (usually molecule node), so it can be accessed or changed later.

template <typename CharT = char>
    class chainid_component
{
public:
/// \name Construction
//@{
    chainid_component(CharT id = CharT(' '))
    :   id_(id)
    {
        static_assert(
            std::is_integral<CharT>::value == true,
            "Only integral types are allowed :(");
	}
//@}

/// \name Attributes
//@{
    CharT chain_id() const
    {   return id_;   }

    void chain_id(CharT id)
    {   id_ = id;   }
//@}

// Implementation
private:
    CharT id_;
};

template <typename CharT = char>
using chainid = chainid_component<CharT>;

}}   // maral::component

#endif    // MARAL_COMPONENTS_CHAINID_HPP
