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
/// \file policies/ordered.hpp
/// \brief Include file for ordered policy class.
///
/// \b ordered.hpp is the include file that defines \b ordered structural policy
/// class.

#ifndef MARAL_POLICIES_ORDERED_HPP
#define MARAL_POLICIES_ORDERED_HPP

namespace maral { namespace policy {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning serial numbers to nodes.
///
/// \param T Type of the string to be used as name (e.g. unsigned, short, ...).
/// \remarks
/// \b ordered is a structural policy class that allows assigning a serial
/// number to a node, so it can be accessed or changed later.

template <typename T>
    class ordered
{
public:
/// \name Construction
//@{
    ordered(T ordinal)
    : ordinal_(ordinal)
    {
        BOOST_STATIC_ASSERT_MSG(
            std::is_floating_point<T>::value == false,
            "only integral types are allowed :(");
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
protected:
    T ordinal_;
};

}}    // namespaces

#endif    // MARAL_POLICIES_ORDERED_HPP
