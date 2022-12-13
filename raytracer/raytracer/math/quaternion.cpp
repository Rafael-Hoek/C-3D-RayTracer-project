#include "math/quaternion.h"

using namespace math;

math::Quaternion::Quaternion(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) { }

Quaternion math::Quaternion::rotation(Angle theta, const Vector3D& axis)
{
	return Quaternion(cos(theta/2), sin(theta/2) * axis.x(), sin(theta/2) * axis.y(), sin(theta/2) * axis.z() );
}

Point3D math::Quaternion::rotate(const Point3D point)
{
	auto resultQ = *this * Quaternion(0, point.x(), point.y(), point.z()) * this->conjugate();
	return Point3D(resultQ.b, resultQ.c, resultQ.d);
}

Quaternion math::Quaternion::conjugate()
{
	return Quaternion(this->a, -this->b, -this->c, -this->d);
}

Quaternion math::operator+(const Quaternion& a, const Quaternion& b)
{
	return Quaternion(a.a + b.a, a.b + b.b, a.c + b.c, a.d + b.d);
}

Quaternion math::operator-(const Quaternion& a, const Quaternion& b)
{
	return Quaternion(a.a-b.a,a.b-b.b,a.c-b.c,a.d-b.d);
}

Quaternion math::operator*(Quaternion& a, Quaternion& b)
{
	double qa = a.a * b.a - a.b * b.b - a.c * b.c - a.d * b.d;
	double qb = a.a * b.b + a.b * b.a + a.c * b.d - a.d * b.c;
	double qc = a.a * b.c - a.b * b.d + a.c * b.a + a.d * b.b;
	double qd = a.a * b.d + a.b * b.c - a.c * b.b + a.d * b.a;
	return Quaternion(qa, qb, qc, qd);
}

Quaternion& math::operator+=(Quaternion& a, const Quaternion& b)
{
	return (a = a + b);
}

Quaternion& math::operator-=(Quaternion& a, const Quaternion& b)
{
	return (a = a - b);
}

Quaternion math::operator*(double a, const Quaternion& b)
{
	return Quaternion(a * b.a, a * b.b, a * b.c, a * b.d);
}

Quaternion math::operator*(const Quaternion& a, double b)
{
	return b*a;
}

Quaternion math::operator/(const Quaternion& a, double b)
{
	return Quaternion(a.a / b, a.b / b, a.c / b, a.d / b);
}

Quaternion& math::operator*=(Quaternion& a, double b)
{
	return (a = b*a);
}

Quaternion& math::operator/=(Quaternion& a, double b)
{
	return (a = a/b);
}

bool math::operator==(const Quaternion& a,const Quaternion& b)
{
	return a.a == b.a && a.b == b.b && a.c == b.c && a.d == b.d;
}

bool math::operator!=(const Quaternion& a, const Quaternion& b)
{
	return !(a == b);
}
