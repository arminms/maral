// $Id$
//------------------------------------------------------------------------------


#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include <fstream>
#include <mtl/mtl.hpp>

using boost::test_tools::output_test_stream;
using namespace maral::mtl;

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
    mtx2[1][1] = (T)21.10f;
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

//BOOST_AUTO_TEST_CASE(Insterters)
//{
//    matrix22<int> mtx { 1,2,3,4 };
//    matrix22<float> mtx { 3.141593, 938.27231, 939.56563, 2.718282 };
//
//    std::ofstream os("../../test/patterns/matrix22.txt");
//    os << separator(',') << mtx << std::endl << std::endl;
//    os << std::fixed << std::setprecision(3)
//       << mtx << std::endl << std::endl;
//    os << delimiters('|') << mtx << std::endl << std::endl;
//    os << setew(7) << mtx << std::endl << std::endl;
//    os << std::setw(25) << mtx << std::endl << std::endl;
//    os << spaces << mtx << std::endl << std::endl;
//    os << horizontal << mtx << std::endl << std::endl;
//    os << setew(0) << mtx << std::endl << std::endl;
//    os << delimiters('{', '}') << mtx << std::endl << std::endl;
//    os << rowmajor << mtx << std::endl << std::endl;
//    os << colmajor << nospaces << mtx << std::endl << std::endl;
//    os << separator(' ') << mtx << std::endl << std::endl;
//    os << std::setw(35) << mtx << std::endl << std::endl;
//    os << delimiters('\0') << mtx << std::endl;
//}

BOOST_AUTO_TEST_CASE(Mat22_Inserter)
{
    output_test_stream cout("../../test/patterns/matrix22.txt", true);
/// [matrix22 inserter]
    matrix22<float> mtx { 3.141593, 938.27231, 939.56563, 2.718282 };

    cout << separator(',') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
       << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(25) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << rowmajor << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << colmajor << nospaces << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(' ') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(35) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << mtx << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [matrix22 inserter]
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
    mtx2[0][2] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));

    mtx2 = mtx1;
    mtx2[2][2] = (T)21.10f;
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
        BOOST_CHECK_CLOSE(mtx1[2][0], mtx2[2][0], eps);
        BOOST_CHECK_CLOSE(mtx1[0][1], mtx2[0][1], eps);
        BOOST_CHECK_CLOSE(mtx1[1][1], mtx2[1][1], eps);
        BOOST_CHECK_CLOSE(mtx1[2][1], mtx2[2][1], eps);
        BOOST_CHECK_CLOSE(mtx1[0][2], mtx2[0][2], eps);
        BOOST_CHECK_CLOSE(mtx1[1][2], mtx2[1][2], eps);
        BOOST_CHECK_CLOSE(mtx1[2][2], mtx2[2][2], eps);
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

//BOOST_AUTO_TEST_CASE(Insterters)
//{
//    matrix33<int> mtx { 1,2,3,4,5,6,7,8,9 };
//
//    matrix33<float> mtx
//    {
//         3.141593, 938.27231,  8.617365,
//           6.0221,  2.718282, 939.56563,
//        931.49432,  1.672623,  0.577216
//    };
//
//    std::ofstream os("../../test/patterns/matrix33.txt");
//    os << separator(',') << mtx << std::endl << std::endl;
//    os << std::fixed << std::setprecision(3)
//       << mtx << std::endl << std::endl;
//    os << delimiters('|') << mtx << std::endl << std::endl;
//    os << setew(7) << mtx << std::endl << std::endl;
//    os << std::setw(30) << mtx << std::endl << std::endl;
//    os << spaces << mtx << std::endl << std::endl;
//    os << horizontal << mtx << std::endl << std::endl;
//    os << setew(0) << mtx << std::endl << std::endl;
//    os << delimiters('{', '}') << mtx << std::endl << std::endl;
//    os << rowmajor << mtx << std::endl << std::endl;
//    os << colmajor << nospaces << mtx << std::endl << std::endl;
//    os << separator(' ') << mtx << std::endl << std::endl;
//    os << std::setw(65) << mtx << std::endl << std::endl;
//    os << delimiters('\0') << mtx << std::endl;
//}

