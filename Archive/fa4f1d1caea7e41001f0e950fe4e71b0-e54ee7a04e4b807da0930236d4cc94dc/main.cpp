#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

template<typename T, typename U>
std::vector<std::pair<T, U>> zip(std::vector<T> const& vt, std::vector<U> const& vu)
{
    std::vector<std::pair<T, U>> v;
    std::transform(
        begin(vt), 
        std::next(std::begin(vt), std::min(vt.size(), vu.size())), 
        begin(vu), 
        std::back_inserter(v), 
        [] (T const& t, U const u) { return std::make_pair(t, u); });
        
    return v;
}

int main()
{
    std::vector<int> vi { 1, 2, 3 };
    std::vector<char> vb { 'a', 'b' };
    
    auto v = zip(vi, vb);
    for (auto const& p : v)
    {
        std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
    }
}