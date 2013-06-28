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
//    point_ops.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains inlines for all operations related to points.
//------------------------------------------------------------------------------

/// \ingroup pnt2ops
/// \name point2 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 equals p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two point2 object to see if they
/// are exactly the same .
/// \see operator!=(const point2<T>&, const point2<T>&)

template<typename T>
inline bool operator== (
    const point2<T>& p1,
    const point2<T>& p2)
{
    return (p1[0] == p2[0] && p1[1] == p2[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 does not equal p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two point2 object to see if they
/// are NOT exactly the same with zero tolerance.
/// \see operator==(const point2<T>&, const point2<T>&)

template<typename T>
inline bool operator!= (
    const point2<T>& p1,
    const point2<T>& p2)
{
    return (p1[0] != p2[0] || p1[1] != p2[1]);
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
/// \see operator==(const point2<T>&, const point2<T>&)

template<typename T>
inline bool is_equal(
    const point2<T>& p1,
    const point2<T>& p2,
    const T eps)
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (abs(p1[0] - p2[0]) <= eps && abs(p1[1] - p2[1]) <= eps);
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after \a v has been added to it.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator adds \a v to \a p and stores the result in \a p.
/// This is equivalent to the expression p = p + v.
/// \see operator+(const point2<T>&, const vector2<T>&)

template<typename T>
inline point2<T>& operator+= (
    point2<T>& p,
    const vector2<T>& v)
{
    p[0] += v[0];
    p[1] += v[1];
    return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of adding \a v to \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator adds \a v to \a p and returns the result. This is
/// equivalent to the expression result = p + v.
/// \see operator+=(point2<T>&, const vector2<T>&)

template<typename T>
inline point2<T> operator+ (
    const point2<T>& p,
    const vector2<T>& v)
{
    point2<T> r(p);
    r += v;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after \a v has been subtracted from it.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator subtracts \a v from \a p and stores the result in
/// \a p. This is equivalent to the expression p = p - v.
/// \see operator-(const point2<T>&, const vector2<T>&)

template<typename T>
inline point2<T>& operator-= (
    point2<T>& p,
    const vector2<T>& v)
{
    p[0] -= v[0];
    p[1] -= v[1];
    return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The resulting vector.
/// \param p1 A point2 object that specify start \a (tail) of the vector.
/// \param p2 A point2 object that specify end \a (head) of the vector.
/// \remarks
/// This overloaded operator returns a vector2 from 2 supplied point2
/// objects. The resulting vector is from \a p1 (tail) to \a p2 (head).
/// \see vector2<T>::vector2(const point2<T>&, const point2<T>&)

template<typename T>
inline vector2<T> operator- (
    const point2<T>& p1,
    const point2<T>& p2)
{
    vector2<T> v(p1, p2);
    return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of subtracting \a v from \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator subtracts \a v from \a p and returns the result.
/// This is equivalent to the expression result = p - v.
/// \see operator-=(point2<T>&, const vector2<T>&),
/// operator-(const point2<T>&)

template<typename T>
inline point2<T> operator- (
    const point2<T>& p,
    const vector2<T>& v)
{
    point2<T> r(p);
    r -= v;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a p.
/// \param p Reference to the point.
/// \remarks
/// This overloaded unary operator changes the sign of each components
/// of a given point and returns the result as a new point. This is
/// equivalent to the expression result = -p.
/// \see operator-(const point2<T>&, const point2<T>&)

template<typename T>
inline point2<T> operator- (
    const point2<T>& p)
{
    point2<T> r(-p[0], -p[1]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after \a v scaled and has been added to it.
/// \param scalar The amount by which to scale \a v
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// Call this funtion to scale a vector by \a scalar factor and add it to a
/// point simultaneously. This is equivalent to the expression p = p + v *
/// scalar.
/// \see sum_scaled(const T&, const point2<T>&, const vector2<T>&)

template<typename T>
inline point2<T>& add_scaled(
    const T& scalar,
    point2<T>& p,
    const vector2<T>& v)
{
    p[0] += scalar * v[0];
    p[1] += scalar * v[1];
    return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of scaling \a v and adding it to \a p.
/// \param scalar The amount by which to scale \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// Call this funtion to get the result of scaling a vector by \a scalar factor
/// and adding it to a point. This is equivalent to the expression result = p +
/// v * scalar.
/// \see add_scaled(const T&, point2<T>&, const vector2<T>&)

template<typename T>
inline point2<T> sum_scaled(
    const T& scalar,
    const point2<T>& p,
    const vector2<T>& v)
{
    point2<T> r;
    r[0] = p[0] + scalar * v[0];
    r[1] = p[1] + scalar * v[1];
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
/// \see minimize(point2<T>&,const point2<T>&,const point2<T>&)

template<typename T>
inline point2<T>& maximize(
    point2<T>& r,
    const point2<T>& p1,
    const point2<T>& p2)
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
/// \see maximize(point2<T>&,const point2<T>&,const point2<T>&)

template<typename T>
inline point2<T>& minimize(
    point2<T>& r,
    const point2<T>& p1,
    const point2<T>& p2)
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
/// \pre Only works with float types (e.g. point2i is not acceptable)
/// \remarks
/// This function returns the middle point between \a p1 and \a
/// p2.

template<typename T>
inline point2<T>& middle(
    point2<T>& r,
    const point2<T>& p1,
    const point2<T>& p2)
{
    r[0] = (p1[0] + p2[0]) * (T)HALF;
    r[1] = (p1[1] + p2[1]) * (T)HALF;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \pre Only works with float types (e.g. point2i is not acceptable)
/// \remarks
/// This function finds distance between two given points.
/// \see distance_sq(const point2<T>&, const point2<T>&)

template<typename T>
inline T distance(
    const point2<T>& p1,
    const point2<T>& p2)
{
    T v[2];
    v[0] = p2[0] - p1[0];
    v[1] = p2[1] - p1[1];
    T r = v[0]*v[0] + v[1]*v[1];
    return (r > T(0) ? sqrt(r) : T(0));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The squared distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function finds squared distance between two points. This can
/// be used in many calculations instead of
/// distance(const point2<T>&, const point2<T>&) to increase speed by
/// saving you an expensive sqrt call.
/// \see distance(const point2<T>&, const point2<T>&)

template<typename T>
inline T distance_sq(
    const point2<T>& p1,
    const point2<T>& p2)
{
    T v[2];
    v[0] = p2[0] - p1[0];
    v[1] = p2[1] - p1[1];
    return (v[0]*v[0] + v[1]*v[1]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in degrees formed between three points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param p3 Reference to the third point.
/// \pre Only works with float types (e.g. point2i is not acceptable)
/// \remarks
/// This function finds the angle formed between the vector from point \a p2 to
/// \a p1 and the vector from point \a p2 to \a p3 and returns the result in
/// degrees.
/// \image html angle_point.svg
/// \image rtf angle_point.svg
/// \see angle(const vector2<T>&,const vector2<T>&)

template<typename T>
inline T angle(
    const point2<T>& p1,
    const point2<T>& p2,
    const point2<T>& p3)
{
    vector2<T> r1(p2, p1);
    vector2<T> r2(p2, p3);
    T len_sq = (r1[0]*r1[0] + r1[1]*r1[1]) * (r2[0]*r2[0] + r2[1]*r2[1]);
    return (len_sq < SMALL ?
        T(0.0f) :
        radian2degree(acos( (r1[0]*r2[0] + r1[1]*r2[1]) / sqrt(len_sq) ) ) );
}

/// @}

/// \ingroup pnt3ops
/// \name point3 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true
/// if p1 equals p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two point3 object to see if they are
/// exactly the same .
/// \see operator!=(const point3<T>&, const point3<T>&)

template<typename T>
inline bool operator== (
    const point3<T>& p1,
    const point3<T>& p2)
{
    return (p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if \a p1
/// does not equal \a p2; \a false otherwise.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This overloaded operator compares two point3 object to see if they are NOT
/// exactly the same with zero tolerance.
/// \see operator==(const point3<T>&, const point3<T>&)

template<typename T>
inline bool operator!= (
    const point3<T>& p1,
    const point3<T>& p2)
{
    return (p1[0] != p2[0] || p1[1] != p2[1] || p1[2] != p2[2]);
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
/// \see operator==(const point3<T>&, const point3<T>&)

template<typename T>
inline bool is_equal(
    const point3<T>& p1,
    const point3<T>& p2,
    const T eps)
{
    BOOST_ASSERT_MSG(eps >= 0, "negative tolerance!");
    return (abs(p1[0] - p2[0]) <= eps &&
        abs(p1[1] - p2[1]) <= eps &&
        abs(p1[2] - p2[2]) <= eps );
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after \a v has been added to it.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator adds \a v to \a p and stores the result in \a p.
/// This is equivalent to the expression p = p + v.
/// \see operator+(const point3<T>&, const vector3<T>&)

template<typename T>
inline point3<T>& operator+= (
    point3<T>& p,
    const vector3<T>& v)
{
    p[0] += v[0];
    p[1] += v[1];
    p[2] += v[2];
    return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of adding \a v to \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator adds \a v to \a p and returns the result. This is
/// equivalent to the expression result = p + v.
/// \see operator+=(point3<T>&, const vector3<T>&)

template<typename T>
inline point3<T> operator+ (
    const point3<T>& p,
    const vector3<T>& v)
{
    point3<T> r(p);
    r += v;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after \a v has been subtracted from it.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator subtracts \a v from \a p and stores the result in
/// \a p. This is equivalent to the expression p = p - v.
/// \see operator-(const point3<T>&, const vector3<T>&)

template<typename T>
inline point3<T>& operator-= (
    point3<T>& p,
    const vector3<T>& v)
{
    p[0] -= v[0];
    p[1] -= v[1];
    p[2] -= v[2];
    return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The resulting vector.
/// \param p1 A point2 object that specify start \a (tail) of the vector.
/// \param p2 A point2 object that specify end \a (head) of the vector.
/// \remarks
/// This overloaded operator returns a vector3 object from 2 supplied point3
/// objects. The resulting vector is from \a p1 (tail) to \a p2 (head).
/// \see vector3<T>::vector3(const point3<T>&, const point3<T>&)

template<typename T>
inline vector3<T> operator- (
    const point3<T>& p1,
    const point3<T>& p2)
{
    vector3<T> v(p1, p2);
    return v;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of subtracting \a v from \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// This overloaded operator subtracts \a v from \a p and returns the result.
/// This is equivalent to the expression result = p - v.
/// \see operator-=(point3<T>&, const vector3<T>&), operator-(const point3<T>&)

template<typename T>
inline point3<T> operator- (
    const point3<T>& p,
    const vector3<T>& v)
{
    point3<T> r(p);
    r -= v;
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of negating \a p.
/// \param p Reference to the point.
/// \remarks
/// This overloaded unary operator changes the sign of each components of a
/// given point and returns the result as a new point. This is
/// equivalent to the expression result = -p.
/// \see operator-(const point3<T>&, const point3<T>&)

template<typename T>
inline point3<T> operator- (
    const point3<T>& p)
{
    point3<T> r(-p[0], -p[1], -p[2]);
    return r;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \a p after \a v scaled and has been added to it.
/// \param scalar The amount by which to scale \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// Call this funtion to scale a vector by \a scalar factor and add it to a
/// point simultaneously. This is equivalent to the expression
/// p = p + v * scalar.
/// \see sum_scaled(const T&, const point3<T>&, const vector3<T>&)

template<typename T>
inline point3<T>& add_scaled(
    const T& scalar,
    point3<T>& p,
    const vector3<T>& v)
{
    p[0] += scalar * v[0];
    p[1] += scalar * v[1];
    p[2] += scalar * v[2];
    return p;
}

////////////////////////////////////////////////////////////////////////////////
/// \return The result of scaling \a v and adding it to \a p.
/// \param scalar The amount by which to scale \a p.
/// \param p Reference to the point.
/// \param v Reference to the vector.
/// \remarks
/// Call this funtion to get the result of scaling a vector by \a scalar factor
/// and adding it to a point. This is equivalent to the expression
/// result = p + v * scalar.
/// \see add_scaled(const T&, point3<T>&, const vector3<T>&)

template<typename T>
inline point3<T> sum_scaled(
    const T& scalar,
    const point3<T>& p,
    const vector3<T>& v)
{
    point3<T> r;
    r[0] = p[0] + scalar * v[0];
    r[1] = p[1] + scalar * v[1];
    r[2] = p[2] + scalar * v[2];
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
/// \see minimize(point3<T>&,const point3<T>&,const point3<T>&)

template<typename T>
inline point3<T>& maximize(
    point3<T>& r,
    const point3<T>& p1,
    const point3<T>& p2)
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
/// \see maximize(point3<T>&,const point3<T>&,const point3<T>&)

template<typename T>
inline point3<T>& minimize(
    point3<T>& r,
    const point3<T>& p1,
    const point3<T>& p2)
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
/// \pre Only works with float types (e.g. point3i is not acceptable)
/// \remarks
/// This function returns the middle point between \a p1 and \a p2.

template<typename T>
inline point3<T>& middle(
    point3<T>& r,
    const point3<T>& p1,
    const point3<T>& p2)
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
/// \pre Only works with float types (e.g. point3i is not acceptable)
/// \remarks
/// This function finds distance between two given points.
/// \see distance_sq(const point3<T>&, const point3<T>&)

template<typename T>
inline T distance(
    const point3<T>& p1,
    const point3<T>& p2)
{
    T v[3];
    v[0] = p2[0] - p1[0];
    v[1] = p2[1] - p1[1];
    v[2] = p2[2] - p1[2];
    T r = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    return (r > T(0) ? sqrt(r) : T(0));
}

////////////////////////////////////////////////////////////////////////////////
/// \return The squared distance between two points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \remarks
/// This function finds squared distance between two points. This can be used
/// in many calculations instead of distance(const point3<T>&, const point3<T>&)
/// to increase speed by saving you an expensive sqrt() call.
/// \see distance(const point3<T>&, const point3<T>&)

template<typename T>
inline T distance_sq(
    const point3<T>& p1,
    const point3<T>& p2)
{
    T v[3];
    v[0] = p2[0] - p1[0];
    v[1] = p2[1] - p1[1];
    v[2] = p2[2] - p1[2];
    return (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in degrees formed between three points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param p3 Reference to the third point.
/// \pre Only works with float types (e.g. point3i is not acceptable)
/// \remarks
/// This function finds the angle formed between the vector from point \a p2 to
/// \a p1 and the vector from point \a p2 to \a p3 and returns the result in
/// degrees.
/// \image html angle_point.svg
/// \image rtf angle_point.svg
/// \see angle(const vector3<T>&,const vector3<T>&)

template<typename T>
inline T angle(
    const point3<T>& p1,
    const point3<T>& p2,
    const point3<T>& p3)
{
    vector3<T> r1(p2, p1);
    vector3<T> r2(p2, p3);
    T len_sq = (r1[0]*r1[0] + r1[1]*r1[1] + r1[2]*r1[2]) *
        (r2[0]*r2[0] + r2[1]*r2[1] + r2[2]*r2[2]);
    return (len_sq < SMALL ?
        T(0.0) :
        radian2degree(acos(
            (r1[0]*r2[0] + r1[1]*r2[1] + r1[2]*r2[2]) / sqrt(len_sq) ) ) );
}

////////////////////////////////////////////////////////////////////////////////
/// \return Torsion angle in degrees formed between four points.
/// \param p1 Reference to the first point.
/// \param p2 Reference to the second point.
/// \param p3 Reference to the third point.
/// \param p4 Reference to the fourth point.
/// \pre Only works with float types (e.g. point3i is not acceptable)
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
/// \see torsion_angle(const vector3<T>&,const vector3<T>&,const vector3<T>&)

template<typename T>
inline T torsion_angle(
    const point3<T>& p1,
    const point3<T>& p2,
    const point3<T>& p3,
    const point3<T>& p4)
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

    T len_sq = (c1x*c1x + c1y*c1y + c1z*c1z) * (c2x*c2x + c2y*c2y + c2z*c2z);
    if (len_sq < SMALL)
        return T(0.0);
    else
    {
        T rad = (c1x*c2x + c1y*c2y + c1z*c2z) / sqrt(len_sq);
        T angle = radian2degree(acos(rad));
        T dot = c2x*x1 + c2y*y1 + c2z*z1;
        return (dot > T(0.0) ? angle : -angle);
    }
}

/// @}
