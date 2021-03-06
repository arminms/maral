// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_PARTIAL_CHARGE_HPP
#define MARAL_COMPONENTS_PARTIAL_CHARGE_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning partial charge to atoms.
///
/// \param T Type of the value (e.g. float, double, etc.).
/// \remarks
/// \b partial_charge is a structural component class that allows assigning a
/// partial charge to an atom, so it can be accessed or changed later.

template <typename T = float>
    class partial_charge_component
{
public:
/// \name Construction
//@{
    partial_charge_component(T chg = T(0))
    : partial_charge_(chg)
    {
        static_assert(
            std::is_floating_point<T>::value == true,
            "Only float types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T partial_charge() const
    {   return partial_charge_;    }

    void partial_charge(T chg)
    {   partial_charge_ = chg; }
//@}

// Implementation
private:
    T partial_charge_;
};

template <typename T = float>
using partial_charge = partial_charge_component<T>;

}}  // maral::component

#endif    // MARAL_COMPONENTS_PARTIAL_CHARGE_HPP
