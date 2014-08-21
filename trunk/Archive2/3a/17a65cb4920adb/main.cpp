#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

template <typename I>
using ValueType = typename std::iterator_traits<I>::value_type;

template<class ForwardIterator>
std::vector<ValueType<ForwardIterator>>
get_odd(ForwardIterator data_begin, ForwardIterator data_end)
{
    std::vector<ValueType<ForwardIterator>> ret;
    std::copy_if(data_begin, data_end, std::back_inserter(ret), [](int x) { return x % 2; });
    return ret;
}

int main()
{
    std::vector<int> vi { 1, 2, 3, 4, 5 };
    for (auto i : get_odd<int>(vi.begin(), vi.end()))
        std::cout << i << ", ";
    std::cout << std::endl;

    std::vector<unsigned int> vui{ 9UL, 8UL, 7UL, 6UL, 5UL };
    // Note the 'char' I provided to the function, this will print weird chars
    for (auto i : get_odd<char>(vui.begin(), vui.end()))
        std::cout << i << ", ";
    std::cout << std::endl;
}
