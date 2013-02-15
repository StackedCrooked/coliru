#include <functional>
#include <iostream>

void foo(int, char const* p){
    std::cout << p << "\n";
}

struct true_{
    template<class F, class... Args>
    bool operator()(F f, Args&&... args){
        return f(args...), true;
    }
};

int main(){
    using namespace std::placeholders;
    std::function<void(int, char const*, bool)> f(std::bind(true_(), foo, 1, _2));
    f(42, "hi", true);
}