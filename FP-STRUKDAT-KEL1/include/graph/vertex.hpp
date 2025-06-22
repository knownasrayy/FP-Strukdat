#pragma once
#include <string>
#include <utility>

/**
 * @class Vertex
 * @brief Represents a vertex in the graph with geographical coordinates
 */
class Vertex {
public:
    /**
     * @brief Construct a new Vertex object
     * 
     * @param id Unique identifier for the vertex
     * @param lat Latitude coordinate
     * @param lon Longitude coordinate
     */
    Vertex(std::string id = "", double lat = 0.0, double lon = 0.0);

    // Getters
    std::string getId() const;
    double getLatitude() const;
    double getLongitude() const;
    std::pair<double, double> getCoordinates() const;

    // Setters
    void setId(const std::string& id);
    void setLatitude(double lat);
    void setLongitude(double lon);
    void setCoordinates(double lat, double lon);

    // Operator overload
    bool operator==(const Vertex& other) const;

private:
    std::string id;
    double latitude;
    double longitude;
};
