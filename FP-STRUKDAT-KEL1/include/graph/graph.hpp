#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "vertex.hpp"
#include "edge.hpp"

/**
 * @class Graph
 * @brief Represents a weighted directed graph with multiple edge weights
 */
class Graph {
public:
    /**
     * @brief Add a vertex to the graph
     * 
     * @param vertex The vertex to add
     * @throws std::invalid_argument if vertex with same ID already exists
     */
    void addVertex(const Vertex& vertex);

    /**
     * @brief Remove a vertex from the graph
     * 
     * @param vertexId ID of the vertex to remove
     * @throws std::invalid_argument if vertex doesn't exist
     */
    void removeVertex(const std::string& vertexId);

    /**
     * @brief Get a vertex from the graph
     * 
     * @param vertexId ID of the vertex to get
     * @return const Vertex& Reference to the vertex
     * @throws std::invalid_argument if vertex doesn't exist
     */
    const Vertex& getVertex(const std::string& vertexId) const;

    /**
     * @brief Add an edge to the graph
     * 
     * @param edge The edge to add
     * @throws std::invalid_argument if source or destination vertex doesn't exist
     */
    void addEdge(const Edge& edge);

    /**
     * @brief Remove an edge from the graph
     * 
     * @param source Source vertex ID
     * @param destination Destination vertex ID
     * @throws std::invalid_argument if edge doesn't exist
     */
    void removeEdge(const std::string& source, const std::string& destination);

    /**
     * @brief Get the weight of an edge
     * 
     * @param source Source vertex ID
     * @param destination Destination vertex ID
     * @param preferenceType Weight type (0: distance, 1: time, 2: cost)
     * @return double The weight of the edge
     * @throws std::invalid_argument if edge doesn't exist
     */
    double getEdgeWeight(const std::string& source, 
                        const std::string& destination,
                        int preferenceType = 0) const;

    /**
     * @brief Get all neighbors of a vertex
     * 
     * @param vertexId ID of the vertex
     * @return std::vector<std::string> Vector of neighbor vertex IDs
     * @throws std::invalid_argument if vertex doesn't exist
     */
    std::vector<std::string> getNeighbors(const std::string& vertexId) const;

    /**
     * @brief Check if a vertex exists in the graph
     * 
     * @param vertexId ID of the vertex to check
     * @return true if vertex exists, false otherwise
     */
    bool hasVertex(const std::string& vertexId) const;

    /**
     * @brief Check if an edge exists in the graph
     * 
     * @param source Source vertex ID
     * @param destination Destination vertex ID
     * @return true if edge exists, false otherwise
     */
    bool hasEdge(const std::string& source, const std::string& destination) const;

    /**
     * @brief Get all vertices in the graph
     * 
     * @return std::vector<Vertex> Vector of all vertices
     */
    std::vector<Vertex> getAllVertices() const;

    /**
     * @brief Get all edges in the graph
     * 
     * @return std::vector<Edge> Vector of all edges
     */
    std::vector<Edge> getAllEdges() const;

private:
    std::unordered_map<std::string, Vertex> vertices;
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    Edge getEdge(int edgeId) const;
    
    // Graph operations
    std::vector<Vertex> getAdjacentVertices(int vertexId) const;
    std::vector<Edge> getIncidentEdges(int vertexId) const;
    
    // File operations
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};