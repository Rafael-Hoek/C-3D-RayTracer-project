#include "primitives/bbacc.h"
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
    class BbaccImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    private:
        Primitive primitive;
        Box box;
    public:
      
        BbaccImplementation(Primitive primitive) : primitive(primitive), box(primitive->bounding_box())
        {
            // NOP
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {

            if (box.is_hit_by(ray))
            {
                return primitive->find_all_hits(ray);
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }

        }

        math::Box bounding_box() const override
        {
            return primitive->bounding_box();
        }
  
       
    };
}

Primitive raytracer::primitives::bounding_box_accelerator(Primitive primitive)
{
    return Primitive(std::make_shared<BbaccImplementation>(primitive));
}
