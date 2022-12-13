#pragma once

#include "renderers/renderer.h"
#include "renderers/renderer-base.h"
#include <functional>


namespace raytracer
{
    namespace renderers
    {
        /// <summary>
        /// Creates an edge renderer.
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
        Renderer edge(unsigned width, unsigned height, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, double stroke_thickness, imaging::Color stroke_color, imaging::Color background_color);
    }
}
