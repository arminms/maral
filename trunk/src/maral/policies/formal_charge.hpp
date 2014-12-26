// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_FORMAL_CHARGE_HPP
#define MARAL_POLICIES_FORMAL_CHARGE_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning formal charge to atoms.
///
/// \param T Type of the value (e.g. char, int, long).
/// \remarks
/// \b formal_charge is a structural component class that allows assigning a formal
/// charge to an atom, so it can be accessed or changed later.

template <typename T>
    class formal_charge
{
public:
/// \name Construction
//@{
    formal_charge(T chg = T(0))
    : formal_charge_(chg)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_integral<T>::value == true,
            "only integral types are allowed :(");
        BOOST_STATIC_ASSERT_MSG(
            std::is_signed<T>::value == true,
            "only signed types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T get_formal_charge() const
    {   return formal_charge_;    }

    void set_formal_charge(T chg)
    {   formal_charge_ = chg; }
//@}

// Implementation
private:
    T formal_charge_;
};

}}    // maral::component

#endif    // MARAL_POLICIES_FORMAL_CHARGE_HPP
