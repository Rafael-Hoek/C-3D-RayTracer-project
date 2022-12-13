#include "math/functions/easing/elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::elastic(double f, double d)
{
    std::function<double(double)> lambda = [f,d](double t) -> double {
        assert(interval(0.0, 1.0).contains(t));

        return
            (-cos(f * t)) / (t * d + 1) + 1;

    };
    return from_lambda(lambda); 
}
