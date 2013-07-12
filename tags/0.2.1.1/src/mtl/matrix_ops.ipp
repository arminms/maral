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

    ret.data_[0] += lhs.data_[0] * rhs.data_[0];
    ret.data_[0] += lhs.data_[2] * rhs.data_[1];

    ret.data_[1] += lhs.data_[1] * rhs.data_[0];
    ret.data_[1] += lhs.data_[3] * rhs.data_[1];

    ret.data_[2] += lhs.data_[0] * rhs.data_[2];
    ret.data_[2] += lhs.data_[2] * rhs.data_[3];

    ret.data_[3] += lhs.data_[1] * rhs.data_[2];
    ret.data_[3] += lhs.data_[3] * rhs.data_[3];

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

/// @}

/// \ingroup mtx33ops
/// \name matrix33 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 equals \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two matrix33 objects to see if they are
/// exactly the same .
/// \see operator!=(const matrix33&, const matrix33&)

template<typename T>
inline bool operator== (
    const matrix33<T>& m1,
    const matrix33<T>& m2)
{
    return (
        m1.data_[0] == m2.data_[0] &&
        m1.data_[1] == m2.data_[1] &&
        m1.data_[2] == m2.data_[2] &&
        m1.data_[3] == m2.data_[3] &&
        m1.data_[4] == m2.data_[4] &&
        m1.data_[5] == m2.data_[5] &&
        m1.data_[6] == m2.data_[6] &&
        m1.data_[7] == m2.data_[7] &&
        m1.data_[8] == m2.data_[8]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 does not equal \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two matrix33 objects to see if they are
/// NOT exactly the same with zero tolerance.
/// \see operator==(const matrix33&, const matrix33&)

template<typename T>
inline bool operator!= (
    const matrix33<T>& m1,
    const matrix33<T>& m2)
{
    return (
        m1.data_[0] != m2.data_[0] ||
        m1.data_[1] != m2.data_[1] ||
        m1.data_[2] != m2.data_[2] ||
        m1.data_[3] != m2.data_[3] ||
        m1.data_[4] != m2.data_[4] ||
        m1.data_[5] != m2.data_[5] ||
        m1.data_[6] != m2.data_[6] ||
        m1.data_[7] != m2.data_[7] ||
        m1.data_[8] != m2.data_[8]);
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
/// \see operator==(const matrix33&, const matrix33&)

template<typename T>
inline bool is_equal(
    const matrix33<T>& m1,
    const matrix33<T>& m2,
    const T eps)
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (
        abs(m1.data_[0] - m2.data_[0]) <= eps &&
        abs(m1.data_[1] - m2.data_[1]) <= eps &&
        abs(m1.data_[2] - m2.data_[2]) <= eps &&
        abs(m1.data_[3] - m2.data_[3]) <= eps &&
        abs(m1.data_[4] - m2.data_[4]) <= eps &&
        abs(m1.data_[5] - m2.data_[5]) <= eps &&
        abs(m1.data_[6] - m2.data_[6]) <= eps &&
        abs(m1.data_[7] - m2.data_[7]) <= eps &&
        abs(m1.data_[8] - m2.data_[8]) <= eps);
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
/// \see operator*(const matrix33&, const matrix33&)

template<typename T>
inline matrix33<T>& mult(
    matrix33<T>& r,
    const matrix33<T>& lhs,
    const matrix33<T>& rhs)
{
    matrix33<T> ret;    // prevents aliasing
    ret.zero();

    ret.data_[0] += lhs.data_[0] * rhs.data_[0];
    ret.data_[0] += lhs.data_[3] * rhs.data_[1];
    ret.data_[0] += lhs.data_[6] * rhs.data_[2];

    ret.data_[1] += lhs.data_[1] * rhs.data_[0];
    ret.data_[1] += lhs.data_[4] * rhs.data_[1];
    ret.data_[1] += lhs.data_[7] * rhs.data_[2];

    ret.data_[2] += lhs.data_[2] * rhs.data_[0];
    ret.data_[2] += lhs.data_[5] * rhs.data_[1];
    ret.data_[2] += lhs.data_[8] * rhs.data_[2];

    ret.data_[3] += lhs.data_[0] * rhs.data_[3];
    ret.data_[3] += lhs.data_[3] * rhs.data_[4];
    ret.data_[3] += lhs.data_[6] * rhs.data_[5];

    ret.data_[4] += lhs.data_[1] * rhs.data_[3];
    ret.data_[4] += lhs.data_[4] * rhs.data_[4];
    ret.data_[4] += lhs.data_[7] * rhs.data_[5];

    ret.data_[5] += lhs.data_[2] * rhs.data_[3];
    ret.data_[5] += lhs.data_[5] * rhs.data_[4];
    ret.data_[5] += lhs.data_[8] * rhs.data_[5];

    ret.data_[6] += lhs.data_[0] * rhs.data_[6];
    ret.data_[6] += lhs.data_[3] * rhs.data_[7];
    ret.data_[6] += lhs.data_[6] * rhs.data_[8];

    ret.data_[7] += lhs.data_[1] * rhs.data_[6];
    ret.data_[7] += lhs.data_[4] * rhs.data_[7];
    ret.data_[7] += lhs.data_[7] * rhs.data_[8];

    ret.data_[8] += lhs.data_[2] * rhs.data_[6];
    ret.data_[8] += lhs.data_[5] * rhs.data_[7];
    ret.data_[8] += lhs.data_[8] * rhs.data_[8];

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
/// \see mult(matrix33<T>&,const matrix33&, const matrix33&),
/// postMult(matrix33<T>&,const matrix33<T>& operand)

template<typename T>
inline matrix33<T>& pre_mult(
    matrix33<T>& r,
    const matrix33<T>& operand)
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
/// \see mult(matrix33<T>&,const matrix33&, const matrix33&),
/// preMult(matrix33<T>&,const matrix33<T>& operand)

template<typename T>
inline matrix33<T>& post_mult(
    matrix33<T>& r,
    const matrix33<T>& operand)
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
/// \see mult(matrix33<T>&,const matrix33&, const matrix33&)

template<typename T>
inline matrix33<T> operator* (
    const matrix33<T>& lhs,
    const matrix33<T>& rhs)
{
    matrix33<T> temp;
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
/// \see postMult(matrix33<T>&,const matrix33<T>& operand)

template<typename T>
inline matrix33<T>& operator*= (
    matrix33<T>& r,
    const matrix33<T>& operand)
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
/// \see transpose(matrix33&, const matrix33&)

template<typename T>
inline matrix33<T>& transpose(
    matrix33<T>& r)
{
    std::swap(r.data_[1], r.data_[3]);
    std::swap(r.data_[2], r.data_[6]);
    std::swap(r.data_[5], r.data_[7]);
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
/// \see transpose(matrix33&)

template<typename T>
inline matrix33<T>& transpose(
    matrix33<T>& r,
    const matrix33<T>& s)
{
    r.data_[0] = s.data_[0]; r.data_[1] = s.data_[3]; r.data_[2] = s.data_[6];
    r.data_[3] = s.data_[1]; r.data_[4] = s.data_[4]; r.data_[5] = s.data_[7];
    r.data_[6] = s.data_[2]; r.data_[7] = s.data_[5]; r.data_[8] = s.data_[8];
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The determinant of the matrix.
/// \param m Reference to the matrix used for the determinant calculation.
/// \remarks
/// This function computes the determinant of the \a m matrix. Determinant is
/// used for the calculation of the inverse of a matrix.
/// \see invert(matrix33&, const matrix33&)

template<typename T>
inline T determinant(
    const matrix33<T>& m)
{
    return ((((m.data_[3]*m.data_[7]) - (m.data_[6]*m.data_[4])) * m.data_[2]) +
            (((m.data_[6]*m.data_[1]) - (m.data_[0]*m.data_[7])) * m.data_[5]) +
            (((m.data_[0]*m.data_[4]) - (m.data_[3]*m.data_[1])) * m.data_[8]));
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after the operation.
/// \param r Reference to the matrix that receives the result of the operation.
/// \param s Reference to the source matrix.
/// \pre Only works with float types (e.g. matrix33<int> is not acceptable).
/// \remarks
/// This function puts the result of inverting \a s into \a r and then returns
/// reference to \a r. In this way, it can be used as a parameter for another
/// function. It uses the \a classical \a adjoint method to compute the inverse.
/// \see invert(const matrix33&)

template<typename T>
inline matrix33<T>& invert(
    matrix33<T>& r,
    const matrix33<T>& s)
{
    T det = determinant(s);
    BOOST_ASSERT_MSG(abs(det) > SMALL, "not invertible!");
    T one_over_det = T(1) / det;
    r.data_[0] = ((s.data_[4]*s.data_[8])-(s.data_[7]*s.data_[5]))*one_over_det;
    r.data_[1] = ((s.data_[7]*s.data_[2])-(s.data_[1]*s.data_[8]))*one_over_det;
    r.data_[2] = ((s.data_[1]*s.data_[5])-(s.data_[4]*s.data_[2]))*one_over_det;
    r.data_[3] = ((s.data_[6]*s.data_[5])-(s.data_[3]*s.data_[8]))*one_over_det;
    r.data_[4] = ((s.data_[0]*s.data_[8])-(s.data_[6]*s.data_[2]))*one_over_det;
    r.data_[5] = ((s.data_[3]*s.data_[2])-(s.data_[0]*s.data_[5]))*one_over_det;
    r.data_[6] = ((s.data_[3]*s.data_[7])-(s.data_[6]*s.data_[4]))*one_over_det;
    r.data_[7] = ((s.data_[6]*s.data_[1])-(s.data_[0]*s.data_[7]))*one_over_det;
    r.data_[8] = ((s.data_[0]*s.data_[4])-(s.data_[3]*s.data_[1]))*one_over_det;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Result of the operation.
/// \param m Reference to the matrix to be inverted.
/// \pre Only works with float types (e.g. matrix33<int> is not acceptable).
/// \remarks
/// This function inverts the given matrix \a m and then returns the result. In
/// this way, it can be used as a parameter for another function. It uses the \a
/// classical \a adjoint method to compute the inverse.
/// \see invert(matrix33&, const matrix33&)

template<typename T>
inline matrix33<T> invert(
    const matrix33<T>& m)
{
    matrix33<T> r;
    return invert(r, m);
}

/// @}

/// \ingroup mtx44ops
/// \name matrix44 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 equals \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two matrix44 objects to see if they are
/// exactly the same .
/// \see operator!=(const matrix44&, const matrix44&)

template<typename T>
inline bool operator== (
    const matrix44<T>& m1,
    const matrix44<T>& m2)
{
    return (
        m1.data_ [0] == m2.data_ [0] &&
        m1.data_ [1] == m2.data_ [1] &&
        m1.data_ [2] == m2.data_ [2] &&
        m1.data_ [3] == m2.data_ [3] &&
        m1.data_ [4] == m2.data_ [4] &&
        m1.data_ [5] == m2.data_ [5] &&
        m1.data_ [6] == m2.data_ [6] &&
        m1.data_ [7] == m2.data_ [7] &&
        m1.data_ [8] == m2.data_ [8] &&
        m1.data_ [9] == m2.data_ [9] &&
        m1.data_[10] == m2.data_[10] &&
        m1.data_[11] == m2.data_[11] &&
        m1.data_[12] == m2.data_[12] &&
        m1.data_[13] == m2.data_[13] &&
        m1.data_[14] == m2.data_[14] &&
        m1.data_[15] == m2.data_[15]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 does not equal \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two matrix44 objects to see if they are
/// NOT exactly the same with zero tolerance.
/// \see operator==(const matrix44&, const matrix44&)

template<typename T>
inline bool operator!= (
    const matrix44<T>& m1,
    const matrix44<T>& m2)
{
    return (
        m1.data_ [0] != m2.data_ [0] ||
        m1.data_ [1] != m2.data_ [1] ||
        m1.data_ [2] != m2.data_ [2] ||
        m1.data_ [3] != m2.data_ [3] ||
        m1.data_ [4] != m2.data_ [4] ||
        m1.data_ [5] != m2.data_ [5] ||
        m1.data_ [6] != m2.data_ [6] ||
        m1.data_ [7] != m2.data_ [7] ||
        m1.data_ [8] != m2.data_ [8] ||
        m1.data_ [9] != m2.data_ [9] ||
        m1.data_[10] != m2.data_[10] ||
        m1.data_[11] != m2.data_[11] ||
        m1.data_[12] != m2.data_[12] ||
        m1.data_[13] != m2.data_[13] ||
        m1.data_[14] != m2.data_[14] ||
        m1.data_[15] != m2.data_[15]);
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
/// \see operator==(const matrix44&, const matrix44&)

template<typename T>
inline bool is_equal(
    const matrix44<T>& m1,
    const matrix44<T>& m2,
    const T eps)
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (
        abs(m1.data_ [0] - m2.data_ [0]) <= eps &&
        abs(m1.data_ [1] - m2.data_ [1]) <= eps &&
        abs(m1.data_ [2] - m2.data_ [2]) <= eps &&
        abs(m1.data_ [3] - m2.data_ [3]) <= eps &&
        abs(m1.data_ [4] - m2.data_ [4]) <= eps &&
        abs(m1.data_ [5] - m2.data_ [5]) <= eps &&
        abs(m1.data_ [6] - m2.data_ [6]) <= eps &&
        abs(m1.data_ [7] - m2.data_ [7]) <= eps &&
        abs(m1.data_ [8] - m2.data_ [8]) <= eps &&
        abs(m1.data_ [9] - m2.data_ [9]) <= eps &&
        abs(m1.data_[10] - m2.data_[10]) <= eps &&
        abs(m1.data_[11] - m2.data_[11]) <= eps &&
        abs(m1.data_[12] - m2.data_[12]) <= eps &&
        abs(m1.data_[13] - m2.data_[13]) <= eps &&
        abs(m1.data_[14] - m2.data_[14]) <= eps &&
        abs(m1.data_[15] - m2.data_[15]) <= eps);
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
/// \see operator*(const matrix44&, const matrix44&)

template<typename T>
inline matrix44<T>& mult(
    matrix44<T>& r,
    const matrix44<T>& lhs,
    const matrix44<T>& rhs)
{
    matrix44<T> ret;    // prevents aliasing
    ret.zero();

    ret.data_ [0] += lhs.data_ [0] * rhs.data_ [0];
    ret.data_ [0] += lhs.data_ [4] * rhs.data_ [1];
    ret.data_ [0] += lhs.data_ [8] * rhs.data_ [2];
    ret.data_ [0] += lhs.data_[12] * rhs.data_ [3];

    ret.data_ [1] += lhs.data_ [1] * rhs.data_ [0];
    ret.data_ [1] += lhs.data_ [5] * rhs.data_ [1];
    ret.data_ [1] += lhs.data_ [9] * rhs.data_ [2];
    ret.data_ [1] += lhs.data_[13] * rhs.data_ [3];

    ret.data_ [2] += lhs.data_ [2] * rhs.data_ [0];
    ret.data_ [2] += lhs.data_ [6] * rhs.data_ [1];
    ret.data_ [2] += lhs.data_[10] * rhs.data_ [2];
    ret.data_ [2] += lhs.data_[14] * rhs.data_ [3];

    ret.data_ [3] += lhs.data_ [3] * rhs.data_ [0];
    ret.data_ [3] += lhs.data_ [7] * rhs.data_ [1];
    ret.data_ [3] += lhs.data_[11] * rhs.data_ [2];
    ret.data_ [3] += lhs.data_[15] * rhs.data_ [3];

    ret.data_ [4] += lhs.data_ [0] * rhs.data_ [4];
    ret.data_ [4] += lhs.data_ [4] * rhs.data_ [5];
    ret.data_ [4] += lhs.data_ [8] * rhs.data_ [6];
    ret.data_ [4] += lhs.data_[12] * rhs.data_ [7];

    ret.data_ [5] += lhs.data_ [1] * rhs.data_ [4];
    ret.data_ [5] += lhs.data_ [5] * rhs.data_ [5];
    ret.data_ [5] += lhs.data_ [9] * rhs.data_ [6];
    ret.data_ [5] += lhs.data_[13] * rhs.data_ [7];

    ret.data_ [6] += lhs.data_ [2] * rhs.data_ [4];
    ret.data_ [6] += lhs.data_ [6] * rhs.data_ [5];
    ret.data_ [6] += lhs.data_[10] * rhs.data_ [6];
    ret.data_ [6] += lhs.data_[14] * rhs.data_ [7];

    ret.data_ [7] += lhs.data_ [3] * rhs.data_ [4];
    ret.data_ [7] += lhs.data_ [7] * rhs.data_ [5];
    ret.data_ [7] += lhs.data_[11] * rhs.data_ [6];
    ret.data_ [7] += lhs.data_[15] * rhs.data_ [7];

    ret.data_ [8] += lhs.data_ [0] * rhs.data_ [8];
    ret.data_ [8] += lhs.data_ [4] * rhs.data_ [9];
    ret.data_ [8] += lhs.data_ [8] * rhs.data_[10];
    ret.data_ [8] += lhs.data_[12] * rhs.data_[11];

    ret.data_ [9] += lhs.data_ [1] * rhs.data_ [8];
    ret.data_ [9] += lhs.data_ [5] * rhs.data_ [9];
    ret.data_ [9] += lhs.data_ [9] * rhs.data_[10];
    ret.data_ [9] += lhs.data_[13] * rhs.data_[11];

    ret.data_[10] += lhs.data_ [2] * rhs.data_ [8];
    ret.data_[10] += lhs.data_ [6] * rhs.data_ [9];
    ret.data_[10] += lhs.data_[10] * rhs.data_[10];
    ret.data_[10] += lhs.data_[14] * rhs.data_[11];

    ret.data_[11] += lhs.data_ [3] * rhs.data_ [8];
    ret.data_[11] += lhs.data_ [7] * rhs.data_ [9];
    ret.data_[11] += lhs.data_[11] * rhs.data_[10];
    ret.data_[11] += lhs.data_[15] * rhs.data_[11];

    ret.data_[12] += lhs.data_ [0] * rhs.data_[12];
    ret.data_[12] += lhs.data_ [4] * rhs.data_[13];
    ret.data_[12] += lhs.data_ [8] * rhs.data_[14];
    ret.data_[12] += lhs.data_[12] * rhs.data_[15];

    ret.data_[13] += lhs.data_ [1] * rhs.data_[12];
    ret.data_[13] += lhs.data_ [5] * rhs.data_[13];
    ret.data_[13] += lhs.data_ [9] * rhs.data_[14];
    ret.data_[13] += lhs.data_[13] * rhs.data_[15];

    ret.data_[14] += lhs.data_ [2] * rhs.data_[12];
    ret.data_[14] += lhs.data_ [6] * rhs.data_[13];
    ret.data_[14] += lhs.data_[10] * rhs.data_[14];
    ret.data_[14] += lhs.data_[14] * rhs.data_[15];

    ret.data_[15] += lhs.data_ [3] * rhs.data_[12];
    ret.data_[15] += lhs.data_ [7] * rhs.data_[13];
    ret.data_[15] += lhs.data_[11] * rhs.data_[14];
    ret.data_[15] += lhs.data_[15] * rhs.data_[15];

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
/// \see mult(matrix44<T>&,const matrix44&, const matrix44&),
/// postMult(matrix44<T>&,const matrix44<T>& operand)

template<typename T>
inline matrix44<T>& pre_mult(
    matrix44<T>& r,
    const matrix44<T>& operand)
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
/// \see mult(matrix44<T>&,const matrix44&, const matrix44&),
/// preMult(matrix44<T>&,const matrix44<T>& operand)

template<typename T>
inline matrix44<T>& post_mult(
    matrix44<T>& r,
    const matrix44<T>& operand)
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
/// \see mult(matrix44<T>&,const matrix44&, const matrix44&)

template<typename T>
inline matrix44<T> operator* (
    const matrix44<T>& lhs,
    const matrix44<T>& rhs)
{
    matrix44<T> temp;
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
/// \see postMult(matrix44<T>&,const matrix44<T>& operand)

template<typename T>
inline matrix44<T>& operator*= (
    matrix44<T>& r,
    const matrix44<T>& operand)
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
/// \see transpose(matrix44&, const matrix44&)

template<typename T>
inline matrix44<T>& transpose(
    matrix44<T>& r)
{
    std::swap(r.data_ [1], r.data_ [4]);
    std::swap(r.data_ [2], r.data_ [8]);
    std::swap(r.data_ [3], r.data_[12]);
    std::swap(r.data_ [6], r.data_ [9]);
    std::swap(r.data_ [7], r.data_[13]);
    std::swap(r.data_[11], r.data_[14]);
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
/// \see transpose(matrix44&)

template<typename T>
inline matrix44<T>& transpose(
    matrix44<T>& r,
    const matrix44<T>& s)
{
    r.data_ [0] = s.data_ [0]; r.data_ [1] = s.data_ [4];
    r.data_ [2] = s.data_ [8]; r.data_ [3] = s.data_[12];
    r.data_ [4] = s.data_ [1]; r.data_ [5] = s.data_ [5];
    r.data_ [6] = s.data_ [9]; r.data_ [7] = s.data_[13];
    r.data_ [8] = s.data_ [2]; r.data_ [9] = s.data_ [6];
    r.data_[10] = s.data_[10]; r.data_[11] = s.data_[14];
    r.data_[12] = s.data_ [3]; r.data_[13] = s.data_ [7];
    r.data_[14] = s.data_[11]; r.data_[15] = s.data_[15];
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The determinant of the matrix.
/// \param m Reference to the matrix used for the determinant calculation.
/// \remarks
/// This function computes the determinant of the \a m matrix. Determinant is
/// used for the calculation of the inverse of a matrix.
/// \see invert(matrix44&, const matrix44&)

template<typename T>
inline T determinant(
    const matrix44<T>& m)
{
    return
        (((
        (((m.data_[10]*m.data_[15])-(m.data_[14]*m.data_[11]))*m.data_ [5]) +
        (((m.data_[14]*m.data_ [7])-(m.data_ [6]*m.data_[15]))*m.data_ [9]) +
        (((m.data_ [6]*m.data_[11])-(m.data_[10]*m.data_ [7]))*m.data_[13]))
          *m.data_ [0]) - ((
        (((m.data_[10]*m.data_[15])-(m.data_[14]*m.data_[11]))*m.data_ [1]) +
        (((m.data_[14]*m.data_ [3])-(m.data_ [2]*m.data_[15]))*m.data_ [9]) +
        (((m.data_ [2]*m.data_[11])-(m.data_[10]*m.data_ [3]))*m.data_[13]))
          *m.data_ [4]) + ((
        (((m.data_ [6]*m.data_[15])-(m.data_[14]*m.data_ [7]))*m.data_ [1]) +
        (((m.data_[14]*m.data_ [3])-(m.data_ [2]*m.data_[15]))*m.data_ [5]) +
        (((m.data_ [2]*m.data_ [7])-(m.data_ [6]*m.data_ [3]))*m.data_[13]))
          *m.data_ [8]) - ((
        (((m.data_ [6]*m.data_[11])-(m.data_[10]*m.data_ [7]))*m.data_ [1]) +
        (((m.data_[10]*m.data_ [3])-(m.data_ [2]*m.data_[11]))*m.data_ [5]) +
        (((m.data_ [2]*m.data_ [7])-(m.data_ [6]*m.data_ [3]))*m.data_ [9]))
          *m.data_[12]
        ));
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after the operation.
/// \param r Reference to the matrix that receives the result of the operation.
/// \param s Reference to the source matrix.
/// \pre Only works with float types (e.g. matrix44<int> is not acceptable).
/// \remarks
/// This function puts the result of inverting \a s into \a r and then returns
/// reference to \a r. In this way, it can be used as a parameter for another
/// function. It uses the \a classical \a adjoint method to compute the inverse.
/// \see invert(const matrix44&)

template<typename T>
inline matrix44<T>& invert(
    matrix44<T>& r,
    const matrix44<T>& s)
{
    T det = determinant(s);
    BOOST_ASSERT_MSG(abs(det) > SMALL, "not invertible!");
    T one_over_det = T(1) / det;
    r.data_ [0] = ((s.data_ [5]*s.data_[10]*s.data_[15]) +
                   (s.data_ [9]*s.data_[14]*s.data_ [7]) +
                   (s.data_[13]*s.data_ [6]*s.data_[11]) -
                   (s.data_ [5]*s.data_[14]*s.data_[11]) -
                   (s.data_ [9]*s.data_ [6]*s.data_[15]) -
                   (s.data_[13]*s.data_[10]*s.data_ [7])) * one_over_det;
    r.data_ [1] = ((s.data_ [1]*s.data_[14]*s.data_[11]) +
                   (s.data_ [9]*s.data_ [2]*s.data_[15]) +
                   (s.data_[13]*s.data_[10]*s.data_ [3]) -
                   (s.data_ [1]*s.data_[10]*s.data_[15]) -
                   (s.data_ [9]*s.data_[14]*s.data_ [3]) -
                   (s.data_[13]*s.data_ [2]*s.data_[11])) * one_over_det;
    r.data_ [2] = ((s.data_ [1]*s.data_ [6]*s.data_[15]) +
                   (s.data_ [5]*s.data_[14]*s.data_ [3]) +
                   (s.data_[13]*s.data_ [2]*s.data_ [7]) -
                   (s.data_ [1]*s.data_[14]*s.data_ [7]) -
                   (s.data_ [5]*s.data_ [2]*s.data_[15]) -
                   (s.data_[13]*s.data_ [6]*s.data_ [3])) * one_over_det;
    r.data_ [3] = ((s.data_ [1]*s.data_[10]*s.data_ [7]) +
                   (s.data_ [5]*s.data_ [2]*s.data_[11]) +
                   (s.data_ [9]*s.data_ [6]*s.data_ [3]) -
                   (s.data_ [1]*s.data_ [6]*s.data_[11]) -
                   (s.data_ [5]*s.data_[10]*s.data_ [3]) -
                   (s.data_ [9]*s.data_ [2]*s.data_ [7])) * one_over_det;
    r.data_ [4] = ((s.data_ [4]*s.data_[14]*s.data_[11]) +
                   (s.data_ [8]*s.data_ [6]*s.data_[15]) +
                   (s.data_[12]*s.data_[10]*s.data_ [7]) -
                   (s.data_ [4]*s.data_[10]*s.data_[15]) -
                   (s.data_ [8]*s.data_[14]*s.data_ [7]) -
                   (s.data_[12]*s.data_ [6]*s.data_[11])) * one_over_det;
    r.data_ [5] = ((s.data_ [0]*s.data_[10]*s.data_[15]) +
                   (s.data_ [8]*s.data_[14]*s.data_ [3]) +
                   (s.data_[12]*s.data_ [2]*s.data_[11]) -
                   (s.data_ [0]*s.data_[14]*s.data_[11]) -
                   (s.data_ [8]*s.data_ [2]*s.data_[15]) -
                   (s.data_[12]*s.data_[10]*s.data_ [3])) * one_over_det;
    r.data_ [6] = ((s.data_ [0]*s.data_[14]*s.data_ [7]) +
                   (s.data_ [4]*s.data_ [2]*s.data_[15]) +
                   (s.data_[12]*s.data_ [6]*s.data_ [3]) -
                   (s.data_ [0]*s.data_ [6]*s.data_[15]) -
                   (s.data_ [4]*s.data_[14]*s.data_ [3]) -
                   (s.data_[12]*s.data_ [2]*s.data_ [7])) * one_over_det;
    r.data_ [7] = ((s.data_ [0]*s.data_ [6]*s.data_[11]) +
                   (s.data_ [4]*s.data_[10]*s.data_ [3]) +
                   (s.data_ [8]*s.data_ [2]*s.data_ [7]) -
                   (s.data_ [0]*s.data_[10]*s.data_ [7]) -
                   (s.data_ [4]*s.data_ [2]*s.data_[11]) -
                   (s.data_ [8]*s.data_ [6]*s.data_ [3])) * one_over_det;
    r.data_ [8] = ((s.data_ [4]*s.data_ [9]*s.data_[15]) +
                   (s.data_ [8]*s.data_[13]*s.data_ [7]) +
                   (s.data_[12]*s.data_ [5]*s.data_[11]) -
                   (s.data_ [4]*s.data_[13]*s.data_[11]) -
                   (s.data_ [8]*s.data_ [5]*s.data_[15]) -
                   (s.data_[12]*s.data_ [9]*s.data_ [7])) * one_over_det;
    r.data_ [9] = ((s.data_ [0]*s.data_[13]*s.data_[11]) +
                   (s.data_ [8]*s.data_ [1]*s.data_[15]) +
                   (s.data_[12]*s.data_ [9]*s.data_ [3]) -
                   (s.data_ [0]*s.data_ [9]*s.data_[15]) -
                   (s.data_ [8]*s.data_[13]*s.data_ [3]) -
                   (s.data_[12]*s.data_ [1]*s.data_[11])) * one_over_det;
    r.data_[10] = ((s.data_ [0]*s.data_ [5]*s.data_[15]) +
                   (s.data_ [4]*s.data_[13]*s.data_ [3]) +
                   (s.data_[12]*s.data_ [1]*s.data_ [7]) -
                   (s.data_ [0]*s.data_[13]*s.data_ [7]) -
                   (s.data_ [4]*s.data_ [1]*s.data_[15]) -
                   (s.data_[12]*s.data_ [5]*s.data_ [3])) * one_over_det;
    r.data_[11] = ((s.data_ [0]*s.data_ [9]*s.data_ [7]) +
                   (s.data_ [4]*s.data_ [1]*s.data_[11]) +
                   (s.data_ [8]*s.data_ [5]*s.data_ [3]) -
                   (s.data_ [0]*s.data_ [5]*s.data_[11]) -
                   (s.data_ [4]*s.data_ [9]*s.data_ [3]) -
                   (s.data_ [8]*s.data_ [1]*s.data_ [7])) * one_over_det;
    r.data_[12] = ((s.data_ [4]*s.data_[13]*s.data_[10]) +
                   (s.data_ [8]*s.data_ [5]*s.data_[14]) +
                   (s.data_[12]*s.data_ [9]*s.data_ [6]) -
                   (s.data_ [4]*s.data_ [9]*s.data_[14]) -
                   (s.data_ [8]*s.data_[13]*s.data_ [6]) -
                   (s.data_[12]*s.data_ [5]*s.data_[10])) * one_over_det;
    r.data_[13] = ((s.data_ [0]*s.data_ [9]*s.data_[14]) +
                   (s.data_ [8]*s.data_[13]*s.data_ [2]) +
                   (s.data_[12]*s.data_ [1]*s.data_[10]) -
                   (s.data_ [0]*s.data_[13]*s.data_[10]) -
                   (s.data_ [8]*s.data_ [1]*s.data_[14]) -
                   (s.data_[12]*s.data_ [9]*s.data_ [2])) * one_over_det;
    r.data_[14] = ((s.data_ [0]*s.data_[13]*s.data_ [6]) +
                   (s.data_ [4]*s.data_ [1]*s.data_[14]) +
                   (s.data_[12]*s.data_ [5]*s.data_ [2]) -
                   (s.data_ [0]*s.data_ [5]*s.data_[14]) -
                   (s.data_ [4]*s.data_[13]*s.data_ [2]) -
                   (s.data_[12]*s.data_ [1]*s.data_ [6])) * one_over_det;
    r.data_[15] = ((s.data_ [0]*s.data_ [5]*s.data_[10]) +
                   (s.data_ [4]*s.data_ [9]*s.data_ [2]) +
                   (s.data_ [8]*s.data_ [1]*s.data_ [6]) -
                   (s.data_ [0]*s.data_ [9]*s.data_ [6]) -
                   (s.data_ [4]*s.data_ [1]*s.data_[10]) -
                   (s.data_ [8]*s.data_ [5]*s.data_ [2])) * one_over_det;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Result of the operation.
/// \param m Reference to the matrix to be inverted.
/// \pre Only works with float types (e.g. matrix44<int> is not acceptable).
/// \remarks
/// This function inverts the given matrix \a m and then returns the result. In
/// this way, it can be used as a parameter for another function. It uses the \a
/// classical \a adjoint method to compute the inverse.
/// \see invert(matrix44&, const matrix44&)

template<typename T>
inline matrix44<T> invert(
    const matrix44<T>& m)
{
    matrix44<T> r;
    return invert(r, m);
}

/// @}
