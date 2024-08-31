//
// Created by marina on 31.08.24.
//
#pragma once

#include <cmath>
#include <stdexcept>

namespace geometry {
    /**
     * @class point
     * @brief represents a point in the space
     *
     * three double fields: x, y and z coordinates
     */
    struct point {
        point(double x, double y, double z) : x(x), y(y), z(z) {}

        bool operator==(const point &other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        point operator+(const point &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        point operator-(const point &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        point operator*(const double k) const {
            return {x * k, y * k, z * k};
        }

        double x;
        double y;
        double z;
    };

    point operator*(double k, const point &p);

    /**
     * @class plane
     * @brief represents a plane in the space
     *
     * The plane is defined by its normal vector (a, b, c) and the constant d in the plane equation `ax + by + cz + d = 0`.
     *
     * four double fields: a, b, c, and d coeffs of a normal equation
     */
    struct plane {
        double a;
        double b;
        double c;
        double d;

        plane(point &M, point &N, point &K);

        plane(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

        bool operator==(const plane &other) const {
            return a == other.a && b == other.b && c == other.c && d == other.d;
        }
    };

    /**
    * @class circle
    * @brief represents a circle on the plane in the space
    *
    * The circle is defined by its center, radius, and plane of the circle.
    */
    struct circle {
        point O;
        double r;
        plane P;

        circle(point &O, double r, plane &P) : O(O), r(r), P(P) {}
    };

    /**
     * @brief Calculates the projection of a point onto a plane.
     *
     * This method calculates the orthogonal projection of a given point onto a specified plane in 3D space.
     *
     * @param A The point object representing the point to be projected.
     * @param P The plane object representing the plane onto which the point is projected.
     *
     * @return point The point object representing the projection of the input point onto the plane.
     */
    point projectionOnPlane(point A, plane P);

    /**
     * @brief Calculates the length (magnitude) of a vector from the origin to the given point.
     *
     * This method calculates the Euclidean distance from the origin (0, 0, 0) to the given point in 3D space.
     *
     * @param v The point object representing the endpoint of the vector.
     *
     * @return double The length of the vector from the origin to the given point.
     */
    double vectorLen(const point &v);

    /**
     * @brief Checks if point belongs to a circle
     *
     * @param toO The Point object representing the endpoint of the vector.
     * @param r The radius of the circle
     *
     * @return true if the point belongs to a circle and false otherwise
     */
    bool isOnCP(point &toO, double r);

    /**
     * @brief Calculates the closest point on a circle to a given point in 3D space.
     *
     * This method determines the nearest point on a specified circle to a given point in 3D space.
     * The returned point lies on the circumference of the circle and is the closest point to the input point.
     *
     * @param point The Point object representing the point from which the nearest point on the circle is calculated.
     * @param circle The Circle object representing the circle in 3D space.
     * @return Point The Point object representing the closest point on the circle to the input point.
     */
    point nearestPointOnCircle(point A, circle C);

} // namespace geometry
