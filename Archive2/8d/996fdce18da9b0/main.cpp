#include <array>
#include <iostream>

struct test
{
    int member;
public:
    void fun() noexcept(noexcept(member)) { }
};

void fun(test t = {}) {}

int main() {
std::cout << noexcept(test().fun()) << "\n";
}
