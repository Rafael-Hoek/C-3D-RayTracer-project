#include "primitives/square-primitive.h"
#include "primitives/rectangle-primitive.h"
#include "primitives/box-primitive.h"
#include "primitives/transformer-primitive.h"
#include "primitives/union-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

Primitive raytracer::primitives::box(double x_size, double y_size, double z_size)
{
    std::vector<Primitive> primitives;

    auto a = xy_rectangle(x_size, y_size);
    auto a2 = translate(Vector3D(0, 0, z_size), xy_rectangle(x_size, y_size));
    auto b = xz_rectangle(x_size, z_size);
    auto b2 = translate(Vector3D(0, y_size, 0), xz_rectangle(x_size, z_size));
    auto c = yz_rectangle(y_size, z_size);
    auto c2 = translate(Vector3D(x_size, 0, 0), yz_rectangle(y_size, z_size));

    primitives.push_back(a);
    primitives.push_back(a2);
    primitives.push_back(b);
    primitives.push_back(b2);
    primitives.push_back(c);
    primitives.push_back(c2);

    return translate( Vector3D(-x_size / 2, -y_size / 2, -z_size / 2), make_union(primitives));
    
}

