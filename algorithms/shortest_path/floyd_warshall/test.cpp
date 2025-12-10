#include "floyd_warshall.h"
#include <iostream>
#include <vector>

int main() {
    using Weight = FloydWarshall::Weight;
    using Matrix = FloydWarshall::Matrix;

    Weight INF = FloydWarshall::inf();

    Matrix adj = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}};

    FloydWarshall fw(adj);

    if (fw.has_negative_cycle()) {
        std::cout << "NEGATIVE CYCLE\n";
        return 0;
    }

    const Matrix &dist = fw.distances();

    std::cout << "Distance matrix:\n";
    for (std::size_t i = 0; i < dist.size(); ++i) {
        for (std::size_t j = 0; j < dist[i].size(); ++j) {
            if (dist[i][j] == INF) {
                std::cout << "INF";
            } else {
                std::cout << dist[i][j];
            }
            if (j + 1 < dist[i].size())
                std::cout << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
