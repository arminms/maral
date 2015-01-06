// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_POSITION_HPP
#define MARAL_COMPONENTS_POSITION_HPP

#ifndef MARAL_TRAITS_HPP
#include <maral/traits.hpp>
#endif // MARAL_TRAITS_HPP

namespace maral { namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning position to nodes.
///
/// \param T Type of the point to be used for the position (e.g. mtl::point3f,
/// mtl::point2d, ...).
/// \remarks
/// \b position is a structural component class that allows assigning a position
/// to a node, so it can be accessed or changed later.

template <typename T = mtl::point3f>
    class position_component
{
    static_assert(
        pntvec_traits<T>::extent::den > 1,
        "Need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    position_component()
    {   pos_.zero();    }

    position_component(const T& pos)
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

    std::size_t size() const
    {   return 1;  }
//@}

/// \name Operators
//@{
    typename pntvec_traits<T>::reference operator()
        (const unsigned idx, const std::size_t frame)
    {   return pos_[idx];   }
    const typename pntvec_traits<T>::value_type operator()
        (const unsigned idx, const std::size_t frame) const
    {   return pos_[idx];   }

    typename pntvec_traits<T>::reference operator[]
        (const unsigned idx)
    {   return pos_[idx];   }
    typename pntvec_traits<T>::value_type operator[]
        (const unsigned idx) const
    {   return pos_[idx]; }
//@}

// Implementation
private:
    T pos_;
};

template <typename T = mtl::point3f>
using position = position_component<T>;

}}  // maral::component

#endif    // MARAL_COMPONENTS_POSITION_HPP

