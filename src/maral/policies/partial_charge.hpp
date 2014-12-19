// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_PARTIAL_CHARGE_HPP
#define MARAL_POLICIES_PARTIAL_CHARGE_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning partial charge to atoms.
///
/// \param T Type of the value (e.g. float, double, etc.).
/// \remarks
/// \b partial_charge is a structural policy class that allows assigning a
/// partial charge to an atom, so it can be accessed or changed later.

template <typename T>
    class partial_charge
{
public:
/// \name Construction
//@{
    partial_charge(T chg = T(0))
    : partial_charge_(chg)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_floating_point<T>::value == true,
            "only float types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T get_partial_charge() const
    {   return partial_charge_;    }

    void set_partial_charge(T chg)
    {   partial_charge_ = chg; }
//@}

// Implementation
private:
    T partial_charge_;
};

}   // namespace policy

GENERATE_HAS_POLICY(partial_charge)    // creates has_policy_partial_charge

}    // namespace maral

#endif    // MARAL_POLICIES_PARTIAL_CHARGE_HPP