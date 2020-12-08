#include <iostream>
#include <set>
#include <vector>

std::vector<std::set<int32_t>> greedy_set_cover(std::set<int32_t> x, const std::vector<std::set<int32_t>> &f);

size_t max_set_intersect(std::set<int32_t> &x, const std::vector<std::set<int32_t>> &f);

void remove_elements(std::set<int32_t> &x, const std::set<int32_t> &intersection);

int main() {
    std::set<int32_t> x{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::set<int32_t>> f{
            {1, 8,  10},
            {2, 10, 5,  6},
            {4},
            {7, 9,  10, 1},
            {3},
            {1, 2,  3,  4, 5},
            {6, 7,  8,  9, 10}
    };
    auto result = greedy_set_cover(x, f);
    for (auto &i : result) {
        for (auto &j : i) {
            std::cout << j << '\t';
        }
        std::cout << '\n';
    }
    return 0;
}

std::vector<std::set<int32_t>> greedy_set_cover(std::set<int32_t> x, const std::vector<std::set<int32_t>> &f) {
    std::vector<std::set<int32_t>> c;
    auto x1 = f[1];
    while (!x.empty()) {
        size_t intersection = max_set_intersect(x, f);
        remove_elements(x, f.at(intersection));
        c.emplace_back(f.at(intersection));
    }
    return c;
}

size_t max_set_intersect(std::set<int32_t> &x, const std::vector<std::set<int32_t>> &f) {
    size_t intersect_size = 0;
    size_t idx = 0;
    size_t j = 0;
    for (auto &i : f) {
        std::vector<int32_t> curr;
        std::set_intersection(x.begin(), x.end(), i.begin(), i.end(), std::back_inserter(curr));
        if (intersect_size < curr.size()) {
            intersect_size = curr.size();
            idx = j;
        }
        ++j;
    }
    return idx;
}

void remove_elements(std::set<int32_t> &x, const std::set<int32_t> &intersection) {
    for (auto &i : intersection) {
        if (x.find(i) != x.end()) {
            x.erase(i);
        }
    }
}