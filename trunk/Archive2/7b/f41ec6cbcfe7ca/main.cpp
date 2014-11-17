#include <iterator>
#include <vector>
#include <iostream>

template<typename ForwardIterator, typename T>
void strided_iota(ForwardIterator first, ForwardIterator last, T value, T stride)
{
    while(first != last) {
        *first++ = value;
        value += stride;
    }
}

int main()
{
    std::vector<float> vec(10);
    strided_iota(std::begin(vec), std::next(std::begin(vec), 5), 2.0f, 0.5f);
    
    for(auto e : vec) { std::cout << e << '\n'; }
}
