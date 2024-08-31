//
// Created by marina on 31.08.24.
//
#include <iostream>
#include "../include/geometry.h"

geometry::plane::plane(point &M, point &N, point &K) {
    a = (N.y - M.y) * (K.z - M.z) - (N.z - M.z) * (K.y - M.y);
    b = (N.z - M.z) * (K.x - M.x) - (N.x - M.x) * (K.z - M.z);
    c = (N.x - M.x) * (K.y - M.y) - (N.y - M.y) * (K.x - M.x);
    d = -(a * M.x + b * M.y + c * M.z);
}

geometry::point geometry::operator*(const double k, const geometry::point &p) {
    return {p.x * k, p.y * k, p.z * k};
}

geometry::point geometry::projectionOnPlane(geometry::point A, geometry::plane P) {
    double norm_squared = P.a * P.a + P.b * P.b + P.c * P.c;

    if (std::fabs(norm_squared) < std::numeric_limits<double>::epsilon()) {
        throw std::runtime_error("Norm of the normal vector is too small, precision may be compromised.");
    }

    double t = -(P.a * A.x + P.b * A.y + P.c * A.z + P.d) / norm_squared;

    return {A.x + P.a * t, A.y + P.b * t, A.z + P.c * t};
}

double geometry::vectorLen(const geometry::point &v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

bool geometry::isOnCP(geometry::point &toO, double r) {
    return vectorLen(toO) <= r;
}

geometry::point geometry::nearestPointOnCircle(geometry::point A, geometry::circle C) {
    point Ap = projectionOnPlane(A, C.P);
    point vecApO(C.O.x - Ap.x, C.O.y - Ap.y, C.O.z - Ap.z);
    if (isOnCP(vecApO, C.r)) {
        return Ap;
    }
    double k = C.r / vectorLen(vecApO);
    return C.O - k * vecApO;
}
