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
//	MtlDefines.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains handy templated inlines.
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// Handy inline templates

/// \ingroup Utils
/// \name Utility
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return Result in radians.
/// \param deg Angle in degrees.
/// \remarks
/// A handy inline template function for converting degrees to radians.
/// \see radian2degree

template<typename T>
inline T degree2radian(T deg)
{
	return T(PIOVER180 * deg);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Result in degrees.
/// \param rad Angle in radians.
/// \remarks
/// A handy inline template function for converting radians to degrees.
/// \see degree2radian

template<typename T>
inline T radian2degree(T rad)
{
	return T(PIUNDER180 * rad);
}

//template <typename T>
//inline T abs(T v)
//{
//	return static_cast<T>(v >= static_cast<T>(0) ? v : -v);
//}

//template <typename T>
//inline T sqrt(T v)
//{
//	return sqrt(v);
//}

/// @}
