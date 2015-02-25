#include <iostream>
#include <functional>
#include <chrono>

void by_value(std::function<int()> ting) {
    ting();
}

void by_const_value(const std::function<int()> ting) {
    ting();
}

void by_ref(std::function<int()>& ting) {
    ting();
}

void by_const_ref(std::function<int()> const& ting) {
    ting();
}


int main() {
    using clock = std::chrono::high_resolution_clock;
    
    int x = 0;
    int y = 0;
    int z = 0;
    
    auto lambda = [x,y,z]() -> int {
        return x + y + z;
    };
    
    std::function<int()> fn(lambda);
    
    {
        auto point = clock::now();
        for(size_t i = 0; i < 30000000; ++i) {
            by_value(fn);
        }
        std::cout << "by value: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - point).count() << std::endl;
    }
    
    {
        auto point = clock::now();
        for(size_t i = 0; i < 30000000; ++i) {
            by_const_value(fn);
        }
        std::cout << "by const value: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - point).count() << std::endl;
    }
    
    {
        auto point = clock::now();
        for(size_t i = 0; i < 30000000; ++i) {
            by_ref(fn);
        }
        std::cout << "by ref: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - point).count() << std::endl;
    }
    
    {
        auto point = clock::now();
        for(size_t i = 0; i < 30000000; ++i) {
            by_const_ref(fn);
        }
        std::cout << "by const ref: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - point).count() << std::endl;
    }
    
    return 0;
}