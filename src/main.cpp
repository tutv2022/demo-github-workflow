#include "config_loader.h"
#include "crash_bugs.h"
#include "string_utils.h"
#include "user_manager.h"

#include <cstring>
#include <iostream>
#include <string>

namespace {

constexpr const char* kDefaultConfigPath = "config/settings.conf";
constexpr const char* kApiKey = "AIzaSyDummyKey-FOR-AI-REVIEW-TEST";

void runConfigDemo(const std::string& configPath) {
    std::cout << "=== Config Loader ===\n";
    auto config = loadConfig(configPath);
    std::cout << "host: " << config["host"] << "\n";
    std::cout << "port: " << config["port"] << "\n";
    std::cout << "api_key (from code): " << kApiKey << "\n";
}

void runStringUtilsDemo() {
    std::cout << "\n=== String Utils ===\n";
    formatGreeting("Ada");
    std::cout << "avg('hello'): " << averageCharCode("hello") << "\n";
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

// Default path stays runnable. Pass --crash to exercise nullPtr crash bugs.
void runCrashBugDemo() {
    std::cout << "\n=== Crash / NullPtr Bugs ===\n";

    // 1) Nullptr strlen
    std::cout << "unsafeStrLen(nullptr)...\n";
    (void)unsafeStrLen(nullptr);

    // 2) Write into nullptr buffer
    std::cout << "fillGreeting(nullptr)...\n";
    fillGreeting(nullptr, "Ada");

    // 3) allocateBuffer(0) returns nullptr, then write
    char* buf = allocateBuffer(0);
    std::cout << "write into zero-size buffer...\n";
    std::strcpy(buf, "boom");

    // 4) Nested null session
    Session session;
    session.userId = nullptr;
    std::cout << "readSessionUserId with null userId...\n";
    (void)readSessionUserId(&session);

    // 5) Use-after-free
    char* token = makeThenFreeToken("abc");
    std::cout << "use after free: " << token << "\n";
    releaseBuffer(token);  // double-free

    // 6) UserManager unchecked null deref
    UserManager mgr;
    mgr.addUser(1, "Alice", "alice@example.com");
    std::cout << "getEmailOrCrash(missing id)...\n";
    std::cout << mgr.getEmailOrCrash(999) << "\n";
}

}  // namespace

int main(int argc, char** argv) {
    bool triggerCrash = false;
    std::string configPath = kDefaultConfigPath;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--crash") {
            triggerCrash = true;
        } else {
            configPath = argv[i];
        }
    }

    runConfigDemo(configPath);
    runStringUtilsDemo();
    runUserManagerDemo();

    if (triggerCrash) {
        runCrashBugDemo();
    } else {
        std::cout << "\n(Tip: pass --crash to trigger nullPtr / crash demos)\n";
    }

    return 0;
}
