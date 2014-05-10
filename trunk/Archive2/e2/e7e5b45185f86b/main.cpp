#include <iostream>
#include <functional>
#include <utility>
#include <type_traits>

template <typename T>
struct foo
{
    foo()
    { static_assert(sizeof(T) <= a_.size(), "foo"); }
    
    std::array<char, 8> a_;
};

int main()
{
    foo<long long> f;
    std::cout << "good" << std::endl;
}