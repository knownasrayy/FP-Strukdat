#pragma once
#include "criteria.hpp"
#include <vector>
#include <string>
#include <memory>

/**
 * @class Preference
 * @brief Manages user preferences for path finding
 * 
 * This class handles the user's preferences for path finding,
 * including weights for different criteria (distance, time, cost)
 * and any additional constraints.
 */
class Preference {
public:
    /**
     * @brief Construct a new Preference object with default weights
     */
    Preference();

    /**
     * @brief Construct a new Preference object with specified weights
     * 
     * @param distanceWeight Weight for distance criterion (0-1)
     * @param timeWeight Weight for time criterion (0-1)
     * @param costWeight Weight for cost criterion (0-1)
     * @throws std::invalid_argument if weights are invalid
     */
    Preference(double distanceWeight, double timeWeight, double costWeight);

    // Getters
    double getDistanceWeight() const;
    double getTimeWeight() const;
    double getCostWeight() const;

    /**
     * @brief Set the weight for distance criterion
     * 
     * @param weight Weight value (0-1)
     * @throws std::invalid_argument if weight is invalid
     */
    void setDistanceWeight(double weight);

    /**
     * @brief Set the weight for time criterion
     * 
     * @param weight Weight value (0-1)
     * @throws std::invalid_argument if weight is invalid
     */
    void setTimeWeight(double weight);

    /**
     * @brief Set the weight for cost criterion
     * 
     * @param weight Weight value (0-1)
     * @throws std::invalid_argument if weight is invalid
     */
    void setCostWeight(double weight);

    /**
     * @brief Calculate the weighted score for a path
     * 
     * @param distance Total distance of the path
     * @param time Total time of the path
     * @param cost Total cost of the path
     * @return double The weighted score
     */
    double calculateScore(double distance, double time, double cost) const;

    /**
     * @brief Normalize weights to ensure they sum to 1
     */
    void normalizeWeights();

private:
    double distanceWeight;
    double timeWeight;
    double costWeight;

    /**
     * @brief Validate a weight value
     * 
     * @param weight Weight to validate
     * @throws std::invalid_argument if weight is invalid
     */
    static void validateWeight(double weight);
};
