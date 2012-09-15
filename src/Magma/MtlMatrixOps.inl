////////////////////////////////////////////////////////////////////////////////
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
//	MtlMatrixOps.inl
//------------------------------------------------------------------------------
// Remarks:
//	This file contains inlines for all operations related to matrices.
//------------------------------------------------------------------------------

/// \ingroup Mtx22Ops
/// \name Matrix22 Operations
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 equals \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two Matrix22 objects to see if they are
/// exactly the same .
/// \see operator!=(const Matrix22&, const Matrix22&)

template<typename T>
inline bool operator== (
	const Matrix22<T>& m1,
	const Matrix22<T>& m2)
{
	return (
		m1.data_[0] == m2.data_[0] &&
		m1.data_[1] == m2.data_[1] &&
		m1.data_[2] == m2.data_[2] &&
		m1.data_[3] == m2.data_[3]);
}

////////////////////////////////////////////////////////////////////////////////
/// \return A \b bool type containing result of the comparison. \a true if
/// \a m1 does not equal \a m2; \a false otherwise.
/// \param m1 Reference to the first matrix.
/// \param m2 Reference to the second matrix.
/// \remarks
/// This overloaded operator compares two Matrix22 objects to see if they are
/// NOT exactly the same with zero tolerance.
/// \see operator==(const Matrix22&, const Matrix22&)

template<typename T>
inline bool operator!= (
	const Matrix22<T>& m1,
	const Matrix22<T>& m2)
{
	return (
		m1.data_[0] != m2.data_[0] ||
		m1.data_[1] != m2.data_[1] ||
		m1.data_[2] != m2.data_[2] ||
		m1.data_[3] != m2.data_[3]);
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
/// \see operator==(const Matrix22&, const Matrix22&)

template<typename T>
inline bool isEqual(
	const Matrix22<T>& m1,
	const Matrix22<T>& m2,
	const T eps)
{
	assert(eps >= 0);
	return (
		abs(m1.data_[0] - m2.data_[0]) <= eps &&
		abs(m1.data_[1] - m2.data_[1]) <= eps &&
		abs(m1.data_[2] - m2.data_[2]) <= eps &&
		abs(m1.data_[3] - m2.data_[3]) <= eps);
}
