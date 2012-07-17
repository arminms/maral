#define BOOST_TEST_MODULE MTL
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/unit_test.hpp>
//#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

//#include <Magma/MtlPoint.hpp>
#include <Magma/MtlPointOps.hpp>
#include <Magma/MtlOutput.hpp>

using boost::test_tools::output_test_stream;
using namespace Magma::Mtl;

typedef boost::mpl::list<int,float,double,long double> test_types;
typedef boost::mpl::list<float,double,long double> float_types;

BOOST_AUTO_TEST_SUITE( Points )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Creation, T, test_types)
{
	Point2<T> point;

	BOOST_CHECK_EQUAL(point[0], (T)0);
	BOOST_CHECK_EQUAL(point[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_CopyConstruct, T, test_types)
{
	Point2<T> point;

	point[0] = (T)2;
	point[1] = (T)4;

	Point2<T> point_copy(point);

	BOOST_CHECK_EQUAL(point_copy[0], (T)2);
	BOOST_CHECK_EQUAL(point_copy[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Constructors, T, test_types)
{
	Point2<T> point((T)1, (T)2);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Set, T, test_types)
{
	Point2<T> point;
	point.set((T)1, (T)2);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_SetPtr, T, test_types)
{
	T data[2] = {(T)1, (T)2};

	Point2<T> point;
	point.set(data);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_GetData, T, test_types)
{
	T* data;
	Point2<T> point((T)1, (T)2);
	data = point.getData();

	BOOST_CHECK_EQUAL(data[0], (T)1);
	BOOST_CHECK_EQUAL(data[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpEqualityCompare, T, test_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2(point1);

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
	Point2<T> point1(1.0, 2.0);
	Point2<T> point2(point1);
	T eps(0.0);

	for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
	{
		BOOST_CHECK(isEqual(point1, point2, eps));
		BOOST_CHECK_CLOSE(point1[0], point2[0], eps);
		BOOST_CHECK_CLOSE(point1[1], point2[1], eps);
	}

	point1.set(1.0, 1.0);
	for(unsigned elt=0; elt<2; elt++)
	{
		point2 = point1;
		point2[elt] = (T)21.0;
		BOOST_CHECK(!isEqual(point1, point2, T(10.0)));
		BOOST_CHECK(!isEqual(point1, point2, T(19.9)));
		BOOST_CHECK( isEqual(point1, point2, T(20.1)));
//		BOOST_CHECK_CLOSE(point1[elt], point2[elt], T(20.1));
		BOOST_CHECK( isEqual(point1, point2, T(22.0)));
//		BOOST_CHECK_CLOSE(point1[elt], point2[elt], T(22.1));
	}
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpPlusEq, T, test_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2((T)2, (T)2);

	point1 += point2;
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpPlus, T, test_types)
{
	Point2<T> point2((T)2, (T)2);
	Point2<T> point3((T)1, (T)2);

	Point2<T> point1 = point3 + point2;
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinusEq, T, test_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2((T)2, (T)2);

	point1 -= point2;
	BOOST_CHECK_EQUAL(point1[0], (T)-1);
	BOOST_CHECK_EQUAL(point1[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinus, T, test_types)
{
	Point2<T> point2((T)2, (T)2);
	Point2<T> point3((T)1, (T)2);

	Point2<T> point1 = point3 - point2;
	BOOST_CHECK_EQUAL(point1[0], (T)-1);
	BOOST_CHECK_EQUAL(point1[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpNegate, T, test_types)
{
	Point2<T> point2((T)2, (T)-3);

	Point2<T> point1 = -point2;
	BOOST_CHECK_EQUAL(point1[0], (T)-2);
	BOOST_CHECK_EQUAL(point1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMultScalarEq, T, test_types)
{
	Point2<T> point((T)1, (T)2);

	point *= (T)4;
	BOOST_CHECK_EQUAL(point[0], (T)4);
	BOOST_CHECK_EQUAL(point[1], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMultScalar, T, test_types)
{
	Point2<T> point2((T)1, (T)2);

	Point2<T> point1 = point2 * (T)4.0;
	BOOST_CHECK_EQUAL(point1[0], (T)4);
	BOOST_CHECK_EQUAL(point1[1], (T)8);

	point1 = (T)4.0 * point2;
	BOOST_CHECK_EQUAL(point1[0], (T)4);
	BOOST_CHECK_EQUAL(point1[1], (T)8);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDivScalarEq, T, test_types)
{
	Point2<T> point((T)12, (T)8);

	point /= (T)4;
	BOOST_CHECK_EQUAL(point[0], (T)3);
	BOOST_CHECK_EQUAL(point[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDivScalar, T, test_types)
{
	Point2<T> point2((T)12, (T)8);

	Point2<T> point1 = point2 / (T)4.0;
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpAddScaled, T, test_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2((T)2, (T)2);

	addScaled((T)4, point1, point2);
	BOOST_CHECK_EQUAL(point1[0], (T)9);
	BOOST_CHECK_EQUAL(point1[1], (T)10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpSumScaled, T, test_types)
{
	Point2<T> point2((T)1, (T)2);
	Point2<T> point3((T)2, (T)2);

	Point2<T> point1 = sumScaled((T)4, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)9);
	BOOST_CHECK_EQUAL(point1[1], (T)10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMaximize, T, test_types)
{
	Point2<T> point1;
	Point2<T> point2((T)1, (T)4);
	Point2<T> point3((T)3, (T)2);

	maximize(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMinimize, T, test_types)
{
	Point2<T> point1;
	Point2<T> point2((T)1, (T)4);
	Point2<T> point3((T)3, (T)2);

	minimize(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)1);
	BOOST_CHECK_EQUAL(point1[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMiddle, T, test_types)
{
	Point2<T> point1;
	Point2<T> point2((T)1, (T)2);
	Point2<T> point3((T)3, (T)4);

	middle(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)2);
	BOOST_CHECK_EQUAL(point1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDistance, T, test_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2((T)3, (T)2);

	BOOST_CHECK_EQUAL(distance(point1, point2), T(2));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDistanceSq, T, test_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2((T)3, (T)2);

	BOOST_CHECK_EQUAL(distanceSq(point1, point2), T(4));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpAngle, T, float_types)
{
	Point2<T> point1((T)1, (T)2);
	Point2<T> point2((T)1, (T)1);
	Point2<T> point3((T)2, (T)1);

	BOOST_CHECK_CLOSE(angle(point1, point2, point3), T(90), T(SMALL));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Output, T, test_types)
{
	output_test_stream output;
	Point2<T> point((T)1, (T)2);
	output << point;
	BOOST_CHECK(!output.is_empty(false) );
	BOOST_CHECK( output.check_length(5, false) );
	BOOST_CHECK( output.is_equal("(1,2)") );
}

BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_CASE( Point2 )
//{
//	BOOST_CHECK( BOOST_IS_DEFINED(SYMBOL1) );
//	BOOST_CHECK( BOOST_IS_DEFINED(SYMBOL2(arg)) );
//}
