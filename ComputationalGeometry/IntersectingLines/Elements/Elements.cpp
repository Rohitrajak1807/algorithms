//
// Created by ronin on 11/21/20.
//

#include "Elements.h"
#include <cmath>


Elements::PolarPoint2D Elements::to_polar_point(const CartesianPoint2D &p) {
    const double& x = p.get_x();
    const double& y = p.get_y();

    double radius = sqrt((x * x) + (y * y));
    double angle = atan(y / x);
    return PolarPoint2D(radius, angle);
}