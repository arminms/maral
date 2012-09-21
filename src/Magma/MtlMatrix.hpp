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
//------------------------------------------------------------------------------
/// \file MtlMatrix.hpp
/// \brief Include file for all classes representing matrices.
///
/// \b MtlMatrix.hpp is the include file for Matrix22f, Matrix22d, Matrix33f,
/// Matrix33d, Matrix44f and Matrix44f classes.

#ifndef MTL_MATRIX_HPP
#define MTL_MATRIX_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace Magma {

	namespace Mtl {

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 2x2 matrix (ordered in memory by Column).
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// Matrix22 class abstracts a 2x2 matrix. To be compatible with \a OpenGL and
/// efficency, elements are stored in column major order (in opposed to row
/// major C/C++ ordering of arrays) as 4 consecutive datatypes. It is templated
/// on the component datatype.
/// \see Matrix22f, Matrix22d
/// \author Armin Madadkar-Sobhani

template <typename T>
class Matrix22
{
public:

	/// \brief Helper nested class for Matrix22::operator[].
	///
	/// \remarks
	/// This nested class encapsulates the row that the user is accessing and
	/// implements a new operator[] that passes the column to use.

	class RowAccessor22
	{
	public:
		RowAccessor22(Matrix22<T>* mat, const unsigned row);

		T& operator[](const unsigned column);

		/// \brief Pointer to the matrix
		///
		/// Pointer to a Matrix22 object set by constructor
		Matrix22<T>* m_;

		/// \brief The row being accessed
		///
		/// The row being accessed set by constructor that can be used later
		/// by RowAccessor22::operator[]
		unsigned r_;
	};

	/// \brief Helper nested class for Matrix22::operator[] const.
	///
	/// \remarks
	/// This nested class encapsulates the row that the user is accessing and
	/// implements a new operator[] that passes the column to use.

	class ConstRowAccessor22
	{
	public:
		ConstRowAccessor22(const Matrix22<T>* mat, const unsigned row);

		const T& operator[](const unsigned column) const;

		/// \brief Pointer to the matrix
		///
		/// Pointer to a Matrix22 object set by constructor
		const Matrix22<T>* m_;

		/// \brief The row being accessed
		///
		/// The row being accessed set by constructor that can be used later
		/// by ConstRowAccessor22::operator[]
		unsigned r_;
	};

/// \name Construction
//@{
	Matrix22();
	Matrix22(std::initializer_list<T> vals);

	// Copy constructor
	Matrix22(const Matrix22<T>& m);

	// Assignment method
	Matrix22<T>& operator=(const Matrix22<T>& m);
//@}

/// \name Attributes
//@{
	Matrix22<T>& identity();
	Matrix22<T>& zero();

	void set(const T* dataPtr);
	void setTranspose(const T* dataPtr);

	T* getData();
	const T* getData() const;
//@}

/// \name Operators
//@{
	T& operator() (const unsigned row, const unsigned column);
	const T& operator() (const unsigned row, const unsigned column) const;

	RowAccessor22 operator[] (const unsigned row);
	ConstRowAccessor22 operator[] (const unsigned row) const;
//@}

// Implementation

	/// \brief Matrix data in column major order
	///
	/// Matrix data in column major order as four consecutive values in memory.
	/// Please use Matrix22::operator()(const unsigned,const unsigned)
	/// or Matrix22::operator[] instead of direct access.
	T data_[4];
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 floats
///
/// Use Matrix22f to define a 2x2 matrix composed of 4 float components. It has
/// all the features of Matrix22, i.e. the member functions of Matrix22f are
/// similar to the member functions of Matrix22 class. So, you can use the
/// Matrix22 reference documentation: Wherever you see a \a T type, substitute
/// it to \a float.

typedef Matrix22<float> Matrix22f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 double
///
/// Use Matrix22d to define a 2x2 matrix composed of 4 double components. It has
/// all the features of Matrix22, i.e. the member functions of Matrix22d are
/// similar to the member functions of Matrix22 class. So, you can use the
/// Matrix22 reference documentation: Wherever you see a \a T type, substitute
/// it to \a double.

typedef Matrix22<double> Matrix22d;

////////////////////////////////////////////////////////////////////////////////
// Inlines

#include "MtlMatrix.inl"

	}	// namespace Mtl
}	// namespace Magma

#endif	//MTL_MATRIX_HPP

