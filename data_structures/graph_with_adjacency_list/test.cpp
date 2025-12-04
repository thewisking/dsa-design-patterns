#include "graph.h"

int main() {
    Graph graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 0);
    graph.addEdge(1, 4);
    graph.addEdge(2, 0);
    graph.addEdge(2, 1);
    graph.addEdge(3, 2);
    graph.print();
}