//
// Created by ronin on 11/21/20.
//

#ifndef ELEMENTS_ELEMENTS_H
#define ELEMENTS_ELEMENTS_H

namespace Elements {
    class CartesianLine2D;
    struct CartesianPoint2D;
    struct PolarPoint2D;

    PolarPoint2D to_polar_point(const CartesianPoint2D &p);
};

struct Elements::CartesianPoint2D {
private:
    double x;
    double y;
public:
    CartesianPoint2D(double x, double y);

    CartesianPoint2D();

    [[nodiscard]] double get_x() const;

    [[nodiscard]] double get_y() const;

    void set_x(double p_x);

    void set_y(double p_y);
};

struct Elements::PolarPoint2D {
private:
    double radius;
    double angle;
public:
    PolarPoint2D(double radius, double angle);

    PolarPoint2D();

    [[nodiscard]] double get_radius() const;

    [[nodiscard]] double get_angle() const;

    void set_radius(double radius);

    void set_angle(double angle);
};

class Elements::CartesianLine2D {
private:
    CartesianPoint2D start_point;
    CartesianPoint2D end_point;
public:
    CartesianLine2D(const CartesianPoint2D &start_point, const CartesianPoint2D &end_point);

    [[nodiscard]] const CartesianPoint2D &get_start() const;

    [[nodiscard]] const CartesianPoint2D &get_end() const;

    void set_start(const CartesianPoint2D &startPoint);

    void set_end(const CartesianPoint2D &endPoint);
};

#endif //ELEMENTS_ELEMENTS_H
