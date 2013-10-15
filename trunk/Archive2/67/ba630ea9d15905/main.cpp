#include <iostream>
#include <functional>
#include <string>

namespace std
{
    template<>
    struct plus<void> 
    { 
        template<typename T, typename U>
        auto operator()(T && t, U && u) -> decltype(std::forward<T>(t) + std::forward<U>(u))
        {
            return std::forward<T>(t) + std::forward<U>(u);
        }
    };
}

int main()
{
    std::plus<void> add{}; //in C++14, you can just write std::plus<> instead of plus<void>
    
    std::cout << add(10, 20) << std::endl;
    std::cout << add(std::string("Hello"), " World!") << std::endl;
    std::cout << add("Sarfaraz", std::string(" Nawaz")) << std::endl;
}