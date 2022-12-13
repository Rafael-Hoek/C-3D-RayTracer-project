#include "raytracers/ray-tracer-v1.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV1::trace(const Scene& scene, const Ray& eye_ray) const
{
    Hit hit;

    // Ask the scene for the first positive hit, i.e. the closest hit in front of the eye
    // If there's a hit, find_first_positive_hit returns true and updates the hit object with information about the hit
    if (scene.root->find_first_positive_hit(eye_ray, &hit))
    {
        //use the hit-object to retrieve the hit-location
        HitPosition hitPosition = hit.local_position;
        //use the hit-object to find the material
        Material material = hit.material;
        //use hitPosition and material to find the MaterialProperties at the given hitPosition
        MaterialProperties  properties = material->at(hitPosition);

        //give scene, materialProperties, hit and ray to determine color of the point hit
        Color hit_color = determine_color(scene, properties, hit, eye_ray);

        // The hit object contains the group id, just copy it (group ids are important for edge detection)
        unsigned group_id = hit.group_id;

        // The t-value indicates where the ray/scene intersection took place.
        // You can use ray.at(t) to find the xyz-coordinates in space.
        double t = hit.t;

        // Group all this data into a TraceResult object.
        return TraceResult(hit_color, group_id, eye_ray, t);
    }
    else
    {
        // The ray missed all objects in the scene
        // Return a TraceResult object representing "no hit found"
        // which is basically the same as returning black
        return TraceResult::no_hit(eye_ray);
    }
}

raytracer::RayTracer raytracer::raytracers::v1()
{
    LOG(INFO) << "Creating ray tracer v1";

    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV1>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV1::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&) const
{
    return compute_ambient(properties);
}

Color raytracer::raytracers::_private_::RayTracerV1::compute_ambient(const MaterialProperties& properties) const
{
    return properties.ambient;
}
