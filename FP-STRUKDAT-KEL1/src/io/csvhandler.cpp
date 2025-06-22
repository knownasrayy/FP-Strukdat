#include "io/csvhandler.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

Graph CSVHandler::loadGraphFromCSV(const string& locationFile,
                                 const string& routeFile) {
    Graph graph;

    // Load locations
    ifstream locFile(locationFile);
    if (!locFile) {
        throw runtime_error("Cannot open location file: " + locationFile);
    }

    string line;
    // Skip header
    getline(locFile, line);

    // Read locations
    while (getline(locFile, line)) {
        auto tokens = parseCSVLine(line);
        if (tokens.size() < 3) {
            continue;  // Skip invalid lines
        }

        try {
            string id = tokens[0];
            double lat = stod(tokens[1]);
            double lon = stod(tokens[2]);

            graph.addVertex(Vertex(id, lat, lon));
        } catch (const exception& e) {
            // Log error and continue
            continue;
        }
    }

    // Load routes
    ifstream routeStream(routeFile);
    if (!routeStream) {
        throw runtime_error("Cannot open route file: " + routeFile);
    }

    // Skip header
    getline(routeStream, line);

    // Read routes
    while (getline(routeStream, line)) {
        auto tokens = parseCSVLine(line);
        if (tokens.size() < 5) {
            continue;  // Skip invalid lines
        }

        try {
            string source = tokens[0];
            string dest = tokens[1];
            double distance = stod(tokens[2]);
            double time = stod(tokens[3]);
            double cost = stod(tokens[4]);

            if (graph.hasVertex(source) && graph.hasVertex(dest)) {
                graph.addEdge(Edge(source, dest, distance, time, cost));
            }
        } catch (const exception& e) {
            // Log error and continue
            continue;
        }
    }

    return graph;
}

void CSVHandler::saveGraphToCSV(const Graph& graph,
                              const string& locationFile,
                              const string& routeFile) {
    // Save locations
    ofstream locFile(locationFile);
    if (!locFile) {
        throw runtime_error("Cannot open location file for writing: " + locationFile);
    }

    // Write header
    locFile << "ID,Latitude,Longitude\n";

    // Write vertices
    for (const auto& vertex : graph.getAllVertices()) {
        locFile << vertex.getId() << ","
                << vertex.getLatitude() << ","
                << vertex.getLongitude() << "\n";
    }

    // Save routes
    ofstream routeStream(routeFile);
    if (!routeStream) {
        throw runtime_error("Cannot open route file for writing: " + routeFile);
    }

    // Write header
    routeStream << "Source,Destination,Distance,Time,Cost\n";

    // Write edges
    for (const auto& edge : graph.getAllEdges()) {
        routeStream << edge.getSource() << ","
                 << edge.getDestination() << ","
                 << edge.getDistance() << ","
                 << edge.getTime() << ","
                 << edge.getCost() << "\n";
    }
}

vector<string> CSVHandler::parseCSVLine(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ',')) {
        // Remove whitespace
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        tokens.push_back(token);
    }

    return tokens;
}