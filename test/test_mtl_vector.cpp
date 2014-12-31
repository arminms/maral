// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#include <fstream>

// due to inclusion of <windows.h> by header only boost::test, we need
// the following define to prevent problem with std::numeric_limits
#   if defined(_MSC_VER)
#       define NOMINMAX
#   endif  //_MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/mpl/list.hpp>

#include <maral/mtl/mtl.hpp>
#include <maral/units.hpp>

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
        ethan [0] = T (0.00000000); ethan [1] = T (0.00000000);
        ethan [2] = T (0.00000000); // [0]  C1       H6
        ethan [3] = T (0.00000000); ethan [4] = T (0.00000000);
        ethan [5] = T (2.91589999); // [3]  C2       |
        ethan [6] = T (1.69855762); ethan [7] = T(-0.98066292);
        ethan [8] = T(-0.69996772); // [6]  H1  H5 - C2 - H4
        ethan [9] = T(-1.69855762); ethan[10] = T(-0.98066792);
        ethan[11] = T(-0.69996772); // [9]  H2       |
        ethan[12] = T (0.00000000); ethan[13] = T (1.96132584);
        ethan[14] = T(-0.69996772); // [12] H3  H2 - C1 - H3
        ethan[15] = T (1.69855762); ethan[16] = T (0.98066292);
        ethan[17] = T (3.61586168); // [15] H4       |
        ethan[18] = T (0.00000000); ethan[19] = T(-1.96132579);
        ethan[20] = T (3.61586168); // [18] H5       H1
        ethan[21] = T(-1.69855762); ethan[22] = T (0.98066292);
        ethan[23] = T (3.61586168); // [21] H6
    }
};

BOOST_AUTO_TEST_SUITE(Vectors)

