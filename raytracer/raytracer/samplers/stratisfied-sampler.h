#pragma once

#include "samplers/sampler.h"
#include "math/rasterizer.h"

namespace raytracer
{
    namespace samplers
    {
        /// <summary>
        /// Creates a sampler that always picks the center of the given rectangle.
        /// </summary>
        Sampler stratified(unsigned rows, unsigned columns);
    }
}