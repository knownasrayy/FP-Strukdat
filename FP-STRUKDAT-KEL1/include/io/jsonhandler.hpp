#include "graph/graph.hpp"
#include "preference/preference.hpp"
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @class JSONHandler
 * @brief Handles reading and writing preferences from/to JSON files
 */
class JSONHandler {
public:
    /**
     * @brief Load user preferences from a JSON file
     * 
     * @param filename Path to the JSON file
     * @return Preference The loaded preferences
     * @throws std::runtime_error if file cannot be opened or has invalid format
     */
    static Preference loadPreferencesFromJSON(const std::string& filename);

    /**
     * @brief Save user preferences to a JSON file
     * 
     * @param preferences The preferences to save
     * @param filename Path to save the JSON file
     * @throws std::runtime_error if file cannot be opened or written
     */
    static void savePreferencesToJSON(const Preference& preferences, 
                                    const std::string& filename);

private:
    /**
     * @brief Parse a JSON string
     * 
     * @param json The JSON string to parse
     * @return std::string The parsed value
     */
    static std::string parseJSONString(const std::string& json);

    /**
     * @brief Format a value as JSON string
     * 
     * @param value The value to format
     * @return std::string The JSON formatted string
     */
    static std::string formatJSONValue(const std::string& value);
};
