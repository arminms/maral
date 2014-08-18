////////////////////////////////////////////////////////////////////////////////
//
//                                  MARAL
//            (Molecular Architectural Record & Assembly Library)
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//------------------------------------------------------------------------------
/// \file policies/position.hpp
/// \brief Include file for \b position policy class.
///
/// \b position.hpp is the include file that defines \b position structural
/// policy class.

#ifndef MARAL_POLICIES_POSITION_HPP
#define MARAL_POLICIES_POSITION_HPP

#ifndef MARAL_TRAITS_HPP
#include <maral/traits.hpp>
#endif // MARAL_TRAITS_HPP

namespace maral { namespace policies {

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
//    typename pntvec_traits<T>::value_type operator[]
//        (const unsigned idx) const;
//    {   return pos_[idx]; }
//@}

// Implementation
protected:
    T pos_;
};

}}    // namespaces

#endif    // MARAL_POLICIES_POSITION_HPP

