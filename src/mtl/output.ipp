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
// $Id: MtlOutput.inl 30 2012-09-21 12:47:14Z armin $
//------------------------------------------------------------------------------
// Filename:
//    output.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains inlines for all output stream operators.
//------------------------------------------------------------------------------

/// \ingroup Output
/// \name Output Stream Operators
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out the stream to write to.
/// \param p the point2 type to output.
/// \remarks
/// Outputs a string representation of the given point2 type to the
/// given output stream. The output is formatted such that
/// point2<int>(1,2) will appear as "[1,2]".

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const point2<T>& p)
{
    out << '[' << p[0] << ',' << p[1] << ']';
    return out;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out The stream to write to.
/// \param v The vector2 type to output.
/// \remarks
/// Outputs a string representation of the given vector2 type to the
/// given output stream. The output is formatted such that
/// vector2<int>(1,2) will appear as "[1,2]".

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const vector2<T>& v)
{
    out << '[' << v[0] << ',' << v[1] << ']';
    return out;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out the stream to write to.
/// \param p the point3 type to output.
/// \remarks
/// Outputs a string representation of the given point3 type to the
/// given output stream. The output is formatted such that
/// point3<int>(1,2,3) will appear as "[1,2,3]".

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const point3<T>& p)
{
    out << '[' << p[0] << ',' << p[1] << ',' << p[2] << ']';
    return out;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out The stream to write to.
/// \param v The vector3 type to output.
/// \remarks
/// Outputs a string representation of the given vector3 type to the
/// given output stream. The output is formatted such that
/// vector3<int>(1,2,3) will appear as "[1,2,3]".

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const vector3<T>& v)
{
    out << '[' << v[0] << ',' << v[1] << ',' << v[2] << ']';
    return out;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out The stream to write to.
/// \param m The matrix22 type to output.
/// \remarks
/// Outputs a string representation of the given matrix22 type to the given
/// output stream. The output is formatted such that
/// matrix22<int> m {1,2,3,4)} will appear as:
/// <pre>
///    | 1 3 |
///    | 2 4 |
/// </pre>

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const matrix22<T>& m)
{
    out << "| " << m(0, 0) << ' ' << m(0, 1) << " |\n";
    out << "| " << m(1, 0) << ' ' << m(1, 1) << " |\n";
    return out;
}

/// @}
