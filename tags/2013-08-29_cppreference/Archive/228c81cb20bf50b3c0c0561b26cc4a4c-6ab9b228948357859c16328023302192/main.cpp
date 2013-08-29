#include <functional>
#include <iostream>

#define SC(A) static_cast<char>(fac(5)-(A))

template<class F>
std::function<int(int)> fix(F f){
    return [=](int i){ return f(fix(f), i); };
}

int main(){
    auto fac = fix([](std::function<int(int)> f, int i){return i == 0 ?1: i * f(i-1); });
    std::cout << SC(18) << SC(12) << SC(9) << SC(6) << SC(15) << SC(5);
    return 0;
}