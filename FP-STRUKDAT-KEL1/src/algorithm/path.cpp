#include "../../include/algorithm/path.hpp"
#include "../../include/graph/graph.hpp"
#include "../../include/algorithm/dijkstra.hpp"
#include <vector>
#include <limits>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

vector<string> ShortestPath::reconstructPath(
    const unordered_map<string, string>& cameFrom,
    const string& start,
    const string& end
) {
    vector<string> path;
    if (cameFrom.find(end) == cameFrom.end() && start != end) return path;
    string current = end;
    while (current != start) {
        path.push_back(current);
        auto it = cameFrom.find(current);
        if (it == cameFrom.end()) return vector<string>();
        current = it->second;
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

double ShortestPath::calculatePathCost(
    const Graph& graph,
    const vector<string>& path,
    const string& criteria
) {
    if (path.empty()) return 0.0;
    double totalCost = 0.0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        string from = path[i];
        string to = path[i+1];
        int prefType = 0;
        if (criteria == "distance") prefType = 0;
        else if (criteria == "time") prefType = 1;
        else if (criteria == "cost") prefType = 2;
        else if (criteria == "transfers") {
            totalCost += 1;
            continue;
        }
        totalCost += graph.getEdgeWeight(from, to, prefType);
    }
    return totalCost;
}