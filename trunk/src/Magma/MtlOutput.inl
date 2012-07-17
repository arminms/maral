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
//	MtlOutput.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all output stream operators.
//------------------------------------------------------------------------------

/// \ingroup Output
/// \name Output Stream Operators
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out the stream to write to.
/// \param p the VecBase type to output.
/// \remarks
/// Outputs a string representation of the given Point2 type to the
/// given output stream. The output is formatted such that
/// Point2<int>(1,2) will appear as "(1,2)".

template<typename T>
inline std::ostream& operator<< (
	std::ostream& out,
	const Point2<T>& p)
{
	out << '(' << p[0] << ',' << p[1] << ')';
	return out;
}

/// @}
