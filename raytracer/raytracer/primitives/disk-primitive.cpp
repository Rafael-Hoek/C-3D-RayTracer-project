#include "primitives/disk-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace {

	class DiskImplementation : public raytracer::primitives::_private_::PrimitiveImplementation {
	protected:
		const math::Vector3D m_normal;
		const double m_radius;

		DiskImplementation(math::Vector3D normal, double radius) : m_normal(normal), m_radius(radius) { }

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

				if (distance(ray.at(t), Point3D(0, 0, 0)) < m_radius) {
					// Create hit object
					auto hit = std::make_shared<Hit>();

					// shared_ptr<T>::get() returns the T* inside the shared pointer
					initialize_hit(hit.get(), ray, t);

					// Put hit in list
					hits.push_back(hit);
				}
			}

			return hits;
		}

	};

	class DiskXYImplementation : public DiskImplementation {
	public:
		DiskXYImplementation(double radius) : DiskImplementation(Vector3D(0, 0, 1), radius) { }

		math::Box bounding_box() const override
		{
			return Box(interval(-m_radius, m_radius), interval(-m_radius, m_radius), interval(-0.01, 0.01));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override {
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
		}
	};

	class DiskXZImplementation : public DiskImplementation {
	public:
		DiskXZImplementation(double radius) : DiskImplementation(Vector3D(0, 1, 0), radius) { }

		math::Box bounding_box() const override
		{
			return Box(interval(-m_radius, m_radius), interval(-0.01, 0.01), interval(-m_radius, m_radius));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override {
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			hit->normal = ray.origin.y() > 0 ? m_normal : -m_normal;
		}
	};

	class DiskYZImplementation : public DiskImplementation {
	public:
		DiskYZImplementation(double radius) : DiskImplementation(Vector3D(1, 0, 0), radius) { }

		math::Box bounding_box() const override
		{
			return Box(interval(-0.01, 0.01), interval(-m_radius, m_radius), interval(-m_radius, m_radius));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override {
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
			hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
		}
	};
}

Primitive raytracer::primitives::xy_disk(double radius)
{
	return Primitive(std::make_shared<DiskXYImplementation>(radius));
}

Primitive raytracer::primitives::xz_disk(double radius)
{
	return Primitive(std::make_shared<DiskXZImplementation>(radius));
}

Primitive raytracer::primitives::yz_disk(double radius)
{
	return Primitive(std::make_shared<DiskYZImplementation>(radius));
}