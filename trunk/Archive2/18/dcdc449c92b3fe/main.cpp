#include <iostream>
#include <utility>

void foo(int &) {
    std::cout << "int &\n";
}

void foo(int &&) {
    std::cout << "int &&\n";   
}

template<typename T>
void bar(T &&t) {
    foo(std::forward<T>(t));   
}

int main() {
    bar(1);
    
    int i{};
    bar(i);
}