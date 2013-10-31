// $Id$
//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE MTL
#ifdef _WIN32
    #define BOOST_TEST_ALTERNATIVE_INIT_API
#else
    #define BOOST_TEST_DYN_LINK
#endif    //_WIN32
//#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/unit_test.hpp>
//#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include <mtl/mtl.hpp>

#include "mtl_data.hpp"

using boost::test_tools::output_test_stream;
using namespace maral::mtl;

typedef boost::mpl::list<int,float,double,long double> test_types;
typedef boost::mpl::list<float,double,long double> float_types;

BOOST_AUTO_TEST_SUITE( Points )

BOOST_AUTO_TEST_SUITE( Pnt2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(point2_Constructors, T, test_types)
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
    point2<T> pnt;

    pnt[0] = (T)1;
    BOOST_CHECK_EQUAL(pnt.data_[0], (T)1);
    pnt[1] = (T)2;
    BOOST_CHECK_EQUAL(pnt.data_[1], (T)2);

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

    BOOST_CHECK_EQUAL(distance_sq(point1, point2), T(8));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpAngle, T, float_types)
{
    point2<T> pnt1(1, 2);
    point2<T> pnt2(1, 1);
    point2<T> pnt3(2, 1);

    BOOST_CHECK_CLOSE(angle(pnt1, pnt2, pnt3), T(90.0), SMALL);
    pnt1.set(2, 2);
    BOOST_CHECK_CLOSE(angle(pnt1, pnt2, pnt3), T(45.0), SMALL);
    pnt1.set(1, 1);
    BOOST_CHECK_CLOSE(angle(pnt1, pnt2, pnt3), T(0.0), SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Output, T, test_types)
{
    output_test_stream output;
    point2<T> pnt((T)1, (T)2);
    output << pnt;
    BOOST_CHECK(!output.is_empty(false) );
    BOOST_CHECK( output.check_length(5, false) );
    BOOST_CHECK( output.is_equal("[1,2]") );
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
    point3<T> pnt;

    pnt[0] = (T)1;
    BOOST_CHECK_EQUAL(pnt.data_[0], (T)1);
    pnt[1] = (T)2;
    BOOST_CHECK_EQUAL(pnt.data_[1], (T)2);
    pnt[2] = (T)3;
    BOOST_CHECK_EQUAL(pnt.data_[2], (T)3);

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
    point3<T> point1(1.0, 2.0, 3.0);
    point3<T> point2(point1);
    T eps(0.0);

    for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
    {
        BOOST_CHECK(is_equal(point1, point2, eps));
        BOOST_CHECK_CLOSE(point1[0], point2[0], eps);
        BOOST_CHECK_CLOSE(point1[1], point2[1], eps);
        BOOST_CHECK_CLOSE(point1[2], point2[2], eps);
    }

    point1.set(1.0f, 1.0f, 1.0f);
    for(unsigned elt=0; elt<3; elt++)
    {
        point2 = point1;
        point2[elt] = (T)21.0;
        BOOST_CHECK(!is_equal(point1, point2, T(10.0)));
        BOOST_CHECK(!is_equal(point1, point2, T(19.9)));
        BOOST_CHECK( is_equal(point1, point2, T(20.1)));
        BOOST_CHECK( is_equal(point1, point2, T(22.0)));
    }
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

    BOOST_CHECK_EQUAL(distance_sq(pnt1, pnt2), T(12));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpAngle, T, float_types)
{
    point3<T> pnt1(1, 1, 0);
    point3<T> pnt2(1, 0, 0);
    point3<T> pnt3(2, 0, 1);

    BOOST_CHECK_CLOSE(angle(pnt1, pnt2, pnt3), T(90.0), SMALL);
    pnt1.set(2, 0, 0);
    BOOST_CHECK_CLOSE(angle(pnt1, pnt2, pnt3), T(45.0), SMALL);
    pnt1.set(0, 0, 0);
    BOOST_CHECK_CLOSE(angle(pnt1, pnt2, pnt3), T(135.0), SMALL);

    DEFINE_ETHYL;
    point3<T> C1;
    C1.set(&ETHYL[0]);
    point3<T> C2;
    C2.set(&ETHYL[3]);
    point3<T> H1;
    H1.set(&ETHYL[6]);
    BOOST_CHECK_CLOSE(angle(C2, C1, H1), 109.640722, SMALL);
    BOOST_CHECK_CLOSE(angle(H1, C1, C2), 109.640722, SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpTorsionAngle, T, float_types)
{
    DEFINE_ETHYL;
    point3<T> C1;
    C1.set(&ETHYL[0]);
    point3<T> C2;
    C2.set(&ETHYL[3]);
    point3<T> H1;
    H1.set(&ETHYL[6]);
    point3<T> H4;
    H4.set(&ETHYL[15]);
    point3<T> H5;
    H5.set(&ETHYL[18]);
    point3<T> H6;
    H6.set(&ETHYL[21]);

    BOOST_CHECK_CLOSE(torsion_angle(H1, C1, C2, H4), T(-60.0), T(0.001));
    BOOST_CHECK_CLOSE(torsion_angle(H4, C2, C1, H1), T(-60.0), T(0.001));
    BOOST_CHECK_CLOSE(torsion_angle(H1, C1, C2, H5), T(60.0), T(0.001));
    BOOST_CHECK_CLOSE(torsion_angle(H5, C2, C1, H1), T(60.0), T(0.001));
    BOOST_CHECK_CLOSE(torsion_angle(H1, C1, C2, H6), T(-180.0), T(0.001));
    BOOST_CHECK_CLOSE(torsion_angle(H6, C2, C1, H1), T(-180.0), T(0.001));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Output, T, test_types)
{
    output_test_stream output;
    point3<T> pnt((T)1, (T)2, (T)3);
    output << pnt;
    BOOST_CHECK(!output.is_empty(false) );
    BOOST_CHECK( output.check_length(7, false) );
    BOOST_CHECK( output.is_equal("[1,2,3]") );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
