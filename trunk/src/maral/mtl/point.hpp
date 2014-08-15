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
/// \file point.hpp
/// \brief Include file for all classes representing points and all point types
/// operations.
///
/// \b point.hpp is the include file for point2i, point2f, point2d, point3i,
/// point3f, point3d, point4i, point4f and point4d classes and all the
/// operations on them.

#ifndef MARAL_MTL_POINT_HPP
#define MARAL_MTL_POINT_HPP

#include <cmath>

#ifndef MARAL_MTL_CONSTANTS_HPP
#include <maral/mtl/constants.hpp>
#endif // MARAL_MTL_CONSTANTS_HPP

namespace maral { namespace mtl {

// forward declarations
template <typename T> class vector2;
template <typename T> class vector3;

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 2D point.
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// \par
/// point2 abstracts a 2D point. It is templated on the component
/// datatype. Points have position but neither magnitude nor direction.
/// It is used to define the position of a point in 2D space.
/// \par
/// Don't use point2 to represent a vector2. One difference you should
/// note is that certain matrix operations are different between point2
/// and vector2 such as xform and operator*. A vector2 xform by matrix
/// is simply a rotation, while a point2 xformed by a matrix is a full
/// matrix transform (rotation, skew, translation, scale).
/// \see point2i, point2f, point2d, vector2
/// \author Armin Madadkar Sobhani

template <typename T>
class point2
{
public:
/// \name Construction
//@{
    point2();
    point2(T x, T y);
    explicit point2(const vector2<T>& v);

    // Copy constructor
    point2(const point2<T>& p);

    // Assignment method
    point2<T>& operator=(const point2<T>& p);
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

    point2<T>& zero();

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator[] (const unsigned i);
    T  operator[] (const unsigned i) const;
//@}

// Implementation
private:
    /// \brief Point's data
    ///
    /// Point's data as two consecutive values in memory. As it is a private
    /// member, use point2::operator[] instead of direct access which in debug
    /// builds asserts when index is not less than 2.
    T data_[2];
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 3D point.
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// \par
/// point3 abstracts a 3D point. It is templated on the component
/// datatype. Points have position but neither magnitude nor direction.
/// It is used to define the position of a point in 3D space.
/// \par
/// Don't use point3 to represent a vector3. One difference you should
/// note is that certain matrix operations are different between point3
/// and vector3 such as xform and operator*. A vector3 xform by matrix
/// is simply a rotation, while a point3 xformed by a matrix is a full
/// matrix transform (rotation, skew, translation, scale).
/// \see point3i, point3f, point3d, vector3
/// \author Armin Madadkar-Sobhani

template <typename T>
class point3
{
public:
/// \name Construction
//@{
    point3();
    point3(T x, T y, T z);
    explicit point3(const vector3<T>& v);

    // Copy constructor
    point3(const point3<T>& p);

    // Assignment method
    point3<T>& operator=(const point3<T>& p);
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

    point3<T>& zero();

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator[] (const unsigned i);
    T  operator[] (const unsigned i) const;
//@}

// Implementation
private:
    /// \brief Point's data
    ///
    /// Point's data as two consecutive values in memory. As it is a private
    /// member, use point3::operator[] instead of direct access which in debug
    /// builds asserts when index is not less than 3.
    T data_[3];
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D point composed of 2 signed integers
///
/// Use Point2i to define a 2D point composed of 2 signed integer
/// components. It has all the features of point2, i.e. the member
/// functions of point2i are similar to the member functions of point2
/// class. So, you can use the point2 reference documentation: Wherever
/// you see a \a T type, substitute it to \a int.
/// \see point2

typedef point2<int> point2i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D point composed of 2 floats
///
/// Use point2f to define a 2D point composed of 2 float components.
/// It has all the features of point2, i.e. the member functions of
/// point2f are similar to the member functions of point2 class. So,
/// you can use the point2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a float.
/// \see point2

typedef point2<float> point2f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D point composed of 2 doubles
///
/// Use point2d to define a 2D point composed of 2 double components.
/// It has all the features of point2, i.e. the member functions of
/// point2d are similar to the member functions of point2 class. So,
/// you can use the point2 reference documentation: Wherever you see
/// a \a T type, substitute it to \a double.
/// \see point2

typedef point2<double> point2d;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3D point composed of 3 signed integers
///
/// Use point3i to define a 3D point composed of 3 signed integer
/// components. It has all the features of point3, i.e. the member
/// functions of point3i are similar to the member functions of point3
/// class. So, you can use the point3 reference documentation: Wherever
/// you see a \a T type, substitute it to \a int.
/// \see point3

typedef point3<int> point3i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3D point composed of 3 floats
///
/// Use point3f to define a 3D point composed of 3 float components.
/// It has all the features of point3, i.e. the member functions of
/// point3f are similar to the member functions of point3 class. So,
/// you can use the point3 reference documentation: Wherever you see
/// a \a T type, substitute it to \a float.
/// \see point3

typedef point3<float> point3f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3D point composed of 3 doubles
///
/// Use point3d to define a 3D point composed of 3 double components.
/// It has all the features of point3, i.e. the member functions of
/// point3d are similar to the member functions of point3 class. So,
/// you can use the point3 reference documentation: Wherever you see
/// a \a T type, substitute it to \a double.
/// \see point3

typedef point3<double> point3d;

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/mtl/point.ipp>
#include <maral/mtl/point_ops.ipp>

}}    // namespaces

#endif    // MARAL_MTL_POINT_HPP
