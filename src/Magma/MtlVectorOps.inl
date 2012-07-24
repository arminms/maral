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
//	MtlVectorOps.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all operations related to vectors.
//------------------------------------------------------------------------------

/// \ingroup Vec2Ops
/// \name Vector2 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if v1 equals v2; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator compares two Vector2 object to see if they
/// are exactly the same .
/// \see operator!=(const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline bool operator== (
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	return (v1[0] == v2[0] && v1[1] == v2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if v1 does not equal v2; \a false otherwise.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator compares two Vector2 object to see if they
/// are NOT exactly the same with zero tolerance.
/// \see operator==(const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline bool operator!= (
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	return (!(v1 == v2));
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
/// \see operator==(const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline bool isEqual(
	const Vector2<T>& v1,
	const Vector2<T>& v2,
	const T eps)
{
	assert(eps >= 0);
	return (abs(v1[0] - v2[0]) <= eps && abs(v1[1] - v2[1]) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v1 after \a v2 has been added to it.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This overloaded operator adds v2 to v1 and stores the result in v1.
/// This is equivalent to the expression v1 = v1 + v2.
/// \see operator+(const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline Vector2<T>& operator+= (
	Vector2<T>& v1,
	const Vector2<T>& v2)
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
/// \see operator+=(Vector2<T>&, const Vector2<T>&)

template<typename T>
inline Vector2<T> operator+ (
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	Vector2<T> r(v1);
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
/// \see operator-(const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline Vector2<T>& operator-= (
	Vector2<T>& v1,
	const Vector2<T>& v2)
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
/// This overloaded operator subtracts v2 from v1 and returns the result.
/// This is equivalent to the expression result = v1 - v2.
/// \see operator-=(Vector2<T>&, const Vector2<T>&),
/// operator-(const Vector2<T>&)

template<typename T>
inline Vector2<T> operator- (
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	Vector2<T> r(v1);
	r -= v2;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a v.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded unary operator changes the sign of each components
/// of a given vector and returns the result as a new vector. This is
/// equivalent to the expression result = -v.
/// \see operator-(const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline Vector2<T> operator- (
	const Vector2<T>& v)
{
	Vector2<T> r(-v[0], -v[1]);
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v after it has been multiplied by \a scalar.
/// \param v Reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \remarks
/// This overloaded operator multiplies \a v by a scalar value and
/// stores the result in \a v. This is equivalent to the expression
/// v = v * scalar.
/// \see operator*(const Vector2<T>&, const T&)

template<typename T>
inline Vector2<T>& operator*= (
	Vector2<T>& v,
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
/// result = v * scalar.
/// \see operator*=(Vector2<T>&, const const T&),
/// operator*(const T&, const Vector2<T>&)

template<typename T>
inline Vector2<T> operator* (
	const Vector2<T>& v,
	const T& scalar)
{
	Vector2<T> r(v);
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
/// \see operator*=(Vector2<T>&, const const T&),
/// operator*(const Vector2<T>&, const T&)

template<typename T>
inline Vector2<T> operator* (
	const T& scalar,
	const Vector2<T>& v)
{
	Vector2<T> r(v);
	r *= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v after it has been divided by \a scalar.
/// \param v Reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \remarks
/// This overloaded operator divides \a v by a scalar value and
/// stores the result in \a v. This is equivalent to the expression
/// v = v / scalar.
/// \see operator/(const Vector2<T>&, const T&)

template<typename T>
inline Vector2<T>& operator/= (
	Vector2<T>& v,
	const T& scalar)
{
	v[0] /= scalar;
	v[1] /= scalar;
	return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of dividing \a v by scalar.
/// \param v Constant reference to the vector to be scaled.
/// \param scalar The amount by which to scale \a v
/// \remarks
/// This overloaded operator divides \a v by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = v / scalar.
/// \see operator*=(Vector2<T>&, const const T&)

template<typename T>
inline Vector2<T> operator/ (
	const Vector2<T>& v,
	const T& scalar)
{
	Vector2<T> r(v);
	r /= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a v1 after \a v2 scaled and has been added to it.
/// \param scalar The amount by which to scale \a v2
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// Call this funtion to scale second vector by \a scalar factor and add
/// it to the first vector simultaneously. This is equivalent to the
/// expression v1 = v2 * scalar.
/// \see sumScaled(const T&, const Vector2<T>&, const Vector2<T>&)

template<typename T>
inline Vector2<T>& addScaled(
	const T& scalar,
	Vector2<T>& v1,
	const Vector2<T>& v2)
{
	v1[0] += scalar * v2[0];
	v1[1] += scalar * v2[1];
	return v1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of scaling \a v2 and adding it to \a v1.
/// \param scalar The amount by which to scale \a v2
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// Call this funtion to get the result of scaling second vector by \a
/// scalar factor and adding it to the first vector. This is equivalent
/// to the expression result = v1 + v2 * scalar.
/// \see addScaled(const T&, Vector2<T>&, const Vector2<T>&)

template<typename T>
inline Vector2<T> sumScaled(
	const T& scalar,
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	Vector2<T> r;
	r[0] = v1[0] + scalar * v2[0];
	r[1] = v1[1] + scalar * v2[1];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after receiving maximum values.
/// \param r Reference to a vector that receives the result.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This function copies maximum values of x and y of \a v1 and
/// \a v2 into \a r and then returns reference to \a r. In this way, it
/// can be used as a parameter for another function.
/// \see minimize(Vector2<T>&,const Vector2<T>&,const Vector2<T>&)

template<typename T>
inline Vector2<T>& maximize(
	Vector2<T>& r,
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	r[0] = v1[0] > v2[0] ? v1[0] : v2[0];
	r[1] = v1[1] > v2[1] ? v1[1] : v2[1];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after receiving minimum values.
/// \param r Reference to a vector that receives the result.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \remarks
/// This function copies minimum values of x and y of \a v1 and
/// \a v2 into \a r and then returns reference to \a r. In this way, it
/// can be used as a parameter for another function.
/// \see maximize(Vector2<T>&,const Vector2<T>&,const Vector2<T>&)

template<typename T>
inline Vector2<T>& minimize(
	Vector2<T>& r,
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	r[0] = v1[0] < v2[0] ? v1[0] : v2[0];
	r[1] = v1[1] < v2[1] ? v1[1] : v2[1];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a vector that receives the result.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \pre Only works with float types (e.g. Vector2i is not acceptable)
/// \remarks
/// This function returns the middle vector between \a v1 and \a
/// v2.

template<typename T>
inline Vector2<T>& middle(
	Vector2<T>& r,
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	r[0] = (v1[0] + v2[0]) * (T)HALF;
	r[1] = (v1[1] + v2[1]) * (T)HALF;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The dot product of \a v1 and \a v2:
/// \li if two vectors are perpendicular, result is 0.
/// \li if two vectors lie in exactly the same direction, result is
/// length(v1)*length(v2).
/// \li if two vectors point in exactly opposite direction, result is
/// -( length(v1) * length(v2) ).
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \remarks
/// This function computes dot product of two given vectors. The dot
/// product is used to calculate the angle between two vectors.
/// \see angle(const Vector2<T>&,const Vector2<T>&)

template<typename T>
inline T dot(
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	return (v1[0]*v2[0] + v1[1]*v2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return The length of \p v.
/// \param v The vector with which to compute the length.
/// \pre Only works with float types (e.g. Vector2i is not acceptable)
/// \remarks
/// This function computes the length of the given vector.
/// \see lengthSq(const Vector2<T>&)

template<typename T>
inline T length(
	const Vector2<T>& v)
{
	T r = lengthSq(v);
	return (r == T(0.0f) ? T(0.0f) : sqrt(r));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The square of the length of \p v.
/// \param v The vector with which to compute the squared length.
/// \remarks
/// This function computes the square of the length of the given
/// vector. This can be used in many calculations instead of
/// length(const Vector2<T>&) to increase speed by saving you an
/// expensive sqrt call.
/// \see length(const Vector2<T>&)

template<typename T>
inline T lengthSq(
	const Vector2<T>& v)
{
	return (v[0]*v[0] + v[1]*v[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in degrees formed between two vectors.
/// \param v1 Reference to the first vector.
/// \param v2 Reference to the second vector.
/// \pre Only works with float types (e.g. Vector2i is not acceptable)
/// \remarks
/// This function finds the angle formed between two vectors and
/// returns the result in degrees.

template<typename T>
inline T angle(
	const Vector2<T>& v1,
	const Vector2<T>& v2)
{
	T lenSq = (v1[0]*v1[0] + v1[1]*v1[1]) * (v2[0]*v2[0] + v2[1]*v2[1]);
	return (lenSq == T(0.0f) ?
		T(0.0f) :
		radian2degree(acos( (v1[0]*v2[0] + v1[1]*v2[1]) / sqrt(lenSq) ) ) );
}

////////////////////////////////////////////////////////////////////////////////
/// \return The length of \p v before it was normalized.
/// \param v The vector to normalize.
/// \pre Only works with float types (e.g. Vector2i is not acceptable)
/// \post length(v) == 1.0 unless length(v) is originally 0.0, in which
/// case it is unchanged
/// \remarks
/// This function normalizes the given vector in place causing it to
/// be of unit length. If the vector is already of length 1.0, nothing
/// is done. For convenience, the original length of the vector is
/// returned.

template<typename T>
inline T normalize(
	Vector2<T>& v)
{
	T len = length(v);
	if (len != T(0.0f))
	{
		v[0] /= len;
		v[1] /= len;
	}
	return len;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \b true if the vector is normalized, \b false otherwise.
/// \param v The vector to test.
/// \param eps The epsilon tolerance.
/// \remarks
/// This function etermines if the given vector is normalized within
/// the given tolerance. The vector is normalized if its lengthSquared
/// is 1
/// \see lengthSq(const Vector2<T>&)

template<typename T>
inline bool isNormalized(
	const Vector2<T>& v,
	const T eps = (T)SMALL)
{
	return isEqual(lengthSq(v), T(1.0), eps);
}

/// @}

