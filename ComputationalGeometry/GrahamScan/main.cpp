#include <iostream>
#include <vector>
#include <stack>
#include "Elements.h"
#include "CartesianPoint2D.h"

static Elements::CartesianPoint2D initial_point = Elements::origin;

std::stack<Elements::CartesianPoint2D> graham_scan(std::vector<Elements::CartesianPoint2D> points);

//returns the element below the top of stack
Elements::CartesianPoint2D below_top(std::stack<Elements::CartesianPoint2D> &points);

//determine the bottom most point ties are broken by considering leftmost point
size_t find_initial_point(std::vector<Elements::CartesianPoint2D> &points);

double orientation(Elements::CartesianPoint2D &p, Elements::CartesianPoint2D &q, Elements::CartesianPoint2D &r);

//sort by polar angle w.r.t points[0], i.e., initial_point
struct {
    bool operator()(Elements::CartesianPoint2D p1, Elements::CartesianPoint2D p2) {
        double cross_prod = Elements::cross_product(p1, p2);
        if (cross_prod != 0) {
            return cross_prod > 0;
        }
        double d1 = Elements::distance(p1, initial_point);
        double d2 = Elements::distance(p2, initial_point);
        return d1 < d2;
    }
} compare;


int main() {
    std::vector<Elements::CartesianPoint2D> points;
    points.emplace_back(0, 3);
    points.emplace_back(1, 1);
    points.emplace_back(2, 2);
    points.emplace_back(4, 4);
    points.emplace_back(0, 0);
    points.emplace_back(1, 2);
    points.emplace_back(3, 1);
    points.emplace_back(3, 3);
    std::stack<Elements::CartesianPoint2D> hull = graham_scan(points);
    while (!hull.empty()) {
        std::cout << hull.top().get_x() << ", " << hull.top().get_y() << '\n';
        hull.pop();
    }
    return 0;
}

std::stack<Elements::CartesianPoint2D> graham_scan(std::vector<Elements::CartesianPoint2D> points) {
    size_t min_idx = find_initial_point(points);
    std::swap(points[min_idx], points[0]);
    initial_point = points[0];
    std::sort(points.begin() + 1, points.end(), compare);
    std::stack<Elements::CartesianPoint2D> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);
    for (size_t i = 3; i < points.size(); ++i) {
        auto next_to_top = below_top(hull);
        auto top = hull.top();
        double direction = orientation(next_to_top, top, points[i]);
        if(direction >= 0) {
            hull.pop();
        }
        hull.push(points[i]);
    }
    return hull;
}

size_t find_initial_point(std::vector<Elements::CartesianPoint2D> &points) {
    size_t min_idx = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        auto &min = points[min_idx];
        if (points[i].get_y() < min.get_y()) {
            min_idx = i;
        } else if (points[i].get_y() == min.get_y()) {
            if (points[i].get_x() < min.get_x()) {
                min_idx = i;
            }
        }
    }
    return min_idx;
}

Elements::CartesianPoint2D below_top(std::stack<Elements::CartesianPoint2D> &points) {
    Elements::CartesianPoint2D top = points.top();
    points.pop();
    Elements::CartesianPoint2D result = points.top();
    points.push(top);
    return result;

}

double orientation(Elements::CartesianPoint2D &p, Elements::CartesianPoint2D &q, Elements::CartesianPoint2D &r) {
    return (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) -
            (q.get_x() - p.get_x()) * (r.get_y() - q.get_y());
}