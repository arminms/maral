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
// Filename:
//    matrix.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation for all matrix classes.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// row_accessor22 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// Constructs a row_accessor22 object. In debug builds, function asserts if
/// \a row is not in the range 0-1.

template <typename T>
inline matrix22<T>::row_accessor22::row_accessor22(
    matrix22<T>* mat,
    const unsigned row)
:    m_(mat)
,    r_(row)
{
    BOOST_ASSERT_MSG(mat != nullptr, "null pointer!");
    BOOST_ASSERT_MSG(row < 2, "out or range!");
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
/// \see matrix22::operator[]

template <typename T>
inline T& matrix22<T>::row_accessor22::operator[] (
    const unsigned column)
{
    BOOST_ASSERT_MSG(column < 2, "out or range!");
    return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// const_row_accessor22 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// Constructs a const_row_accessor22 object. In debug builds, function asserts
/// if \a row is not in the range 0-1.

template <typename T>
inline matrix22<T>::const_row_accessor22::const_row_accessor22(
    const matrix22<T>* mat,
    const unsigned row)
:    m_(mat)
,    r_(row)
{
    BOOST_ASSERT_MSG(mat != nullptr, "null pointer!");
    BOOST_ASSERT_MSG(row < 2, "out of range!");
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
/// \see matrix22::operator[](const unsigned) const

template <typename T>
inline const T& matrix22<T>::const_row_accessor22::operator[] (
    const unsigned column) const
{
    BOOST_ASSERT_MSG(column < 2, "out or range!");
    return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// matrix22 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a matrix22 object (default constructor). For efficiency, no
/// initialization is performed which leaves matrix in an indeterminate state.
/// You may call matrix22::identity or matrix22::zero member functions later to
/// make an identity or zero matrix.
/// \see matrix22::identity, matrix22::zero

template <typename T>
inline matrix22<T>::matrix22()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \pre vals.size() > 4
/// \remarks
/// Constructs a matrix22 object from an \a initializer-list (\a
/// initializer-list constructor). In debug builds, function asserts if number
/// of elements in \a vals is more than 4. If number of elements in \a vals is
/// less than 4, the rest will be initialized to 0.
///
/// \code
/// matrix22f zero {}; // matrix with all elements set to zero
/// matrix22f iden {1.0f, 0.0f, 0.0f, 1.0f}; // identity matrix
/// \endcode

template <typename T>
inline matrix22<T>::matrix22(
    std::initializer_list<T> vals)
{
    BOOST_ASSERT_MSG(vals.size() <= 4, "out of range initializer list!");
    unsigned count = 0;
    for (auto it=vals.begin(); it != vals.end(); ++it)
        data_[count++] = *it;
    if (count < 4)
        for (register unsigned i = count; i < 4; ++i)
            data_[i] = T(0);
}

////////////////////////////////////////////////////////////////////////////////
/// \param m A matrix22 object that already exists.
/// \remarks
/// Constructs a matrix22 object from another one (copy constructor).

template <typename T>
inline matrix22<T>::matrix22(const matrix22<T>& m)
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
/// \return Reference to this matrix22 object.
/// \param m A matrix22 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source matrix22 \a m into
/// this matrix22.

template <typename T>
inline matrix22<T>& matrix22<T>::operator=(const matrix22<T>& m)
{
    if (this != &m)
    {
        data_[0] = m.data_[0]; data_[1] = m.data_[1];
        data_[2] = m.data_[2]; data_[3] = m.data_[3];
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// an identity matrix.
/// \remarks
/// Sets this matrix to identity (every element is 0 except the matrix's
/// diagonal, whose elements are 1) then returns its reference. In this way, it
/// can be used as a parameter for another function.

template <typename T>
inline matrix22<T>& matrix22<T>::identity()
{
    data_[0] = data_[3] = (T)1;
    data_[1] = data_[2] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// zero.
/// \remarks
/// Sets all elements of this matrix to zero then returns its reference. In this
/// way, it can be used as a parameter for another function.

template <typename T>
inline matrix22<T>& matrix22<T>::zero()
{
    data_[0] = data_[1] = data_[2] = data_[3] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of four arbitrary types.
/// \pre \a data_ptr is in the native format of the matrix22 class which is a
/// column major order, if not, then you might be able to use the
/// matrix22<T>::setTranspose function.
/// \remarks
/// This member function sets the matrix to the given data. It is useful to copy
/// matrix data from another math library. Normally this function is used when
/// you want to use an array to init the matrix (see code example).
/// \see matrix22::setTranspose

template <typename T>
inline void matrix22<T>::set(const T* data_ptr)
{
    BOOST_ASSERT_MSG(data_ptr, "null pointer!");
    data_[0] = data_ptr[0]; data_[1] = data_ptr[1];
    data_[2] = data_ptr[2]; data_[3] = data_ptr[3];
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of four arbitrary types.
/// \pre \a data_ptr is in the transpose (row major order) of the matrix22
/// native format which is a column major order.
/// \remarks
/// This member function sets the matrix to the transpose of the given data.
/// matrix22<T>::set() takes raw matrix data in column major order, this
/// function allows you to pass in row major order data. Normally this function
/// is used when you want to use an array to init the matrix (see code example).
///
/// \code
/// int data[] = { 1, 2, 3, 4 };
/// matrix22i mat;
/// mat.setTranspose(data); // becomes { 1, 3, 2, 4 }
/// \endcode
/// \see matrix22::set

template <typename T>
inline void matrix22<T>::set_transpose(const T* data_ptr)
{
    BOOST_ASSERT_MSG(data_ptr, "null pointer!");
    data_[0] = data_ptr[0]; data_[1] = data_ptr[2];
    data_[2] = data_ptr[1]; data_[3] = data_ptr[3];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the head of the matrix data.
/// \remarks
/// Gets a pointer to the matrix data.

template <typename T>
inline T* matrix22<T>::get_data()
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Constant pointer to the head of the matrix data.
/// \remarks
/// Gets a constant pointer to the matrix data.

template <typename T>
inline const T* matrix22<T>::get_data() const
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param idx The zero-based index of the component to access.
/// \pre idx < 4
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used on either the right (r-value) or the left (l-value) of an
/// assignment statement. In debug builds, function asserts if \a idx is not in
/// the range 0-3.

template <typename T>
inline T& matrix22<T>::operator() (
    const unsigned idx)
{
    BOOST_ASSERT_MSG(idx < 4, "out of range!");
    return data_[idx];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param idx The zero-based index of the component to access.
/// \pre idx < 4
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used only on the right (r-value) of an assignment statement. In debug
/// builds, function asserts if \a idx is not in the range 0-3.

template <typename T>
inline const T& matrix22<T>::operator() (
    const unsigned idx) const
{
    BOOST_ASSERT_MSG(idx < 4, "out of range!");
    return data_[idx];
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
/// \see matrix22::operator[]

template <typename T>
inline T& matrix22<T>::operator() (
    const unsigned row,
    const unsigned column)
{
    BOOST_ASSERT_MSG(row < 2, "row out of range!");
    BOOST_ASSERT_MSG(column < 2, "column out or range!");
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
/// \see matrix22::operator[](const unsigned) const

template <typename T>
inline const T& matrix22<T>::operator() (
    const unsigned row,
    const unsigned column) const
{
    BOOST_ASSERT_MSG(row < 2, "row out of range!");
    BOOST_ASSERT_MSG(column < 2, "column out of range!");
    return data_[(column<<1)+row];
}

////////////////////////////////////////////////////////////////////////////////
/// \return A row_accessor22 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// This overloaded operator returns row_accessor22 object that can be used
/// subsequently to access desired column. It can be used on either the right
/// (r-value) or the left (l-value) of an assignment statement. In debug builds,
/// function asserts if \a row is not in the range 0-1.
/// \see matrix22::operator()(const unsigned,const unsigned)

template <typename T>
inline typename matrix22<T>::row_accessor22 matrix22<T>::operator[] (
    const unsigned row)
{
    return row_accessor22(this, row);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A const_row_accessor22 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 2
/// \remarks
/// This overloaded operator returns const_row_accessor22 object that can be used
/// subsequently to access desired column. It can be used only on the right
/// (r-value) of an assignment statement. In debug builds, function asserts if
/// \a row is not in the range 0-1.
/// \see matrix22::operator()(const unsigned,const unsigned) const

template <typename T>
inline typename matrix22<T>::const_row_accessor22 matrix22<T>::operator[] (
    const unsigned row) const
{
    return const_row_accessor22(this, row);
}

////////////////////////////////////////////////////////////////////////////////
// row_accessor33 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 3
/// \remarks
/// Constructs a row_accessor33 object. In debug builds, function asserts if
/// \a row is not in the range 0-2.

template <typename T>
inline matrix33<T>::row_accessor33::row_accessor33(
    matrix33<T>* mat,
    const unsigned row)
:    m_(mat)
,    r_(row)
{
    BOOST_ASSERT_MSG(mat != nullptr, "null pointer!");
    BOOST_ASSERT_MSG(row < 3, "out or range!");
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param column The zero-based index of the column to access.
/// \pre column < 3
/// \remarks
/// This overloaded operator returns the value at the specified row (implicit)
/// and \a column. It can be used on either the right (r-value) or the left
/// (l-value) of an assignment statement. In debug builds, function asserts if
/// \a column is not in the range 0-2.
/// \see matrix33::operator[]

template <typename T>
inline T& matrix33<T>::row_accessor33::operator[] (
    const unsigned column)
{
    BOOST_ASSERT_MSG(column < 3, "out or range!");
    return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// const_row_accessor33 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 3
/// \remarks
/// Constructs a const_row_accessor33 object. In debug builds, function asserts
/// if \a row is not in the range 0-2.

template <typename T>
inline matrix33<T>::const_row_accessor33::const_row_accessor33(
    const matrix33<T>* mat,
    const unsigned row)
:    m_(mat)
,    r_(row)
{
    BOOST_ASSERT_MSG(mat != nullptr, "null pointer!");
    BOOST_ASSERT_MSG(row < 3, "out of range!");
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param column The zero-based index of the column to access.
/// \pre column < 3
/// \remarks
/// This overloaded operator returns the value at the specified row (implicit)
/// and \a column. It can be used only on the right (r-value) of an assignment
/// statement. In debug builds, function asserts if \a column is not in the
/// range 0-2.
/// \see matrix33::operator[](const unsigned) const

template <typename T>
inline const T& matrix33<T>::const_row_accessor33::operator[] (
    const unsigned column) const
{
    BOOST_ASSERT_MSG(column < 3, "out or range!");
    return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// matrix33 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a matrix33 object (default constructor). For efficiency, no
/// initialization is performed which leaves matrix in an indeterminate state.
/// You may call matrix33::identity or matrix33::zero member functions later to
/// make an identity or zero matrix.
/// \see matrix33::identity, matrix33::zero

template <typename T>
inline matrix33<T>::matrix33()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \pre vals.size() > 9
/// \remarks
/// Constructs a matrix33 object from an \a initializer-list (\a
/// initializer-list constructor). In debug builds, function asserts if number
/// of elements in \a vals is more than 9. If number of elements in \a vals is
/// less than 9, the rest will be initialized to 0.
///
/// \code
/// matrix33f zero {}; // matrix with all elements set to zero
/// matrix33f iden { 1.0f, 0.0f, 0.0f,
///                  0.0f, 1.0f, 0.0f,
///                  0.0f, 0.0f, 1.0f }; // identity matrix
/// \endcode

template <typename T>
inline matrix33<T>::matrix33(
    std::initializer_list<T> vals)
{
    BOOST_ASSERT_MSG(vals.size() <= 9, "out of range initializer list!");
    unsigned count = 0;
    for (auto it=vals.begin(); it != vals.end(); ++it)
        data_[count++] = *it;
    if (count < 9)
        for (register unsigned i = count; i < 9; ++i)
            data_[i] = T(0);
}

////////////////////////////////////////////////////////////////////////////////
/// \param m A matrix33 object that already exists.
/// \remarks
/// Constructs a matrix33 object from another one (copy constructor).

template <typename T>
inline matrix33<T>::matrix33(const matrix33<T>& m)
{
    if (this != &m)
    {
        data_[0] = m.data_[0]; data_[1] = m.data_[1]; data_[2] = m.data_[2];
        data_[3] = m.data_[3]; data_[4] = m.data_[4]; data_[5] = m.data_[5];
        data_[6] = m.data_[6]; data_[7] = m.data_[7]; data_[8] = m.data_[8];
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix33 object.
/// \param m A matrix33 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source matrix33 \a m into
/// this matrix33.

template <typename T>
inline matrix33<T>& matrix33<T>::operator=(const matrix33<T>& m)
{
    if (this != &m)
    {
        data_[0] = m.data_[0]; data_[1] = m.data_[1]; data_[2] = m.data_[2];
        data_[3] = m.data_[3]; data_[4] = m.data_[4]; data_[5] = m.data_[5];
        data_[6] = m.data_[6]; data_[7] = m.data_[7]; data_[8] = m.data_[8];
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// an identity matrix.
/// \remarks
/// Sets this matrix to identity (every element is 0 except the matrix's
/// diagonal, whose elements are 1) then returns its reference. In this way, it
/// can be used as a parameter for another function.

template <typename T>
inline matrix33<T>& matrix33<T>::identity()
{
    data_[8] = data_[4] = data_[0] = (T)1;
    data_[7] = data_[6] = data_[5] = data_[3] = data_[2] = data_[1] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// zero.
/// \remarks
/// Sets all elements of this matrix to zero then returns its reference. In this
/// way, it can be used as a parameter for another function.

template <typename T>
inline matrix33<T>& matrix33<T>::zero()
{
    data_[8] = data_[7] = data_[6] = data_[5] = data_[4] =
    data_[3] = data_[2] = data_[1] = data_[0] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of nine arbitrary types.
/// \pre \a data_ptr is in the native format of the matrix33 class which is a
/// column major order, if not, then you might be able to use the
/// matrix33<T>::setTranspose function.
/// \remarks
/// This member function sets the matrix to the given data. It is useful to copy
/// matrix data from another math library. Normally this function is used when
/// you want to use an array to init the matrix (see code example).
/// \see matrix33::setTranspose

template <typename T>
inline void matrix33<T>::set(const T* data_ptr)
{
    BOOST_ASSERT_MSG(data_ptr, "null pointer!");
    data_[0] = data_ptr[0]; data_[1] = data_ptr[1]; data_[2] = data_ptr[2];
    data_[3] = data_ptr[3]; data_[4] = data_ptr[4]; data_[5] = data_ptr[5];
    data_[6] = data_ptr[6]; data_[7] = data_ptr[7]; data_[8] = data_ptr[8];
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of nine arbitrary types.
/// \pre \a data_ptr is in the transpose (row major order) of the matrix33
/// native format which is a column major order.
/// \remarks
/// This member function sets the matrix to the transpose of the given data.
/// matrix33<T>::set() takes raw matrix data in column major order, this
/// function allows you to pass in row major order data. Normally this function
/// is used when you want to use an array to init the matrix (see code example).
///
/// \code
/// int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
/// matrix33i mat;
/// mat.setTranspose(data); // becomes { 1, 4, 7, 2, 5, 8, 3, 6, 9 }
/// \endcode
/// \see matrix33::set

template <typename T>
inline void matrix33<T>::set_transpose(const T* data_ptr)
{
    BOOST_ASSERT_MSG(data_ptr, "null pointer!");
    data_[0] = data_ptr[0]; data_[1] = data_ptr[3]; data_[2] = data_ptr[6];
    data_[3] = data_ptr[1]; data_[4] = data_ptr[4]; data_[5] = data_ptr[7];
    data_[6] = data_ptr[2]; data_[7] = data_ptr[5]; data_[8] = data_ptr[8];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the head of the matrix data.
/// \remarks
/// Gets a pointer to the matrix data.

template <typename T>
inline T* matrix33<T>::get_data()
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Constant pointer to the head of the matrix data.
/// \remarks
/// Gets a constant pointer to the matrix data.

template <typename T>
inline const T* matrix33<T>::get_data() const
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param idx The zero-based index of the component to access.
/// \pre idx < 9
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used on either the right (r-value) or the left (l-value) of an
/// assignment statement. In debug builds, function asserts if \a idx is not in
/// the range 0-8.

template <typename T>
inline T& matrix33<T>::operator() (
    const unsigned idx)
{
    BOOST_ASSERT_MSG(idx < 9, "out of range!");
    return data_[idx];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param idx The zero-based index of the component to access.
/// \pre idx < 9
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used only on the right (r-value) of an assignment statement. In debug
/// builds, function asserts if \a idx is not in the range 0-8.

template <typename T>
inline const T& matrix33<T>::operator() (
    const unsigned idx) const
{
    BOOST_ASSERT_MSG(idx < 9, "out of range!");
    return data_[idx];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) at the
/// specified \a row and \a column.
/// \param row The zero-based index of the row to access.
/// \param column The zero-based index of the column to access.
/// \pre row < 3
/// \pre column < 3
/// \remarks
/// This overloaded operator returns the value at the specified \a row and
/// \a column. It can be used on either the right (r-value) or the left (l-value)
/// of an assignment statement. In debug builds, function asserts if either
/// \a row or \a column are not in the range 0-2.
/// \see matrix33::operator[]

template <typename T>
inline T& matrix33<T>::operator() (
    const unsigned row,
    const unsigned column)
{
    BOOST_ASSERT_MSG(row < 3, "row out of range!");
    BOOST_ASSERT_MSG(column < 3, "column out or range!");
    return data_[((column<<1)+column)+row];

}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) at the
/// specified \a row and \a column.
/// \param row The zero-based index of the row to access.
/// \param column The zero-based index of the column to access.
/// \pre row < 3
/// \pre column < 3
/// \remarks
/// This overloaded operator returns the value at the specified \a row and
/// \a column. It can be used only on the right (r-value) of an assignment
/// statement. In debug builds, function asserts if either \a row or \a column
/// are not in the range 0-2.
/// \see matrix33::operator[](const unsigned) const

template <typename T>
inline const T& matrix33<T>::operator() (
    const unsigned row,
    const unsigned column) const
{
    BOOST_ASSERT_MSG(row < 3, "row out of range!");
    BOOST_ASSERT_MSG(column < 3, "column out of range!");
    return data_[((column<<1)+column)+row];
}

////////////////////////////////////////////////////////////////////////////////
/// \return A row_accessor33 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 3
/// \remarks
/// This overloaded operator returns row_accessor33 object that can be used
/// subsequently to access desired column. It can be used on either the right
/// (r-value) or the left (l-value) of an assignment statement. In debug builds,
/// function asserts if \a row is not in the range 0-2.
/// \see matrix33::operator()(const unsigned,const unsigned)

template <typename T>
inline typename matrix33<T>::row_accessor33 matrix33<T>::operator[] (
    const unsigned row)
{
    return row_accessor33(this, row);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A const_row_accessor33 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 3
/// \remarks
/// This overloaded operator returns const_row_accessor33 object that can be
/// used subsequently to access desired column. It can be used only on the right
/// (r-value) of an assignment statement. In debug builds, function asserts if
/// \a row is not in the range 0-2.
/// \see matrix33::operator()(const unsigned,const unsigned) const

template <typename T>
inline typename matrix33<T>::const_row_accessor33 matrix33<T>::operator[] (
    const unsigned row) const
{
    return const_row_accessor33(this, row);
}

////////////////////////////////////////////////////////////////////////////////
// row_accessor44 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 4
/// \remarks
/// Constructs a row_accessor44 object. In debug builds, function asserts if
/// \a row is not in the range 0-3.

template <typename T>
inline matrix44<T>::row_accessor44::row_accessor44(
    matrix44<T>* mat,
    const unsigned row)
:    m_(mat)
,    r_(row)
{
    BOOST_ASSERT_MSG(mat != nullptr, "null pointer!");
    BOOST_ASSERT_MSG(row < 4, "out or range!");
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param column The zero-based index of the column to access.
/// \pre column < 4
/// \remarks
/// This overloaded operator returns the value at the specified row (implicit)
/// and \a column. It can be used on either the right (r-value) or the left
/// (l-value) of an assignment statement. In debug builds, function asserts if
/// \a column is not in the range 0-3.
/// \see matrix44::operator[]

template <typename T>
inline T& matrix44<T>::row_accessor44::operator[] (
    const unsigned column)
{
    BOOST_ASSERT_MSG(column < 4, "out or range!");
    return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// const_row_accessor44 member functions

////////////////////////////////////////////////////////////////////////////////
/// \param mat Pointer to the matrix.
/// \param row The zero-based index of the row to access.
/// \pre row < 4
/// \remarks
/// Constructs a const_row_accessor44 object. In debug builds, function asserts
/// if \a row is not in the range 0-3.

template <typename T>
inline matrix44<T>::const_row_accessor44::const_row_accessor44(
    const matrix44<T>* mat,
    const unsigned row)
:    m_(mat)
,    r_(row)
{
    BOOST_ASSERT_MSG(mat != nullptr, "null pointer!");
    BOOST_ASSERT_MSG(row < 4, "out of range!");
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param column The zero-based index of the column to access.
/// \pre column < 4
/// \remarks
/// This overloaded operator returns the value at the specified row (implicit)
/// and \a column. It can be used only on the right (r-value) of an assignment
/// statement. In debug builds, function asserts if \a column is not in the
/// range 0-3.
/// \see matrix44::operator[](const unsigned) const

template <typename T>
inline const T& matrix44<T>::const_row_accessor44::operator[] (
    const unsigned column) const
{
    BOOST_ASSERT_MSG(column < 4, "out or range!");
    return (*m_)(r_, column);
}

////////////////////////////////////////////////////////////////////////////////
// matrix44 member functions

////////////////////////////////////////////////////////////////////////////////
/// \remarks
/// Constructs a matrix44 object (default constructor). For efficiency, no
/// initialization is performed which leaves matrix in an indeterminate state.
/// You may call matrix44::identity or matrix44::zero member functions later to
/// make an identity or zero matrix.
/// \see matrix44::identity, matrix44::zero

template <typename T>
inline matrix44<T>::matrix44()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \pre vals.size() > 16
/// \remarks
/// Constructs a matrix44 object from an \a initializer-list (\a
/// initializer-list constructor). In debug builds, function asserts if number
/// of elements in \a vals is more than 16. If number of elements in \a vals is
/// less than 16, the rest will be initialized to 0.
///
/// \code
/// matrix44f zero {}; // matrix with all elements set to zero
/// matrix44f iden { 1.0f, 0.0f, 0.0f, 0.0f
///                  0.0f, 1.0f, 0.0f, 0.0f
///                  0.0f, 0.0f, 1.0f, 0.0f
///                  0.0f, 0.0f, 0.0f, 1.0f }; // identity matrix
/// \endcode

template <typename T>
inline matrix44<T>::matrix44(
    std::initializer_list<T> vals)
{
    BOOST_ASSERT_MSG(vals.size() <= 16, "out of range initializer list!");
    unsigned count = 0;
    for (auto val : vals)
        data_[count++] = val;
    if (count < 16)
        for (register unsigned i = count; i < 16; ++i)
            data_[i] = T(0);
}

////////////////////////////////////////////////////////////////////////////////
/// \param m A matrix44 object that already exists.
/// \remarks
/// Constructs a matrix44 object from another one (copy constructor).

template <typename T>
inline matrix44<T>::matrix44(const matrix44<T>& m)
{
    if (this != &m)
    {
        data_ [0] = m.data_ [0]; data_ [1] = m.data_ [1];
        data_ [2] = m.data_ [2]; data_ [3] = m.data_ [3];
        data_ [4] = m.data_ [4]; data_ [5] = m.data_ [5];
        data_ [6] = m.data_ [6]; data_ [7] = m.data_ [7];
        data_ [8] = m.data_ [8]; data_ [9] = m.data_ [9];
        data_[10] = m.data_[10]; data_[11] = m.data_[11];
        data_[12] = m.data_[12]; data_[13] = m.data_[13];
        data_[14] = m.data_[14]; data_[15] = m.data_[15];
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix44 object.
/// \param m A matrix44 object that already exists.
/// \remarks
/// The overloaded assignment operator copies the source matrix44 \a m into
/// this matrix44.

template <typename T>
inline matrix44<T>& matrix44<T>::operator=(const matrix44<T>& m)
{
    if (this != &m)
    {
        data_ [0] = m.data_ [0]; data_ [1] = m.data_ [1];
        data_ [2] = m.data_ [2]; data_ [3] = m.data_ [3];
        data_ [4] = m.data_ [4]; data_ [5] = m.data_ [5];
        data_ [6] = m.data_ [6]; data_ [7] = m.data_ [7];
        data_ [8] = m.data_ [8]; data_ [9] = m.data_ [9];
        data_[10] = m.data_[10]; data_[11] = m.data_[11];
        data_[12] = m.data_[12]; data_[13] = m.data_[13];
        data_[14] = m.data_[14]; data_[15] = m.data_[15];
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// an identity matrix.
/// \remarks
/// Sets this matrix to identity (every element is 0 except the matrix's
/// diagonal, whose elements are 1) then returns its reference. In this way, it
/// can be used as a parameter for another function.

template <typename T>
inline matrix44<T>& matrix44<T>::identity()
{
    data_[15] = data_[10] = data_[5] = data_[0] = (T)1;
    data_[14] = data_[13] = data_[12] = data_[11] = data_[9] = data_[8] =
    data_ [7] = data_ [6] = data_ [4] = data_ [3] = data_[2] = data_[1] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to this matrix after all components were initialized to
/// zero.
/// \remarks
/// Sets all elements of this matrix to zero then returns its reference. In this
/// way, it can be used as a parameter for another function.

template <typename T>
inline matrix44<T>& matrix44<T>::zero()
{
    data_[15] = data_[14] = data_[13] = data_[12] = data_[11] = data_[10] =
    data_ [9] = data_ [8] = data_ [7] = data_ [6] = data_ [5] = data_ [4] =
    data_ [3] = data_ [2] = data_ [1] = data_ [0] = (T)0;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of sixteen arbitrary types.
/// \pre \a data_ptr is in the native format of the matrix44 class which is a
/// column major order, if not, then you might be able to use the
/// matrix44<T>::setTranspose function.
/// \remarks
/// This member function sets the matrix to the given data. It is useful to copy
/// matrix data from another math library. Normally this function is used when
/// you want to use an array to init the matrix (see code example).
/// \see matrix44::setTranspose

template <typename T>
inline void matrix44<T>::set(const T* data_ptr)
{
    BOOST_ASSERT_MSG(data_ptr, "null pointer!");
    data_ [0] = data_ptr [0]; data_ [1] = data_ptr [1];
    data_ [2] = data_ptr [2]; data_ [3] = data_ptr [3];
    data_ [4] = data_ptr [4]; data_ [5] = data_ptr [5];
    data_ [6] = data_ptr [6]; data_ [7] = data_ptr [7];
    data_ [8] = data_ptr [8]; data_ [9] = data_ptr [9];
    data_[10] = data_ptr[10]; data_[11] = data_ptr[11];
    data_[12] = data_ptr[12]; data_[13] = data_ptr[13];
    data_[14] = data_ptr[14]; data_[15] = data_ptr[15];
}

////////////////////////////////////////////////////////////////////////////////
/// \param data_ptr Pointer to an array of sixteen arbitrary types.
/// \pre \a data_ptr is in the transpose (row major order) of the matrix44
/// native format which is a column major order.
/// \remarks
/// This member function sets the matrix to the transpose of the given data.
/// matrix44<T>::set() takes raw matrix data in column major order, this
/// function allows you to pass in row major order data. Normally this function
/// is used when you want to use an array to init the matrix (see code example).
///
/// \code
/// int data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
/// matrix44i mat;
/// mat.setTranspose(data); // becomes {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16}
/// \endcode
/// \see matrix44::set

template <typename T>
inline void matrix44<T>::set_transpose(const T* data_ptr)
{
    BOOST_ASSERT_MSG(data_ptr, "null pointer!");
    data_ [0] = data_ptr [0]; data_ [1] = data_ptr [4];
    data_ [2] = data_ptr [8]; data_ [3] = data_ptr[12];
    data_ [4] = data_ptr [1]; data_ [5] = data_ptr [5];
    data_ [6] = data_ptr [9]; data_ [7] = data_ptr[13];
    data_ [8] = data_ptr [2]; data_ [9] = data_ptr [6];
    data_[10] = data_ptr[10]; data_[11] = data_ptr[14];
    data_[12] = data_ptr [3]; data_[13] = data_ptr [7];
    data_[14] = data_ptr[11]; data_[15] = data_ptr[15];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Pointer to the head of the matrix data.
/// \remarks
/// Gets a pointer to the matrix data.

template <typename T>
inline T* matrix44<T>::get_data()
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Constant pointer to the head of the matrix data.
/// \remarks
/// Gets a constant pointer to the matrix data.

template <typename T>
inline const T* matrix44<T>::get_data() const
{
    return data_;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param idx The zero-based index of the component to access.
/// \pre idx < 16
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used on either the right (r-value) or the left (l-value) of an
/// assignment statement. In debug builds, function asserts if \a idx is not in
/// the range 0-15.

template <typename T>
inline T& matrix44<T>::operator() (
    const unsigned idx)
{
    BOOST_ASSERT_MSG(idx < 16, "out of range!");
    return data_[idx];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) containing
/// specified component.
/// \param idx The zero-based index of the component to access.
/// \pre idx < 9
/// \remarks
/// This overloaded operator returns the value of the specified component. It
/// can be used only on the right (r-value) of an assignment statement. In debug
/// builds, function asserts if \a idx is not in the range 0-15.

template <typename T>
inline const T& matrix44<T>::operator() (
    const unsigned idx) const
{
    BOOST_ASSERT_MSG(idx < 16, "out of range!");
    return data_[idx];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) at the
/// specified \a row and \a column.
/// \param row The zero-based index of the row to access.
/// \param column The zero-based index of the column to access.
/// \pre row < 4
/// \pre column < 4
/// \remarks
/// This overloaded operator returns the value at the specified \a row and
/// \a column. It can be used on either the right (r-value) or the left (l-value)
/// of an assignment statement. In debug builds, function asserts if either
/// \a row or \a column are not in the range 0-3.
/// \see matrix44::operator[]

template <typename T>
inline T& matrix44<T>::operator() (
    const unsigned row,
    const unsigned column)
{
    BOOST_ASSERT_MSG(row < 4, "row out of range!");
    BOOST_ASSERT_MSG(column < 4, "column out or range!");
    return data_[(column<<2)+row];
}

////////////////////////////////////////////////////////////////////////////////
/// \return Reference to an arbitrary type (int, float, double, ...) at the
/// specified \a row and \a column.
/// \param row The zero-based index of the row to access.
/// \param column The zero-based index of the column to access.
/// \pre row < 4
/// \pre column < 4
/// \remarks
/// This overloaded operator returns the value at the specified \a row and
/// \a column. It can be used only on the right (r-value) of an assignment
/// statement. In debug builds, function asserts if either \a row or \a column
/// are not in the range 0-3.
/// \see matrix44::operator[](const unsigned) const

template <typename T>
inline const T& matrix44<T>::operator() (
    const unsigned row,
    const unsigned column) const
{
    BOOST_ASSERT_MSG(row < 4, "row out of range!");
    BOOST_ASSERT_MSG(column < 4, "column out of range!");
    return data_[(column<<2)+row];
}

////////////////////////////////////////////////////////////////////////////////
/// \return A row_accessor44 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 4
/// \remarks
/// This overloaded operator returns row_accessor44 object that can be used
/// subsequently to access desired column. It can be used on either the right
/// (r-value) or the left (l-value) of an assignment statement. In debug builds,
/// function asserts if \a row is not in the range 0-3.
/// \see matrix44::operator()(const unsigned,const unsigned)

template <typename T>
inline typename matrix44<T>::row_accessor44 matrix44<T>::operator[] (
    const unsigned row)
{
    return row_accessor44(this, row);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A const_row_accessor44 object that can be used to access columns.
/// \param row The zero-based index of the row to access.
/// \pre row < 4
/// \remarks
/// This overloaded operator returns const_row_accessor44 object that can be
/// used subsequently to access desired column. It can be used only on the right
/// (r-value) of an assignment statement. In debug builds, function asserts if
/// \a row is not in the range 0-3.
/// \see matrix44::operator()(const unsigned,const unsigned) const

template <typename T>
inline typename matrix44<T>::const_row_accessor44 matrix44<T>::operator[] (
    const unsigned row) const
{
    return const_row_accessor44(this, row);
}
