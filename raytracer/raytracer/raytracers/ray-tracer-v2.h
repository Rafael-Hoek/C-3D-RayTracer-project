#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v1.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV2 : public RayTracerV1
            {
            protected:
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&)  const override;
                virtual imaging::Color process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&) const;
                virtual imaging::Color process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const raytracer::LightSource&) const;
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const raytracer::LightRay&) const;
                imaging::Color compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray&, const raytracer::LightRay&) const;
            };
        }

        /// <summary>
        /// Creates ray tracer.
        /// </summary>
        RayTracer v2();
    }
}