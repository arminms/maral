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
// $Id$
//------------------------------------------------------------------------------
// Filename:
//    matrix.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains inlines for all matrix classes.
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
/// Sets this matrix to identity (every element is 0 except the matrix's
///  diagonal, whose elements are 1) then returns its reference. In this way, it
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
/// float data[] = { 1, 0, 0, 15 };
/// matrix22f mat;
/// mat.setTranspose(data);
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

