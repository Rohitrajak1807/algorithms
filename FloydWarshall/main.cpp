#include <iostream>
#include <vector>
#include <limits>

#define POSITIVE_INFINITY_FLOAT (std::numeric_limits<float>::infinity())
#define NEGATIVE_INFINITY_FLOAT (-1 * (POSITIVE_INFINITY_FLOAT))

static std::vector<std::vector<int>> next;

std::vector<std::vector<float>> floyd_warshall(const std::vector<std::vector<float>> &graph);

void setup(const std::vector<std::vector<float>> &graph, std::vector<std::vector<float>> &dp);

void propagate_negative_cycles(std::vector<std::vector<float>> &dp);

std::vector<int> get_path(const std::vector<std::vector<float>> &dp, int start, int end);

int main() {
    std::vector<std::vector<float>> graph = {
            {0,                       2,                       5,                       POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, 10},
            {POSITIVE_INFINITY_FLOAT, 0,                       2,                       POSITIVE_INFINITY_FLOAT, 11,                      POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT},
            {POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, 0,                       POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, 2},
            {POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, 0,                       1,                       1,                       POSITIVE_INFINITY_FLOAT},
            {POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, 0,                       1,                       POSITIVE_INFINITY_FLOAT},
            {POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, -2,                      0,                       POSITIVE_INFINITY_FLOAT},
            {POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, POSITIVE_INFINITY_FLOAT, 11,                      0},
    };
    std::vector<std::vector<float>> distance = floyd_warshall(graph);
    for (auto &i : distance) {
        for (auto &j: i)
            std::cout << j << "\t\t";
        std::cout << '\n';
    }
    std::vector<int> path = get_path(distance, 0, 6);
    for (auto &i : path)
        std::cout << i << "\t";

    return 0;
}

std::vector<std::vector<float>> floyd_warshall(const std::vector<std::vector<float>> &graph) {
    int n = graph.size();
    std::vector<std::vector<float>> dp(n, std::vector<float>(n));
    next = std::vector<std::vector<int>>(n);
    setup(graph, dp);

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                float new_dist = dp[i][k] + dp[k][j];
                if (new_dist < dp[i][j]) {
                    dp[i][j] = new_dist;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

//    optional if the graph is guaranteed to hot have any -ve edge weights
    propagate_negative_cycles(dp);
    return dp;
}

void setup(const std::vector<std::vector<float>> &graph, std::vector<std::vector<float>> &dp) {
    int n = graph.size();
    for (auto &i : next)
        i = std::vector<int>(n, INT32_MAX);

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            dp[i][j] = graph[i][j];
            if (graph[i][j] != POSITIVE_INFINITY_FLOAT)
                next[i][j] = j;
        }
    }
}

void propagate_negative_cycles(std::vector<std::vector<float>> &dp) {
    int n = dp.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                float new_dist = dp[i][k] + dp[k][j];
                if (new_dist < dp[i][j]) {
                    dp[i][j] = NEGATIVE_INFINITY_FLOAT;
                    next[i][j] = -1;
                }
            }
        }
    }
}

std::vector<int> get_path(const std::vector<std::vector<float>> &dp, int start, int end) {
    std::vector<int> path;
    std::vector<int> path_temp;
    bool swapped = false;
//    check if the destination is reachable at all
    if (dp[start][end] != POSITIVE_INFINITY_FLOAT) {
        int at = start;
        for (; at != end; at = next[at][end]) {
//            if -ve cycle is encountered midway then return an invalid path
            if (at == -1) {
                swapped = true;
                path.swap(path_temp);
                path.emplace_back(INT32_MAX);
                break;
            }
            path.emplace_back(at);
        }

//      if the destination falls in a -ve cycle return an invalid path
        if (!swapped && at == -1) {
                path.swap(path_temp);
                path.emplace_back(INT32_MAX);
        } else if (at != -1){
            path.emplace_back(end);
        }
    }

    return path;
}