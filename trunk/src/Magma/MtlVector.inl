////////////////////////////////////////////////////////////////////////////////
//     Molecular Animation, Graphics and Modeling Application Framework
//                                  MAGMA
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// Filename:
//	MtlVector.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all vector classes.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// Vector2 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a Vector2 object (default constructor). All components
/// are initialized to zero.

template <typename T>
inline Vector2<T>::Vector2()
{
	data_[0] = data_[1] = (T)0;
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Constructs a Vector2 object from 2 supplied arbitrary type.

template <typename T>
inline Vector2<T>::Vector2(T x, T y)
{
	data_[0] = x; data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param p1 A Point2 object that specify start \a (tail) of the vector.
/// \param p2 A Point2 object that specify end \a (head) of the vector.
/// \remarks
/// Constructs a Vector2 object from 2 supplied Point2 object. The resulting
/// vector is from \a p1 (tail) to \a p2 (head).

template <typename T>
inline Vector2<T>::Vector2(const Point2<T>& p1, const Point2<T>& p2)
{
	data_[0] = p2[0] - p1[0];
	data_[1] = p2[1] - p1[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A Point2 object that already exists.
/// \remarks
/// Explicitly constructs a Vector2 object from a Point2.

template <typename T>
inline Vector2<T>::Vector2(const Point2<T>& p)
{
	data_[0] = p[0]; data_[1] = p[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param v A Vector2 object that already exists.
/// \remarks
/// Constructs a Vector2 object from another one (copy constructor).

template <typename T>
inline Vector2<T>::Vector2(const Vector2<T>& v)
{
	if (this != &v)
	{
		data_[0] = v.data_[0];
		data_[1] = v.data_[1];
	}
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this Vector2 object.
/// \param v A Vector2 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source Vector2 \a v
/// object into this Vector2 object.

template <typename T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& v)
{
	if (this != &v)
	{
		data_[0] = v[0];
		data_[1] = v[1];
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this vector.
/// \remarks
/// Returns x coordinate of this vector. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see Vector2<T>::setX, Vector2<T>::getX

template <typename T>
inline T& Vector2<T>::x()
{
	return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this vector.
/// \remarks
/// Returns y coordinate of this vector. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see Vector2<T>::setY, Vector2<T>::getY

template <typename T>
inline T& Vector2<T>::y()
{
	return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this vector.
/// \remarks
/// Returns x coordinate of this vector. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Vector2<T>::x, Vector2<T>::setX

template <typename T>
inline T Vector2<T>::getX() const
{
	return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this vector.
/// \remarks
/// Returns y coordinate of this vector. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Vector2<T>::y, Vector2<T>::setY

template <typename T>
inline T Vector2<T>::getY() const
{
	return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \remarks
/// Changes x coordinate of this vector.
/// \see Vector2<T>::x, Vector2<T>::getX

template <typename T>
inline void Vector2<T>::setX(T x)
{
	data_[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Changes y coordinate of this vector.
/// \see Vector2<T>::y, Vector2<T>::getY

template <typename T>
inline void Vector2<T>::setY(T y)
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
/// vector to new values.
/// \see Vector2<T>::set(const T*)

template <typename T>
inline void Vector2<T>::set(T x, T y)
{
	data_[0] = x; data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param dataPtr Pointer to an array of two arbitrary types containing
/// x and y.
/// \remarks
/// This overloaded member function changes x and y components of this
/// vector to new values.
/// \see Vector2<T>::set(T,T)

template <typename T>
inline void Vector2<T>::set(const T* dataPtr)
{
	assert(dataPtr);
	data_[0] = dataPtr[0]; data_[1] = dataPtr[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this vector.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline T* Vector2<T>::getData()
{
	return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this vector.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline const T* Vector2<T>::getData() const
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
/// \see Vector2<T>::operator[](const unsigned) const

template <typename T>
inline T& Vector2<T>::operator[] (const unsigned i)
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
/// \see Vector2<T>::operator[](const unsigned)

template <typename T>
inline T Vector2<T>::operator[] (const unsigned i) const
{
	assert(i < 2);
	return data_[i];
}

////////////////////////////////////////////////////////////////////////////////
// Vector3 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a Vector3 object (default constructor). All components
/// are initialized to zero.

template <typename T>
inline Vector3<T>::Vector3()
{
	data_[0] = data_[1] = data_[2] = (T)0;
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \param z An arbitrary type (int, float, double, ...) containing z
/// coordinate.
/// \remarks
/// Constructs a Vector3 object from 3 supplied arbitrary type.

template <typename T>
inline Vector3<T>::Vector3(T x, T y, T z)
{
	data_[0] = x; data_[1] = y; data_[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
/// \param p1 A Point3 object that specify start \a (tail) of the vector.
/// \param p2 A Point3 object that specify end \a (head) of the vector.
/// \remarks
/// Constructs a Vector3 object from 2 supplied Point3 object. The resulting
/// vector is from \a p1 (tail) to \a p2 (head).

template <typename T>
inline Vector3<T>::Vector3(const Point3<T>& p1, const Point3<T>& p2)
{
	data_[0] = p2[0] - p1[0];
	data_[1] = p2[1] - p1[1];
	data_[2] = p2[2] - p1[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A Point3 object that already exists.
/// \remarks
/// Explicitly constructs a Vector3 object from a Point3.

template <typename T>
inline Vector3<T>::Vector3(const Point3<T>& p)
{
	data_[0] = p[0]; data_[1] = p[1]; data_[2] = p[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \param v A Vector3 object that already exists.
/// \remarks
/// Constructs a Vector3 object from another one (copy constructor).

template <typename T>
inline Vector3<T>::Vector3(const Vector3<T>& v)
{
	if (this != &v)
	{
		data_[0] = v.data_[0];
		data_[1] = v.data_[1];
		data_[2] = v.data_[2];
	}
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this Vector3 object.
/// \param v A Vector3 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source Vector3 \a v
/// object into this Vector3 object.

template <typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& v)
{
	if (this != &v)
	{
		data_[0] = v[0];
		data_[1] = v[1];
		data_[2] = v[2];
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this vector.
/// \remarks
/// Returns x coordinate of this vector. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see Vector3<T>::setX, Vector3<T>::getX

template <typename T>
inline T& Vector3<T>::x()
{
	return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this vector.
/// \remarks
/// Returns y coordinate of this vector. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see Vector3<T>::setY, Vector3<T>::getY

template <typename T>
inline T& Vector3<T>::y()
{
	return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing z
/// coordinate of this vector.
/// \remarks
/// Returns z coordinate of this vector. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see Vector3<T>::setZ, Vector3<T>::getZ

template <typename T>
inline T& Vector3<T>::z()
{
	return data_[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this vector.
/// \remarks
/// Returns x coordinate of this vector. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Vector3<T>::x, Vector3<T>::setX

template <typename T>
inline T Vector3<T>::getX() const
{
	return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this vector.
/// \remarks
/// Returns y coordinate of this vector. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Vector3<T>::y, Vector3<T>::setY

template <typename T>
inline T Vector3<T>::getY() const
{
	return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing z
/// coordinate of this vector.
/// \remarks
/// Returns z coordinate of this vector. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Vector3<T>::z, Vector3<T>::setZ

template <typename T>
inline T Vector3<T>::getZ() const
{
	return data_[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \remarks
/// Changes x coordinate of this vector.
/// \see Vector3<T>::x, Vector3<T>::getX

template <typename T>
inline void Vector3<T>::setX(T x)
{
	data_[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Changes y coordinate of this vector.
/// \see Vector3<T>::y, Vector3<T>::getY

template <typename T>
inline void Vector3<T>::setY(T y)
{
	data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param z An arbitrary type (int, float, double, ...) containing z
/// coordinate.
/// \remarks
/// Changes z coordinate of this vector.
/// \see Vector3<T>::z, Vector3<T>::getZ

template <typename T>
inline void Vector3<T>::setZ(T z)
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
/// This overloaded member function changes x, y and z components of this
/// vector to new values.
/// \see Vector3<T>::set(const T*)

template <typename T>
inline void Vector3<T>::set(T x, T y, T z)
{
	data_[0] = x; data_[1] = y; data_[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
/// \param dataPtr Pointer to an array of two arbitrary types containing
/// x and y.
/// \remarks
/// This overloaded member function changes x and y components of this
/// vector to new values.
/// \see Vector3<T>::set(T,T)

template <typename T>
inline void Vector3<T>::set(const T* dataPtr)
{
	assert(dataPtr);
	data_[0] = dataPtr[0]; data_[1] = dataPtr[1]; data_[2] = dataPtr[2];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this vector.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline T* Vector3<T>::getData()
{
	return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this vector.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline const T* Vector3<T>::getData() const
{
	return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...)
/// containing specified component.
/// \param i The zero-based index of the component to access (x=0, y=1, z=2).
/// \pre i < 3
/// \remarks
/// This overloaded operator returns the value of the specified
/// component. It can be used on either the right (r-value) or the
/// left (l-value) of an assignment statement. In debug builds,
/// function asserts if \a i is not in the range 0-2.
/// \see Vector3<T>::operator[](const unsigned) const

template <typename T>
inline T& Vector3<T>::operator[] (const unsigned i)
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
/// This overloaded operator returns the value of the specified
/// component. It can be used only on the right (r-value) of an
/// assignment statement. In debug builds, function asserts if \a i is
/// not in the range 0-2.
/// \see Vector3<T>::operator[](const unsigned)

template <typename T>
inline T Vector3<T>::operator[] (const unsigned i) const
{
	assert(i < 3);
	return data_[i];
}
