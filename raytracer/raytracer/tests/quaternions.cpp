#ifdef TEST_BUILD
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "math/quaternion.h"

#include <iostream>
#include <vector>
#include <algorithm>

#define Q(a, b, c, d)       (a, b, c, d)

#define TEST_ADDITION(q1, q2, qe)                                \
    TEST_CASE("Addition of "#q1 " and " #q2 " should give " #qe) \
    {                                                            \
       math::Quaternion quat1 q1;                                \
       math::Quaternion quat2 q2;                                \
       math::Quaternion expected qe;                             \
       SECTION("Using operator +")                               \
       {                                                         \
           math::Quaternion actual = quat1 + quat2;              \
           CHECK(actual == expected);                            \
       }                                                         \
       SECTION("Using operator +=")                              \
       {                                                         \
           quat1 += quat2;                                       \
           CHECK(quat1 == expected);                             \
       }                                                         \
    }

#define TEST_SUBTRACTION(q1, q2, qe)                                \
    TEST_CASE("Subtraction of "#q1 " and " #q2 " should give " #qe) \
    {                                                            \
       math::Quaternion quat1 q1;                                \
       math::Quaternion quat2 q2;                                \
       math::Quaternion expected qe;                             \
       SECTION("Using operator -")                               \
       {                                                         \
           math::Quaternion actual = quat1 - quat2;              \
           CHECK(actual == expected);                            \
       }                                                         \
       SECTION("Using operator -=")                              \
       {                                                         \
           quat1 -= quat2;                                       \
           CHECK(quat1 == expected);                             \
       }                                                         \
    }

#define TEST_MULTIPLICATION_REALS(q, r, qe)                       \
    TEST_CASE("Multiplication of "#q " and " #r " should give " #qe)\
    {                                                            \
       math::Quaternion quat q;                                  \
       math::Quaternion expected qe;                             \
       SECTION("Using operator q * r")                           \
       {                                                         \
           math::Quaternion actual = quat*r;                     \
           CHECK(actual == expected);                            \
       }                                                         \
       SECTION("Using operator r * q")                           \
       {                                                         \
           math::Quaternion actual = r*quat;                     \
           CHECK(actual == expected);                            \
       }                                                         \
       SECTION("Using operator *=")                              \
       {                                                         \
           quat*=r;                                              \
           CHECK(quat == expected);                              \
       }                                                         \
    }

#define TEST_MULTIPLICATION_QUATERNIONS(q1, q2, qe)              \
    TEST_CASE("Multiplication of "#q1 " and " #q2 " should give " #qe)\
    {                                                            \
       math::Quaternion quat1 q1;                                \
       math::Quaternion quat2 q2;                                \
       math::Quaternion expected qe;                             \
       SECTION("Using operator q1 * q2")                         \
       {                                                         \
           math::Quaternion actual = quat1*quat2;                \
           CHECK(actual == expected);                            \
       }                                                         \
    }

#define AXIS(x, y, z)     (x, y, z)
#define POINT(x, y, z)    (x, y, z)

#define TEST_ROTATION(axis_, angle_, point_, expected_)                        \
    TEST_CASE("Rotation of " #point_ " by " #angle_ " degrees around " #axis_) \
    {                                                                          \
      math::Vector3D axis axis_;                                               \
      math::Angle angle = math::Angle::degrees(angle_);                        \
      math::Point3D point point_;                                              \
      math::Point3D expected expected_;                                        \
      math::Quaternion quaternion = math::Quaternion::rotation(angle, axis);   \
      math::Point3D actual = quaternion.rotate(point);                         \
      CHECK(actual == approx(expected));                                       \
    }

// Test cases

TEST_ADDITION(Q(0, 0, 0, 0), Q(0, 0, 0, 0), Q(0, 0, 0, 0))
TEST_ADDITION(Q(1, 0, 0, 0), Q(0, 0, 0, 0), Q(1, 0, 0, 0))
TEST_ADDITION(Q(0, 1, 0, 0), Q(0, 0, 0, 0), Q(0, 1, 0, 0))
TEST_ADDITION(Q(0, 0, 1, 0), Q(0, 0, 0, 0), Q(0, 0, 1, 0))
TEST_ADDITION(Q(0, 0, 0, 1), Q(0, 0, 0, 0), Q(0, 0, 0, 1))
TEST_ADDITION(Q(3, 5, 2, 1), Q(7, 4, 2, 6), Q(10, 9, 4, 7))

TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 0, 0, 0), Q(0, 0, 0, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(1, 0, 0, 0), Q(-1, 0, 0, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 1, 0, 0), Q(0, -1, 0, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 0, 1, 0), Q(0, 0, -1, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 0, 0, 1), Q(0, 0, 0, -1))
TEST_SUBTRACTION(Q(3, 5, 2, 1), Q(7, 4, 2, 6), Q(-4, 1, 0, -5))

TEST_MULTIPLICATION_REALS(Q(0, 0, 0, 0), 5, Q(0, 0, 0, 0))
TEST_MULTIPLICATION_REALS(Q(1, 0, 0, 0), 5, Q(5, 0, 0, 0))
TEST_MULTIPLICATION_REALS(Q(0, 1, 0, 0), 3, Q(0, 3, 0, 0))
TEST_MULTIPLICATION_REALS(Q(0, 0, 1, 0), 7, Q(0, 0, 7, 0))
TEST_MULTIPLICATION_REALS(Q(0, 0, 0, 1), 4, Q(0, 0, 0, 4))
TEST_MULTIPLICATION_REALS(Q(1, 2, 3, 4), 2, Q(2, 4, 6, 8))

TEST_MULTIPLICATION_QUATERNIONS(Q(1, 0, 0, 0), Q(1, 0, 0, 0), Q(1, 0, 0, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(1, 0, 0, 0), Q(0, 1, 0, 0), Q(0, 1, 0, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(1, 0, 0, 0), Q(0, 0, 1, 0), Q(0, 0, 1, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(1, 0, 0, 0), Q(0, 0, 0, 1), Q(0, 0, 0, 1))

TEST_MULTIPLICATION_QUATERNIONS(Q(0, 1, 0, 0), Q(1, 0, 0, 0), Q(0, 1, 0, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 1, 0, 0), Q(0, 1, 0, 0), Q(-1, 0, 0, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 1, 0, 0), Q(0, 0, 1, 0), Q(0, 0, 0, 1))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 1, 0, 0), Q(0, 0, 0, 1), Q(0, 0, -1, 0))

TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 1, 0), Q(1, 0, 0, 0), Q(0, 0, 1, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 1, 0), Q(0, 1, 0, 0), Q(0, 0, 0, -1))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 1, 0), Q(0, 0, 1, 0), Q(-1, 0, 0, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 1, 0), Q(0, 0, 0, 1), Q(0, 1, 0, 0))

TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 0, 1), Q(1, 0, 0, 0), Q(0, 0, 0, 1))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 0, 1), Q(0, 1, 0, 0), Q(0, 0, 1, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 0, 1), Q(0, 0, 1, 0), Q(0, -1, 0, 0))
TEST_MULTIPLICATION_QUATERNIONS(Q(0, 0, 0, 1), Q(0, 0, 0, 1), Q(-1, 0, 0, 0))

TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(1, 0, 0), 270, POINT(1, 0, 0), POINT(1, 0, 0))

TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(1, 0, 0), POINT(0, 0, -1))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(1, 0, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 270, POINT(1, 0, 0), POINT(0, 0, 1))

TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(1, 0, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(1, 0, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 0, 1), 270, POINT(1, 0, 0), POINT(0, -1, 0))

TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(0, 1, 0), POINT(0, 0, 1))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(0, 1, 0), POINT(0, -1, 0))
TEST_ROTATION(AXIS(1, 0, 0), 270, POINT(0, 1, 0), POINT(0, 0, -1))

TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(0, 1, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(0, 1, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 1, 0), 270, POINT(0, 1, 0), POINT(0, 1, 0))

TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(0, 1, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(0, 1, 0), POINT(0, -1, 0))
TEST_ROTATION(AXIS(0, 0, 1), 270, POINT(0, 1, 0), POINT(1, 0, 0))

TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(0, 0, 1), POINT(0, -1, 0))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(0, 0, 1), POINT(0, 0, -1))
TEST_ROTATION(AXIS(1, 0, 0), 270, POINT(0, 0, 1), POINT(0, 1, 0))

TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(0, 0, 1), POINT(1, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(0, 0, 1), POINT(0, 0, -1))
TEST_ROTATION(AXIS(0, 1, 0), 270, POINT(0, 0, 1), POINT(-1, 0, 0))

TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(0, 0, 1), POINT(0, 0, 1))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(0, 0, 1), POINT(0, 0, 1))
TEST_ROTATION(AXIS(0, 0, 1), 270, POINT(0, 0, 1), POINT(0, 0, 1))

#endif