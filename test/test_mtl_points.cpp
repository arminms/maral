// $Id$
//------------------------------------------------------------------------------

#include <fstream>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/mpl/list.hpp>

#include <mtl/mtl.hpp>
#include <units.hpp>

#define PATTERNS_FOLDER "patterns/"

using boost::test_tools::output_test_stream;
using namespace maral::mtl;
namespace utrc = boost::unit_test::runtime_config;

typedef boost::mpl::list<int,float,double,long double> test_types;
typedef boost::mpl::list<float,double,long double> float_types;

template<typename T>
struct ETHAN
{
    T ethan[24];

    ETHAN()
    {
        // Ref: Snyder L.C., Basch H. Molecular wave functions and properties:
        // tabulated form SCF calculation in a Guassian basis set, John Wiley
        // & Sons, p T-74, 1972
        ethan [0] = T( 0.00000000); ethan [1] = T( 0.00000000);
        ethan [2] = T( 0.00000000); // [0]  C1       H6
        ethan [3] = T( 0.00000000); ethan [4] = T( 0.00000000);
        ethan [5] = T( 2.91589999); // [3]  C2       |
        ethan [6] = T( 1.69855762); ethan [7] = T(-0.98066292);
        ethan [8] = T(-0.69996772); // [6]  H1  H5 - C2 - H4
        ethan [9] = T(-1.69855762); ethan[10] = T(-0.98066792);
        ethan[11] = T(-0.69996772); // [9]  H2       |
        ethan[12] = T( 0.00000000); ethan[13] = T( 1.96132584);
        ethan[14] = T(-0.69996772); // [12] H3  H2 - C1 - H3
        ethan[15] = T( 1.69855762); ethan[16] = T( 0.98066292);
        ethan[17] = T( 3.61586168); // [15] H4       |
        ethan[18] = T( 0.00000000); ethan[19] = T(-1.96132579);
        ethan[20] = T( 3.61586168); // [18] H5       H1
        ethan[21] = T(-1.69855762); ethan[22] = T( 0.98066292);
        ethan[23] = T( 3.61586168); // [21] H6
    }
};

BOOST_AUTO_TEST_SUITE(Points)

