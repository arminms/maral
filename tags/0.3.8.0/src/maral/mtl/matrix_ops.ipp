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
//    matrix_ops.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation for all operations related to matrices.
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
        m1(0) == m2(0) &&
        m1(1) == m2(1) &&
        m1(2) == m2(2) &&
        m1(3) == m2(3) );
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
        m1(0) != m2(0) ||
        m1(1) != m2(1) ||
        m1(2) != m2(2) ||
        m1(3) != m2(3) );
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
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (
        std::abs(m1(0) - m2(0)) <= eps &&
        std::abs(m1(1) - m2(1)) <= eps &&
        std::abs(m1(2) - m2(2)) <= eps &&
        std::abs(m1(3) - m2(3)) <= eps );
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

    ret(0) += lhs(0) * rhs(0);
    ret(0) += lhs(2) * rhs(1);

    ret(1) += lhs(1) * rhs(0);
    ret(1) += lhs(3) * rhs(1);

    ret(2) += lhs(0) * rhs(2);
    ret(2) += lhs(2) * rhs(3);

    ret(3) += lhs(1) * rhs(2);
    ret(3) += lhs(3) * rhs(3);

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
    std::swap(r(1), r(2));
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
    r(0) = s(0); r(1) = s(2);
    r(2) = s(1); r(3) = s(3);
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
    return ( (m(0)*m(3)) - (m(1)*m(2)) );
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
    T det = ( (s(0)*s(3)) - (s(1)*s(2)) );
    BOOST_ASSERT_MSG(std::abs(det) > SMALL, "not invertible!");
    T one_over_det = T(1) / det;
    r(0) =  s(3) * one_over_det;
    r(1) = -s(1) * one_over_det;
    r(2) = -s(2) * one_over_det;
    r(3) =  s(0) * one_over_det;
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
        m1(0) == m2(0) &&
        m1(1) == m2(1) &&
        m1(2) == m2(2) &&
        m1(3) == m2(3) &&
        m1(4) == m2(4) &&
        m1(5) == m2(5) &&
        m1(6) == m2(6) &&
        m1(7) == m2(7) &&
        m1(8) == m2(8));
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
        m1(0) != m2(0) ||
        m1(1) != m2(1) ||
        m1(2) != m2(2) ||
        m1(3) != m2(3) ||
        m1(4) != m2(4) ||
        m1(5) != m2(5) ||
        m1(6) != m2(6) ||
        m1(7) != m2(7) ||
        m1(8) != m2(8));
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
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (
        std::abs(m1(0) - m2(0)) <= eps &&
        std::abs(m1(1) - m2(1)) <= eps &&
        std::abs(m1(2) - m2(2)) <= eps &&
        std::abs(m1(3) - m2(3)) <= eps &&
        std::abs(m1(4) - m2(4)) <= eps &&
        std::abs(m1(5) - m2(5)) <= eps &&
        std::abs(m1(6) - m2(6)) <= eps &&
        std::abs(m1(7) - m2(7)) <= eps &&
        std::abs(m1(8) - m2(8)) <= eps);
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

    ret(0) += lhs(0) * rhs(0);
    ret(0) += lhs(3) * rhs(1);
    ret(0) += lhs(6) * rhs(2);

    ret(1) += lhs(1) * rhs(0);
    ret(1) += lhs(4) * rhs(1);
    ret(1) += lhs(7) * rhs(2);

    ret(2) += lhs(2) * rhs(0);
    ret(2) += lhs(5) * rhs(1);
    ret(2) += lhs(8) * rhs(2);

    ret(3) += lhs(0) * rhs(3);
    ret(3) += lhs(3) * rhs(4);
    ret(3) += lhs(6) * rhs(5);

    ret(4) += lhs(1) * rhs(3);
    ret(4) += lhs(4) * rhs(4);
    ret(4) += lhs(7) * rhs(5);

    ret(5) += lhs(2) * rhs(3);
    ret(5) += lhs(5) * rhs(4);
    ret(5) += lhs(8) * rhs(5);

    ret(6) += lhs(0) * rhs(6);
    ret(6) += lhs(3) * rhs(7);
    ret(6) += lhs(6) * rhs(8);

    ret(7) += lhs(1) * rhs(6);
    ret(7) += lhs(4) * rhs(7);
    ret(7) += lhs(7) * rhs(8);

    ret(8) += lhs(2) * rhs(6);
    ret(8) += lhs(5) * rhs(7);
    ret(8) += lhs(8) * rhs(8);

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
    std::swap(r(1), r(3));
    std::swap(r(2), r(6));
    std::swap(r(5), r(7));
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
    r(0) = s(0); r(1) = s(3); r(2) = s(6);
    r(3) = s(1); r(4) = s(4); r(5) = s(7);
    r(6) = s(2); r(7) = s(5); r(8) = s(8);
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
    return ((((m(3)*m(7)) - (m(6)*m(4))) * m(2)) +
            (((m(6)*m(1)) - (m(0)*m(7))) * m(5)) +
            (((m(0)*m(4)) - (m(3)*m(1))) * m(8)));
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
    BOOST_ASSERT_MSG(std::abs(det) > SMALL, "not invertible!");
    T one_over_det = T(1) / det;
    r(0) = ((s(4)*s(8))-(s(7)*s(5)))*one_over_det;
    r(1) = ((s(7)*s(2))-(s(1)*s(8)))*one_over_det;
    r(2) = ((s(1)*s(5))-(s(4)*s(2)))*one_over_det;
    r(3) = ((s(6)*s(5))-(s(3)*s(8)))*one_over_det;
    r(4) = ((s(0)*s(8))-(s(6)*s(2)))*one_over_det;
    r(5) = ((s(3)*s(2))-(s(0)*s(5)))*one_over_det;
    r(6) = ((s(3)*s(7))-(s(6)*s(4)))*one_over_det;
    r(7) = ((s(6)*s(1))-(s(0)*s(7)))*one_over_det;
    r(8) = ((s(0)*s(4))-(s(3)*s(1)))*one_over_det;
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
        m1 (0) == m2 (0) &&
        m1 (1) == m2 (1) &&
        m1 (2) == m2 (2) &&
        m1 (3) == m2 (3) &&
        m1 (4) == m2 (4) &&
        m1 (5) == m2 (5) &&
        m1 (6) == m2 (6) &&
        m1 (7) == m2 (7) &&
        m1 (8) == m2 (8) &&
        m1 (9) == m2 (9) &&
        m1(10) == m2(10) &&
        m1(11) == m2(11) &&
        m1(12) == m2(12) &&
        m1(13) == m2(13) &&
        m1(14) == m2(14) &&
        m1(15) == m2(15));
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
        m1 (0) != m2 (0) ||
        m1 (1) != m2 (1) ||
        m1 (2) != m2 (2) ||
        m1 (3) != m2 (3) ||
        m1 (4) != m2 (4) ||
        m1 (5) != m2 (5) ||
        m1 (6) != m2 (6) ||
        m1 (7) != m2 (7) ||
        m1 (8) != m2 (8) ||
        m1 (9) != m2 (9) ||
        m1(10) != m2(10) ||
        m1(11) != m2(11) ||
        m1(12) != m2(12) ||
        m1(13) != m2(13) ||
        m1(14) != m2(14) ||
        m1(15) != m2(15));
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
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (
        std::abs(m1 (0) - m2 (0)) <= eps &&
        std::abs(m1 (1) - m2 (1)) <= eps &&
        std::abs(m1 (2) - m2 (2)) <= eps &&
        std::abs(m1 (3) - m2 (3)) <= eps &&
        std::abs(m1 (4) - m2 (4)) <= eps &&
        std::abs(m1 (5) - m2 (5)) <= eps &&
        std::abs(m1 (6) - m2 (6)) <= eps &&
        std::abs(m1 (7) - m2 (7)) <= eps &&
        std::abs(m1 (8) - m2 (8)) <= eps &&
        std::abs(m1 (9) - m2 (9)) <= eps &&
        std::abs(m1(10) - m2(10)) <= eps &&
        std::abs(m1(11) - m2(11)) <= eps &&
        std::abs(m1(12) - m2(12)) <= eps &&
        std::abs(m1(13) - m2(13)) <= eps &&
        std::abs(m1(14) - m2(14)) <= eps &&
        std::abs(m1(15) - m2(15)) <= eps);
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

    ret (0) += lhs (0) * rhs (0);
    ret (0) += lhs (4) * rhs (1);
    ret (0) += lhs (8) * rhs (2);
    ret (0) += lhs(12) * rhs (3);

    ret (1) += lhs (1) * rhs (0);
    ret (1) += lhs (5) * rhs (1);
    ret (1) += lhs (9) * rhs (2);
    ret (1) += lhs(13) * rhs (3);

    ret (2) += lhs (2) * rhs (0);
    ret (2) += lhs (6) * rhs (1);
    ret (2) += lhs(10) * rhs (2);
    ret (2) += lhs(14) * rhs (3);

    ret (3) += lhs (3) * rhs (0);
    ret (3) += lhs (7) * rhs (1);
    ret (3) += lhs(11) * rhs (2);
    ret (3) += lhs(15) * rhs (3);

    ret (4) += lhs (0) * rhs (4);
    ret (4) += lhs (4) * rhs (5);
    ret (4) += lhs (8) * rhs (6);
    ret (4) += lhs(12) * rhs (7);

    ret (5) += lhs (1) * rhs (4);
    ret (5) += lhs (5) * rhs (5);
    ret (5) += lhs (9) * rhs (6);
    ret (5) += lhs(13) * rhs (7);

    ret (6) += lhs (2) * rhs (4);
    ret (6) += lhs (6) * rhs (5);
    ret (6) += lhs(10) * rhs (6);
    ret (6) += lhs(14) * rhs (7);

    ret (7) += lhs (3) * rhs (4);
    ret (7) += lhs (7) * rhs (5);
    ret (7) += lhs(11) * rhs (6);
    ret (7) += lhs(15) * rhs (7);

    ret (8) += lhs (0) * rhs (8);
    ret (8) += lhs (4) * rhs (9);
    ret (8) += lhs (8) * rhs(10);
    ret (8) += lhs(12) * rhs(11);

    ret (9) += lhs (1) * rhs (8);
    ret (9) += lhs (5) * rhs (9);
    ret (9) += lhs (9) * rhs(10);
    ret (9) += lhs(13) * rhs(11);

    ret(10) += lhs (2) * rhs (8);
    ret(10) += lhs (6) * rhs (9);
    ret(10) += lhs(10) * rhs(10);
    ret(10) += lhs(14) * rhs(11);

    ret(11) += lhs (3) * rhs (8);
    ret(11) += lhs (7) * rhs (9);
    ret(11) += lhs(11) * rhs(10);
    ret(11) += lhs(15) * rhs(11);

    ret(12) += lhs (0) * rhs(12);
    ret(12) += lhs (4) * rhs(13);
    ret(12) += lhs (8) * rhs(14);
    ret(12) += lhs(12) * rhs(15);

    ret(13) += lhs (1) * rhs(12);
    ret(13) += lhs (5) * rhs(13);
    ret(13) += lhs (9) * rhs(14);
    ret(13) += lhs(13) * rhs(15);

    ret(14) += lhs (2) * rhs(12);
    ret(14) += lhs (6) * rhs(13);
    ret(14) += lhs(10) * rhs(14);
    ret(14) += lhs(14) * rhs(15);

    ret(15) += lhs (3) * rhs(12);
    ret(15) += lhs (7) * rhs(13);
    ret(15) += lhs(11) * rhs(14);
    ret(15) += lhs(15) * rhs(15);

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
    std::swap(r (1), r (4));
    std::swap(r (2), r (8));
    std::swap(r (3), r(12));
    std::swap(r (6), r (9));
    std::swap(r (7), r(13));
    std::swap(r(11), r(14));
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
    r (0) = s (0); r (1) = s (4);
    r (2) = s (8); r (3) = s(12);
    r (4) = s (1); r (5) = s (5);
    r (6) = s (9); r (7) = s(13);
    r (8) = s (2); r (9) = s (6);
    r(10) = s(10); r(11) = s(14);
    r(12) = s (3); r(13) = s (7);
    r(14) = s(11); r(15) = s(15);
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
        (((m(10)*m(15))-(m(14)*m(11)))*m (5)) +
        (((m(14)*m (7))-(m (6)*m(15)))*m (9)) +
        (((m (6)*m(11))-(m(10)*m (7)))*m(13)))
          *m (0)) - ((
        (((m(10)*m(15))-(m(14)*m(11)))*m (1)) +
        (((m(14)*m (3))-(m (2)*m(15)))*m (9)) +
        (((m (2)*m(11))-(m(10)*m (3)))*m(13)))
          *m (4)) + ((
        (((m (6)*m(15))-(m(14)*m (7)))*m (1)) +
        (((m(14)*m (3))-(m (2)*m(15)))*m (5)) +
        (((m (2)*m (7))-(m (6)*m (3)))*m(13)))
          *m (8)) - ((
        (((m (6)*m(11))-(m(10)*m (7)))*m (1)) +
        (((m(10)*m (3))-(m (2)*m(11)))*m (5)) +
        (((m (2)*m (7))-(m (6)*m (3)))*m (9)))
          *m(12)
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
    BOOST_ASSERT_MSG(std::abs(det) > SMALL, "not invertible!");
    T one_over_det = T(1) / det;
    r (0) = ((s (5)*s(10)*s(15)) +
                   (s (9)*s(14)*s (7)) +
                   (s(13)*s (6)*s(11)) -
                   (s (5)*s(14)*s(11)) -
                   (s (9)*s (6)*s(15)) -
                   (s(13)*s(10)*s (7))) * one_over_det;
    r (1) = ((s (1)*s(14)*s(11)) +
                   (s (9)*s (2)*s(15)) +
                   (s(13)*s(10)*s (3)) -
                   (s (1)*s(10)*s(15)) -
                   (s (9)*s(14)*s (3)) -
                   (s(13)*s (2)*s(11))) * one_over_det;
    r (2) = ((s (1)*s (6)*s(15)) +
                   (s (5)*s(14)*s (3)) +
                   (s(13)*s (2)*s (7)) -
                   (s (1)*s(14)*s (7)) -
                   (s (5)*s (2)*s(15)) -
                   (s(13)*s (6)*s (3))) * one_over_det;
    r (3) = ((s (1)*s(10)*s (7)) +
                   (s (5)*s (2)*s(11)) +
                   (s (9)*s (6)*s (3)) -
                   (s (1)*s (6)*s(11)) -
                   (s (5)*s(10)*s (3)) -
                   (s (9)*s (2)*s (7))) * one_over_det;
    r (4) = ((s (4)*s(14)*s(11)) +
                   (s (8)*s (6)*s(15)) +
                   (s(12)*s(10)*s (7)) -
                   (s (4)*s(10)*s(15)) -
                   (s (8)*s(14)*s (7)) -
                   (s(12)*s (6)*s(11))) * one_over_det;
    r (5) = ((s (0)*s(10)*s(15)) +
                   (s (8)*s(14)*s (3)) +
                   (s(12)*s (2)*s(11)) -
                   (s (0)*s(14)*s(11)) -
                   (s (8)*s (2)*s(15)) -
                   (s(12)*s(10)*s (3))) * one_over_det;
    r (6) = ((s (0)*s(14)*s (7)) +
                   (s (4)*s (2)*s(15)) +
                   (s(12)*s (6)*s (3)) -
                   (s (0)*s (6)*s(15)) -
                   (s (4)*s(14)*s (3)) -
                   (s(12)*s (2)*s (7))) * one_over_det;
    r (7) = ((s (0)*s (6)*s(11)) +
                   (s (4)*s(10)*s (3)) +
                   (s (8)*s (2)*s (7)) -
                   (s (0)*s(10)*s (7)) -
                   (s (4)*s (2)*s(11)) -
                   (s (8)*s (6)*s (3))) * one_over_det;
    r (8) = ((s (4)*s (9)*s(15)) +
                   (s (8)*s(13)*s (7)) +
                   (s(12)*s (5)*s(11)) -
                   (s (4)*s(13)*s(11)) -
                   (s (8)*s (5)*s(15)) -
                   (s(12)*s (9)*s (7))) * one_over_det;
    r (9) = ((s (0)*s(13)*s(11)) +
                   (s (8)*s (1)*s(15)) +
                   (s(12)*s (9)*s (3)) -
                   (s (0)*s (9)*s(15)) -
                   (s (8)*s(13)*s (3)) -
                   (s(12)*s (1)*s(11))) * one_over_det;
    r(10) = ((s (0)*s (5)*s(15)) +
                   (s (4)*s(13)*s (3)) +
                   (s(12)*s (1)*s (7)) -
                   (s (0)*s(13)*s (7)) -
                   (s (4)*s (1)*s(15)) -
                   (s(12)*s (5)*s (3))) * one_over_det;
    r(11) = ((s (0)*s (9)*s (7)) +
                   (s (4)*s (1)*s(11)) +
                   (s (8)*s (5)*s (3)) -
                   (s (0)*s (5)*s(11)) -
                   (s (4)*s (9)*s (3)) -
                   (s (8)*s (1)*s (7))) * one_over_det;
    r(12) = ((s (4)*s(13)*s(10)) +
                   (s (8)*s (5)*s(14)) +
                   (s(12)*s (9)*s (6)) -
                   (s (4)*s (9)*s(14)) -
                   (s (8)*s(13)*s (6)) -
                   (s(12)*s (5)*s(10))) * one_over_det;
    r(13) = ((s (0)*s (9)*s(14)) +
                   (s (8)*s(13)*s (2)) +
                   (s(12)*s (1)*s(10)) -
                   (s (0)*s(13)*s(10)) -
                   (s (8)*s (1)*s(14)) -
                   (s(12)*s (9)*s (2))) * one_over_det;
    r(14) = ((s (0)*s(13)*s (6)) +
                   (s (4)*s (1)*s(14)) +
                   (s(12)*s (5)*s (2)) -
                   (s (0)*s (5)*s(14)) -
                   (s (4)*s(13)*s (2)) -
                   (s(12)*s (1)*s (6))) * one_over_det;
    r(15) = ((s (0)*s (5)*s(10)) +
                   (s (4)*s (9)*s (2)) +
                   (s (8)*s (1)*s (6)) -
                   (s (0)*s (9)*s (6)) -
                   (s (4)*s (1)*s(10)) -
                   (s (8)*s (5)*s (2))) * one_over_det;
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
