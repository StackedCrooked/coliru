#include <iostream>
#include <cstdio>

struct log {
    void logf(std::string, std::string, const char*, ...) __attribute__((format (printf, 4, 5))) {}
};

#define L(m, ...) loglog.logf("no", __func__, (m), __VA_ARGS__)

int main() {
    log loglog;
    //log::logf("hi", "hi", "test %u", "hi");
    L("test %u", "hi");
}

