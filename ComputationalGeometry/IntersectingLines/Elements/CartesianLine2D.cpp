//
// Created on 11/19/20.
//

#include "Elements.h"

const Elements::CartesianPoint2D& Elements::CartesianLine2D::get_start() const {
    return start_point;
}

const Elements::CartesianPoint2D& Elements::CartesianLine2D::get_end() const {
    return end_point;
}

void Elements::CartesianLine2D::set_start(const Elements::CartesianPoint2D &startPoint) {
    start_point = startPoint;
}

void Elements::CartesianLine2D::set_end(const Elements::CartesianPoint2D &endPoint) {
    end_point = endPoint;
}

Elements::CartesianLine2D::CartesianLine2D(const Elements::CartesianPoint2D &start_point, const Elements::CartesianPoint2D &end_point) : start_point(
        start_point), end_point(end_point) {}