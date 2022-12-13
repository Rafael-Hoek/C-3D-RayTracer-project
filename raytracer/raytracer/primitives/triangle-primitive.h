#pragma once

#include "primitives/primitive.h"
#include "math/point.h"

namespace raytracer
{
    namespace primitives
    {
        Primitive triangle(math::Point3D, math::Point3D, math::Point3D);
    }
}

