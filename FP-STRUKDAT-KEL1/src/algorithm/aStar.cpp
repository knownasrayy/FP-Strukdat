#include "algorithm/aStar.hpp"
#include "graph/graph.hpp"
#include <queue>
#include <cmath>
#include <unordered_map>
#include <limits>
#include <stdexcept>
#include <algorithm>    // untuk std::reverse

using namespace std;

vector<string> AStar::findPath(const Graph& graph, 
                                        const string& start, 
                                        const string& goal) {
    // Validate input vertices
    if (!graph.hasVertex(start) || !graph.hasVertex(goal)) {
        throw invalid_argument("Start or goal vertex not found in graph");
    }

    // Priority queue for open set
    auto compare = [](const pair<string, double>& a, 
                     const pair<string, double>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<string, double>,
                       vector<pair<string, double>>,
                       decltype(compare)> openSet(compare);

    // Initialize data structures
    unordered_map<string, double> gScore;
    unordered_map<string, double> fScore;
    unordered_map<string, string> cameFrom;
    
    // Set initial values
    gScore[start] = 0;
    fScore[start] = heuristic(graph.getVertex(start), 
                             graph.getVertex(goal), 
                             graph);
    openSet.push({start, fScore[start]});

    while (!openSet.empty()) {
        string current = openSet.top().first;
        openSet.pop();

        if (current == goal) {
            // Reconstruct path
            vector<string> path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        const auto& neighbors = graph.getNeighbors(current);
        for (const auto& neighbor : neighbors) {
            double tentativeGScore = gScore[current] + 
                                   graph.getEdgeWeight(current, neighbor);

            if (!gScore.count(neighbor) || 
                tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = gScore[neighbor] + 
                                 heuristic(graph.getVertex(neighbor),
                                         graph.getVertex(goal),
                                         graph);
                openSet.push({neighbor, fScore[neighbor]});
            }
        }
    }

    throw runtime_error("No path found between start and goal");
}

double AStar::heuristic(const Vertex& current, 
                       const Vertex& goal,
                       const Graph& graph) {
    // Using Euclidean distance as heuristic
    double dx = current.getLongitude() - goal.getLongitude();
    double dy = current.getLatitude() - goal.getLatitude();
    
    // Convert to approximate distance in same units as edge weights
    double distanceScale = 111.0;  // km per degree at equator
    return sqrt(dx * dx + dy * dy) * distanceScale;
}