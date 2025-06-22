#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

/**
 * @class Logger
 * @brief Simple logging utility for the application
 */
class Logger {
public:
    enum class LogLevel { DEBUG, INFO, WARNING, ERROR, NONE };

    /**
     * @brief Initialize the logger
     * 
     * @param filename Name of the log file
     */
    static void init(const std::string& filename);

    /**
     * @brief Set the log level
     * 
     * @param level The log level to set
     */
    static void setLogLevel(LogLevel level);

    /**
     * @brief Log a debug message
     * 
     * @param message The message to log
     */
    static void debug(const std::string& message);

    /**
     * @brief Log an info message
     * 
     * @param message The message to log
     */
    static void info(const std::string& message);

    /**
     * @brief Log a warning message
     * 
     * @param message The message to log
     */
    static void warning(const std::string& message);

    /**
     * @brief Log an error message
     * 
     * @param message The message to log
     */
    static void error(const std::string& message);

private:
    static std::ofstream logFile;
    static std::mutex logMutex;
    static LogLevel currentLevel;
    
    /**
     * @brief Get current timestamp as string
     * 
     * @return std::string Formatted timestamp
     */
    static std::string getTimestamp();

    /**
     * @brief Log a message with specified level
     * 
     * @param level Log level (DEBUG/INFO/WARNING/ERROR)
     * @param message The message to log
     */
    static void log(const LogLevel& level, const std::string& message);

    /**
     * @brief Log a message to file
     * 
     * @param message The message to log
     */
    static void logToFile(const std::string& message);
};
