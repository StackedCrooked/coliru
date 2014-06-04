#include <iostream>

struct A {
    int z;
    A(std::string) {}
    A() {}
};

int main() {
    char buf[1000];
    std::fill(buf, buf + 1000, 'x');
    auto a = new(buf) A{};
    std::cerr << "A.z: " << a->z << std::endl;
}
