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
/// \file constants.hpp
/// \brief Include file for some frequently used mathematical constants.
///
/// \b constants.hpp is the include file for some frequently used mathematical
/// constants.

#ifndef MARAL_MTL_CONSTANTS_HPP_INCLUDED_
#define MARAL_MTL_CONSTANTS_HPP_INCLUDED_

////////////////////////////////////////////////////////////////////////////////
/// \brief The namespace for \b Maral.
///
/// This is the main namespace for the \b Maral application framework.
/// In order to work with \b Maral this namespace must be used (i.e by
/// \a using keyword or scope operator (maral::...)

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the \b Mtl (maral::mtl).
///
/// Namespace for the \b Math \b Template \b Library (\b Mtl). \b Mtl is the
/// mathematical engine behind \b Maral and because all the classes and
/// functions have been implemented as header only inlines, it is
/// highly efficient. The \b Mtl has two aspects: The \a data \a types,
/// and the \a operations on the data. All data types and operations
/// are defined in the mtl namespace. Thus all types must be prefixed
/// with the mtl:: scope or a \a using \a namespace \a maral::mtl;
/// command can be used to bring all of the \b Mtl functionality into
/// the local scope.

namespace mtl {

////////////////////////////////////////////////////////////////////////////////
// Frequently used constants

/// \cond Consts

const float  SMALL       = 0.00001f;
const float  SMALLREV    = 1.0E+5;

/// \endcond

}}    // namespaces

#endif    // MARAL_MTL_CONSTANTS_HPP_INCLUDED_
