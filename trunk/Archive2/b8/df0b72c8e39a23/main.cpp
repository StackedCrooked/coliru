#include <vector>
#include <iostream>

struct S {
    std::vector<int>&& vec;
};

int main() {
    S s1{std::vector<int>(5)}; // construct with temporary
    std::cout << "foo bar";
    std::cout << s1.vec[0] << '\n'; // fine, temporary is alive

    return 0;
}