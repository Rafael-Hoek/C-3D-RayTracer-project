#pragma once

#include "samplers/sampler.h"
#include <random>


namespace raytracer
{
    namespace samplers
    {
        /// <summary>
        /// Creates a sampler that always picks the center of the given rectangle.
        /// </summary>
        Sampler random(int);
    }
}
