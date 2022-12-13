#pragma once

#include "lights/point-light.h"
#include "imaging/color.h"
#include "math/point.h"
#include <memory>

namespace raytracer
{
	namespace lights
	{
		LightSource spot(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color);

		//LightSource spot(const math::Point3D& position, const math::Point3D& target, math::Angle angle, const imaging::Color& color);
	}
}