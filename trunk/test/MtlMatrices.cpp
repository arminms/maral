// $Id$
//------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include <Magma/Magma.hpp>
using boost::test_tools::output_test_stream;
using namespace Magma::Mtl;

typedef boost::mpl::list<int,float,double,long double> test_types;
typedef boost::mpl::list<float,double,long double> float_types;

BOOST_AUTO_TEST_SUITE( Matrices )

BOOST_AUTO_TEST_SUITE( Mat2x2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_InitListConstruct, T, test_types)
{
//	Matrix22<T> zero {}; // because of bug in g++ > 4.5
	Matrix22<T> zero {0};
	BOOST_CHECK_EQUAL(zero.data_[0], T(0));
	BOOST_CHECK_EQUAL(zero.data_[1], T(0));
	BOOST_CHECK_EQUAL(zero.data_[2], T(0));
	BOOST_CHECK_EQUAL(zero.data_[3], T(0));

	Matrix22<T> iden { T(1), T(0), T(0), T(1) };
	BOOST_CHECK_EQUAL(iden.data_[0], T(1));
	BOOST_CHECK_EQUAL(iden.data_[1], T(0));
	BOOST_CHECK_EQUAL(iden.data_[2], T(0));
	BOOST_CHECK_EQUAL(iden.data_[3], T(1));

	Matrix22<T> first { T(1) };
	BOOST_CHECK_EQUAL(first.data_[0], T(1));
	BOOST_CHECK_EQUAL(first.data_[1], T(0));
	BOOST_CHECK_EQUAL(first.data_[2], T(0));
	BOOST_CHECK_EQUAL(first.data_[3], T(0));

	Matrix22<T> third { T(1), T(2), T(3) };
	BOOST_CHECK_EQUAL(third.data_[0], T(1));
	BOOST_CHECK_EQUAL(third.data_[1], T(2));
	BOOST_CHECK_EQUAL(third.data_[2], T(3));
	BOOST_CHECK_EQUAL(third.data_[3], T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_CopyConstruct, T, test_types)
{
	Matrix22<T> m { 1,2,3,4 };
	Matrix22<T> m_copy(m);

	BOOST_CHECK(m == m_copy);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_AssignOp, T, test_types)
{
	Matrix22<T> m { 1,2,3,4 };
	Matrix22<T> m_new;

	m_new = m;
	BOOST_CHECK(m == m_new);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Identity, T, test_types)
{
	Matrix22<T> m;

	m.identity();
	BOOST_CHECK_EQUAL(m(0, 0), T(1));
	BOOST_CHECK_EQUAL(m(1, 1), T(1));
	BOOST_CHECK_EQUAL(m(0, 1), T(0));
	BOOST_CHECK_EQUAL(m(1, 0), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Set, T, test_types)
{
	T mat22[] = { T(0), T(1), T(2), T(3) };

	Matrix22<T> m;
	m.set(mat22);

	BOOST_CHECK_EQUAL(m(0, 0), T(0));
	BOOST_CHECK_EQUAL(m(1, 0), T(1));
	BOOST_CHECK_EQUAL(m(0, 1), T(2));
	BOOST_CHECK_EQUAL(m(1, 1), T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_SetTranspose, T, test_types)
{
	T mat22[] = { T(0), T(1), T(2), T(3) };

	Matrix22<T> m;
	m.setTranspose(mat22);

	BOOST_CHECK_EQUAL(m(0, 0), T(0));
	BOOST_CHECK_EQUAL(m(0, 1), T(1));
	BOOST_CHECK_EQUAL(m(1, 0), T(2));
	BOOST_CHECK_EQUAL(m(1, 1), T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_GetData, T, test_types)
{
	T* data;
	Matrix22<T> m { 1,2,3,4 };
	data = m.getData();

	BOOST_CHECK_EQUAL(data[0], T(1));
	BOOST_CHECK_EQUAL(data[1], T(2));
	BOOST_CHECK_EQUAL(data[2], T(3));
	BOOST_CHECK_EQUAL(data[3], T(4));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_ParaOp, T, test_types)
{
	Matrix22<T> m { 0,1,2,3 };

	BOOST_CHECK_EQUAL(m(0, 0), T(0));
	BOOST_CHECK_EQUAL(m(1, 0), T(1));
	BOOST_CHECK_EQUAL(m(0, 1), T(2));
	BOOST_CHECK_EQUAL(m(1, 1), T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_BracketOp, T, test_types)
{
	Matrix22<T> m { 0,1,2,3 };

	BOOST_CHECK_EQUAL(m[0][0], T(0));
	BOOST_CHECK_EQUAL(m[1][0], T(1));
	BOOST_CHECK_EQUAL(m[0][1], T(2));
	BOOST_CHECK_EQUAL(m[1][1], T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_ParaVsBraOps, T, test_types)
{
	Matrix22<T> m { 0,1,2,3 };

	for (unsigned row=0; row<2; ++row)
		for (unsigned col=0; col<2; ++col)
			BOOST_CHECK_EQUAL(m(row, col), m[row][col]);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

