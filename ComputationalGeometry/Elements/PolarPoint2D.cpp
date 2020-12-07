//
// Created by on 11/19/20.
//

#include "PolarPoint2D.h"

double Elements::PolarPoint2D::get_radius() const {
    return radius;
}

void Elements::PolarPoint2D::set_radius(double radius_p) {
    PolarPoint2D::radius = radius_p;
}

double Elements::PolarPoint2D::get_angle() const {
    return angle;
}

void Elements::PolarPoint2D::set_angle(double angle_p) {
    PolarPoint2D::angle = angle_p;
}

Elements::PolarPoint2D::PolarPoint2D(double radius, double angle) : radius(radius), angle(angle) {}

Elements::PolarPoint2D::PolarPoint2D() : radius(0), angle(0) {}
