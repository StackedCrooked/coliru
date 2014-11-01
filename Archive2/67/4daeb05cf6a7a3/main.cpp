#include <iostream>

class c {
public:
    c() {
        std::cout << "c::c\n";
    }

    ~c() {
        std::cout << "c::~c\n";
    }
};

c o;

int main() {
    std::cout << "main\n";
    return 0;
}