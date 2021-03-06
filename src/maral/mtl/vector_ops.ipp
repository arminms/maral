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
//    vector_ops.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation for all operations related to vectors.
//------------------------------------------------------------------------------

/// \ingroup vec2ops
/// \name vector2 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if v1 equals v2; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator compares two vector2 object to see if they
/// are exactly the same .
/// \see operator!=(const vector2<T>&, const vector2<T>&)

template<typename T>
inline bool operator== (
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    return (v1[0] == v2[0] && v1[1] == v2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if v1 does not equal v2; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator compares two vector2 object to see if they
/// are NOT exactly the same with zero tolerance.
/// \see operator==(const vector2<T>&, const vector2<T>&)

template<typename T>
inline bool operator!= (
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    return (v1[0] != v2[0] || v1[1] != v2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if v1 equals v2 within the tolerance; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \param eps The epsilon tolerance value.
/// \pre eps must be >= 0
/// \remarks
/// Compares \a v1 and \a v2 to see if they are the same within the
/// given epsilon tolerance.
/// \see operator==(const vector2<T>&, const vector2<T>&)

template<typename T>
inline bool is_equal(
    const vector2<T>& v1,
    const vector2<T>& v2,
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (std::abs(v1[0] - v2[0]) <= eps && std::abs(v1[1] - v2[1]) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v1 after \a v2 has been added to it.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator adds v2 to v1 and stores the result in v1.
/// This is equivalent to the expression v1 = v1 + v2.
/// \see operator+(const vector2<T>&, const vector2<T>&)

template<typename T>
inline vector2<T>& operator+= (
    vector2<T>& v1,
    const vector2<T>& v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    return v1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of adding \a v2 to \a v1.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator adds v2 to v1 and returns the result.
/// This is equivalent to the expression result = v1 + v2.
/// \see operator+=(vector2<T>&, const vector2<T>&)

template<typename T>
inline vector2<T> operator+ (
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    vector2<T> r(v1);
    r += v2;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v1 after \a v2 has been subtracted from it.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator subtracts v2 from v1 and stores the
/// result in v1. This is equivalent to the expression v1 = v1 - v2.
/// \see operator-(const vector2<T>&, const vector2<T>&)

template<typename T>
inline vector2<T>& operator-= (
    vector2<T>& v1,
    const vector2<T>& v2)
{
    v1[0] -= v2[0];
    v1[1] -= v2[1];
    return v1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of subtracting \a v2 from \a v1.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator subtracts \a v2 from \a v1 and returns the result.
/// This is equivalent to the expression result = v1 - v2.
/// \see operator-=(vector2<T>&, const vector2<T>&),
/// operator-(const vector2<T>&)

template<typename T>
inline vector2<T> operator- (
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    vector2<T> r(v1);
    r -= v2;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a v.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded unary operator changes the sign of each components of a
/// given vector and returns the result as a new vector. This is
/// equivalent to the expression result = -v which is a vector negation.
/// Negating a vector results in a vector of the same magnitude but opposite
/// direction.
/// \see operator-(const vector2<T>&, const vector2<T>&)

template<typename T>
inline vector2<T> operator- (
    const vector2<T>& v)
{
    vector2<T> r(-v[0], -v[1]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v after it has been multiplied by \a scalar.
/// \param v Reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and stores the
/// result in \a v. This is equivalent to the expression v = v * scalar. The
/// result is a vector parallel with the original one, except with a different
/// length and possibly opposite direction.
/// \see operator*(const vector2<T>&, const T&)

template<typename T>
inline vector2<T>& operator*= (
    vector2<T>& v,
    const T& scalar)
{
    v[0] *= scalar;
    v[1] *= scalar;
    return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a v by scalar.
/// \param v Constant reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = v * scalar. The result is a vector parallel with the original one,
/// except with a different length and possibly opposite direction.
/// \see operator*=(vector2<T>&, const const T&),
/// operator*(const T&, const vector2<T>&)

template<typename T>
inline vector2<T> operator* (
    const vector2<T>& v,
    const T& scalar)
{
    vector2<T> r(v);
    r *= scalar;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a v by scalar.
/// \param scalar The amount by which to scale \a v
/// \param v Constant reference to the vector to be scaled.
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = scalar * v. This is a convenient argument position
/// indifference overloader.
/// \see operator*=(vector2<T>&, const const T&),
/// operator*(const vector2<T>&, const T&)

template<typename T>
inline vector2<T> operator* (
    const T& scalar,
    const vector2<T>& v)
{
    vector2<T> r(v);
    r *= scalar;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v after it has been divided by \a scalar.
/// \param v Reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \pre scalar != 0
/// \remarks
/// This overloaded operator divides \a v by a scalar value and
/// stores the result in \a v. This is equivalent to the expression
/// v = v / scalar. The result is a vector parallel with the original one,
/// except with a different length and possibly opposite direction.
/// \see operator/(const vector2<T>&, const T&)

template<typename T>
inline vector2<T>& operator/= (
    vector2<T>& v,
    const T& scalar)
{
    BOOST_ASSERT_MSG(scalar != T(0), "divide by zero!");
    v[0] /= scalar;
    v[1] /= scalar;
    return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of dividing \a v by scalar.
/// \param v Constant reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \pre scalar != 0
/// \remarks
/// This overloaded operator divides \a v by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = v / scalar. The result is a vector parallel with the original one,
/// except with a different length and possibly opposite direction.
/// \see operator*=(vector2<T>&, const const T&)

template<typename T>
inline vector2<T> operator/ (
    const vector2<T>& v,
    const T& scalar)
{
    vector2<T> r(v);
    r /= scalar;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a vector that receives the result.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \pre Only works with float types (e.g. vector2i is not acceptable)
/// \remarks
/// This function returns the middle vector between \a v1 and \a v2.

template<typename T>
inline vector2<T>& middle(
    vector2<T>& r,
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    static_assert(
        std::is_floating_point<T>::value,
        "need a float type :(");

    BOOST_CONSTEXPR_OR_CONST T half = T(1) / T(2);
    r[0] = (v1[0] + v2[0]) * half;
    r[1] = (v1[1] + v2[1]) * half;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The dot product of \a v1 and \a v2:
/// \li if two vectors are perpendicular, result is 0 (angle = 90°, or \a right).
/// \li if two vectors lie in exactly the same direction, result is
/// length(v1)*length(v2) (i.e. > 0, angle < 90° or \a acute) .
/// \li if two vectors point in exactly opposite direction, result is
/// -( length(v1) * length(v2) ) (i.e. < 0, 90° < angle < 180° or \a obtuse).
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \remarks
/// This function computes dot product (AKA \a scalar \a product, \a inner \a
/// product) of two given vectors. It tells how \a similar two vectors are; the
/// larger the dot product, the more similar the two vectors. The dot product is
/// used to calculate the angle between two vectors.
/// \see angle(const vector2<T>&,const vector2<T>&)

template<typename T>
inline T dot(
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    return (v1[0]*v2[0] + v1[1]*v2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return The length of \p v.
/// \param v The vector with which to compute the length.
/// \pre Only works with float types (e.g. vector2i is not acceptable)
/// \remarks
/// This function computes the length (AKA \a magnitude or \a norm) of the
/// given vector.
/// \see length2(const vector2<T>&)

template<typename T>
inline T length(
    const vector2<T>& v)
{
    T r = v[0]*v[0] + v[1]*v[1];
    return (r > T(0) ? sqrt(r) : T(0));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The square of the length of \p v.
/// \param v The vector with which to compute the squared length.
/// \remarks
/// This function computes the square of the length of the given
/// vector. This can be used in many calculations instead of
/// length(const vector2<T>&) to increase speed by saving you an
/// expensive sqrt call.
/// \see length(const vector2<T>&)

template<typename T>
inline T length2(
    const vector2<T>& v)
{
    return (v[0]*v[0] + v[1]*v[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle formed between two vectors in radians.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \pre Only works with float types (e.g. vector2i is not acceptable)
/// \remarks
/// This function finds the angle formed between two vectors and returns the
/// result in radians. You can use units::to_degrees for converting to degrees.
/// \image html angle_point.svg
/// \image rtf angle_point.svg
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector2 angle

template<typename T>
inline T angle(
    const vector2<T>& v1,
    const vector2<T>& v2)
{
    static_assert(
        std::is_floating_point<T>::value,
        "need a float type :(");

    T len_sq = (v1[0]*v1[0] + v1[1]*v1[1]) * (v2[0]*v2[0] + v2[1]*v2[1]);
    return (len_sq == T(0.0f)
            ? T(0.0f)
            : std::acos( (v1[0]*v2[0] + v1[1]*v2[1]) / std::sqrt(len_sq) ) );
}

////////////////////////////////////////////////////////////////////////////////
/// \return The length of \p v before it was normalized.
/// \param v The vector to normalize.
/// \pre Only works with float types (e.g. vector2i is not acceptable)
/// \post length(v) == 1.0 unless length(v) is originally 0.0, in which
/// case it is unchanged.
/// \remarks
/// This function normalizes the given vector in place causing it to
/// be of unit length. If the vector is already of length 1.0, nothing
/// is done.

template<typename T>
inline void normalize(
    vector2<T>& v)
{
    T len_sq = v[0]*v[0] + v[1]*v[1];
    if (len_sq > T(0))
    {
        T one_over_len = T(1) / std::sqrt(len_sq);
        v[0] *= one_over_len;
        v[1] *= one_over_len;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \return \b true if the vector is normalized, \b false otherwise.
/// \param v The vector to test.
/// \param eps The epsilon tolerance.
/// \remarks
/// This function determines if the given vector is normalized within the given
/// tolerance. The vector is normalized if its lengthSq() is 1.
/// \see length_sq(const vector2<T>&)

template<typename T>
inline bool is_normalized(
    const vector2<T>& v,
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= static_cast<T>(0), "negative tolerance!");
    return (std::abs(length2(v) - T(1.0)) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a vector that receives the result.
/// \param v Reference to the original vector that we want to reflect.
/// \param n Reference to the normal vector.
/// \post \a r contains the reflected vector.
/// \remarks
/// This method reflects the given vector around the given normal
/// vector. It is similar to if the normal vector was for a plane that
/// you wanted to reflect about. \a v going into the plane, \a n normal
/// to the plane, and \a r coming back out of the plane (see below).
///
/// \image html vector_reflect.png
/// \image rtf vector_reflect.png

template<typename T>
inline vector2<T>& reflect(
    vector2<T>& r,
    const vector2<T>& v,
    const vector2<T>& n)
{
    r = v - ( T(2.0) * (dot(v, n) * n) );
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a result after getting the result of the operation.
/// \param result Reference to a vector that receives the result.
/// \param lerp_val The value to interpolate between \a from and \a to.
/// \param from The vector at \a lerp_val 0.
/// \param to The vector at \a lerp_val 1.
/// \pre   \a lerp_val is a value between 0 and 1 that interpolates
/// between \a from and \a to.
/// \pre   Only works with float types (e.g. vector2i is not acceptable)
/// \post  Undefined if \a lerp_val < 0 or \a lerp_val > 1.
/// \remarks
/// Linearly interpolates between two vectors. For convenience reference to \a
/// result is returned. In this way, it can be used as a parameter for another
/// function.

template<typename T>
inline vector2<T>& lerp(
    vector2<T>& result,
    const T& lerp_val,
    const vector2<T>& from,
    const vector2<T>& to)
{
    result[0] = to[0] - from[0];
    result[0] *= lerp_val;
    result[0] += from[0];
    result[1] = to[1] - from[1];
    result[1] *= lerp_val;
    result[1] += from[1];
    return result;
}

/// @}

/// \ingroup vec3ops
/// \name vector3 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if \a v1
/// equals \a v2; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator compares two vector3 object to see if they are
/// exactly the same .
/// \see operator!=(const vector3<T>&, const vector3<T>&)

template<typename T>
inline bool operator== (
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    return (v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if \a v1
/// does not equal \a v2; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator compares two vector3 object to see if they are NOT
/// exactly the same with zero tolerance.
/// \see operator==(const vector3<T>&, const vector3<T>&)

template<typename T>
inline bool operator!= (
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    return (v1[0] != v2[0] || v1[1] != v2[1] || v1[2] != v2[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if \a v1
/// equals \a v2 within the tolerance; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \param eps The epsilon tolerance value.
/// \pre \a eps must be >= 0
/// \remarks
/// Compares \a v1 and \a v2 to see if they are the same within the given
/// epsilon tolerance.
/// \see operator==(const vector3<T>&, const vector3<T>&)

template<typename T>
inline bool is_equal(
    const vector3<T>& v1,
    const vector3<T>& v2,
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (std::abs(v1[0] - v2[0]) <= eps &&
            std::abs(v1[1] - v2[1]) <= eps &&
            std::abs(v1[2] - v2[2]) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v1 after \a v2 has been added to it.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator adds \a v2 to \a v1 and stores the result in \a v1.
/// This is equivalent to the expression v1 = v1 + v2.
/// \see operator+(const vector3<T>&, const vector3<T>&)

template<typename T>
inline vector3<T>& operator+= (
    vector3<T>& v1,
    const vector3<T>& v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
    return v1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of adding \a v2 to \a v1.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator adds \a v2 to \a v1 and returns the result. This is
/// equivalent to the expression result = v1 + v2.
/// \see operator+=(vector3<T>&, const vector3<T>&)

template<typename T>
inline vector3<T> operator+ (
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    vector3<T> r(v1);
    r += v2;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v1 after \a v2 has been subtracted from it.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator subtracts \a v2 from \a v1 and stores the result in
/// \a v1. This is equivalent to the expression v1 = v1 - v2.
/// \see operator-(const vector3<T>&, const vector3<T>&)

template<typename T>
inline vector3<T>& operator-= (
    vector3<T>& v1,
    const vector3<T>& v2)
{
    v1[0] -= v2[0];
    v1[1] -= v2[1];
    v1[2] -= v2[2];
    return v1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of subtracting \a v2 from \a v1.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator subtracts \a v2 from \a v1 and returns the result.
/// This is equivalent to the expression result = v1 - v2.
/// \see operator-=(vector3<T>&, const vector3<T>&),
/// operator-(const vector3<T>&)

template<typename T>
inline vector3<T> operator- (
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    vector3<T> r(v1);
    r -= v2;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a v.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded unary operator changes the sign of each components of a
/// given vector and returns the result as a new vector. This is equivalent to
/// the expression result = -v  which is a vector negation. Negating a vector
/// results in a vector of the same magnitude but opposite direction.
/// \see operator-(const vector3<T>&, const vector3<T>&)

template<typename T>
inline vector3<T> operator- (
    const vector3<T>& v)
{
    vector3<T> r(-v[0], -v[1], -v[2]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v after it has been multiplied by \a scalar.
/// \param v Reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and stores the
/// result in \a v. This is equivalent to the expression v = v * scalar. The
/// result is a vector parallel with the original one, except with a different
/// length and possibly opposite direction.
/// \see operator*(const vector3<T>&, const T&)

template<typename T>
inline vector3<T>& operator*= (
    vector3<T>& v,
    const T& scalar)
{
    v[0] *= scalar;
    v[1] *= scalar;
    v[2] *= scalar;
    return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a v by scalar.
/// \param v Constant reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v.
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and returns the
/// result. This is equivalent to the expression result = v * scalar. The result
/// is a vector parallel with the original one, except with a different length
/// and possibly opposite direction.
/// \see operator*=(vector3<T>&, const const T&),
/// operator*(const T&, const vector3<T>&)

template<typename T>
inline vector3<T> operator* (
    const vector3<T>& v,
    const T& scalar)
{
    vector3<T> r(v);
    r *= scalar;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a v by scalar.
/// \param scalar The amount by which to scale \a v.
/// \param v Constant reference to the vector to be scaled.
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and returns the
/// result. This is equivalent to the expression result = scalar * v. This is a
/// convenient argument position indifference overloader.
/// \see operator*=(vector3<T>&, const const T&),
/// operator*(const vector3<T>&, const T&)

template<typename T>
inline vector3<T> operator* (
    const T& scalar,
    const vector3<T>& v)
{
    vector3<T> r(v);
    r *= scalar;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v after it has been divided by \a scalar.
/// \param v Reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v.
/// \pre scalar != 0
/// \remarks
/// This overloaded operator divides \a v by a scalar value and stores the
/// result in \a v. This is equivalent to the expression v = v / scalar. The
/// result is a vector parallel with the original one, except with a different
/// length and possibly opposite direction.
/// \see operator/(const vector3<T>&, const T&)

template<typename T>
inline vector3<T>& operator/= (
    vector3<T>& v,
    const T& scalar)
{
    BOOST_ASSERT_MSG(scalar != T(0), "divide by zero!");
    v[0] /= scalar;
    v[1] /= scalar;
    v[2] /= scalar;
    return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of dividing \a v by scalar.
/// \param v Constant reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v.
/// \pre scalar != 0
/// \remarks
/// This overloaded operator divides \a v by a scalar value and returns the
/// result. This is equivalent to the expression result = v / scalar. The result
/// is a vector parallel with the original one, except with a different length
/// and possibly opposite direction.
/// \see operator*=(vector3<T>&, const const T&)

template<typename T>
inline vector3<T> operator/ (
    const vector3<T>& v,
    const T& scalar)
{
    vector3<T> r(v);
    r /= scalar;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a vector that receives the result.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \pre Only works with float types (e.g. vector3i is not acceptable).
/// \remarks
/// This function returns the middle vector between \a v1 and \a v2.

template<typename T>
inline vector3<T>& middle(
    vector3<T>& r,
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    static_assert(
        std::is_floating_point<T>::value,
        "need a float type :(");

    BOOST_CONSTEXPR_OR_CONST T half = T(1) / T(2);
    r[0] = (v1[0] + v2[0]) * half;
    r[1] = (v1[1] + v2[1]) * half;
    r[2] = (v1[2] + v2[2]) * half;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The dot product of \a v1 and \a v2:
/// \li if two vectors are perpendicular, result is 0 (angle = 90°, or \a right).
/// \li if two vectors lie in exactly the same direction, result is
/// length(v1)*length(v2) (i.e. > 0, angle < 90° or \a acute) .
/// \li if two vectors point in exactly opposite direction, result is
/// -( length(v1) * length(v2) ) (i.e. < 0, 90° < angle < 180° or \a obtuse).
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \remarks
/// This function computes dot product (AKA \a scalar \a product, \a inner \a
/// product) of two given vectors. It tells how \a similar two vectors are; the
/// larger the dot product, the more similar the two vectors. The dot product is
/// used to calculate the angle between two vectors.
/// \see angle(const vector3<T>&,const vector3<T>&)

template<typename T>
inline T dot(
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    return (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return The length of \p v.
/// \param v The vector with which to compute the length.
/// \pre Only works with float types (e.g. vector3i is not acceptable).
/// \remarks
/// This function computes the length (AKA \a magnitude or \a norm) of the
/// given vector.
/// \see length_sq(const vector3<T>&)

template<typename T>
inline T length(
    const vector3<T>& v)
{
    T r = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    return (r > T(0) ? std::sqrt(r) : T(0.0f));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The square of the length of \p v.
/// \param v The vector with which to compute the squared length.
/// \remarks
/// This function computes the square of the length of the given vector. This
/// can be used in many calculations instead of length(const vector3<T>&) to
/// increase speed by saving you an expensive sqrt() call.
/// \see length(const vector3<T>&)

template<typename T>
inline T length_sq(
    const vector3<T>& v)
{
    return (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle formed between two vectors in radians.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \pre Only works with float types (e.g. vector3i is not acceptable).
/// \remarks
/// This function finds the angle formed between two vectors and returns the
/// result in radians. You can use units::to_degrees for converting to degrees.
/// \image html angle_point.svg
/// \image rtf angle_point.svg
/// \see angle(const point3<T>&,const point3<T>&,const point3<T>&)
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector3 angle

template<typename T>
inline T angle(
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    static_assert(
        std::is_floating_point<T>::value,
        "need a float type :(");

    T len_sq =
        (v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2])
        *
        (v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2]);
    return (len_sq < SMALL
            ? T(0.0)
            : std::acos( (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2])
                         / std::sqrt(len_sq) ) );
}

////////////////////////////////////////////////////////////////////////////////
/// \param v The vector to normalize.
/// \pre Only works with float types (e.g. vector3i is not acceptable).
/// \post length(v) == 1.0 unless length(v) is originally 0.0, in which case it
/// is unchanged.
/// \remarks
/// This function normalizes the given vector in place causing it to be of unit
/// length. If the vector is already of length 1.0, nothing is done.

template<typename T>
inline void normalize(
    vector3<T>& v)
{
    T len_sq = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    if (len_sq > T(0))
    {
        T one_over_len = T(1) / std::sqrt(len_sq);
        v[0] *= one_over_len;
        v[1] *= one_over_len;
        v[2] *= one_over_len;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \return \b true if the vector is normalized, \b false otherwise.
/// \param v The vector to test.
/// \param eps The epsilon tolerance.
/// \remarks
/// This function determines if the given vector is normalized within the given
/// tolerance. The vector is normalized if its lengthSq() is 1.
/// \see length_sq(const vector3<T>&)

template<typename T>
inline bool is_normalized(
    const vector3<T>& v,
    const T eps = T(0.0005) )
{
    BOOST_ASSERT_MSG(eps >= static_cast<T>(0), "negative tolerance!");
    return (std::abs(length_sq(v) - T(1.0)) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a vector that receives the result.
/// \param v Reference to the original vector that we want to reflect.
/// \param n Reference to the normal vector.
/// \post \a r contains the reflected vector.
/// \remarks
/// This method reflects the given vector around the given normal vector. It is
/// similar to if the normal vector was for a plane that you wanted to reflect
/// about. \a v going into the plane, \a n normal to the plane, and \a r coming
/// back out of the plane (see below).
///
/// \image html vector_reflect.png
/// \image rtf vector_reflect.png

template<typename T>
inline vector3<T>& reflect(
    vector3<T>& r,
    const vector3<T>& v,
    const vector3<T>& n)
{
    r = v - ( T(2.0) * (dot(v, n) * n) );
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a result after getting the result of the operation.
/// \param result Reference to a vector that receives the result.
/// \param lerp_val The value to interpolate between \a from and \a to.
/// \param from The vector at \a lerp_val 0.
/// \param to The vector at \a lerp_val 1.
/// \pre   \a lerp_val is a value between 0 and 1 that interpolates
/// between \a from and \a to.
/// \pre   Only works with float types (e.g. vector3i is not acceptable).
/// \post  Undefined if \a lerp_val < 0 or \a lerp_val > 1.
/// \remarks
/// Linearly interpolates between two vectors. For convenience reference to \a
/// result is returned. In this way, it can be used as a parameter for another
/// function.

template<typename T>
inline vector3<T>& lerp(
    vector3<T>& result,
    const T& lerp_val,
    const vector3<T>& from,
    const vector3<T>& to)
{
    result[0] = to[0] - from[0];
    result[0] *= lerp_val;
    result[0] += from[0];
    result[1] = to[1] - from[1];
    result[1] *= lerp_val;
    result[1] += from[1];
    result[2] = to[2] - from[2];
    result[2] *= lerp_val;
    result[2] += from[2];
    return result;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Filled with the result of the cross product between \a v1 and \a v2.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \remarks
/// Computes the cross product (AKA \a outer \a product) between \a v1 and \a v2
/// which is another vector peripendicular to the plane defined by the original
/// two vectors and stores the result in \a r. In a left-handed coordinate
/// system, the direction of the cross product vector would be toward you for
/// a clockwise turn from \a v1 to \a v2 when head of \a v1 aligned with the
/// tail of \a v2. The result is also returned by reference. In this way, it
/// can be used as a parameter for another function.
/// \see cross(const vector3<T>&,const vector3<T>&)

template<typename T>
inline vector3<T>& cross(
    vector3<T>& r,
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    r[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
    r[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
    r[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Cross product vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \remarks
/// Computes the cross product (AKA \a outer \a product) between \a v1 and \a v2
/// which is another vector peripendicular to the plane defined by the original
/// two vectors. In a left-handed coordinate system, the direction of the cross
/// product vector would be toward you for a clockwise turn from \a v1 to \a v2
/// when head of \a v1 aligned with the tail of \a v2.
/// \see cross(vector3<T>&,const vector3<T>&,const vector3<T>&)

template<typename T>
inline vector3<T> cross(
    const vector3<T>& v1,
    const vector3<T>& v2)
{
    vector3<T> r;
    r[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
    r[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
    r[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return Torsion angle formed between three vectors in radians.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \param v3 Reference to the third vector.
/// \pre Only works with float types (e.g. vector3i is not acceptable)
/// \remarks
/// This function finds the torsional (or dihedral) angle formed between vectors
/// \a v1 and \a v3 when viewed along the \a v2. This function assumes IUPAC
/// definition of a torsion angle proposed by W. Klyne and V. Prelog
/// (Experientia, 1960, 16, 521-523), in which an eclipsed conformation
/// corresponds to a torsion angle of 0 degree and a \a trans or \a anti
/// conformation to a torsion angle of 180 degrees. According to this definition
/// if one looks along the vector \a v2, then torsion angle is clockwise rotation
/// of up to 180° necessary to bring the vector \a v1 into an eclipsed position
/// with the \a v3 vector. You can use units::to_degrees for converting the
/// result to degrees.
/// \image html angle_point.svg
/// \image rtf angle_point.svg
/// \see torsion_angle(const point3<T>&,const point3<T>&,const point3<T>&,const point3<T>&)
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector3 torsion angle

template<typename T>
inline T torsion_angle(
    const vector3<T>& v1,
    const vector3<T>& v2,
    const vector3<T>& v3)
{
    static_assert(
        std::is_floating_point<T>::value,
        "need a float type :(");

    // 1st cross product
    T c1x = v2[1]*v1[2] - v2[2]*v1[1];
    T c1y = v2[2]*v1[0] - v2[0]*v1[2];
    T c1z = v2[0]*v1[1] - v2[1]*v1[0];
    // 2nd cross product
    T c2x = v2[1]*v3[2] - v2[2]*v3[1];
    T c2y = v2[2]*v3[0] - v2[0]*v3[2];
    T c2z = v2[0]*v3[0] - v2[1]*v3[0];

    T len_sq = (c1x*c1x + c1y*c1y + c1z*c1z) * (c2x*c2x + c2y*c2y + c2z*c2z);
    if (len_sq < SMALL)
        return T(0.0);
    else
    {
        T ang = std::acos( (c1x*c2x + c1y*c2y + c1z*c2z) / std::sqrt(len_sq) );
        T dot = c2x*v1[0] + c2y*v1[1] + c2z*v1[2];
        return (dot > T(0.0) ? ang : -ang);
    }
}

/// @}
