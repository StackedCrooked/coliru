#include <iostream>

struct A1 {
    int z;
    A1(std::string) {}
    A1() = default;
};

struct A2 {
    int z;
    A2(std::string) {}
    A2() {}
};

struct A3 {
    int z;
    A3() = default;
};

int main() {
    char buf[1000];
    std::fill(buf, buf + 1000, 'x');
    auto a1 = new(buf) A1{};
    auto a2 = new(buf + 100) A2{};
    auto a3 = new(buf + 200) A3{};
    std::cerr << "A1.z: " << a1->z << std::endl;
    std::cerr << "A2.z: " << a2->z << std::endl;
    std::cerr << "A3.z: " << a3->z << std::endl;
}




















