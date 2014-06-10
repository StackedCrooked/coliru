#include <iostream>
#include <iterator>

int main() {
    for (auto it = "Hello"; it != "there"; ++it) {
        std::cout << *it << ' ' << +*it << '\n';   
    }
}