#include "raytracers/ray-tracer-v2.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::RayTracer raytracer::raytracers::v2()
{
    LOG(INFO) << "Creating ray tracer v2";

    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    auto result = colors::black();
    result += raytracer::raytracers::_private_::RayTracerV1::determine_color(scene, properties, hit, ray);
    result += process_lights(scene, properties, hit, ray);
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    auto result = colors::black();
    for each (auto light_source in scene.light_sources)
    {
        result += process_light_source(scene, properties, hit, ray, light_source);
    }
    return result;
}


imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightSource& light_source) const
{
    auto result = colors::black();

    for each (auto& light_ray in light_source->lightrays_to(hit.position))
    {
        result += process_light_ray(scene, properties, hit, eye_ray, light_ray);
    }

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightRay& light_ray) const
{
    auto result = colors::black();
    result += compute_diffuse(properties, hit, eye_ray, light_ray);
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightRay& light_ray) const
{
    auto n = hit.normal;
    auto L = light_ray.ray.origin;
    auto P = hit.position;
    auto CL = light_ray.color;
    auto CS = properties.diffuse;

    auto cos = math::cos_of_angle_between(n, L - P);

    if (cos > 0)
    {
        return cos * CL * CS;
    }
    else
    {
        return colors::black();
    }
}