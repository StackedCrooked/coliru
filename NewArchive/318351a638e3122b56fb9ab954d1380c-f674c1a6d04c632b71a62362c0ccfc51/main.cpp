#include <iostream>


template<typename... T>
double average(T&&... args) {
    int f[sizeof...(args)] = { args... };
    double total = 0;
    for(auto&& i : f)
        total += i;
    
    return total / sizeof...(args);
}

int main() {
    std::cout << average(1,2,3,4,5,6,7,8);
}