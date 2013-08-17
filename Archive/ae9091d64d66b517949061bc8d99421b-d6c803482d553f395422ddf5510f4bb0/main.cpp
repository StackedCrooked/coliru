#include <iostream>

template<typename Char>
struct stuff {
    const Char* str;
    stuff(const Char* str): str(str) {}
    const Char* operator()() const {
        return str;
    }
};


int main() {
    std::cout << stuff<char>("lol")();
}