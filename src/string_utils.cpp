#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// String utilities with security issues and edge-case bugs
// for the AI reviewer to catch.

// BUG: fixed-size buffer with unbounded input -> classic buffer overflow.
void formatGreeting(const char* name) {
    char buffer[32];
    sprintf(buffer, "Hello, %s! Welcome back.", name);
    printf("%s\n", buffer);
}

// BUG: division by zero when the string is empty.
double averageCharCode(const std::string& s) {
    int sum = 0;
    for (size_t i = 0; i < s.size(); i++) {
        sum += s[i];
    }
    return sum / s.size();
}

// BUG: returns a pointer to a local (stack) buffer.
const char* toUpper(const char* input) {
    char result[256];
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        result[i] = toupper(input[i]);
    }
    result[len] = '\0';
    return result;
}

// Inefficient O(n^2) implementation; also mutates the input by value copy.
std::string removeDuplicates(std::string s) {
    for (size_t i = 0; i < s.size(); i++) {
        for (size_t j = i + 1; j < s.size(); j++) {
            if (s[i] == s[j]) {
                s.erase(j, 1);
                // BUG: j is not decremented after erase, so consecutive
                // duplicates are skipped.
            }
        }
    }
    return s;
}

// BUG: atoi silently returns 0 on invalid input, no error handling.
int parsePort(const char* portStr) {
    int port = atoi(portStr);
    return port;  // No range validation (1-65535) either.
}

int main() {
    formatGreeting("A very long user name that definitely does not fit in the buffer");
    printf("avg: %f\n", averageCharCode(""));
    printf("upper: %s\n", toUpper("hello"));
    printf("dedup: %s\n", removeDuplicates("aabbccaa").c_str());
    printf("port: %d\n", parsePort("not-a-number"));
    return 0;
}
