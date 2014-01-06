#include <vector>
#include <iostream>

template <typename Iter, typename SomeFunction>                         
void wrap(Iter first, Iter last, SomeFunction someFunction)
{
    someFunction(first, last);
}

template <typename Iter>
void fill5(Iter first, Iter last)
{
    fill(first, last, 5); 
}

#define WRAP(f) \
    [&] (auto&&... args) { f (std::forward<decltype(args)>(args)...); }

int main()
{
    std::vector<int> v(100, -1);
    wrap(v.begin(), v.end(), WRAP(fill5));
    std::cout << v[42];
}