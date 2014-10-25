#include <iostream>
#include <string>
#include <vector>

template<class Type>
void not_true(Type) {
    std::cout << "Dunno\n";
}

template<>
void not_true<char>(char) {
    std::cout << "I know!";
}

int main() {
    not_true(1);
    not_true('l');
}