#include <iostream>

namespace {
    bool& hasAccess() {
        static bool haveAccess = false;
        return haveAccess;
    }
}

void myMethod() {
    hasAccess() = true;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << "HasAccess: " << hasAccess() << std::endl;
    myMethod();
    std::cout << "HasAccess: " << hasAccess() << std::endl;
    return 0;
}