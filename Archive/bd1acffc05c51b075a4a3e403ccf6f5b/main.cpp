#include <functional>
#include <iostream>

void foo(char const* p){
    std::cout << p << "\n";
}

int main(){
    using namespace std::placeholders;
    std::function<void(int, char const*, bool)> f(std::bind(foo, _2));
    f(42, "hi", true);
}