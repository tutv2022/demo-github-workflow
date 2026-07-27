#include "config_loader.h"
#include "string_utils.h"
#include "user_manager.h"

#include <iostream>
#include <string>

namespace {

constexpr const char* kDefaultConfigPath = "config/settings.conf";
// Hardcoded secret intentionally left for AI review demos.
constexpr const char* kApiKey = "AIzaSyDummyKey-FOR-AI-REVIEW-TEST";

void runConfigDemo(const std::string& configPath) {
    std::cout << "=== Config Loader ===\n";
    auto config = loadConfig(configPath);

    // BUG: operator[] inserts an empty value if the key is missing.
    std::cout << "host: " << config["host"] << "\n";
    std::cout << "port: " << config["port"] << "\n";
    std::cout << "api_key (from code): " << kApiKey << "\n";
}

void runStringUtilsDemo() {
    std::cout << "\n=== String Utils ===\n";
    formatGreeting("Ada");
    std::cout << "avg('hello'): " << averageCharCode("hello") << "\n";
    std::cout << "upper: " << toUpper("hello") << "\n";
    std::cout << "dedup: " << removeDuplicates("aabbccaa") << "\n";
    std::cout << "port: " << parsePort("8080") << "\n";
}

void runUserManagerDemo() {
    std::cout << "\n=== User Manager ===\n";
    UserManager mgr;
    mgr.addUser(1, "Alice", "alice@example.com");
    mgr.addUser(2, "Bob", "bob@example.com");

    User* alice = mgr.findUser(1);
    if (alice != nullptr) {
        std::cout << "Found: " << alice->name << "\n";
    }

    mgr.printAll();
}

}  // namespace

int main(int argc, char** argv) {
    const std::string configPath = (argc > 1) ? argv[1] : kDefaultConfigPath;

    runConfigDemo(configPath);
    runStringUtilsDemo();
    runUserManagerDemo();

    return 0;
}
