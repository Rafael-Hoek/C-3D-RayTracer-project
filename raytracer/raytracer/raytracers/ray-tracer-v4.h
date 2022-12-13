#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v3.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV4 : public RayTracerV3
            {
            protected:
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const raytracer::LightRay&) const override;
            };
        }

        /// <summary>
        /// Creates ray tracer.
        /// </summary>
        RayTracer v4();
    }
}
