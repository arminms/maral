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
/// \file mtl/inserters.hpp
/// \brief Include file for stream insterters for maral::mtl classes.
///
/// \b mtl/inserters.hpp is the header file for all stream inserters for
/// maral::mtl classes.

#ifndef MARAL_MTL_INSERTERS_HPP
#define MARAL_MTL_INSERTERS_HPP

#ifndef MARAL_MTL_POINT_HPP
#include <maral/mtl/point.hpp>
#endif // MARAL_MTL_POINT_HPP

#ifndef MARAL_MTL_VECTOR_HPP
#include <maral/mtl/vector.hpp>
#endif // MARAL_MTL_VECTOR_HPP

#ifndef MARAL_MTL_MATRIX_HPP
#include <maral/mtl/matrix.hpp>
#endif // MARAL_MTL_MATRIX_HPP

#ifndef MARAL_MTL_IOMANIP_HPP
#include <maral/mtl/iomanip.hpp>
#endif // MARAL_MTL_IOMANIP_HPP

namespace maral { namespace mtl {

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/mtl/inserters.ipp>

}}    // namespaces

#endif // MARAL_MTL_INSERTERS_HPP
