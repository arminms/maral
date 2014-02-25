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
/// \file matrix.hpp
/// \brief Include file for all classes representing matrices.
///
/// \b matrix.hpp is the include file for matrix22f, matrix22d, matrix33f,
/// matrix33d, matrix44f and matrix44f classes.

#ifndef MARAL_MTL_MATRIX_HPP_INCLUDED_
#define MARAL_MTL_MATRIX_HPP_INCLUDED_

namespace maral { namespace mtl {

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 2x2 matrix (ordered in memory by column).
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// matrix22 class abstracts a 2x2 matrix. To be compatible with \a OpenGL and
/// efficency, elements are stored in column major order (in opposed to row
/// major C/C++ ordering of arrays) as 4 consecutive datatypes. It is templated
/// on the component datatype.
/// \see matrix22i, matrix22f, matrix22d
/// \author Armin Madadkar Sobhani

template <typename T>
class matrix22
{
public:

    /// \brief Helper nested class for matrix22::operator[].
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class row_accessor22
    {
    public:
        row_accessor22(matrix22<T>* mat, const unsigned row);

        T& operator[](const unsigned column);

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix22 object set by constructor
        matrix22<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by row_accessor22::operator[]
        unsigned r_;
    };

    /// \brief Helper nested class for matrix22::operator[] const.
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class const_row_accessor22
    {
    public:
        const_row_accessor22(const matrix22<T>* mat, const unsigned row);

        const T& operator[](const unsigned column) const;

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix22 object set by constructor
        const matrix22<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by const_row_accessor22::operator[]
        unsigned r_;
    };

/// \name Construction
//@{
    matrix22();
    matrix22(std::initializer_list<T> vals);

    // Copy constructor
    matrix22(const matrix22<T>& m);

    // Assignment method
    matrix22<T>& operator=(const matrix22<T>& m);
//@}

/// \name Attributes
//@{
    matrix22<T>& identity();
    matrix22<T>& zero();

    void set(const T* data_ptr);
    void set_transpose(const T* data_ptr);

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator() (const unsigned idx);
    const T& operator() (const unsigned idx) const;

    T& operator() (const unsigned row, const unsigned column);
    const T& operator() (const unsigned row, const unsigned column) const;

    row_accessor22 operator[] (const unsigned row);
    const_row_accessor22 operator[] (const unsigned row) const;
//@}

// Implementation
private:
    /// \brief Matrix's data in column major order
    ///
    /// Matrix's data in column major order as four consecutive values in
    /// memory. As it is a private member, use
    /// matrix22::operator()(const unsigned),
    /// matrix22::operator()(const unsigned,const unsigned)
    /// or matrix22::operator[] instead of direct access.
    T data_[4];
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 3x3 matrix (ordered in memory by column).
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// matrix33 class abstracts a 3x3 matrix. To be compatible with \a OpenGL and
/// efficency, elements are stored in column major order (in opposed to row
/// major C/C++ ordering of arrays) as 9 consecutive datatypes. It is templated
/// on the component datatype.
/// \see matrix33i, matrix33f, matrix33d
/// \author Armin Madadkar Sobhani

template <typename T>
class matrix33
{
public:

    /// \brief Helper nested class for matrix33::operator[].
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class row_accessor33
    {
    public:
        row_accessor33(matrix33<T>* mat, const unsigned row);

        T& operator[](const unsigned column);

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix33 object set by constructor
        matrix33<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by row_accessor33::operator[]
        unsigned r_;
    };

    /// \brief Helper nested class for matrix33::operator[] const.
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class const_row_accessor33
    {
    public:
        const_row_accessor33(const matrix33<T>* mat, const unsigned row);

        const T& operator[](const unsigned column) const;

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix33 object set by constructor
        const matrix33<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by const_row_accessor33::operator[]
        unsigned r_;
    };

/// \name Construction
//@{
    matrix33();
    matrix33(std::initializer_list<T> vals);

