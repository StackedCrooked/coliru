#include <functional>
#include <iostream>

void f(int a, int b){
    std::cout << "a: " << a << ", b: " << b << "\n";
}

int main(){
    using namespace std::placeholders;
    std::bind(f, _1, _3)(1,2,3);
}