#include <iostream>

class Test {
public:
    operator int() {
        return 42;
    }
};

int main() {
    std::cout << Test{};
}
