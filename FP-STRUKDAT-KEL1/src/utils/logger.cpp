#include "../../include/utils/logger.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace std;

mutex Logger::logMutex;
Logger::LogLevel Logger::currentLevel = Logger::LogLevel::INFO;

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
}

string Logger::getTimestamp() {
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

void Logger::logToFile(const string& message) {
    lock_guard<mutex> lock(logMutex);
    ofstream logFile("transport.log", ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getTimestamp() << "] " << message << "\n";
    }
}

void Logger::debug(const string& message) {
    if (currentLevel <= LogLevel::DEBUG) {
        cout << "\033[36m[DEBUG] " << message << "\033[0m\n";
        logToFile("[DEBUG] " + message);
    }
}

void Logger::info(const string& message) {
    if (currentLevel <= LogLevel::INFO) {
        cout << "\033[32m[INFO] " << message << "\033[0m\n";
        logToFile("[INFO] " + message);
    }
}

void Logger::warning(const string& message) {
    if (currentLevel <= LogLevel::WARNING) {
        cout << "\033[33m[WARNING] " << message << "\033[0m\n";
        logToFile("[WARNING] " + message);
    }
}

void Logger::error(const string& message) {
    if (currentLevel <= LogLevel::ERROR) {
        cerr << "\033[31m[ERROR] " << message << "\033[0m\n";
        logToFile("[ERROR] " + message);
    }
}

void Logger::init(const std::string& filename) {
    // Implementasi dummy, bisa diisi log file setup jika perlu
    (void)filename;
}