#pragma once
#include "math/angle.h"
#include "math/vector.h"
#include "math/point.h"

namespace math {

	struct Quaternion {
		double a, b, c, d;
		Quaternion(double a, double b, double c, double d);

		static Quaternion rotation(Angle theta, const Vector3D& axis);

		Point3D rotate(const Point3D point);
		Quaternion conjugate();
	};

	Quaternion operator + (const Quaternion& a, const Quaternion& b);
	Quaternion operator - (const Quaternion& a, const Quaternion& b);
	Quaternion operator * (Quaternion& a, Quaternion& b);
	Quaternion& operator += (Quaternion& a, const Quaternion& b);
	Quaternion& operator -= (Quaternion& a, const Quaternion& b);
	Quaternion operator * (double a, const Quaternion& b);
	Quaternion operator * (const Quaternion& a, double b);
	Quaternion operator / (const Quaternion& a, double b);
	Quaternion& operator *= (Quaternion& a, double b);
	Quaternion& operator /= (Quaternion& a, double b);
	bool operator == (const Quaternion& a, const Quaternion& b);
	bool operator != (const Quaternion& a, const Quaternion& b);

}