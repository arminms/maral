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
//	MtlPoint.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all point classes.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a Point2 object (default constructor). All components
/// are initialized to zero.

template <typename T>
inline Point2<T>::Point2()
{
	data_[0] = data_[1] = (T)0;
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Constructs a Point2 object from 2 supplied arbitrary type.

template <typename T>
inline Point2<T>::Point2(T x, T y)
{
	data_[0] = x; data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A Vector2 object that already exists.
/// \remarks
/// Explicitly constructs a Point2 object from a Vector2.

template <typename T>
inline Point2<T>::Point2(const Vector2<T>& v)
{
	data_[0] = v[0]; data_[1] = v[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A Point2 object that already exists.
/// \remarks
/// Constructs a Point2 object from another one (copy constructor).

template <typename T>
inline Point2<T>::Point2(const Point2<T>& p)
{
	if (this != &p)
	{
		data_[0] = p.data_[0];
		data_[1] = p.data_[1];
	}
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this Point2 object.
/// \param p A Point2 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source Point2 \a p
/// object into this Point2 object.

template <typename T>
inline Point2<T>& Point2<T>::operator=(const Point2<T>& p)
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
/// \see Point2<T>::setX, Point2<T>::getX

template <typename T>
inline T& Point2<T>::x()
{
	return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing y
/// coordinate of this point.
/// \remarks
/// Returns y coordinate of this point. It can be used on either the
/// right (r-value) or the left (l-value) of an assignment statement.
/// \see Point2<T>::setY, Point2<T>::getY

template <typename T>
inline T& Point2<T>::y()
{
	return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this point.
/// \remarks
/// Returns x coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Point2<T>::x, Point2<T>::setX

template <typename T>
inline T Point2<T>::getX() const
{
	return data_[0];
}

////////////////////////////////////////////////////////////////////////////////
/// \return An arbitrary type (int, float, double, ...) containing x
/// coordinate of this point.
/// \remarks
/// Returns y coordinate of this point. It can be used only on the
/// right side (r-value) of an assignment statement.
/// \see Point2<T>::y, Point2<T>::setY

template <typename T>
inline T Point2<T>::getY() const
{
	return data_[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \param x An arbitrary type (int, float, double, ...) containing x
/// coordinate.
/// \remarks
/// Changes x coordinate of this point.
/// \see Point2<T>::x, Point2<T>::getX

template <typename T>
inline void Point2<T>::setX(T x)
{
	data_[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
/// \param y An arbitrary type (int, float, double, ...) containing y
/// coordinate.
/// \remarks
/// Changes y coordinate of this point.
/// \see Point2<T>::y, Point2<T>::getY

template <typename T>
inline void Point2<T>::setY(T y)
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
/// \see Point2<T>::set(const T*)

template <typename T>
inline void Point2<T>::set(T x, T y)
{
	data_[0] = x; data_[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// \param dataPtr Pointer to an array of two arbitrary types containing
/// x and y.
/// \remarks
/// This overloaded member function changes x and y components of this
/// point to new values.
/// \see Point2<T>::set(T,T)

template <typename T>
inline void Point2<T>::set(const T* dataPtr)
{
	assert(dataPtr);
	data_[0] = dataPtr[0]; data_[1] = dataPtr[1];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this point.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline T* Point2<T>::getData()
{
	return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the first element (x coordinate) of the component
/// array for this point.
/// \remarks
/// Gets the internal array of the components.

template <typename T>
inline const T* Point2<T>::getData() const
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
/// \see Point2<T>::operator[](const unsigned) const

template <typename T>
inline T& Point2<T>::operator[] (const unsigned i)
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
/// \see Point2<T>::operator[](const unsigned)

template <typename T>
inline T Point2<T>::operator[] (const unsigned i) const
{
	assert(i < 2);
	return data_[i];
}
