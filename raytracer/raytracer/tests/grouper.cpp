#ifdef TEST_BUILD
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include "primitives/sphere-primitive.h"
#include "primitives/group-primitive.h"
#include "primitives/transformer-primitive.h"
#include "math/ray.h"
#include "math/vector.h"

#include <iostream>
#include <vector>
#include <algorithm>

TEST_CASE("no group ID gives missing ID for sphere")
{
	auto s = raytracer::primitives::sphere();
	auto r = math::Ray(math::Point3D::cartesian(5, 0, 0), math::Point3D::cartesian(0, 0, 0));
	auto hits = s->find_all_hits(r);
	for (auto hit : hits) {
		REQUIRE(hit->group_id == unsigned(-1));
	}
}

TEST_CASE("group ID 1 given returns group ID 1 for single sphere")
{
	auto s = raytracer::primitives::group(1, raytracer::primitives::sphere());
	auto r = math::Ray(math::Point3D::cartesian(5, 0, 0), math::Point3D::cartesian(0, 0, 0));
	auto hits = s->find_all_hits(r);
	for (auto hit : hits) {
		REQUIRE(hit->group_id == 1);
	}
}

TEST_CASE("group ID 1 given returns group ID 1 for several spheres")
{
	auto s1 = raytracer::primitives::group(1, raytracer::primitives::sphere());
	auto s2 = raytracer::primitives::group(1, raytracer::primitives::translate(math::Vector3D::cartesian(-3,0,0),raytracer::primitives::sphere()));
	auto r = math::Ray(math::Point3D::cartesian(5, 0, 0), math::Point3D::cartesian(0, 0, 0));
	auto hits1 = s1->find_all_hits(r);
	auto hits2 = s2->find_all_hits(r);
	for (auto hit : hits1) {
		REQUIRE(hit->group_id == 1);
	}
	for (auto hit : hits2) {
		REQUIRE(hit->group_id == 1);
	}
}

TEST_CASE("different group IDs given returns correct group ID for given spheres spheres")
{
	auto s1 = raytracer::primitives::group(1, raytracer::primitives::sphere());
	auto s2 = raytracer::primitives::group(2, raytracer::primitives::translate(math::Vector3D::cartesian(-3, 0, 0), raytracer::primitives::sphere()));
	auto r = math::Ray(math::Point3D::cartesian(5, 0, 0), math::Point3D::cartesian(0, 0, 0));
	auto hits1 = s1->find_all_hits(r);
	auto hits2 = s2->find_all_hits(r);
	for (auto hit : hits1) {
		REQUIRE(hit->group_id == 1);
	}
	for (auto hit : hits2) {
		REQUIRE(hit->group_id == 2);
	}
}

#endif