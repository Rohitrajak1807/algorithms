//
// Created on 12/4/20.
//

#ifndef ELEMENTS_CARTESIANLINE2D_H
#define ELEMENTS_CARTESIANLINE2D_H
#include "CartesianPoint2D.h"

namespace Elements {
    class CartesianLine2D {
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
}

#endif //ELEMENTS_CARTESIANLINE2D_H
