#include <iostream>
#include <string>
#include <vector>

template<typename CharT, CharT... String>
constexpr int operator"" _test() {
    return sizeof...(String) + sizeof(CharT);
}

int main() {
    return "hello"_test;
}
