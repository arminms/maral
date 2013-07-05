// $Id$
//------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include <magma.hpp>
using boost::test_tools::output_test_stream;
using namespace magma::mtl;

typedef boost::mpl::list<int,float,double,long double> test_types;
typedef boost::mpl::list<float,double,long double> float_types;

BOOST_AUTO_TEST_SUITE( Matrices )

BOOST_AUTO_TEST_SUITE( Mat2x2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_InitListConstruct, T, test_types)
{
//    matrix22<T> zero {}; // because of a bug in g++ > 4.5
    matrix22<T> zero {0};
    BOOST_CHECK_EQUAL(zero.data_[0], T(0));
    BOOST_CHECK_EQUAL(zero.data_[1], T(0));
    BOOST_CHECK_EQUAL(zero.data_[2], T(0));
    BOOST_CHECK_EQUAL(zero.data_[3], T(0));

    matrix22<T> iden { T(1), T(0), T(0), T(1) };
    BOOST_CHECK_EQUAL(iden.data_[0], T(1));
    BOOST_CHECK_EQUAL(iden.data_[1], T(0));
    BOOST_CHECK_EQUAL(iden.data_[2], T(0));
    BOOST_CHECK_EQUAL(iden.data_[3], T(1));

    matrix22<T> first { T(1) };
    BOOST_CHECK_EQUAL(first.data_[0], T(1));
    BOOST_CHECK_EQUAL(first.data_[1], T(0));
    BOOST_CHECK_EQUAL(first.data_[2], T(0));
    BOOST_CHECK_EQUAL(first.data_[3], T(0));

    matrix22<T> third { T(1), T(2), T(3) };
    BOOST_CHECK_EQUAL(third.data_[0], T(1));
    BOOST_CHECK_EQUAL(third.data_[1], T(2));
    BOOST_CHECK_EQUAL(third.data_[2], T(3));
    BOOST_CHECK_EQUAL(third.data_[3], T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_CopyConstruct, T, test_types)
{
    matrix22<T> m { 1,2,3,4 };
    matrix22<T> m_copy(m);

    BOOST_CHECK(m == m_copy);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_AssignOp, T, test_types)
{
    matrix22<T> m { 1,2,3,4 };
    matrix22<T> m_new;

    m_new = m;
    BOOST_CHECK(m == m_new);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Identity, T, test_types)
{
    matrix22<T> m;

    m.identity();
    BOOST_CHECK_EQUAL(m(0, 0), T(1));
    BOOST_CHECK_EQUAL(m(1, 1), T(1));
    BOOST_CHECK_EQUAL(m(0, 1), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Zero, T, test_types)
{
    matrix22<T> m;

    m.zero();
    BOOST_CHECK_EQUAL(m(0, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 1), T(0));
    BOOST_CHECK_EQUAL(m(0, 1), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Set, T, test_types)
{
    T mat22[] = { T(0), T(1), T(2), T(3) };

    matrix22<T> m;
    m.set(mat22);

    BOOST_CHECK_EQUAL(m(0, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(1));
    BOOST_CHECK_EQUAL(m(0, 1), T(2));
    BOOST_CHECK_EQUAL(m(1, 1), T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_SetTranspose, T, test_types)
{
    T mat22[] = { T(0), T(1), T(2), T(3) };

    matrix22<T> m;
    m.set_transpose(mat22);

    BOOST_CHECK_EQUAL(m(0, 0), T(0));
    BOOST_CHECK_EQUAL(m(0, 1), T(1));
    BOOST_CHECK_EQUAL(m(1, 0), T(2));
    BOOST_CHECK_EQUAL(m(1, 1), T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_GetData, T, test_types)
{
    T* data;
    matrix22<T> m { 1,2,3,4 };
    data = m.get_data();

    BOOST_CHECK_EQUAL(data[0], T(1));
    BOOST_CHECK_EQUAL(data[1], T(2));
    BOOST_CHECK_EQUAL(data[2], T(3));
    BOOST_CHECK_EQUAL(data[3], T(4));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_ParaOp, T, test_types)
{
    matrix22<T> m { 0,1,2,3 };

    BOOST_CHECK_EQUAL(m(0, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(1));
    BOOST_CHECK_EQUAL(m(0, 1), T(2));
    BOOST_CHECK_EQUAL(m(1, 1), T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_BracketOp, T, test_types)
{
    matrix22<T> m { 0,1,2,3 };

    BOOST_CHECK_EQUAL(m[0][0], T(0));
    BOOST_CHECK_EQUAL(m[1][0], T(1));
    BOOST_CHECK_EQUAL(m[0][1], T(2));
    BOOST_CHECK_EQUAL(m[1][1], T(3));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_ParaVsBraOps, T, test_types)
{
    matrix22<T> m { 0,1,2,3 };

    for (unsigned row=0; row<2; ++row)
        for (unsigned col=0; col<2; ++col)
            BOOST_CHECK_EQUAL(m(row, col), m[row][col]);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Mat22Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpEqualityCompare, T, test_types)
{
    matrix22<T> mtx1 { 1,2,3,4 };
    matrix22<T> mtx2(mtx1);

    BOOST_CHECK(mtx1 == mtx2);
    BOOST_CHECK(!(mtx1 != mtx2));

    mtx2 = mtx1;
    mtx2[0][1] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));

    mtx2 = mtx1;
    mtx2[1][0] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpIsEqual, T, float_types)
{
    matrix22<T> mtx1 { 1.0, 2.0, 3.0, 4.0 };
    matrix22<T> mtx2(mtx1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(mtx1, mtx2, eps));
        BOOST_CHECK_CLOSE(mtx1[0][0], mtx2[0][0], eps);
        BOOST_CHECK_CLOSE(mtx1[1][0], mtx2[1][0], eps);
        BOOST_CHECK_CLOSE(mtx1[0][1], mtx2[0][1], eps);
        BOOST_CHECK_CLOSE(mtx1[1][1], mtx2[1][1], eps);
    }

    mtx1 = matrix22<T>{ 1.0, 1.0, 1.0, 1.0 };
    for(unsigned elt=0; elt<2; elt++)
    {
        mtx2 = mtx1;
        mtx2[elt][elt] = (T)21.0;
        BOOST_CHECK(!is_equal(mtx1, mtx2, T(10.0)));
        BOOST_CHECK(!is_equal(mtx1, mtx2, T(19.9)));
        BOOST_CHECK( is_equal(mtx1, mtx2, T(20.1)));
        BOOST_CHECK( is_equal(mtx1, mtx2, T(22.0)));
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpMult, T, test_types)
{
    matrix22<T> m1 { 2,-6,-4,8 };
    matrix22<T> m2 { -1,3,2,-4 };

    matrix22<T> r;
    mult(r, m1, m2);
    BOOST_CHECK_EQUAL(r(0, 0), T(-14));
    BOOST_CHECK_EQUAL(r(0, 1), T(20));
    BOOST_CHECK_EQUAL(r(1, 0), T(30));
    BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpPreMult, T, test_types)
{
    matrix22<T> r { 2,-6,-4,8 };
    matrix22<T> m { -1,3,2,-4 };

    pre_mult(r, m);
    BOOST_CHECK_EQUAL(r(0, 0), T(-14));
    BOOST_CHECK_EQUAL(r(0, 1), T(20));
    BOOST_CHECK_EQUAL(r(1, 0), T(30));
    BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpPostMult, T, test_types)
{
    matrix22<T> r { -1,3,2,-4 };
    matrix22<T> m { 2,-6,-4,8 };

    post_mult(r, m);
    BOOST_CHECK_EQUAL(r(0, 0), T(-14));
    BOOST_CHECK_EQUAL(r(0, 1), T(20));
    BOOST_CHECK_EQUAL(r(1, 0), T(30));
    BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpMultOp, T, test_types)
{
    matrix22<T> m1 { 2,-6,-4,8 };
    matrix22<T> m2 { -1,3,2,-4 };

    matrix22<T> r;
    r = m1 * m2;
    BOOST_CHECK_EQUAL(r(0, 0), T(-14));
    BOOST_CHECK_EQUAL(r(0, 1), T(20));
    BOOST_CHECK_EQUAL(r(1, 0), T(30));
    BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpMultEqOp, T, test_types)
{
    matrix22<T> r { -1,3,2,-4 };
    matrix22<T> m { 2,-6,-4,8 };

    r *= m;
    BOOST_CHECK_EQUAL(r(0, 0), T(-14));
    BOOST_CHECK_EQUAL(r(0, 1), T(20));
    BOOST_CHECK_EQUAL(r(1, 0), T(30));
    BOOST_CHECK_EQUAL(r(1, 1), T(-44));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpTransposeInPlace, T, test_types)
{
    matrix22<T> t { 1,2,3,4 };
    matrix22<T> r { 1,3,2,4 };

    BOOST_CHECK(transpose(t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpTranspose, T, test_types)
{
    matrix22<T> t { 1,2,3,4 };
    matrix22<T> r { 1,3,2,4 };

    matrix22<T> m;
    BOOST_CHECK(transpose(m, t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpDeterminant, T, test_types)
{
    matrix22<T> m { 1,2,3,4 };

    BOOST_CHECK(determinant(m) == -2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpInvert, T, float_types)
{
    matrix22<T> t { 1,2,3,4 };
    matrix22<T> r { -2,1,1.5,-0.5 };

    matrix22<T> m;
    BOOST_CHECK(invert(m, t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_OpInvertUnary, T, float_types)
{
    matrix22<T> t { 1,2,3,4 };
    matrix22<T> r { -2,1,1.5,-0.5 };

    BOOST_CHECK(invert(t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat22_Output, T, test_types)
{
    output_test_stream output;
    matrix22<T> m { 0,1,2,3 };
    output << m;
    BOOST_CHECK(!output.is_empty(false) );
    BOOST_CHECK( output.check_length(16, false) );
    BOOST_CHECK( output.is_equal("| 0 2 |\n| 1 3 |\n") );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Mat3x3 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_InitListConstruct, T, test_types)
{
//    matrix33<T> zero {}; // because of a bug in g++ > 4.5
    matrix33<T> zero {0};
    BOOST_CHECK_EQUAL(zero.data_[0], T(0));
    BOOST_CHECK_EQUAL(zero.data_[1], T(0));
    BOOST_CHECK_EQUAL(zero.data_[2], T(0));
    BOOST_CHECK_EQUAL(zero.data_[3], T(0));
    BOOST_CHECK_EQUAL(zero.data_[4], T(0));
    BOOST_CHECK_EQUAL(zero.data_[5], T(0));
    BOOST_CHECK_EQUAL(zero.data_[6], T(0));
    BOOST_CHECK_EQUAL(zero.data_[7], T(0));
    BOOST_CHECK_EQUAL(zero.data_[8], T(0));

    matrix33<T> iden { T(1), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(1) };
    BOOST_CHECK_EQUAL(iden.data_[0], T(1));
    BOOST_CHECK_EQUAL(iden.data_[1], T(0));
    BOOST_CHECK_EQUAL(iden.data_[2], T(0));
    BOOST_CHECK_EQUAL(iden.data_[3], T(0));
    BOOST_CHECK_EQUAL(iden.data_[4], T(1));
    BOOST_CHECK_EQUAL(iden.data_[5], T(0));
    BOOST_CHECK_EQUAL(iden.data_[6], T(0));
    BOOST_CHECK_EQUAL(iden.data_[7], T(0));
    BOOST_CHECK_EQUAL(iden.data_[8], T(1));

    matrix33<T> first { T(1) };
    BOOST_CHECK_EQUAL(first.data_[0], T(1));
    BOOST_CHECK_EQUAL(first.data_[1], T(0));
    BOOST_CHECK_EQUAL(first.data_[2], T(0));
    BOOST_CHECK_EQUAL(first.data_[3], T(0));
    BOOST_CHECK_EQUAL(first.data_[4], T(0));
    BOOST_CHECK_EQUAL(first.data_[5], T(0));
    BOOST_CHECK_EQUAL(first.data_[6], T(0));
    BOOST_CHECK_EQUAL(first.data_[7], T(0));
    BOOST_CHECK_EQUAL(first.data_[8], T(0));

    matrix33<T> eighth { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8) };
    BOOST_CHECK_EQUAL(eighth.data_[0], T(1));
    BOOST_CHECK_EQUAL(eighth.data_[1], T(2));
    BOOST_CHECK_EQUAL(eighth.data_[2], T(3));
    BOOST_CHECK_EQUAL(eighth.data_[3], T(4));
    BOOST_CHECK_EQUAL(eighth.data_[4], T(5));
    BOOST_CHECK_EQUAL(eighth.data_[5], T(6));
    BOOST_CHECK_EQUAL(eighth.data_[6], T(7));
    BOOST_CHECK_EQUAL(eighth.data_[7], T(8));
    BOOST_CHECK_EQUAL(eighth.data_[8], T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_CopyConstruct, T, test_types)
{
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };
    matrix33<T> m_copy(m);

    BOOST_CHECK(m == m_copy);
}
//
BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_AssignOp, T, test_types)
{
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };
    matrix33<T> m_new;

    m_new = m;
    BOOST_CHECK(m == m_new);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_Identity, T, test_types)
{
    matrix33<T> m;

    m.identity();
    BOOST_CHECK_EQUAL(m(0, 0), T(1));
    BOOST_CHECK_EQUAL(m(1, 1), T(1));
    BOOST_CHECK_EQUAL(m(2, 2), T(1));
    BOOST_CHECK_EQUAL(m(0, 1), T(0));
    BOOST_CHECK_EQUAL(m(0, 2), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 2), T(0));
    BOOST_CHECK_EQUAL(m(2, 0), T(0));
    BOOST_CHECK_EQUAL(m(2, 1), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_Zero, T, test_types)
{
    matrix33<T> m;

    m.zero();
    BOOST_CHECK_EQUAL(m(0, 0), T(0));
    BOOST_CHECK_EQUAL(m(0, 1), T(0));
    BOOST_CHECK_EQUAL(m(0, 2), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 1), T(0));
    BOOST_CHECK_EQUAL(m(1, 2), T(0));
    BOOST_CHECK_EQUAL(m(2, 0), T(0));
    BOOST_CHECK_EQUAL(m(2, 1), T(0));
    BOOST_CHECK_EQUAL(m(2, 2), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_Set, T, test_types)
{
    T mat33[] = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9) };

    matrix33<T> m;
    m.set(mat33);

    BOOST_CHECK_EQUAL(m(0, 0), T(1));
    BOOST_CHECK_EQUAL(m(1, 0), T(2));
    BOOST_CHECK_EQUAL(m(2, 0), T(3));
    BOOST_CHECK_EQUAL(m(0, 1), T(4));
    BOOST_CHECK_EQUAL(m(1, 1), T(5));
    BOOST_CHECK_EQUAL(m(2, 1), T(6));
    BOOST_CHECK_EQUAL(m(0, 2), T(7));
    BOOST_CHECK_EQUAL(m(1, 2), T(8));
    BOOST_CHECK_EQUAL(m(2, 2), T(9));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_SetTranspose, T, test_types)
{
    T mat33[] = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9) };

    matrix33<T> m;
    m.set_transpose(mat33);

    BOOST_CHECK_EQUAL(m(0, 0), T(1));
    BOOST_CHECK_EQUAL(m(0, 1), T(2));
    BOOST_CHECK_EQUAL(m(0, 2), T(3));
    BOOST_CHECK_EQUAL(m(1, 0), T(4));
    BOOST_CHECK_EQUAL(m(1, 1), T(5));
    BOOST_CHECK_EQUAL(m(1, 2), T(6));
    BOOST_CHECK_EQUAL(m(2, 0), T(7));
    BOOST_CHECK_EQUAL(m(2, 1), T(8));
    BOOST_CHECK_EQUAL(m(2, 2), T(9));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_GetData, T, test_types)
{
    T* data;
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };
    data = m.get_data();

    BOOST_CHECK_EQUAL(data[0], T(1));
    BOOST_CHECK_EQUAL(data[1], T(2));
    BOOST_CHECK_EQUAL(data[2], T(3));
    BOOST_CHECK_EQUAL(data[3], T(4));
    BOOST_CHECK_EQUAL(data[4], T(5));
    BOOST_CHECK_EQUAL(data[5], T(6));
    BOOST_CHECK_EQUAL(data[6], T(7));
    BOOST_CHECK_EQUAL(data[7], T(8));
    BOOST_CHECK_EQUAL(data[8], T(9));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_ParaOp, T, test_types)
{
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };

    BOOST_CHECK_EQUAL(m(0, 0), T(1));
    BOOST_CHECK_EQUAL(m(1, 0), T(2));
    BOOST_CHECK_EQUAL(m(2, 0), T(3));
    BOOST_CHECK_EQUAL(m(0, 1), T(4));
    BOOST_CHECK_EQUAL(m(1, 1), T(5));
    BOOST_CHECK_EQUAL(m(2, 1), T(6));
    BOOST_CHECK_EQUAL(m(0, 2), T(7));
    BOOST_CHECK_EQUAL(m(1, 2), T(8));
    BOOST_CHECK_EQUAL(m(2, 2), T(9));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_BracketOp, T, test_types)
{
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };

    BOOST_CHECK_EQUAL(m[0][0], T(1));
    BOOST_CHECK_EQUAL(m[1][0], T(2));
    BOOST_CHECK_EQUAL(m[2][0], T(3));
    BOOST_CHECK_EQUAL(m[0][1], T(4));
    BOOST_CHECK_EQUAL(m[1][1], T(5));
    BOOST_CHECK_EQUAL(m[2][1], T(6));
    BOOST_CHECK_EQUAL(m[0][2], T(7));
    BOOST_CHECK_EQUAL(m[1][2], T(8));
    BOOST_CHECK_EQUAL(m[2][2], T(9));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_ParaVsBraOps, T, test_types)
{
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };

    for (unsigned row=0; row<3; ++row)
        for (unsigned col=0; col<3; ++col)
            BOOST_CHECK_EQUAL(m(row, col), m[row][col]);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Mat33Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpEqualityCompare, T, test_types)
{
    matrix33<T> mtx1 { 1,2,3,4,5,6,7,8,9 };
    matrix33<T> mtx2(mtx1);

    BOOST_CHECK(mtx1 == mtx2);
    BOOST_CHECK(!(mtx1 != mtx2));

    mtx2 = mtx1;
    mtx2[0][1] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));

    mtx2 = mtx1;
    mtx2[1][0] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpIsEqual, T, float_types)
{
    matrix33<T> mtx1 { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    matrix33<T> mtx2(mtx1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(mtx1, mtx2, eps));
        BOOST_CHECK_CLOSE(mtx1[0][0], mtx2[0][0], eps);
        BOOST_CHECK_CLOSE(mtx1[1][0], mtx2[1][0], eps);
        BOOST_CHECK_CLOSE(mtx1[0][1], mtx2[0][1], eps);
        BOOST_CHECK_CLOSE(mtx1[1][1], mtx2[1][1], eps);
    }

    mtx1 = matrix33<T>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    for(unsigned elt=0; elt<2; elt++)
    {
        mtx2 = mtx1;
        mtx2[elt][elt] = (T)21.0;
        BOOST_CHECK(!is_equal(mtx1, mtx2, T(10.0)));
        BOOST_CHECK(!is_equal(mtx1, mtx2, T(19.9)));
        BOOST_CHECK( is_equal(mtx1, mtx2, T(20.1)));
        BOOST_CHECK( is_equal(mtx1, mtx2, T(22.0)));
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpMult, T, test_types)
{
    matrix33<T> m1 { -4,0,1,-3,2,4,3,-2,-1 };
    matrix33<T> m2 { 1,0,5,2,1,6,3,4,0 };

    matrix33<T> r;
    mult(r, m1, m2);
    BOOST_CHECK_EQUAL(r(0, 0), T(11));
    BOOST_CHECK_EQUAL(r(0, 1), T(7));
    BOOST_CHECK_EQUAL(r(0, 2), T(-24));
    BOOST_CHECK_EQUAL(r(1, 0), T(-10));
    BOOST_CHECK_EQUAL(r(1, 1), T(-10));
    BOOST_CHECK_EQUAL(r(1, 2), T(8));
    BOOST_CHECK_EQUAL(r(2, 0), T(-4));
    BOOST_CHECK_EQUAL(r(2, 1), T(0));
    BOOST_CHECK_EQUAL(r(2, 2), T(19));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpPreMult, T, test_types)
{
    matrix33<T> r { 1,0,5,2,1,6,3,4,0 };
    matrix33<T> m { -4,0,1,-3,2,4,3,-2,-1 };

    pre_mult(r, m);
    BOOST_CHECK_EQUAL(r(0, 0), T(11));
    BOOST_CHECK_EQUAL(r(0, 1), T(7));
    BOOST_CHECK_EQUAL(r(0, 2), T(-24));
    BOOST_CHECK_EQUAL(r(1, 0), T(-10));
    BOOST_CHECK_EQUAL(r(1, 1), T(-10));
    BOOST_CHECK_EQUAL(r(1, 2), T(8));
    BOOST_CHECK_EQUAL(r(2, 0), T(-4));
    BOOST_CHECK_EQUAL(r(2, 1), T(0));
    BOOST_CHECK_EQUAL(r(2, 2), T(19));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpPostMult, T, test_types)
{
    matrix33<T> r { -4,0,1,-3,2,4,3,-2,-1 };
    matrix33<T> m { 1,0,5,2,1,6,3,4,0 };

    post_mult(r, m);
    BOOST_CHECK_EQUAL(r(0, 0), T(11));
    BOOST_CHECK_EQUAL(r(0, 1), T(7));
    BOOST_CHECK_EQUAL(r(0, 2), T(-24));
    BOOST_CHECK_EQUAL(r(1, 0), T(-10));
    BOOST_CHECK_EQUAL(r(1, 1), T(-10));
    BOOST_CHECK_EQUAL(r(1, 2), T(8));
    BOOST_CHECK_EQUAL(r(2, 0), T(-4));
    BOOST_CHECK_EQUAL(r(2, 1), T(0));
    BOOST_CHECK_EQUAL(r(2, 2), T(19));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpMultOp, T, test_types)
{
    matrix33<T> m1 { -4,0,1,-3,2,4,3,-2,-1 };
    matrix33<T> m2 { 1,2,4,5,4,6,3,7,2 };

    matrix33<T> r;
    r = m1 * m2;
    BOOST_CHECK_EQUAL(r(0, 0), T(2));
    BOOST_CHECK_EQUAL(r(0, 1), T(-14));
    BOOST_CHECK_EQUAL(r(0, 2), T(-27));
    BOOST_CHECK_EQUAL(r(1, 0), T(-4));
    BOOST_CHECK_EQUAL(r(1, 1), T(-4));
    BOOST_CHECK_EQUAL(r(1, 2), T(10));
    BOOST_CHECK_EQUAL(r(2, 0), T(5));
    BOOST_CHECK_EQUAL(r(2, 1), T(15));
    BOOST_CHECK_EQUAL(r(2, 2), T(29));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpMultEqOp, T, test_types)
{
    matrix33<T> r { -4,0,1,-3,2,4,3,-2,-1 };
    matrix33<T> m { 1,2,4,5,4,6,3,7,2 };

    r *= m;
    BOOST_CHECK_EQUAL(r(0, 0), T(2));
    BOOST_CHECK_EQUAL(r(0, 1), T(-14));
    BOOST_CHECK_EQUAL(r(0, 2), T(-27));
    BOOST_CHECK_EQUAL(r(1, 0), T(-4));
    BOOST_CHECK_EQUAL(r(1, 1), T(-4));
    BOOST_CHECK_EQUAL(r(1, 2), T(10));
    BOOST_CHECK_EQUAL(r(2, 0), T(5));
    BOOST_CHECK_EQUAL(r(2, 1), T(15));
    BOOST_CHECK_EQUAL(r(2, 2), T(29));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpTransposeInPlace, T, test_types)
{
    matrix33<T> t { 1,2,3,4,5,6,7,8,9 };
    matrix33<T> r { 1,4,7,2,5,8,3,6,9 };

    BOOST_CHECK(transpose(t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpTranspose, T, test_types)
{
    matrix33<T> t { 1,2,3,4,5,6,7,8,9 };
    matrix33<T> r { 1,4,7,2,5,8,3,6,9 };

    matrix33<T> m;
    BOOST_CHECK(transpose(m, t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpDeterminant, T, test_types)
{
    matrix33<T> m1 { -4,0,1,-3,2,4,3,-2,-1 };
    matrix33<T> m2 { 1,0,5,2,1,6,3,4,0 };

    BOOST_CHECK_EQUAL(determinant(m1), T(-24));
    BOOST_CHECK_EQUAL(determinant(m2), T(1));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpInvert, T, float_types)
{
    matrix33<T> t { -4,0,1,-3,2,4,3,-2,-1 };
    matrix33<T> r { -0.25,0.083,0.083,-0.375,-0.042,-0.542,0.0,0.333,0.333 };

    matrix33<T> m;
    invert(m, t);
    BOOST_CHECK(is_equal(m, r, T(SMALL)));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_OpInvertUnary, T, float_types)
{
    matrix33<T> t { 1,0,5,2,1,6,3,4,0 };
    matrix33<T> r { -24,20,-5,18,-15,4,5,-4,1 };

    BOOST_CHECK(is_equal(invert(t), r, T(SMALL)));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat33_Output, T, test_types)
{
    output_test_stream output;
    matrix33<T> m { 1,2,3,4,5,6,7,8,9 };
    output << m;
    BOOST_CHECK(!output.is_empty(false) );
    BOOST_CHECK( output.check_length(30, false) );
    BOOST_CHECK( output.is_equal("| 1 4 7 |\n| 2 5 8 |\n| 3 6 9 |\n") );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

