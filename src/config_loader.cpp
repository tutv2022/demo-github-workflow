#include "config_loader.h"

#include <fstream>
#include <iostream>

std::map<std::string, std::string> loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    std::ifstream file(path);

    // BUG: no check that the file actually opened.
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments.
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t pos = line.find('=');
        // BUG: lines without '=' produce key = whole line, value = garbage-ish.
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        config[key] = value;  // No trimming of whitespace.
    }
    return config;
}

std::string getConfigValue(const std::map<std::string, std::string>& config,
                           const std::string& key,
                           const std::string& defaultValue) {
    auto it = config.find(key);
    if (it == config.end()) {
        return defaultValue;
    }
    return it->second;
}
