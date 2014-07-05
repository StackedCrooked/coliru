#include <string>
#include <iostream>
#include <utility>

void print(std::string&& x) {}

int main() {
    std::string fmt = "x";
    print(fmt);
}