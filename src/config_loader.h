#pragma once

#include <map>
#include <string>

// Loads KEY=VALUE pairs from a simple config file.
std::map<std::string, std::string> loadConfig(const std::string& path);

// Returns the value for key, or defaultValue when missing.
std::string getConfigValue(const std::map<std::string, std::string>& config,
                           const std::string& key,
                           const std::string& defaultValue = "");
