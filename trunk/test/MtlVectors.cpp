#define BOOST_TEST_MODULE MTL
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/unit_test.hpp>
//#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include <Magma/Magma.hpp>

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
	Vector2<T> v1(1, 0);
	Vector2<T> v2(0, 1);

	// base vectors
	BOOST_CHECK_CLOSE(T(0), dot(v1,v2), T(SMALL));

	// other vectors
	v1.set(13.45f, -7.8f);
	v2.set(0.777f, 5.333f);

	T ans = -31.14675;
	BOOST_CHECK_CLOSE(dot(v1,v2), ans, T(SMALL));
	BOOST_CHECK_CLOSE(dot(v2,v1), ans, T(SMALL));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpDot, T, float_types)
{
	Vector2<T> vec1;
	Vector2<T> vec2((T)1, (T)2);
	Vector2<T> vec3((T)3, (T)4);

	middle(vec1, vec2, vec3);
	BOOST_CHECK_EQUAL(vec1[0], (T)2);
	BOOST_CHECK_EQUAL(vec1[1], (T)3);
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

	BOOST_CHECK_CLOSE(angle(vec1, vec2), 90, SMALL);
	vec2.set(1, 1);
	BOOST_CHECK_CLOSE(angle(vec1, vec2), 45, SMALL);
	vec2.set(3, 0);
	vec2.set(3, 3);
	BOOST_CHECK_CLOSE(angle(vec1, vec2), 45, SMALL);
	vec2.set(0, 0);
	BOOST_CHECK_CLOSE(angle(vec1, vec2), 0, SMALL);
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

BOOST_AUTO_TEST_CASE_TEMPLATE(Vector2_OpIsNormalized, T, float_types )
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

BOOST_AUTO_TEST_SUITE_END()
