#include <iostream>
#include <string>

struct test {
    constexpr static const char* description = "Testing a static description!\n";
};

int main() {
    std::cout << test::description << "\n";
    return 0;
}