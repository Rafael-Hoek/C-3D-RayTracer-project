#include "raytracers/ray-tracer-v4.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::RayTracer raytracer::raytracers::v4()
{
    LOG(INFO) << "Creating ray tracer v4";

    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightRay& light_ray) const
{
    Hit light_hit;
    auto has_hit = scene.root->find_first_positive_hit(light_ray.ray, &light_hit);

    if (has_hit && !(light_hit.t >= 0 && light_hit.t < 0.9999)) {
        return raytracer::raytracers::_private_::RayTracerV3::process_light_ray(scene, properties, hit, eye_ray, light_ray);
    }
    else {
        return colors::black();
    }
}
