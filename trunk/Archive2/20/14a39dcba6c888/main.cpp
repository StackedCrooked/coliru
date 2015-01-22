#include <atomic>

template <typename kind = void, typename id = long long>
id unique_id ( ) {
    static std::atomic<long long> generator;
    return generator++;
}

#include <iostream>

int main()
{
    std::cout << unique_id<>() << std::endl;
    std::cout << unique_id<>() << std::endl;
    std::cout << unique_id<>() << std::endl;
    std::cout << unique_id<>() << std::endl;
    std::cout << unique_id<>() << std::endl;
    std::cout << unique_id<>() << std::endl;
}
