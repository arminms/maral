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

#ifndef MARAL_MTL_INSERTERS_HPP_INCLUDED_
#define MARAL_MTL_INSERTERS_HPP_INCLUDED_

#include <iomanip>

#ifndef MARAL_MTL_IOMANIP_HPP_INCLUDED_
#include "iomanip.hpp"
#endif // MARAL_MTL_IOMANIP_HPP_INCLUDED_

namespace maral { namespace mtl {

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include "inserters.ipp"

}}    // namespaces

#endif // MARAL_MTL_INSERTERS_HPP_INCLUDED_
