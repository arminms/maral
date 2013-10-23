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
/// \file vector.hpp
/// \brief Include file for all classes representing vectors.
///
/// \b vector.hpp is the include file for vector2i, vector2f,
/// vector2d, vector3i, vector3f, vector3d, vector4i, vector4f and
/// vector4d classes.

#ifndef MARAL_MTL_VECTOR_HPP_INCLUDED_
#define MARAL_MTL_VECTOR_HPP_INCLUDED_

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace maral {
    namespace mtl {

template <typename T> class point2;
template <typename T> class point3;

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 2D vector.
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// \par
/// vector2 abstracts a 2D vector. It is templated on the component
/// datatype. Vectors have magnitude and direction but no position. It
/// is used to define the displacement of a point in the 2D space. So
/// considered as difference between 2 points: V = P2 - P1..
/// \par
/// Don't use vector2 to represent a point2. One difference you should
/// note is that certain matrix operations are different between point2
/// and vector2 such as xform and operator*. A vector2 xform by matrix
/// is simply a rotation, while a point2 xformed by a matrix is a full
/// matrix transform (rotation, skew, translation, scale).
/// \see vector2i, vector2f, vector2d, point2
/// \author Armin Madadkar Sobhani

template <typename T>
class vector2
{
public:
/// \name Construction
//@{
    vector2();
    vector2(T x, T y);
    vector2(const point2<T>& p1, const point2<T>& p2);
    explicit vector2(const point2<T>& p);

    // Copy constructor
    vector2(const vector2<T>& v);

    // Assignment method
    vector2<T>& operator=(const vector2<T>& v);
//@}

/// \name Attributes
//@{
    T& x();
    T& y();

    T get_x() const;
    T get_y() const;

    void set_x(T x);
    void set_y(T y);

    void set(T x, T y);
    void set(const T* data_ptr);

    vector2<T>& zero();

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator[] (const unsigned i);
    T  operator[] (const unsigned i) const;
//@}

// Implementation

    /// \brief Vector's data
    ///
    /// Vector's data as two consecutive values in memory. Please use
    /// vector2::operator[] instead of direct access which in debug builds
    /// asserts when index is not less than 2.
    T data_[2];
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 3D vector.
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// \par
/// vector3 abstracts a 3D vector. It is templated on the component
/// datatype. vectors have magnitude and direction but no position. It
/// is used to define the displacement of a point in the 3D space. So
/// considered as difference between 2 points: V = P2 - P1..
/// \par
/// Don't use vector3 to represent a point3. One difference you should
/// note is that certain matrix operations are different between point3
/// and vector3 such as xform and operator*. A vector3 xform by matrix
/// is simply a rotation, while a point3 xformed by a matrix is a full
/// matrix transform (rotation, skew, translation, scale).
/// \see vector3i, vector3f, vector3d, point3
/// \author Armin Madadkar Sobhani

template <typename T>
class vector3
{
public:
/// \name Construction
//@{
    vector3();
    vector3(T x, T y, T z);
    vector3(const point3<T>& p1, const point3<T>& p2);
    explicit vector3(const point3<T>& p);

    // Copy constructor
    vector3(const vector3<T>& v);

    // Assignment method
    vector3<T>& operator=(const vector3<T>& v);
//@}

/// \name Attributes
//@{
    T& x();
    T& y();
    T& z();

    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(T x);
    void set_y(T y);
    void set_z(T y);

    void set(T x, T y, T z);
    void set(const T* data_ptr);

    vector3<T>& zero();

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator[] (const unsigned i);
    T  operator[] (const unsigned i) const;
//@}

// Implementation

    /// \brief Vector's data
    ///
    /// Vector's data as three consecutive values in memory. Please use
    /// vector3::operator[] instead of direct access which in debug builds
    /// asserts when index is not less than 3.
    T data_[3];
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D vector composed of 2 unsigned integers
///
/// Use vector2i to define a 2D vector composed of 2 unsigned integer
/// components. It has all the features of vector2, i.e. the member
/// functions of vector2i are similar to the member functions of
/// vector2 class. So, you can use the vector2 reference documentation:
/// Wherever you see a \a T type, substitute it to \a int.
/// \see vector2

typedef vector2<int> vector2i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D vector composed of 2 unsigned floats
///
/// Use vector2f to define a 2D vector composed of 2 float components.
/// It has all the features of vector2, i.e. the member functions of
/// vector2f are similar to the member functions of vector2 class. So,
/// you can use the vector2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a float.
/// \see vector2

typedef vector2<float> vector2f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D vector composed of 2 unsigned doubles
///
/// Use vector2d to define a 2D vector composed of 2 double components.
/// It has all the features of vector2, i.e. the member functions of
/// vector2d are similar to the member functions of vector2 class. So,
/// you can use the vector2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a double.
/// \see vector2

typedef vector2<double> vector2d;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3D vector composed of 3 unsigned integers
///
/// Use vector3i to define a 3D vector composed of 3 unsigned integer
/// components. It has all the features of vector3, i.e. the member
/// functions of vector3i are similar to the member functions of
/// vector3 class. So, you can use the vector3 reference documentation:
/// Wherever you see a \a T type, substitute it to \a int.
/// \see vector3

typedef vector3<int> vector3i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3D vector composed of 3 floats
///
/// Use vector3f to define a 3D vector composed of 3 float components.
/// It has all the features of vector3, i.e. the member functions of
/// vector3f are similar to the member functions of vector3 class. So,
/// you can use the vector3 reference documentation: Wherever you see
/// a \a T type, substitute it to \a float.
/// \see vector3

typedef vector3<float> vector3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3D vector composed of 3 doubles
///
/// Use vector3d to define a 3D vector composed of 3 double components.
/// It has all the features of vector3, i.e. the member functions of
/// vector3d are similar to the member functions of vector3 class. So,
/// you can use the vector3 reference documentation: Wherever you see
/// a \a T type, substitute it to \a double.
/// \see vector3

typedef vector3<double> vector3d;

////////////////////////////////////////////////////////////////////////////////
// Inlines

#include "vector.ipp"

    }    // namespace mtl
}    // namespace maral

#endif    // MARAL_MTL_VECTOR_HPP_INCLUDED_
