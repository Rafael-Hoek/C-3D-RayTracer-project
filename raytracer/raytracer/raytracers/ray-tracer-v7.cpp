#include "raytracers\ray-tracer-v7.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

raytracer::RayTracer raytracer::raytracers::v7()
{
	LOG(INFO) << "Creating ray tracer v7";

	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV7>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV7::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
	auto result = colors::black();
	result += RayTracerV6::determine_color(scene, properties, hit, eye_ray, weight);
	result += compute_translucency(scene, properties, hit, eye_ray, weight);
	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV7::compute_translucency(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
	auto translucency = material_properties.translucency;

	if (translucency > 0)
	{
		auto new_direction = eye_ray.direction;
		auto new_origin = hit.position + 0.000001 * new_direction;
		auto new_ray = Ray(new_origin, new_direction);
		auto new_weight = translucency * weight;
		auto color = RayTracerV7::trace(scene, new_ray, new_weight).color;

		return translucency * color;
	}
	else
	{
		return colors::black();
	}
}
