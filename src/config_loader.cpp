#include "config_loader.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

// Intentionally buggy helpers for AI PR-review testing.

namespace {

// BUG: hardcoded secret committed in source.
const char* kDbPassword = "SuperSecretPassword123!";
const char* kApiKey = "AIzaSyDummyKey-FOR-AI-REVIEW-TEST";

// BUG: returns pointer to stack memory (dangling pointer after return).
const char* buildConnectionString(const std::string& host, int port) {
    char buffer[128];
    sprintf(buffer, "postgres://admin:%s@%s:%d/app", kDbPassword, host.c_str(),
            port);
    return buffer;
}

}  // namespace

std::map<std::string, std::string> loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    std::ifstream file(path);

    // BUG: never checks whether the file opened successfully.

    std::string line;
    // BUG: eof() loop processes a failed final read and can insert empty keys.
    while (!file.eof()) {
        std::getline(file, line);

        // BUG: no handling for missing '=' (npos), comments, or blank lines.
        size_t pos = line.find('=');
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        config[key] = value;
        std::cout << "Loaded setting " << key << "=" << value << std::endl;
    }
    return config;
}

int main(int argc, char* argv[]) {
    const std::string path =
        argc > 1 ? argv[1] : "/etc/myapp/settings.conf";
    auto config = loadConfig(path);

    std::cout << "host: " << config["host"] << std::endl;
    std::cout << "port: " << config["port"] << std::endl;
    std::cout << "api_key: " << kApiKey << std::endl;

    // BUG: operator[] inserts empty string if key is missing; stoi then throws
    // or parses garbage. No try/catch around stoi.
    int port = std::stoi(config["port"]);

    // BUG: should be && (AND). With || this is always true for any int.
    if (port > 0 || port <= 65535) {
        const char* conn = buildConnectionString(config["host"], port);
        // BUG: uses dangling pointer from buildConnectionString.
        std::cout << "Connecting with " << conn << std::endl;

        // BUG: command injection if host comes from untrusted config.
        std::string cmd = "ping -c 1 " + config["host"];
        std::system(cmd.c_str());
    }

    // BUG: integer overflow / wrap risk; also divides without checking zero.
    int retries = std::stoi(config["retries"]);
    int delayMs = 1000 / retries;

    char* scratch = new char[64];
    strcpy(scratch, config["host"].c_str());  // BUG: no bounds check vs 64.
    // BUG: memory leak — scratch is never deleted.
    std::cout << "scratch host copy: " << scratch << " delay=" << delayMs
              << std::endl;

    return 0;
}
