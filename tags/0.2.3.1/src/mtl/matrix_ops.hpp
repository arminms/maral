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
/// \file matrix_ops.hpp
/// \brief Include file for all matrix types operations.
///
/// \b matrix_ops.hpp is the header file for all the operations on
/// matrices (i.e. matrix22, matrix33, matrix44).

#ifndef MARAL_MTL_MATRIX_OPS_HPP_INCLUDED_
#define MARAL_MTL_MATRIX_OPS_HPP_INCLUDED_

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace maral
{
    namespace mtl
    {

////////////////////////////////////////////////////////////////////////////////
// Inlines

        #include "matrix_ops.ipp"

    }    // namespace mtl
}    // namespace maral

#endif    // MARAL_MTL_MATRIX_OPS_HPP_INCLUDED_

