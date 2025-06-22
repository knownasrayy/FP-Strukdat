#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "graph/graph.hpp"
#include "graph/vertex.hpp"
#include "graph/edge.hpp"

TEST_CASE("Vertex operations", "[vertex]") {
    SECTION("Constructor and getters") {
        Vertex v("A", -6.2, 106.8);
        
        REQUIRE(v.getId() == "A");
        REQUIRE(v.getLatitude() == Approx(-6.2));
        REQUIRE(v.getLongitude() == Approx(106.8));
    }
    
    SECTION("Setters") {
        Vertex v("A", 0.0, 0.0);
        v.setLatitude(-6.2);
        v.setLongitude(106.8);
        
        REQUIRE(v.getLatitude() == Approx(-6.2));
        REQUIRE(v.getLongitude() == Approx(106.8));
    }
}

TEST_CASE("Edge operations", "[edge]") {
    SECTION("Constructor and getters") {
        Edge e("A", "B", 1.5, 10.0, 5000.0);
        
        REQUIRE(e.getSource() == "A");
        REQUIRE(e.getDestination() == "B");
        REQUIRE(e.getDistance() == Approx(1.5));
        REQUIRE(e.getTime() == Approx(10.0));
        REQUIRE(e.getCost() == Approx(5000.0));
    }
    
    SECTION("Weight by preference type") {
        Edge e("A", "B", 1.5, 10.0, 5000.0);
        
        REQUIRE(e.getWeight(0) == Approx(1.5));    // Distance
        REQUIRE(e.getWeight(1) == Approx(10.0));   // Time
        REQUIRE(e.getWeight(2) == Approx(5000.0)); // Cost
    }
}

TEST_CASE("Graph operations", "[graph]") {
    Graph g;
    
    SECTION("Adding and retrieving vertices") {
        Vertex v1("A", -6.2, 106.8);
        Vertex v2("B", -6.3, 106.9);
        
        g.addVertex(v1);
        g.addVertex(v2);
        
        REQUIRE(g.hasVertex("A"));
        REQUIRE(g.hasVertex("B"));
        REQUIRE_FALSE(g.hasVertex("C"));
        
        auto vertices = g.getAllVertices();
        REQUIRE(vertices.size() == 2);
    }
    
    SECTION("Adding and retrieving edges") {
        Vertex v1("A", -6.2, 106.8);
        Vertex v2("B", -6.3, 106.9);
        g.addVertex(v1);
        g.addVertex(v2);
        
        Edge e("A", "B", 1.5, 10.0, 5000.0);
        g.addEdge(e);
        
        REQUIRE(g.hasEdge("A", "B"));
        REQUIRE_FALSE(g.hasEdge("B", "A")); // Directed graph
        
        auto edges = g.getAllEdges();
        REQUIRE(edges.size() == 1);
    }
    
    SECTION("Getting neighbors") {
        Vertex v1("A", -6.2, 106.8);
        Vertex v2("B", -6.3, 106.9);
        Vertex v3("C", -6.4, 107.0);
        g.addVertex(v1);
        g.addVertex(v2);
        g.addVertex(v3);
        
        g.addEdge(Edge("A", "B", 1.5, 10.0, 5000.0));
        g.addEdge(Edge("A", "C", 2.0, 15.0, 7000.0));
        
        auto neighbors = g.getNeighbors("A");
        REQUIRE(neighbors.size() == 2);
        REQUIRE(std::find(neighbors.begin(), neighbors.end(), "B") != neighbors.end());
        REQUIRE(std::find(neighbors.begin(), neighbors.end(), "C") != neighbors.end());
    }
    
    SECTION("Edge weights") {
        Vertex v1("A", -6.2, 106.8);
        Vertex v2("B", -6.3, 106.9);
        g.addVertex(v1);
        g.addVertex(v2);
        
        g.addEdge(Edge("A", "B", 1.5, 10.0, 5000.0));
        
        REQUIRE(g.getEdgeWeight("A", "B", 0) == Approx(1.5));    // Distance
        REQUIRE(g.getEdgeWeight("A", "B", 1) == Approx(10.0));   // Time
        REQUIRE(g.getEdgeWeight("A", "B", 2) == Approx(5000.0)); // Cost
    }
}