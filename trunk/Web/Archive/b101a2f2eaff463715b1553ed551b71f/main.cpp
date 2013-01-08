#include <iostream>
#include <functional>

void myFunction(std::function<void(void)> f) {
    std::cout << "Calling function f...\n";
    f();
}

void f() {
    std::cout << "function f called.. \n";
}

int main() {
    myFunction(f);
    myFunction([](){ std::cout << "lambda called this time..\n";});
}