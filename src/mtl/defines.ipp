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
//    defines.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains handy templated inlines.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// Handy inline templates

/// \ingroup Utils
/// \name Utility
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return \b true if two values are almost equal, \b false otherwise.
/// \param a First float type value.
/// \param b Second float type value.
/// \param tolerance Tolerance for the comparison.
/// \remarks
/// A handy inline template function that test for equality within
/// some tolerance.

//template<typename T>
//inline bool is_equal(
//    const T& a,
//    const T& b,
//    const T& tolerance = T(0.0005) )
//{
//    BOOST_ASSERT_MSG(tolerance >= static_cast<T>(0), "negative tolerance!");
//    return (std::abs(a - b) <= tolerance);
//}

//template <typename T>
//inline T abs(T v)
//{
//    return static_cast<T>(v >= static_cast<T>(0) ? v : -v);
//}

//template <typename T>
//inline T sqrt(T v)
//{
//    return sqrt(v);
//}

/// @}
