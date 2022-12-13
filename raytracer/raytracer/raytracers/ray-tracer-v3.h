#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v2.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV3 : public RayTracerV2
            {
            protected:
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const raytracer::LightRay&) const override;
                imaging::Color compute_specular(const MaterialProperties& properties, const Hit& hit, const math::Ray&, const raytracer::LightRay&) const;
            };
        }

        /// <summary>
        /// Creates ray tracer.
        /// </summary>
        RayTracer v3();
    }
}