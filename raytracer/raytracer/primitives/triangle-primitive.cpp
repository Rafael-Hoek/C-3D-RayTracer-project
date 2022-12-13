#include "primitives/triangle-primitive.h"
#include "primitives/sphere-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    private:

        Point3D p1, p2, p3;
        Vector3D normal;

        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            // Update Hit object
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->normal = normal;
        }

    public:

        TriangleImplementation(math::Point3D p1, math::Point3D p2, math::Point3D p3) : p1(p1), p2(p2), p3(p3)
        {
            normal = (p2 - p1).cross(p3 - p1).normalized();
        }


        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
            double t = ((p1 - ray.origin).dot(normal)) / (ray.direction.dot(normal));

            Point3D H = ray.at(t);

            auto p1p2 = ((p2 - p1).cross(H - p1)).dot(normal);
            auto p2p3 = ((p3 - p2).cross(H - p2)).dot(normal);
            auto p3p1 = ((p1 - p3).cross(H - p3)).dot(normal);

            if (p1p2 < 0)
            {
                return std::vector<std::shared_ptr<Hit>>();
            }

            if (p2p3 < 0)
            {
                return std::vector<std::shared_ptr<Hit>>();
            }

            if (p3p1 < 0)
            {
                return std::vector<std::shared_ptr<Hit>>();
            }

            auto hit = std::make_shared<Hit>();
            initialize_hit(hit.get(), ray, t);

            auto hits = std::vector<std::shared_ptr<Hit>>();
            hits.push_back(hit);

            return hits;
        }

        math::Box bounding_box() const override
        {

            auto max_x = fmax(fmax(p1.x(), p2.x()), p3.x());
            auto max_y = fmax(fmax(p1.y(), p2.y()), p3.y());
            auto max_z = fmax(fmax(p1.z(), p2.z()), p3.z());

            auto min_x = fmin(fmin(p1.x(), p2.x()), p3.x());
            auto min_y = fmin(fmin(p1.y(), p2.y()), p3.y());
            auto min_z = fmin(fmin(p1.z(), p2.z()), p3.z());

            return Box(interval(min_x, max_x), interval(min_y, max_y), interval(min_z, max_z));
        }
       
        double fmax(const double& a, const double& b) const
        {
            return a > b ? a : b;
        }

        double fmin(const double& a, const double& b) const
        {
            return a > b ? b : a;
        }

    };
}

Primitive raytracer::primitives::triangle(math::Point3D p1, math::Point3D p2, math::Point3D p3)
{
    return Primitive(std::make_shared<TriangleImplementation>(p1, p2, p3));
}
