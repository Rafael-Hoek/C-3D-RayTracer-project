#include "raytracers/ray-tracer-v5.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::RayTracer raytracer::raytracers::v5()
{
    LOG(INFO) << "Creating ray tracer v5";

    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV5::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, const raytracer::LightRay& light_ray) const
{
    auto all_hits = scene.root->find_all_hits(light_ray.ray);
    auto filter_color = colors::white();

    for (auto passed_through : all_hits) {
        if (passed_through->t > 0 && passed_through->t < 0.9999) {
            auto matProps = passed_through->material->at(passed_through->local_position);
            filter_color = filter_color * matProps.light_filtering;
        }
    }
    auto surviving_light_ray = LightRay(light_ray.ray, filter_color * light_ray.color);
    return raytracer::raytracers::_private_::RayTracerV3::process_light_ray(scene, properties, hit, eye_ray, surviving_light_ray);
}