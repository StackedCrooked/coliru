#include <iostream>
#include <string>
#include <type_traits>
struct Ex1 { int n; };
int main() {
    std::cout << std::boolalpha
              << std::is_assignable<int&, int>::value;
}