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
// $Id: MtlPoint.inl 25 2012-09-15 23:57:30Z armin $
//------------------------------------------------------------------------------
// Filename:
//    point.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains inlines for all point classes.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// point2 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a point2 object (default constructor). For efficiency, no
/// initialization is performed which leaves point in an indeterminate state.
/// You may call zero() member function later to make a zero point.
/// \see point2::zero

template <typename T>
inline point2<T>::point2()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Constructs a point2 object from 2 supplied arbitrary type.

template <typename T>
inline point2<T>::point2(T x, T y)
{
    data_[0] = x; data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param v A vector2 object that already exists.
/// \remarks
/// Explicitly constructs a point2 object from a vector2.

template <typename T>
inline point2<T>::point2(const vector2<T>& v)
{
    data_[0] = v[0]; data_[1] = v[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A point2 object that already exists.
/// \remarks
/// Constructs a point2 object from another one (copy constructor).

template <typename T>
inline point2<T>::point2(const point2<T>& p)
{
    if (this != &p)
    {
        data_[0] = p.data_[0];
        data_[1] = p.data_[1];
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this point2 object.
/// \param p A point2 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source point2 \a p
/// object into this point2 object.

template <typename T>
inline point2<T>& point2<T>::operator=(const point2<T>& p)
{
    if (this != &p)
    {
        data_[0] = p[0];
        data_[1] = p[1];
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this point.
/// \remarks
/// Returns x coordinate of this point. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see point2::set_x, point2::get_x

template <typename T>
inline T& point2<T>::x()
{
    return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this point.
/// \remarks
/// Returns y coordinate of this point. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see point2::set_y, point2::get_y

template <typename T>
inline T& point2<T>::y()
{
    return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this point.
/// \remarks
/// Returns x coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see point2::x, point2::set_x

template <typename T>
inline T point2<T>::get_x() const
{
    return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this point.
/// \remarks
/// Returns y coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see point2::y, point2::set_y

template <typename T>
inline T point2<T>::get_y() const
{
    return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \remarks
/// Changes x coordinate of this point.
/// \see point2::x, point2::get_x

template <typename T>
inline void point2<T>::set_x(T x)
{
    data_[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Changes y coordinate of this point.
/// \see point2::y, point2::get_y

template <typename T>
inline void point2<T>::set_y(T y)
{
    data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// This overloaded member function changes x and y components of this
/// point to new values.
/// \see point2::set(const T*)

template <typename T>
inline void point2<T>::set(T x, T y)
{
    data_[0] = x; data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of two arbitrary types containing
/// x and y.
/// \remarks
/// This overloaded member function changes x and y components of this
/// point to new values.
/// \see point2::set(T,T)

template <typename T>
inline void point2<T>::set(const T* data_ptr)
{
    assert(data_ptr);
    data_[0] = data_ptr[0]; data_[1] = data_ptr[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this point after all components were initialized to
/// zero.
/// \remarks
/// Sets the point to zero then returns its reference. In this way, it can be
/// used as a parameter for another function.

template <typename T>
inline point2<T>& point2<T>::zero()
{
    data_[0] = data_[1] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this point.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline T* point2<T>::get_data()
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this point.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline const T* point2<T>::get_data() const
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...)
/// containing specified component.
/// \param i The zero-based index of the component to access (x=0, y=1).
/// \pre i < 2
/// \remarks
/// This overloaded operator returns the value of the specified
/// component. It can be used on either the right (r-value) or the
/// left (l-value) of an assignment statement. In debug builds,
/// function asserts if \a i is not in the range 0-1.
/// \see point2::operator[](const unsigned) const

template <typename T>
inline T& point2<T>::operator[] (const unsigned i)
{
    assert(i < 2);
    return data_[i];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...)
/// containing specified component.
/// \param i The zero-based index of the component to access (x=0, y=1).
/// \pre i < 2
/// \remarks
/// This overloaded operator returns the value of the specified
/// component. It can be used only on the right (r-value) of an
/// assignment statement. In debug builds, function asserts if \a i is
/// not in the range 0-1.
/// \see point2::operator[](const unsigned)

template <typename T>
inline T point2<T>::operator[] (const unsigned i) const
{
    assert(i < 2);
    return data_[i];
}

////////////////////////////////////////////////////////////////////////////////
// point3 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a point3 object (default constructor). For efficiency, no
/// initialization is performed which leaves point in an indeterminate state.
/// You may call zero() member function later to make a zero point.
/// \see point3::zero


template <typename T>
inline point3<T>::point3()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \param z An arbitrary type (int, float, double, ...) containing z
/// coordinate.
/// \remarks
/// Constructs a point3 object from 3 supplied arbitrary type.

template <typename T>
inline point3<T>::point3(T x, T y, T z)
{
    data_[0] = x; data_[1] = y; data_[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
/// \param v A vector3 object that already exists.
/// \remarks
/// Explicitly constructs a point3 object from a vector3.

template <typename T>
inline point3<T>::point3(const vector3<T>& v)
{
    data_[0] = v[0]; data_[1] = v[1]; data_[2] = v[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A point3 object that already exists.
/// \remarks
/// Constructs a point3 object from another one (copy constructor).

template <typename T>
inline point3<T>::point3(const point3<T>& p)
{
    if (this != &p)
    {
        data_[0] = p.data_[0];
        data_[1] = p.data_[1];
        data_[2] = p.data_[2];
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this point3 object.
/// \param p A point3 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source point3 \a p
/// object into this point3 object.

template <typename T>
inline point3<T>& point3<T>::operator=(const point3<T>& p)
{
    if (this != &p)
    {
        data_[0] = p[0];
        data_[1] = p[1];
        data_[2] = p[2];
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this point.
/// \remarks
/// Returns x coordinate of this point. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see point3::set_x, point3::get_x

template <typename T>
inline T& point3<T>::x()
{
    return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this point.
/// \remarks
/// Returns y coordinate of this point. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see point3::set_y, point3::get_y

template <typename T>
inline T& point3<T>::y()
{
    return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing z
/// coordinate of this point.
/// \remarks
/// Returns z coordinate of this point. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see point3::set_z, point3::get_z

template <typename T>
inline T& point3<T>::z()
{
    return data_[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this point.
/// \remarks
/// Returns x coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see point3::x, point3::set_x

template <typename T>
inline T point3<T>::get_x() const
{
    return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this point.
/// \remarks
/// Returns y coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see point3::y, point3::set_y

template <typename T>
inline T point3<T>::get_y() const
{
    return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing z
/// coordinate of this point.
/// \remarks
/// Returns z coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see point3::z, point3::set_z

template <typename T>
inline T point3<T>::get_z() const
{
    return data_[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \remarks
/// Changes x coordinate of this point.
/// \see point3::x, point3::get_x

template <typename T>
inline void point3<T>::set_x(T x)
{
    data_[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Changes y coordinate of this point.
/// \see point3::y, point3::get_y

template <typename T>
inline void point3<T>::set_y(T y)
{
    data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param z An arbitrary type (int, float, double, ...) containing z
/// coordinate.
/// \remarks
/// Changes z coordinate of this point.
/// \see point3::z, point3::get_z

template <typename T>
inline void point3<T>::set_z(T z)
{
    data_[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \param z An arbitrary type (int, float, double, ...) containing z
/// coordinate.
/// \remarks
/// This overloaded member function changes x, y and z components of
/// this point to new values.
/// \see point3::set(const T*)

template <typename T>
inline void point3<T>::set(T x, T y, T z)
{
    data_[0] = x; data_[1] = y; data_[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of two arbitrary types containing
/// x and y.
/// \remarks
/// This overloaded member function changes x and y components of this
/// point to new values.
/// \see point3::set(T,T,T)

template <typename T>
inline void point3<T>::set(const T* data_ptr)
{
    assert(data_ptr);
    data_[0] = data_ptr[0]; data_[1] = data_ptr[1]; data_[2] = data_ptr[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this point after all components were initialized to
/// zero.
/// \remarks
/// Sets the point to zero then returns its reference. In this way, it can be
/// used as a parameter for another function.

template <typename T>
inline point3<T>& point3<T>::zero()
{
    data_[0] = data_[1] = data_[2] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this point.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline T* point3<T>::get_data()
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this point.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline const T* point3<T>::get_data() const
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...)
/// containing specified component.
/// \param i The zero-based index of the component to access (x=0, y=1, z=2).
/// \pre i < 3
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used only on the right (r-value) of an assignment statement. In debug
/// builds, function asserts if \a i is not in the range 0-2.
/// \see point3::operator[](const unsigned) const

template <typename T>
inline T& point3<T>::operator[] (const unsigned i)
{
    assert(i < 3);
    return data_[i];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...)
/// containing specified component.
/// \param i The zero-based index of the component to access (x=0, y=1, z=2).
/// \pre i < 3
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used only on the right (r-value) of an assignment statement. In debug
/// builds, function asserts if \a i is not in the range 0-2.
/// \see point3::operator[]

template <typename T>
inline T point3<T>::operator[] (const unsigned i) const
{
    assert(i < 3);
    return data_[i];
}
