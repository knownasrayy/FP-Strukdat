#include "../../include/preference/preference.hpp"
#include <stdexcept>
#include <algorithm>

Preference::Preference() : distanceWeight(1.0/3), timeWeight(1.0/3), costWeight(1.0/3) {}

Preference::Preference(double distanceWeight, double timeWeight, double costWeight)
    : distanceWeight(distanceWeight), timeWeight(timeWeight), costWeight(costWeight) {
    normalizeWeights();
}

double Preference::getDistanceWeight() const { return distanceWeight; }
double Preference::getTimeWeight() const { return timeWeight; }
double Preference::getCostWeight() const { return costWeight; }

void Preference::setDistanceWeight(double weight) {
    validateWeight(weight);
    distanceWeight = weight;
    normalizeWeights();
}

void Preference::setTimeWeight(double weight) {
    validateWeight(weight);
    timeWeight = weight;
    normalizeWeights();
}

void Preference::setCostWeight(double weight) {
    validateWeight(weight);
    costWeight = weight;
    normalizeWeights();
}

double Preference::calculateScore(double distance, double time, double cost) const {
    return distanceWeight * distance + timeWeight * time + costWeight * cost;
}

void Preference::normalizeWeights() {
    double sum = distanceWeight + timeWeight + costWeight;
    if (sum > 0) {
        distanceWeight /= sum;
        timeWeight /= sum;
        costWeight /= sum;
    }
}

void Preference::validateWeight(double weight) {
    if (weight < 0.0 || weight > 1.0) {
        throw std::invalid_argument("Weight must be between 0 and 1");
    }
}