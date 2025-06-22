#include "../../include/graph/vertex.hpp"

Vertex::Vertex(std::string id, double latitude, double longitude)
    : id(std::move(id)), latitude(latitude), longitude(longitude) {}

std::string Vertex::getId() const { return id; }
double Vertex::getLatitude() const { return latitude; }
double Vertex::getLongitude() const { return longitude; }
std::pair<double, double> Vertex::getCoordinates() const { return {latitude, longitude}; }

void Vertex::setId(const std::string& newId) { id = newId; }
void Vertex::setLatitude(double lat) { latitude = lat; }
void Vertex::setLongitude(double lon) { longitude = lon; }
void Vertex::setCoordinates(double lat, double lon) {
    latitude = lat;
    longitude = lon;
}

bool Vertex::operator==(const Vertex& other) const {
    return id == other.id;
}