#include "primitives/group-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace {

	class GrouperImplementation : public raytracer::primitives::_private_::PrimitiveImplementation {
	protected:
		unsigned id;
		Primitive child;

	public:
		GrouperImplementation(unsigned id, Primitive child) : id(id), child(child) { }

		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			auto hits = child->find_all_hits(ray);
			for (auto hit : hits) {
				hit->group_id = id;
			}
			return hits;
		}

		math::Box bounding_box() const override
		{
			return child->bounding_box();
		}

	};

}

Primitive raytracer::primitives::group(unsigned id, Primitive child) {
	return Primitive(std::make_shared<GrouperImplementation>(id, child));
}