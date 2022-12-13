#include "raytracers/ray-tracer-v3.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::RayTracer raytracer::raytracers::v3()
{
    LOG(INFO) << "Creating ray tracer v3";

    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightRay& light_ray) const
{
    auto result = colors::black();

    result += raytracer::raytracers::_private_::RayTracerV2::process_light_ray(scene, properties, hit, eye_ray, light_ray);
    result += compute_specular(properties, hit, eye_ray, light_ray);
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightRay& light_ray) const
{
    if (properties.specular == colors::black())
    {
        return colors::black();
    }

    auto L = light_ray.ray.origin;
    auto P = hit.position;
    auto E = eye_ray.origin;
    auto CL = light_ray.color;
    auto CP = properties.specular;
    auto e = properties.specular_exponent;

    auto n = hit.normal;

    Vector3D i = (P - L).Vector3D::normalized();
    Vector3D r = i.reflect_by(n);
    Vector3D v = (E - P).Vector3D::normalized();
    auto cos = math::cos_of_angle_between(v, r);

    if (cos > 0)
    {
        return  CL * CP * pow(cos, e);
    }
    else
    {
        return colors::black();
    }
}
