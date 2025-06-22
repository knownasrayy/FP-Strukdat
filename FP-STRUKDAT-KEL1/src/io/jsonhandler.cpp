#include "io/jsonhandler.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Preference JSONHandler::loadPreferencesFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open preferences file: " + filename);
    }

    try {
        json data = json::parse(file);
        
        double distanceWeight = data["weights"]["distance"].get<double>();
        double timeWeight = data["weights"]["time"].get<double>();
        double costWeight = data["weights"]["cost"].get<double>();

        return Preference(distanceWeight, timeWeight, costWeight);
    } catch (const json::exception& e) {
        throw std::runtime_error("Error parsing JSON: " + std::string(e.what()));
    }
}

void JSONHandler::savePreferencesToJSON(const Preference& preferences,
                                      const std::string& filename) {
    json data;
    data["weights"]["distance"] = preferences.getDistanceWeight();
    data["weights"]["time"] = preferences.getTimeWeight();
    data["weights"]["cost"] = preferences.getCostWeight();

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    file << data.dump(4);  // Pretty print with 4 spaces indent
}