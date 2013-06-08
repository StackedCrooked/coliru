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
    using iterator_type = decltype(begin(container));
    using iterator_traits = std::iterator_traits<iterator_type>;
    using iterator_category = typename iterator_traits::iterator_category;
    static_assert(std::is_same<iterator_category, std::random_access_iterator_tag>::value,
                  "Shuffling requires a Random Access Container.");

    std::random_shuffle(begin(container), end(container));
}

template <typename ContainerType>
void sort(ContainerType & container)
{
    using iterator_type = decltype(begin(container));
    using iterator_traits = std::iterator_traits<iterator_type>;
    using iterator_category = typename iterator_traits::iterator_category;
    static_assert(std::is_same<iterator_category, std::random_access_iterator_tag>::value,
                  "Sorting requires a Random Access Container.");
    
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