BOOST_AUTO_TEST_SUITE( Vec2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Constructors, T, test_types)
{
    vector2<T> vec((T)1, (T)2);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_ConstructFromPoints, T, test_types)
{
    point2<T> pnt1((T)2, (T)2);
    point2<T> pnt2((T)1, (T)2);

    vector2<T> vec(pnt1, pnt2);
    BOOST_CHECK_EQUAL(vec[0], (T)-1);
    BOOST_CHECK_EQUAL(vec[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_PointExplicit, T, test_types)
{
    point2<T> point((T)1, (T)2);
    vector2<T> vec((point2<T>)point);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_CopyConstruct, T, test_types)
{
    vector2<T> vec;

    vec[0] = (T)2;
    vec[1] = (T)4;

    vector2<T> vecCopy(vec);

    BOOST_CHECK_EQUAL(vecCopy[0], (T)2);
    BOOST_CHECK_EQUAL(vecCopy[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_X, T, test_types)
{
    vector2<T> vec;

    vec.x() = (T)1;
    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Y, T, test_types)
{
    vector2<T> vec;

    vec.y() = (T)2;
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_GetX, T, test_types)
{
    vector2<T> vec((T)1, (T)2);

    BOOST_CHECK_EQUAL(vec.get_x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_GetY, T, test_types)
{
    vector2<T> vec((T)1, (T)2);

    BOOST_CHECK_EQUAL(vec.get_y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_SetX, T, test_types)
{
    vector2<T> vec;

    vec.set_x((T)1);
    BOOST_CHECK_EQUAL(vec[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_SetY, T, test_types)
{
    vector2<T> vec;

    vec.set_y((T)2);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Set, T, test_types)
{
    vector2<T> vec;
    vec.set((T)1, (T)2);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_SetPtr, T, test_types)
{
    T data[2] = {(T)1, (T)2};

    vector2<T> vec;
    vec.set(data);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Zero, T, test_types)
{
    vector2<T> vec;

    BOOST_CHECK_EQUAL(vec.zero()[0], (T)0);
    BOOST_CHECK_EQUAL(vec[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_GetData, T, test_types)
{
    T* data;
    vector2<T> vec((T)1, (T)2);
    data = vec.get_data();

    BOOST_CHECK_EQUAL(data[0], (T)1);
    BOOST_CHECK_EQUAL(data[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_BracketOp, T, test_types)
{
    vector2<T> ref((T)1, (T)2);
    vector2<T> vec;

    vec[0] = (T)1;
    vec[1] = (T)2;
    BOOST_CHECK(ref == vec);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Vec2Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpEqualityCompare, T, test_types)
{
    vector2<T> vec1((T)1, (T)2);
    vector2<T> vec2(vec1);

    BOOST_CHECK(vec1 == vec2);
    BOOST_CHECK(!(vec1 != vec2));

    vec2 = vec1;
    vec2[0] = (T)21.10f;
    BOOST_CHECK(vec1 != vec2);
    BOOST_CHECK(!(vec1 == vec2));

    vec2 = vec1;
    vec2[1] = (T)21.10f;
    BOOST_CHECK(vec1 != vec2);
    BOOST_CHECK(!(vec1 == vec2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpIsEqual, T, float_types)
{
    vector2<T> vec1(1.0, 2.0);
    vector2<T> vec2(vec1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(vec1, vec2, eps));
        BOOST_CHECK_CLOSE(vec1[0], vec2[0], eps);
        BOOST_CHECK_CLOSE(vec1[1], vec2[1], eps);
    }

    vec1.set(1.0, 1.0);
    for(unsigned elt=0; elt<2; elt++)
    {
        vec2 = vec1;
        vec2[elt] = (T)21.0;
        BOOST_CHECK(!is_equal(vec1, vec2, T(10.0)));
        BOOST_CHECK(!is_equal(vec1, vec2, T(19.9)));
        BOOST_CHECK( is_equal(vec1, vec2, T(20.1)));
        BOOST_CHECK( is_equal(vec1, vec2, T(22.0)));
    }


    vec1.set( T(3.141593), T(938.27231) );
    vec2.set(  T(3.14159),   T(938.272) );

    BOOST_CHECK(!is_equal(vec1, vec2, T(0)) );
    BOOST_CHECK(!is_equal(vec1, vec2, T(0.0001)) );
    BOOST_CHECK( is_equal(vec1, vec2, T(0.0005)) );
    BOOST_CHECK( is_equal(vec1, vec2, T(0.001)) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpPlusEq, T, test_types)
{
    vector2<T> vec1((T)1, (T)2);
    vector2<T> vec2((T)2, (T)2);

    vec1 += vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)3);
    BOOST_CHECK_EQUAL(vec1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpPlus, T, test_types)
{
    vector2<T> vec2((T)2, (T)2);
    vector2<T> vec3((T)1, (T)2);

    vector2<T> vec1 = vec3 + vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)3);
    BOOST_CHECK_EQUAL(vec1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMinusEq, T, test_types)
{
    vector2<T> vec1((T)1, (T)2);
    vector2<T> vec2((T)2, (T)2);

    vec1 -= vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)-1);
    BOOST_CHECK_EQUAL(vec1[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMinus, T, test_types)
{
    vector2<T> vec2((T)2, (T)2);
    vector2<T> vec3((T)1, (T)2);

    vector2<T> vec1 = vec3 - vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)-1);
    BOOST_CHECK_EQUAL(vec1[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpNegate, T, test_types)
{
    vector2<T> vec2((T)2, (T)-3);

    vector2<T> vec1 = -vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)-2);
    BOOST_CHECK_EQUAL(vec1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMultScalarEq, T, test_types)
{
    vector2<T> vec((T)1, (T)2);

    vec *= (T)4;
    BOOST_CHECK_EQUAL(vec[0], (T)4);
    BOOST_CHECK_EQUAL(vec[1], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMultScalar, T, test_types)
{
    vector2<T> vec2((T)1, (T)2);

    vector2<T> vec1 = vec2 * (T)4.0;
    BOOST_CHECK_EQUAL(vec1[0], (T)4);
    BOOST_CHECK_EQUAL(vec1[1], (T)8);

    vec1 = (T)4.0 * vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)4);
    BOOST_CHECK_EQUAL(vec1[1], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDivScalarEq, T, test_types)
{
    vector2<T> vec((T)12, (T)8);

    vec /= (T)4;
    BOOST_CHECK_EQUAL(vec[0], (T)3);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDivScalar, T, test_types)
{
    vector2<T> vec2((T)12, (T)8);

    vector2<T> vec1 = vec2 / (T)4.0;
    BOOST_CHECK_EQUAL(vec1[0], (T)3);
    BOOST_CHECK_EQUAL(vec1[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMiddle, T, float_types)
{
    vector2<T> vec1;
    vector2<T> vec2((T)1, (T)2);
    vector2<T> vec3((T)3, (T)4);

    middle(vec1, vec2, vec3);
    BOOST_CHECK_EQUAL(vec1[0], (T)2);
    BOOST_CHECK_EQUAL(vec1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDot, T, float_types)
{
    vector2<T> v1(1, 0);
    vector2<T> v2(0, 1);

    // base vectors
    BOOST_CHECK_CLOSE(T(0), dot(v1,v2), T(SMALL));

    // other vectors
    v1.set(13.45f, -7.8f);
    v2.set(0.777f, 5.333f);

    T ans = -31.14675f;
    BOOST_CHECK_CLOSE(dot(v1,v2), ans, T(SMALL));
    BOOST_CHECK_CLOSE(dot(v2,v1), ans, T(SMALL));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpLength, T, float_types)
{
    vector2<T> v1(1, 0);
    vector2<T> v2(0, 1);
    T len, ans;

    BOOST_CHECK_CLOSE(length(v1), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length(v2), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length2(v1), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length2(v2), T(1.0f), T(SMALL));

    v1.set(2.0f, 4.0f);
    v2.set(12.0f, -2.0f);

    ans = 4.0f + 16.0f;
    len = length2(v1);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));

    ans = sqrt(ans);
    len = length(v1);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));

    ans = 144.0f + 4.0f;
    len = length2(v2);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));

    ans = sqrt(ans);
    len = length(v2);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpAngle, T, float_types)
{
/// [vector2 angle]
    namespace mu = maral::units;

    vector2<T> vec1(1, 0);
    vector2<T> vec2(0, 1);

    auto ang = mu::radians( angle(vec1, vec2) );
    BOOST_CHECK_CLOSE( mu::to_degrees(ang).value(), 90.0f, SMALL );

    vec2.set(1, 1);
    ang = mu::radians( angle(vec1, vec2) );
    BOOST_CHECK_CLOSE( mu::to_degrees(ang).value(), 45.0f, SMALL );

    vec1.set(3, 0);
    vec2.set(3, 3);
    ang = mu::radians( angle(vec1, vec2) );
    BOOST_CHECK_CLOSE( mu::to_degrees(ang).value(), 45.0f, SMALL );

    vec2.set(0, 0);
    ang = mu::radians( angle(vec1, vec2) );
    BOOST_CHECK_CLOSE( mu::to_degrees(ang).value(), 0.0f, SMALL );
/// [vector2 angle]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpNormalize, T, float_types)
{
    vector2<T> vec1(2, 4);
    vector2<T> vec2(vec1);

    normalize(vec1);
    vector2<T> temp = (vec1*length(vec2) );
    BOOST_CHECK(is_equal(vec2, temp, T(SMALL) ) );
    vec1.set(12, -2);
    vec2 = vec1;
    normalize(vec1);
    BOOST_CHECK(is_equal(vec2, vector2<T>(vec1*length(vec2) ), T(SMALL) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpIsNormalized, T, float_types)
{
    vector2<T> v1(1, 0);
    vector2<T> v2(0, 1);
    vector2<T> v3(2, 4);

    BOOST_CHECK(is_normalized(v1) );
    BOOST_CHECK(is_normalized(v2) );
    BOOST_CHECK(! is_normalized(v3) );

    v2 = v1;

    // epsilon tolerance
    for (T eps=0; eps<10; eps+=0.5)
    {
        BOOST_CHECK(is_normalized(v1, eps));
    }

    v2.set(21,0);
    BOOST_CHECK( ! is_normalized(v2, T(15.0f * 15.0f) ) );
    BOOST_CHECK( ! is_normalized(v2, T(19.9f * 19.9f) ) );
    BOOST_CHECK( is_normalized(v2, T(21.0f * 21.0f - 0.9f) ) );
    BOOST_CHECK( is_normalized(v2, T(21.0f * 21.0f + 0.9f) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpReflect, T, test_types)
{
    vector2<T> v(1, -1);
    vector2<T> n(0, 1);
    vector2<T> r;
    vector2<T> ans(1, 1);

    reflect(r, v, n);
    BOOST_CHECK(r == ans);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpLerp, T, float_types)
{
    vector2<T> v1(1, 0);
    vector2<T> v2(0, 1);
    vector2<T> v3(2, 4);

    const float eps = 0.0001f;
    vector2<T> q1(2, 3), q2(9.01f, 8.4f);
    vector2<T> expected_result1(q1), res1;
    vector2<T> expected_result2(q2), res2;

    lerp(res1, T(0.0f), q1, q2);
    lerp(res2, T(1.0f), q1, q2);
    BOOST_CHECK_CLOSE(expected_result1[0], res1[0], eps);
    BOOST_CHECK_CLOSE(expected_result1[1], res1[1], eps);
    BOOST_CHECK_CLOSE(expected_result2[0], res2[0], eps);
    BOOST_CHECK_CLOSE(expected_result2[1], res2[1], eps);

    // test interpolated values...
    vector2<T> q3(0, 0), q4(1, 1);
    vector2<T> expected_result3(0.35f, 0.35f), res3;
    vector2<T> expected_result4(0.69f, 0.69f), res4;

    lerp(res3, T(0.35f), q3, q4);
    lerp(res4, T(0.69f), q3, q4);
    BOOST_CHECK_CLOSE(expected_result3[0], res3[0], eps);
    BOOST_CHECK_CLOSE(expected_result3[1], res3[1], eps);
    BOOST_CHECK_CLOSE(expected_result4[0], res4[0], eps);
    BOOST_CHECK_CLOSE(expected_result4[1], res4[1], eps);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Inserter, T, float_types)
{
    output_test_stream cout(
        PATTERNS_FOLDER"pntvec2.txt",
        !utrc::save_pattern() );
/// [vector2 inserter]
    vector2<T> vec( T(3.141593), T(938.27231) );

    cout << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
         << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7) << delimiters('[', ']')
         << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(15) << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << delimiters('|') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(',') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << nospaces << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(20) << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << vec << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [vector2 inserter]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Extractor, T, float_types)
{
    std::ifstream cin(PATTERNS_FOLDER"pntvec2.txt");
/// [vector2 extractor]
    vector2<T> vec( T(3.141593), T(938.27231) );
    vector2<T> ext;

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('[', ']') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> horizontal >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> separator(',') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('{', '}') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('\0') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );
/// [vector2 extractor]
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Vec3 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Constructors, T, test_types)
{
    vector3<T> vec((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_ConstructFromPoints, T, test_types)
{
    point3<T> p1((T)2, (T)2, (T)4);
    point3<T> p2((T)1, (T)2, (T)5);

    vector3<T> vec(p1, p2);
    BOOST_CHECK_EQUAL(vec[0], (T)-1);
    BOOST_CHECK_EQUAL(vec[1], (T)0);
    BOOST_CHECK_EQUAL(vec[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_PointExplicit, T, test_types)
{
    point3<T> point((T)1, (T)2, (T)3);
    vector3<T> vec((point3<T>)point);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_CopyConstruct, T, test_types)
{
    vector3<T> vec;

    vec[0] = (T)2;
    vec[1] = (T)4;
    vec[2] = (T)8;

    vector3<T> vecCopy(vec);

    BOOST_CHECK_EQUAL(vecCopy[0], (T)2);
    BOOST_CHECK_EQUAL(vecCopy[1], (T)4);
    BOOST_CHECK_EQUAL(vecCopy[2], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_X, T, test_types)
{
    vector3<T> vec;

    vec.x() = (T)1;
    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Y, T, test_types)
{
    vector3<T> vec;

    vec.y() = (T)2;
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Z, T, test_types)
{
    vector3<T> vec;

    vec.z() = (T)3;
    BOOST_CHECK_EQUAL(vec[2], (T)3);
    BOOST_CHECK_EQUAL(vec.z(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetX, T, test_types)
{
    vector3<T> vec((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(vec.get_x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetY, T, test_types)
{
    vector3<T> vec((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(vec.get_y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetZ, T, test_types)
{
    vector3<T> vec((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(vec.get_z(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetX, T, test_types)
{
    vector3<T> vec;

    vec.set_x((T)1);
    BOOST_CHECK_EQUAL(vec[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetY, T, test_types)
{
    vector3<T> vec;

    vec.set_y((T)2);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetZ, T, test_types)
{
    vector3<T> vec;

    vec.set_z((T)3);
    BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Set, T, test_types)
{
    vector3<T> vec;
    vec.set((T)1, (T)2, (T)3);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetPtr, T, test_types)
{
    T data[3] = {(T)1, (T)2, (T)3};

    vector3<T> vec;
    vec.set(data);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Zero, T, test_types)
{
    vector3<T> vec;

    BOOST_CHECK_EQUAL(vec.zero()[0], (T)0);
    BOOST_CHECK_EQUAL(vec[1], (T)0);
    BOOST_CHECK_EQUAL(vec[2], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetData, T, test_types)
{
    T* data;
    vector3<T> vec((T)1, (T)2, (T)3);
    data = vec.get_data();

    BOOST_CHECK_EQUAL(data[0], (T)1);
    BOOST_CHECK_EQUAL(data[1], (T)2);
    BOOST_CHECK_EQUAL(data[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_BracketOp, T, test_types)
{
    vector3<T> ref((T)1, (T)2, (T)3);
    vector3<T> vec;

    vec[0] = (T)1;
    vec[1] = (T)2;
    vec[2] = (T)3;
    BOOST_CHECK(ref == vec);

    BOOST_CHECK_EQUAL(vec[0], (T)1);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Vec3Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpEqualityCompare, T, test_types)
{
    vector3<T> vec1((T)1, (T)2, (T)3);
    vector3<T> vec2(vec1);

    BOOST_CHECK(vec1 == vec2);
    BOOST_CHECK(!(vec1 != vec2));

    vec2 = vec1;
    vec2[0] = (T)21.10f;
    BOOST_CHECK(vec1 != vec2);
    BOOST_CHECK(!(vec1 == vec2));

    vec2 = vec1;
    vec2[1] = (T)21.10f;
    BOOST_CHECK(vec1 != vec2);
    BOOST_CHECK(!(vec1 == vec2));

    vec2 = vec1;
    vec2[2] = (T)21.10f;
    BOOST_CHECK(vec1 != vec2);
    BOOST_CHECK(!(vec1 == vec2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpIsEqual, T, float_types)
{
//    vector3<T> vec1 {1.0, 2.0, 3.0};
    vector3<T> vec1(1.0, 2.0, 3.0);
    vector3<T> vec2(vec1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(vec1, vec2, eps));
        BOOST_CHECK_CLOSE(vec1[0], vec2[0], eps);
        BOOST_CHECK_CLOSE(vec1[1], vec2[1], eps);
    }

    vec1.set(1.0f, 1.0f, 1.0f);
    for(unsigned elt=0; elt<3; elt++)
    {
        vec2 = vec1;
        vec2[elt] = (T)21.0;
        BOOST_CHECK(!is_equal(vec1, vec2, T(10.0)));
        BOOST_CHECK(!is_equal(vec1, vec2, T(19.9)));
        BOOST_CHECK( is_equal(vec1, vec2, T(20.1)));
        BOOST_CHECK( is_equal(vec1, vec2, T(22.0)));
    }

    vec1.set(T(3.141593), T(938.27231), T(2.718282) );
    vec2.set( T(3.14159),   T(938.272),  T(2.71828) );

    BOOST_CHECK(!is_equal(vec1, vec2, T(0)) );
    BOOST_CHECK(!is_equal(vec1, vec2, T(0.0001)) );
    BOOST_CHECK( is_equal(vec1, vec2, T(0.0005)) );
    BOOST_CHECK( is_equal(vec1, vec2, T(0.001)) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpPlusEq, T, test_types)
{
    vector3<T> vec1((T)1, (T)2, (T)3);
    vector3<T> vec2((T)2, (T)2, (T)2);

    vec1 += vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)3);
    BOOST_CHECK_EQUAL(vec1[1], (T)4);
    BOOST_CHECK_EQUAL(vec1[2], (T)5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpPlus, T, test_types)
{
    vector3<T> vec2((T)2, (T)2, (T)2);
    vector3<T> vec3((T)1, (T)2, (T)3);

    vector3<T> vec1 = vec3 + vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)3);
    BOOST_CHECK_EQUAL(vec1[1], (T)4);
    BOOST_CHECK_EQUAL(vec1[2], (T)5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMinusEq, T, test_types)
{
    vector3<T> vec1((T)1, (T)2, (T)3);
    vector3<T> vec2((T)2, (T)2, (T)2);

    vec1 -= vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)-1);
    BOOST_CHECK_EQUAL(vec1[1], (T)0);
    BOOST_CHECK_EQUAL(vec1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMinus, T, test_types)
{
    vector3<T> vec2((T)2, (T)2, (T)2);
    vector3<T> vec3((T)1, (T)2, (T)3);

    vector3<T> vec1 = vec3 - vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)-1);
    BOOST_CHECK_EQUAL(vec1[1], (T)0);
    BOOST_CHECK_EQUAL(vec1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpNegate, T, test_types)
{
    vector3<T> vec2((T)2, (T)-3, (T)5);

    vector3<T> vec1 = -vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)-2);
    BOOST_CHECK_EQUAL(vec1[1], (T)3);
    BOOST_CHECK_EQUAL(vec1[2], (T)-5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMultScalarEq, T, test_types)
{
    vector3<T> vec((T)1, (T)2, (T)3);

    vec *= (T)4;
    BOOST_CHECK_EQUAL(vec[0], (T)4);
    BOOST_CHECK_EQUAL(vec[1], (T)8);
    BOOST_CHECK_EQUAL(vec[2], (T)12);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMultScalar, T, test_types)
{
    vector3<T> vec2((T)1, (T)2, (T)3);

    vector3<T> vec1 = vec2 * (T)4.0;
    BOOST_CHECK_EQUAL(vec1[0], (T)4);
    BOOST_CHECK_EQUAL(vec1[1], (T)8);
    BOOST_CHECK_EQUAL(vec1[2], (T)12);

    vec1 = (T)4.0 * vec2;
    BOOST_CHECK_EQUAL(vec1[0], (T)4);
    BOOST_CHECK_EQUAL(vec1[1], (T)8);
    BOOST_CHECK_EQUAL(vec1[2], (T)12);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpDivScalarEq, T, test_types)
{
    vector3<T> vec((T)12, (T)8, (T)4);

    vec /= (T)4;
    BOOST_CHECK_EQUAL(vec[0], (T)3);
    BOOST_CHECK_EQUAL(vec[1], (T)2);
    BOOST_CHECK_EQUAL(vec[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpDivScalar, T, test_types)
{
    vector3<T> vec2((T)12, (T)8, (T)4);

    vector3<T> vec1 = vec2 / (T)4.0;
    BOOST_CHECK_EQUAL(vec1[0], (T)3);
    BOOST_CHECK_EQUAL(vec1[1], (T)2);
    BOOST_CHECK_EQUAL(vec1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMiddle, T, float_types)
{
    vector3<T> vec1;
    vector3<T> vec2((T)1, (T)2, (T)3);
    vector3<T> vec3((T)3, (T)4, (T)5);

    middle(vec1, vec2, vec3);
    BOOST_CHECK_EQUAL(vec1[0], (T)2);
    BOOST_CHECK_EQUAL(vec1[1], (T)3);
    BOOST_CHECK_EQUAL(vec1[2], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpDot, T, float_types)
{
    vector3<T> v1(1, 0, 0);
    vector3<T> v2(0, 1, 0);
    vector3<T> v3(0, 0, 1);

    BOOST_CHECK_CLOSE(T(0), dot(v1,v2), T(SMALL));

    v1.set(13.45f, -7.8f, 0.056f);
    v2.set(0.777f, 5.333f, 12.21f);
    v3.set(3.4f, -1.6f, 0.23f);

    T ans = -30.463f;
    BOOST_CHECK_CLOSE(dot(v1,v2), ans, T(0.001));
    BOOST_CHECK_CLOSE(dot(v2,v1), ans, T(0.001));
    ans = -3.0827f;
    BOOST_CHECK_CLOSE(dot(v2,v3), ans, T(0.001));
    BOOST_CHECK_CLOSE(dot(v3,v2), ans, T(0.001));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpLength, T, float_types)
{
    vector3<T> v1(1, 0, 0);
    vector3<T> v2(0, 1, 0);
    vector3<T> v3(0, 0, 1);
    T len, ans;

    BOOST_CHECK_CLOSE(length(v1), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length(v2), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length(v3), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length_sq(v1), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length_sq(v2), T(1.0f), T(SMALL));
    BOOST_CHECK_CLOSE(length_sq(v3), T(1.0f), T(SMALL));

    v1.set(2.0f, 4.0f, 5.0f);
    v2.set(12.0f, -2.0f, -4.0f);

    ans = 4.0f + 16.0f + 25.0f;
    len = length_sq(v1);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));

    ans = sqrt(ans);
    len = length(v1);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));

    ans = 144.0f + 4.0f + 16.0f;
    len = length_sq(v2);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));

    ans = sqrt(ans);
    len = length(v2);
    BOOST_CHECK_CLOSE(len, ans, T(SMALL));
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(Vector3_OpAngle, T, float_types, ETHAN<T>)
{
/// [vector3 angle]
    namespace mu = maral::units;

    point3<T> p1(1, 1, 0);
    point3<T> p2(1, 0, 0);
    point3<T> p3(2, 0, 1);
    vector3<T> v1(p2, p1);
    vector3<T> v2(p2, p3);

    auto ang = mu::radians( angle(v1, v2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(90.0), SMALL);

    p1.set(2, 0, 0);
    v1 = vector3<T>(p2, p1);
    ang = mu::radians( angle(v1, v2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(45.0), SMALL);

    p1.set(0, 0, 0);
    v1 = vector3<T>(p2, p1);
    ang = mu::radians( angle(v1, v2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(135.0), SMALL);

    v1.set(0, 0, 0);
    ang = mu::radians( angle(v1, v2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(0.0), SMALL);

    v1.set(2, -3, 4);
    v2.set(5, 2, 1);
    ang = mu::radians( angle(v1, v2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(74.26280), SMALL);

    point3<T> C1;
    C1.set(&ETHAN<T>::ethan[0]);
    point3<T> C2;
    C2.set(&ETHAN<T>::ethan[3]);
    point3<T> H1;
    H1.set(&ETHAN<T>::ethan[6]);
    v1 = vector3<T>(C1, C2);
    v2 = vector3<T>(C1, H1);
    ang = mu::radians( angle(v1, v2) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(109.640722), SMALL);
    ang = mu::radians( angle(v2, v1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(109.640722), SMALL);
/// [vector3 angle]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpNormalize, T, float_types)
{
    vector3<T> vec1(2, 4, 5);
    vector3<T> vec2(vec1);

    normalize(vec1);
    vector3<T> temp = (vec1*length(vec2) );
    BOOST_CHECK(is_equal(vec2, temp, T(SMALL) ) );
    vec1.set(12, -2, -4);
    vec2 = vec1;
    normalize(vec1);
    BOOST_CHECK(is_equal(vec2, vector3<T>(vec1*length(vec2) ), T(SMALL) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpIsNormalized, T, float_types)
{
    vector3<T> v1(1, 0, 0);
    vector3<T> v2(0, 1, 0);
    vector3<T> v3(0, 0, 1);
    vector3<T> v4(2, 4, 5);

    BOOST_CHECK( is_normalized(v1) );
    BOOST_CHECK( is_normalized(v2) );
    BOOST_CHECK( is_normalized(v3) );
    BOOST_CHECK(!is_normalized(v4) );

    v2 = v1;

    // epsilon tolerance
    for (T eps=0; eps<10; eps+=0.5)
    {
        BOOST_CHECK(is_normalized(v1, eps));
    }

    v2.set(21, 0, 0);
    BOOST_CHECK( ! is_normalized(v2, T(15.0f * 15.0f) ) );
    BOOST_CHECK( ! is_normalized(v2, T(19.9f * 19.9f) ) );
    BOOST_CHECK( is_normalized(v2, T(21.0f * 21.0f - 0.9f) ) );
    BOOST_CHECK( is_normalized(v2, T(21.0f * 21.0f + 0.9f) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpReflect, T, float_types)
{
    vector3<T> v1(1,1,1);
    vector3<T> v2(3,1,2);
    vector3<T> v3(4,5,1);
    vector3<T> n1(1,0,0); // normal of the surface/plane
    vector3<T> n2(0,1,0);
    vector3<T> n3(0,0,1);
    vector3<T> ex1(-1,1,1); // flipped about the surface
    vector3<T> ex2(3,-1,2);
    vector3<T> ex3(4,5,-1);
    vector3<T> res;

    const T eps = 0.001f;
    reflect(res, v1, n1);
    BOOST_CHECK(is_equal(res, ex1, eps));
    reflect(res, v2, n2);
    BOOST_CHECK(is_equal(res, ex2, eps));
    reflect(res, v3, n3);
    BOOST_CHECK(is_equal(res, ex3, eps));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpLerp, T, float_types)
{
    const T eps = 0.0001f;
    vector3<T> q1( 2, 3, 4 ), q2( 9.01f, 8.4f, 7.1f );
    vector3<T> expected_result1(q1), res1;
    vector3<T> expected_result2(q2), res2;

    lerp( res1, T(0.0), q1, q2 );
    lerp( res2, T(1.0), q1, q2 );
    BOOST_CHECK(is_equal(expected_result1, res1, eps) );
    BOOST_CHECK(is_equal(expected_result2, res2, eps) );

    // test interpolated values...
    vector3<T> q3(0, 0, 0), q4(1, 1, 1);
    vector3<T> expected_result3(0.35f, 0.35f, 0.35f), res3;
    vector3<T> expected_result4(0.69f, 0.69f, 0.69f), res4;

    lerp(res3, T(0.35), q3, q4);
    lerp(res4, T(0.69), q3, q4);
    BOOST_CHECK(is_equal(expected_result3, res3, eps) );
    BOOST_CHECK(is_equal(expected_result4, res4, eps) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpCross, T, float_types)
{
    vector3<T> v1(1,0,0);
    vector3<T> v2(0,1,0);
    vector3<T> v3(0,0,1);
    vector3<T> r;

    cross(r, v1, v2);
    BOOST_CHECK(is_equal(r, v3, T(0.001f) ) );
    BOOST_CHECK(is_equal(cross(v1, v2), v3, T(0.001f) ) );
    cross(r, v2, v1);
    BOOST_CHECK(is_equal(r, vector3<T>(-v3), T(0.001f) ) );
    BOOST_CHECK(is_equal(cross(v2, v1), vector3<T>(-v3), T(0.001f) ) );

    v1.set(13.45f, -7.8f, 0.056f);
    v2.set(0.777f, 5.333f, 12.21f);
    v3.set(-95.537f, -164.181f, 77.789f);

    cross(r, v1, v2);
    BOOST_CHECK(is_equal(r, v3, T(0.001f) ) );
    BOOST_CHECK(is_equal(cross(v1, v2), v3, T(0.001f) ) );
    cross(r, v2, v1);
    BOOST_CHECK(is_equal(r, vector3<T>(-v3), T(0.001f) ) );
    BOOST_CHECK(is_equal(cross(v2, v1), vector3<T>(-v3), T(0.001f) ) );
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(Vector3_OpTorsionAngle, T, float_types, ETHAN<T>)
{
/// [vector3 torsion angle]
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

    vector3<T> C1H1(C1, H1);
    vector3<T> C1C2(C1, C2);
    vector3<T> C2C1(C2, C1);
    vector3<T> C2H4(C2, H4);

    auto ang = mu::radians( torsion_angle(C1H1, C1C2, C2H4) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-60.0), T(0.001));
    ang = mu::radians( torsion_angle(C2H4, C2C1, C1H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-60.0), T(0.001));

    vector3<T> C2H5(C2, H5);
    ang = mu::radians( torsion_angle(C1H1, C1C2, C2H5) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(60.0), T(0.001));
    ang = mu::radians( torsion_angle(C2H5, C2C1, C1H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(60.0), T(0.001));

    vector3<T> C2H6(C2, H6);
    ang = mu::radians( torsion_angle(C1H1, C1C2, C2H6) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-180.0), T(0.001));
    ang = mu::radians( torsion_angle(C2H6, C2C1, C1H1) );
    BOOST_CHECK_CLOSE(mu::to_degrees(ang).value(), T(-180.0), T(0.001));
/// [vector3 torsion angle]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Linear_Algebra_Identities, T, float_types)
{
    vector3<T> v1(1,2,3);
    vector3<T> v2(-1,0,1);
    vector3<T> v3(2,4,-5);
    vector3<T> r;
    vector3<T> zero;

    BOOST_CHECK(v1+v2 == v2+v1);
    BOOST_CHECK(v1-v2 == v1+(-v2) );
    BOOST_CHECK((v1+v2)+v3 == v1+(v2+v3));
    BOOST_CHECK(v1*T(3) == T(3)*v1);
    BOOST_CHECK(T(3)*(v1+v2) == (T(3)*v1) + (T(3)*v2));
    BOOST_CHECK_CLOSE(length(v1*T(-3)), length(v1)*abs(T(-3)), SMALL);
//    BOOST_CHECK((length(v1)*length(v1)) + (length(v2)*length(v2)) == length(v1+v2) * length(v1+v2));
    BOOST_CHECK(length(v1)+length(v2) >= length(v1+v2));
    BOOST_CHECK(dot(v1, v2) == dot(v2, v1));
    BOOST_CHECK_CLOSE(length(v1), sqrt(dot(v1, v1)), SMALL);
    BOOST_CHECK(T(3)*dot(v1, v2) == dot(T(3)*v1, v2));
    BOOST_CHECK(T(3)*dot(v1, v2) == dot(v1, T(3)*v2));
    BOOST_CHECK(dot(v1, v2+v3) == dot(v1, v2) + dot(v1, v3));
    BOOST_CHECK(cross(r, v1, v1) == zero.zero());
    BOOST_CHECK(cross(v1, v2) == -(cross(v2, v1)));
    BOOST_CHECK(cross(v1, v2) == cross(-v1, -v2));
    BOOST_CHECK(T(3)*cross(v1, v2) == cross(v1*T(3), v2));
    BOOST_CHECK(T(3)*cross(v1, v2) == cross(v1, v2*T(3)));
    BOOST_CHECK(cross(v1, v2+v3) == cross(v1, v2) + cross(v1, v3));
    BOOST_CHECK(dot(v1, cross(v1, v2)) == T(0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Inserter, T, float_types)
{
    output_test_stream cout(
        PATTERNS_FOLDER"pntvec3.txt",
        !utrc::save_pattern() );
/// [vector3 inserter]
    vector3<T> vec( T(3.141593), T(938.27231), T(2.718282) );

    cout << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::fixed << std::setprecision(3)
         << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('|') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(7)  << delimiters('[', ']')
         << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(15) << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << spaces << delimiters('|') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << horizontal << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << separator(',') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('{', '}') << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << nospaces << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << setew(0) << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << std::setw(25) << vec << std::endl << std::endl;
    BOOST_CHECK( cout.match_pattern() );

    cout << delimiters('\0') << vec << std::endl;
    BOOST_CHECK( cout.match_pattern() );
/// [vector3 inserter]
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Extractor, T, float_types)
{
    std::ifstream cin(PATTERNS_FOLDER"pntvec3.txt");
/// [vector3 extractor]
    vector3<T> vec( T(3.141593), T(938.27231), T(2.718282) );
    vector3<T> ext;

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('[', ']') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('|') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> horizontal >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> separator(',') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('{', '}') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );

    cin >> delimiters('\0') >> ext.zero();
    BOOST_CHECK( is_equal(vec, ext) );
/// [vector3 extractor]
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
