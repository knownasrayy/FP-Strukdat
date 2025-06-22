#pragma once
#include "graph/graph.hpp"
#include "preference/preference.hpp"
#include <vector>
#include <string>
#include <unordered_map>

/**
 * @class Dijkstra
 * @brief Implements Dijkstra's shortest path algorithm with multiple weights
 */
class Dijkstra {
public:
    /**
     * @brief Find shortest path between two vertices using Dijkstra's algorithm
     * 
     * @param graph The graph to search in
     * @param start Starting vertex ID
     * @param goal Goal vertex ID
     * @param preferences User preferences for weight calculation
     * @return std::vector<std::string> Vector of vertex IDs representing the path
     * @throws std::invalid_argument if start or goal vertices don't exist
     * @throws std::runtime_error if no path is found
     */
    static std::vector<std::string> findShortestPath(
        const Graph& graph,
        const std::string& start,
        const std::string& goal,
        const Preference& preferences
    );

    /**
     * @brief Get the total distance of a path
     * 
     * @param graph The graph containing the path
     * @param path Vector of vertex IDs representing the path
     * @return double Total distance of the path
     */
    static double getPathDistance(const Graph& graph, 
                                const std::vector<std::string>& path);

    /**
     * @brief Get the total time of a path
     * 
     * @param graph The graph containing the path
     * @param path Vector of vertex IDs representing the path
     * @return double Total time of the path
     */
    static double getPathTime(const Graph& graph, 
                            const std::vector<std::string>& path);

    /**
     * @brief Get the total cost of a path
     * 
     * @param graph The graph containing the path
     * @param path Vector of vertex IDs representing the path
     * @return double Total cost of the path
     */
    static double getPathCost(const Graph& graph, 
                            const std::vector<std::string>& path);

private:
    /**
     * @brief Calculate the weighted cost between two vertices
     * 
     * @param graph The graph containing the vertices
     * @param source Source vertex ID
     * @param dest Destination vertex ID
     * @param preferences User preferences for weight calculation
     * @return double The weighted cost
     */
    static double calculateWeightedCost(
        const Graph& graph,
        const std::string& source,
        const std::string& dest,
        const Preference& preferences
    );

    /**
     * @brief Reconstruct the path from start to end
     * 
     * @param cameFrom Map of vertices and their predecessors
     * @param start Starting vertex ID
     * @param end Goal vertex ID
     * @return std::vector<std::string> Vector of vertex IDs representing the path
     */
    static std::vector<std::string> reconstructPath(
        const std::unordered_map<std::string, std::string>& cameFrom, 
        const std::string& start, 
        const std::string& end
    );
};
