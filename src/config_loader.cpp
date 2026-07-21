#include <fstream>
#include <iostream>
#include <map>
#include <string>

// Naive config loader with a few issues for the AI reviewer.

std::map<std::string, std::string> loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    std::ifstream file(path);
    // BUG: no check that the file actually opened.

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        // BUG: lines without '=' produce key = whole line, value = garbage
        // (substr(npos + 1) happens to be 0, but the intent is unclear).
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        config[key] = value;  // No trimming, no comment handling.
    }
    return config;
}

int main() {
    auto config = loadConfig("/etc/myapp/settings.conf");
    // BUG: operator[] inserts an empty value if the key is missing,
    // silently masking configuration errors.
    std::cout << "host: " << config["host"] << std::endl;
    std::cout << "port: " << config["port"] << std::endl;
    return 0;
}
