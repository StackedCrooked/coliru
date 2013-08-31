#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>
using std::begin;
using std::end;

template <typename ContainerType>
void print(const ContainerType & container)
{
    for (auto && element : container) std::cout << element << ' ';
    std::cout << '\n';
}

template <typename ContainerType>
void shuffle(const ContainerType & container)
{
    std::random_shuffle(begin(container), end(container));
}

template <typename ContainerType>
void sort(ContainerType & container)
{
    std::sort(begin(container), end(container));
}

int main()
{
    std::list<int> container(10);
    std::iota(begin(container), end(container), 1);
    print(container);
    sort(container);
    print(container);
}
