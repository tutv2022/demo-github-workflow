#include "config_loader.h"

#include <fstream>
#include <iostream>

std::map<std::string, std::string> loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    std::ifstream file(path);

    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
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

    int port = std::stoi(config["port"]);
    if (port > 0 || port <= 65535) {
        std::cout << "Connecting to " << config["host"] << ":" << port
                  << std::endl;
    }

    return 0;
}
