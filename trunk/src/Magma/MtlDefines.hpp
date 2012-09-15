////////////////////////////////////////////////////////////////////////////////
//     Molecular Animation, Graphics and Modeling Application Framework
//                                  MAGMA
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//
/// \file MtlDefines.hpp
/// \brief Include file for some frequently used mathematical defines.
///
/// \b MtlDefines.hpp is the include file for some frequently used
/// mathematical constansts and handy templated inlines.

#ifndef MTL_DEFINES_HPP
#define MTL_DEFINES_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
/// \brief The namespace for \b Magma.
///
/// This is the main namespace for the \b Magma application framework.
/// In order to work with \b Magma this namespace must be used (i.e by
/// \a using keyword or scope operator (Magma::...)

namespace Magma
{

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the \b Mtl (Magma::Mtl).
///
/// Namespace for the \b Math \b Template \b Library (MTL). \b MTL is the
/// mathematical engine behind \b Magma and because all the classes and
/// functions have been implemented as header only inlines, it is
/// highly efficient. The \b MTL has two aspects: The \a data \a types,
/// and the \a operations on the data. All data types and operations
/// are defined in the Mtl namespace. Thus all types must be prefixed
/// with the Mtl:: scope or a \a using \a namespace \a Magma::Mtl;
/// command can be used to bring all of the \b MTL functionality into
/// the local scope.

	namespace Mtl
	{

////////////////////////////////////////////////////////////////////////////////
// Frequently used constants

/// \cond Consts

const float  HALF        = 0.5f;
const float  SMALL       = 0.00001f;
const float  SMALLREV    = 1.0E+5;
const float  CMPERR      = 0.00001f;
const float  CMPERRSQ    = 1.0E-10f;
const float  CMPERRSQAPX = 1.0E-9f;
const float  PIUNDER180F = 5.72957795130823E+001f;
const float  FPI         = 3.141593f;
const double PI          = 3.14159265358979323846;
const double PIOVER180   = 1.74532925199433E-002;
const double PIUNDER180  = 5.72957795130823E+001;

/// \endcond

////////////////////////////////////////////////////////////////////////////////
// Inlines

#include "MtlDefines.inl"

	}	// namespace Mtl
}	// namespace Magma

#endif	//MTL_DEFINES_HPP
