#include <iostream>
#include <vector>

namespace foo
{
    struct bar
    {
        std::vector<int> v{ 0, 1, 2 };
    };
    
    using bar_iterator = decltype(bar::v)::iterator;
    using bar_const_iterator = decltype(bar::v)::const_iterator;
    
    bar_iterator begin(bar &b)
    { return b.v.begin(); }
    bar_const_iterator cbegin(bar const &b)
    { return b.v.begin(); }
    
    bar_iterator end(bar &b)
    { return b.v.end(); }
    bar_const_iterator cend(bar const &b)
    { return b.v.cend(); }
}

int main()
{
    foo::bar b;
    for(auto const &i : b)
    { std::cout << i << std::endl; }
}
