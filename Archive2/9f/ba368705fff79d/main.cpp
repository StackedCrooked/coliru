#include <iostream>

template<typename Function> 
struct deferred_wrapper {
    Function callback;
    
    deferred_wrapper(const Function& f) : callback{f} {}
    deferred_wrapper(Function&& f) : callback{std::move(f)} {}
    
    ~deferred_wrapper() { callback(); }
};

template<typename Function>
deferred_wrapper<Function> defer(Function&& f) {
    return deferred_wrapper<Function>{std::forward<Function>(f)};
}

int main() {
    int i = 0;
    auto deferred = defer([&] { std::cout << i++ << '\n'; });
    {
        auto deferred = defer([&] { std::cout << i++ << '\n'; });
    }
    {
        auto deferred = defer([&] { std::cout << i++ << '\n'; });
    }
}