#include "samplers/stratified-half-jittered-sampler.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
	class HalfJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
	{

	public:
		HalfJitteredSampler(unsigned n, unsigned m) {
			this->n = n;
			this->m = m;
		}

	private:
		int n;
		int m;

	public:
		void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
		{

			std::default_random_engine generator;
			std::uniform_real_distribution<double> distribution(0.25, 0.75);

			for (int i = 0; i != this->n; i++)
			{
				for (int j = 0; j != this->m; j++)
				{
					auto x = distribution(generator);
					auto y = distribution(generator);
					function(rectangle.from_relative(Point2D((x + i) / n, (y + j) / m)));
				}
			}
		}
	};
}

Sampler raytracer::samplers::stratified_half_jittered(unsigned rows, unsigned columns)
{
	return Sampler(std::make_shared<HalfJitteredSampler>(rows, columns));
}