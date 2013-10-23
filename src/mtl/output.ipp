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
/// matrix22<int> m {1,2,3,4} will appear as:
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

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out The stream to write to.
/// \param m The matrix33 type to output.
/// \remarks
/// Outputs a string representation of the given matrix33 type to the given
/// output stream. The output is formatted such that
/// matrix33<int> m {1,2,3,4,5,6,7,8,9} will appear as:
/// <pre>
///    | 1 4 7 |
///    | 2 5 8 |
///    | 3 6 9 |
/// </pre>

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const matrix33<T>& m)
{
    out << "| " << m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << " |\n";
    out << "| " << m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << " |\n";
    out << "| " << m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << " |\n";
    return out;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out The stream to write to.
/// \param m The matrix44 type to output.
/// \remarks
/// Outputs a string representation of the given matrix44 type to the given
/// output stream. The output is formatted such that
/// matrix44<int> m {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16} will appear as:
/// <pre>
///    | 1 5 9 13 |
///    | 2 6 10 14 |
///    | 3 7 11 15 |
///    | 4 8 12 16 |
/// </pre>

template<typename T>
inline std::ostream& operator<< (
    std::ostream& out,
    const matrix44<T>& m)
{
    out << "| " << m(0, 0) << ' ' << m(0, 1) << ' '
                << m(0, 2) << ' ' << m(0, 3) << " |\n";
    out << "| " << m(1, 0) << ' ' << m(1, 1) << ' '
                << m(1, 2) << ' ' << m(1, 3) << " |\n";
    out << "| " << m(2, 0) << ' ' << m(2, 1) << ' '
                << m(2, 2) << ' ' << m(2, 3) << " |\n";
    out << "| " << m(3, 0) << ' ' << m(3, 1) << ' '
                << m(3, 2) << ' ' << m(3, 3) << " |\n";
    return out;
}

/// @}