BOOST_AUTO_TEST_SUITE( Pnt2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_RvalueRef, T, test_types)
{
    point2<T> pnt = point2<T>().zero();
    BOOST_CHECK(pnt == point2<T>().zero());
    BOOST_CHECK_EQUAL(pnt[0], (T)0);
    BOOST_CHECK_EQUAL(pnt[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Constructors, T, test_types)
{
    point2<T> pnt((T)1, (T)2);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_VectorExplicit, T, test_types)
{
    vector2<T> vec((T)1, (T)2);
    point2<T> pnt((vector2<T>)vec);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_CopyConstruct, T, test_types)
{
    point2<T> pnt;

    pnt[0] = (T)2;
    pnt[1] = (T)4;

    point2<T> point_copy(pnt);

    BOOST_CHECK_EQUAL(point_copy[0], (T)2);
    BOOST_CHECK_EQUAL(point_copy[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_X, T, test_types)
{
    point2<T> pnt;

    pnt.x() = (T)1;
    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Y, T, test_types)
{
    point2<T> pnt;

    pnt.y() = (T)2;
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_GetX, T, test_types)
{
    point2<T> pnt((T)1, (T)2);

    BOOST_CHECK_EQUAL(pnt.get_x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_GetY, T, test_types)
{
    point2<T> pnt((T)1, (T)2);

    BOOST_CHECK_EQUAL(pnt.get_y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_SetX, T, test_types)
{
    point2<T> pnt;

    pnt.set_x((T)1);
    BOOST_CHECK_EQUAL(pnt[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_SetY, T, test_types)
{
    point2<T> pnt;

    pnt.set_y((T)2);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Set, T, test_types)
{
    point2<T> pnt;
    pnt.set((T)1, (T)2);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_SetPtr, T, test_types)
{
    T data[2] = {(T)1, (T)2};

    point2<T> pnt;
    pnt.set(data);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Zero, T, test_types)
{
    point2<T> pnt;

    BOOST_CHECK_EQUAL(pnt.zero()[0], (T)0);
    BOOST_CHECK_EQUAL(pnt[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_GetData, T, test_types)
{
    T* data;
    point2<T> pnt((T)1, (T)2);
    data = pnt.get_data();

    BOOST_CHECK_EQUAL(data[0], (T)1);
    BOOST_CHECK_EQUAL(data[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_BracketOp, T, test_types)
{
    point2<T> ref((T)1, (T)2);
    point2<T> pnt;

    pnt[0] = (T)1;
    pnt[1] = (T)2;
    BOOST_CHECK(ref == pnt);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Pnt2Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpEqualityCompare, T, test_types)
{
    point2<T> point1((T)1, (T)2);
    point2<T> point2(point1);

    BOOST_CHECK(point1 == point2);
    BOOST_CHECK(!(point1 != point2));

    point2 = point1;
    point2[0] = (T)21.10f;
    BOOST_CHECK(point1 != point2);
    BOOST_CHECK(!(point1 == point2));

    point2 = point1;
    point2[1] = (T)21.10f;
    BOOST_CHECK(point1 != point2);
    BOOST_CHECK(!(point1 == point2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpIsEqual, T, float_types)
{
    point2<T> pnt1(1.0, 2.0);
    point2<T> pnt2(pnt1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(pnt1, pnt2, eps));
        BOOST_CHECK_CLOSE(pnt1[0], pnt2[0], eps);
        BOOST_CHECK_CLOSE(pnt1[1], pnt2[1], eps);
    }

    pnt1.set(1.0, 1.0);
    for(unsigned elt=0; elt<2; elt++)
    {
        pnt2 = pnt1;
        pnt2[elt] = (T)21.0;
        BOOST_CHECK(!is_equal(pnt1, pnt2, T(10.0)));
        BOOST_CHECK(!is_equal(pnt1, pnt2, T(19.9)));
        BOOST_CHECK( is_equal(pnt1, pnt2, T(20.1)));
        BOOST_CHECK( is_equal(pnt1, pnt2, T(22.0)));
    }

    pnt1.set( T(3.141593), T(938.27231) );
    pnt2.set(  T(3.14159),   T(938.272) );

    BOOST_CHECK(!is_equal(pnt1, pnt2, T(0)) );
    BOOST_CHECK(!is_equal(pnt1, pnt2, T(0.0001)) );
    BOOST_CHECK( is_equal(pnt1, pnt2, T(0.0005)) );
    BOOST_CHECK( is_equal(pnt1, pnt2, T(0.001)) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpPlusEq, T, test_types)
{
    point2<T> p((T)1, (T)2);
    vector2<T> v((T)2, (T)2);

    p += v;
    BOOST_CHECK_EQUAL(p[0], (T)3);
    BOOST_CHECK_EQUAL(p[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpPlus, T, test_types)
{
    point2<T> p((T)2, (T)2);
    vector2<T> v((T)1, (T)2);

    point2<T> r = p + v;
    BOOST_CHECK_EQUAL(r[0], (T)3);
    BOOST_CHECK_EQUAL(r[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinusEq, T, test_types)
{
    point2<T> p((T)1, (T)2);
    vector2<T> v((T)2, (T)2);

    p -= v;
    BOOST_CHECK_EQUAL(p[0], (T)-1);
    BOOST_CHECK_EQUAL(p[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinusVector, T, test_types)
{
    point2<T> point1((T)2, (T)2);
    point2<T> point2((T)1, (T)2);

    vector2<T> vec = point1 - point2;
    BOOST_CHECK_EQUAL(vec[0], (T)-1);
    BOOST_CHECK_EQUAL(vec[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinus, T, test_types)
{
    point2<T> p((T)2, (T)2);
    vector2<T> v((T)1, (T)2);

    point2<T> r = p - v;
    BOOST_CHECK_EQUAL(r[0], (T)1);
    BOOST_CHECK_EQUAL(r[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpNegate, T, test_types)
{
    point2<T> pnt2((T)2, (T)-3);

    point2<T> pnt1 = -pnt2;
    BOOST_CHECK_EQUAL(pnt1[0], (T)-2);
    BOOST_CHECK_EQUAL(pnt1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpAddScaled, T, test_types)
{
    point2<T> p((T)1, (T)2);
    vector2<T> v((T)2, (T)2);

    add_scaled((T)4, p, v);
    BOOST_CHECK_EQUAL(p[0], (T)9);
    BOOST_CHECK_EQUAL(p[1], (T)10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpSumScaled, T, test_types)
{
    point2<T> p((T)1, (T)2);
    vector2<T> v((T)2, (T)2);

    point2<T> result = sum_scaled((T)4, p, v);
    BOOST_CHECK_EQUAL(result[0], (T)9);
    BOOST_CHECK_EQUAL(result[1], (T)10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMaximize, T, test_types)
{
    point2<T> pnt1;
    point2<T> pnt2((T)1, (T)4);
    point2<T> pnt3((T)3, (T)2);

    maximize(pnt1, pnt2, pnt3);
    BOOST_CHECK_EQUAL(pnt1[0], (T)3);
    BOOST_CHECK_EQUAL(pnt1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinimize, T, test_types)
{
    point2<T> pnt1;
    point2<T> pnt2((T)1, (T)4);
    point2<T> pnt3((T)3, (T)2);

    minimize(pnt1, pnt2, pnt3);
    BOOST_CHECK_EQUAL(pnt1[0], (T)1);
    BOOST_CHECK_EQUAL(pnt1[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMiddle, T, float_types)
{
    point2<T> pnt1;
    point2<T> pnt2((T)1, (T)2);
    point2<T> pnt3((T)3, (T)4);

    middle(pnt1, pnt2, pnt3);
    BOOST_CHECK_EQUAL(pnt1[0], (T)2);
    BOOST_CHECK_EQUAL(pnt1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDistance, T, float_types)
{
    point2<T> point1((T)3, (T)4);
    point2<T> point2((T)1, (T)2);

    BOOST_CHECK_CLOSE(distance(point1, point2), T(2.828427f), SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDistanceSq, T, test_types)
{
    point2<T> point1((T)3, (T)4);
    point2<T> point2((T)1, (T)2);

    BOOST_CHECK_EQUAL(distance2(point1, point2), T(8));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpAngle, T, float_types)
{
/// [point2 angle]
    namespace mu = maral::units;

    point2<T> pnt1(1, 2);
    point2<T> pnt2(1, 1);
    point2<T> pnt3(2, 1);

    auto ang = mu::radians( angle(pnt1, pnt2, pnt3) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(90.0), SMALL);

    pnt1.set(2, 2);
    ang = mu::radians( angle(pnt1, pnt2, pnt3) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(45.0), SMALL);

    pnt1.set(1, 1);
    ang = mu::radians( angle(pnt1, pnt2, pnt3) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(0.0), SMALL);
/// [point2 angle]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Inserter, T, float_types)
{
    output_test_stream cout(
        PATTERNS_FOLDER"pntvec2.txt",
        !utrc::save_pattern() );
/// [point2 inserter]
    point2<T> pnt( T(3.141593), T(938.27231) );

    cout << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
         << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7) << delimiters('[', ']')
         << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(15) << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << delimiters('|') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(',') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << nospaces << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(20) << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << pnt << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [point2 inserter]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Extractor, T, float_types)
{
    std::ifstream cin(PATTERNS_FOLDER"pntvec2.txt");
/// [point2 extractor]
    point2<T> pnt( T(3.141593), T(938.27231) );
    point2<T> ext;

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('[', ']') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> horizontal >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> separator(',') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('{', '}') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('\0') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );
/// [point2 extractor]
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Pnt3 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Constructors, T, test_types)
{
    point3<T> pnt((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_VectorExplicit, T, test_types)
{
    vector3<T> vec((T)1, (T)2, (T)3);
    point3<T> pnt((vector3<T>)vec);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_CopyConstruct, T, test_types)
{
    point3<T> pnt;

    pnt[0] = (T)2;
    pnt[1] = (T)4;
    pnt[2] = (T)6;

    point3<T> point_copy(pnt);

    BOOST_CHECK_EQUAL(point_copy[0], (T)2);
    BOOST_CHECK_EQUAL(point_copy[1], (T)4);
    BOOST_CHECK_EQUAL(point_copy[2], (T)6);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_X, T, test_types)
{
    point3<T> pnt;

    pnt.x() = (T)1;
    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Y, T, test_types)
{
    point3<T> pnt;

    pnt.y() = (T)2;
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Z, T, test_types)
{
    point3<T> pnt;

    pnt.z() = (T)3;
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
    BOOST_CHECK_EQUAL(pnt.z(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetX, T, test_types)
{
    point3<T> pnt((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(pnt.get_x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetY, T, test_types)
{
    point3<T> pnt((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(pnt.get_y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetZ, T, test_types)
{
    point3<T> pnt((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(pnt.get_z(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetX, T, test_types)
{
    point3<T> pnt;

    pnt.set_x((T)1);
    BOOST_CHECK_EQUAL(pnt[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetY, T, test_types)
{
    point3<T> pnt;

    pnt.set_y((T)2);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetZ, T, test_types)
{
    point3<T> pnt;

    pnt.set_z((T)3);
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Set, T, test_types)
{
    point3<T> pnt;
    pnt.set((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetPtr, T, test_types)
{
    T data[3] = {(T)1, (T)2, (T)3};

    point3<T> pnt;
    pnt.set(data);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Zero, T, test_types)
{
    point3<T> pnt;

    BOOST_CHECK_EQUAL(pnt.zero()[0], (T)0);
    BOOST_CHECK_EQUAL(pnt[1], (T)0);
    BOOST_CHECK_EQUAL(pnt[2], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetData, T, test_types)
{
    T* data;
    point3<T> pnt((T)1, (T)2, (T)3);
    data = pnt.get_data();

    BOOST_CHECK_EQUAL(data[0], (T)1);
    BOOST_CHECK_EQUAL(data[1], (T)2);
    BOOST_CHECK_EQUAL(data[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_BracketOp, T, test_types)
{
    point3<T> ref((T)1, (T)2, (T)3);
    point3<T> pnt;

    pnt[0] = (T)1;
    pnt[1] = (T)2;
    pnt[2] = (T)3;
    BOOST_CHECK(ref == pnt);

    BOOST_CHECK_EQUAL(pnt[0], (T)1);
    BOOST_CHECK_EQUAL(pnt[1], (T)2);
    BOOST_CHECK_EQUAL(pnt[2], (T)3);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Pnt3Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpEqualityCompare, T, test_types)
{
    point3<T> point1((T)1, (T)2, T(3));
    point3<T> point2(point1);

    BOOST_CHECK(point1 == point2);
    BOOST_CHECK(!(point1 != point2));

    point2 = point1;
    point2[0] = (T)21.10f;
    BOOST_CHECK(point1 != point2);
    BOOST_CHECK(!(point1 == point2));

    point2 = point1;
    point2[1] = (T)21.10f;
    BOOST_CHECK(point1 != point2);
    BOOST_CHECK(!(point1 == point2));

    point2 = point1;
    point2[2] = (T)21.10f;
    BOOST_CHECK(point1 != point2);
    BOOST_CHECK(!(point1 == point2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpIsEqual, T, float_types)
{
    point3<T> pnt1(1.0, 2.0, 3.0);
    point3<T> pnt2(pnt1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(pnt1, pnt2, eps));
        BOOST_CHECK_CLOSE(pnt1[0], pnt2[0], eps);
        BOOST_CHECK_CLOSE(pnt1[1], pnt2[1], eps);
        BOOST_CHECK_CLOSE(pnt1[2], pnt2[2], eps);
    }

    pnt1.set(1.0f, 1.0f, 1.0f);
    for(unsigned elt=0; elt<3; elt++)
    {
        pnt2 = pnt1;
        pnt2[elt] = (T)21.0;
        BOOST_CHECK(!is_equal(pnt1, pnt2, T(10.0)));
        BOOST_CHECK(!is_equal(pnt1, pnt2, T(19.9)));
        BOOST_CHECK( is_equal(pnt1, pnt2, T(20.1)));
        BOOST_CHECK( is_equal(pnt1, pnt2, T(22.0)));
    }

    pnt1.set( T(3.141593), T(938.27231), T(2.718282) );
    pnt2.set(  T(3.14159),   T(938.272),  T(2.71828) );

    BOOST_CHECK(!is_equal(pnt1, pnt2, T(0)) );
    BOOST_CHECK(!is_equal(pnt1, pnt2, T(0.0001)) );
    BOOST_CHECK( is_equal(pnt1, pnt2, T(0.0005)) );
    BOOST_CHECK( is_equal(pnt1, pnt2, T(0.001)) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpPlusEq, T, test_types)
{
    point3<T> p((T)1, (T)2, (T)3);
    vector3<T> v((T)2, (T)2, (T)2);

    p += v;
    BOOST_CHECK_EQUAL(p[0], (T)3);
    BOOST_CHECK_EQUAL(p[1], (T)4);
    BOOST_CHECK_EQUAL(p[2], (T)5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpPlus, T, test_types)
{
    vector3<T> v((T)2, (T)2, (T)3);
    point3<T> p((T)1, (T)2, (T)3);

    point3<T> r = p + v;
    BOOST_CHECK_EQUAL(r[0], (T)3);
    BOOST_CHECK_EQUAL(r[1], (T)4);
    BOOST_CHECK_EQUAL(r[2], (T)6);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMinusEq, T, test_types)
{
    point3<T> p((T)1, (T)2, (T)3);
    vector3<T> v((T)2, (T)2, (T)2);

    p -= v;
    BOOST_CHECK_EQUAL(p[0], (T)-1);
    BOOST_CHECK_EQUAL(p[1], (T)0);
    BOOST_CHECK_EQUAL(p[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMinusVector, T, test_types)
{
    point3<T> p1((T)2, (T)2, (T)4);
    point3<T> p2((T)1, (T)2, (T)5);

    vector3<T> vec = p1 - p2;
    BOOST_CHECK_EQUAL(vec[0], (T)-1);
    BOOST_CHECK_EQUAL(vec[1], (T)0);
    BOOST_CHECK_EQUAL(vec[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMinus, T, test_types)
{
    vector3<T> v((T)2, (T)2, (T)2);
    point3<T> p((T)1, (T)2, (T)3);

    point3<T> r = p - v;
    BOOST_CHECK_EQUAL(r[0], (T)-1);
    BOOST_CHECK_EQUAL(r[1], (T)0);
    BOOST_CHECK_EQUAL(r[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpNegate, T, test_types)
{
    point3<T> point2((T)2, (T)-3, (T)5);

    point3<T> point1 = -point2;
    BOOST_CHECK_EQUAL(point1[0], (T)-2);
    BOOST_CHECK_EQUAL(point1[1], (T)3);
    BOOST_CHECK_EQUAL(point1[2], (T)-5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpAddScaled, T, test_types)
{
    point3<T> p((T)1, (T)2, (T)3);
    vector3<T> v((T)2, (T)2, (T)2);

    add_scaled((T)4, p, v);
    BOOST_CHECK_EQUAL(p[0], (T)9);
    BOOST_CHECK_EQUAL(p[1], (T)10);
    BOOST_CHECK_EQUAL(p[2], (T)11);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpSumScaled, T, test_types)
{
    point3<T> p((T)1, (T)2, (T)3);
    vector3<T> v((T)2, (T)2, (T)2);

    point3<T> result = sum_scaled((T)4, p, v);
    BOOST_CHECK_EQUAL(result[0], (T)9);
    BOOST_CHECK_EQUAL(result[1], (T)10);
    BOOST_CHECK_EQUAL(result[2], (T)11);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMaximize, T, test_types)
{
    point3<T> pnt1;
    point3<T> pnt2((T)1, (T)-4, (T)-1);
    point3<T> pnt3((T)3, (T)2, (T)-2);

    maximize(pnt1, pnt2, pnt3);
    BOOST_CHECK_EQUAL(pnt1[0], (T)3);
    BOOST_CHECK_EQUAL(pnt1[1], (T)2);
    BOOST_CHECK_EQUAL(pnt1[2], (T)-1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMinimize, T, test_types)
{
    point3<T> pnt1;
    point3<T> pnt2((T)1, (T)-4, (T)-1);
    point3<T> pnt3((T)3, (T)2, (T)-2);

    minimize(pnt1, pnt2, pnt3);
    BOOST_CHECK_EQUAL(pnt1[0], (T)1);
    BOOST_CHECK_EQUAL(pnt1[1], (T)-4);
    BOOST_CHECK_EQUAL(pnt1[2], (T)-2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMiddle, T, float_types)
{
    point3<T> pnt1;
    point3<T> pnt2((T)1, (T)2, (T)3);
    point3<T> pnt3((T)3, (T)4, (T)5);

    middle(pnt1, pnt2, pnt3);
    BOOST_CHECK_EQUAL(pnt1[0], (T)2);
    BOOST_CHECK_EQUAL(pnt1[1], (T)3);
    BOOST_CHECK_EQUAL(pnt1[2], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpDistance, T, float_types)
{
    point3<T> pnt1((T)3, (T)4, (T)5);
    point3<T> pnt2((T)1, (T)2, (T)5);

    BOOST_CHECK_CLOSE(distance(pnt1, pnt2), T(2.828427f), SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpDistanceSq, T, test_types)
{
    point3<T> pnt1((T)3, (T)4, (T)3);
    point3<T> pnt2((T)1, (T)2, (T)5);

    BOOST_CHECK_EQUAL(distance2(pnt1, pnt2), T(12));
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(Point3_OpAngle, T, float_types, ETHAN<T>)
{
/// [point3 angle]
    namespace mu = maral::units;

    point3<T> pnt1(1, 1, 0);
    point3<T> pnt2(1, 0, 0);
    point3<T> pnt3(2, 0, 1);

    auto ang = mu::radians( angle(pnt1, pnt2, pnt3) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(90.0), SMALL);

//    std::cout << ang << " ("
//              << mu::to_degrees(ang) << ", "
//              << mu::to_gradians(ang)
//              << ')' << std::endl;

    pnt1.set(2, 0, 0);
    ang = mu::radians( angle(pnt1, pnt2, pnt3) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(45.0), SMALL);

    pnt1.set(0, 0, 0);
    ang = mu::radians( angle(pnt1, pnt2, pnt3) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(135.0), SMALL);

    point3<T> C1;
    C1.set(&ETHAN<T>::ethan[0]);
    point3<T> C2;
    C2.set(&ETHAN<T>::ethan[3]);
    point3<T> H1;
    H1.set(&ETHAN<T>::ethan[6]);
    ang = mu::radians( angle(C2, C1, H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), 109.640722, SMALL);
    ang = mu::radians( angle(H1, C1, C2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), 109.640722, SMALL);
/// [point3 angle]
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(Point3_OpTorsionAngle, T, float_types, ETHAN<T>)
{
/// [point3 torsion angle]
    namespace mu = maral::units;

    point3<T> C1;
    C1.set(&ETHAN<T>::ethan[0]);
    point3<T> C2;
    C2.set(&ETHAN<T>::ethan[3]);
    point3<T> H1;
    H1.set(&ETHAN<T>::ethan[6]);
    point3<T> H4;
    H4.set(&ETHAN<T>::ethan[15]);
    point3<T> H5;
    H5.set(&ETHAN<T>::ethan[18]);
    point3<T> H6;
    H6.set(&ETHAN<T>::ethan[21]);

    auto ang = mu::radians( torsion_angle(H1, C1, C2, H4) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-60.0), T(0.001));

    ang = mu::radians( torsion_angle(H4, C2, C1, H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-60.0), T(0.001));

    ang = mu::radians( torsion_angle(H1, C1, C2, H5) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(60.0), T(0.001));

    ang = mu::radians( torsion_angle(H5, C2, C1, H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(60.0), T(0.001));

    ang = mu::radians( torsion_angle(H1, C1, C2, H6) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-180.0), T(0.001));

    ang = mu::radians( torsion_angle(H6, C2, C1, H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-180.0), T(0.001));
/// [point3 torsion angle]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Inserter, T, float_types)
{
    output_test_stream cout(
        PATTERNS_FOLDER"pntvec3.txt",
        !utrc::save_pattern() );
/// [point3 inserter]
    point3<T> pnt( T(3.141593), T(938.27231), T(2.718282) );

    cout << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
         << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7) << delimiters('[', ']')
         << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(15) << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << delimiters('|') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(',') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << nospaces << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(25) << pnt << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << pnt << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [point3 inserter]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Extractor, T, float_types)
{
    std::ifstream cin(PATTERNS_FOLDER"pntvec3.txt");
/// [point3 extractor]
    point3<T> pnt( T(3.141593), T(938.27231), T(2.718282) );
    point3<T> ext;

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('[', ']') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> horizontal >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> separator(',') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('{', '}') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );

    cin >> delimiters('\0') >> ext.zero();
    BOOST_CHECK( is_equal(pnt, ext) );
/// [point3 extractor]
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
