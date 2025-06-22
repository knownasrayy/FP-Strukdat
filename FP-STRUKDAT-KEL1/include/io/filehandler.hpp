#pragma once
#include <string>

class FileHandler {
public:
    static std::string readFile(const std::string& filename);
    static void writeFile(const std::string& filename, const std::string& content);
};
