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

/*
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
*/
BOOST_AUTO_TEST_SUITE_END()
