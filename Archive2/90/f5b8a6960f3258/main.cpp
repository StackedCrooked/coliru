#include <vector>
#include <iostream>


template<typename T, size_t N>
void f(const T(&arr)[N]) {
    std::cout << N << '\n';
}


int main() {
    int x[] = {1,2,3,4};
    int y[] = {1,2,3,4,5};
    int z[] = {1,2,3};
    
    f(x);
    f(y);
    f(z);
}