////////////////////////////////////////////////////////////////////////////////
//
//     Molecular Animation, Graphics and Modeling Application Framework
//                                  MAGMA
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

#ifndef MAGMA_MTL_MATRIX_OPS_HPP_INCLUDED_
#define MAGMA_MTL_MATRIX_OPS_HPP_INCLUDED_

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace magma
{
    namespace mtl
    {

////////////////////////////////////////////////////////////////////////////////
// Inlines

        #include "matrix_ops.ipp"

    }    // namespace mtl
}    // namespace magma

#endif    // MAGMA_MTL_MATRIX_OPS_HPP_INCLUDED_

