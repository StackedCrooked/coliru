#include <string>

struct S {
    S() {
        new (&s) std::string("hi");
    }

    ~S() {
        s.std::string::~basic_string();
    }

    union {
        std::string s;
    };
};

int main() {}