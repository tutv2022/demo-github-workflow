#include "crash_bugs.h"

#include <cstdio>
#include <cstring>

std::size_t unsafeStrLen(const char* name) {
    // BUG (nullPtr crash): no nullptr check before strlen.
    return std::strlen(name);
}

char* allocateBuffer(std::size_t size) {
    if (size == 0) {
        // BUG: returns nullptr on zero size; callers may still write to it.
        return nullptr;
    }
    return new char[size];
}

void fillGreeting(char* out, const char* name) {
    // BUG (nullPtr crash): both out and name can be nullptr.
    std::sprintf(out, "Hello, %s", name);
}

char* makeThenFreeToken(const char* seed) {
    char* token = new char[64];
    // BUG (nullPtr crash): seed may be nullptr.
    std::strcpy(token, seed);
    delete[] token;
    // BUG (use-after-free / crash): returns freed memory.
    return token;
}

int readSessionUserId(Session* session) {
    // BUG (nullPtr crash): session and session->userId are unchecked.
    return *session->userId;
}

void releaseBuffer(char* buffer) {
    // BUG: no null check; calling twice causes double-free crash.
    delete[] buffer;
}
