//
// Created by ronin on 11/21/20.
//

#ifndef ELEMENTS_ELEMENTS_H
#define ELEMENTS_ELEMENTS_H

#include "CartesianPoint2D.h"
#include "PolarPoint2D.h"

namespace Elements {
    double cross_product(CartesianPoint2D x1, CartesianPoint2D x2);
    double distance(CartesianPoint2D x1, CartesianPoint2D x2);
    PolarPoint2D to_polar_point(const CartesianPoint2D &p);
    const CartesianPoint2D origin = CartesianPoint2D();
}





#endif //ELEMENTS_ELEMENTS_H
