#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename Container, 
         typename It = typename Container::const_iterator, 
         typename T = typename std::iterator_traits<It>::value_type>
bool if_sorted(Container const &container) {
    using std::begin;
    using std::end;

    It l(end(container));
    return l == std::adjacent_find(begin(container),l,std::greater_equal<T>());
}

int main()
{
    std::vector<int> v(10);
    do    std::generate_n(v.begin(), v.size(), rand);
    while (!if_sorted(v));

    std::cout << "Yay, found a vector that was accidentally sorted: \n";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
}
