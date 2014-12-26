// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_B_FACTOR_HPP
#define MARAL_POLICIES_B_FACTOR_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning B-factor to atoms.
///
/// \param T Type of the value (e.g. float, double, ...).
/// \remarks
/// \b b_factor is a structural policy class that allows assigning a B-factor
/// to atom, so it can be accessed or changed later. The B-factor, also know as
/// Debye–Waller factor (DWF) or temperature factor, is used in condensed matter
/// physics to describe the attenuation of x-ray scattering or coherent neutron
/// scattering caused by thermal motion.

template <typename T>
    class b_factor
{
public:
/// \name Construction
//@{
    b_factor(T bf = T(0))
    : dwf_(bf)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_floating_point<T>::value == true,
            "only float types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T get_b_factor() const
    {   return dwf_;    }

    void set_b_factor(T bf)
    {   dwf_ = bf; }
//@}

// Implementation
private:
    T dwf_;
};

}}   // namespace maral::policy

#endif    // MARAL_POLICIES_OCCUPANCY_HPP
