#include "string_utils.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// BUG: fixed-size buffer with unbounded input -> classic buffer overflow crash.
void formatGreeting(const char* name) {
    char buffer[32];
    // BUG (nullPtr crash): name may be nullptr.
    sprintf(buffer, "Hello, %s! Welcome back.", name);
    printf("%s\n", buffer);
}

// BUG: division by zero crash when the string is empty.
double averageCharCode(const std::string& s) {
    int sum = 0;
    for (size_t i = 0; i < s.size(); i++) {
        sum += static_cast<unsigned char>(s[i]);
    }
    return static_cast<double>(sum) / static_cast<double>(s.size());
}

// BUG: returns a pointer to a local (stack) buffer -> use-after-return crash/UB.
const char* toUpper(const char* input) {
    char result[256];
    // BUG (nullPtr crash): input may be nullptr.
    size_t len = strlen(input);
    for (size_t i = 0; i < len && i < sizeof(result) - 1; i++) {
        result[i] = static_cast<char>(toupper(static_cast<unsigned char>(input[i])));
    }
    result[len < sizeof(result) - 1 ? len : sizeof(result) - 1] = '\0';
    return result;
}

std::string removeDuplicates(std::string s) {
    for (size_t i = 0; i < s.size(); i++) {
        for (size_t j = i + 1; j < s.size(); j++) {
            if (s[i] == s[j]) {
                s.erase(j, 1);
                // BUG: j is not decremented after erase.
            }
        }
    }
    return s;
}

// BUG: atoi silently returns 0 on invalid input; nullptr input crashes.
int parsePort(const char* portStr) {
    // BUG (nullPtr crash): no check before atoi(portStr).
    int port = atoi(portStr);
    return port;
}

const char* firstCharAsCString(const char* text) {
    // BUG (nullPtr crash): dereferences text with no null check.
    // Also returns address of a temporary/local-style misuse via static buffer overwrite.
    static char one[2];
    one[0] = text[0];
    one[1] = '\0';
    return one;
}
