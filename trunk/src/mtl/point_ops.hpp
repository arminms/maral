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
/// \file point_ops.hpp
/// \brief Include file for all point types operations.
///
/// \b point_ops.hpp is the header file for all the operations on
/// points (i.e. point2, point3, point4).

#ifndef MARAL_MTL_POINT_OPS_HPP_INCLUDED_
#define MARAL_MTL_POINT_OPS_HPP_INCLUDED_

#include <cmath>

#ifndef MARAL_MTL_CONSTANTS_HPP_INCLUDED_
#include "constants.hpp"
#endif // MARAL_MTL_CONSTANTS_HPP_INCLUDED_

namespace maral { namespace mtl {

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include "point_ops.ipp"

}}    // namespaces

#endif    // MARAL_MTL_POINT_OPS_HPP_INCLUDED_
