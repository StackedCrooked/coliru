#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename Range> bool if_sorted(Range const &r) {
    using std::begin;
    using std::end;

    auto f(begin(r)),
         l(end(r));

    if (f==l || std::next(f)==l)
        return true;

    return l == std::adjacent_find(f,l,std::greater_equal<int>());
}

int main()
{
    std::vector<int> v(10);
    do    std::generate_n(v.begin(), v.size(), rand);
    while (!if_sorted(v));

    std::cout << "Yay, found a vector that was accidentally sorted: \n";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));

}