BOOST_AUTO_TEST_CASE(Mat33_Inserter)
{
    output_test_stream cout("../../test/patterns/matrix33.txt", true);
/// [matrix33 inserter]
    matrix33<float> mtx
    {
         3.141593, 938.27231,  8.617365,
           6.0221,  2.718282, 939.56563,
        931.49432,  1.672623,  0.577216
    };

    cout << separator(',') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
       << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(30) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << rowmajor << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << colmajor << nospaces << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(' ') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(65) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << mtx << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [matrix33 inserter]
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Mat4x4 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_InitListConstruct, T, test_types)
{
//    matrix44<T> zero {}; // because of a bug in g++ > 4.5
    matrix44<T> zero {0};
    BOOST_CHECK_EQUAL(zero.data_ [0], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [1], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [2], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [3], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [4], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [5], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [6], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [7], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [8], T(0));
    BOOST_CHECK_EQUAL(zero.data_ [9], T(0));
    BOOST_CHECK_EQUAL(zero.data_[10], T(0));
    BOOST_CHECK_EQUAL(zero.data_[11], T(0));
    BOOST_CHECK_EQUAL(zero.data_[12], T(0));
    BOOST_CHECK_EQUAL(zero.data_[13], T(0));
    BOOST_CHECK_EQUAL(zero.data_[14], T(0));
    BOOST_CHECK_EQUAL(zero.data_[15], T(0));

    matrix44<T> iden { T(1), T(0), T(0), T(0), T(0), T(1), T(0), T(0),
                       T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1) };
    BOOST_CHECK_EQUAL(iden.data_ [0], T(1));
    BOOST_CHECK_EQUAL(iden.data_ [1], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [2], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [3], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [4], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [5], T(1));
    BOOST_CHECK_EQUAL(iden.data_ [6], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [7], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [8], T(0));
    BOOST_CHECK_EQUAL(iden.data_ [9], T(0));
    BOOST_CHECK_EQUAL(iden.data_[10], T(1));
    BOOST_CHECK_EQUAL(iden.data_[11], T(0));
    BOOST_CHECK_EQUAL(iden.data_[12], T(0));
    BOOST_CHECK_EQUAL(iden.data_[13], T(0));
    BOOST_CHECK_EQUAL(iden.data_[14], T(0));
    BOOST_CHECK_EQUAL(iden.data_[15], T(1));

    matrix44<T> first { T(1) };
    BOOST_CHECK_EQUAL(first.data_ [0], T(1));
    BOOST_CHECK_EQUAL(first.data_ [1], T(0));
    BOOST_CHECK_EQUAL(first.data_ [2], T(0));
    BOOST_CHECK_EQUAL(first.data_ [3], T(0));
    BOOST_CHECK_EQUAL(first.data_ [4], T(0));
    BOOST_CHECK_EQUAL(first.data_ [5], T(0));
    BOOST_CHECK_EQUAL(first.data_ [6], T(0));
    BOOST_CHECK_EQUAL(first.data_ [7], T(0));
    BOOST_CHECK_EQUAL(first.data_ [8], T(0));
    BOOST_CHECK_EQUAL(first.data_ [9], T(0));
    BOOST_CHECK_EQUAL(first.data_[10], T(0));
    BOOST_CHECK_EQUAL(first.data_[11], T(0));
    BOOST_CHECK_EQUAL(first.data_[12], T(0));
    BOOST_CHECK_EQUAL(first.data_[13], T(0));
    BOOST_CHECK_EQUAL(first.data_[14], T(0));
    BOOST_CHECK_EQUAL(first.data_[15], T(0));

    matrix44<T> sixteenth { T (1), T (2), T (3), T (4),
                            T (5), T (6), T (7), T (8),
                            T (9), T(10), T(11), T(12),
                            T(13), T(14), T(15), T(16) };
    BOOST_CHECK_EQUAL(sixteenth.data_ [0], T (1));
    BOOST_CHECK_EQUAL(sixteenth.data_ [1], T (2));
    BOOST_CHECK_EQUAL(sixteenth.data_ [2], T (3));
    BOOST_CHECK_EQUAL(sixteenth.data_ [3], T (4));
    BOOST_CHECK_EQUAL(sixteenth.data_ [4], T (5));
    BOOST_CHECK_EQUAL(sixteenth.data_ [5], T (6));
    BOOST_CHECK_EQUAL(sixteenth.data_ [6], T (7));
    BOOST_CHECK_EQUAL(sixteenth.data_ [7], T (8));
    BOOST_CHECK_EQUAL(sixteenth.data_ [8], T (9));
    BOOST_CHECK_EQUAL(sixteenth.data_ [9], T(10));
    BOOST_CHECK_EQUAL(sixteenth.data_[10], T(11));
    BOOST_CHECK_EQUAL(sixteenth.data_[11], T(12));
    BOOST_CHECK_EQUAL(sixteenth.data_[12], T(13));
    BOOST_CHECK_EQUAL(sixteenth.data_[13], T(14));
    BOOST_CHECK_EQUAL(sixteenth.data_[14], T(15));
    BOOST_CHECK_EQUAL(sixteenth.data_[15], T(16));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_CopyConstruct, T, test_types)
{
    matrix44<T> m { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    matrix44<T> m_copy(m);

    BOOST_CHECK(m == m_copy);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_AssignOp, T, test_types)
{
    matrix44<T> m { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    matrix44<T> m_new;

    m_new = m;
    BOOST_CHECK(m == m_new);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_Identity, T, test_types)
{
    matrix44<T> m;

    m.identity();
    BOOST_CHECK_EQUAL(m(0, 0), T(1));
    BOOST_CHECK_EQUAL(m(1, 1), T(1));
    BOOST_CHECK_EQUAL(m(2, 2), T(1));
    BOOST_CHECK_EQUAL(m(3, 3), T(1));
    BOOST_CHECK_EQUAL(m(0, 1), T(0));
    BOOST_CHECK_EQUAL(m(0, 2), T(0));
    BOOST_CHECK_EQUAL(m(0, 3), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 2), T(0));
    BOOST_CHECK_EQUAL(m(1, 3), T(0));
    BOOST_CHECK_EQUAL(m(2, 0), T(0));
    BOOST_CHECK_EQUAL(m(2, 1), T(0));
    BOOST_CHECK_EQUAL(m(2, 3), T(0));
    BOOST_CHECK_EQUAL(m(3, 0), T(0));
    BOOST_CHECK_EQUAL(m(3, 1), T(0));
    BOOST_CHECK_EQUAL(m(3, 2), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_Zero, T, test_types)
{
    matrix44<T> m;

    m.zero();
    BOOST_CHECK_EQUAL(m(0, 0), T(0));
    BOOST_CHECK_EQUAL(m(0, 1), T(0));
    BOOST_CHECK_EQUAL(m(0, 2), T(0));
    BOOST_CHECK_EQUAL(m(0, 3), T(0));
    BOOST_CHECK_EQUAL(m(1, 0), T(0));
    BOOST_CHECK_EQUAL(m(1, 1), T(0));
    BOOST_CHECK_EQUAL(m(1, 2), T(0));
    BOOST_CHECK_EQUAL(m(1, 3), T(0));
    BOOST_CHECK_EQUAL(m(2, 0), T(0));
    BOOST_CHECK_EQUAL(m(2, 1), T(0));
    BOOST_CHECK_EQUAL(m(2, 2), T(0));
    BOOST_CHECK_EQUAL(m(2, 3), T(0));
    BOOST_CHECK_EQUAL(m(3, 0), T(0));
    BOOST_CHECK_EQUAL(m(3, 1), T(0));
    BOOST_CHECK_EQUAL(m(3, 2), T(0));
    BOOST_CHECK_EQUAL(m(3, 3), T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_Set, T, test_types)
{
    T mat44[] = { T (1), T (2), T (3), T (4), T (5), T (6), T (7), T (8),
                  T (9), T(10), T(11), T(12), T(13), T(14), T(15), T(16) };

    matrix44<T> m;
    m.set(mat44);

    BOOST_CHECK_EQUAL(m(0, 0), T (1));
    BOOST_CHECK_EQUAL(m(1, 0), T (2));
    BOOST_CHECK_EQUAL(m(2, 0), T (3));
    BOOST_CHECK_EQUAL(m(3, 0), T (4));
    BOOST_CHECK_EQUAL(m(0, 1), T (5));
    BOOST_CHECK_EQUAL(m(1, 1), T (6));
    BOOST_CHECK_EQUAL(m(2, 1), T (7));
    BOOST_CHECK_EQUAL(m(3, 1), T (8));
    BOOST_CHECK_EQUAL(m(0, 2), T (9));
    BOOST_CHECK_EQUAL(m(1, 2), T(10));
    BOOST_CHECK_EQUAL(m(2, 2), T(11));
    BOOST_CHECK_EQUAL(m(3, 2), T(12));
    BOOST_CHECK_EQUAL(m(0, 3), T(13));
    BOOST_CHECK_EQUAL(m(1, 3), T(14));
    BOOST_CHECK_EQUAL(m(2, 3), T(15));
    BOOST_CHECK_EQUAL(m(3, 3), T(16));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_SetTranspose, T, test_types)
{
    T mat44[] = { T (1), T (2), T (3), T (4), T (5), T (6), T (7), T (8),
                  T (9), T(10), T(11), T(12), T(13), T(14), T(15), T(16) };

    matrix44<T> m;
    m.set_transpose(mat44);

    BOOST_CHECK_EQUAL(m(0, 0), T (1));
    BOOST_CHECK_EQUAL(m(1, 0), T (5));
    BOOST_CHECK_EQUAL(m(2, 0), T (9));
    BOOST_CHECK_EQUAL(m(3, 0), T(13));
    BOOST_CHECK_EQUAL(m(0, 1), T (2));
    BOOST_CHECK_EQUAL(m(1, 1), T (6));
    BOOST_CHECK_EQUAL(m(2, 1), T(10));
    BOOST_CHECK_EQUAL(m(3, 1), T(14));
    BOOST_CHECK_EQUAL(m(0, 2), T (3));
    BOOST_CHECK_EQUAL(m(1, 2), T (7));
    BOOST_CHECK_EQUAL(m(2, 2), T(11));
    BOOST_CHECK_EQUAL(m(3, 2), T(15));
    BOOST_CHECK_EQUAL(m(0, 3), T (4));
    BOOST_CHECK_EQUAL(m(1, 3), T (8));
    BOOST_CHECK_EQUAL(m(2, 3), T(12));
    BOOST_CHECK_EQUAL(m(3, 3), T(16));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_GetData, T, test_types)
{
    T* data;
    matrix44<T> m { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    data = m.get_data();

    BOOST_CHECK_EQUAL(data [0], T (1));
    BOOST_CHECK_EQUAL(data [1], T (2));
    BOOST_CHECK_EQUAL(data [2], T (3));
    BOOST_CHECK_EQUAL(data [3], T (4));
    BOOST_CHECK_EQUAL(data [4], T (5));
    BOOST_CHECK_EQUAL(data [5], T (6));
    BOOST_CHECK_EQUAL(data [6], T (7));
    BOOST_CHECK_EQUAL(data [7], T (8));
    BOOST_CHECK_EQUAL(data [8], T (9));
    BOOST_CHECK_EQUAL(data [9], T(10));
    BOOST_CHECK_EQUAL(data[10], T(11));
    BOOST_CHECK_EQUAL(data[11], T(12));
    BOOST_CHECK_EQUAL(data[12], T(13));
    BOOST_CHECK_EQUAL(data[13], T(14));
    BOOST_CHECK_EQUAL(data[14], T(15));
    BOOST_CHECK_EQUAL(data[15], T(16));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_ParaOp, T, test_types)
{
    matrix44<T> m { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    BOOST_CHECK_EQUAL(m(0, 0), T (1));
    BOOST_CHECK_EQUAL(m(1, 0), T (2));
    BOOST_CHECK_EQUAL(m(2, 0), T (3));
    BOOST_CHECK_EQUAL(m(3, 0), T (4));
    BOOST_CHECK_EQUAL(m(0, 1), T (5));
    BOOST_CHECK_EQUAL(m(1, 1), T (6));
    BOOST_CHECK_EQUAL(m(2, 1), T (7));
    BOOST_CHECK_EQUAL(m(3, 1), T (8));
    BOOST_CHECK_EQUAL(m(0, 2), T (9));
    BOOST_CHECK_EQUAL(m(1, 2), T(10));
    BOOST_CHECK_EQUAL(m(2, 2), T(11));
    BOOST_CHECK_EQUAL(m(3, 2), T(12));
    BOOST_CHECK_EQUAL(m(0, 3), T(13));
    BOOST_CHECK_EQUAL(m(1, 3), T(14));
    BOOST_CHECK_EQUAL(m(2, 3), T(15));
    BOOST_CHECK_EQUAL(m(3, 3), T(16));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_BracketOp, T, test_types)
{
    matrix44<T> m { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    BOOST_CHECK_EQUAL(m[0][0], T (1));
    BOOST_CHECK_EQUAL(m[1][0], T (2));
    BOOST_CHECK_EQUAL(m[2][0], T (3));
    BOOST_CHECK_EQUAL(m[3][0], T (4));
    BOOST_CHECK_EQUAL(m[0][1], T (5));
    BOOST_CHECK_EQUAL(m[1][1], T (6));
    BOOST_CHECK_EQUAL(m[2][1], T (7));
    BOOST_CHECK_EQUAL(m[3][1], T (8));
    BOOST_CHECK_EQUAL(m[0][2], T (9));
    BOOST_CHECK_EQUAL(m[1][2], T(10));
    BOOST_CHECK_EQUAL(m[2][2], T(11));
    BOOST_CHECK_EQUAL(m[3][2], T(12));
    BOOST_CHECK_EQUAL(m[0][3], T(13));
    BOOST_CHECK_EQUAL(m[1][3], T(14));
    BOOST_CHECK_EQUAL(m[2][3], T(15));
    BOOST_CHECK_EQUAL(m[3][3], T(16));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_ParaVsBraOps, T, test_types)
{
    matrix44<T> m { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    for (unsigned row=0; row<4; ++row)
        for (unsigned col=0; col<4; ++col)
            BOOST_CHECK_EQUAL(m(row, col), m[row][col]);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Mat44Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpEqualityCompare, T, test_types)
{
    matrix44<T> mtx1 { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    matrix44<T> mtx2(mtx1);

    BOOST_CHECK(mtx1 == mtx2);
    BOOST_CHECK(!(mtx1 != mtx2));

    mtx2 = mtx1;
    mtx2[0][3] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));

    mtx2 = mtx1;
    mtx2[3][3] = (T)21.10f;
    BOOST_CHECK(mtx1 != mtx2);
    BOOST_CHECK(!(mtx1 == mtx2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpIsEqual, T, float_types)
{
    matrix44<T> mtx1 { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
                       10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    matrix44<T> mtx2(mtx1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(mtx1, mtx2, eps));
        BOOST_CHECK_CLOSE(mtx1[0][0], mtx2[0][0], eps);
        BOOST_CHECK_CLOSE(mtx1[1][0], mtx2[1][0], eps);
        BOOST_CHECK_CLOSE(mtx1[2][0], mtx2[2][0], eps);
        BOOST_CHECK_CLOSE(mtx1[3][0], mtx2[3][0], eps);
        BOOST_CHECK_CLOSE(mtx1[0][1], mtx2[0][1], eps);
        BOOST_CHECK_CLOSE(mtx1[1][1], mtx2[1][1], eps);
        BOOST_CHECK_CLOSE(mtx1[2][1], mtx2[2][1], eps);
        BOOST_CHECK_CLOSE(mtx1[3][1], mtx2[3][1], eps);
        BOOST_CHECK_CLOSE(mtx1[0][2], mtx2[0][2], eps);
        BOOST_CHECK_CLOSE(mtx1[1][2], mtx2[1][2], eps);
        BOOST_CHECK_CLOSE(mtx1[2][2], mtx2[2][2], eps);
        BOOST_CHECK_CLOSE(mtx1[3][2], mtx2[3][2], eps);
        BOOST_CHECK_CLOSE(mtx1[0][3], mtx2[0][3], eps);
        BOOST_CHECK_CLOSE(mtx1[1][3], mtx2[1][3], eps);
        BOOST_CHECK_CLOSE(mtx1[2][3], mtx2[2][3], eps);
        BOOST_CHECK_CLOSE(mtx1[3][3], mtx2[3][3], eps);
    }

    mtx1 = matrix44<T>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    for(unsigned elt=0; elt<3; elt++)
    {
        mtx2 = mtx1;
        mtx2[elt][elt] = (T)21.0;
        BOOST_CHECK(!is_equal(mtx1, mtx2, T(10.0)));
        BOOST_CHECK(!is_equal(mtx1, mtx2, T(19.9)));
        BOOST_CHECK( is_equal(mtx1, mtx2, T(20.1)));
        BOOST_CHECK( is_equal(mtx1, mtx2, T(22.0)));
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpMult, T, test_types)
{
    matrix44<T> m1 { 4,-6,9,-5,-3,7,8,6,5,4,-1,-8,2,0,3,-4 };
    matrix44<T> m2 { -7,5,1,-8,3,3,-7,-9,9,-6,0,2,-2,8,4,1 };

    matrix44<T> r;
    mult(r, m1, m2);
    BOOST_CHECK_EQUAL(r(0, 0), T(-54));
    BOOST_CHECK_EQUAL(r(0, 1), T(-50));
    BOOST_CHECK_EQUAL(r(0, 2), T(58));
    BOOST_CHECK_EQUAL(r(0, 3), T(-10));
    BOOST_CHECK_EQUAL(r(1, 0), T(81));
    BOOST_CHECK_EQUAL(r(1, 1), T(-25));
    BOOST_CHECK_EQUAL(r(1, 2), T(-96));
    BOOST_CHECK_EQUAL(r(1, 3), T(84));
    BOOST_CHECK_EQUAL(r(2, 0), T(-48));
    BOOST_CHECK_EQUAL(r(2, 1), T(31));
    BOOST_CHECK_EQUAL(r(2, 2), T(39));
    BOOST_CHECK_EQUAL(r(2, 3), T(45));
    BOOST_CHECK_EQUAL(r(3, 0), T(89));
    BOOST_CHECK_EQUAL(r(3, 1), T(95));
    BOOST_CHECK_EQUAL(r(3, 2), T(-89));
    BOOST_CHECK_EQUAL(r(3, 3), T(22));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpPreMult, T, test_types)
{
    matrix44<T> r { -7,5,1,-8,3,3,-7,-9,9,-6,0,2,-2,8,4,1 };
    matrix44<T> m { 4,-6,9,-5,-3,7,8,6,5,4,-1,-8,2,0,3,-4 };

    pre_mult(r, m);
    BOOST_CHECK_EQUAL(r(0, 0), T(-54));
    BOOST_CHECK_EQUAL(r(0, 1), T(-50));
    BOOST_CHECK_EQUAL(r(0, 2), T(58));
    BOOST_CHECK_EQUAL(r(0, 3), T(-10));
    BOOST_CHECK_EQUAL(r(1, 0), T(81));
    BOOST_CHECK_EQUAL(r(1, 1), T(-25));
    BOOST_CHECK_EQUAL(r(1, 2), T(-96));
    BOOST_CHECK_EQUAL(r(1, 3), T(84));
    BOOST_CHECK_EQUAL(r(2, 0), T(-48));
    BOOST_CHECK_EQUAL(r(2, 1), T(31));
    BOOST_CHECK_EQUAL(r(2, 2), T(39));
    BOOST_CHECK_EQUAL(r(2, 3), T(45));
    BOOST_CHECK_EQUAL(r(3, 0), T(89));
    BOOST_CHECK_EQUAL(r(3, 1), T(95));
    BOOST_CHECK_EQUAL(r(3, 2), T(-89));
    BOOST_CHECK_EQUAL(r(3, 3), T(22));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpPostMult, T, test_types)
{
    matrix44<T> r { 4,-6,9,-5,-3,7,8,6,5,4,-1,-8,2,0,3,-4 };
    matrix44<T> m { -7,5,1,-8,3,3,-7,-9,9,-6,0,2,-2,8,4,1 };

    post_mult(r, m);
    BOOST_CHECK_EQUAL(r(0, 0), T(-54));
    BOOST_CHECK_EQUAL(r(0, 1), T(-50));
    BOOST_CHECK_EQUAL(r(0, 2), T(58));
    BOOST_CHECK_EQUAL(r(0, 3), T(-10));
    BOOST_CHECK_EQUAL(r(1, 0), T(81));
    BOOST_CHECK_EQUAL(r(1, 1), T(-25));
    BOOST_CHECK_EQUAL(r(1, 2), T(-96));
    BOOST_CHECK_EQUAL(r(1, 3), T(84));
    BOOST_CHECK_EQUAL(r(2, 0), T(-48));
    BOOST_CHECK_EQUAL(r(2, 1), T(31));
    BOOST_CHECK_EQUAL(r(2, 2), T(39));
    BOOST_CHECK_EQUAL(r(2, 3), T(45));
    BOOST_CHECK_EQUAL(r(3, 0), T(89));
    BOOST_CHECK_EQUAL(r(3, 1), T(95));
    BOOST_CHECK_EQUAL(r(3, 2), T(-89));
    BOOST_CHECK_EQUAL(r(3, 3), T(22));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpMultOp, T, test_types)
{
    matrix44<T> m1 { 4,-6,9,-5,-3,7,8,6,5,4,-1,-8,2,0,3,-4 };
    matrix44<T> m2 { -7,5,1,-8,3,3,-7,-9,9,-6,0,2,-2,8,4,1 };

    matrix44<T> r;
    r = m1 * m2;
    BOOST_CHECK_EQUAL(r(0, 0), T(-54));
    BOOST_CHECK_EQUAL(r(0, 1), T(-50));
    BOOST_CHECK_EQUAL(r(0, 2), T(58));
    BOOST_CHECK_EQUAL(r(0, 3), T(-10));
    BOOST_CHECK_EQUAL(r(1, 0), T(81));
    BOOST_CHECK_EQUAL(r(1, 1), T(-25));
    BOOST_CHECK_EQUAL(r(1, 2), T(-96));
    BOOST_CHECK_EQUAL(r(1, 3), T(84));
    BOOST_CHECK_EQUAL(r(2, 0), T(-48));
    BOOST_CHECK_EQUAL(r(2, 1), T(31));
    BOOST_CHECK_EQUAL(r(2, 2), T(39));
    BOOST_CHECK_EQUAL(r(2, 3), T(45));
    BOOST_CHECK_EQUAL(r(3, 0), T(89));
    BOOST_CHECK_EQUAL(r(3, 1), T(95));
    BOOST_CHECK_EQUAL(r(3, 2), T(-89));
    BOOST_CHECK_EQUAL(r(3, 3), T(22));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpMultEqOp, T, test_types)
{
    matrix44<T> r { 4,-6,9,-5,-3,7,8,6,5,4,-1,-8,2,0,3,-4 };
    matrix44<T> m { -7,5,1,-8,3,3,-7,-9,9,-6,0,2,-2,8,4,1 };

    r *= m;
    BOOST_CHECK_EQUAL(r(0, 0), T(-54));
    BOOST_CHECK_EQUAL(r(0, 1), T(-50));
    BOOST_CHECK_EQUAL(r(0, 2), T(58));
    BOOST_CHECK_EQUAL(r(0, 3), T(-10));
    BOOST_CHECK_EQUAL(r(1, 0), T(81));
    BOOST_CHECK_EQUAL(r(1, 1), T(-25));
    BOOST_CHECK_EQUAL(r(1, 2), T(-96));
    BOOST_CHECK_EQUAL(r(1, 3), T(84));
    BOOST_CHECK_EQUAL(r(2, 0), T(-48));
    BOOST_CHECK_EQUAL(r(2, 1), T(31));
    BOOST_CHECK_EQUAL(r(2, 2), T(39));
    BOOST_CHECK_EQUAL(r(2, 3), T(45));
    BOOST_CHECK_EQUAL(r(3, 0), T(89));
    BOOST_CHECK_EQUAL(r(3, 1), T(95));
    BOOST_CHECK_EQUAL(r(3, 2), T(-89));
    BOOST_CHECK_EQUAL(r(3, 3), T(22));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpTransposeInPlace, T, test_types)
{
    matrix44<T> t { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    matrix44<T> r { 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };

    BOOST_CHECK(transpose(t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpTranspose, T, test_types)
{
    matrix44<T> t { 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };
    matrix44<T> r { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    matrix44<T> m;
    BOOST_CHECK(transpose(m, t) == r);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpDeterminant, T, test_types)
{
    matrix44<T> m1 { -5,0,-3,1,6,1,4,6,0,-1,-5,0,0,2,1,3 };
    matrix44<T> m2 { 3,1,4,5,0,2,0,0,2,0,6,2,-1,-2,-3,0 };

    BOOST_CHECK_EQUAL(determinant(m1), T(-255));
    BOOST_CHECK_EQUAL(determinant(m2), T(20));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpInvert, T, float_types)
{
    matrix44<T> t { -5,0,-3,1,6,1,4,6,0,-1,-5,0,0,2,1,3 };
    matrix44<T> r { -0.2,0,0.133,0.067,-0.353,-0.294,0.118,0.706,0.071,
                     0.059,-0.224,-0.141,0.212,0.176,-0.004,-0.09 };

    matrix44<T> m;
    invert(m, t);
    BOOST_CHECK(is_equal(m, r, T(SMALL)));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Mat44_OpInvertUnary, T, float_types)
{
    matrix44<T> t { 3,1,4,5,0,2,0,0,2,0,6,2,-1,-2,-3,0 };
    matrix44<T> r { 0.6,-2.5,-1.5,-2.2,0,0.5,0,0,-0.2,
                    0.5,0.5,0.4,0,1.0,0.5,1.0 };

    BOOST_CHECK(is_equal(invert(t), r, T(SMALL)));
}

//BOOST_AUTO_TEST_CASE(Insterters)
//{
//    matrix44<int> mtx { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
//
//    matrix44<float> mtx
//    {
//         3.141593, 938.27231,  8.617365,  1.674929,
//           6.0221,  2.718282, 939.56563,  8.314510,
//        931.49432,  1.672623,  0.577216, 54.722391,
//         96.48530, 57.883882,  20.67834,  1.618034
//    };
//
//    std::ofstream os("../../test/patterns/matrix44.txt");
//    os << separator(',') << mtx << std::endl << std::endl;
//    os << std::fixed << std::setprecision(3)
//       << mtx << std::endl << std::endl;
//    os << delimiters('|') << mtx << std::endl << std::endl;
//    os << setew(7) << mtx << std::endl << std::endl;
//    os << std::setw(40) << mtx << std::endl << std::endl;
//    os << spaces << mtx << std::endl << std::endl;
//    os << horizontal << mtx << std::endl << std::endl;
//    os << setew(0) << mtx << std::endl << std::endl;
//    os << delimiters('{', '}') << mtx << std::endl << std::endl;
//    os << rowmajor << mtx << std::endl << std::endl;
//    os << colmajor << nospaces << mtx << std::endl << std::endl;
//    os << separator(' ') << mtx << std::endl << std::endl;
//    os << std::setw(115) << mtx << std::endl << std::endl;
//    os << delimiters('\0') << mtx << std::endl;
//}

BOOST_AUTO_TEST_CASE(Mat44_Inserter)
{
    output_test_stream cout("../../test/patterns/matrix44.txt", true);
/// [matrix44 inserter]
    matrix44<float> mtx
    {
         3.141593, 938.27231,  8.617365,  1.674929,
           6.0221,  2.718282, 939.56563,  8.314510,
        931.49432,  1.672623,  0.577216, 54.722391,
         96.48530, 57.883882,  20.67834,  1.618034
    };

    cout << separator(',') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
       << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(40) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << rowmajor << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << colmajor << nospaces << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(' ') << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(115) << mtx << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << mtx << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [matrix44 inserter]
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

