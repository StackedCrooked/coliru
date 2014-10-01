#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

namespace std
{
    template <typename T>
    auto size(T &c) -> decltype(c.size())
    { return c.size(); }
    template <typename T>
    auto size(T const &c) -> decltype(c.size())
    { return c.size(); }
    template <typename T, std::size_t N>
    std::size_t constexpr size(T (&arr)[N])
    { return N; }
}

template <typename T, typename R>
void more_practical(std::function<R ()> f)
{
    T t{};
    std::generate_n(std::begin(t), std::size(t), f);
    std::copy_n(std::begin(t), std::size(t), std::ostream_iterator<int>(std::cout, " "));
}

int main()
{
    int arr[10]{};
    std::cout << std::size(arr) << std::endl;
    
    std::vector<int> v(10, 0);
    std::cout << std::size(v) << std::endl;
    
    more_practical<int [10], int>([]{ return 0; });
}
