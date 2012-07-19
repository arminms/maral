////////////////////////////////////////////////////////////////////////////////
//     Molecular Animation, Graphics and Modeling Application Framework
//                                  MAGMA
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
/// \file MtlPoint.hpp
/// \brief Include file for all classes representing points.
///
/// \b MtlPoint.hpp is the include file for Point2i, Point2f, Point2d,
/// Point3i, Point3f, Point3d, Point4i, Point4f and Point4d classes.

#ifndef MTL_POINT_HPP
#define MTL_POINT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace Magma {

	namespace Mtl {

template <typename T> class Vector2;

////////////////////////////////////////////////////////////////////////////////
/// \brief The Point2 class abstracts a 2D point.
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// \par
/// Point2 abstracts a 2D point. It is templated on the component
/// datatype. Points have position but neither magnitude nor direction.
/// It is used to define the position of a point in 2D space.
/// \par
/// Don't use Point2 to represent a Vector2. One difference you should
/// note is that certain matrix operations are different between Point2
/// and Vector2 such as xform and operator*. A Vector2 xform by matrix
/// is simply a rotation, while a Point2 xformed by a matrix is a full
/// matrix transform (rotation, skew, translation, scale).
/// \see Point2i, Point2f, Point2d, Vector2
/// \author Armin Madadkar-Sobhani

template <typename T>
class Point2
{
public:
/// \name Construction
//@{
	Point2();
	Point2(T x, T y);
	explicit Point2(const Vector2<T>& v);

	// Copy constructor
	Point2(const Point2<T>& p);

	// Assignment method
	Point2<T>& operator=(const Point2<T>& p);
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

#include "MtlPoint.inl"

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Use Point2i to define a 2D point composed of 2 unsigned integer
/// components. It has all the features of Point2, i.e. the member
/// functions of Point2i are similar to the member functions of Point2
/// class. So, you can use the Point2 reference documentation: Wherever
/// you see a \a T type, substitute it to \a int.
/// \see Point2

typedef Point2<int> Point2i;

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Use Point2f to define a 2D point composed of 2 float components.
/// It has all the features of Point2, i.e. the member functions of
/// Point2f are similar to the member functions of Point2 class. So,
/// you can use the Point2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a float.
/// \see Point2

typedef Point2<float> Point2f;

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Use Point2d to define a 2D point composed of 2 double components.
/// It has all the features of Point2, i.e. the member functions of
/// Point2d are similar to the member functions of Point2 class. So,
/// you can use the Point2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a double.
/// \see Point2

typedef Point2<double> Point2d;

	}	// namespace Mtl
}	// namespace Magma

#endif	//MTL_POINT_HPP
