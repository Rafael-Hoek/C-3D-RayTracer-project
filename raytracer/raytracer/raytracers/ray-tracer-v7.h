#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v6.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV7 : public RayTracerV6
            {
            protected:
                imaging::Color compute_translucency(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
            public:
            };
        }

        /// <summary>
        /// Creates ray tracer.
        /// </summary>
        RayTracer v7();
    }
}