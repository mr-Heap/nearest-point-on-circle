//
// Created by marina on 31.08.24.
//

#include "../include/geometry.h"
#include <gtest/gtest.h>


TEST(ProjectionOnPlane, Simple) {
    geometry::plane P(0, 0, 1, 0); // XOY

    geometry::point a(0, 0, 0);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), a);

    a = geometry::point(0, 0, 1);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(0, 0, 0));

    a = geometry::point(0, 0, 2);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(0, 0, 0));

    a = geometry::point(0, 5, 2);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(0, 5, 0));
}

TEST(ProjectionOnPlane, BigValues) {
    geometry::plane P(0, 0, 1, 0); // XOY

    geometry::point a(999999999999999, 999999999999999, 999999999999999);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(999999999999999, 999999999999999, 0));
}

TEST(ProjectionOnPlane, ObliquePlane) {
    geometry::plane P(1, 1, 1, 0); // 45 to XOY

    geometry::point a(0, 0, 0);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), a);

    a = geometry::point(1, 1, 1);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(0, 0, 0));

    a = geometry::point(6, 6, 3);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(1, 1, -2));

    a = geometry::point(-6, -6, -3);
    EXPECT_EQ(geometry::projectionOnPlane(a, P), geometry::point(-1, -1, 2));
}

TEST(NearestPointOnCircle, BelongsToCircle) {
    geometry::plane P(0, 0, 1, 0); // XOY
    geometry::point zero(0, 0, 0);
    geometry::circle C(zero, 1, P);

    geometry::point a(0, 0, 0);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), a);

    a = geometry::point(1, 0, 0);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), a);

    a = geometry::point(0.5, 0.03, 0);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), a);

    a = geometry::point(0.000000001, 0.000000001, 0);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), a);

    C = geometry::circle(zero, 999999999999999, P);
    a = geometry::point(999999999999999, 999999, 0);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), a);
}

TEST(NearestPointOnCircle, ProjectionBelongsToCircle) {
    geometry::plane P(0, 0, 1, 0); // XOY
    geometry::point zero(0, 0, 0);
    geometry::circle C(zero, 1, P);

    geometry::point a(0, 0, 1);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(0, 0, 0));

    a = geometry::point(1, 0, 1);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(1, 0, 0));

    a = geometry::point(0.5, 0.03, 0.76);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(0.5, 0.03, 0));

    a = geometry::point(0.000000001, 0.000000001, 0.999999999999);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(0.000000001, 0.000000001, 0));

    C = geometry::circle(zero, 999999999999999, P);
    a = geometry::point(999999999999999, 999999, 999999999999999);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(999999999999999, 999999, 0));
}

TEST(NearestPointOnCircle, NotOnPlane) {
    geometry::plane P(0, 0, 1, 0); // XOY
    geometry::point zero(0, 0, 0);
    geometry::circle C(zero, 1, P);

    geometry::point a(0, -2, 1);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(0, -1, 0));

    a = geometry::point(0, 2, 1);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(0, 1, 0));

    a = geometry::point(2, 0, 1);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(1, 0, 0));

    a = geometry::point(-2, 0, 1);
    EXPECT_EQ(geometry::nearestPointOnCircle(a, C), geometry::point(-1, 0, 0));
}

int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
