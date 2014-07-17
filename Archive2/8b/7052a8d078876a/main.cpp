#include <iostream>
#include <typeindex>
#include <utility>

int main() {
    std::cout << std::hash<std::type_index>()(std::type_index(typeid(int))) << '\n';
    std::cout << std::hash<std::type_index>()(std::type_index(typeid(double))) << '\n';
}