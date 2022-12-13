#include "primitives/rectangle-primitive.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class CoordinateRectangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    protected:
        const Vector3D m_normal;

        double x_size;
        double y_size;
        double z_size;

        double xhalf;
        double yhalf;
        double zhalf;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="normal">
        /// Normal vector on plane. Needs to have unit length.
        /// </param>
        CoordinateRectangleImplementation(const Vector3D& normal, double x_size, double y_size, double z_size)
            : m_normal(normal), x_size(x_size), y_size(y_size), z_size(z_size), xhalf(x_size / 2), yhalf(y_size / 2), zhalf(y_size / 2)
        {


            assert(normal.is_unit());
        }

        virtual void initialize_hit(Hit* hit, const Ray& ray, double t) const = 0;

    public:
        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            // Compute denominator
            double denom = ray.direction.dot(m_normal);

            // If denominator == 0, there is no intersection (ray runs parallel to plane)
            if (denom != approx(0.0))
            {
                // Compute numerator
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

                // Compute t
                double t = numer / denom;

                // Create hit object
                auto hit = std::make_shared<Hit>();

                // shared_ptr<T>::get() returns the T* inside the shared pointer
                initialize_hit(hit.get(), ray, t);

              

                if (
                    hit->local_position.xyz.x() <= xhalf && hit->local_position.xyz.x() >= -xhalf &&
                    hit->local_position.xyz.y() <= yhalf && hit->local_position.xyz.y() >= -yhalf &&
                    hit->local_position.xyz.z() <= zhalf && hit->local_position.xyz.z() >= -zhalf
                    )
                {
                    // Put hit in list
                    hits.push_back(hit);
                }
            }
            return hits;
        }
    };


    class XYRectangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    private:
        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
            hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
        }

        double x_size;
        double y_size;

        const Vector3D m_normal;

    public:

        XYRectangleImplementation(double x_size, double y_size) : m_normal(0, 0, 1), x_size(x_size), y_size(y_size)
        {
            // NOP
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            // Compute denominator
            double denom = ray.direction.dot(m_normal);

            // If denominator == 0, there is no intersection (ray runs parallel to plane)
            if (denom != approx(0.0))
            {
                // Compute numerator
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

                // Compute t
                double t = numer / denom;

                // Create hit object
                auto hit = std::make_shared<Hit>();

                // shared_ptr<T>::get() returns the T* inside the shared pointer
                initialize_hit(hit.get(), ray, t);

                if (!(hit->position.x() < 0 || hit->position.x() > x_size || hit->position.y() < 0 || hit->position.y() > y_size))
                {
                    // Put hit in list
                    hits.push_back(hit);
                }
            }
            return hits;
        }

        math::Box bounding_box() const override
        {
            return Box(Interval<double>(0, x_size), Interval<double>(0, y_size), Interval<double>(0, 0));
        }
    };

    class XZRectangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    protected:
        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
            hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
        }

        double x_size;
        double z_size;

        const Vector3D m_normal;

    public:

        XZRectangleImplementation(double x_size, double z_size) : m_normal(Vector3D(0, 1, 0)), x_size(x_size), z_size(z_size)
        {
            // NOP
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            // Compute denominator
            double denom = ray.direction.dot(m_normal);

            // If denominator == 0, there is no intersection (ray runs parallel to plane)
            if (denom != approx(0.0))
            {
                // Compute numerator
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

                // Compute t
                double t = numer / denom;

                // Create hit object
                auto hit = std::make_shared<Hit>();

                // shared_ptr<T>::get() returns the T* inside the shared pointer
                initialize_hit(hit.get(), ray, t);

                if (!(hit->position.x() < 0 || hit->position.x() > x_size || hit->position.z() < 0 || hit->position.z() > z_size))
                {
                    // Put hit in list
                    hits.push_back(hit);
                }
            }
            return hits;
        }

        math::Box bounding_box() const override
        {
            return Box(Interval<double>(0, x_size), Interval<double>(0, 0), Interval<double>(0, z_size));
        }
    };

    class YZRectangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    protected:
        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
            hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
        }

        double y_size;
        double z_size;

        const Vector3D m_normal;

    public:

        YZRectangleImplementation(double y_size, double z_size) : m_normal(Vector3D(1, 0, 0)), y_size(y_size), z_size(z_size)
        {
            // NOP
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            // Compute denominator
            double denom = ray.direction.dot(m_normal);

            // If denominator == 0, there is no intersection (ray runs parallel to plane)
            if (denom != approx(0.0))
            {
                // Compute numerator
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

                // Compute t
                double t = numer / denom;

                // Create hit object
                auto hit = std::make_shared<Hit>();

                // shared_ptr<T>::get() returns the T* inside the shared pointer
                initialize_hit(hit.get(), ray, t);

                if (!(hit->position.y() < 0 || hit->position.y() > y_size || hit->position.z() < 0 || hit->position.z() > z_size))
                {
                    // Put hit in list
                    hits.push_back(hit);
                }
            }
            return hits;
        }

        math::Box bounding_box() const override
        {
            return Box(Interval<double>(0,0), Interval<double>(0, y_size), Interval<double>(0, z_size));
        }
    };
}

Primitive raytracer::primitives::xy_rectangle(double x_size, double y_size)
{
    return Primitive(std::make_shared<XYRectangleImplementation>(x_size, y_size));
}

Primitive raytracer::primitives::xz_rectangle(double x_size, double z_size)
{
    return Primitive(std::make_shared<XZRectangleImplementation>(x_size, z_size));
}

Primitive raytracer::primitives::yz_rectangle(double y_size, double z_size)
{
    return Primitive(std::make_shared<YZRectangleImplementation>(y_size, z_size));
}
