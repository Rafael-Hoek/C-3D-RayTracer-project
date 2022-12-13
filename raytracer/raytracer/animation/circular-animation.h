#pragma once

#include "animation/animation.h"
#include "math/quaternion.h"

namespace animation {

	Animation<math::Point3D> circular(const math::Point3D& point, const math::Point3D& center, const math::Vector3D axis, const math::Interval<math::Angle>& angle_interval, const Duration& duration);
}