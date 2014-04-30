#include <vector>
#include <cstdint>
#include <deque>

template <typename V>
    std::deque<std::size_t> dims_of(V const& v) {
    return {};
}

template <typename T>
    std::deque<std::size_t> dims_of(std::vector<T> const& v)
{
    if (v.empty())
        return { 0 };
    else
    {
        auto dims = dims_of(v.front());
        dims.push_front(v.size());
        return dims;
    }
}

#include <iostream>

int main()
{
    std::vector<std::vector<std::vector<int> > > const
        v(7, std::vector<std::vector<int> >(
            10, std::vector<int>(3, 0)
            )
         );

    for (auto dim : dims_of(v))
        std::cout << dim << " ";

} 
