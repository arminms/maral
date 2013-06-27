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
/// \file matrix.hpp
/// \brief Include file for all classes representing matrices.
///
/// \b matrix.hpp is the include file for matrix22f, matrix22d, matrix33f,
/// matrix33d, matrix44f and matrix44f classes.

#ifndef MATRIX_HPP
#define MATRIX_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace magma {

    namespace mtl {

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 2x2 matrix (ordered in memory by Column).
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// matrix22 class abstracts a 2x2 matrix. To be compatible with \a OpenGL and
/// efficency, elements are stored in column major order (in opposed to row
/// major C/C++ ordering of arrays) as 4 consecutive datatypes. It is templated
/// on the component datatype.
/// \see matrix22f, matrix22d
/// \author Armin Madadkar Sobhani

template <typename T>
class matrix22
{
public:

    /// \brief Helper nested class for matrix22::operator[].
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class row_accessor22
    {
    public:
        row_accessor22(matrix22<T>* mat, const unsigned row);

        T& operator[](const unsigned column);

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix22 object set by constructor
        matrix22<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by row_accessor22::operator[]
        unsigned r_;
    };

    /// \brief Helper nested class for matrix22::operator[] const.
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class const_row_accessor22
    {
    public:
        const_row_accessor22(const matrix22<T>* mat, const unsigned row);

        const T& operator[](const unsigned column) const;

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix22 object set by constructor
        const matrix22<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by const_row_accessor22::operator[]
        unsigned r_;
    };

/// \name Construction
//@{
    matrix22();
    matrix22(std::initializer_list<T> vals);

    // Copy constructor
    matrix22(const matrix22<T>& m);

    // Assignment method
    matrix22<T>& operator=(const matrix22<T>& m);
//@}

/// \name Attributes
//@{
    matrix22<T>& identity();
    matrix22<T>& zero();

    void set(const T* dataPtr);
    void set_transpose(const T* dataPtr);

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator() (const unsigned row, const unsigned column);
    const T& operator() (const unsigned row, const unsigned column) const;

    row_accessor22 operator[] (const unsigned row);
    const_row_accessor22 operator[] (const unsigned row) const;
//@}

// Implementation

    /// \brief Matrix's data in column major order
    ///
    /// Matrix's data in column major order as four consecutive values in
    /// memory. Please use matrix22::operator()(const unsigned,const unsigned)
    /// or matrix22::operator[] instead of direct access.
    T data_[4];
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 floats
///
/// Use matrix22f to define a 2x2 matrix composed of 4 float components. It has
/// all the features of matrix22, i.e. the member functions of matrix22f are
/// similar to the member functions of matrix22 class. So, you can use the
/// matrix22 reference documentation: Wherever you see a \a T type, substitute
/// it to \a float.

typedef matrix22<float> matrix22f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 double
///
/// Use matrix22d to define a 2x2 matrix composed of 4 double components. It has
/// all the features of matrix22, i.e. the member functions of matrix22d are
/// similar to the member functions of matrix22 class. So, you can use the
/// matrix22 reference documentation: Wherever you see a \a T type, substitute
/// it to \a double.

typedef matrix22<double> matrix22d;

////////////////////////////////////////////////////////////////////////////////
// Inlines

#include "matrix.ipp"

    }    // namespace mtl
}    // namespace magma

#endif    // MATRIX_HPP

