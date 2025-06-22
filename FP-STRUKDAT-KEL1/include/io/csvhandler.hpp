#pragma once
#include "graph/graph.hpp"
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @class CSVHandler
 * @brief Handles reading and writing graph data from/to CSV files
 */
class CSVHandler {
public:
    /**
     * @brief Load graph data from a CSV file
     * 
     * @param locationFile Path to the location CSV file
     * @param routeFile Path to the route CSV file
     * @return Graph The constructed graph
     * @throws std::runtime_error if file cannot be opened or has invalid format
     */
    static Graph loadGraphFromCSV(const std::string& locationFile, 
                                const std::string& routeFile);

    /**
     * @brief Save graph data to CSV files
     * 
     * @param graph The graph to save
     * @param locationFile Path to save locations
     * @param routeFile Path to save routes
     * @throws std::runtime_error if file cannot be opened or written
     */
    static void saveGraphToCSV(const Graph& graph,
                             const std::string& locationFile,
                             const std::string& routeFile);

private:
    /**
     * @brief Parse a CSV line into tokens
     * 
     * @param line The CSV line to parse
     * @return std::vector<std::string> Vector of tokens
     */
    static std::vector<std::string> parseCSVLine(const std::string& line);

    /**
     * @brief Escape a string for CSV format
     * 
     * @param str The string to escape
     * @return std::string The escaped string
     */
    static std::string escapeCSV(const std::string& str);
};
