#include "../../include/algorithm/dijkstra.hpp"
#include "../../include/graph/graph.hpp"
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm> // For std::reverse

using namespace std;

vector<string> Dijkstra::findShortestPath(
    const Graph& graph,
    const string& startId,
    const string& endId,
    const Preference& preferences
) {
    // Initialize data structures for Dijkstra's algorithm
    unordered_map<string, string> cameFrom;
    unordered_map<string, double> costSoFar;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> frontier;
    
    // Start from the initial node
    frontier.push({0, startId});
    costSoFar[startId] = 0;
    
    while (!frontier.empty()) {
        string current = frontier.top().second;
        frontier.pop();
        
        // If we reached the goal, break
        if (current == endId) break;
        
        // Use getNeighbors to get all adjacent nodes
        for (const auto& next : graph.getNeighbors(current)) {
            // You may need to select the preference type from preferences
            int preferenceType = 0; // TODO: set this based on preferences
            double newCost = costSoFar[current] + graph.getEdgeWeight(current, next, preferenceType);
            
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                cameFrom[next] = current;
                frontier.push({newCost, next});
            }
        }
    }
    
    return reconstructPath(cameFrom, startId, endId);
}

// Helper to reconstruct path from cameFrom map (string version)
vector<string> Dijkstra::reconstructPath(const unordered_map<string, string>& cameFrom, const string& start, const string& end) {
    vector<string> path;
    if (cameFrom.find(end) == cameFrom.end() && start != end) return path;
    string current = end;
    while (current != start) {
        path.push_back(current);
        auto it = cameFrom.find(current);
        if (it == cameFrom.end()) return vector<string>(); // No path
        current = it->second;
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

double Dijkstra::getPathDistance(const Graph& graph, const std::vector<std::string>& path) {
    double total = 0.0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        total += graph.getEdgeWeight(path[i], path[i+1], 0); // 0: distance
    }
    return total;
}
double Dijkstra::getPathTime(const Graph& graph, const std::vector<std::string>& path) {
    double total = 0.0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        total += graph.getEdgeWeight(path[i], path[i+1], 1); // 1: time
    }
    return total;
}
double Dijkstra::getPathCost(const Graph& graph, const std::vector<std::string>& path) {
    double total = 0.0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        total += graph.getEdgeWeight(path[i], path[i+1], 2); // 2: cost
    }
    return total;
}