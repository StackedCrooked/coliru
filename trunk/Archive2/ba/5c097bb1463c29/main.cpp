#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>

template<class FwdIt, class T>
FwdIt find_before_first(FwdIt first, FwdIt last, T const& value)
{
     return std::adjacent_find(first, last, [&](int const&, int const& R) { return R == value; });
}

int main() 
{
     auto mylist = std::forward_list<int>{ 1, 2, 3, 4, 3, 5 };
     mylist.erase_after(find_before_first(begin(mylist), end(mylist), 3));
     std::copy(begin(mylist), end(mylist), std::ostream_iterator<int>(std::cout, ","));
}
