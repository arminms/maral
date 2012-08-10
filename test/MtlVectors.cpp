#define BOOST_TEST_MODULE MTL
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/unit_test.hpp>
//#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include <Magma/Magma.hpp>
#include "MtlData.hpp"
using boost::test_tools::output_test_stream;
using namespace Magma::Mtl;

typedef boost::mpl::list<int,float,double,long double> test_types;
typedef boost::mpl::list<float,double,long double> float_types;

BOOST_AUTO_TEST_SUITE( Vectors )

BOOST_AUTO_TEST_SUITE( Vec2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Creation, T, test_types)
{
	Vector2<T> vec;

	BOOST_CHECK_EQUAL(vec[0], (T)0);
	BOOST_CHECK_EQUAL(vec[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Constructors, T, test_types)
{
	Vector2<T> vec((T)1, (T)2);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_ConstructFromPoints, T, test_types)
{
	Point2<T> point1((T)2, (T)2);
	Point2<T> point2((T)1, (T)2);

	Vector2<T> vec(point1, point2);
	BOOST_CHECK_EQUAL(vec[0], (T)-1);
	BOOST_CHECK_EQUAL(vec[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_PointExplicit, T, test_types)
{
	Point2<T> point((T)1, (T)2);
	Vector2<T> vec((Point2<T>)point);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_CopyConstruct, T, test_types)
{
	Vector2<T> vec;

	vec[0] = (T)2;
	vec[1] = (T)4;

	Vector2<T> vecCopy(vec);

	BOOST_CHECK_EQUAL(vecCopy[0], (T)2);
	BOOST_CHECK_EQUAL(vecCopy[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_X, T, test_types)
{
	Vector2<T> vec;

	vec.x() = (T)1;
	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Y, T, test_types)
{
	Vector2<T> vec;

	vec.y() = (T)2;
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_GetX, T, test_types)
{
	Vector2<T> vec((T)1, (T)2);

	BOOST_CHECK_EQUAL(vec.getX(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_GetY, T, test_types)
{
	Vector2<T> vec((T)1, (T)2);

	BOOST_CHECK_EQUAL(vec.getY(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_SetX, T, test_types)
{
	Vector2<T> vec;

	vec.setX((T)1);
	BOOST_CHECK_EQUAL(vec[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_SetY, T, test_types)
{
	Vector2<T> vec;

	vec.setY((T)2);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Set, T, test_types)
{
	Vector2<T> vec;
	vec.set((T)1, (T)2);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_SetPtr, T, test_types)
{
	T data[2] = {(T)1, (T)2};

	Vector2<T> vec;
	vec.set(data);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_GetData, T, test_types)
{
	T* data;
	Vector2<T> vec((T)1, (T)2);
	data = vec.getData();

	BOOST_CHECK_EQUAL(data[0], (T)1);
	BOOST_CHECK_EQUAL(data[1], (T)2);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Vec2Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpEqualityCompare, T, test_types)
{
	Vector2<T> vec1((T)1, (T)2);
	Vector2<T> vec2(vec1);

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
	Vector2<T> vec1(1.0, 2.0);
	Vector2<T> vec2(vec1);
	T eps(0.0);

	for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
	{
		BOOST_CHECK(isEqual(vec1, vec2, eps));
		BOOST_CHECK_CLOSE(vec1[0], vec2[0], eps);
		BOOST_CHECK_CLOSE(vec1[1], vec2[1], eps);
	}

	vec1.set(1.0, 1.0);
	for(unsigned elt=0; elt<2; elt++)
	{
		vec2 = vec1;
		vec2[elt] = (T)21.0;
		BOOST_CHECK(!isEqual(vec1, vec2, T(10.0)));
		BOOST_CHECK(!isEqual(vec1, vec2, T(19.9)));
		BOOST_CHECK( isEqual(vec1, vec2, T(20.1)));
		BOOST_CHECK( isEqual(vec1, vec2, T(22.0)));
	}
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpPlusEq, T, test_types)
{
	Vector2<T> vec1((T)1, (T)2);
	Vector2<T> vec2((T)2, (T)2);

	vec1 += vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpPlus, T, test_types)
{
	Vector2<T> vec2((T)2, (T)2);
	Vector2<T> vec3((T)1, (T)2);

	Vector2<T> vec1 = vec3 + vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMinusEq, T, test_types)
{
	Vector2<T> vec1((T)1, (T)2);
	Vector2<T> vec2((T)2, (T)2);

	vec1 -= vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)-1);
	BOOST_CHECK_EQUAL(vec1[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMinus, T, test_types)
{
	Vector2<T> vec2((T)2, (T)2);
	Vector2<T> vec3((T)1, (T)2);

	Vector2<T> vec1 = vec3 - vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)-1);
	BOOST_CHECK_EQUAL(vec1[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpNegate, T, test_types)
{
	Vector2<T> vec2((T)2, (T)-3);

	Vector2<T> vec1 = -vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)-2);
	BOOST_CHECK_EQUAL(vec1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMultScalarEq, T, test_types)
{
	Vector2<T> vec((T)1, (T)2);

	vec *= (T)4;
	BOOST_CHECK_EQUAL(vec[0], (T)4);
	BOOST_CHECK_EQUAL(vec[1], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMultScalar, T, test_types)
{
	Vector2<T> vec2((T)1, (T)2);

	Vector2<T> vec1 = vec2 * (T)4.0;
	BOOST_CHECK_EQUAL(vec1[0], (T)4);
	BOOST_CHECK_EQUAL(vec1[1], (T)8);

	vec1 = (T)4.0 * vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)4);
	BOOST_CHECK_EQUAL(vec1[1], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDivScalarEq, T, test_types)
{
	Vector2<T> vec((T)12, (T)8);

	vec /= (T)4;
	BOOST_CHECK_EQUAL(vec[0], (T)3);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDivScalar, T, test_types)
{
	Vector2<T> vec2((T)12, (T)8);

	Vector2<T> vec1 = vec2 / (T)4.0;
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpAddScaled, T, test_types)
{
	Vector2<T> vec1((T)1, (T)2);
	Vector2<T> vec2((T)2, (T)2);

	addScaled((T)4, vec1, vec2);
	BOOST_CHECK_EQUAL(vec1[0], (T)9);
	BOOST_CHECK_EQUAL(vec1[1], (T)10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpSumScaled, T, test_types)
{
	Vector2<T> vec2((T)1, (T)2);
	Vector2<T> vec3((T)2, (T)2);

	Vector2<T> vec1 = sumScaled((T)4, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)9);
	BOOST_CHECK_EQUAL(vec1[1], (T)10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMaximize, T, test_types)
{
	Vector2<T> vec1;
	Vector2<T> vec2((T)1, (T)4);
	Vector2<T> vec3((T)3, (T)2);

	maximize(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMinimize, T, test_types)
{
	Vector2<T> vec1;
	Vector2<T> vec2((T)1, (T)4);
	Vector2<T> vec3((T)3, (T)2);

	minimize(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)1);
	BOOST_CHECK_EQUAL(vec1[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpMiddle, T, float_types)
{
	Vector2<T> vec1;
	Vector2<T> vec2((T)1, (T)2);
	Vector2<T> vec3((T)3, (T)4);

	middle(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)2);
	BOOST_CHECK_EQUAL(vec1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDot, T, float_types)
{
	Vector2<T> v1(1, 0);
	Vector2<T> v2(0, 1);

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
	Vector2<T> v1(1, 0);
	Vector2<T> v2(0, 1);
	T len, ans;

	BOOST_CHECK_CLOSE(length(v1), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(length(v2), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(lengthSq(v1), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(lengthSq(v2), T(1.0f), T(SMALL));

	v1.set(2.0f, 4.0f);
	v2.set(12.0f, -2.0f);

	ans = 4.0f + 16.0f;
	len = lengthSq(v1);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));

	ans = sqrt(ans);
	len = length(v1);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));

	ans = 144.0f + 4.0f;
	len = lengthSq(v2);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));

	ans = sqrt(ans);
	len = length(v2);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpAngle, T, float_types)
{
	Vector2<T> vec1(1, 0);
	Vector2<T> vec2(0, 1);

	BOOST_CHECK_CLOSE(angle(vec1, vec2), 90.0f, SMALL);
	vec2.set(1, 1);
	BOOST_CHECK_CLOSE(angle(vec1, vec2), 45.0f, SMALL);
	vec1.set(3, 0);
	vec2.set(3, 3);
	BOOST_CHECK_CLOSE(angle(vec1, vec2), 45.0f, SMALL);
	vec2.set(0, 0);
	BOOST_CHECK_CLOSE(angle(vec1, vec2), 0.0f, SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpNormalize, T, float_types)
{
	Vector2<T> vec1(2, 4);
	Vector2<T> vec2(vec1);

	normalize(vec1);
	Vector2<T> temp = (vec1*length(vec2) );
	BOOST_CHECK(isEqual(vec2, temp, T(SMALL) ) );
	vec1.set(12, -2);
	vec2 = vec1;
	normalize(vec1);
	BOOST_CHECK(isEqual(vec2, Vector2<T>(vec1*length(vec2) ), T(SMALL) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpIsNormalized, T, float_types)
{
	Vector2<T> v1(1, 0);
	Vector2<T> v2(0, 1);
	Vector2<T> v3(2, 4);

	BOOST_CHECK(isNormalized(v1) );
	BOOST_CHECK(isNormalized(v2) );
	BOOST_CHECK(! isNormalized(v3) );

	v2 = v1;

	// epsilon tolerance
	for (T eps=0; eps<10; eps+=0.5)
	{
		BOOST_CHECK(isNormalized(v1, eps));
	}

	v2.set(21,0);
	BOOST_CHECK( ! isNormalized(v2, T(15.0f * 15.0f) ) );
	BOOST_CHECK( ! isNormalized(v2, T(19.9f * 19.9f) ) );
	BOOST_CHECK( isNormalized(v2, T(21.0f * 21.0f - 0.9f) ) );
	BOOST_CHECK( isNormalized(v2, T(21.0f * 21.0f + 0.9f) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpReflect, T, test_types)
{
	Vector2<T> v(1, -1);
	Vector2<T> n(0, 1);
	Vector2<T> r;
	Vector2<T> ans(1, 1);

	reflect(r, v, n);
	BOOST_CHECK(r == ans);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpLerp, T, float_types)
{
	Vector2<T> v1(1, 0);
	Vector2<T> v2(0, 1);
	Vector2<T> v3(2, 4);

	const float eps = 0.0001f;
	Vector2<T> q1(2, 3), q2(9.01f, 8.4f);
	Vector2<T> expected_result1(q1), res1;
	Vector2<T> expected_result2(q2), res2;

	lerp(res1, T(0.0f), q1, q2);
	lerp(res2, T(1.0f), q1, q2);
	BOOST_CHECK_CLOSE(expected_result1[0], res1[0], eps);
	BOOST_CHECK_CLOSE(expected_result1[1], res1[1], eps);
	BOOST_CHECK_CLOSE(expected_result2[0], res2[0], eps);
	BOOST_CHECK_CLOSE(expected_result2[1], res2[1], eps);

	// test interpolated values...
	Vector2<T> q3(0, 0), q4(1, 1);
	Vector2<T> expected_result3(0.35f, 0.35f), res3;
	Vector2<T> expected_result4(0.69f, 0.69f), res4;

	lerp(res3, T(0.35f), q3, q4);
	lerp(res4, T(0.69f), q3, q4);
	BOOST_CHECK_CLOSE(expected_result3[0], res3[0], eps);
	BOOST_CHECK_CLOSE(expected_result3[1], res3[1], eps);
	BOOST_CHECK_CLOSE(expected_result4[0], res4[0], eps);
	BOOST_CHECK_CLOSE(expected_result4[1], res4[1], eps);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_Output, T, test_types)
{
	output_test_stream output;
	Vector2<T> vec((T)1, (T)2);
	output << vec;
	BOOST_CHECK(!output.is_empty(false) );
	BOOST_CHECK( output.check_length(5, false) );
	BOOST_CHECK( output.is_equal("(1,2)") );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Vec3 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Creation, T, test_types)
{
	Vector3<T> vec;

	BOOST_CHECK_EQUAL(vec[0], (T)0);
	BOOST_CHECK_EQUAL(vec[1], (T)0);
	BOOST_CHECK_EQUAL(vec[2], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Constructors, T, test_types)
{
	Vector3<T> vec((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_ConstructFromPoints, T, test_types)
{
	Point3<T> point1((T)2, (T)2, (T)4);
	Point3<T> Point3((T)1, (T)2, (T)5);

	Vector3<T> vec(point1, Point3);
	BOOST_CHECK_EQUAL(vec[0], (T)-1);
	BOOST_CHECK_EQUAL(vec[1], (T)0);
	BOOST_CHECK_EQUAL(vec[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_PointExplicit, T, test_types)
{
	Point3<T> point((T)1, (T)2, (T)3);
	Vector3<T> vec((Point3<T>)point);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_CopyConstruct, T, test_types)
{
	Vector3<T> vec;

	vec[0] = (T)2;
	vec[1] = (T)4;
	vec[2] = (T)8;

	Vector3<T> vecCopy(vec);

	BOOST_CHECK_EQUAL(vecCopy[0], (T)2);
	BOOST_CHECK_EQUAL(vecCopy[1], (T)4);
	BOOST_CHECK_EQUAL(vecCopy[2], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_X, T, test_types)
{
	Vector3<T> vec;

	vec.x() = (T)1;
	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Y, T, test_types)
{
	Vector3<T> vec;

	vec.y() = (T)2;
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Z, T, test_types)
{
	Vector3<T> vec;

	vec.z() = (T)3;
	BOOST_CHECK_EQUAL(vec[2], (T)3);
	BOOST_CHECK_EQUAL(vec.z(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetX, T, test_types)
{
	Vector3<T> vec((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(vec.getX(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetY, T, test_types)
{
	Vector3<T> vec((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(vec.getY(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetZ, T, test_types)
{
	Vector3<T> vec((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(vec.getZ(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetX, T, test_types)
{
	Vector3<T> vec;

	vec.setX((T)1);
	BOOST_CHECK_EQUAL(vec[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetY, T, test_types)
{
	Vector3<T> vec;

	vec.setY((T)2);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetZ, T, test_types)
{
	Vector3<T> vec;

	vec.setZ((T)3);
	BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Set, T, test_types)
{
	Vector3<T> vec;
	vec.set((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_SetPtr, T, test_types)
{
	T data[3] = {(T)1, (T)2, (T)3};

	Vector3<T> vec;
	vec.set(data);

	BOOST_CHECK_EQUAL(vec[0], (T)1);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_GetData, T, test_types)
{
	T* data;
	Vector3<T> vec((T)1, (T)2, (T)3);
	data = vec.getData();

	BOOST_CHECK_EQUAL(data[0], (T)1);
	BOOST_CHECK_EQUAL(data[1], (T)2);
	BOOST_CHECK_EQUAL(data[2], (T)3);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Vec3Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpEqualityCompare, T, test_types)
{
	Vector3<T> vec1((T)1, (T)2, (T)3);
	Vector3<T> vec2(vec1);

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
	Vector3<T> vec1(1.0, 2.0, 3.0);
	Vector3<T> vec2(vec1);
	T eps(0.0);

	for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
	{
		BOOST_CHECK(isEqual(vec1, vec2, eps));
		BOOST_CHECK_CLOSE(vec1[0], vec2[0], eps);
		BOOST_CHECK_CLOSE(vec1[1], vec2[1], eps);
	}

	vec1.set(1.0f, 1.0f, 1.0f);
	for(unsigned elt=0; elt<3; elt++)
	{
		vec2 = vec1;
		vec2[elt] = (T)21.0;
		BOOST_CHECK(!isEqual(vec1, vec2, T(10.0)));
		BOOST_CHECK(!isEqual(vec1, vec2, T(19.9)));
		BOOST_CHECK( isEqual(vec1, vec2, T(20.1)));
		BOOST_CHECK( isEqual(vec1, vec2, T(22.0)));
	}
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpPlusEq, T, test_types)
{
	Vector3<T> vec1((T)1, (T)2, (T)3);
	Vector3<T> vec2((T)2, (T)2, (T)2);

	vec1 += vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)4);
	BOOST_CHECK_EQUAL(vec1[2], (T)5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpPlus, T, test_types)
{
	Vector3<T> vec2((T)2, (T)2, (T)2);
	Vector3<T> vec3((T)1, (T)2, (T)3);

	Vector3<T> vec1 = vec3 + vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)4);
	BOOST_CHECK_EQUAL(vec1[2], (T)5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMinusEq, T, test_types)
{
	Vector3<T> vec1((T)1, (T)2, (T)3);
	Vector3<T> vec2((T)2, (T)2, (T)2);

	vec1 -= vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)-1);
	BOOST_CHECK_EQUAL(vec1[1], (T)0);
	BOOST_CHECK_EQUAL(vec1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMinus, T, test_types)
{
	Vector3<T> vec2((T)2, (T)2, (T)2);
	Vector3<T> vec3((T)1, (T)2, (T)3);

	Vector3<T> vec1 = vec3 - vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)-1);
	BOOST_CHECK_EQUAL(vec1[1], (T)0);
	BOOST_CHECK_EQUAL(vec1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpNegate, T, test_types)
{
	Vector3<T> vec2((T)2, (T)-3, (T)5);

	Vector3<T> vec1 = -vec2;
	BOOST_CHECK_EQUAL(vec1[0], (T)-2);
	BOOST_CHECK_EQUAL(vec1[1], (T)3);
	BOOST_CHECK_EQUAL(vec1[2], (T)-5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMultScalarEq, T, test_types)
{
	Vector3<T> vec((T)1, (T)2, (T)3);

	vec *= (T)4;
	BOOST_CHECK_EQUAL(vec[0], (T)4);
	BOOST_CHECK_EQUAL(vec[1], (T)8);
	BOOST_CHECK_EQUAL(vec[2], (T)12);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMultScalar, T, test_types)
{
	Vector3<T> vec2((T)1, (T)2, (T)3);

	Vector3<T> vec1 = vec2 * (T)4.0;
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
	Vector3<T> vec((T)12, (T)8, (T)4);

	vec /= (T)4;
	BOOST_CHECK_EQUAL(vec[0], (T)3);
	BOOST_CHECK_EQUAL(vec[1], (T)2);
	BOOST_CHECK_EQUAL(vec[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpDivScalar, T, test_types)
{
	Vector3<T> vec2((T)12, (T)8, (T)4);

	Vector3<T> vec1 = vec2 / (T)4.0;
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)2);
	BOOST_CHECK_EQUAL(vec1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpAddScaled, T, test_types)
{
	Vector3<T> vec1((T)1, (T)2, (T)3);
	Vector3<T> vec2((T)2, (T)2, (T)2);

	addScaled((T)4, vec1, vec2);
	BOOST_CHECK_EQUAL(vec1[0], (T)9);
	BOOST_CHECK_EQUAL(vec1[1], (T)10);
	BOOST_CHECK_EQUAL(vec1[2], (T)11);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpSumScaled, T, test_types)
{
	Vector3<T> vec2((T)1, (T)2, (T)3);
	Vector3<T> vec3((T)2, (T)2, (T)2);

	Vector3<T> vec1 = sumScaled((T)4, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)9);
	BOOST_CHECK_EQUAL(vec1[1], (T)10);
	BOOST_CHECK_EQUAL(vec1[2], (T)11);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMaximize, T, test_types)
{
	Vector3<T> vec1;
	Vector3<T> vec2((T)1, (T)-4, (T)-1);
	Vector3<T> vec3((T)3, (T)2, (T)-2);

	maximize(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)3);
	BOOST_CHECK_EQUAL(vec1[1], (T)2);
	BOOST_CHECK_EQUAL(vec1[2], (T)-1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMinimize, T, test_types)
{
	Vector3<T> vec1;
	Vector3<T> vec2((T)1, (T)-4, (T)-1);
	Vector3<T> vec3((T)3, (T)2, (T)-2);

	minimize(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)1);
	BOOST_CHECK_EQUAL(vec1[1], (T)-4);
	BOOST_CHECK_EQUAL(vec1[2], (T)-2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpMiddle, T, float_types)
{
	Vector3<T> vec1;
	Vector3<T> vec2((T)1, (T)2, (T)3);
	Vector3<T> vec3((T)3, (T)4, (T)5);

	middle(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)2);
	BOOST_CHECK_EQUAL(vec1[1], (T)3);
	BOOST_CHECK_EQUAL(vec1[2], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpDot, T, float_types)
{
	Vector3<T> v1(1, 0, 0);
	Vector3<T> v2(0, 1, 0);
	Vector3<T> v3(0, 0, 1);

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
	Vector3<T> v1(1, 0, 0);
	Vector3<T> v2(0, 1, 0);
	Vector3<T> v3(0, 0, 1);
	T len, ans;

	BOOST_CHECK_CLOSE(length(v1), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(length(v2), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(length(v3), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(lengthSq(v1), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(lengthSq(v2), T(1.0f), T(SMALL));
	BOOST_CHECK_CLOSE(lengthSq(v3), T(1.0f), T(SMALL));

	v1.set(2.0f, 4.0f, 5.0f);
	v2.set(12.0f, -2.0f, -4.0f);

	ans = 4.0f + 16.0f + 25.0f;
	len = lengthSq(v1);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));

	ans = sqrt(ans);
	len = length(v1);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));

	ans = 144.0f + 4.0f + 16.0f;
	len = lengthSq(v2);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));

	ans = sqrt(ans);
	len = length(v2);
	BOOST_CHECK_CLOSE(len, ans, T(SMALL));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpAngle, T, float_types)
{
	Point3<T> p1(1, 1, 0);
	Point3<T> p2(1, 0, 0);
	Point3<T> p3(2, 0, 1);
	Vector3<T> v1(p2, p1);
	Vector3<T> v2(p2, p3);

	BOOST_CHECK_CLOSE(angle(v1, v2), T(90.0), SMALL);
	p1.set(2, 0, 0);
	v1 = Vector3<T>(p2, p1);
	BOOST_CHECK_CLOSE(angle(v1, v2), T(45.0), SMALL);
	p1.set(0, 0, 0);
	v1 = Vector3<T>(p2, p1);
	BOOST_CHECK_CLOSE(angle(v1, v2), T(135.0), SMALL);
	v1.set(0, 0, 0);
	BOOST_CHECK_CLOSE(angle(v1, v2), T(0.0), SMALL);

	v1.set(2, -3, 4);
	v2.set(5, 2, 1);
	BOOST_CHECK_CLOSE(angle(v1, v2), T(74.26280), SMALL);

	DEFINE_ETHYL;
	Point3<T> C1;
	C1.set(&ETHYL[0]);
	Point3<T> C2;
	C2.set(&ETHYL[3]);
	Point3<T> H1;
	H1.set(&ETHYL[6]);
	v1 = Vector3<T>(C1, C2);
	v2 = Vector3<T>(C1, H1);
	BOOST_CHECK_CLOSE(angle(v1, v2), T(109.640722), SMALL);
	BOOST_CHECK_CLOSE(angle(v2, v1), T(109.640722), SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpNormalize, T, float_types)
{
	Vector3<T> vec1(2, 4, 5);
	Vector3<T> vec2(vec1);

	normalize(vec1);
	Vector3<T> temp = (vec1*length(vec2) );
	BOOST_CHECK(isEqual(vec2, temp, T(SMALL) ) );
	vec1.set(12, -2, -4);
	vec2 = vec1;
	normalize(vec1);
	BOOST_CHECK(isEqual(vec2, Vector3<T>(vec1*length(vec2) ), T(SMALL) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpIsNormalized, T, float_types)
{
	Vector3<T> v1(1, 0, 0);
	Vector3<T> v2(0, 1, 0);
	Vector3<T> v3(0, 0, 1);
	Vector3<T> v4(2, 4, 5);

	BOOST_CHECK(isNormalized(v1) );
	BOOST_CHECK(isNormalized(v2) );
	BOOST_CHECK(isNormalized(v3) );
	BOOST_CHECK(! isNormalized(v4) );

	v2 = v1;

	// epsilon tolerance
	for (T eps=0; eps<10; eps+=0.5)
	{
		BOOST_CHECK(isNormalized(v1, eps));
	}

	v2.set(21, 0, 0);
	BOOST_CHECK( ! isNormalized(v2, T(15.0f * 15.0f) ) );
	BOOST_CHECK( ! isNormalized(v2, T(19.9f * 19.9f) ) );
	BOOST_CHECK( isNormalized(v2, T(21.0f * 21.0f - 0.9f) ) );
	BOOST_CHECK( isNormalized(v2, T(21.0f * 21.0f + 0.9f) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpReflect, T, float_types)
{
	Vector3<T> v1(1,1,1);
	Vector3<T> v2(3,1,2);
	Vector3<T> v3(4,5,1);
	Vector3<T> n1(1,0,0); // normal of the surface/plane
	Vector3<T> n2(0,1,0);
	Vector3<T> n3(0,0,1);
	Vector3<T> ex1(-1,1,1); // flipped about the surface
	Vector3<T> ex2(3,-1,2);
	Vector3<T> ex3(4,5,-1);
	Vector3<T> res;

	const T eps = 0.001f;
	reflect(res, v1, n1);
	BOOST_CHECK(isEqual(res, ex1, eps));
	reflect(res, v2, n2);
	BOOST_CHECK(isEqual(res, ex2, eps));
	reflect(res, v3, n3);
	BOOST_CHECK(isEqual(res, ex3, eps));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpLerp, T, float_types)
{
	const T eps = 0.0001f;
	Vector3<T> q1( 2, 3, 4 ), q2( 9.01f, 8.4f, 7.1f );
	Vector3<T> expected_result1(q1), res1;
	Vector3<T> expected_result2(q2), res2;

	lerp( res1, T(0.0), q1, q2 );
	lerp( res2, T(1.0), q1, q2 );
	BOOST_CHECK(isEqual(expected_result1, res1, eps) );
	BOOST_CHECK(isEqual(expected_result2, res2, eps) );

	// test interpolated values...
	Vector3<T> q3(0, 0, 0), q4(1, 1, 1);
	Vector3<T> expected_result3(0.35f, 0.35f, 0.35f), res3;
	Vector3<T> expected_result4(0.69f, 0.69f, 0.69f), res4;

	lerp(res3, T(0.35), q3, q4);
	lerp(res4, T(0.69), q3, q4);
	BOOST_CHECK(isEqual(expected_result3, res3, eps) );
	BOOST_CHECK(isEqual(expected_result4, res4, eps) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpCross, T, float_types)
{
	Vector3<T> v1(1,0,0);
	Vector3<T> v2(0,1,0);
	Vector3<T> v3(0,0,1);
	Vector3<T> r;

	cross(r, v1, v2);
	BOOST_CHECK(isEqual(r, v3, T(0.001f) ) );
	cross(r, v2, v1);
	BOOST_CHECK(isEqual(r, Vector3<T>(-v3), T(0.001f) ) );

	v1.set(13.45f, -7.8f, 0.056f);
	v2.set(0.777f, 5.333f, 12.21f);
	v3.set(-95.537f, -164.181f, 77.789f);

	cross(r, v1, v2);
	BOOST_CHECK(isEqual(r, v3, T(0.001f) ) );
	cross(r, v2, v1);
	BOOST_CHECK(isEqual(r, Vector3<T>(-v3), T(0.001f) ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_OpTorsionAngle, T, float_types)
{
	DEFINE_ETHYL;
	Point3<T> C1;
	C1.set(&ETHYL[0]);
	Point3<T> C2;
	C2.set(&ETHYL[3]);
	Point3<T> H1;
	H1.set(&ETHYL[6]);
	Point3<T> H4;
	H4.set(&ETHYL[15]);
	Point3<T> H5;
	H5.set(&ETHYL[18]);
	Point3<T> H6;
	H6.set(&ETHYL[21]);

	Vector3<T> C1H1(C1, H1);
	Vector3<T> C1C2(C1, C2);
	Vector3<T> C2C1(C2, C1);
	Vector3<T> C2H4(C2, H4);
	BOOST_CHECK_CLOSE(torsionAngle(C1H1, C1C2, C2H4), T(-60.0), T(0.001));
	BOOST_CHECK_CLOSE(torsionAngle(C2H4, C2C1, C1H1), T(-60.0), T(0.001));

	Vector3<T> C2H5(C2, H5);
	BOOST_CHECK_CLOSE(torsionAngle(C1H1, C1C2, C2H5), T(60.0), T(0.001));
	BOOST_CHECK_CLOSE(torsionAngle(C2H5, C2C1, C1H1), T(60.0), T(0.001));

	Vector3<T> C2H6(C2, H6);
	BOOST_CHECK_CLOSE(torsionAngle(C1H1, C1C2, C2H6), T(-180.0), T(0.001));
	BOOST_CHECK_CLOSE(torsionAngle(C2H6, C2C1, C1H1), T(-180.0), T(0.001));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector3_Output, T, test_types)
{
	output_test_stream output;
	Vector3<T> vec((T)1, (T)2, (T)3);
	output << vec;
	BOOST_CHECK(!output.is_empty(false) );
	BOOST_CHECK( output.check_length(7, false) );
	BOOST_CHECK( output.is_equal("(1,2,3)") );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
