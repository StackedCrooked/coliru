#include <iostream>
#include <functional>


void doTwice(std::function<void (int)> func) {
    int i = 1;
    func(i);
    func(i);
}

void fun(int i, float j) {
    std::cout << i << "\n";
    std::cout << j << "\n";
}

int main()
{
    std::function<void (int)> proof = std::bind(&fun, std::placeholders::_1, 3.f);
    doTwice(std::bind(&fun, std::placeholders::_1, 3.f));
}
