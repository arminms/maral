// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_LINKED_POSITION_HPP
#define MARAL_POLICIES_LINKED_POSITION_HPP

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

template
<
    typename T
,   template <class> class Coordinates
>
    class linked_position
{
    static_assert(
        pntvec_traits<T>::extent::den > 1,
        "need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    linked_position()
    :   idx_(Coordinates<T>::add_coord(std::move(T())))
    //{   idx_ = typename Coordinates<T>::add_coord(T());    }
    //{   idx_ = Coordinates<T>::add_coord(std::move(T()));    }
    {}

    linked_position(const T& pos)
    //:   idx_(typename Coordinates<T>::add_coord(pos))
    :   idx_(Coordinates<T>::add_coord(std::move(pos)))
    {}
//@}

/// \name Attributes
//@{
    T& center()
    {   return Coordinates<T>::coord(idx_);    }

    T get_center() const
    {   return Coordinates<T>::coord(idx_);    }

    void set_center(const T& pos)
    {   Coordinates<T>::coord(idx_) = pos; }

    std::size_t size() const
    {   return Coordinates<T>::frames_size();  }
//@}

/// \name Operators
//@{
    typename pntvec_traits<T>::reference operator()
        (const unsigned idx, const std::size_t frame)
    {   return Coordinates<T>::coord(idx_, frame)[idx];   }
    const typename pntvec_traits<T>::value_type operator()
        (const unsigned idx, const std::size_t frame) const
    {   return Coordinates<T>::coord(idx_, frame)[idx];   }

    typename pntvec_traits<T>::reference operator[]
        (const unsigned idx)
    {   return Coordinates<T>::coord(idx_)[idx];   }
    typename pntvec_traits<T>::value_type operator[]
        (const unsigned idx) const
    {   return Coordinates<T>::coord(idx_)[idx]; }
//@}

// Implementation
private:
    //unsigned idx_;
    std::size_t idx_;
};

}   // namespace policy

GENERATE_HAS_POLICY(linked_position)   // creates has_policy_linked_position

}    // namespace maral

#endif    // MARAL_POLICIES_LINKED_POSITION_HPP
