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

    int source = 0;
    int destination = 3;
    // even though node 3 is adjacent to node 0 (addEdge(0, 3)), we took three turns to get to it.
    std::cout << "DFS traversal from " << source << " to " << destination << ": " << graph.dfs(source, destination);
    /*
Directed graph for this setup:

          +====+
  +---->  | 4  |
  |       +====+
  |
  |
  |
+====+  <----  +====+ ----> +====+
| 1  |         | 0  |       | 3  |
+====+  ---->  +====+ <---- +====+
  ^              ^
  |              |
  |              |
  |              |
+====+           |
| 2  |-----------+
+====+

Edges:
0 -> 1, 3
1 -> 0, 4
2 -> 0, 1
3 -> 2
4 -> (no outgoing edges)

Notes:
- 1 <--> 0 shows the two-way connection: 0 -> 1 and 1 -> 0.
- 2 has arrows going up to both 1 and 0 (2 -> 1, 2 -> 0).
- 3 -> 2 is implied by the arrow from 3 back toward 2 (bottom-left).
*/
}