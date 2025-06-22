#include "../../include/graph/edge.hpp"

Edge::Edge(std::string source, std::string destination, double distance, double time, double cost)
    : sourceId(std::move(source)), destinationId(std::move(destination)), distance(distance), time(time), cost(cost) {}

std::string Edge::getSource() const { return sourceId; }
std::string Edge::getDestination() const { return destinationId; }
double Edge::getDistance() const { return distance; }
double Edge::getTime() const { return time; }
double Edge::getCost() const { return cost; }

void Edge::setSource(const std::string& src) { sourceId = src; }
void Edge::setDestination(const std::string& dst) { destinationId = dst; }
void Edge::setDistance(double d) { distance = d; }
void Edge::setTime(double t) { time = t; }
void Edge::setCost(double c) { cost = c; }

double Edge::getWeight(int preferenceType) const {
    switch (preferenceType) {
        case 0: return distance;
        case 1: return time;
        case 2: return cost;
        default: return distance;
    }
}