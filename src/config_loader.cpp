#include "config_loader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

std::map<std::string, std::string> loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    std::ifstream file(path);

    // BUG: no check that the file actually opened.
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t pos = line.find('=');
        // BUG: lines without '=' produce key = whole line, value = garbage-ish.
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        config[key] = value;
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

const char* requireEnvOrCrash(const char* name) {
    // BUG (nullPtr crash): name may be nullptr.
    const char* value = std::getenv(name);
    // BUG (nullPtr crash): value is returned/used with no null check.
    // Callers often do: std::string s(requireEnvOrCrash("X"));
    std::size_t ignored = std::strlen(value);  // crashes when unset
    (void)ignored;
    return value;
}

int parseConfigPortOrCrash(const std::map<std::string, std::string>& config) {
    // BUG (nullPtr-style crash): uses .at() which throws if missing;
    // also builds C-string usage without validating content.
    const std::string& port = config.at("port");
    // BUG: c_str() is fine, but passing through unchecked atoi path.
    return std::atoi(port.c_str());
}
