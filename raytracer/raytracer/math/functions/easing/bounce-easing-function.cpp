#include "math/functions/easing/bounce-easing-function.h"
#include "math/functions/easing-functions.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::bounce(double f, double d)
{
    std::function<double(double)> lambda = [f,d](double t) -> double {
        assert(interval(0.0, 1.0).contains(t));
        
        auto ease = (-cos(f * t)) / (t * d + 1);

        return -abs(ease) + 1;
    };

    return from_lambda(lambda);
}
