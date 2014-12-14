// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_OCCUPANCY_HPP
#define MARAL_POLICIES_OCCUPANCY_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning occupancy to atoms.
///
/// \param T Type of the float to be used for the value (e.g. float, double,
/// ...).
/// \remarks
/// \b occupancy is a structural policy class that allows assigning an occupancy
/// to atom, so it can be accessed or changed later.

template <typename T>
    class occupancy
{
public:
/// \name Construction
//@{
    occupancy(T occ = T(1))
    : occupancy_(occ)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_floating_point<T>::value == true,
            "only float types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T get_occupancy() const
    {   return occupancy_;    }

    void set_occupancy(T occ)
    {   occupancy_ = occ; }
//@}

// Implementation
private:
    T occupancy_;
};

}   // namespace policy

GENERATE_HAS_POLICY(occupancy)    // creates has_policy_occupancy

}    // namespace maral

#endif    // MARAL_POLICIES_OCCUPANCY_HPP
