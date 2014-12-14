// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_ORDERED_HPP
#define MARAL_POLICIES_ORDERED_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning serial numbers to nodes.
///
/// \param T Type of the value (e.g. unsigend, int, ...).
/// \remarks
/// \b ordered is a structural policy class that allows assigning a serial
/// number to a node, so it can be accessed or changed later.

template <typename T>
    class ordered
{
public:
/// \name Construction
//@{
    ordered(T ordinal = T(1))
    : ordinal_(ordinal)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_integral<T>::value == true,
            "only integral types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T ordinal() const
    {   return ordinal_;    }

    void ordinal(T ordinal)
    {   ordinal_ = ordinal; }
//@}

// Implementation
private:
    T ordinal_;
};

}   // namespace policy

GENERATE_HAS_POLICY(ordered)    // creates has_policy_ordered

}    // namespace maral

#endif    // MARAL_POLICIES_ORDERED_HPP
