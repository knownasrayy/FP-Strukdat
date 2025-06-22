#pragma once
#include "graph/graph.hpp"
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @class AStar
 * @brief Implements the A* pathfinding algorithm for graph traversal
 * 
 * This class provides methods to find the optimal path between two vertices
 * in a weighted graph using the A* algorithm, which uses heuristics to improve
 * pathfinding efficiency.
 */
class AStar {
public:
    /**
     * @brief Finds the shortest path between two vertices using A* algorithm
     * 
     * @param graph The graph to search in
     * @param start The starting vertex ID
     * @param goal The target vertex ID
     * @return std::vector<std::string> Vector of vertex IDs representing the path
     * @throws std::invalid_argument if start or goal vertices don't exist
     * @throws std::runtime_error if no path is found
     */
    static std::vector<std::string> findPath(const Graph& graph, 
                                           const std::string& start, 
                                           const std::string& goal);

private:
    /**
     * @brief Calculates the heuristic distance between two vertices
     * 
     * @param current Current vertex being evaluated
     * @param goal Target vertex
     * @param graph The graph containing the vertices
     * @return double Estimated distance to goal
     */
    static double heuristic(const Vertex& current, 
                          const Vertex& goal, 
                          const Graph& graph);
};
