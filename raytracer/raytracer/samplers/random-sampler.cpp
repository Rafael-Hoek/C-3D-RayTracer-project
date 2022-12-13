#include "samplers/random-sampler.h"

using namespace math;
using namespace raytracer;


namespace
{
    class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    private:
        int n;
        mutable std::default_random_engine eng;
        std::uniform_real_distribution<double> distr;
    public:
        RandomSampler(int n) : n(n), distr(0,1) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {

            for (int i = 0; i < n; i++) {
                auto randX = distr(eng);
                auto randY = distr(eng);
                auto point = rectangle.from_relative(Point2D(randX, randY));
                function(point);
            }
        }
    };
}

Sampler raytracer::samplers::random(int n)
{
    return Sampler(std::make_shared<RandomSampler>(n));
}
