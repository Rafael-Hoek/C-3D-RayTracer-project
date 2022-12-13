#pragma once

#include "animation/animation.h"

namespace animation {

	Animation<math::Point3D> lissajous(double x_amplitude, double y_amplitude, double z_amplitude, double x_frequency, double y_frequency, double z_frequency, const math::Angle& x_phase, const math::Angle& y_phase, const math::Angle& z_phase, const Duration& duration);
}