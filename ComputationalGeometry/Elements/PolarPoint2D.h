//
// Created on 12/4/20.
//

#ifndef ELEMENTS_POLARPOINT2D_H
#define ELEMENTS_POLARPOINT2D_H
namespace Elements {
    struct PolarPoint2D {
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
}

#endif //ELEMENTS_POLARPOINT2D_H
