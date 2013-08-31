#include <iostream>
#include <string>
#include <vector>
#include <functional>

std::function<void()> get(std::vector<std::string>& v, int i) {
    std::string& r = v[i];
    auto lambda = [&r](){r="!!!!";}; //lambda contains a reference to a particular string.
    return {lambda};
}

int main() {
    std::vector<std::string> v = {"HI", "HELLO", "WORLD"};
    std::function<void()> f; //this is like 8 bytes or something.
    f = get(v, 1); //now contains a lambda which contains a reference to the second string in v, which takes space
    std::cout << v[1];
    f(); //modifies the second string.
    std::cout << v[1];
}