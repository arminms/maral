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

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Zero, T, test_types)
{
	Matrix22<T> m;

	m.zero();
	BOOST_CHECK_EQUAL(m(0, 0), T(0));
	BOOST_CHECK_EQUAL(m(1, 1), T(0));
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
BOOST_AUTO_TEST_SUITE( Mat22Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpMult, T, test_types)
{
	Matrix22<T> m1 { 2,-6,-4,8 };
	Matrix22<T> m2 { -1,3,2,-4 };

	Matrix22<T> r;
	mult(r, m1, m2);
	BOOST_CHECK_EQUAL(r(0, 0), T(-14));
	BOOST_CHECK_EQUAL(r(0, 1), T(20));
	BOOST_CHECK_EQUAL(r(1, 0), T(30));
	BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpPreMult, T, test_types)
{
	Matrix22<T> r { 2,-6,-4,8 };
	Matrix22<T> m { -1,3,2,-4 };

	preMult(r, m);
	BOOST_CHECK_EQUAL(r(0, 0), T(-14));
	BOOST_CHECK_EQUAL(r(0, 1), T(20));
	BOOST_CHECK_EQUAL(r(1, 0), T(30));
	BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpPostMult, T, test_types)
{
	Matrix22<T> r { -1,3,2,-4 };
	Matrix22<T> m { 2,-6,-4,8 };

	postMult(r, m);
	BOOST_CHECK_EQUAL(r(0, 0), T(-14));
	BOOST_CHECK_EQUAL(r(0, 1), T(20));
	BOOST_CHECK_EQUAL(r(1, 0), T(30));
	BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpMultOp, T, test_types)
{
	Matrix22<T> m1 { 2,-6,-4,8 };
	Matrix22<T> m2 { -1,3,2,-4 };

	Matrix22<T> r;
	r = m1 * m2;
	BOOST_CHECK_EQUAL(r(0, 0), T(-14));
	BOOST_CHECK_EQUAL(r(0, 1), T(20));
	BOOST_CHECK_EQUAL(r(1, 0), T(30));
	BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpMultEqOp, T, test_types)
{
	Matrix22<T> r { -1,3,2,-4 };
	Matrix22<T> m { 2,-6,-4,8 };

	r *= m;
	BOOST_CHECK_EQUAL(r(0, 0), T(-14));
	BOOST_CHECK_EQUAL(r(0, 1), T(20));
	BOOST_CHECK_EQUAL(r(1, 0), T(30));
	BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpTransposeInPlace, T, test_types)
{
	Matrix22<T> t { 1,2,3,4 };
	Matrix22<T> r { 1,3,2,4 };

	BOOST_CHECK(transpose(t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpTranspose, T, test_types)
{
	Matrix22<T> t { 1,2,3,4 };
	Matrix22<T> r { 1,3,2,4 };

	Matrix22<T> m;
	BOOST_CHECK(transpose(m, t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpDeterminant, T, test_types)
{
	Matrix22<T> m { 1,2,3,4 };

	BOOST_CHECK(determinant(m) == -2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpInvert, T, float_types)
{
	Matrix22<T> t { 1,2,3,4 };
	Matrix22<T> r { -2,1,1.5,-0.5 };

	Matrix22<T> m;
	BOOST_CHECK(invert(m, t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpInvertUnary, T, float_types)
{
	Matrix22<T> t { 1,2,3,4 };
	Matrix22<T> r { -2,1,1.5,-0.5 };

	BOOST_CHECK(invert(t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Output, T, test_types)
{
	output_test_stream output;
	Matrix22<T> m { 0,1,2,3 };
	output << m;
	BOOST_CHECK(!output.is_empty(false) );
	BOOST_CHECK( output.check_length(16, false) );
	BOOST_CHECK( output.is_equal("| 0 2 |\n| 1 3 |\n") );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

