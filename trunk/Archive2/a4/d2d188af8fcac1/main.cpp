#include <functional>
#include <iostream> 

template<typename Ret, typename... Args>
int fargs(const std::function<Ret(Args...)> &) {
    return sizeof...(Args);   
}

int main() {
    std::function<void(int, int, int)> f{[](int, int, int){}};
    std::function<void(int)> g{[](int){}};
    std::function<void()> h{[]{}};
    
    std::cout << fargs(f) << ' ' << fargs(g) << ' ' << fargs(h) << '\n';
}