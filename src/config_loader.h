#pragma once

#include <map>
#include <string>

// Loads KEY=VALUE pairs from a simple config file.
std::map<std::string, std::string> loadConfig(const std::string& path);

// Returns the value for key, or defaultValue when missing.
std::string getConfigValue(const std::map<std::string, std::string>& config,
                           const std::string& key,
                           const std::string& defaultValue = "");

// Returns getenv(name) with no null checks (crash risk).
const char* requireEnvOrCrash(const char* name);

// Reads config["port"] with unchecked access (throws / crashes on misuse).
int parseConfigPortOrCrash(const std::map<std::string, std::string>& config);
