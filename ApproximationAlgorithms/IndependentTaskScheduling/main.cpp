#include <iostream>
#include <vector>

int32_t schedule(std::vector<int32_t> tasks, int32_t machine_count);

int main() {
    std::vector<int32_t> tasks{2, 4, 33, 22, 69, 32, 31, 40, 20, 50, 88};
    int32_t machine_count = 5;
    std::cout << schedule(tasks, machine_count);
    return 0;
}

int32_t schedule(std::vector<int32_t> tasks, int32_t machine_count) {
    std::sort(tasks.begin(), tasks.end(), std::greater<>());
    std::vector<int32_t> make_spans(machine_count, 0);
    for (int32_t &i : tasks) {
        auto least_loaded_machine = std::min_element(make_spans.begin(), make_spans.end());
        *least_loaded_machine += i;
    }
    return *std::max_element(make_spans.begin(), make_spans.end());
}
