#include "../include/algorithm/dijkstra.hpp"
#include "../include/algorithm/aStar.hpp"
#include "../include/graph/graph.hpp"
#include "../include/graph/vertex.hpp"
#include "../include/utils/logger.hpp"
#include "../include/preference/preference.hpp"
#include <vector>
#include <cassert>
#include <iostream>

Graph buildTestGraph() {
    Graph g;
    g.addVertex(Vertex("1", 0, 0));  // Koordinat dummy
    g.addVertex(Vertex("2", 1, 1));
    g.addVertex(Vertex("3", 2, 2));
    
    // A-B: distance=10, time=15, cost=20000
    g.addEdge(Edge("1", "2", 10.0, 15.0, 20000.0));
    
    // B-C: distance=5, time=10, cost=15000
    g.addEdge(Edge("2", "3", 5.0, 10.0, 15000.0));
    
    // A-C: distance=20, time=30, cost=30000 (direct)
    g.addEdge(Edge("1", "3", 20.0, 30.0, 30000.0));
    
    return g;
}

void testDijkstra() {
    Graph g = buildTestGraph();
    // Test berdasarkan jarak (harus A-B-C karena 10+5 < 20)
    auto path = Dijkstra::findShortestPath(g, "1", "3", Preference());
    assert(path.size() == 3);
    assert(path[0] == "1" && path[1] == "2" && path[2] == "3");
    // Test berdasarkan waktu (15+10 < 30)
    path = Dijkstra::findShortestPath(g, "1", "3", Preference());
    assert(path[0] == "1" && path[1] == "2" && path[2] == "3");
    std::cout << "Dijkstra tests passed!\n";
}

void testAStar() {
    Graph g = buildTestGraph();
    // A* dengan heuristik jarak
    auto path = AStar::findPath(g, "1", "3");
    assert(!path.empty());
    
    std::cout << "AStar tests passed!\n";
}

int main() {
    testDijkstra();
    testAStar();
    return 0;
}