#pragma once
#include "raytracers/ray-tracer-v7.h"


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV8 : public RayTracerV7
            {
            protected:
                imaging::Color RayTracerV8::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
                imaging::Color compute_refraction(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
            };
        }

        /// <summary>
        /// Creates v8 ray tracer.
        /// </summary>
        RayTracer v8();
    }
}
