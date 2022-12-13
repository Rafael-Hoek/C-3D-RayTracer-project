#include "raytracers\ray-tracer-v6.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

raytracer::RayTracer raytracer::raytracers::v6()
{
	LOG(INFO) << "Creating ray tracer v6";

	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
	auto result = colors::black();
	result += raytracer::raytracers::_private_::RayTracerV5::determine_color(scene, properties, hit, eye_ray);
	result += compute_reflection(scene, properties, hit, eye_ray, weight);
	return result;
}

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const math::Ray& eye_ray, double weight) const
{
	Hit hit;
	if (weight > 0.01 && scene.root->find_first_positive_hit(eye_ray, &hit))
	{
		auto mat = hit.material->at(hit.local_position);
		auto hit_color = determine_color(scene, mat, hit, eye_ray, weight);
		
		return TraceResult(hit_color, hit.group_id, eye_ray, hit.t);
	}
	else
	{
		return TraceResult::no_hit(eye_ray);
	}
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_reflection(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
	auto reflectivity = properties.reflectivity;

	if (reflectivity > 0)
	{
		auto reflected_ray_direction = eye_ray.direction.reflect_by(hit.normal);
		auto reflected_ray_origin = hit.position + 0.000001 * reflected_ray_direction;
		auto reflected_ray = Ray(reflected_ray_origin, reflected_ray_direction);
		auto reflected_color = trace(scene, reflected_ray, weight * reflectivity).color;
		return reflectivity * reflected_color;
	}
	else
	{
		return colors::black();
	}
}

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const math::Ray& eye_ray) const
{
	return raytracer::raytracers::_private_::RayTracerV6::trace(scene, eye_ray, 1.0);
}
