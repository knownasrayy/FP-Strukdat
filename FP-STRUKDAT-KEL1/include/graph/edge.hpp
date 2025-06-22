#pragma once
#include <string>
#include <utility>

/**
 * @class Edge
 * @brief Represents an edge in the graph with multiple weights
 */
class Edge {
public:
    /**
     * @brief Construct a new Edge object
     * 
     * @param source Source vertex ID
     * @param destination Destination vertex ID
     * @param distance Physical distance in kilometers
     * @param time Travel time in minutes
     * @param cost Travel cost in currency units
     */
    Edge(std::string source = "", 
         std::string destination = "", 
         double distance = 0.0, 
         double time = 0.0, 
         double cost = 0.0);

    // Getters
    std::string getSource() const;
    std::string getDestination() const;
    double getDistance() const;
    double getTime() const;
    double getCost() const;

    // Setters
    void setSource(const std::string& source);
    void setDestination(const std::string& destination);
    void setDistance(double distance);
    void setTime(double time);
    void setCost(double cost);

    /**
     * @brief Get weight based on preference type
     * 
     * @param preferenceType 0 for distance, 1 for time, 2 for cost
     * @return double The weight value for the specified preference
     */
    double getWeight(int preferenceType) const;

private:
    std::string sourceId;
    std::string destinationId;
    double distance;
    double time;
    double cost;
};
