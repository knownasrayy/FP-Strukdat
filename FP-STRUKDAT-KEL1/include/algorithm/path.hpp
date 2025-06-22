#pragma once

#include "../graph/graph.hpp"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class ShortestPath {
public:
    virtual ~ShortestPath() = default;
    
    virtual std::vector<std::string> findPath(
        const Graph& graph,
        const std::string& startId,
        const std::string& endId,
        const std::string& criteria = "distance"
    ) = 0;
    
    virtual double calculatePathCost(
        const Graph& graph,
        const std::vector<std::string>& path,
        const std::string& criteria
    ) = 0;
    
    static std::vector<std::string> reconstructPath(
        const std::unordered_map<std::string, std::string>& cameFrom,
        const std::string& start,
        const std::string& end
    );
};