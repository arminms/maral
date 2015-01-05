// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_ATOMIC_NUMBER_HPP
#define MARAL_COMPONENTS_ATOMIC_NUMBER_HPP

#include <array>
#include <unordered_map>

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////

template <typename CharT = char>
struct chemical_symbols_db
{
    chemical_symbols_db();

    std::array<const CharT*, 120> symbols_;
    std::unordered_map<std::basic_string<CharT>, unsigned> map_;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning atomic number to atoms.
///
/// \param T Type of the value (e.g. char, int, long).
/// \remarks
/// \b atomic_number is a structural component class that allows assigning an
/// atomic number an atom, so it can be accessed or changed later.

template
<
    typename Zt = unsigned char
,   typename CharT = char
>
    class atomic_number_component
{
public:
/// \name Construction
//@{
    atomic_number_component(Zt z = Zt(6))
    : atomic_number_(z)
    {
        static_assert(
            std::is_integral<Zt>::value == true,
            "Only integral types are allowed :(");
        static_assert(
            std::is_unsigned<Zt>::value == true,
            "Only unsigned types are allowed :(");
    }
//@}

/// \name Attributes
//@{
    unsigned atomic_number() const
    {   return atomic_number_;    }

    void atomic_number(unsigned z)
    {   atomic_number_ = Zt(z); }

    std::basic_string<CharT> chemical_symbol() const
    {   return db_.symbols_[atomic_number_]; }

    void chemical_symbol(const std::basic_string<CharT>& sym)
    {
        auto search = db_.map_.find(sym);
        atomic_number_ =  search != db_.map_.end() ? search->second : 119;
    }
//@}

// Implementation
private:
    Zt atomic_number_;
    static chemical_symbols_db<CharT> db_;
};

template
<
    typename Zt
,   typename CharT
>
chemical_symbols_db<CharT> atomic_number_component<Zt, CharT>::db_;

template
<
    typename Zt = unsigned char
,   typename CharT = char
>
using atomic_number = atomic_number_component<Zt, CharT>;

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/components/atomic_number.ipp>

}}    // maral::component

#endif    // MARAL_COMPONENTS_ATOMIC_NUMBER_HPP
