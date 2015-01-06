// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_ORDER_HPP
#define MARAL_COMPONENTS_ORDER_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning serial numbers to nodes.
///
/// \param T Type of the value (e.g. unsigend, int, ...).
/// \remarks
/// \b order is a structural component class that allows assigning a serial
/// number to a node, so it can be accessed or changed later.

template <typename T = int>
    class order_component
{
public:
/// \name Construction
//@{
    order_component(T ordinal = T(1))
    : ordinal_(ordinal)
    {
        static_assert(std::is_integral<T>::value == true,
            "Only integral types are allowed :(");
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

template <typename T = int>
using order = order_component<T>;

}}  // maral::component

#endif    // MARAL_COMPONENTS_ORDER_HPP
