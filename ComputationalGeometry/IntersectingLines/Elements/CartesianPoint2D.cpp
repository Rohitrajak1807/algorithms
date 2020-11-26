//
// Created on 11/19/20.
//

#include <cmath>
#include "Elements.h"


double Elements::CartesianPoint2D::get_x() const {
    return x;
}

double Elements::CartesianPoint2D::get_y() const {
    return y;
}

void Elements::CartesianPoint2D::set_x(double p_x) {
    CartesianPoint2D::x = p_x;
}

void Elements::CartesianPoint2D::set_y(double p_y) {
    y = p_y;
}

Elements::CartesianPoint2D::CartesianPoint2D() : x(0), y(0) {}

Elements::CartesianPoint2D::CartesianPoint2D(double x, double y) : x(x), y(y) {}
