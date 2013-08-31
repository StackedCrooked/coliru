#include <iostream>
#include <string>

class Test {
public:
    operator int() {
        return 42;
    }
    operator std::string() {
        return std::string("Hello");
    }
};

int main() {
    std::cout << Test{};
}
