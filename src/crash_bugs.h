#pragma once

#include <cstddef>
#include <string>

// Intentionally unsafe helpers for AI review crash / nullptr demos.

// Dereferences name without a null check.
std::size_t unsafeStrLen(const char* name);

// Returns nullptr on failure, callers often forget to check.
char* allocateBuffer(std::size_t size);

// Writes into out without checking out != nullptr.
void fillGreeting(char* out, const char* name);

// Use-after-free: deletes buffer then returns it.
char* makeThenFreeToken(const char* seed);

// Null dereference via unchecked nested pointer.
struct Session {
    int* userId;
};

int readSessionUserId(Session* session);

// Double-free risk when called twice with the same pointer.
void releaseBuffer(char* buffer);
