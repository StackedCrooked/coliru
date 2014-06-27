#include <algorithm>
#include <cassert>
#include <forward_list>
#include <iostream>
#include <ios>
#include <iterator>

// returns an iterator before first element equal to value, or last if no such element is present
// pre-condition: before_first is incrementable and not equal to last
template<class FwdIt, class T>
FwdIt find_before(FwdIt before_first, FwdIt last, T const& value)
{
    assert(before_first != last);
    auto first = std::next(before_first);
    if (first == last) return last;
    if (*first == value) return before_first;
    return std::adjacent_find(first, last, [&](auto const&, auto const& R) { 
        return R == value; 
    });
}

int main() 
{
    auto e = std::forward_list<int>{};
    std::cout << std::boolalpha << (++e.before_begin() == end(e)) << "\n";
    std::cout << (find_before(e.before_begin(), end(e), 0) == end(e)) << "\n";
    
    auto s = std::forward_list<int>{ 0 };
    std::cout << (find_before(s.before_begin(), end(s), 0) == s.before_begin()) << "\n";
    
    auto d = std::forward_list<int>{ 0, 1 };
    std::cout << (find_before(d.before_begin(), end(d), 0) == d.before_begin()) << "\n";
    std::cout << (find_before(d.before_begin(), end(d), 1) == begin(d)) << "\n";
    std::cout << (find_before(d.before_begin(), end(d), 2) == end(d)) << "\n";

    // erase after
    auto m = std::forward_list<int>{ 1, 2, 3, 4, 1, 3, 5 };
    auto it = find_before(m.before_begin(), end(m), 3);
    if (it != end(m)) 
        m.erase_after(it);
    std::copy(begin(m), end(m), std::ostream_iterator<int>(std::cout, ","));
}
