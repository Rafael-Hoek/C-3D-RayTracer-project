#include "stratisfied-sampler.h"

using namespace math;
using namespace raytracer;

namespace
{
    class StratifiedSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    private:
        unsigned n;
        unsigned m;
        
    public:
        StratifiedSampler(unsigned n, unsigned m) : n(n), m(m) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {

            auto raster = Rasterizer(rectangle, n, m);

            for (unsigned x = 0; x < raster.vertical_subdivisions(); x++)
            {
                for (unsigned y = 0; y < raster.horizontal_subdivisions(); y++)
                {
                    function(raster[Position2D(x, y)].center());
                }
            }
        }
    };
}

Sampler raytracer::samplers::stratified(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratifiedSampler>(rows, columns));
}