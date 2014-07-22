#include <iostream>

extern "C" {
inline void blah() {
    std::cout << "123" << std::endl;
}
}

namespace NN {
extern "C" {
inline void blah() {
    std::cout << "123" << std::endl;
}
}
}

int main() {
    blah();
    return 0;
}
