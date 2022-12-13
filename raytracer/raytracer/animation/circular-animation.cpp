#include "animation/circular-animation.h"

using namespace animation;
using namespace math;

Animation<math::Point3D> animation::circular(const math::Point3D& point, const math::Point3D& center, const math::Vector3D axis, const math::Interval<math::Angle>& angle_interval, const Duration& duration)
{

    auto time_interval = interval(TimeStamp::zero(), TimeStamp::from_epoch(duration));

    std::function<math::Point3D(TimeStamp)> lambda = [angle_interval, time_interval, axis, point, center](TimeStamp now) -> math::Point3D {
        double t = time_interval.to_relative(now);
        auto angle = angle_interval.from_relative(t);
        auto point_to_center = point - center;
        auto axis_to_center = center - math::Point3D::cartesian(0,0,0);
        auto shifted_point = math::Point3D::cartesian(0, 0, 0) + point_to_center;
        auto position_interval = math::Quaternion::rotation(angle, axis).rotate(shifted_point) + axis_to_center;

        return position_interval;
    };

    return make_animation(from_lambda(lambda), duration);
}
