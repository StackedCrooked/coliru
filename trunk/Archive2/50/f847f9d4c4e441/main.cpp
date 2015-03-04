#include <iostream>
const int t = 2010101010;

int add(int i){
    return t + i;
}

template<class U>
int add2(U i){
    return t + i;
}

int main() {
    std::cout << add(1.f) << std::endl;
    std::cout << add2(1.f) << std::endl;
}