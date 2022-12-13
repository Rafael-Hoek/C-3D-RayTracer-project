#ifdef TEST_BUILD
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include "samplers/stratisfied-sampler.h"

#include "math/rectangle2d.h"
#include "math/rectangle3d.h"

#include <iostream>
#include <vector>
#include <algorithm>

bool contains(std::vector<math::Point2D> reqpoints, std::vector<math::Point2D> points)
{
	if (points.size() != reqpoints.size())
	{
		return false;
	}

	for (unsigned i = 0; i < reqpoints.size(); i++)
	{
		auto key = reqpoints[i];

		if (!(std::find(points.begin(), points.end(), key) != points.end()))
		{
			return false;
		}
	}
	return true;
}

// [0,1]x[0,1] and 1x1
TEST_CASE("test 1")
{
	auto rect = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(0.5, 0.5));

	REQUIRE(contains(strat->sample(rect), points));
}

// [5,7]x[3,7] and 1x1
TEST_CASE("test 2")
{
	auto rect = math::Rectangle2D(math::Point2D(5, 3), math::Vector2D(2, 0), math::Vector2D(0, 4));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(6,5));

	REQUIRE(contains(strat->sample(rect), points));
}

// [0,2]x[0,2] and 1x1
TEST_CASE("test 3")
{
	auto rect = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(1, 1));

	REQUIRE(contains(strat->sample(rect), points));
}

// [0,4]x[0,2] and 2x1
TEST_CASE("test 4")
{
	auto rect = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 2));
	auto strat = raytracer::samplers::stratified(2, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(1,1));
	points.push_back(math::Point2D(1, 3));

	REQUIRE(contains(strat->sample(rect), points));
}

// [0,2]x[0,4] and 1x2
TEST_CASE("test 5")
{
	auto rect = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 4));
	auto strat = raytracer::samplers::stratified(1, 2);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(1, 1));
	points.push_back(math::Point2D(3, 1));

	REQUIRE(contains(strat->sample(rect), points));
}

// [0,3]x[0,3] and 1x1
TEST_CASE("test 6")
{
	auto rect = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(3, 0), math::Vector2D(0, 3));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(1.5, 1.5));

	REQUIRE(contains(strat->sample(rect), points));
}

// [1,1]x[3,3] and 1x1
TEST_CASE("test 7")
{
	auto rect = math::Rectangle2D(math::Point2D(1, 1), math::Vector2D(2, 0), math::Vector2D(0, 2));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(2, 2));

	REQUIRE(contains(strat->sample(rect), points));
}


// [0,6]x[0,6] and 1x1
TEST_CASE("test 8")
{
	auto rect = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(6, 0), math::Vector2D(0, 6));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(3,3));

	REQUIRE(contains(strat->sample(rect), points));
}

// [1,1]x[5,5] and 1x1
TEST_CASE("test 9")
{
	auto rect = math::Rectangle2D(math::Point2D(1, 1), math::Vector2D(4, 0), math::Vector2D(0, 4));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(3, 3));

	REQUIRE(contains(strat->sample(rect), points));
}

// [2,2]x[4,4] and 1x1
TEST_CASE("test 10")
{
	auto rect = math::Rectangle2D(math::Point2D(2, 2), math::Vector2D(2, 0), math::Vector2D(0, 2));
	auto strat = raytracer::samplers::stratified(1, 1);

	std::vector<math::Point2D> points;
	points.push_back(math::Point2D(3, 3));

	REQUIRE(contains(strat->sample(rect), points));
}

#endif