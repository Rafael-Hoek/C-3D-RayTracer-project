#pragma once

#include "renderers/renderer.h"
#include "renderers/renderer.h"
#include <functional>


namespace raytracer
{
    namespace renderers
    {
        /// <summary>
        /// Creates a cartoon renderer.
        /// </summary>
        /// <param name="width">
        /// Width of the bitmaps to be produced.
        /// </param>
        /// <param name="height">
        /// Height of the bitmaps to be produced.
        /// </param>
        /// <param name="sampler">
        /// Sampler used for rendering pixels.
        /// </param>
        /// <param name="ray_tracer">
        /// Ray tracer to be used for tracing rays.
        /// </param>
        /// <param name="scheduler">
        /// Task scheduler.
        /// </param>
        Renderer cartoon(unsigned width, unsigned height, unsigned shade_count, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler);
    }
}