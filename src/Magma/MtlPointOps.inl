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
//	MtlPointOps.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all operations related to points.
//------------------------------------------------------------------------------

/// \ingroup Pnt2Ops
/// \name Point2 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 equals p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two Point2 object to see if they
/// are exactly the same .
/// \see operator!=(const Point2<T>&, const Point2<T>&)

template<typename T>
inline bool operator== (
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	return (p1[0] == p2[0] && p1[1] == p2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 does not equal p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two Point2 object to see if they
/// are NOT exactly the same with zero tolerance.
/// \see operator==(const Point2<T>&, const Point2<T>&)

template<typename T>
inline bool operator!= (
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	return (!(p1 == p2));
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 equals p2 within the tolerance; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param eps The epsilon tolerance value.
/// \pre eps must be >= 0
/// \remarks
/// Compares \a p1 and \a p2 to see if they are the same within the
/// given epsilon tolerance.
/// \see operator==(const Point2<T>&, const Point2<T>&)

template<typename T>
inline bool isEqual(
	const Point2<T>& p1,
	const Point2<T>& p2,
	const T eps)
{
	assert(eps >= 0);
	return (abs(p1[0] - p2[0]) <= eps && abs(p1[1] - p2[1]) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p1 after \a p2 has been added to it.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator adds p2 to p1 and stores the result in p1.
/// This is equivalent to the expression p1 = p1 + p2.
/// \see operator+(const Point2<T>&, const Point2<T>&)

template<typename T>
inline Point2<T>& operator+= (
	Point2<T>& p1,
	const Point2<T>& p2)
{
	p1[0] += p2[0];
	p1[1] += p2[1];
	return p1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of adding \a p2 to \a p1.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator adds p2 to p1 and returns the result.
/// This is equivalent to the expression result = p1 + p2.
/// \see operator+=(Point2<T>&, const Point2<T>&)

template<typename T>
inline Point2<T> operator+ (
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	Point2<T> r(p1);
	r += p2;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p1 after \a p2 has been subtracted from it.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator subtracts p2 from p1 and stores the
/// result in p1. This is equivalent to the expression p1 = p1 - p2.
/// \see operator-(const Point2<T>&, const Point2<T>&)

template<typename T>
inline Point2<T>& operator-= (
	Point2<T>& p1,
	const Point2<T>& p2)
{
	p1[0] -= p2[0];
	p1[1] -= p2[1];
	return p1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of subtracting \a p2 from \a p1.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator subtracts p2 from p1 and returns the result.
/// This is equivalent to the expression result = p1 - p2.
/// \see operator-=(Point2<T>&, const Point2<T>&),
/// operator-(const Point2<T>&)

template<typename T>
inline Point2<T> operator- (
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	Point2<T> r(p1);
	r -= p2;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a p.
/// \param p Reference to the point.
/// \remarks
/// This overloaded unary operator changes the sign of each components
/// of a given point and returns the result as a new point. This is
/// equivalent to the expression result = -p.
/// \see operator-(const Point2<T>&, const Point2<T>&)

template<typename T>
inline Point2<T> operator- (
	const Point2<T>& p)
{
	Point2<T> r(-p[0], -p[1]);
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after it has been multiplied by \a scalar.
/// \param p Reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator multiplies \a p by a scalar value and
/// stores the result in \a p. This is equivalent to the expression
/// p = p * scalar.
/// \see operator*(const Point2<T>&, const T&)

template<typename T>
inline Point2<T>& operator*= (
	Point2<T>& p,
	const T& scalar)
{
	p[0] *= scalar;
	p[1] *= scalar;
	return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a p by scalar.
/// \param p Constant reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator multiplies \a p by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = p * scalar.
/// \see operator*=(Point2<T>&, const const T&),
/// operator*(const T&, const Point2<T>&)

template<typename T>
inline Point2<T> operator* (
	const Point2<T>& p,
	const T& scalar)
{
	Point2<T> r(p);
	r *= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a p by scalar.
/// \param scalar The amount by which to scale \a p
/// \param p Constant reference to the point to be scaled.
/// \remarks
/// This overloaded operator multiplies \a p by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = scalar * p. This is a convenient argument position
/// indifference overloader.
/// \see operator*=(Point2<T>&, const const T&),
/// operator*(const Point2<T>&, const T&)

template<typename T>
inline Point2<T> operator* (
	const T& scalar,
	const Point2<T>& p)
{
	Point2<T> r(p);
	r *= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after it has been divided by \a scalar.
/// \param p Reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator divides \a p by a scalar value and
/// stores the result in \a p. This is equivalent to the expression
/// p = p / scalar.
/// \see operator/(const Point2<T>&, const T&)

template<typename T>
inline Point2<T>& operator/= (
	Point2<T>& p,
	const T& scalar)
{
	p[0] /= scalar;
	p[1] /= scalar;
	return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of dividing \a p by scalar.
/// \param p Constant reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator divides \a p by a scalar value and
/// returns the result. This is equivalent to the expression
/// result = p / scalar.
/// \see operator*=(Point2<T>&, const const T&)

template<typename T>
inline Point2<T> operator/ (
	const Point2<T>& p,
	const T& scalar)
{
	Point2<T> r(p);
	r /= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p1 after \a p2 scaled and has been added to it.
/// \param scalar The amount by which to scale \a p2
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// Call this funtion to scale second point by \a scalar factor and add
/// it to the first point simultaneously. This is equivalent to the
/// expression p1 = p2 * scalar.
/// \see sumScaled(const T&, const Point2<T>&, const Point2<T>&)

template<typename T>
inline Point2<T>& addScaled(
	const T& scalar,
	Point2<T>& p1,
	const Point2<T>& p2)
{
	p1[0] += scalar * p2[0];
	p1[1] += scalar * p2[1];
	return p1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of scaling \a p2 and adding it to \a p1.
/// \param scalar The amount by which to scale \a p2
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// Call this funtion to get the result of scaling second point by \a
/// scalar factor and adding it to the first point. This is equivalent
/// to the expression result = p1 + p2 * scalar.
/// \see addScaled(const T&, Point2<T>&, const Point2<T>&)

template<typename T>
inline Point2<T> sumScaled(
	const T& scalar,
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	Point2<T> r;
	r[0] = p1[0] + scalar * p2[0];
	r[1] = p1[1] + scalar * p2[1];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after receiving maximum values.
/// \param r Reference to a point that receives the result.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function copies maximum values of x and y of \a p1 and
/// \a p2 into \a r and then returns reference to \a r. In this way, it
/// can be used as a parameter for another function.
/// \see minimize(Point2<T>&,const Point2<T>&,const Point2<T>&)

template<typename T>
inline Point2<T>& maximize(
	Point2<T>& r,
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	r[0] = p1[0] > p2[0] ? p1[0] : p2[0];
	r[1] = p1[1] > p2[1] ? p1[1] : p2[1];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after receiving minimum values.
/// \param r Reference to a point that receives the result.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function copies minimum values of x and y of \a p1 and
/// \a p2 into \a r and then returns reference to \a r. In this way, it
/// can be used as a parameter for another function.
/// \see maximize(Point2<T>&,const Point2<T>&,const Point2<T>&)

template<typename T>
inline Point2<T>& minimize(
	Point2<T>& r,
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	r[0] = p1[0] < p2[0] ? p1[0] : p2[0];
	r[1] = p1[1] < p2[1] ? p1[1] : p2[1];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a point that receives the result.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \pre Only works with float types (e.g. Point2i is not acceptable)
/// \remarks
/// This function returns the middle point between \a p1 and \a
/// p2.

template<typename T>
inline Point2<T>& middle(
	Point2<T>& r,
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	r[0] = (p1[0] + p2[0]) * (T)HALF;
	r[1] = (p1[1] + p2[1]) * (T)HALF;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \pre Only works with float types (e.g. Point2i is not acceptable)
/// \remarks
/// This function finds distance between two given points.
/// \see distanceSq(const Point2<T>&, const Point2<T>&)

template<typename T>
inline T distance(
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	T r = distanceSq(p1, p2);
	return (r == T(0.0f) ? T(0.0f) : sqrt(r));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The squared distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function finds squared distance between two points. This can
/// be used in many calculations instead of
/// distance(const Point2<T>&, const Point2<T>&) to increase speed by
/// saving you an expensive sqrt call.
/// \see distance(const Point2<T>&, const Point2<T>&)

template<typename T>
inline T distanceSq(
	const Point2<T>& p1,
	const Point2<T>& p2)
{
	Point2<T> r = p1 - p2;
	return (r[0]*r[0] + r[1]*r[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in degrees formed between three points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param p3 Reference to the third point.
/// \pre Only works with float types (e.g. Point2i is not acceptable)
/// \remarks
/// This function finds the angle formed between the vector from point \a p2 to
/// \a p1 and the vector from point \a p2 to \a p3 and returns the result in
/// degrees.

template<typename T>
inline T angle(
	const Point2<T>& p1,
	const Point2<T>& p2,
	const Point2<T>& p3)
{
	Point2<T> r1 = p1 - p2;
	Point2<T> r2 = p3 - p2;
	T lenSq = (r1[0]*r1[0] + r1[1]*r1[1]) * (r2[0]*r2[0] + r2[1]*r2[1]);
	return (lenSq < SMALL ?
		T(0.0f) :
		radian2degree(acos( (r1[0]*r2[0] + r1[1]*r2[1]) / sqrt(lenSq) ) ) );
}

/// @}

/// \ingroup Pnt3Ops
/// \name Point3 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 equals p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two Point3 object to see if they are
/// exactly the same .
/// \see operator!=(const Point3<T>&, const Point3<T>&)

template<typename T>
inline bool operator== (
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	return (p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if \a p1
/// does not equal \a p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two Point3 object to see if they are NOT
/// exactly the same with zero tolerance.
/// \see operator==(const Point3<T>&, const Point3<T>&)

template<typename T>
inline bool operator!= (
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	return (!(p1 == p2));
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if \a p1
/// equals p2 within the tolerance; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param eps The epsilon tolerance value.
/// \pre eps must be >= 0
/// \remarks
/// Compares \a p1 and \a p2 to see if they are the same within the given
/// epsilon tolerance.
/// \see operator==(const Point3<T>&, const Point3<T>&)

template<typename T>
inline bool isEqual(
	const Point3<T>& p1,
	const Point3<T>& p2,
	const T eps)
{
	assert(eps >= 0);
	return (abs(p1[0] - p2[0]) <= eps &&
		abs(p1[1] - p2[1]) <= eps &&
		abs(p1[2] - p2[2]) <= eps );
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p1 after \a p2 has been added to it.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator adds p2 to p1 and stores the result in p1. This is
/// equivalent to the expression p1 = p1 + p2.
/// \see operator+(const Point3<T>&, const Point3<T>&)

template<typename T>
inline Point3<T>& operator+= (
	Point3<T>& p1,
	const Point3<T>& p2)
{
	p1[0] += p2[0];
	p1[1] += p2[1];
	p1[2] += p2[2];
	return p1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of adding \a p2 to \a p1.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator adds \a p2 to \a p1 and returns the result. This is
/// equivalent to the expression result = p1 + p2.
/// \see operator+=(Point3<T>&, const Point3<T>&)

template<typename T>
inline Point3<T> operator+ (
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	Point3<T> r(p1);
	r += p2;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p1 after \a p2 has been subtracted from it.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator subtracts \a p2 from \a p1 and stores the result in
/// \a p1. This is equivalent to the expression p1 = p1 - p2.
/// \see operator-(const Point3<T>&, const Point3<T>&)

template<typename T>
inline Point3<T>& operator-= (
	Point3<T>& p1,
	const Point3<T>& p2)
{
	p1[0] -= p2[0];
	p1[1] -= p2[1];
	p1[2] -= p2[2];
	return p1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of subtracting \a p2 from \a p1.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator subtracts \a p2 from \a p1 and returns the result.
/// This is equivalent to the expression result = p1 - p2.
/// \see operator-=(Point3<T>&, const Point3<T>&), operator-(const Point3<T>&)

template<typename T>
inline Point3<T> operator- (
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	Point3<T> r(p1);
	r -= p2;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a p.
/// \param p Reference to the point.
/// \remarks
/// This overloaded unary operator changes the sign of each components of a
/// given point and returns the result as a new point. This is
/// equivalent to the expression result = -p.
/// \see operator-(const Point3<T>&, const Point3<T>&)

template<typename T>
inline Point3<T> operator- (
	const Point3<T>& p)
{
	Point3<T> r(-p[0], -p[1], -p[2]);
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after it has been multiplied by \a scalar.
/// \param p Reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator multiplies \a p by a scalar value and stores the
/// result in \a p. This is equivalent to the expression p = p * scalar.
/// \see operator*(const Point3<T>&, const T&)

template<typename T>
inline Point3<T>& operator*= (
	Point3<T>& p,
	const T& scalar)
{
	p[0] *= scalar;
	p[1] *= scalar;
	p[2] *= scalar;
	return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a p by scalar.
/// \param p Constant reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator multiplies \a p by a scalar value and returns the
/// result. This is equivalent to the expression result = p * scalar.
/// \see operator*=(Point3<T>&, const const T&),
/// operator*(const T&, const Point3<T>&)

template<typename T>
inline Point3<T> operator* (
	const Point3<T>& p,
	const T& scalar)
{
	Point3<T> r(p);
	r *= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of multiplying \a p by scalar.
/// \param scalar The amount by which to scale \a p
/// \param p Constant reference to the point to be scaled.
/// \remarks
/// This overloaded operator multiplies \a p by a scalar value and returns the
/// result. This is equivalent to the expression result = scalar * p. This is a
/// convenient argument position indifference overloader.
/// \see operator*=(Point3<T>&, const const T&),
/// operator*(const Point3<T>&, const T&)

template<typename T>
inline Point3<T> operator* (
	const T& scalar,
	const Point3<T>& p)
{
	Point3<T> r(p);
	r *= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after it has been divided by \a scalar.
/// \param p Reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator divides \a p by a scalar value and stores the
/// result in \a p. This is equivalent to the expression p = p / scalar.
/// \see operator/(const Point3<T>&, const T&)

template<typename T>
inline Point3<T>& operator/= (
	Point3<T>& p,
	const T& scalar)
{
	p[0] /= scalar;
	p[1] /= scalar;
	p[2] /= scalar;
	return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of dividing \a p by scalar.
/// \param p Constant reference to the point to be scaled.
/// \param scalar The amount by which to scale \a p
/// \remarks
/// This overloaded operator divides \a p by a scalar value and returns the
/// result. This is equivalent to the expression result = p / scalar.
/// \see operator*=(Point3<T>&, const const T&)

template<typename T>
inline Point3<T> operator/ (
	const Point3<T>& p,
	const T& scalar)
{
	Point3<T> r(p);
	r /= scalar;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p1 after \a p2 scaled and has been added to it.
/// \param scalar The amount by which to scale \a p2
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// Call this funtion to scale second point by \a scalar factor and add it to
/// the first point simultaneously. This is equivalent to the expression
/// p1 = p2 * scalar.
/// \see sumScaled(const T&, const Point3<T>&, const Point3<T>&)

template<typename T>
inline Point3<T>& addScaled(
	const T& scalar,
	Point3<T>& p1,
	const Point3<T>& p2)
{
	p1[0] += scalar * p2[0];
	p1[1] += scalar * p2[1];
	p1[2] += scalar * p2[2];
	return p1;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of scaling \a p2 and adding it to \a p1.
/// \param scalar The amount by which to scale \a p2
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// Call this funtion to get the result of scaling second point by \a scalar
/// factor and adding it to the first point. This is equivalent to the
/// expression result = p1 + p2 * scalar.
/// \see addScaled(const T&, Point3<T>&, const Point3<T>&)

template<typename T>
inline Point3<T> sumScaled(
	const T& scalar,
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	Point3<T> r;
	r[0] = p1[0] + scalar * p2[0];
	r[1] = p1[1] + scalar * p2[1];
	r[2] = p1[2] + scalar * p2[2];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after receiving maximum values.
/// \param r Reference to a point that receives the result.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function copies maximum values of x and y of \a p1 and \a p2 into \a r
/// and then returns reference to \a r. In this way, it can be used as a
/// parameter for another function.
/// \see minimize(Point3<T>&,const Point3<T>&,const Point3<T>&)

template<typename T>
inline Point3<T>& maximize(
	Point3<T>& r,
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	r[0] = p1[0] > p2[0] ? p1[0] : p2[0];
	r[1] = p1[1] > p2[1] ? p1[1] : p2[1];
	r[2] = p1[2] > p2[2] ? p1[2] : p2[2];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after receiving minimum values.
/// \param r Reference to a point that receives the result.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function copies minimum values of x and y of \a p1 and \a p2 into \a r
/// and then returns reference to \a r. In this way, it can be used as a
/// parameter for another function.
/// \see maximize(Point3<T>&,const Point3<T>&,const Point3<T>&)

template<typename T>
inline Point3<T>& minimize(
	Point3<T>& r,
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	r[0] = p1[0] < p2[0] ? p1[0] : p2[0];
	r[1] = p1[1] < p2[1] ? p1[1] : p2[1];
	r[2] = p1[2] < p2[2] ? p1[2] : p2[2];
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a r after getting the result of the operation.
/// \param r Reference to a point that receives the result.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \pre Only works with float types (e.g. Point3i is not acceptable)
/// \remarks
/// This function returns the middle point between \a p1 and \a p2.

template<typename T>
inline Point3<T>& middle(
	Point3<T>& r,
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	r[0] = (p1[0] + p2[0]) * (T)HALF;
	r[1] = (p1[1] + p2[1]) * (T)HALF;
	r[2] = (p1[2] + p2[2]) * (T)HALF;
	return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \pre Only works with float types (e.g. Point3i is not acceptable)
/// \remarks
/// This function finds distance between two given points.
/// \see distanceSq(const Point3<T>&, const Point3<T>&)

template<typename T>
inline T distance(
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	T r = distanceSq(p1, p2);
	return (r == T(0.0f) ? T(0.0f) : sqrt(r));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The squared distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function finds squared distance between two points. This can be used
/// in many calculations instead of distance(const Point3<T>&, const Point3<T>&)
/// to increase speed by saving you an expensive sqrt() call.
/// \see distance(const Point3<T>&, const Point3<T>&)

template<typename T>
inline T distanceSq(
	const Point3<T>& p1,
	const Point3<T>& p2)
{
	Point3<T> r = p1 - p2;
	return (r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in degrees formed between three points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param p3 Reference to the third point.
/// \pre Only works with float types (e.g. Point3i is not acceptable)
/// \remarks
/// This function finds the angle formed between the vector from point \a p2 to
/// \a p1 and the vector from point \a p2 to \a p3 and returns the result in
/// degrees.
/// \see angle(const Vector3<T>&,const Vector3<T>&)

template<typename T>
inline T angle(
	const Point3<T>& p1,
	const Point3<T>& p2,
	const Point3<T>& p3)
{
	Point3<T> r1 = p1 - p2;
	Point3<T> r2 = p3 - p2;
	T lenSq = (r1[0]*r1[0] + r1[1]*r1[1] + r1[2]*r1[2]) *
		(r2[0]*r2[0] + r2[1]*r2[1] + r2[2]*r2[2]);
	return (lenSq < SMALL ?
		T(0.0) :
		radian2degree(acos(
			(r1[0]*r2[0] + r1[1]*r2[1] + r1[2]*r2[2]) / sqrt(lenSq) ) ) );
}

////////////////////////////////////////////////////////////////////////////////
/// \return Torsion angle in degrees formed between four points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param p3 Reference to the third point.
/// \param p4 Reference to the fourth point.
/// \pre Only works with float types (e.g. Point3i is not acceptable)
/// \remarks
/// This function finds the torsional (or dihedral) angle formed between vectors
/// \a p2 -> \a p1 and \a p3 -> \a p4 when viewed along the vector from \a p2 to
/// \a p3. This function assumes IUPAC definition of a torsion angle proposed by
/// W. Klyne and V. Prelog (Experientia, 1960, 16, 521-523), in which an
/// eclipsed conformation corresponds to a torsion angle of 0 degree and a \a
/// trans or \a anti conformation to a torsion angle of 180 degrees. According
/// to this definition if one looks along the vector \a p2 -> \a p3, then
/// torsion angle is clockwise rotation of up to 180° necessary to bring the
/// vector \a p2 -> \a p1 into an eclipsed position with the \a p3 -> \a p4
/// vector.
/// \see torsionAngle(const Vector3<T>&,const Vector3<T>&,const Vector3<T>&)

template<typename T>
inline T torsionAngle(
	const Point3<T>& p1,
	const Point3<T>& p2,
	const Point3<T>& p3,
	const Point3<T>& p4)
{
	// 1st vector
	T x1 = p1[0] - p2[0];
	T y1 = p1[1] - p2[1];
	T z1 = p1[2] - p2[2];
	// 2nd vector (pivot)
	T x2 = p3[0] - p2[0];
	T y2 = p3[1] - p2[1];
	T z2 = p3[2] - p2[2];
	// 3rd vector
	T x3 = p4[0] - p3[0];
	T y3 = p4[1] - p3[1];
	T z3 = p4[2] - p3[2];
	// 1st cross product
	T c1x = y2*z1 - z2*y1;
	T c1y = z2*x1 - x2*z1;
	T c1z = x2*y1 - y2*x1;
	// 2nd cross product
	T c2x = y2*z3 - z2*y3;
	T c2y = z2*x3 - x2*z3;
	T c2z = x2*y3 - y2*x3;

	T lenSq = (c1x*c1x + c1y*c1y + c1z*c1z) * (c2x*c2x + c2y*c2y + c2z*c2z);
	if (lenSq < SMALL)
		return T(0.0);
	else
	{
		T rad = (c1x*c2x + c1y*c2y + c1z*c2z) / sqrt(lenSq);
		T angle = radian2degree(acos(rad));
		T dot = c2x*x1 + c2y*y1 + c2z*z1;
		return (dot > T(0.0) ? angle : -angle);
	}
}

/// @}
