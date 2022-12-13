#include "primitives/cube-primitive.h"
#include "primitives/box-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


Primitive raytracer::primitives::cube()
{
    return box(1,1,1);
}


