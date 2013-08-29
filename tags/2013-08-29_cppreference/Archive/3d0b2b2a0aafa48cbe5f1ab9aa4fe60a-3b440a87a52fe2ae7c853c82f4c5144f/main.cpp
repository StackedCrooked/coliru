#include <iostream>
int main() {
    int caught = 1986;
    auto f = [=](){return caught;};
    std::cout << f();
}