#include "raytracers\ray-tracer-v8.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV8::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    imaging::Color result = imaging::colors::black();
    result += RayTracerV7::determine_color(scene, material_properties, hit, eye_ray, weight);
    result += compute_refraction(scene, material_properties, hit, eye_ray, weight);
    return result;
}

math::Vector3D* refract(const math::Vector3D& i, math::Vector3D& n, double n1, double n2)
{
    math::Vector3D ox = (n1 / n2) * (i - i.dot(n) * n);
    if ((1 - (ox.dot(ox))) < 0)
    {
        return nullptr;
    }
    math::Vector3D oy = (-1 * sqrt(1 - (ox.dot(ox)))) * n;
    return new math::Vector3D(ox + oy);
}


imaging::Color raytracer::raytracers::_private_::RayTracerV8::compute_refraction(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    imaging::Color result = imaging::colors::black();
    auto transparency = material_properties.transparency;

    if (transparency > 0)
    {
        double n1 = 1;
        double n2 = material_properties.refractive_index;

        // Point 1

        math::Vector3D normal_at_p1 = hit.normal;
        math::Vector3D* refracted_direction = refract(eye_ray.direction, normal_at_p1, n1, n2);

        if (refracted_direction == nullptr)
        {
            return result;
        }

        math::Point3D point1 = hit.position + *refracted_direction * 0.0000001;
        math::Ray refracted_ray = math::Ray(point1, *refracted_direction);

        Hit exit_hit;
        if (!scene.root->find_first_positive_hit(refracted_ray, &exit_hit))
        {
            return result;
        }

        // Point 2

        math::Vector3D normal_at_p2 = exit_hit.normal;
        math::Vector3D* refracted_direction2 = refract(refracted_ray.direction, normal_at_p2, n2, n1);

        if (refracted_direction2 == nullptr)
        {
            return result;
        }

        math::Point3D p2 = exit_hit.position + *refracted_direction2 * 0.0000001;
        math::Ray exit_ray = math::Ray(p2, *refracted_direction2);

        result += trace(scene, exit_ray, weight * transparency).color * transparency;

        delete refracted_direction;
        delete refracted_direction2;
        return result;

    }
    return result;
}

raytracer::RayTracer raytracer::raytracers::v8()
{
    LOG(INFO) << "Creating ray tracer v8";

    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV8>());
}