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
//    matrix_ops.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains inlines for all operations related to matrices.
//------------------------------------------------------------------------------

/// \ingroup mtx22ops
/// \name matrix22 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 equals \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two matrix22 objects to see if they are
/// exactly the same .
/// \see operator!=(const matrix22&, const matrix22&)

template<typename T>
inline bool operator== (
    const matrix22<T>& m1,
    const matrix22<T>& m2)
{
    return (
        m1.data_[0] == m2.data_[0] &&
        m1.data_[1] == m2.data_[1] &&
        m1.data_[2] == m2.data_[2] &&
        m1.data_[3] == m2.data_[3]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 does not equal \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two matrix22 objects to see if they are
/// NOT exactly the same with zero tolerance.
/// \see operator==(const matrix22&, const matrix22&)

template<typename T>
inline bool operator!= (
    const matrix22<T>& m1,
    const matrix22<T>& m2)
{
    return (
        m1.data_[0] != m2.data_[0] ||
        m1.data_[1] != m2.data_[1] ||
        m1.data_[2] != m2.data_[2] ||
        m1.data_[3] != m2.data_[3]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 equals \a m2 within the tolerance; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \param eps The epsilon tolerance value.
/// \pre eps must be >= 0
/// \remarks
/// Compares \a m1 and \a m2 to see if they are the same within the given
/// epsilon tolerance.
/// \see operator==(const matrix22&, const matrix22&)

template<typename T>
inline bool is_equal(
    const matrix22<T>& m1,
    const matrix22<T>& m2,
    const T eps)
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (
        abs(m1.data_[0] - m2.data_[0]) <= eps &&
        abs(m1.data_[1] - m2.data_[1]) <= eps &&
        abs(m1.data_[2] - m2.data_[2]) <= eps &&
        abs(m1.data_[3] - m2.data_[3]) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a matrix that receives the result of the operation.
/// You can safely pass either \a lhs or \a rhs as \a r.
/// \param lhs Reference to the left-hand side matrix.
/// \param rhs Reference to the right-hand side matrix.
/// \remarks
/// This function puts results of the \a lhs and \a rhs matrix multiplication
/// into \a r and then returns reference to \a r. In this way, it can be used as
/// a parameter for another function. This is equivalent to the expression \a r
/// = \a lhs * \a rhs (where \a rhs is applied first).
/// \see operator*(const matrix22&, const matrix22&)

template<typename T>
inline matrix22<T>& mult(
    matrix22<T>& r,
    const matrix22<T>& lhs,
    const matrix22<T>& rhs)
{
    matrix22<T> ret;    // prevents aliasing
    ret.zero();

    ret(0, 0) += lhs(0, 0) * rhs(0, 0);
    ret(0, 0) += lhs(0, 1) * rhs(1, 0);

    ret(0, 1) += lhs(0, 0) * rhs(0, 1);
    ret(0, 1) += lhs(0, 1) * rhs(1, 1);

    ret(1, 0) += lhs(1, 0) * rhs(0, 0);
    ret(1, 0) += lhs(1, 1) * rhs(1, 0);

    ret(1, 1) += lhs(1, 0) * rhs(0, 1);
    ret(1, 1) += lhs(1, 1) * rhs(1, 1);

    return r = ret;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a matrix that receives the result of the operation.
/// \param operand Reference to a matrix.
/// \post \a r = \a operand * \a r
/// \remarks
/// This function puts results of the \a operand and \a r matrix multiplication
/// into \a r and then returns reference to \a r. In this way, it can be used as
/// a parameter for another function. This is equivalent to the expression \a r
/// = \a operand * \a r.
/// \see mult(matrix22<T>&,const matrix22&, const matrix22&),
/// postMult(matrix22<T>&,const matrix22<T>& operand)

template<typename T>
inline matrix22<T>& pre_mult(
    matrix22<T>& r,
    const matrix22<T>& operand)
{
    return mult(r, operand, r);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a matrix that receives the result of the operation.
/// \param operand Reference to a matrix.
/// \post \a r = \a r * \a operand
/// \remarks
/// This function puts results of the \a r and \a operand matrix multiplication
/// into \a r and then returns reference to \a r. In this way, it can be used as
/// a parameter for another function. This is equivalent to the expression \a r
/// = \a r * \a operand.
/// \see mult(matrix22<T>&,const matrix22&, const matrix22&),
/// preMult(matrix22<T>&,const matrix22<T>& operand)

template<typename T>
inline matrix22<T>& post_mult(
    matrix22<T>& r,
    const matrix22<T>& operand)
{
    return mult(r, r, operand);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Result of the operation.
/// \param lhs Reference to the left-hand side matrix.
/// \param rhs Reference to the right-hand side matrix.
/// \remarks
/// This overloaded binary operator multiplies \a rhs by \a lhs then returns the
/// result. This is equivalent to the expression \a r = \a lhs * \a rhs (where
/// \a rhs is applied first).
/// \see mult(matrix22<T>&,const matrix22&, const matrix22&)

template<typename T>
inline matrix22<T> operator* (
    const matrix22<T>& lhs,
    const matrix22<T>& rhs)
{
    matrix22<T> temp;
    return mult(temp, lhs, rhs);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a matrix that receives the result of the operation.
/// \param operand Reference to a matrix.
/// \post \a r = \a r * \a operand
/// \remarks
/// This overloaded binary operator multiplies \a r by \a operand and then
/// returns reference to \a r. In this way, it can be used as a parameter for
/// another function. This is equivalent to the expression \a r  = \a r *
/// \a operand.
/// \see postMult(matrix22<T>&,const matrix22<T>& operand)

template<typename T>
inline matrix22<T>& operator*= (
    matrix22<T>& r,
    const matrix22<T>& operand)
{
    return mult(r, r, operand);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after the operation.
/// \param r Reference to the matrix to be transposed.
/// \remarks
/// This function transposes the given matrix \a r in place and then returns
/// reference to \a r. In this way, it can be used as a parameter for another
/// function.
/// \see transpose(matrix22&, const matrix22&)

template<typename T>
inline matrix22<T>& transpose(
    matrix22<T>& r)
{
    std::swap(r.data_[1], r.data_[2]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after the operation.
/// \param r Reference to the matrix that receives the result of the operation.
/// \param s Reference to the source matrix.
/// \remarks
/// This function puts the result of transposing \a s into \a r and then returns
/// reference to \a r. In this way, it can be used as a parameter for another
/// function.
/// \see transpose(matrix22&)

template<typename T>
inline matrix22<T>& transpose(
    matrix22<T>& r,
    const matrix22<T>& s)
{
    r.data_[0] = s.data_[0]; r.data_[1] = s.data_[2];
    r.data_[2] = s.data_[1]; r.data_[3] = s.data_[3];
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The determinant of the matrix.
/// \param m Reference to the matrix used for the determinant calculation.
/// \remarks
/// This function computes the determinant of the \a m matrix. Determinant is
/// used for the calculation of the inverse of a matrix.
/// \see invert(matrix22&, const matrix22&)

template<typename T>
inline T determinant(
    const matrix22<T>& m)
{
    return ((m.data_[0]*m.data_[3]) - (m.data_[1]*m.data_[2]));
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after the operation.
/// \param r Reference to the matrix that receives the result of the operation.
/// \param s Reference to the source matrix.
/// \pre Only works with float types (e.g. matrix22<int> is not acceptable).
/// \remarks
/// This function puts the result of inverting \a s into \a r and then returns
/// reference to \a r. In this way, it can be used as a parameter for another
/// function.
/// \see invert(const matrix22&)

template<typename T>
inline matrix22<T>& invert(
    matrix22<T>& r,
    const matrix22<T>& s)
{
    T det = ((s.data_[0]*s.data_[3]) - (s.data_[1]*s.data_[2]));
    BOOST_ASSERT_MSG(abs(det) > SMALL, "not invertible!");
    T one_over_det = T(1) / det;
    r.data_[0] =  s.data_[3] * one_over_det;
    r.data_[1] = -s.data_[1] * one_over_det;
    r.data_[2] = -s.data_[2] * one_over_det;
    r.data_[3] =  s.data_[0] * one_over_det;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Result of the operation.
/// \param m Reference to the matrix to be inverted.
/// \pre Only works with float types (e.g. matrix22<int> is not acceptable).
/// \remarks
/// This function inverts the given matrix \a m and then returns the result. In
/// this way, it can be used as a parameter for another function.
/// \see invert(matrix22&, const matrix22&)

template<typename T>
inline matrix22<T> invert(
    const matrix22<T>& m)
{
    matrix22<T> r;
    return invert(r, m);
}
