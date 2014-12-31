// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_LINKED_POSITION_HPP
#define MARAL_COMPONENTS_LINKED_POSITION_HPP

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
/// \b position is a structural component class that allows assigning a position to
/// a node, so it can be accessed or changed later.

template
<
    typename T
,   template <class> class Coordinates
>
    class linked_position_component
{
    static_assert(
        pntvec_traits<T>::extent::den > 1,
        "need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    linked_position_component()
    :   idx_(Coordinates<T>::add_coord(std::move(T())))
    //{   idx_ = typename Coordinates<T>::add_coord(T());    }
    //{   idx_ = Coordinates<T>::add_coord(std::move(T()));    }
    {}

    linked_position_component(const T& pos)
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

template
<
    typename T
,   template <class> class Coordinates
>
using linked_position = linked_position_component<T, Coordinates>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_LINKED_POSITION_HPP
