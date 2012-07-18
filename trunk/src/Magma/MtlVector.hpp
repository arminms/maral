////////////////////////////////////////////////////////////////////////////////
//     Molecular Animation, Graphics and Modeling Application Framework
//                                  MAGMA
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
/// \file MtlVector.hpp
/// \brief Include file for all classes representing vectors.
///
/// \b MtlVector.hpp is the include file for Vector2i, Vector2f,
/// Vector2d, Vector3i, Vector3f, Vector3d, Vector4i, Vector4f and
/// Vector4d classes.

#ifndef MTL_VECTOR_HPP
#define MTL_VECTOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Magma/MtlDefines.hpp>

namespace Magma {
	namespace Mtl {

template <typename T> class Point2;

////////////////////////////////////////////////////////////////////////////////
/// \brief The Vector2 class abstracts a 2D vector.
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// \par
/// Vector2 abstracts a 2D vector. It is templated on the component
/// datatype. Vectors have magnitude and direction but no position. It
/// is used to define the displacement of a point in the 2D space. So
/// considered as difference between 2 points: V = P2 - P1..
/// \par
/// Don't use Vector2 to represent a Point2. One difference you should
/// note is that certain matrix operations are different between Point2
/// and Vector2 such as xform and operator*. A Vector2 xform by matrix
/// is simply a rotation, while a Point2 xformed by a matrix is a full
/// matrix transform (rotation, skew, translation, scale).
/// \see Vector2i, Vector2f, Vector2d, Point2
/// \author Armin Madadkar-Sobhani

template <typename T>
class Vector2
{
public:
/// \name Construction
//@{
	Vector2();
	Vector2(T x, T y);
	Vector2(const Point2<T>& p1, const Point2<T>& p2);
	explicit Vector2(const Point2<T>& p);

	// Copy constructor
	Vector2(const Vector2<T>& p);

	// Assignment method
	Vector2<T>& operator=(const Vector2<T>& p);
//@}

/// \name Attributes
//@{
	T& x();
	T& y();

	T getX() const;
	T getY() const;

	void setX(T x);
	void setY(T y);

	void set(T x, T y);
	void set(const T* dataPtr);

	T* getData();
	const T* getData() const;
//@}

/// \name Operators
//@{
	T& operator[] (const unsigned i);
	T  operator[] (const unsigned i) const;
//@}

// Implementation
protected:
	T data_[2];
};

////////////////////////////////////////////////////////////////////////////////
// Inlines

#include "MtlVector.inl"

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Use Vector2i to define a 2D vector composed of 2 unsigned integer
/// components. It has all the features of Vector2, i.e. the member
/// functions of Vector2i are similar to the member functions of
/// Vector2 class. So, you can use the Vector2 reference documentation:
/// Wherever you see a \a T type, substitute it to \a int.
/// \see Vector2

typedef Vector2<int> Vector2i;

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Use Vector2f to define a 2D vector composed of 2 float components.
/// It has all the features of Vector2, i.e. the member functions of
/// Vector2f are similar to the member functions of Vector2 class. So,
/// you can use the Vector2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a float.
/// \see Vector2

typedef Vector2<float> Vector2f;

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Use Vector2d to define a 2D vector composed of 2 double components.
/// It has all the features of Vector2, i.e. the member functions of
/// Vector2d are similar to the member functions of Vector2 class. So,
/// you can use the Vector2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a double.
/// \see Vector2

typedef Vector2<double> Vector2d;

	}	// namespace Mtl
}	// namespace Magma

#endif	//MTL_VECTOR_HPP
