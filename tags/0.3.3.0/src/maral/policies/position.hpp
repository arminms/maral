// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_POSITION_HPP
#define MARAL_POLICIES_POSITION_HPP

#ifndef MARAL_TRAITS_HPP
#include <maral/traits.hpp>
#endif // MARAL_TRAITS_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning position to nodes.
///
/// \param T Type of the point to be used for the position (e.g. mtl::point3f,
/// mtl::point2d, ...).
/// \remarks
/// \b position is a structural policy class that allows assigning a position to
/// a node, so it can be accessed or changed later.

template <typename T>
    class position
{
    static_assert(
        pntvec_traits<T>::extent::den > 1,
        "need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    position()
    {   pos_.zero();    }

    position(const T& pos)
    :   pos_(pos)
    {}
//@}

/// \name Attributes
//@{
    T& center()
    {   return pos_;    }

    T get_center() const
    {   return pos_;    }

    void set_center(const T& pos)
    {   pos_ = pos; }
//@}

/// \name Operators
//@{
    typename pntvec_traits<T>::reference operator[]
        (const unsigned idx)
    {   return pos_[idx];   }
    typename pntvec_traits<T>::value_type operator[]
        (const unsigned idx) const
    {   return pos_[idx]; }
//@}

// Implementation
protected:
    T pos_;
};

}   // namespace policy

GENERATE_HAS_POLICY(position)   // creates has_policy_position

}    // namespace maral

#endif    // MARAL_POLICIES_POSITION_HPP

