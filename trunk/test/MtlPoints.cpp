#define BOOST_TEST_MODULE MTL
#ifdef _WIN32
	#define BOOST_TEST_ALTERNATIVE_INIT_API
#else
	#define BOOST_TEST_DYN_LINK
#endif	//_WIN32
//#define BOOST_TEST_MAIN
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

BOOST_AUTO_TEST_SUITE( Points )

BOOST_AUTO_TEST_SUITE( Pnt2 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Creation, T, test_types)
{
	Point2<T> point;

	BOOST_CHECK_EQUAL(point[0], (T)0);
	BOOST_CHECK_EQUAL(point[1], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Constructors, T, test_types)
{
	Point2<T> point((T)1, (T)2);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_VectorExplicit, T, test_types)
{
	Vector2<T> vec((T)1, (T)2);
	Point2<T> point((Vector2<T>)vec);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
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

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_X, T, test_types)
{
	Point2<T> point;

	point.x() = (T)1;
	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_Y, T, test_types)
{
	Point2<T> point;

	point.y() = (T)2;
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_GetX, T, test_types)
{
	Point2<T> point((T)1, (T)2);

	BOOST_CHECK_EQUAL(point.getX(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_GetY, T, test_types)
{
	Point2<T> point((T)1, (T)2);

	BOOST_CHECK_EQUAL(point.getY(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_SetX, T, test_types)
{
	Point2<T> point;

	point.setX((T)1);
	BOOST_CHECK_EQUAL(point[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_SetY, T, test_types)
{
	Point2<T> point;

	point.setY((T)2);
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

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Pnt2Ops )

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

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpMiddle, T, float_types)
{
	Point2<T> point1;
	Point2<T> point2((T)1, (T)2);
	Point2<T> point3((T)3, (T)4);

	middle(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)2);
	BOOST_CHECK_EQUAL(point1[1], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDistance, T, float_types)
{
	Point2<T> point1((T)3, (T)4);
	Point2<T> point2((T)1, (T)2);

	BOOST_CHECK_CLOSE(distance(point1, point2), T(2.828427f), SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpDistanceSq, T, test_types)
{
	Point2<T> point1((T)3, (T)4);
	Point2<T> point2((T)1, (T)2);

	BOOST_CHECK_EQUAL(distanceSq(point1, point2), T(8));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point2_OpAngle, T, float_types)
{
	Point2<T> point1(1, 2);
	Point2<T> point2(1, 1);
	Point2<T> point3(2, 1);

	BOOST_CHECK_CLOSE(angle(point1, point2, point3), 90, SMALL);
	point1.set(2, 2);
	BOOST_CHECK_CLOSE(angle(point1, point2, point3), 45, SMALL);
	point1.set(1, 1);
	BOOST_CHECK_CLOSE(angle(point1, point2, point3), 0, SMALL);
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
BOOST_AUTO_TEST_SUITE( Pnt3 )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Creation, T, test_types)
{
	Point3<T> point;

	BOOST_CHECK_EQUAL(point[0], (T)0);
	BOOST_CHECK_EQUAL(point[1], (T)0);
	BOOST_CHECK_EQUAL(point[2], (T)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Constructors, T, test_types)
{
	Point3<T> point((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_VectorExplicit, T, test_types)
{
	Vector3<T> vec((T)1, (T)2, (T)3);
	Point3<T> point((Vector3<T>)vec);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_CopyConstruct, T, test_types)
{
	Point3<T> point;

	point[0] = (T)2;
	point[1] = (T)4;
	point[2] = (T)6;

	Point3<T> point_copy(point);

	BOOST_CHECK_EQUAL(point_copy[0], (T)2);
	BOOST_CHECK_EQUAL(point_copy[1], (T)4);
	BOOST_CHECK_EQUAL(point_copy[2], (T)6);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_X, T, test_types)
{
	Point3<T> point;

	point.x() = (T)1;
	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point.x(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Y, T, test_types)
{
	Point3<T> point;

	point.y() = (T)2;
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point.y(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Z, T, test_types)
{
	Point3<T> point;

	point.z() = (T)3;
	BOOST_CHECK_EQUAL(point[2], (T)3);
	BOOST_CHECK_EQUAL(point.z(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetX, T, test_types)
{
	Point3<T> point((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(point.getX(), (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetY, T, test_types)
{
	Point3<T> point((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(point.getY(), (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetZ, T, test_types)
{
	Point3<T> point((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(point.getZ(), (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetX, T, test_types)
{
	Point3<T> point;

	point.setX((T)1);
	BOOST_CHECK_EQUAL(point[0], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetY, T, test_types)
{
	Point3<T> point;

	point.setY((T)2);
	BOOST_CHECK_EQUAL(point[1], (T)2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetZ, T, test_types)
{
	Point3<T> point;

	point.setZ((T)3);
	BOOST_CHECK_EQUAL(point[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Set, T, test_types)
{
	Point3<T> point;
	point.set((T)1, (T)2, (T)3);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_SetPtr, T, test_types)
{
	T data[3] = {(T)1, (T)2, (T)3};

	Point3<T> point;
	point.set(data);

	BOOST_CHECK_EQUAL(point[0], (T)1);
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point[2], (T)3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_GetData, T, test_types)
{
	T* data;
	Point3<T> point((T)1, (T)2, (T)3);
	data = point.getData();

	BOOST_CHECK_EQUAL(data[0], (T)1);
	BOOST_CHECK_EQUAL(data[1], (T)2);
	BOOST_CHECK_EQUAL(data[2], (T)3);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( Pnt3Ops )

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpEqualityCompare, T, test_types)
{
	Point3<T> point1((T)1, (T)2, T(3));
	Point3<T> point2(point1);

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
	Point3<T> point1(1.0, 2.0, 3.0);
	Point3<T> point2(point1);
	T eps(0.0);

	for(eps=(T)0.0; eps<(T)10.0; eps += (T)0.05)
	{
		BOOST_CHECK(isEqual(point1, point2, eps));
		BOOST_CHECK_CLOSE(point1[0], point2[0], eps);
		BOOST_CHECK_CLOSE(point1[1], point2[1], eps);
		BOOST_CHECK_CLOSE(point1[2], point2[2], eps);
	}

	point1.set(1.0f, 1.0f, 1.0f);
	for(unsigned elt=0; elt<3; elt++)
	{
		point2 = point1;
		point2[elt] = (T)21.0;
		BOOST_CHECK(!isEqual(point1, point2, T(10.0)));
		BOOST_CHECK(!isEqual(point1, point2, T(19.9)));
		BOOST_CHECK( isEqual(point1, point2, T(20.1)));
		BOOST_CHECK( isEqual(point1, point2, T(22.0)));
	}
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpPlusEq, T, test_types)
{
	Point3<T> point1((T)1, (T)2, (T)3);
	Point3<T> point2((T)2, (T)2, (T)2);

	point1 += point2;
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)4);
	BOOST_CHECK_EQUAL(point1[2], (T)5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpPlus, T, test_types)
{
	Point3<T> point2((T)2, (T)2, (T)3);
	Point3<T> point3((T)1, (T)2, (T)3);

	Point3<T> point1 = point3 + point2;
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)4);
	BOOST_CHECK_EQUAL(point1[2], (T)6);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMinusEq, T, test_types)
{
	Point3<T> point1((T)1, (T)2, (T)3);
	Point3<T> point2((T)2, (T)2, (T)2);

	point1 -= point2;
	BOOST_CHECK_EQUAL(point1[0], (T)-1);
	BOOST_CHECK_EQUAL(point1[1], (T)0);
	BOOST_CHECK_EQUAL(point1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMinus, T, test_types)
{
	Point3<T> point2((T)2, (T)2, (T)2);
	Point3<T> point3((T)1, (T)2, (T)3);

	Point3<T> point1 = point3 - point2;
	BOOST_CHECK_EQUAL(point1[0], (T)-1);
	BOOST_CHECK_EQUAL(point1[1], (T)0);
	BOOST_CHECK_EQUAL(point1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpNegate, T, test_types)
{
	Point3<T> point2((T)2, (T)-3, (T)5);

	Point3<T> point1 = -point2;
	BOOST_CHECK_EQUAL(point1[0], (T)-2);
	BOOST_CHECK_EQUAL(point1[1], (T)3);
	BOOST_CHECK_EQUAL(point1[2], (T)-5);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMultScalarEq, T, test_types)
{
	Point3<T> point((T)1, (T)2, (T)3);

	point *= (T)4;
	BOOST_CHECK_EQUAL(point[0], (T)4);
	BOOST_CHECK_EQUAL(point[1], (T)8);
	BOOST_CHECK_EQUAL(point[2], (T)12);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMultScalar, T, test_types)
{
	Point3<T> point2((T)1, (T)2, (T)3);

	Point3<T> point1 = point2 * (T)4.0;
	BOOST_CHECK_EQUAL(point1[0], (T)4);
	BOOST_CHECK_EQUAL(point1[1], (T)8);
	BOOST_CHECK_EQUAL(point1[2], (T)12);

	point1 = (T)4.0 * point2;
	BOOST_CHECK_EQUAL(point1[0], (T)4);
	BOOST_CHECK_EQUAL(point1[1], (T)8);
	BOOST_CHECK_EQUAL(point1[2], (T)12);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpDivScalarEq, T, test_types)
{
	Point3<T> point((T)12, (T)8, (T)4);

	point /= (T)4;
	BOOST_CHECK_EQUAL(point[0], (T)3);
	BOOST_CHECK_EQUAL(point[1], (T)2);
	BOOST_CHECK_EQUAL(point[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpDivScalar, T, test_types)
{
	Point3<T> point2((T)12, (T)8, (T)4);

	Point3<T> point1 = point2 / (T)4.0;
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)2);
	BOOST_CHECK_EQUAL(point1[2], (T)1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpAddScaled, T, test_types)
{
	Point3<T> point1((T)1, (T)2, (T)3);
	Point3<T> point2((T)2, (T)2, (T)2);

	addScaled((T)4, point1, point2);
	BOOST_CHECK_EQUAL(point1[0], (T)9);
	BOOST_CHECK_EQUAL(point1[1], (T)10);
	BOOST_CHECK_EQUAL(point1[2], (T)11);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpSumScaled, T, test_types)
{
	Point3<T> point2((T)1, (T)2, (T)3);
	Point3<T> point3((T)2, (T)2, (T)2);

	Point3<T> point1 = sumScaled((T)4, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)9);
	BOOST_CHECK_EQUAL(point1[1], (T)10);
	BOOST_CHECK_EQUAL(point1[2], (T)11);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMaximize, T, test_types)
{
	Point3<T> point1;
	Point3<T> point2((T)1, (T)-4, (T)-1);
	Point3<T> point3((T)3, (T)2, (T)-2);

	maximize(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)3);
	BOOST_CHECK_EQUAL(point1[1], (T)2);
	BOOST_CHECK_EQUAL(point1[2], (T)-1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMinimize, T, test_types)
{
	Point3<T> point1;
	Point3<T> point2((T)1, (T)-4, (T)-1);
	Point3<T> point3((T)3, (T)2, (T)-2);

	minimize(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)1);
	BOOST_CHECK_EQUAL(point1[1], (T)-4);
	BOOST_CHECK_EQUAL(point1[2], (T)-2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpMiddle, T, float_types)
{
	Point3<T> point1;
	Point3<T> point2((T)1, (T)2, (T)3);
	Point3<T> point3((T)3, (T)4, (T)5);

	middle(point1, point2, point3);
	BOOST_CHECK_EQUAL(point1[0], (T)2);
	BOOST_CHECK_EQUAL(point1[1], (T)3);
	BOOST_CHECK_EQUAL(point1[2], (T)4);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpDistance, T, float_types)
{
	Point3<T> point1((T)3, (T)4, (T)5);
	Point3<T> point2((T)1, (T)2, (T)5);

	BOOST_CHECK_CLOSE(distance(point1, point2), T(2.828427f), SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpDistanceSq, T, test_types)
{
	Point3<T> point1((T)3, (T)4, (T)3);
	Point3<T> point2((T)1, (T)2, (T)5);

	BOOST_CHECK_EQUAL(distanceSq(point1, point2), T(12));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpAngle, T, float_types)
{
	Point3<T> point1(1, 1, 0);
	Point3<T> point2(1, 0, 0);
	Point3<T> point3(2, 0, 1);

	BOOST_CHECK_CLOSE(angle(point1, point2, point3), 90, SMALL);
	point1.set(2, 0, 0);
	BOOST_CHECK_CLOSE(angle(point1, point2, point3), 45, SMALL);
	point1.set(0, 0, 0);
	BOOST_CHECK_CLOSE(angle(point1, point2, point3), 135, SMALL);

	DEFINE_ETHYL;
	Point3<T> C1;
	C1.set(&ETHYL[0]);
	Point3<T> C2;
	C2.set(&ETHYL[3]);
	Point3<T> H1;
	H1.set(&ETHYL[6]);
	BOOST_CHECK_CLOSE(angle(C2, C1, H1), 109.640722, SMALL);
	BOOST_CHECK_CLOSE(angle(H1, C1, C2), 109.640722, SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_OpTorsionAngle, T, float_types)
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

	BOOST_CHECK_CLOSE(torsionAngle(H1, C1, C2, H4), 60.000007, SMALL);
	BOOST_CHECK_CLOSE(torsionAngle(H4, C2, C1, H1), 60.000007, SMALL);
	BOOST_CHECK_CLOSE(torsionAngle(H1, C1, C2, H5), -59.99999, SMALL);
	BOOST_CHECK_CLOSE(torsionAngle(H5, C2, C1, H1), -59.99999, SMALL);
	BOOST_CHECK_CLOSE(torsionAngle(H1, C1, C2, H6), -180, SMALL);
	BOOST_CHECK_CLOSE(torsionAngle(H6, C2, C1, H1), -180, SMALL);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Point3_Output, T, test_types)
{
	output_test_stream output;
	Point3<T> point((T)1, (T)2, (T)3);
	output << point;
	BOOST_CHECK(!output.is_empty(false) );
	BOOST_CHECK( output.check_length(7, false) );
	BOOST_CHECK( output.is_equal("(1,2,3)") );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
