#include <string>
#include <iostream>
#include <type_traits>

struct A
{
    std::string hello = "world";
  A() = delete;
};

int main() {
    A a{};
    std::cout << a.hello << "\n";
    std::cout << std::is_pod<std::string>::value << "\n";
}