    // Copy constructor
    matrix33(const matrix33<T>& m);

    // Assignment method
    matrix33<T>& operator=(const matrix33<T>& m);
//@}

/// \name Attributes
//@{
    matrix33<T>& identity();
    matrix33<T>& zero();

    void set(const T* data_ptr);
    void set_transpose(const T* data_ptr);

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator() (const unsigned idx);
    const T& operator() (const unsigned idx) const;

    T& operator() (const unsigned row, const unsigned column);
    const T& operator() (const unsigned row, const unsigned column) const;

    row_accessor33 operator[] (const unsigned row);
    const_row_accessor33 operator[] (const unsigned row) const;
//@}

// Implementation
private:
    /// \brief Matrix's data in column major order
    ///
    /// Matrix's data in column major order as four consecutive values in
    /// memory. As it is a private member, use
    /// matrix33::operator()(const unsigned),
    /// matrix33::operator()(const unsigned,const unsigned)
    /// or matrix33::operator[] instead of direct access.
    T data_[9];
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstracts a 4x4 matrix (ordered in memory by column).
///
/// \param T Type of the elements stored (e.g. int, float, double, ...).
/// \remarks
/// matrix44 class abstracts a 4x4 matrix. To be compatible with \a OpenGL and
/// efficency, elements are stored in column major order (in opposed to row
/// major C/C++ ordering of arrays) as 16 consecutive datatypes. It is templated
/// on the component datatype.
/// \see matrix44i, matrix44f, matrix44d
/// \author Armin Madadkar Sobhani

template <typename T>
class matrix44
{
public:

    /// \brief Helper nested class for matrix44::operator[].
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class row_accessor44
    {
    public:
        row_accessor44(matrix44<T>* mat, const unsigned row);

        T& operator[](const unsigned column);

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix44 object set by constructor
        matrix44<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by row_accessor44::operator[]
        unsigned r_;
    };

    /// \brief Helper nested class for matrix44::operator[] const.
    ///
    /// \remarks
    /// This nested class encapsulates the row that the user is accessing and
    /// implements a new operator[] that passes the column to use.

    class const_row_accessor44
    {
    public:
        const_row_accessor44(const matrix44<T>* mat, const unsigned row);

        const T& operator[](const unsigned column) const;

        /// \brief Pointer to the matrix
        ///
        /// Pointer to a matrix44 object set by constructor
        const matrix44<T>* m_;

        /// \brief The row being accessed
        ///
        /// The row being accessed set by constructor that can be used later
        /// by const_row_accessor44::operator[]
        unsigned r_;
    };

/// \name Construction
//@{
    matrix44();
    matrix44(std::initializer_list<T> vals);

    // Copy constructor
    matrix44(const matrix44<T>& m);

    // Assignment method
    matrix44<T>& operator=(const matrix44<T>& m);
//@}

/// \name Attributes
//@{
    matrix44<T>& identity();
    matrix44<T>& zero();

    void set(const T* data_ptr);
    void set_transpose(const T* data_ptr);

    T* get_data();
    const T* get_data() const;
//@}

/// \name Operators
//@{
    T& operator() (const unsigned idx);
    const T& operator() (const unsigned idx) const;

    T& operator() (const unsigned row, const unsigned column);
    const T& operator() (const unsigned row, const unsigned column) const;

