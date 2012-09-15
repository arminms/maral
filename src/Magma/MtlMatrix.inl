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
// Filename:
//	MtlMatrix.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all matrix classes.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// RowAccessor22 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// Constructs a RowAccessor22 object. In debug builds, function asserts if
/// \a row is not in the range 0-1.

template <typename T>
inline Matrix22<T>::RowAccessor22::RowAccessor22(
	Matrix22<T>* mat,
	const unsigned row)
:	m_(mat)
,	r_(row)
{
	assert(mat != nullptr);
	assert(row < 2);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param column The zero-based index of the column to access.
/// \pre column < 2
/// \remarks
/// This overloaded operator returns the value at the specified row (implicit)
/// and \a column. It can be used on either the right (r-value) or the left
/// (l-value) of an assignment statement. In debug builds, function asserts if
/// \a column is not in the range 0-1.
/// \see Matrix22::operator[]

template <typename T>
inline T& Matrix22<T>::RowAccessor22::operator[] (
	const unsigned column)
{
	return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// ConstRowAccessor22 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// Constructs a ConstRowAccessor22 object. In debug builds, function asserts if
/// \a row is not in the range 0-1.

template <typename T>
inline Matrix22<T>::ConstRowAccessor22::ConstRowAccessor22(
	const Matrix22<T>* mat,
	const unsigned row)
:	m_(mat)
,	r_(row)
{
	assert(mat != nullptr);
	assert(row < 2);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param column The zero-based index of the column to access.
/// \pre column < 2
/// \remarks
/// This overloaded operator returns the value at the specified row (implicit)
/// and \a column. It can be used only on the right (r-value) of an assignment
/// statement. In debug builds, function asserts if \a column is not in the
/// range 0-1.
/// \see Matrix22::operator[](const unsigned) const

template <typename T>
inline const T& Matrix22<T>::ConstRowAccessor22::operator[] (
	const unsigned column) const
{
	return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// Matrix22 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a Matrix22 object (default constructor). For efficiency, no
/// initialization is performed which leaves matrix in an indeterminate state.
/// You may call Matrix22::identity member function later to make an identity
/// matrix.
/// \see Matrix22::identity

template <typename T>
inline Matrix22<T>::Matrix22()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \pre vals.size() > 4
/// \remarks
/// Constructs a Matrix22 object from an \a initializer-list (\a initializer-list
/// constructor). In debug builds, function asserts if number of elements in
/// \a vals is more than 4. If number of elements in \a vals is less than 4, the
/// rest will be initialized to 0.
///
/// \code
/// Matrix22f zero {}; // matrix with all elements set to zero
/// Matrix22f iden {1.0f, 0.0f, 0.0f, 1.0f}; // identity matrix
/// \endcode

template <typename T>
inline Matrix22<T>::Matrix22(
	std::initializer_list<T> vals)
{
	assert(vals.size() <= 4);
	unsigned count = 0;
	for (auto it=vals.begin(); it != vals.end(); ++it)
		data_[count++] = *it;
	if (count < 4)
		for (register unsigned i = count; i < 4; ++i)
			data_[i] = T(0);
}

////////////////////////////////////////////////////////////////////////////////
/// \param p A Matrix22 object that already exists.
/// \remarks
/// Constructs a Matrix22 object from another one (copy constructor).

template <typename T>
inline Matrix22<T>::Matrix22(const Matrix22<T>& m)
{
	if (this != &m)
	{
		data_[0] = m.data_[0];
		data_[1] = m.data_[1];
		data_[2] = m.data_[2];
		data_[3] = m.data_[3];
	}
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this Matrix22 object.
/// \param m A Matrix22 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source Matrix22 \a m into
/// this Matrix22.

template <typename T>
inline Matrix22<T>& Matrix22<T>::operator=(const Matrix22<T>& m)
{
	if (this != &m)
	{
		data_[0] = m.data_[0];
		data_[1] = m.data_[1];
		data_[2] = m.data_[2];
		data_[3] = m.data_[3];
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// an identity matrix.
/// \remarks
/// Sets this matrix to identity then returns its reference. In this way, it can
/// be used as a parameter for another function.

template <typename T>
inline Matrix22<T>& Matrix22<T>::identity()
{
	data_[0] = data_[3] = (T)1;
	data_[1] = data_[2] = (T)0;
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \param dataPtr Pointer to an array of four arbitrary types.
/// \pre \a dataPtr is in the native format of the Matrix22 class which is a
/// column major order, if not, then you might be able to use the
/// Matrix22<T>::setTranspose function.
/// \remarks
/// This member function sets the matrix to the given data. It is useful to copy
/// matrix data from another math library. Normally this function is used when
/// you want to use an array to init the matrix (see code example).
/// \see Matrix22::setTranspose

template <typename T>
inline void Matrix22<T>::set(const T* dataPtr)
{
	assert(dataPtr);
	data_[0] = dataPtr[0]; data_[1] = dataPtr[1];
	data_[2] = dataPtr[2]; data_[3] = dataPtr[3];
}

////////////////////////////////////////////////////////////////////////////////
/// \param dataPtr Pointer to an array of four arbitrary types.
/// \pre \a dataPtr is in the transpose (row major order) of the Matrix22 native
/// format which is a column major order.
/// \remarks
/// This member function sets the matrix to the transpose of the given data.
/// Matrix22<T>::set() takes raw matrix data in column major order, this
/// function allows you to pass in row major order data. Normally this function
/// is used when you want to use an array to init the matrix (see code example).
///
/// \code
/// float data[] = { 1, 0, 0, 15 };
/// Matrix22f mat;
/// mat.setTranspose(data);
/// \endcode
/// \see Matrix22::set

template <typename T>
inline void Matrix22<T>::setTranspose(const T* dataPtr)
{
	assert(dataPtr);
	data_[0] = dataPtr[0]; data_[1] = dataPtr[2];
	data_[2] = dataPtr[1]; data_[3] = dataPtr[3];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the head of the matrix data.
/// \remarks
/// Gets a pointer to the matrix data.

template <typename T>
inline T* Matrix22<T>::getData()
{
	return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Constant pointer to the head of the matrix data.
/// \remarks
/// Gets a constant pointer to the matrix data.

template <typename T>
inline const T* Matrix22<T>::getData() const
{
	return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) at the
/// specified \a row and \a column.
/// \param row The zero-based index of the row to access.
/// \param column The zero-based index of the column to access.
/// \pre row < 2
/// \pre column < 2
/// \remarks
/// This overloaded operator returns the value at the specified \a row and
/// \a column. It can be used on either the right (r-value) or the left (l-value)
/// of an assignment statement. In debug builds, function asserts if either
/// \a row or \a column are not in the range 0-1.
/// \see Matrix22::operator[]

template <typename T>
inline T& Matrix22<T>::operator() (
	const unsigned row,
	const unsigned column)
{
	assert(row < 2);
	assert(column < 2);
	return data_[(column<<1)+row];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) at the
/// specified \a row and \a column.
/// \param row The zero-based index of the row to access.
/// \param column The zero-based index of the column to access.
/// \pre row < 2
/// \pre column < 2
/// \remarks
/// This overloaded operator returns the value at the specified \a row and
/// \a column. It can be used only on the right (r-value) of an assignment
/// statement. In debug builds, function asserts if either \a row or \a column
/// are not in the range 0-1.
/// \see Matrix22::operator[](const unsigned) const

template <typename T>
inline const T& Matrix22<T>::operator() (
	const unsigned row,
	const unsigned column) const
{
	assert(row < 2);
	assert(column < 2);
	return data_[(column<<1)+row];
}

////////////////////////////////////////////////////////////////////////////////
/// \return A RowAccessor22 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// This overloaded operator returns RowAccessor22 object that can be used
/// subsequently to access desired column. It can be used on either the right
/// (r-value) or the left (l-value) of an assignment statement. In debug builds,
/// function asserts if \a row is not in the range 0-1.
/// \see Matrix22::operator()(const unsigned,const unsigned)

template <typename T>
inline typename Matrix22<T>::RowAccessor22 Matrix22<T>::operator[] (
	const unsigned row)
{
	return RowAccessor22(this, row);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A ConstRowAccessor22 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// This overloaded operator returns ConstRowAccessor22 object that can be used
/// subsequently to access desired column. It can be used only on the right
/// (r-value) of an assignment statement. In debug builds, function asserts if
/// \a row is not in the range 0-1.
/// \see Matrix22::operator()(const unsigned,const unsigned) const

template <typename T>
inline typename Matrix22<T>::ConstRowAccessor22 Matrix22<T>::operator[] (
	const unsigned row) const
{
	return ConstRowAccessor22(this, row);
}

