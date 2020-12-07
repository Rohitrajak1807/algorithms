//
// Created by on 11/21/20.
//

#include "Elements.h"
#include <cmath>
#include <iostream>

double Elements::cross_product(const CartesianPoint2D x1, const CartesianPoint2D x2) {
    return (x1.get_x() * x2.get_y()) - (x2.get_x() * x1.get_y());
}

double Elements::distance(CartesianPoint2D x1, CartesianPoint2D x2) {
    double x = x1.get_x() -x2.get_x();
    double y = x1.get_y() -x2.get_y();
    return sqrt((x * x) + (y * y));
}

Elements::PolarPoint2D Elements::to_polar_point(const CartesianPoint2D &p) {
    const double& x = p.get_x();
    const double& y = p.get_y();
    double radius = sqrt((x * x) + (y * y));
    double angle = atan(y / x);
    return PolarPoint2D(radius, angle);
}
