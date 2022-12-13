#pragma once

#include "primitives/primitive.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive group(unsigned id, Primitive child);
    }
}