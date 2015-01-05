// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_B_FACTOR_HPP
#define MARAL_COMPONENTS_B_FACTOR_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning B-factor to atoms.
///
/// \param T Type of the value (e.g. float, double, ...).
/// \remarks
/// \b b_factor is a structural component class that allows assigning a B-factor
/// to atom, so it can be accessed or changed later. The B-factor, also know as
/// Debye–Waller factor (DWF) or temperature factor, is used in condensed matter
/// physics to describe the attenuation of x-ray scattering or coherent neutron
/// scattering caused by thermal motion.

template <typename T = float>
    class b_factor_component
{
public:
/// \name Construction
//@{
    b_factor_component(T bf = T(0))
    : dwf_(bf)
    {
        static_assert(
            std::is_floating_point<T>::value == true,
            "Only float types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T b_factor() const
    {   return dwf_;    }

    void b_factor(T bf)
    {   dwf_ = bf; }
//@}

// Implementation
private:
    T dwf_;
};

template <typename T = float>
using b_factor = b_factor_component<T>;

}}   // namespace maral::component

#endif    // MARAL_COMPONENTS_OCCUPANCY_HPP
