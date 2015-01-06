// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_COVALENT_RADIUS_HPP
#define MARAL_COMPONENTS_COVALENT_RADIUS_HPP

#include <array>

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////

template <typename T = float>
struct covalent_radius_db
{
    covalent_radius_db();

    std::array<T, 120> covalent_radii_;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Functional component for accessing chemcial symbol of atoms.
///
/// \param T Type of the string to be used as the symbol (e.g. std::string,
/// std::wstring, ...).
/// \remarks
/// chemical_symbol is a functional component class that allows accessing
/// chemcial symbol of an atom or chaning it.

template <typename T = float>
class covalent_radius_component
{
public:
/// \name Construction
//@{
    covalent_radius_component()
    {}
//@}

/// \name Attributes
//@{
    static T z_2_covalent_radius(unsigned z)
    {   return db_.covalent_radii_[z]; }
//@}

// Implementation
private:
    static covalent_radius_db<T> db_;
};

template <typename T>
covalent_radius_db<T> covalent_radius_component<T>::db_;

template <typename T = float>
using covalent_radius = covalent_radius_component<T>;

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/components/covalent_radius.ipp>

}}    // maral::component

#endif    // MARAL_COMPONENTS_COVALENT_RADIUS_HPP
