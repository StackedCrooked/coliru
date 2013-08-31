#include <initializer_list>
#include <iostream>

struct S {
    S(int);
    S(std::initializer_list<int>){std::cout << "foo";}
};

int main() {
    S{};
}