    row_accessor44 operator[] (const unsigned row);
    const_row_accessor44 operator[] (const unsigned row) const;
//@}

// Implementation
private:
    /// \brief Matrix's data in column major order
    ///
    /// Matrix's data in column major order as four consecutive values in
    /// memory. As it is a private member, use
    /// matrix44::operator()(const unsigned),
    /// matrix44::operator()(const unsigned,const unsigned)
    /// or matrix44::operator[] instead of direct access.
    T data_[16];
};

////////////////////////////////////////////////////////////////////////////////
// Helper types

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 signed integers
///
/// Use matrix22i to define a 2x2 matrix composed of 4 signed integer
/// components. It has all the features of matrix22, i.e. the member functions
/// of matrix22i are similar to the member functions of matrix22 class. So, you
/// can use the matrix22 reference documentation: Wherever you see a \a T type,
/// substitute it to \a int.

typedef matrix22<int> matrix22i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 floats
///
/// Use matrix22f to define a 2x2 matrix composed of 4 float components. It has
/// all the features of matrix22, i.e. the member functions of matrix22f are
/// similar to the member functions of matrix22 class. So, you can use the
/// matrix22 reference documentation: Wherever you see a \a T type, substitute
/// it to \a float.

typedef matrix22<float> matrix22f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 2x2 matrix composed of 4 double
///
/// Use matrix22d to define a 2x2 matrix composed of 4 double components. It has
/// all the features of matrix22, i.e. the member functions of matrix22d are
/// similar to the member functions of matrix22 class. So, you can use the
/// matrix22 reference documentation: Wherever you see a \a T type, substitute
/// it to \a double.

typedef matrix22<double> matrix22d;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3x3 matrix composed of 9 signed integers
///
/// Use matrix33i to define a 3x3 matrix composed of 9 signed integer
/// components. It has all the features of matrix33, i.e. the member functions
/// of matrix33i are similar to the member functions of matrix33 class. So, you
/// can use the matrix33 reference documentation: Wherever you see a \a T type,
/// substitute it to \a int.

typedef matrix33<int> matrix33i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3x3 matrix composed of 9 floats
///
/// Use matrix33f to define a 3x3 matrix composed of 9 float components. It has
/// all the features of matrix33, i.e. the member functions of matrix33f are
/// similar to the member functions of matrix33 class. So, you can use the
/// matrix33 reference documentation: Wherever you see a \a T type, substitute
/// it to \a float.

typedef matrix33<float> matrix33f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 3x3 matrix composed of 9 double
///
/// Use matrix33d to define a 3x3 matrix composed of 9 double components. It has
/// all the features of matrix33, i.e. the member functions of matrix33d are
/// similar to the member functions of matrix33 class. So, you can use the
/// matrix33 reference documentation: Wherever you see a \a T type, substitute
/// it to \a double.

typedef matrix33<double> matrix33d;

////////////////////////////////////////////////////////////////////////////////
/// \brief 4x4 matrix composed of 16 signed integers
///
/// Use matrix44i to define a 4x4 matrix composed of 16 signed integer
/// components. It has all the features of matrix44, i.e. the member functions
/// of matrix44i are similar to the member functions of matrix44 class. So, you
/// can use the matrix44 reference documentation: Wherever you see a \a T type,
/// substitute it to \a int.

typedef matrix44<int> matrix44i;

////////////////////////////////////////////////////////////////////////////////
/// \brief 4x4 matrix composed of 16 floats
///
/// Use matrix44f to define a 4x4 matrix composed of 16 float components. It has
/// all the features of matrix44, i.e. the member functions of matrix44f are
/// similar to the member functions of matrix44 class. So, you can use the
/// matrix44 reference documentation: Wherever you see a \a T type, substitute
/// it to \a float.

typedef matrix44<float> matrix44f;

////////////////////////////////////////////////////////////////////////////////
/// \brief 4x4 matrix composed of 16 double
///
/// Use matrix44d to define a 4x4 matrix composed of 16 double components. It
/// has all the features of matrix44, i.e. the member functions of matrix44d are
/// similar to the member functions of matrix44 class. So, you can use the
/// matrix44 reference documentation: Wherever you see a \a T type, substitute
/// it to \a double.

typedef matrix44<double> matrix44d;

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include "matrix.ipp"

}}    // namespaces

#endif    // MARAL_MTL_MATRIX_HPP_INCLUDED_

