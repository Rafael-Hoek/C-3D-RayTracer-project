#pragma once

#include "primitives/hit.h"
#include "math/ray.h"
#include "math/box.h"
#include <iostream>
#include <vector>
#include <memory>
#include "primitives\primitive.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive mesh(const std::string& path);
    }
}