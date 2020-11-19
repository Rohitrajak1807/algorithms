//
// Created on 11/19/20.
//

#ifndef ELEMENTS_CARTESIANPOINT2D_H
#define ELEMENTS_CARTESIANPOINT2D_H

#include "PolarPoint2D.h"

namespace Elements {
    struct CartesianPoint2D {
    private:
        double x;
        double y;
        PolarPoint2D polar;
    public:
        CartesianPoint2D(double x, double y);

        CartesianPoint2D();

        [[nodiscard]] double get_x() const;

        [[nodiscard]] double get_y() const;

        void set_x(double p_x);

        void set_y(double p_y);
    };
}
#endif //ELEMENTS_CARTESIANPOINT2D_H