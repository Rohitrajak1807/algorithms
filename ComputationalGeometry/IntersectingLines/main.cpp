#include <iostream>
#include "Elements/Elements.h"

bool segments_intersect(const Elements::CartesianLine2D &l1, const Elements::CartesianLine2D &l2);

double direction(const Elements::CartesianLine2D &line, const Elements::CartesianPoint2D &point);

bool on_segment(const Elements::CartesianLine2D &line, const Elements::CartesianPoint2D &point);

int main() {
    Elements::CartesianPoint2D p1(1, 1), p2(3, 5);
    Elements::CartesianPoint2D q1(-4, 4), q2(4, 4);
    Elements::CartesianLine2D l1(p1, p2), l2(q1, q2);
    std::cout << segments_intersect(l1, l2);
    return 0;
}

bool segments_intersect(const Elements::CartesianLine2D &l1, const Elements::CartesianLine2D &l2) {
    double d1, d2, d3, d4;
    d1 = direction(l2, l1.get_start());
    d2 = direction(l2, l1.get_end());
    d3 = direction(l1, l1.get_start());
    d4 = direction(l1, l1.get_end());

    if ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0) || (d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)) {
        return true;
    } else if ((d1 == 0 && on_segment(l2, l1.get_start())) || (d2 == 0 && on_segment(l2, l1.get_end())) ||
               (d3 == 0 && on_segment(l1, l2.get_start())) || (d4 == 0 && on_segment(l2, l1.get_end())))
        return true;
    return false;
}

double direction(const Elements::CartesianLine2D &line, const Elements::CartesianPoint2D &point) {
    return ((line.get_start().get_x() - point.get_x()) * (line.get_end().get_y() - line.get_start().get_y())) -
           ((line.get_start().get_y() - point.get_y()) * (line.get_end().get_x() - line.get_start().get_x()));
}

bool on_segment(const Elements::CartesianLine2D &line, const Elements::CartesianPoint2D &point) {
    return std::min(line.get_start().get_x(), line.get_end().get_x()) <= point.get_x() &&
           point.get_x() <= std::max(line.get_start().get_x(), line.get_end().get_x()) &&
           std::min(line.get_start().get_y(), line.get_end().get_y()) <= point.get_y() &&
           point.get_y() <= std::max(line.get_start().get_y(), line.get_end().get_y());
}