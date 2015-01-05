// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_OCCUPANCY_HPP
#define MARAL_COMPONENTS_OCCUPANCY_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning occupancy to atoms.
///
/// \param T Type of the float to be used for the value (e.g. float, double,
/// ...).
/// \remarks
/// \b occupancy is a structural component class that allows assigning an
/// occupancy to atom, so it can be accessed or changed later.

template <typename T = float>
    class occupancy_component
{
public:
/// \name Construction
//@{
    occupancy_component(T occ = T(1))
    : occupancy_(occ)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_floating_point<T>::value == true,
            "Only float types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    T occupancy() const
    {   return occupancy_;    }

    void occupancy(T occ)
    {   occupancy_ = occ; }
//@}

// Implementation
private:
    T occupancy_;
};

template <typename T = float>
using occupancy = occupancy_component<T>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_OCCUPANCY_HPP
