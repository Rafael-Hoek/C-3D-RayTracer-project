#include "animation/lissajous-animation.h"

using namespace animation;
using namespace math;

Animation<math::Point3D> animation::lissajous(double x_amplitude, double y_amplitude, double z_amplitude, double x_frequency, double y_frequency, double z_frequency, const math::Angle& x_phase, const math::Angle& y_phase, const math::Angle& z_phase, const Duration& duration)
{

    auto time_interval = interval(TimeStamp::zero(), TimeStamp::from_epoch(duration));

    std::function<math::Point3D(TimeStamp)> lambda = [time_interval, x_amplitude, y_amplitude, z_amplitude, x_frequency, y_frequency, z_frequency, x_phase, y_phase, z_phase](TimeStamp now) -> math::Point3D {
        double t = time_interval.to_relative(now);
        double pi = 3.14159265;
        auto x_value = x_amplitude * math::sin(math::Angle::radians(x_frequency * t * 2 * pi) - x_phase);
        auto y_value = y_amplitude * math::sin(math::Angle::radians(y_frequency * t * 2 * pi) - y_phase);;
        auto z_value = z_amplitude * math::sin(math::Angle::radians(z_frequency * t * 2 * pi) - z_phase);;
        auto position_interval = math::Point3D(x_value, y_value, z_value);

        return position_interval;
    };

    return make_animation(from_lambda(lambda), duration);
}
