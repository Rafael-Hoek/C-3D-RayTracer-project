#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v5.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV6 : public RayTracerV5
            {
            protected:
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
                virtual TraceResult trace(const Scene& scene, const math::Ray& eye_ray, double weight) const;
                virtual imaging::Color compute_reflection(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;

            public:
                /// <summary>
                /// Traces the given ray.
                /// </summary>
                /// <param name="scene">
                /// Scene to be rendered.
                /// </param>
                /// <param name="eye_ray">
                /// Ray originating in the camera's eye and travelling through the scene.
                /// </param>
                /// <returns>
                /// Information about how to render the point where the eye_ray intersects the scene.
                /// </returns>
                virtual TraceResult trace(const Scene& scene, const math::Ray& eye_ray) const override;

            };
        }

        /// <summary>
        /// Creates ray tracer.
        /// </summary>
        RayTracer v6();
    }
}