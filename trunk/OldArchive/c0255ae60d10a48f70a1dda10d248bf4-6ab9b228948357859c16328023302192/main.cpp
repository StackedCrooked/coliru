#include <functional>

template<class F>
std::function<int(int)> fix(F f){
    return [=](int i){ return f(fix(f), i); };
}

#include <iostream>

int main(){
    using fun = std::function<int(int)>;
    auto fac = fix([](fun f, int i){ return i == 0 ? 1 : i * f(i-1); });
    std::cout << fac(5);
}
